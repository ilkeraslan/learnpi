#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "learnpi.h"

extern int yydebug;
extern FILE *yyin;

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
      sp->v = NULL;
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

// Valuta un'espressione, passata tramite struttura AST.
struct val * eval(struct ast *a) {
  struct symbol *s = NULL;
  struct val * v = NULL;
  struct val *temp = NULL;

  if(!a) {
    return NULL;
  }

  switch(a->nodetype) {
  // costante
  case T_constant:
    v = ((struct value_val *)a)->v;
    break;
  // riferimento al nome
	case T_newref:
		s = lookup(((struct symref *)a)->s);
		if(!s) {
			yyerror("variable %s not found.", ((struct symref *)a)->s);
      free(a);

      return NULL;
		}
	  v = s->v;
    break;
  case T_newdel: ;
    struct symbol *symbol = lookup(((struct symref *)a)->s);
    if(!symbol) {
      yyerror("variable %s not found.", ((struct symref *)a)->s);
      free(a);

      return NULL;
    }
    if(symbol->func) {
      yyerror("cannot delete a function.");
      free(a);

      return NULL;
    }
    // libera la memoria e cancella la variabile
    if(symbol->name) {
      free(symbol->name);
      symbol->name = NULL;
    }
    if(symbol->v) {
      free(symbol->v);
      symbol->v = NULL;
    }
    symbol = NULL;
    break;
    // assegnamento
  case T_assign:
    v = eval(((struct symasgn *)a)->v);
    s = lookup(((struct symasgn *)a)->s);
    if(!s) {
      yyerror("symbol %s not instantiated\n", ((struct symasgn *)a)->s);
      free(v);
      free(a);

      return NULL;
    }
    if(!is_primitivetype(s->v->type)) {
      yyerror("cannot assign value to complex type");
      free(v);
      free(a);

      return NULL;
    }
    s->v = v;
  break;

  // operazioni aritmetiche
  case '+': v = sum(eval(a->l), eval(a->r)); break;
  case '-': v = sub(eval(a->l), eval(a->r)); break;
  case '*': v = mul(eval(a->l), eval(a->r)); break;
  case '/': v = division(eval(a->l), eval(a->r)); break;
  case T_absvalue: v = abs_value(eval(a->l)); break;
  case T_unaryminus: v = sign(eval(a->l)); break;

  // operazioni logiche
  case T_logicand: v = logic_and(eval(a->l),eval(a->r)); break;
  case T_logicor: v = logic_or(eval(a->l),eval(a->r)); break;

  // confronti
  case '1': v = greater_than(eval(a->l), eval(a->r)); break;
  case '2': v = less_than(eval(a->l), eval(a->r)); break;
  case '3':
    v = equal(eval(a->l), eval(a->r));
    v->datavalue.bit = !v->datavalue.bit;
  break;
  case '4': v = equal(eval(a->l), eval(a->r)); break;
  case '5': v = greater_equal_than(eval(a->l), eval(a->r)); break;
  case '6': v = less_equal_than(eval(a->l), eval(a->r)); break;

  // flussi di controllo
  // le espressioni nulle sono permesse nella grammatica, per cui controlla che le espressioni non siano nulle
  // if/then/else
  case T_if:
    temp = (eval(((struct flow *)a)->cond));
    if(typeof_value(temp) != D_bit) {
      yyerror("invalid condition");
      free(a);

      return NULL;
    }
    if(temp->datavalue.bit != 0) {
      if(((struct flow *)a)->tl) {
	      v = eval(((struct flow *)a)->tl);
      } else {
        v = NULL;
      }   
    } else {
      if(((struct flow *)a)->el) {
        v = eval(((struct flow *)a)->el);
      } else {
        v = NULL;
      }  
    }
    break;
  // loop
  case T_loop:
    v = NULL;
    if(((struct flow *)a)->tl) {
      temp = (eval(((struct flow *)a)->cond));
      if(typeof_value(temp) != D_bit) {
        yyerror("invalid condition");
        free(a);
        
        return NULL;
      }
      while(temp->datavalue.bit != 0) {
	      v = eval(((struct flow *)a)->tl);
        temp = (eval(((struct flow *)a)->cond));
      }
    }
  break;
  case T_doloop:
    v = NULL;
    if(((struct flow *)a)->tl) {
      // esegui le espressioni prima di valutare la condizione
      v = eval(((struct flow *)a)->tl);
      temp = (eval(((struct flow *)a)->cond));
      if(typeof_value(temp) != D_bit) {
        yyerror("invalid condition");
        free(a);
        
        return NULL;
      }
      while(temp->datavalue.bit != 0) {
	      v = eval(((struct flow *)a)->tl);
        temp = (eval(((struct flow *)a)->cond));
      }
    }
  break;

  // valore
  case T_stmtlist:
    eval(a->l);
    v = eval(a->r);
    break;

  case T_builtin:
    v = callbuiltin((struct fncall *)a);
    break;

  case T_calluser:
    calluser((struct ufncall *)a);
  break;

  // dichiarazione di variabile
  case T_declaration: ;
      struct symdecl *symdecl = (struct symdecl *)a;
      s = insert_symbol(symdecl->s);
      if(!s) {
        free(symdecl->s);
        free(symdecl);
				return NULL;
			}
      switch(symdecl->type) {
        case D_bit:
          s->v = create_bit(0);
        break;
        case D_integer:
          s->v = create_integer(0);
        break;
        case D_decimal:
          s->v = create_decimal(0.0);
        break;
        case D_string:
          s->v = create_string("");
        break;
        default:
          yyerror("invalid type value");
          free(symdecl->s);
          free(symdecl);
          free(s->name);
          s = NULL;
        break;
      }
  break;
  // dichiarazione e assegnamento
  case T_declarationassign: ;
    struct symdeclasgn * symdeclasgn = (struct symdeclasgn *)a;
    v = eval(symdeclasgn->v);
    if (v && symdeclasgn->type != v->type) {
      yyerror("invalid type value");
      free(symdeclasgn);
      free(v);

      return NULL;
    }
    struct symbol * s = insert_symbol(symdeclasgn->s);
    if(!s) {
      free(symdeclasgn);
      free(v);
      return NULL;
    }
    s->v = v;
  break;

  case T_cmpxassign: ;
    struct symdeclasgncmpx * symdeclasgncmpx = (struct symdeclasgncmpx *)a;
    struct ast *args = symdeclasgncmpx->l;
    int nargs = 0;
    // conto il numero di argomenti
    while(args) {
      args = args->r;
      nargs++;
    }
    struct val ** newval = (struct val **)malloc(nargs * sizeof(struct val));
    args = symdeclasgncmpx->l;
    // inserisco gli argomenti nell'array
    for(nargs = 0; args; nargs++) {
      if(args->nodetype == T_stmtlist) {	/* if this is a list node */
        newval[nargs] = eval(args->l);
        args = args->r;
      } else {			/* if it's the end of the list */
        newval[nargs] = eval(args);
        args = NULL;
      }
      if(newval[nargs]->type != D_integer) {
        yyerror("pin value must be an integer");
        free(symdeclasgncmpx->s);
        free(symdeclasgncmpx->l);
        free(symdeclasgncmpx);
        free(newval);

        return NULL;
      }
    }
    switch(symdeclasgncmpx->type) {
        case D_LED:
          if(!check_pin_no(nargs, 1)) {
            return NULL;
          }
          v = create_LED(newval);
        break;
        case D_DISPLAY_1DIGIT:
          if(!check_pin_no(nargs, 7)) {
            return NULL;
          }
          v = create_DISPLAY_1DIGIT(newval);
        break;
        case D_DISPLAY_LCD:
          v = create_DISPLAY_LCD();
        break;
        case D_BUTTON:
          if(!check_pin_no(nargs, 1)) {
            return NULL;
          }
          v = create_BUTTON(newval);
        break;
        case D_KEYPAD:
          if(!check_pin_no(nargs, 8)) {
            return NULL;
          }
          v = create_KEYPAD(newval);
        break;
        case D_BUZZER:
          if(!check_pin_no(nargs, 1)) {
            return NULL;
          }
          v = create_BUZZER(newval);
        break;
        case D_THERMISTOR:
          v = create_THERMISTOR();
        break;
        case D_PHOTORESISTOR:
          v = create_PHOTORESISTOR();
        break;
        case D_SERVO:
          if(!check_pin_no(nargs, 1)) {
            return NULL;
          }
          v = create_SERVO(newval);
        break;
        case D_RFID:
          v = create_RFID();
        break;
        default:
          yyerror("invalid type value");
          free(symdeclasgncmpx->s);
          free(symdeclasgncmpx->l);
          free(symdeclasgncmpx);
          free(newval);
        return NULL;
    }
    if (v && symdeclasgncmpx->type != v->type) {
      yyerror("invalid type value");
      free(symdeclasgncmpx->s);
      free(symdeclasgncmpx->l);
      free(symdeclasgncmpx);
      free(newval);
      return NULL;
    }
    s = insert_symbol(symdeclasgncmpx->s);
    if(!s) {
      free(symdeclasgncmpx->s);
      free(symdeclasgncmpx->l);
      free(symdeclasgncmpx);
      free(newval);
      return NULL;
    }
    s->v = v;
  break;
      
  default:
    yyerror("internal error: bad node %d\n", a->nodetype);
    free(a);
    break;
  }
  return v;
}

// Libera la memoria risalendo l'AST.
void treefree(struct ast *a) {
  switch(a->nodetype) {
  case '+':
  case '-':
  case '*':
  case '/':
  case T_logicor:
  case T_logicand:
  case '1':  case '2':  case '3':  case '4':  case '5':  case '6':
  case T_stmtlist:
    treefree(a->r);
    break;

  case T_absvalue: case T_unaryminus: case T_calluser: case T_builtin:
    if(a->l) {
      treefree(a->l);
    }
    break;

  case T_constant: case T_newref: case T_newdel: case T_declaration:
    break;

  case T_assign:
    free(((struct symasgn *)a)->v);
    break;

  case T_if: case T_loop: case T_doloop:
    free(((struct flow *)a)->cond);
    if(((struct flow *)a)->tl) free(((struct flow *)a)->tl);
    if(((struct flow *)a)->el) free(((struct flow *)a)->el);
    break;


  case T_declarationassign: case T_cmpxassign:
    if(((struct symdeclasgn *)a)->v) {
      treefree(((struct symdeclasgn *)a)->v);
    }
  break;

  default: yyerror("internal error: free bad node %d\n", a->nodetype);
  }
  
  free(a); /* always free the node itself */
}