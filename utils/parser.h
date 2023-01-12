#ifndef LM_PARSER
#define LM_PARSER


typedef enum {
    LM_EXPRESSION,
    LM_OP,
    LM_NSET = -1, // not set
}ExprType;

typedef char* ExprValue;

typedef struct {
    ExprType n_type;
    ExprValue n_value;
    struct tree_node* children;
}tree_node;


tree_node* cr_lm_expr_tree();

void string_split(char * string, char sep, char *** r_array_string, int * r_size);



#endif
