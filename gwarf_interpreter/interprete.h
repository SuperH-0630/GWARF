#define false 0
#define true 1
#define bool int

// the type of data(GWARF_value)
typedef enum{
    NUMBER_value = 1,
    INT_value,  // INT 类型
    BOOL_value,  // bool : true or false
    STRING_value,  // char *
} GWARF_value_type;

// all value is GWARF_value
typedef struct GWARF_value{
    GWARF_value_type type;
    union
    {
        double double_value;  // NUMBER
        int int_value;
        bool bool_value;
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
        for_cycle,
        if_branch,  // if
        break_cycle,  // break
        broken,  // break_cycle and other {}
        continue_cycle,
        continued,
        restart,
        restarted,
        rego,
        rewent,
        set_default,
        set_global,
        set_nonlocal,
        code_block,
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
                POW_func,  // <>
                LOG_func,  // <>
                SQRT_func,  // <>
                NEGATIVE_func,  // -a
            } type;
            struct statement *right_exp;  // the right exp
            struct statement *left_exp;  // the left exp
        } operation;

        struct{
            struct statement *condition;  // when to while 
            struct statement *done;  // while to do
        } while_cycle;

        struct{
            struct statement *first;  // the first to do 
            struct statement *condition;  // when to while 
            struct statement *after;  // what to do after the done
            struct statement *done;  // while to do
        } for_cycle;
        
        struct{
            struct if_list *done;  // if_list
        } if_branch;

        struct{
            char *var_name;  // return var
            struct statement *from;  // from where [double->int]
        } base_var;

        struct{
            GWARF_value value;  // return value
        } base_value;

        struct{
            struct statement *times;  // 层数
        } break_cycle;

        struct{
            struct statement *times;  // 层数
        } broken;

        struct{
            struct statement *times;  // 层数
        } continue_cycle;

        struct{
            struct statement *times;  // 层数
        } continued;

        struct{
            struct statement *times;  // 层数
        } restart;

        struct{
            struct statement *times;  // 层数
        } restarted;

        struct{
        } rego;

        struct{
        } rewent;

        struct{
            char *name;
            struct statement *times;  // 层数
        } set_default;

        struct{
            char *name;
        } set_global;

        struct{
            char *name;
        } set_nonlocal;

        struct{
            struct statement *done;  // while to do
        } code_block;

    } code;
    struct statement *next;
} statement;

// ------------------------- result value

typedef struct GWARF_result{
    GWARF_value value;
    enum{
        return_def=1,
        statement_end,
        cycle_break,
        code_broken,
        cycle_continue,
        code_continued,
        cycle_restart,
        code_restarted,
        code_rego,
        code_rewent,
        name_no_found,
    } u;  // the result type[from where]
} GWARF_result;

// ------------------------- default_var [记录默认变量[层]]
typedef struct default_var{
    char *name;
    int from;
    struct default_var *next;
} default_var;

// ------------------------- var base list [记录每一层变量base的链表]

typedef struct var_list{
    var *var_base;
    default_var *default_list;
    struct var_list *next;
} var_list;

// ------------------------- inter paser [记录每一层变量code的链表]

typedef struct statement_list{
    statement *statement_base;
    struct statement_list *next;
} statement_list;


// ------------------------- if list [记录着if...elif...else]

typedef struct if_list{
    struct statement *condition;  // when to while 
    struct statement *done;  // while to do
    struct if_list *next;
} if_list;

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


default_var *make_default_var();
default_var *make_default_var_base();
void append_default_var_base(char * ,int , default_var *);
int get_default(char *, default_var *);


//------- statement func
statement *make_statement();
statement *append_statement(statement *, statement*);

statement_list *make_statement_list();
statement_list *make_statement_base(statement *);
statement_list *append_statement_list(statement *, statement_list *);
statement *find_statement_list(int, statement_list *);
statement_list *free_statement_list(statement_list *);

//------- if func
if_list *make_base_if();
if_list *make_if(statement *, statement *);
if_list *append_elif(if_list *, if_list *);

//------- run func
GWARF_result traverse(statement *, var_list *, bool);
GWARF_result traverse_global(statement *, var_list *);

//------- inter func
inter *get_inter();

// //------ paser func
int yyerror(char const *);
FILE *yyin;
char *yytext;

// main
inter *global_inter;
statement_list *statement_base;
