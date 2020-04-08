#define false 0
#define true 1
#define bool int

// the type of data(GWARF_value)
typedef enum{
    NUMBER_value = 1,
    STRING_value,
} GWARF_value_type;

// all value is GWARF_value
typedef struct GWARF_value{
    GWARF_value_type type;
    union
    {
        double double_value;  // NUMBER
        char *string;  // STRING
    } value;
    
} GWARF_value;

// ------------------------- var

typedef struct var{
    char *name;  // var name
    GWARF_value value;
    struct var *next;  // for list
} var;

// ------------------------- statement

typedef struct statement{
    enum statement_type{
        start=1,  // for base statement
        operation,  // such as + - * /
        base_var,  // return var address
        base_value,  // return an number or number
        while_cycle,  // while
    } type;  // the statement type

    union
    {
        struct{
            enum{
                ADD_func = 1,  // +
                SUB_func,  // -
                DIV_func,  // /
                MUL_func,  // *
                ASSIGMENT_func, // =
                EQUAL_func,  // ==
                MORE_func,  // >
                LESS_func,  // <
                MOREEQ_func,  // >=
                LESSEQ_func,  // <=
                NOTEQ_func,  // <>
            } type;
            struct statement *right_exp;  // the right exp
            struct statement *left_exp;  // the left exp
        } operation;

        struct{
            char *var_name;  // return var
        } base_var;

        struct{
            GWARF_value value;  // return value
        } base_value;
    } code;
    struct statement *next;
} statement;

// ------------------------- result value

typedef struct GWARF_result{
    GWARF_value value;
    enum{
        return_def=1,
        break_while,
        wrong,
    } u;  // the result type[from where]
} GWARF_result;

// ------------------------- var base list [记录每一层变量base的链表]

typedef struct var_list{
    var *var_base;
    struct var_list *next;
} var_list;

// ------------------------- inter

typedef struct{
    var *global_var;  // global var链表
    statement *global_code;  // global code链表
} inter;

//------- var func
var *make_var();
void append_var(char *, GWARF_value , var *);
void free_var(var *);
var *get_var(char *, var *);
void del_var(char *, var *);

//------- statement func
statement *make_statement();
statement *append_statement(statement *, statement*);

//------- run func
GWARF_result traverse(statement *, var_list *, bool);

//------- inter func
inter *get_inter();

// //------ paser func
int yyerror(char const *);
FILE *yyin;
char *yytext;

// main
inter *global_inter;
