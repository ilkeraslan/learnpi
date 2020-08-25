#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "learnpi.h"
#include "functions.h"

extern int yydebug;
extern FILE *yyin;

// Hash a symbol using its string
static unsigned symhash(char *sym) {
  unsigned int hash = 0;
  unsigned c;
  while((c = *sym++)) {
    hash = hash*9 ^ c;
  }

  return hash;
}

// Cerca il simbolo che identifica la variabile nella tabella contenente i simboli già dichiarati.
struct symbol * lookup(char* sym) {
  struct symbol * symtab;
  struct symtable_stack * curr_scope = symstack;
  struct symbol *sp;
  int scount = NHASH;		// numero di simboli controllati

  while(curr_scope && curr_scope->symtab) {
    symtab = curr_scope->symtab;
    sp = &symtab[symhash(sym)%NHASH];
    
    while(--scount >= 0) {
      if(sp->name && !strcmp(sp->name, sym)) {
        return sp;
      }

      // Caso in cui il simbolo non è ancora stato dichiarato, quindi si tratta di una entry nuova
      if(!sp->name) {
        break;
      }

      if(++sp >= symtab+NHASH) { 
        sp = symtab; // prova la prossima entry
      }
    }
    curr_scope = curr_scope->next;
  }

  return NULL;
}

struct symbol * insert_symbol(char* sym) {
  struct symbol * symtab;
  struct symtable_stack * curr_scope = symstack;
  struct symbol *sp;
  int scount = NHASH;		// numero di simboli controllati

  symtab = curr_scope->symtab;
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

// Function to define a custom function
void define_function(char *function_name, struct symlist *symbol_list, struct ast *function) {
  struct symbol * custom_function = insert_symbol(function_name);

  // Assign symbol list and function
  custom_function->syms = symbol_list;
  custom_function->func = function;
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
      v = ((struct constant_value *)abstract_syntax_tree)->v;
    break;

    case NEW_REFERENCE:
      s = lookup(((struct symbol_reference *)abstract_syntax_tree)->s);

      // Check if new reference is created correctly
      if(!s) {
        yyerror("variable %s not found.", ((struct symbol_reference *)abstract_syntax_tree)->s);
        free(abstract_syntax_tree);
        return NULL;
      }

      v = s->value;
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

      // Check if symbol exists
      if(!s) {
        yyerror("Cannot find symbol %s.\n", ((struct assign_symbol *)abstract_syntax_tree)->s);
        free(v);
        free(abstract_syntax_tree);
        return NULL;
      }

      // Check if we have primitive type
      if(!is_primitive(s->value->type)) {
        yyerror("cannot assign value to complex type");
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
      v = sub(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case '*': 
      v = mul(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case '/': 
      v = division(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case ABSOLUTE_VALUE: 
      v = abs_value(eval(abstract_syntax_tree->l)); 
      break;
    case UNARY_MINUS: 
      v = sign(eval(abstract_syntax_tree->l)); 
      break;

    case LOGICAL_AND: 
      v = logic_and(eval(abstract_syntax_tree->l),eval(abstract_syntax_tree->r)); 
      break;
    case LOGICAL_OR: 
      v = logic_or(eval(abstract_syntax_tree->l),eval(abstract_syntax_tree->r)); 
      break;

    case '1': 
      v = greater_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
        break;
    case '2': 
      v = less_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
        break;
    case '3':
      v = equal(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r));
      // v->datavalue.bit = !v->datavalue.bit; TODO: define datavalue
      break;
    case '4': 
      v = equal(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case '5': 
      v = greater_equal_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
      break;
    case '6': 
      v = less_equal_than(eval(abstract_syntax_tree->l), eval(abstract_syntax_tree->r)); 
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
      v = builtin_function_call((struct function *)abstract_syntax_tree);
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
            s->value = create_bit(0); // TODO: create this function
            break;
          case INTEGER_TYPE:
            s->value = create_integer(0); // TODO: create this function
            break;
          case DECIMAL_TYPE:
            s->value = create_decimal(0.0); // TODO: create this function
            break;
          case STRING_TYPE:
            s->value = create_string(""); // TODO: create this function
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

    case ABSOLUTE_VALUE: 
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

void initialize_symbol_table_stack() {
  // Initialize a new symbol table stack
	struct symtable_stack * new_scope = calloc(1, sizeof(struct symtable_stack));
	new_scope->next = symstack;
	new_scope->symtab = calloc(NHASH, sizeof(struct symbol));

  // Check if allocated space correctly
	if(!new_scope->symtab){
    yyerror("No memory.");
    exit(0);
	}

  // Assign the created symbol table stack reference
	symstack = new_scope;
}

void free_symbol_table_stack() {
  // Get the symbol table stack reference
	struct symtable_stack * inner = symstack;
  
  // Assign the next node to symbol stack 
	symstack = symstack->next;

  // Free allocated memories
	free(inner->symtab);
	free(inner);
}

// Function to check if we have a primitive type
bool is_primitive(int type) {
  // TODO: check primitive types here
  return true;
}

// Helper method to check value type, returns -1 if null
int get_value_type(struct val *v) {
  if(v != NULL) {
    return v->type;
  }
  yyerror("Value is null.");
  return -1;
}

// Function to store function call value into a structure
struct val * builtin_function_call(struct function *foo) {
  return NULL; // TODO: return the structure
}

// Function to call custom functions
void calluser(struct user_function_call *foo) {
  // TODO: Implement user function call
}