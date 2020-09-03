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
        printf("Assigned NULL to value!\n");
        sp->func = NULL;
        sp->syms = NULL;
        return sp;
    }

    if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
  }

  yyerror("LOOKUP: symbol table overflow\n");
  abort(); /* tried them all, table is full */
}

struct symbol *insert_symbol(char* sym) {
  // struct symbol * symtab;
  // struct symtable_stack * curr_scope = symstack;
  struct symbol *sp;
  int scount = NHASH;		// numero di simboli controllati

  // symtab = curr_scope->symtab;
  sp = &symtab[symhash(sym) % NHASH];
  while (--scount >= 0) {
    if (sp->name && !strcmp(sp->name, sym)) {
      yyerror("symbol %s already defined in this scope", sym);

			return NULL;
    }

    // Caso in cui il simbolo non è ancora stato dichiarato, quindi si tratta di una entry nuova
    if (!sp->name) {
      sp->name = strdup(sym);
      sp->value = NULL;
      sp->func = NULL;
      sp->syms = NULL;

      return sp;
    }

    if (++sp >= symtab + NHASH) {
      sp = symtab;	// prova la prossima entry
    }
  }

  yyerror("symbol table overflow\n");
  abort(); /* tried them all, table is full */
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
  struct symbol * custom_function = insert_symbol(function_name);

  // Assign symbol list and function
  custom_function->syms = symbol_list;
  custom_function->func = function;
}

// Function to create a new symbol list
struct symbol_list *create_symbol_list(char *symbol, struct symbol_list *next) {
  struct symbol_list *new_symbol_list = NULL;
  return new_symbol_list; // TODO: implement newsymlist
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

// Function to evaluate an AST
struct val * eval(struct ast *abstract_syntax_tree) {
  struct symbol *s = NULL;
  struct val *v = NULL;
  struct val *helper_value = NULL;
  struct symbol *symbol = NULL;
  struct declare_symbol *declare_symbol = NULL;
  struct assign_and_declare_symbol *assign_and_declare_symbol = NULL;
  struct assign_and_declare_complex_symbol *assign_and_declare_complex_symbol = NULL;
  struct ast *args = NULL;

  // Return null if no AST is found
  if(!abstract_syntax_tree) {
    return NULL;
  }

  switch(abstract_syntax_tree->nodetype) {
    case CONSTANT:
      printf("Evaluating CONSTANT...\n");
      v = ((struct constant_value *)abstract_syntax_tree)->v;
      printf("Evaluated CONSTANT...\n");
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
      printf("Evaluated NEW REFERENCE...\n");
      break;

    case DELETION:
      symbol = lookup(((struct symbol_reference *)abstract_syntax_tree)->s);
      
      // Check if symbol is created correctly
      if(!symbol) {
        yyerror("variable %s not found.", ((struct symbol_reference *)abstract_syntax_tree)->s);
        free(abstract_syntax_tree);
        return NULL;
      }

      // Check if trying to delete a function
      if(symbol->func) {
        yyerror("Function deletion is not permitted.");
        free(abstract_syntax_tree);
        return NULL;
      }

      // Delete the variable
      if(symbol->name) {
        free(symbol->name);
        symbol->name = NULL;
      }

      // Delete the value
      if(symbol->value) {
        free(symbol->value);
        symbol->value = NULL;
      }

      // Set the reference to NULL
      symbol = NULL;
      break;

    case ASSIGNMENT:
      v = eval(((struct assign_symbol *)abstract_syntax_tree)->v);
      s = lookup(((struct assign_symbol *)abstract_syntax_tree)->s);

      //Check if symbol exists
      if(!s) {
        yyerror("Cannot find symbol %s.\n", ((struct assign_symbol *)abstract_syntax_tree)->s);
        free(v);
        free(abstract_syntax_tree);
        return NULL;
      }

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
      v = calculate_equals(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      // v->datavalue.bit = !v->datavalue.bit; TODO: define datavalue
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
      helper_value = (eval(((struct flow *)abstract_syntax_tree)->condition));

      // Check if value type is 1
      if(get_value_type(helper_value) != 1) {
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

    case LOOP_STATEMENT:
      v = NULL;

      // Check if we have then list in AST
      if(((struct flow *)abstract_syntax_tree)->then_list) {
        helper_value = (eval(((struct flow *)abstract_syntax_tree)->condition));

        // Check if value type is 1
        if(get_value_type(helper_value) != 1) {
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
      eval(abstract_syntax_tree->l);
      v = eval(abstract_syntax_tree->r);
      break;

    case BUILTIN_TYPE:
      v = builtin_function_call((struct builtin_function_call *)abstract_syntax_tree);
      break;

    case USER_CALL:
      calluser((struct user_function_call *)abstract_syntax_tree);
    break;

    case DECLARATION:
        declare_symbol = (struct declare_symbol *)abstract_syntax_tree;
        s = insert_symbol(declare_symbol->s);

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
      struct symbol * s = insert_symbol(assign_and_declare_symbol->s);
      if(!s) {
        free(assign_and_declare_symbol);
        free(v);
        return NULL;
      }
      s->value = v;
    break;

    case COMPLEX_ASSIGNMENT:
      assign_and_declare_complex_symbol = (struct assign_and_declare_complex_symbol *)abstract_syntax_tree;
      args = assign_and_declare_complex_symbol->value;

      for(int i=0; args!=NULL; i++) {
        // Create an helper structure
        struct ast *helper = args->r;
        struct val *evaluation_result;

        // Evaluate the left node pointing the result
        evaluation_result = eval(args->l);

        // Switch the result
        switch(assign_and_declare_complex_symbol->type) {
          case LED:
            v = create_LED(&evaluation_result);
            break;
        }

        // Point to right node previosuly memorized in helper structure
        args = helper;
      }
      
      // TODO: free memory
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
    case DELETION: 
    case DECLARATION:
      break;

    case ASSIGNMENT:
      free(((struct assign_symbol *)abstract_syntax_tree)->v);
      break;

    case IF_STATEMENT:
    case LOOP_STATEMENT: 
      free(((struct flow *)abstract_syntax_tree)->condition);
      if(((struct flow *)abstract_syntax_tree)->then_list) free(((struct flow *)abstract_syntax_tree)->then_list);
      if(((struct flow *)abstract_syntax_tree)->else_list) free(((struct flow *)abstract_syntax_tree)->else_list);
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

// Function to initialize symbol table stack
// void initialize_symbol_table_stack() {
//   // Initialize a new symbol table stack
// 	struct symtable_stack * new_scope = calloc(1, sizeof(struct symtable_stack));
// 	new_scope->next = symstack;
// 	new_scope->symtab = calloc(NHASH, sizeof(struct symbol));

//   // Check if allocated space correctly
// 	if(!new_scope->symtab){
//     yyerror("No memory.");
//     exit(0);
// 	}

//   // Assign the created symbol table stack reference
// 	symstack = new_scope;
// }

// Function to free symbol table stack
// void free_symbol_table_stack() {
//   // Get the symbol table stack reference
// 	struct symtable_stack * inner = symstack;
  
//   // Assign the next node to symbol stack 
// 	symstack = symstack->next;

//   // Free allocated memories
// 	free(inner->symtab);
// 	free(inner);
// }

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
  struct val *result = NULL;
  struct symbol *variable = NULL;
  struct val *value = NULL;

  int is_terminal = 0;

  // Check if the function names are different
  if(builtin_function->s && strcmp(builtin_function->s, "terminal")) {
    variable = lookup(builtin_function->s);
    if(!variable) {
      yyerror("variable %s not found.", builtin_function->s);
      free(builtin_function->s);
      free(builtin_function);
      return NULL;
    }
    value = variable->value;
  } else {
      is_terminal = 1;
  }

  if(builtin_function->function_type != BUILT_IN_DELAY && !value && !is_terminal) {
    yyerror("cannot call function without complex type");
    return NULL;
  }

  struct ast *args = builtin_function->argument_list;
  int nargs = 0;

  /* count the arguments */
  while(args) {
    args = args->r;
    nargs++;
  }

  // Define a val structure to store the new value
  struct val ** newval = (struct val **)malloc(nargs * sizeof(struct val));

  // Memorize the argument list
  args = builtin_function->argument_list;

  /* evaluate the arguments */
  for(nargs = 0; args; nargs++) {
    if(args->nodetype == STATEMENT_LIST) {
      /* List node */
      newval[nargs] = eval(args->l);
      args = args->r;
    } else {			
      /* End of the list */
      newval[nargs] = eval(args);
      args = NULL;
    }
  }

  int args_no = 0;
  
  switch(builtin_function->function_type) {
    case BUILT_IN_LED_ON:
      if(value->type != LED) {
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(newval);
        break;
      }
      args_no = 0;
      if(nargs > args_no) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(newval);
        break;
      }
      int res = led_on(value);
      if(res != 0) {
        yyerror("Bad GPIO level.");
      }
      break;

    case BUILT_IN_LED_OFF:
      if(value->type != LED) {
        yyerror("Operation not permitted.");
        free(builtin_function);
        free(newval);
        break;
      }
      args_no = 0;
      if(nargs > args_no) {
        yyerror("Too many arguments.");
        free(builtin_function);
        free(newval);
        break;
      }
      int res2 = led_off(value);
      if(res2 != 0) {
        yyerror("Bad GPIO level.");
      }
      break;
    
    default:
      yyerror("Function does not exist: %d", builtin_function->function_type);
      free(builtin_function);
      free(newval);
      break;
  }

  return result;
}

// Function to create a node for user defined function in the AST
struct ast *new_user_function(char *s, struct ast *argument_list) {
  struct builtin_function_call *ast = malloc(sizeof(struct builtin_function_call));
  
  if(!ast) {
    yyerror("No space.");
    exit(0);
  }

  ast->nodetype = BUILTIN_TYPE;
  ast->argument_list = argument_list;
  ast->s = s;

  return (struct ast *)ast;
}

// Function to call custom functions
void calluser(struct user_function_call *foo) {
  // TODO: Implement user function call
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

	// symstack = calloc(1, sizeof(struct symtable_stack));
	// symstack->next = NULL;
	// symstack->symtab = NULL;

	// initialize_symbol_table_stack();

	newfile("stdin");

	for(int i = 1; i < argc; i++) {
		if(checkSuffix(argv[1], ".learnpi") == 1 && newfile(argv[1])) {
			yyparse();
		} else {
			fprintf(stderr, "Not a valid file.\n");
		}
	}

	// free_symbol_table_stack();

  printf("Thanks for using learnpi.\n");

  return 0;
}
