#define NHASH 9997

// Expression types
enum expression_type {
  CONSTANT = 1,
  NEW_REFERENCE,
  DELETION,
  ASSIGNMENT,
  COMPLEX_ASSIGNMENT,
  STATEMENT_LIST,
  UNARY_MINUS,
  ABSOLUTE_VALUE,
  LOGICAL_AND,
  LOGICAL_OR,
  IF_STATEMENT,
  LOOP,
  DO_LOOP,
  DECLARATION,
  DECLARATION_WITH_ASSIGNMENT,
  BUILTIN_TYPE,
  USER_CALL
};

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

// Symbol assignment structure
struct assign_symbol {
  int nodetype;
  char *s;
  struct ast *v;
};

// Structure for flow control
struct flow {
  int nodetype;
  struct ast *condition;
  struct ast *then_list;
  struct ast *else_list;
};

// Symbol table stack structure
struct symtable_stack{
	struct symbol * symtab;
	struct symtable_stack * next;
};

// Structure for declaration with assignment
struct assign_and_declare_symbol {
  int nodetype;
  int type;
  char *s;
  struct ast *value;
};

// Lookup function
struct symbol *lookup(char*);

// Symbol table stack reference
struct symtable_stack * symstack;

// Function to define a custom function
void define_function(char *function_name, struct symlist *symbol_list, struct ast *function);

// Prototipo della funzione che valuta l'AST.
struct val *eval(struct ast *);

// Prototipo della funzione che elimina e libera un AST.
void treefree(struct ast *);

void initialize_symbol_table_stack();

void free_symbol_table_stack();