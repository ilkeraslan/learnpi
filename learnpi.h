#define NHASH 9997
#include <stdbool.h>

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

// Structure for a variable symbol
struct symbol {
  char *name;
  struct val *value;
  struct ast *func;
  struct symlist *syms;
};

// Structure for value
struct val {
    int type;
    union datavalue { // TODO: change this
        int bit;
        int integer;
        double decimal;
        char * string;
        int * GPIO_PIN;
    } datavalue;
};


// Structure for symbol list
struct symlist {
  char *sym;
  struct symlist *next;
};

// Structure for Abstract Syntax Tree
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

// Structure for symbol reference
struct symbol_reference {
  int nodetype;
  char *s;
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

// Structure for constant values
struct constant_value {
  int nodetype;
  struct val *v;
};

// Structure for value

// Function to define a custom function
void define_function(char *function_name, struct symlist *symbol_list, struct ast *function);

// Function to evaluate an AST
struct val *eval(struct ast *);

// Function to free an AST
void treefree(struct ast *);

// Function to initialize symbol table stack
void initialize_symbol_table_stack();

// Function to free symbol table stack
void free_symbol_table_stack();

// Function to check if we have a primitive type
bool is_primitive(int type);

// Helper method to check value type
int get_value_type(struct val *v);