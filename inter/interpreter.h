#include "../mem/mem.h"

#ifndef _INTERPRETER_H
#define _INTERPRETER_H
#define MAX_SIZE (1024)

#define false 0
#define true 1
#define bool int

#define assignment_statement(the_statement,the_var,login_var,right_result,global_inter) assignment_statement_core(the_statement,the_var,login_var,right_result,1,auto_public,global_inter)
#define assignment_statement_eq(the_statement,the_var,login_var,right_result,global_inter) assignment_statement_core(the_statement,the_var,login_var,right_result,0,auto_public,global_inter)
#define read_statement_list(the_statement,the_var,global_inter) read_statement(the_statement,the_var,NULL,NULL,lock,global_inter)
#define run_func(base_the_var,the_var,name,global_inter) run_func_core(base_the_var,the_var,name,false,global_inter)
#define GWARF_value_reset {.type=NULL_value,.value.int_value=0,.lock_token=base}
#define GWARF_result_reset {.value.type=NULL_value,.value.value.int_value=0,.value.lock_token=base,.u = statement_end,.father=NULL,.error_info="",.base_name=NULL}

#define error_space(tmp, to, as) \
do{ \
if(is_error(&tmp) || is_space(&tmp)){ \
    as = tmp; \
    goto to; \
} \
}while(0);

#define push_statement(tmp_statement,token) \
do{ \
append_statement(tmp_statement,token.data.statement_value); \
}while(0);

// 日志文件
extern FILE *debug, *status_log, *token_log, *token_info, *inter_info, *tree_info;

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
    enum {
        base,
        lock,
    } lock_token;  // 代表object、class等的访问权限 之对self和cls有效
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
    enum{  // 代表变量访问权限
        auto_public,  // 自动权限
        public,
        protect,
        private,
    } lock;
    char *name;  // var name
    GWARF_value value;
    struct var *next;  // for list
} var;

// ------------------------- hash_var
typedef struct hash_var{
    struct var **hash;  // 这是一个指针数组
} hash_var;

// ------------------------- statement

typedef enum var_key_token{
    auto_token,  // 默认情况下auto_token是具有权限访问protetc base_var的，但不具有权限修改protect var，使用point运算符时会修改auto_token
    public_token,
    protect_token,
    private_token,
} var_key_token;

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
        base_svar,
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
                NOTEQ_func,  // !=
                POW_func,  // **
                LOG_func,  // log
                SQRT_func,  // sqrt
                NEGATIVE_func,  // -a
                AND_func,  // &&
                OR_func,  // ||
                NOT_func,  // !
                MOD_func,  // %
                INTDIV_func,  // //
                AADD_func,  // +=
                ASUB_func,  // -=
                ADIV_func,  // /=
                AMUL_func,  // *=
                AMOD_func,  // %=
                AINTDIV_func,  // //=
                APOW_func,  // **=
                ABITAND_func,  // &=
                ABITOR_func,  // |=
                ABITNOTOR_func, // ^=
                ABITRIGHT_func,  // >>=
                ABITLEFT_func,  // <<=
                FADD_func,  // a++
                LADD_func,  // ++a
                FSUB_func,  // a--
                LSUB_func,  // --a
                BITAND_func,
                BITOR_func,
                BITNOTOR_func,
                BITRIGHT_func,
                BITLEFT_func,
                BITNOT_func,
                ILEFT_func,  // <==
                IRIGHT_func,  // ==>
                ISLEFT_func,  // <:=
                ISRIGHT_func,  // =:>
                BOOLNOTOR_func,  // !==
                BOOLIS_func,  // <=>
                BOOLSAND_func,  // and
                BOOLSOR_func,  // or
                IS_func,  // a is b
                IN_func,
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
            struct statement *else_do;  // else to do
        } while_cycle;

        struct{
            struct statement *first;  // the first to do 
            struct statement *condition;  // when to while 
            struct statement *after;  // what to do after the done
            struct statement *done;  // while to do
            struct statement *else_do;  // else to do
        } for_cycle;
        
        struct{
            struct if_list *done;  // if_list
        } if_branch;

        struct{
            char *var_name;  // return var
            struct statement *from;  // from where [double->int]
            enum var_key_token lock_token;  // 如果用于赋值，则是新变量的权限，如果用于读取则是访问的权限 [默认情况 base_var访问权限不受限制，point的时候会更正访问权限]
        } base_var;

        struct{
            struct statement *var;  // return var
            struct statement *from;  // from where [double->int]
            enum var_key_token lock_token;
        } base_svar;

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
            struct statement *var;  // 方法的名字
            struct statement *setup;  // setup to do
            enum {
                function,
                action,
                cls,
                auto_func,
            } type;  // 静态函数[function] or 实例函数[action] or 类方法[cls] or 默认[def]
            bool is_inline;  // inline函数不设单独的func_var空间
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
            struct statement *else_do;  // else to do
            struct statement *finally_do;  // finally to do
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
            struct statement *else_do;  // else to do
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
    GWARF_value value;
    GWARF_value *father;  // a.b --> a
    int return_times;  // return用
    char *error_info;  // 输出的错误信息
    char *base_name;  // 返回名字
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
    enum{
        run_func,
        run_while,
        run_if,
        run_class,
        run_object,
    } tag;  // var_list的标签
} var_list;

// ------------------------- inter paser [记录每一层变量code的链表]

typedef struct statement_list{
    struct statement *statement_base;
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
    printf_func,
    input_func,
    isinherited_func,
    __init__func,
    __value__func,
    __add__func,
    __sub__func,
    __mul__func,
    __div__func,
    __eq__func,
    __more__func,
    __less__func,
    __eqmore__func,
    __eqless__func,
    __noteq__func,
    __pow__func,
    __log__func,
    __sqrt__func,
    __negative__func,
    __powr__func,
    __logr__func,
    __sqrtr__func,
    __subr__func,
    __divr__func,
    __len__func,
    __down__func,
    __set__func,
    __slice__func,
    __iter__func,
    __next__func,
    __idiv__func,
    __idivr__func,
    __mod__func,
    __modr__func,
    __bitand__func,
    __bitor__func,
    __bitnotor__func,
    __bitleft__func,
    __bitleftr__func,
    __bitright__func,
    __bitrightr__func,
    __bitnot__func,
    __assignment__func,
    __in__func,
} official_func_type;

typedef struct func{
    func_type type;
    official_func_type official_func;
    struct GWARF_result (*paser)(struct func *, struct parameter *, struct var_list *, struct GWARF_result, struct var_list *,inter *);
    struct parameter *parameter_list;  // def parameter
    struct statement *done;  // def to do
    struct var_list *the_var;  // func会记录the_var，因为不同地方调用var如果var链不统一那就会很乱
    struct var_list *self;  // func会记录自己的self信息(可以类似于class和object那样调用)，对于setup func会合并到the_var中
    int is_class;
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
GWARF_result operation_func(statement *, var_list *, var_list *, inter *);
GWARF_result while_func(statement *, var_list *, inter *);
GWARF_result if_func(if_list *, var_list *, inter *);
GWARF_result for_func(statement *, var_list *, inter *);
GWARF_result call_back(statement *, var_list *, inter *);
GWARF_result login_var(var_list *, var_list *, parameter *, parameter *, inter *);
GWARF_result call_back_core(GWARF_result, var_list *, parameter *, inter *);
GWARF_result block_func(statement *, var_list *, inter *);
GWARF_result try_func(statement *, var_list *, inter *);
GWARF_result raise_func(statement *, var_list *, bool, inter *);
GWARF_result import_func(statement *, var_list *, inter *);
GWARF_result include_func(statement *, var_list *, inter *);
GWARF_result forin_func(statement *, var_list *, inter *);
GWARF_result assert_func(statement *, var_list *, inter *);

GWARF_result add_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result pow_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result log_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result sqrt_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result assignment_func(char *, GWARF_result, var_list *, int, int);  // 不需要inter
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int, inter *);
GWARF_result is_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result negative_func(GWARF_result, var_list *, inter *);
GWARF_result assignment_statement_core(statement *, var_list *, var_list *, GWARF_result, bool, int, inter *);
GWARF_result assignment_statement_value(statement *, var_list *, var_list *, GWARF_value, inter *);
GWARF_result not_func(GWARF_result, var_list *, inter *);
GWARF_result matchbool_func(statement *, statement *, var_list *, int, inter *);
GWARF_result sleft_func(statement *, statement *, var_list *, inter *);
GWARF_result sright_func(statement *, statement *, var_list *, inter *);
GWARF_result or_func(statement *, statement *, var_list *, inter *);
GWARF_result and_func(statement *, statement *, var_list *, inter *);
GWARF_result int_div_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result mod_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result bit_not_func(GWARF_result, var_list *, inter *);
GWARF_result bit_right_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result bit_left_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result bit_notor_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result bit_or_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result bit_and_func(GWARF_result, GWARF_result, var_list *, inter *);
GWARF_result in_func(GWARF_result, GWARF_result, var_list *, inter *);

double sqrt_(double, double);
double log_(double, double);

GWARF_result to_int(GWARF_value, var_list *the_var,inter *);
GWARF_result to_double(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_str(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_str_dict(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_bool_(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_list(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_dict(GWARF_value value, var_list *the_var,inter *);
GWARF_result to_tuple(GWARF_value value, inter *);
GWARF_result parameter_to_list(parameter *tmp_s, var_list *the_var, inter *global_inter);
GWARF_result parameter_to_dict(parameter *tmp_s, var_list *the_var, inter *global_inter);

bool start_with(char *, char *);
char *del_start(char *, char *);
GWARF_value key_to_str(char *);

bool to_bool(GWARF_value, inter *global_inter);

GWARF_result get__value__(GWARF_value *, var_list *, inter *);
GWARF_result get__bool__(GWARF_value *, var_list *, inter *);
GWARF_result get__iter__(GWARF_value *, var_list *, inter *);
GWARF_result get__next__(GWARF_value *, var_list *, inter *);
GWARF_result get__assignment__(GWARF_value *, var_list *, inter *);
GWARF_result run_func_core(GWARF_value *, var_list *, char *, bool, inter *);

int len_only_double(double num);
int len_double(double num);
int len_int(int num);
int len_intx(unsigned int num);
GWARF_result to_object(GWARF_result, inter *);
GWARF_result get_object(parameter *, char *, var_list *, inter *);
class_object *make_object(var_list *the_var, var_list *father_var_list);

void login_official_func(int type, int is_class, var_list *the_var, char *name, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *));
void login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *),inter *);

// 内置函数
GWARF_result official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// object内置类
class_object *object_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *),inter *);
GWARF_result object_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// gobject内置类
class_object *gobject_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result gobject_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// int内置类
class_object *int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// double内置类
class_object *double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// str内置类
class_object *str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// bool内置类
class_object *bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// list内置类
class_object *tuple_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result tuple_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// list内置类
class_object *list_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result list_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// dict内置类
class_object *dict_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result dict_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

// 错误内置类
class_object *BaseException_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list,inter *);
GWARF_result BaseException_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter);

class_object *Exception_login_official(var_list *the_var, var_list *father_var_list,inter *global_inter);
class_object *NameException_login_official(var_list *the_var, var_list *father_var_list,inter *global_inter);
class_object *IterException_login_official(var_list *the_var, var_list *father_var_list,inter *global_inter);
class_object *AssertException_login_official(var_list *the_var, var_list *father_var_list,inter *global_inter);
class_object *AssignmentException_login_official(var_list *the_var, var_list *father_var_list,inter *global_inter);
class_object *IndexException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *KeyException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *ImportException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *IncludeException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *DivZeroException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *ValueException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *TypeException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *ArgsException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *SystemctlException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);
class_object *VarException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter);

// 生成错误
GWARF_result to_error(char *, char *, inter *);


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
void append_var(char *name, GWARF_value, var *, int);
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
var *find_var(var_list *,int , char *, int *);
void add_var(var_list *,int , char *, GWARF_value, int);
void del_var_var_list(var_list *,int, char *);
var_list *copy_var_list(var_list *);

hash_var *make_hash_var();
unsigned int time33(char *);
int login_node(char *, GWARF_value, hash_var *, int);
var *find_node(char *, hash_var *);
void del_var_node(char *, hash_var *);

parameter *make_parameter_name(statement *);
parameter *append_parameter_name(statement *, parameter *);

parameter *make_parameter_value(statement *);
parameter *append_parameter_value(statement *, parameter *);
parameter *add_parameter_value(statement *, parameter *);

parameter *pack_value_parameter(GWARF_value);
statement *pack_call_name(char *, statement *);


GWARF_result traverse(statement *, var_list *, bool,inter *);
GWARF_result traverse_global(statement *, var_list *,inter *);
GWARF_result traverse_get_value(statement *, var_list *, var_list *,inter *);

inter *get_inter();
void login(var_list *the_var, inter *global_inter);

void traverse_tree(statement *the_statement, int lv);
void print_statement(statement *the_statement, int lv);
void parameter_tree(parameter *the_parameter, int lv);
void if_tree(if_list *the_branch, int lv);

#endif