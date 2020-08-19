// Struttura che definisce il simbolo di una variabile.
struct symbol {
  char *name;             // nome della variabile
  struct val* v;          // valore primitivo immagazzinato nella variabile
  struct ast *func;	      // statement per la funzione
  struct symlist *syms;   // lista dei dummy arguments
};

// Struttura che definisce una lista di simboli (per una lista di argomenti).
struct symlist {
  char *sym;
  struct symlist *next;
};

// Struttura che definisce l'AST.
struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
};

void define_function(char *function_name, struct symlist *symbol_list, struct ast *function);

// Prototipo della funzione relativa alla definizione di una nuova funzione da parte dell'utente.
void dodef(char *name, struct symlist *symlist, struct ast *func);

// Prototipo della funzione che valuta l'AST.
struct val *eval(struct ast *);

// Prototipo della funzione che elimina e libera un AST.
void treefree(struct ast *);