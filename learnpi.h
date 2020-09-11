#ifndef LEARNPI_H
#define LEARNPI_H

#define NHASH 9997
// #define RPI_SIMULATION 1
#include <stdbool.h>
#include "types.h"

// Expression types
enum expression_type {
  CONSTANT = 1,
  NEW_REFERENCE,
  DELETION,
  ASSIGNMENT,
  COMPLEX_ASSIGNMENT,
  STATEMENT_LIST,
  UNARY_MINUS,
  LOGICAL_AND,
  LOGICAL_OR,
  IF_STATEMENT,
  LOOP_STATEMENT,
  FOR_STATEMENT,
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
  struct symbol_list *syms;
};

// Symbol table variable
struct symbol symtab[NHASH];

// Structure for value
struct val {
    int type;
    union datavalue { // TODO: change this
        int bit;
        int integer;
        double decimal;
        char * string;
        unsigned * GPIO_PIN;
    } datavalue;
};

// Structure for symbol list
struct symbol_list {
  char *sym;
  struct symbol_list *next;
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

// Structure for for_flow control
struct for_flow {
  int nodetype;
  struct ast *initialization;
  struct ast *condition;
  struct ast *then_list;
  struct ast *else_list;
};

// Structure for symbol reference
struct symbol_reference {
  int nodetype;
  char *s;
};

// Structure for symbol assignment
struct symasgn {
  int nodetype;
  char *s;
  struct ast *v;
};

// Structure for variable declaration
struct declare_symbol {
  int nodetype;
  int type;
  char *s;
};

// Structure for variable declaration with assignment
struct assign_and_declare_symbol {
  int nodetype;
  int type;
  char *s;
  struct ast *value;
};

// Structure for variable declaration with assignment
struct assign_and_declare_complex_symbol {
  int nodetype;
  int type;
  char *s;
  struct ast *value;
};

// Structure for constant values
struct constant_value {
  int nodetype;
  struct val *v;
};

// Structure for builtin function call
struct builtin_function_call {
  int nodetype;
  struct ast *argument_list;
  enum built_in_function_types function_type;
  char *s;
};

// Structure for user function call
struct user_function_call {
  int nodetype;
  struct ast *argument_list;
  char *s;
};

// Lookup function
struct symbol *lookup(char*);

// Function for new declaration
struct ast *new_declaration(char *s, int type);

// Function for new variable asignment
struct ast * new_assignment(char *s, struct ast *v);

// Function to create a new control flow
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

// Function to create a new control for_flow
struct ast *new_for_flow(int nodetype, struct ast *initialization, struct ast *cond, struct ast *tl, struct ast *tr);

// Function for new complex variable assignment
struct ast *new_complex_assignment(char *s, int type, struct ast *l);

// Function to create an AST with generic node type and one child
struct ast *new_ast_with_child(int type, struct ast *l);

// Function to create an AST with generic node type and two children
struct ast *new_ast_with_children(int type, struct ast *l, struct ast *r);

// Function to create a new reference
struct ast *new_reference(char *s);

// Function to create an AST with comparision type
struct ast *new_comparison(int type, struct ast *l, struct ast *r);

// Function to create a new value
struct ast *new_value(struct val *value);

// Symbol table stack reference to use in main function
struct symtable_stack *symstack;

// Function to create a built in function
struct ast *new_builtin_function(int function_type, char *s, struct ast *l);

// Function to create a node for user defined function in the AST
struct ast *new_user_function(char *s, struct ast *argument_list);

// Function to define a custom function
void define_function(char *function_name, struct symbol_list *symbol_list, struct ast *function);

// Function to create a new symbol list
struct symbol_list *create_symbol_list(char *symbol, struct symbol_list *next);

// Function to create a new control flow
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

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

// Function to create a node for built in function in the AST
struct ast *new_builtin_function(int function_type, char *s, struct ast *l);

// Function to call built in functions
struct val *builtin_function_call(struct builtin_function_call *builtin_function);

// Function to call custom functions
void calluser(struct user_function_call *user_function);

void dodef(char *n, struct symbol_list *symbol_list, struct ast *function);

#endif