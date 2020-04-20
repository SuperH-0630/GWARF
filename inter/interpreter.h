#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#define malloc(size) safe_malloc(size)
#define free(p) p=safe_free(p)
#define realloc(p,size) safe_realloc(p,size)
#define memcpy(p1,p2,size) safe_memcpy(p1,p2,size)

#define false 0
#define true 1
#define bool int
#define read_statement_list(the_statement, the_var) read_statement(the_statement, the_var, NULL)

// the type of data(GWARF_value)
typedef enum{
    NUMBER_value = 1,  // [只允许系统使用] [1]
    INT_value,  // INT 类型[只允许系统使用] [2]
    BOOL_value,  // bool : true or false [只允许系统使用] [3]
    STRING_value,  // char * [只允许系统使用] [4]
    NULL_value,  // 无值类型 [5]
    FUNC_value,  // 函数 [6]
    CLASS_value,  // 对象 [7]
    OBJECT_value,  // 实例 [8]
    LIST_value,  // 列表类型 [9]
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
        struct the_list *list_value;
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
        base_value,  // return an GWARF_value
        base_list,  // return an GWARF_value->LIST_value
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
        down,  // a[b]  注：返回变量同时返回the_var链表[func 用于回调]
        slice,
        return_code,
        set_class,  // class aaa; b = aaa() is ```call```
        try_code,  // try to do something except to do something
        raise_e,  // raise exception
        throw_e,  // throw the object class func or NULL
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
            struct statement *base_var;  // a[b] --> a
            struct statement *child_var;  // a[b] --> b
        } down;

        struct{
            GWARF_value value;  // return value
        } base_value;

        struct{
            parameter *value;  // [1,2,3,4] -> to_list
        } base_list;

        struct{
            struct statement *base_var;  // a[1:2:3] -> a
            parameter *value;  // a[1:2:3] -> 1 2 3
        } slice;

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

        struct
        {
            struct statement *try;
            struct statement *except;
            char *name;  // as var
        } try_code;

        struct
        {
            struct statement *done;  // done to get exception object
            struct statement *info;  // the info
        } raise_e;

        struct
        {
            struct statement *done;  // done to get exception object
        } throw_e;

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
        error,
    } u;  // the result type[from where]
    int return_times;  // return用
    char *error_info;  // 输出的错误信息
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
    __pow__func = 14,
    __log__func = 15,
    __sqrt__func = 16,
    __negative__func = 17,
    __powr__func = 18,
    __logr__func = 19,
    __sqrtr__func = 20,
    __subr__func = 21,
    __divr__func = 22,
    __len__func = 23,
    __down__func = 24,
    __set__func = 25,
    __slice__func = 26,
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

typedef struct the_list  // 列表类型
{
    GWARF_value *list_value;  // 列表类型
    int index;  // the max index
} the_list;

// 函数声明
GWARF_result operation_func(statement *, var_list *, var_list *);
GWARF_result while_func(statement *, var_list *);
GWARF_result if_func(if_list *, var_list *);
GWARF_result for_func(statement *, var_list *);
GWARF_result call_back(statement *, var_list *);
GWARF_result call_back_core(GWARF_result, var_list *, parameter *);
GWARF_result block_func(statement *, var_list *);
GWARF_result try_func(statement *, var_list *);
GWARF_result raise_func(statement *, var_list *, bool);

GWARF_result add_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result pow_func(GWARF_result, GWARF_result, var_list *);
GWARF_result log_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sqrt_func(GWARF_result, GWARF_result, var_list *);
GWARF_result assigment_func(char *, GWARF_result, var_list *, int);
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int);
GWARF_result negative_func(GWARF_result, var_list *);

double sqrt_(double, double);
double log_(double, double);

GWARF_value to_int(GWARF_value, var_list *the_var);
GWARF_value to_double(GWARF_value value, var_list *the_var);
GWARF_value to_str(GWARF_value value, var_list *the_var);
GWARF_value to_bool_(GWARF_value value, var_list *the_var);
GWARF_value to_list(GWARF_value value, var_list *the_var);
GWARF_value parameter_to_list(parameter *tmp_s, var_list *the_var);
bool to_bool(GWARF_value);

GWARF_result get__value__(GWARF_value *, var_list *);
GWARF_result get__bool__(GWARF_value *, var_list *);
GWARF_result run_func(GWARF_value *, var_list *, char *);

int len_only_double(double num);
int len_double(double num);
int len_int(int num);
int len_intx(unsigned int num);
GWARF_value to_object(GWARF_value, var_list *);
class_object *make_object(var_list *the_var, var_list *father_var_list);

void login_official_func(int type, int is_class, var_list *the_var, char *name, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
void login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));

// 内置函数
GWARF_result official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// object内置类
class_object *object_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *));
GWARF_result object_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// gobject内置类
class_object *gobject_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result gobject_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// int内置类
class_object *int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// double内置类
class_object *double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *);

// str内置类
class_object *str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// bool内置类
class_object *bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// list内置类
class_object *list_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result list_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// 错误内置类
class_object *BaseException_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result BaseException_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

class_object *Exception_login_official(var_list *the_var, var_list *father_var_list);
class_object *NameException_login_official(var_list *the_var, var_list *father_var_list);

// 生成错误
GWARF_result to_error(char *error_info, char *error_type, var_list *the_var);


bool is_space(GWARF_result *);
bool is_error(GWARF_result *tmp);

if_list *make_base_if();
if_list *make_if(statement *, statement *);
if_list *append_elif(if_list *, if_list *);

statement *make_statement();
statement *append_statement(statement *, statement*);
statement_list *make_statement_list();
statement_list *make_statement_base(statement *);
statement_list *append_statement_list(statement *, statement_list *);
statement *find_statement_list(int, statement_list *);
statement_list *free_statement_list(statement_list *);

var *make_var();
void append_var(char *name, GWARF_value, var *);
void free_var(var *);
var *get_var(char *, var *);
void del_var(char *, var *);
default_var *make_default_var();
default_var *make_default_var_base();
void append_default_var_base(char * ,int , default_var *);
int get_default(char *, default_var *);
var_list *make_var_list();
var_list *make_var_base(var *);
var_list *append_var_list(var *, var_list *);
var_list *append_by_var_list(var_list *, var_list *);
var_list *free_var_list(var_list *);
int get_var_list_len(var_list *);
var *find_var(var_list *,int , char *);
void add_var(var_list *,int , char *, GWARF_value);
var_list *copy_var_list(var_list *);

parameter *make_parameter_name(char *);
void append_parameter_name(char *, parameter *);

parameter *make_parameter_value(statement *);
void append_parameter_value(statement *, parameter *);
parameter *add_parameter_value(statement *, parameter *);

parameter *pack_value_parameter(GWARF_value);
statement *pack_call_name(char *, statement *);


GWARF_result traverse(statement *, var_list *, bool);
GWARF_result traverse_global(statement *, var_list *);

inter *get_inter();

inter *global_inter;
statement_list *statement_base;

int yyerror(char const *);
FILE *yyin;
char *yytext;
#endif