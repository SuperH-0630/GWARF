#include "../mem/mem.h"

#ifndef _INTERPRETER_H
#define _INTERPRETER_H
#define MAX_SIZE (1024)

#define false 0
#define true 1
#define bool int

#define read_statement_list(the_statement,the_var) read_statement(the_statement,the_var,NULL)
#define run_func(base_the_var,the_var,name) run_func_core(base_the_var,the_var,name,false)

#define push_statement(base,token) \
do{ \
statement *tmp = find_statement_list(0, base); \
append_statement(tmp, token.data.statement_value); \
}while(0);

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
    LIST_value,  // 列表类型 [只允许系统使用] [9]
    DICT_value,  // 字典类型 [只允许系统使用] [10]
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
        struct the_dict *dict_value;
    } value;
} GWARF_value;

// ------------------------- parameter for def
typedef struct parameter{
    struct
    {
        struct statement *var;  // the_var
        struct statement *value;  // var value
    } u;
    enum {
        only_value,
        name_value,  // 形参/实参
        put_args,
        put_kwargs,
    } type;
    struct parameter *next;  // for list
} parameter;

// ------------------------- var

typedef struct var{
    char *name;  // var name
    GWARF_value value;
    struct var *next;  // for list
} var;

// ------------------------- hash_var
typedef struct hash_var{
    struct var **hash;  // 这是一个指针数组
} hash_var;

// ------------------------- statement

typedef struct statement{
    enum statement_type{
        start=1,  // for base statement
        operation,  // such as + - * /
        base_var,  // return var value by name
        base_value,  // return an GWARF_value
        base_tuple,
        base_list,  // return an GWARF_value->LIST_value
        base_dict,  // return an GWARF_value->DICT_value
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
        lambda_func,  // lambda x:x**2
        call,  // func()
        point,  // a.b  注：返回变量同时返回the_var链表[func 用于回调]
        down,  // a[b]  注：返回变量同时返回the_var链表[func 用于回调]
        slice,
        return_code,  // [26]
        set_class,  // class aaa; b = aaa() is ```call```
        try_code,  // try to do something except to do something
        raise_e,  // raise exception
        throw_e,  // throw the object class func or NULL
        import_class,   // import file
        include_import,  // include file
        for_in_cycle,  // for i in a
        assert_e,
        chose_exp,
        pack_eq,
    } type;  // the statement type

    union
    {
        struct{
            enum{
                ADD_func = 1,  // +
                SUB_func,  // -
                DIV_func,  // /
                MUL_func,  // *
                ASSIGnMENT_func, // =
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
                AND_func,  // -a
                OR_func,  // -a
                NOT_func,  // -a
                MOD_func,  // %
                INTDIV_func,  // //
                AADD_func,  // +=
                ASUB_func,  // -=
                ADIV_func,  // /=
                AMUL_func,  // *=
                AMOD_func,  // %=
                AINTDIV_func,  // //=
                FADD_func,  // a++
                LADD_func,  // ++a
                FSUB_func,  // a--
                LSUB_func,  // --a
                APOW_func,  // ^=
                BITAND_func,
                BITOR_func,
                BITNOTOR_func,
                BITRIGHT_func,
                BITLEFT_func,
                BITNOT_func,
            } type;
            struct statement *right_exp;  // the right exp
            struct statement *left_exp;  // the left exp
        } operation;

        struct{
            struct statement *condition;  // xxx if yyy else zzz -> xxx
            struct statement *true_do;  // xxx if yyy else zzz -> yyy
            struct statement *false_do;  // xxx if yyy else zzz -> zzz
        } chose_exp;

        struct{
            struct statement *condition;  // when to while 
            struct statement *done;  // while to do
            bool first_do;  // do_while = true, while = false
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
            struct parameter *child_var;  // a[b,c,d] --> b,c,d
        } down;

        struct{
            GWARF_value value;  // return value
        } base_value;

        struct{
            parameter *value;  // [1,2,3,4] -> to_list
        } base_list;

        struct{
            parameter *value;  // [1,2,3,4] -> to_tuple
        } base_tuple;

        struct{
            parameter *right;  // 实参
            parameter *left;  // 形参
        } pack_eq;

        struct{
            parameter *value;  // [1,2,3,4] -> to_list
        } base_dict;

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
            parameter *parameter_list;  // def parameter
            struct statement *done;  // def to do
            struct statement *var;  // from where
        } def;

        struct{
            parameter *parameter_list;  // lambda parameter
            struct statement *done;  // lambda to do
        } lambda_func;

        struct{
            parameter *parameter_list;  // def parameter
            struct statement *func;  // get func value
        } call;

        struct{
            struct statement *times;  // 层数
            struct statement *value;  // return value
        } return_code;

        struct{
            struct statement *done;  // class to do
            parameter *father_list;  // 继承
            struct statement *var;  // from where [double->int]
        } set_class;

        struct
        {
            struct statement *try;
            struct statement *except;
            struct statement *var;  // as var
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

        struct
        {
            struct statement *file;  // get address for file
            struct statement *var;  // as name
        } import_class;

        struct
        {
            struct statement *file;  // get address for file
        } include_import;

        struct
        {
            struct statement *var;  // for i in a -> i
            struct statement *iter;  // for i in a -> a
            struct statement *done;  // for while to do
        } for_in_cycle;

        struct
        {
            struct statement *condition;  // for i in a -> i
            struct statement *info;  // for while to do
        } assert_e;

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
    struct hash_var *hash_var_base;
    struct default_var *default_list;
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
    hash_var *global_var;  // global var链表
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
    __iter__func = 27,
    __next__func = 28,
    __idiv__func = 29,
    __idivr__func = 30,
    __mod__func = 31,
    __modr__func = 32,
    __bitand__func = 33,
    __bitor__func = 34,
    __bitnotor__func = 35,
    __bitleft__func = 36,
    __bitleftr__func = 37,
    __bitright__func = 38,
    __bitrightr__func = 39,
    __bitnot__func = 40,
    __assignment__func = 41,
} official_func_type;

typedef struct func{
    func_type type;
    official_func_type official_func;
    struct GWARF_result (*paser)(struct func *, struct parameter *, struct var_list *the_var, GWARF_result, var_list *);
    struct parameter *parameter_list;  // def parameter
    struct statement *done;  // def to do
    struct var_list *the_var;  // func会记录the_var，因为不同地方调用var如果var链不统一那就会很乱
    bool is_class; 
    bool is_lambda;
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

typedef struct the_dict  // 列表类型
{
    struct hash_var *dict_value;  // 列表类型
    int index;  // the max index
    struct dict_key *name_list;  // 值插入的顺序
} the_dict;

typedef struct dict_key  // dict的key类型
{
    char *key;
    struct dict_key *next;
} dict_key;

// 函数声明
GWARF_result operation_func(statement *, var_list *, var_list *);
GWARF_result while_func(statement *, var_list *);
GWARF_result if_func(if_list *, var_list *);
GWARF_result for_func(statement *, var_list *);
GWARF_result call_back(statement *, var_list *);
GWARF_result login_var(var_list *, var_list *, parameter *, parameter *);
GWARF_result call_back_core(GWARF_result, var_list *, parameter *);
GWARF_result block_func(statement *, var_list *);
GWARF_result try_func(statement *, var_list *);
GWARF_result raise_func(statement *, var_list *, bool);
GWARF_result import_func(statement *, var_list *);
GWARF_result include_func(statement *, var_list *);
GWARF_result forin_func(statement *, var_list *);
GWARF_result assert_func(statement *, var_list *);

GWARF_result add_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result pow_func(GWARF_result, GWARF_result, var_list *);
GWARF_result log_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sqrt_func(GWARF_result, GWARF_result, var_list *);
GWARF_result assignment_func(char *, GWARF_result, var_list *, int);
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int);
GWARF_result negative_func(GWARF_result, var_list *);
GWARF_result assignment_statement(statement *, var_list *, var_list *, GWARF_result);
GWARF_result assignment_statement_value(statement *, var_list *, var_list *, GWARF_value);
GWARF_result not_func(GWARF_result, var_list *);
GWARF_result or_func(statement *, statement *, var_list *);
GWARF_result and_func(statement *, statement *, var_list *);
GWARF_result int_div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mod_func(GWARF_result, GWARF_result, var_list *);
GWARF_result bit_not_func(GWARF_result, var_list *);
GWARF_result bit_right_func(GWARF_result, GWARF_result, var_list *);
GWARF_result bit_left_func(GWARF_result, GWARF_result, var_list *);
GWARF_result bit_notor_func(GWARF_result, GWARF_result, var_list *);
GWARF_result bit_or_func(GWARF_result, GWARF_result, var_list *);
GWARF_result bit_and_func(GWARF_result, GWARF_result, var_list *);

double sqrt_(double, double);
double log_(double, double);

GWARF_value to_int(GWARF_value, var_list *the_var);
GWARF_value to_double(GWARF_value value, var_list *the_var);
GWARF_value to_str(GWARF_value value, var_list *the_var);
GWARF_value to_str_dict(GWARF_value value, var_list *the_var);
GWARF_value to_bool_(GWARF_value value, var_list *the_var);
GWARF_value to_list(GWARF_value value, var_list *the_var);
GWARF_value to_dict(GWARF_value value, var_list *the_var);
GWARF_value parameter_to_list(parameter *tmp_s, var_list *the_var);
GWARF_value parameter_to_dict(parameter *tmp_s, var_list *the_var);

bool start_with(char *, char *);
char *del_start(char *, char *);
GWARF_value key_to_str(char *);

bool to_bool(GWARF_value);

GWARF_result get__value__(GWARF_value *, var_list *);
GWARF_result get__bool__(GWARF_value *, var_list *);
GWARF_result get__iter__(GWARF_value *, var_list *);
GWARF_result get__next__(GWARF_value *, var_list *);
GWARF_result get__assignment__(GWARF_value *, var_list *);
GWARF_result run_func_core(GWARF_value *, var_list *, char *, bool);

int len_only_double(double num);
int len_double(double num);
int len_int(int num);
int len_intx(unsigned int num);
GWARF_value to_object(GWARF_value, var_list *);
GWARF_result get_object(parameter *, char *, var_list *);
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
class_object *tuple_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result tuple_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// list内置类
class_object *list_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result list_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// dict内置类
class_object *dict_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result dict_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

// 错误内置类
class_object *BaseException_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list);
GWARF_result BaseException_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var);

class_object *Exception_login_official(var_list *the_var, var_list *father_var_list);
class_object *NameException_login_official(var_list *the_var, var_list *father_var_list);
class_object *IterException_login_official(var_list *the_var, var_list *father_var_list);
class_object *AssertException_login_official(var_list *the_var, var_list *father_var_list);
class_object *AssignmentException_login_official(var_list *the_var, var_list *father_var_list);

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
var_list *make_var_base(hash_var *);
var_list *append_var_list(hash_var *, var_list *);
var_list *append_by_var_list(var_list *, var_list *);
var_list *free_var_list(var_list *);
int get_var_list_len(var_list *);
var *find_var(var_list *,int , char *);
void add_var(var_list *,int , char *, GWARF_value);
void del_var_var_list(var_list *,int, char *);
var_list *copy_var_list(var_list *);

hash_var *make_hash_var();
unsigned int time33(char *);
int login_node(char *, GWARF_value, hash_var *);
var *find_node(char *, hash_var *);
void del_var_node(char *, hash_var *);

parameter *make_parameter_name(statement *);
parameter *append_parameter_name(statement *, parameter *);

parameter *make_parameter_value(statement *);
parameter *append_parameter_value(statement *, parameter *);
parameter *add_parameter_value(statement *, parameter *);

parameter *pack_value_parameter(GWARF_value);
statement *pack_call_name(char *, statement *);


GWARF_result traverse(statement *, var_list *, bool);
GWARF_result traverse_global(statement *, var_list *);

inter *get_inter();
void login(var_list *the_var);

inter *global_inter;
statement_list *statement_base;

int yyerror(char const *);
FILE *yyin;
char *yytext;
#endif