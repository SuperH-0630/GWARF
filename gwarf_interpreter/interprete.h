#include <stdio.h>
#define false 0
#define true 1
#define bool int
#define read_statement_list(the_statement, the_var) read_statement(the_statement, the_var, NULL)

// the type of data(GWARF_value)
typedef enum{
    NUMBER_value = 1,  // [只允许系统使用]
    INT_value,  // INT 类型[只允许系统使用]
    BOOL_value,  // bool : true or false [只允许系统使用]
    STRING_value,  // char * [只允许系统使用]
    NULL_value,  // 无值类型
    FUNC_value,  // 函数
    CLASS_value,  // 对象
    OBJECT_value,  // 实例
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
        struct func *func_value;
        struct class_object *class_value;
        struct the_object *object_value;
    } value;
} GWARF_value;

// ------------------------- parameter for def
typedef struct parameter{
    union
    {
        char *name;  // var name
        struct statement *value;  // or value
    } u;
    struct parameter *next;  // for list
} parameter;

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
        base_var,  // return var value by name
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
        def,  // func
        call,  // func()
        point,  // a.b  注：返回变量同时返回the_var链表[func 用于回调]
        return_code,
        set_class,  // class aaa; b = aaa() is ```call```
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
            struct statement *base_var;  // a.b --> a
            struct statement *child_var;  // a.b --> b
        } point;

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
            struct statement *done;  // block to do
        } code_block;

        struct{
            char *name;
            parameter *parameter_list;  // def parameter
            struct statement *done;  // def to do
        } def;

        struct{
            parameter *parameter_list;  // def parameter
            struct statement *func;  // get func value
        } call;

        struct{
            struct statement *times;  // 层数
            struct statement *value;  // return value
        } return_code;

        struct{
            char *name;  // class name
            struct statement *done;  // class to do
            parameter *father_list;  // 继承
        } set_class;

    } code;
    struct statement *next;
} statement;

// ------------------------- result value

typedef struct GWARF_result{
    GWARF_value value;
    GWARF_value *father;  // a.b --> a
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
    int return_times;  // return用
} GWARF_result;

// ------------------------- default_var [记录默认变量[层]] 用于default语句
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

//------- class/object/func
typedef enum{
    customize = 1,  // func by user
    official,  // func by gwarf
} func_type;

typedef enum{
    printf_func = 1,  // print_func
    __init__func = 2,
    __value__func = 3,
    __add__func = 4,
    __sub__func = 5,
    __mul__func = 6,
    __div__func = 7,
    __eq__func = 8,
    __more__func = 9,
    __less__func = 10,
    __eqmore__func = 11,
    __eqless__func = 12,
    __noteq__func = 13,
} official_func_type;

typedef struct func{
    func_type type;
    official_func_type official_func;
    struct GWARF_result (*paser)(struct func *, struct parameter *, struct var_list *the_var, GWARF_result, var_list *);
    struct parameter *parameter_list;  // def parameter
    struct statement *done;  // def to do
    struct var_list *the_var;  // func会记录the_var，因为不同地方调用var如果var链不统一那就会很乱
    int is_class; 
} func;

typedef struct class_object{
    struct var_list *out_var;  // 外部the_var list
    struct var_list *the_var;  // 记录class_object的  -- 相当与cls
} class_object;

typedef struct the_object{
    struct var_list *cls;  // 记录class_object的  -- 相当与cls
    struct var_list *the_var;  // 记录class_object的实例  -- 相当与self
} the_object;

//------- inter func
inter *get_inter();

// //------ paser func
int yyerror(char const *);
FILE *yyin;
char *yytext;

// ---- parameter func[形参]
parameter *make_parameter_name(char *);
void append_parameter_name(char *, parameter *);

// ---- parameter func[实参]
parameter *make_parameter_value(statement *);
void append_parameter_value(statement *, parameter *);
parameter *add_parameter_value(statement *, parameter *);

parameter *pack_value_parameter(GWARF_value);
statement *pack_call_name(char *, statement *);

// main
inter *global_inter;
statement_list *statement_base;
GWARF_value to_object(GWARF_value, var_list *);

void login_official_func(int type, int is_class, var_list *the_var, char *name, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
void login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));

// 内置函数
GWARF_result official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// int内置类
void int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// double内置类
void double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// str内置类
void str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// bool内置类
void bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);