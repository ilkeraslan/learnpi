#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#ifndef RPI_SIMULATION
#include <pigpio.h>
#endif

#include "learnpi.h"
#include "functions.h"

extern int yydebug;
extern FILE *yyin;
int is_file = 0;

// Hash a symbol using its string
static unsigned symhash(char *sym) {
  unsigned int hash = 0;
  unsigned c;
  while((c = *sym++)) {
    hash = hash*9 ^ c;
  }

  return hash;
}

// Function to lookup variables in symbol table
struct symbol *lookup(char* sym) {
  struct symbol *sp = &symtab[symhash(sym)%NHASH];
  int scount = NHASH;		/* how many have we looked at */

  while(--scount >= 0) {
    if(sp->name && !strcmp(sp->name, sym)) { 
      printf("Value already declared.\n");
      return sp; 
    }

    if(!sp->name) {		/* new entry */
        sp->name = strdup(sym);
        sp->value = NULL;
        sp->func = NULL;
        sp->syms = NULL;
        return sp;
    }

    if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
  }

  yyerror("LOOKUP: symbol table overflow\n");
  abort(); /* tried them all, table is full */
}

// Function for new declaration
struct ast *new_declaration(char *s, int type) {
  struct declare_symbol *declaration = malloc(sizeof(struct declare_symbol));

  if(!declaration) {
    yyerror("out of space");
    exit(0);
  }
  
  declaration->nodetype = DECLARATION;
  declaration->type = type;
  declaration->s = s;
  
  return (struct ast *)declaration;
}

// Function for new variable agisnment
struct ast * new_assignment(char *s, struct ast *v) {
  struct symasgn *assignment = malloc(sizeof(struct symasgn));

  if(!assignment) {
    yyerror("out of space");
    exit(0);
  }

  assignment->nodetype = ASSIGNMENT;
  assignment->s = s;
  assignment->v = v;

  return (struct ast *)assignment;
}

// Function for new complex variable assignment
struct ast *new_complex_assignment(char *s, int type, struct ast *value) {
  struct assign_and_declare_complex_symbol *complex_value = malloc(sizeof(struct assign_and_declare_complex_symbol));

  if(!complex_value) {
    yyerror("out of space");
    exit(0);
  }

  complex_value->nodetype = COMPLEX_ASSIGNMENT;
  complex_value->type = type;
  complex_value->value = value;
  complex_value->s = s;

  return (struct ast *)complex_value;
}

// Function to create an AST with generic node type and one child
struct ast *new_ast_with_child(int type, struct ast *l) {
  struct ast *ast = malloc(sizeof(struct ast));

  if(!ast) {
    yyerror("out of space");
    exit(0);
  }

  ast->nodetype = type;
  ast->l = l;
  ast->r = NULL;
  return ast;
}

// Function to create an AST with generic node type and two children
struct ast *new_ast_with_children(int type, struct ast *l, struct ast *r) {
  struct ast *ast = malloc(sizeof(struct ast));

  if(!ast) {
    yyerror("out of space");
    exit(0);
  }

  ast->nodetype = type;
  ast->l = l;
  ast->r = r;

  return ast;
}

// Function to create a new value
struct ast *new_value(struct val *value) {
  struct constant_value *ast = malloc(sizeof(struct constant_value));

  if(!ast) {
    yyerror("No space.");
    exit(0);
  }

  ast->nodetype = CONSTANT;
  ast->v = value;

  return (struct ast *)ast;
}

// Function to create a new reference
struct ast *new_reference(char *s) {
  struct symbol_reference *ast = malloc(sizeof(struct symbol_reference));

  if(!ast) {
    yyerror("No space.");
    exit(0);
  }

  ast->nodetype = NEW_REFERENCE;
  ast->s = s;

  return (struct ast *)ast;
}

// Function to create an AST with comparision type
struct ast *new_comparison(int type, struct ast *l, struct ast *r) {
  struct ast *ast = malloc(sizeof(struct ast));

    if(!ast) {
      yyerror("No space");
      exit(0);
    }

    ast->nodetype = '0' + type;
    ast->l = l;
    ast->r = r;

  return ast;
}

// Function to define a custom function
void define_function(char *function_name, struct symbol_list *symbol_list, struct ast *function) {
  struct symbol * custom_function = lookup(function_name);

  // Assign symbol list and function
  custom_function->syms = symbol_list;
  custom_function->func = function;
}

// Function to create a new symbol list
struct symbol_list *create_symbol_list(char *symbol, struct symbol_list *next) {
  struct symbol_list *new_symbol_list = malloc(sizeof(struct symbol_list));

  if(!new_symbol_list) {
    yyerror("out of space");
    exit(0);
  }
  
  new_symbol_list->sym = symbol;
  new_symbol_list->next = next;

  return new_symbol_list;
}

// Function to create a new control flow
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr) {
  struct flow *flow = malloc(sizeof(struct flow));

  if(!flow) {
    yyerror("out of space");
    exit(0);
  }

  flow->nodetype = nodetype;
  flow->condition = cond;
  flow->then_list = tl;
  flow->else_list = tr;

  return (struct ast *)flow;
}

struct ast *new_for_flow(int nodetype, struct ast *initialization, struct ast *cond, struct ast *tl, struct ast *tr) {
  struct for_flow *flow = malloc(sizeof(struct for_flow));

  if(!flow) {
    yyerror("out of space");
    exit(0);
  }

  flow->nodetype = nodetype;
  flow->initialization = initialization;
  flow->condition = cond;
  flow->then_list = tl;
  flow->else_list = tr;

  return (struct ast *)flow;
}

// Function to evaluate an AST
struct val * eval(struct ast *abstract_syntax_tree) {
  struct symbol *s = NULL;
  struct val *v = NULL;
  struct val *helper_value = NULL;
  struct declare_symbol *declare_symbol = NULL;
  struct assign_and_declare_symbol *assign_and_declare_symbol = NULL;
  struct assign_and_declare_complex_symbol *assign_and_declare_complex_symbol = NULL;
  struct ast *args = NULL;
  struct val *evaluation_helper = NULL;
  struct val *initialization_helper = NULL;

  // Return null if no AST is found
  if(!abstract_syntax_tree) {
    return NULL;
  }

  switch(abstract_syntax_tree->nodetype) {
    case CONSTANT:
      printf("Evaluating CONSTANT...\n");
      evaluation_helper = ((struct constant_value *)abstract_syntax_tree)->v;
      switch(evaluation_helper->type) {
          case BIT_TYPE:
            v = create_bit_value(evaluation_helper->datavalue.bit);
            printf("CONSTANT value is: %d\n", v->datavalue.bit);
            break;
          case INTEGER_TYPE:
            v = create_integer_value(evaluation_helper->datavalue.integer);
            printf("CONSTANT value is: %d\n", v->datavalue.integer);
            break;
          case DECIMAL_TYPE:
            v = create_decimal_value(evaluation_helper->datavalue.decimal);
            printf("CONSTANT value is: %f\n", v->datavalue.decimal);
            break;
          case STRING_TYPE:
            v = create_string_value(evaluation_helper->datavalue.string);
            printf("CONSTANT value is: %s\n", v->datavalue.string);
            break;
      }
    break;

    case NEW_REFERENCE:
      printf("Evaluating NEW REFERENCE...\n");
      s = lookup(((struct symbol_reference *)abstract_syntax_tree)->s);

      // Check if new reference is created correctly
      if(!s) {
        yyerror("variable %s not found.", ((struct symbol_reference *)abstract_syntax_tree)->s);
        free(abstract_syntax_tree);
        return NULL;
      }

      v = s->value;
      printf("New reference evaluation type is: %d\n", s->value->type);
      printf("Evaluated NEW REFERENCE...\n");
      break;

    case ASSIGNMENT:
      printf("Before the assignment node type is: %d\n", ((struct assign_symbol *)abstract_syntax_tree)->v->nodetype);
      s = lookup(((struct assign_symbol *)abstract_syntax_tree)->s);

      //Check if symbol exists
      if(!s) {
        yyerror("Cannot find symbol %s.\n", ((struct assign_symbol *)abstract_syntax_tree)->s);
        free(v);
        free(abstract_syntax_tree);
        return NULL;
      }

      // Evaluate the assignment
      v = eval(((struct assign_symbol *)abstract_syntax_tree)->v);

      // Assign the symbol value to symbol
      s->value = v;
      break;

    case '+':
      v = sum(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '-': 
      v = subtract(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '*': 
      v = multiply(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '/': 
      v = divide(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '|': 
      v = get_absolute_value(eval(abstract_syntax_tree->l)); 
      break;
    case UNARY_MINUS: 
      v = change_sign(eval(abstract_syntax_tree->l));
      break;

    case LOGICAL_AND: 
      v = calculate_logical_and(eval(abstract_syntax_tree->l),eval(abstract_syntax_tree->r)); 
      break;
    case LOGICAL_OR: 
      v = calculate_logical_or(eval(abstract_syntax_tree->l),eval(abstract_syntax_tree->r)); 
      break;

    case '1':
      v = calculate_greater_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '2': 
      v = calculate_less_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '3':
      v = calculate_not_equals(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '4': 
      v = calculate_equals(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      break;
    case '5': 
      v = calculate_greater_equal_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case '6': 
      v = calculate_less_equal_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;

    case IF_STATEMENT:
      helper_value = eval(
        ((struct flow *)abstract_syntax_tree)->condition
      );

      // Check if value type is comparison
      if(get_value_type(helper_value) != 0) {
        yyerror("invalid condition");
        free(abstract_syntax_tree);
        return NULL;
      }

      // Check if condition is met
      if(helper_value->datavalue.bit != 0) {
        if(((struct flow *)abstract_syntax_tree)->then_list) {
          v = eval(((struct flow *)abstract_syntax_tree)->then_list);
        } else {
          v = NULL;
        }   
      } else {
        // Else, create an AST with else list
        if(((struct flow *)abstract_syntax_tree)->else_list) {
          v = eval(((struct flow *)abstract_syntax_tree)->else_list);
        } else {
          v = NULL;
        }  
      }
      break;

    case FOR_STATEMENT:
      initialization_helper = eval(((struct for_flow *)abstract_syntax_tree)->initialization);
      if(initialization_helper != NULL) {
        printf("Initialization evaluation is not null.\n");
      }

      helper_value = eval(
        ((struct for_flow *)abstract_syntax_tree)->condition
      );

      // Check if value type is comparison
      if(get_value_type(helper_value) != 0) {
        yyerror("invalid condition");
        free(abstract_syntax_tree);
        return NULL;
      }

      // Check if condition is met
      if(helper_value->datavalue.bit != 0) {
        if(((struct for_flow *)abstract_syntax_tree)->then_list) {
          v = eval(((struct for_flow *)abstract_syntax_tree)->then_list);
        } else {
          v = NULL;
        }   
      } else {
        // Else, create an AST with else list
        if(((struct for_flow *)abstract_syntax_tree)->else_list) {
          v = eval(((struct for_flow *)abstract_syntax_tree)->else_list);
        } else {
          v = NULL;
        }  
      }
      break;

    case LOOP_STATEMENT:
      v = NULL;

      // Check if we have then list in AST
      if(((struct flow *)abstract_syntax_tree)->then_list) {
        helper_value = (eval(((struct flow *)abstract_syntax_tree)->condition));

        // Check if value type is comparison
        if(get_value_type(helper_value) != 0) {
          yyerror("invalid condition");
          free(abstract_syntax_tree);
          return NULL;
        }

        // Loop while condition is met
        while(helper_value->datavalue.bit != 0) {
          v = eval(((struct flow *)abstract_syntax_tree)->then_list);
          helper_value = (eval(((struct flow *)abstract_syntax_tree)->condition));
        }
      }
      break;
  
    case STATEMENT_LIST:
      evaluation_helper = eval(abstract_syntax_tree->l);
      //eval(abstract_syntax_tree->l);
      printf("Statement list nodetype is: %d.\n", abstract_syntax_tree->l->nodetype);
      printf("Value type before second evaluation is: %d\n", evaluation_helper->type);
      v = eval(abstract_syntax_tree->r);

      // Assign type to value after evaluation in order not to lose the type information
      switch (evaluation_helper->type) {
        case BIT_TYPE:
          v->type = BIT_TYPE;
          break;
        
        case INTEGER_TYPE:
          v->type = INTEGER_TYPE;
          break;

        case DECIMAL_TYPE:
          v->type = DECIMAL_TYPE;
          break;

        case STRING_TYPE:
          v->type = STRING_TYPE;
          break;

        case LED:
          v->type = LED;
          break;

        case BUTTON:
          v->type = BUTTON;
          break;

        case KEYPAD:
          v->type = KEYPAD;
          break;

        case BUZZER:
          v->type = BUZZER;
          break;

        case SERVO_MOTOR:
          v->type = SERVO_MOTOR;
          break;
      
        default:
        v->type = INTEGER_TYPE;
          break;
      }
      
      break;

    case BUILTIN_TYPE:
      v = builtin_function_call((struct builtin_function_call *)abstract_syntax_tree);
      break;

    case USER_CALL:
      calluser((struct user_function_call *)abstract_syntax_tree);
      break;

    case DECLARATION:
        declare_symbol = (struct declare_symbol *)abstract_syntax_tree;
        s = lookup(declare_symbol->s);
        printf("Inserted symbol.");

        // Control if variable is inserted as symbol
        if(!s) {
          free(declare_symbol->s);
          free(declare_symbol);
          return NULL;
        }

        // Check symbol declaration types to assign symbol value
        switch(declare_symbol->type) {
          case BIT_TYPE:
            s->value = create_bit_value(0);
            break;
          case INTEGER_TYPE:
            s->value = create_integer_value(0);
            break;
          case DECIMAL_TYPE:
            s->value = create_decimal_value(0.0);
            break;
          case STRING_TYPE:
            s->value = create_string_value("");
            break;
          case LED:
            s->value = create_led_value(NULL, 1);
            break;
          case BUTTON:
            s->value = create_button_value(NULL, 1);
            break;
          case KEYPAD:
            s->value = create_keypad_value(NULL, 1);
            break;
          case BUZZER:
            s->value = create_buzzer_value(NULL, 1);
            break;
          case SERVO_MOTOR:
            s->value = create_servo_motor_value(NULL, 1);
            break;
          default:
            yyerror("Type not recognized.");
            free(declare_symbol->s);
            free(declare_symbol);
            free(s->name);
            s = NULL;
            break;
        }
      break;

    case DECLARATION_WITH_ASSIGNMENT:
      assign_and_declare_symbol = ((struct assign_and_declare_symbol *)abstract_syntax_tree);
      v = eval(assign_and_declare_symbol->value);

      // Control if variable is inserted as symbol
      if (v && assign_and_declare_symbol->type != v->type) {
        yyerror("Type not recognized.");
        free(assign_and_declare_symbol);
        free(v);
        return NULL;
      }

      // Insert the new declaration and do sanity check
      struct symbol *s = lookup(assign_and_declare_symbol->s);
      if(!s) {
        free(assign_and_declare_symbol);
        free(v);
        return NULL;
      }
      s->value = v;
      break;

    case COMPLEX_ASSIGNMENT:
      // Cast AST back to assign_and_declare_complex_symbol in order to access the fields
      assign_and_declare_complex_symbol = (struct assign_and_declare_complex_symbol *)abstract_syntax_tree;

      // Get the value of assign_and_declare_complex_symbol struct
      args = assign_and_declare_complex_symbol->value;

      // Get argument number
      struct ast *helper = args;
      int argument_number = 0;

      while(helper != NULL) {
          argument_number +=1;
          helper = helper->r;
      }

      // Declare an helper structure to memorize evaluated part of the assign_and_declare_complex_symbol structure
      struct val ** argument_storage = (struct val **)malloc(argument_number * sizeof(struct val)); 
 
      for(int i=0; args!=NULL; i++) {
        if(args->nodetype == STATEMENT_LIST) {
          argument_storage[i] = eval(args->l);
          args = args->r;
        } else {
          argument_storage[i] = eval(args);
          args = NULL;
        }

        // Switch the result
        switch(assign_and_declare_complex_symbol->type) {
          case LED:
              printf("LED TYPE detected.\n");
              v = create_LED(argument_storage);
              break;

          case BUTTON:
              printf("BUTTON TYPE detected.\n");
              v = create_BUTTON(argument_storage);
              break;

          case KEYPAD:
              printf("KEYPAD TYPE detected.\n");
              v = create_KEYPAD(argument_storage);
              break;

          case BUZZER:
              printf("BUZZER TYPE detected.\n");
              v = create_BUZZER(argument_storage);
              break;

          case SERVO_MOTOR:
              printf("SERVO_MOTOR TYPE detected.\n");
              v = create_SERVO_MOTOR(argument_storage);
              break;              

          default:
              printf("NO TYPE detected.\n");
              v = NULL;
              break;
        }
      }

      // Insert the symbol memorizing the value
      s = lookup(assign_and_declare_complex_symbol->s);
      s->value = v;
      s->name = assign_and_declare_complex_symbol->s;
      
      break;

  default:
    yyerror("internal error: bad node %d\n", abstract_syntax_tree->nodetype);
    free(abstract_syntax_tree);
    break;
  }
  
  // Return the evaluated value
  return v;
}

// Function to free AST
void treefree(struct ast *abstract_syntax_tree) {
  switch(abstract_syntax_tree->nodetype) {
    case '+':
    case '-':
    case '*':
    case '/':
    case LOGICAL_OR:
    case LOGICAL_AND:
    case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
    case STATEMENT_LIST:
      treefree(abstract_syntax_tree->r);
      break;

    case '|': 
    case UNARY_MINUS:
    case USER_CALL:
    case BUILTIN_TYPE:
      if(abstract_syntax_tree->l) {
        treefree(abstract_syntax_tree->l);
      }
      break;

    case CONSTANT: 
    case NEW_REFERENCE: 
    case DECLARATION:
      break;

    case ASSIGNMENT:
      free(((struct assign_symbol *)abstract_syntax_tree)->v);
      break;

    case IF_STATEMENT:
    case LOOP_STATEMENT: 
      free(((struct flow *)abstract_syntax_tree)->condition);
      if(((struct flow *)abstract_syntax_tree)->then_list) {
        free(((struct flow *)abstract_syntax_tree)->then_list);
      }
      if(((struct flow *)abstract_syntax_tree)->else_list) {
        free(((struct flow *)abstract_syntax_tree)->else_list);
      }
      break;
    
    case FOR_STATEMENT: 
      free(((struct for_flow *)abstract_syntax_tree)->condition);
      if(((struct for_flow *)abstract_syntax_tree)->then_list) {
        free(((struct for_flow *)abstract_syntax_tree)->then_list);
      }
      if(((struct for_flow *)abstract_syntax_tree)->else_list) {
        free(((struct for_flow *)abstract_syntax_tree)->else_list);
      }
      break;

    case DECLARATION_WITH_ASSIGNMENT: 
    case COMPLEX_ASSIGNMENT:
      if(((struct assign_and_declare_symbol *)abstract_syntax_tree)->value) {
        treefree(((struct assign_and_declare_symbol *)abstract_syntax_tree)->value);
      }
    break;

    default: yyerror("internal error: free bad node %d\n", abstract_syntax_tree->nodetype);
  }
  
  free(abstract_syntax_tree); /* always free the node itself */
}

// Function to check if we have a primitive type
bool is_primitive(int type) {
  return type == BIT_TYPE || type == INTEGER_TYPE || type == DECIMAL_TYPE || type == STRING_TYPE;
}

// Function to create a node for built in function in the AST
struct ast *new_builtin_function(int function_type, char *s, struct ast *argument_list) {
  struct builtin_function_call *ast = malloc(sizeof(struct builtin_function_call));
  
  if(!ast) {
    yyerror("No space.");
    exit(0);
  }

  ast->nodetype = BUILTIN_TYPE;
  ast->function_type = function_type;
  ast->argument_list = argument_list;
  ast->s = s;

  return (struct ast *)ast;
}

// Function to call built in functions
struct val *builtin_function_call(struct builtin_function_call *builtin_function) {
  printf("Executing built-in function call.\n");
  struct val *result = NULL;
  struct symbol *variable = NULL;
  struct val *value = NULL;

  // Check if function has a name, else pass in an empty string to lookup
  if(builtin_function->s != NULL) {
    variable = lookup(builtin_function->s);
  } else {
    variable = lookup("");
  }
  
  // Evaluate the argument list to assign the value
  variable->value = eval(builtin_function->argument_list);
  value = variable->value;

  if(value == NULL) {
    printf("Value is null after the assignment!\n");
  } else {
    printf("Value is %d after the assignment!\n", value->type);
  }

  struct ast *args = builtin_function->argument_list;
  int number_of_arguments = 0;

  /* count the arguments */
  while(args) {
    args = args->r;
    number_of_arguments++;
  }

  // Define a val structure to store the new value
  struct val ** argument_storage = (struct val **)malloc(number_of_arguments * sizeof(struct val));

  // Memorize the argument list
  args = builtin_function->argument_list;

  /* evaluate the arguments */
  for(number_of_arguments = 0; args; number_of_arguments++) {
    if(args->nodetype == STATEMENT_LIST) {
      /* List node */
      argument_storage[number_of_arguments] = eval(args->l);
      args = args->r;
    } else {			
      /* End of the list */
      argument_storage[number_of_arguments] = eval(args);
      args = NULL;
    }
  }

  int expected_argument_numbers = 0;
  
  switch(builtin_function->function_type) {
    case BUILT_IN_PRINT:
      if(!value) {
        yyerror("Value is null.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      print_type(value);
      break;

    case BUILT_IN_SQUARE_ROOT:
      if(value->type != DECIMAL_TYPE && value->type != INTEGER_TYPE) {
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      result = square_root(value);
      printf("SQUARE ROOT result: %f\n", result->datavalue.decimal);
      break;

    case BUILT_IN_LED_ON:
      if(value->type != LED) {
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }
      
      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      #ifdef RPI_SIMULATION
       // TODO: Check if can assign LED to this pin number
        int res = led_on(value);
      #else
        printf("Simulated led_on.\n");
        int res = 0;
      #endif
      
      if(res != 0) {
        yyerror("Bad GPIO level.");
      }
      break;

    case BUILT_IN_LED_OFF:
      if(value->type != LED) {
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      #ifdef RPI_SIMULATION
        int res2 = led_off(value);
      #else
        printf("Simulated led_off.\n");
        int res2 = 0;
      #endif

      if(res2 != 0) {
        yyerror("Bad GPIO level.");
      }
      break;

    case BUILT_IN_IS_BUTTON_PRESSED:
      if(value->type != BUTTON) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      printf("Calling pigpio function.\n");

      #ifdef RPI_SIMULATION
        struct val *res3 = malloc(sizeof(struct val));
        res3 = is_button_pressed(value);
      #else
        printf("Simulated is_button_pressed.\n");
        struct val *res3 = malloc(sizeof(struct val));
        res3->type = BIT_TYPE;
        res3->datavalue.bit = 0; 
      #endif

      if(res3 == NULL) {
        yyerror("Pin number is not permitted to be read.\n");
      }

      result = res3;
      break;

    case BUILT_IN_GET_PRESSED_KEY:
      if(value->type != KEYPAD) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      #ifdef RPI_SIMULATION
        struct val *res4 = malloc(sizeof(struct val));
        res4 = is_button_pressed(value);
      #else
        printf("Simulated get_pressed_key.\n");
        struct val *res4 = malloc(sizeof(struct val));
        res4->type = STRING_TYPE;
        res4->datavalue.string = strdup("A"); 
      #endif

      if(res4 == NULL) {
        yyerror("Cannot determine if key is pressed.\n");
      }

      result = res4;
      break;

    case BUILT_IN_BUZZ_START:
      if(value->type != BUZZER) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      struct val *res5 = malloc(sizeof(struct val));

      #ifdef RPI_SIMULATION
        res5 = buzz_start(value);
      #else
        printf("Simulated buzz_start.\n");
        res5 = 0; 
      #endif

      if(res5 != 0) {
        yyerror("Bad GPIO level.");
      }

      result = res5;
      break;

    case BUILT_IN_BUZZ_STOP:
      if(value->type != BUZZER) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      struct val *res6 = malloc(sizeof(struct val));

      #ifdef RPI_SIMULATION
        res6 = buzz_stop(value);
      #else
        printf("Simulated buzz_stop.\n");
        res6 = 0; 
      #endif

      if(res6 != 0) {
        yyerror("Bad GPIO level.");
      }

      result = res6;
      break;

    case BUILT_IN_MOVE_SERVO_TO_ANGLE:
      if(value->type != SERVO_MOTOR) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 2;

      if(number_of_arguments != expected_argument_numbers) {
        yyerror("Too many or too few arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      struct val *res7 = malloc(sizeof(struct val));

      #ifdef RPI_SIMULATION
        res7 = move_servo_to_angle(value, argument_storage[0]);
      #else
        printf("Simulated move_servo_to_angle.\n");
        res7 = 0; 
      #endif

      if(res7 != 0) {
        yyerror("PI_BAD_DUTYCYCLE.");
      }

      result = res7;
      break;

    case BUILT_IN_MOVE_SERVO_INFINITELY:
      if(value->type != SERVO_MOTOR) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments != expected_argument_numbers) {
        yyerror("Too many or too few arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      struct val *res8 = malloc(sizeof(struct val));

      #ifdef RPI_SIMULATION
        res8 = move_servo_infinitely(value);
      #else
        printf("Simulated move_servo_infinitely.\n");
        res8 = 0; 
      #endif

      if(res8 != 0) {
        yyerror("PI_BAD_DUTYCYCLE.");
      }

      result = res8;
      break;

    case BUILT_IN_SERVO_STOP:
      if(value->type != SERVO_MOTOR) {
        printf("Type is: %d\n", value->type);
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      expected_argument_numbers = 1;

      if(number_of_arguments > expected_argument_numbers) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(argument_storage);
        break;
      }

      struct val *res9 = malloc(sizeof(struct val));

      #ifdef RPI_SIMULATION
        res9 = servo_stop(value);
      #else
        printf("Simulated servo_stop.\n");
        res9 = 0; 
      #endif

      if(res9 != 0) {
        yyerror("Bad GPIO level.");
      }

      result = res9;
      break;

    case BUILT_IN_DELAY:
      #ifdef RPI_SIMULATION
        delay_pi();
      #else
        printf("Simulated delay.\n");
      #endif

      result = NULL;
      break;
    
    default:
      yyerror("Function does not exist: %d", builtin_function->function_type);
      free(builtin_function);
      free(argument_storage);
      break;
  }

  return result;
}

// Function to create a node for user defined function in the AST
struct ast *new_user_function(char *s, struct ast *argument_list) {
  struct user_function_call *ast = malloc(sizeof(struct user_function_call));
  
  if(!ast) {
    yyerror("No space.");
    exit(0);
  }

  ast->nodetype = USER_CALL;
  ast->argument_list = argument_list;
  ast->s = s;

  return (struct ast *)ast;
}

// Function to call custom functions
void calluser(struct user_function_call *user_function) {
    struct symbol *user_function_call = lookup(user_function->s); /* function name */
    struct symbol_list *sl; /* dummy arguments */
    struct ast *args = user_function->argument_list; /* actual arguments */
    struct val **oldval, **newval; /* saved arg values */
    int nargs;
    int i;

    if(!user_function) {
      yyerror("Call to undefined function", user_function->s);
      return;
    }

    /* count the arguments */
    sl = (struct symbol_list *)user_function->argument_list;
    for(nargs = 0; sl; sl = sl->next)
    nargs++;

    /* prepare to save them */
    oldval = (struct val **)malloc(nargs * sizeof(struct val));
    newval = (struct val **)malloc(nargs * sizeof(struct val));

    if(!oldval || !newval) {
      yyerror("Out of space in %s", user_function->s);
    }

    /* evaluate the arguments */
    for(i = 0; i < nargs; i++) {
      if(!args) {
        yyerror("Too few args in call to %s", user_function->s);
        free(oldval); 
        free(newval);
        return;
      }
    }

    if(args->nodetype == STATEMENT_LIST) { 
      /* if this is a list node */
      newval[i] = eval(args->l);
      args = args->r;
    } else {
      /* if it's the end of the list */
      newval[i] = eval(args);
      args = NULL;
    }

    /* save old values of dummies, assign new ones */
    sl = (struct symbol_list *)user_function->argument_list;
    for(i = 0; i < nargs; i++) {
      struct symbol *s = lookup(sl->sym);
      if(s == NULL) {
        s = lookup(sl->sym);
      }

      oldval[i] = s->value;
      s->value = newval[i];
      sl = sl->next;
    }

    /* evaluate the function */
    eval(user_function_call->func);

    /* put the dummies back */
    sl = user_function_call->syms;
    for(i = 0; i < nargs; i++) {
      struct symbol *s = lookup(sl->sym);

      s->value = oldval[i];
      sl = sl->next;
    }

    free(newval);
    free(oldval);
}

void dodef(char *n, struct symbol_list *symbol_list, struct ast *function) {
  struct symbol *name = (struct symbol *) n;
  if(name->syms) name->syms = NULL;
  if(name->func) treefree(name->func);
  name->syms = symbol_list;
  name->func = function;
}

// Function to create a new file
int newfile(char *fn) {
  FILE *f;

  if(strcmp(fn, "stdin")) {
    // Found files
    f = fopen(fn, "r");
		is_file = 1;
  } else {
    // Use standard input
    f = stdin;
		is_file = 0;
  }

  if(!f) {
    perror(fn);
    return -1;
  }

  yyin = f;

  return 1;
}

// Function to check passed in file suffix
int checkSuffix(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char **argv) {

  #ifdef RPI_SIMULATION
    if (gpioInitialise()<0) return 1;
    printf("Executing on PI.\n");
  #else
    printf("Executing locally.\n");
  #endif

  printf("Learnpi...\n");
	newfile("stdin");

  if(argc == 1) {
      printf("%s", "Learnpi~€: ");
      yyparse();
  } else {
    for(int i = 1; i < argc; i++) {
      if(checkSuffix(argv[1], ".learnpi") == 1 && newfile(argv[1])) {
        yyparse();
      } else {
        fprintf(stderr, "Not a valid file.\n");
      }
    }
  }

  printf("Thanks for using learnpi.\n");
  return 0;
}
