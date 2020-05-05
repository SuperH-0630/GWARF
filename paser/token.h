#ifndef TOKN_INCLUED
#define TOKN_INCLUED

#include "../inter/interpreter.h"

#define MAX_PASER_SIZE 86
#define INT_PASER 0
#define DOUBLE_PASER 1
#define ENTER_PASER 2
#define SPACE_PASER 3
#define ADD_PASER 4
#define SUB_PASER 5
#define MUL_PASER 6
#define DIV_PASER 7
#define LB_PASER 8
#define RB_PASER 9
#define WHILE_PASER 10
#define LP_PASER 11
#define RP_PASER 12
#define IF_PASER 13
#define ELIF_PASER 14
#define ELSE_PASER 15
#define COLON_PASER 16
#define FOR_PASER 17
#define VAR_PASER 18
#define LI_PASER 19
#define RI_PASER 20
#define POW_PASER 21
#define LOG_PASER 22
#define SQRT_PASER 23
#define BITNOT_PASER 24
#define BITRIGHT_PASER 25
#define BITLEFT_PASER 26
#define BITAND_PASER 27
#define BITOR_PASER 28
#define BITNOTOR_PASER 29
#define EQEQ_PASER 30
#define MORE_PASER 31
#define MOREEQ_PASER 32
#define LESS_PASER 33
#define LESSEQ_PASER 34
#define NOTEQ_PASER 35
#define AND_PASER 36
#define OR_PASER 37
#define NOT_PASER 38
#define EQ_PASER 39
#define DEF_PASER 40
#define COMMA_PASER 41
#define BREAK_PASER 42
#define BROKEN_PASER 43
#define CONTINUE_PASER 44
#define CONTINUED_PASER 45
#define RESTART_PASER 46
#define RESTARTED_PASER 47
#define REGO_PASER 48
#define REWENT_PASER 49
#define GLOBAL_PASER 50
#define NOLOCAL_PASER 51
#define DEFAULT_PASER 52
#define RETURN_PASER 53
#define STR_PASER 54
#define TRUE_PASER 55
#define FALSE_PASER 56
#define NONE_PASER 57
#define DO_PASER 58
#define IN_PASER 59
#define CLASS_PASER 60
#define TRY_PASER 61
#define EXCEPT_PASER 62
#define AS_PASER 63
#define RAISE_PASER 64
#define THROW_PASER 65
#define ASSERT_PASER 66
#define IGNORE_ENTER 67
#define INTDIV_PASER 68
#define MOD_PASER 69
#define AADD_PASER 70
#define ASUB_PASER 71
#define AMUL_PASER 72
#define ADIV_PASER 73
#define AMOD_PASER 74
#define AINTDIV_PASER 75
#define APOW_PASER 76
#define FADD_PASER 77
#define FSUB_PASER 78
#define LAMBDA_PASER 79
#define POINT_PASER 80
#define IMPORT_PASER 81
#define INCLUDE_PASER 82
#define COMMENT_PASER 83
#define SVAR_PASER 84
#define FUNC_PASER 85

// 获取并返回一个token
#define get_pop_token(status,list,new_token) \
do{ \
    safe_get_token(status, list); \
    new_token = pop_node(list); \
}while(0);

// 执行右边的匹配
#define get_right_token(status,list,func,new_token) \
do{ \
    safe_get_token(status, list); \
    func(status, list); \
    new_token = pop_node(list); \
}while(0);

// 执行左边的匹配
#define get_base_token(status,list,func,new_token) \
do{ \
    func(status, list); \
    new_token = pop_node(list); \
}while(0);

// 返回一个token...不需要back_token
#define back_one_token(list, new_token) add_node(list, new_token)

#define back_again(list, new_token) \
do{ \
add_node(list, new_token); \
back_token(list); \
}while(0);

#define get_stop_token(status, list)  \
do{ \
token stop; \
get_pop_token(&status, list, stop); \
printf("stop.type = %d\n", stop.type); \
if((status.dict_to_enter && stop.type == RP_PASER) || stop.type == EOF_token){ \
    back_again(list, stop); \
    break;  \
} \
if(stop.type != ENTER_PASER){ \
    paser_error("Don't get stop token or EOF"); \
} \
}while(0);
// EOF的返回使用了回退，目的是让command_list第二次执行command的时候，执行safe_get_token获取EOF，否则将会回去两个EOF

// 非终结符
#define NonTerminator -1

typedef enum token_type
{
    INT = INT_PASER,
    DOUBLE = DOUBLE_PASER,
    ENTER = ENTER_PASER,
    SPACE = SPACE_PASER,
    ADD = ADD_PASER,
    SUB = SUB_PASER,
    MUL = MUL_PASER,
    DIV = DIV_PASER,
    LB = LB_PASER,
    RB = RB_PASER,
    WHILE = WHILE_PASER,
    LP = LP_PASER,
    RP = RP_PASER,
    LI = LI_PASER,
    RI = RI_PASER,
    POW = POW_PASER,
    LOG = LOG_PASER,
    SQRT = SQRT_PASER,
    IF = IF_PASER,
    ELIF = ELIF_PASER,
    ELSE = ELSE_PASER,
    COLON = COLON_PASER,
    VAR = VAR_PASER,
    BITNOT = BITNOT_PASER,
    BITRIGHT = BITRIGHT_PASER,
    BITLEFT = BITLEFT_PASER,
    BITAND = BITAND_PASER,
    BITOR = BITOR_PASER,
    BITNOTOR = BITNOTOR_PASER,
    EQEQ = EQEQ_PASER,
    MORE = MORE_PASER,
    MOREEQ = MOREEQ_PASER,
    LESS = LESS_PASER,
    LESSEQ = LESSEQ_PASER,
    NOTEQ = NOTEQ_PASER,
    AND = AND_PASER,
    OR = OR_PASER,
    NOT = NOT_PASER,
    EQ = EQ_PASER,
    DEF = DEF_PASER,
    COMMA = COMMA_PASER,
    BREAK = BREAK_PASER,
    BROKEN = BROKEN_PASER,
    CONTINUE = CONTINUE_PASER,
    CONTINUED = CONTINUED_PASER,
    RESTART = RESTART_PASER,
    RESTARTED = RESTARTED_PASER,
    REGO = REGO_PASER,
    REWENT = REWENT_PASER,
    GLOBAL = GLOBAL_PASER,
    NOLOCAL = NOLOCAL_PASER,
    DEFAULT = DEFAULT_PASER,
    RETURN = RETURN_PASER,
    STR = STR_PASER,
    DO = DO_PASER,
    BOO_TRUE = TRUE_PASER,
    BOOL_FALSE = FALSE_PASER,
    NONE = NONE_PASER,
    IN = IN_PASER,
    CLASS = CLASS_PASER,
    TRY = TRY_PASER,
    EXCEPT = EXCEPT_PASER,
    AS = AS_PASER,
    RAISE = RAISE_PASER,
    THROW = THROW_PASER,
    ASSERT = ASSERT_PASER,
    IGNORE = IGNORE_ENTER,
    INTDIV = INTDIV_PASER,
    MOD = MOD_PASER,
    AADD = AADD_PASER,
    ASUB = ASUB_PASER,
    AMUL = AMUL_PASER,
    ADIV = ADIV_PASER,
    AMOD = AMOD_PASER,
    AINTDIV = AINTDIV_PASER,
    APOW = APOW_PASER,
    FADD = FADD_PASER,
    FSUB = FSUB_PASER,
    LAMBDA = LAMBDA_PASER,
    POINT = POINT_PASER,
    SVAR = SVAR_PASER,

    // 特殊符号
    BAD_token = -2,
    EOF_token = -3,

    // 终结符
    NON_base_value = -4,
    NON_factor = -6,
    NON_polynomial = -7,
    NON_command = -8,
    NON_command_list = -9,
    NON_while = -10,
    NON_block = -11,
    NON_top_exp = -12,
    NON_if = -13,
    NON_elif = -14,
    NON_else = -15,
    NON_for = -16,
    NON_element = -17,
    NON_base_var = -18,
    NON_power = -19,
    NON_bit_not = -20,
    NON_negative = -21,
    NON_bit_move = -22,
    NON_bit_and = -23,
    NON_bit_or = -24,
    NON_bit_notor = -25,
    NON_compare = -26,
    NON_bool_and = -27,
    NON_bool_or = -28,
    NON_bool_not = -29,
    NON_eq = -30,
    NON_def = -31,
    NON_call = -32,
    NON_parameter = -33,
    NON_call_down = -34,
    NON_ctrl = -35,
    NON_var_ctrl = -36,
    NON_return = -37,
    NON_list = -38,
    NON_dict = -39,
    NON_hide_list = -40,
    NON_do_while = -41,
    NON_try = -42,
    NON_exception = -43,
    NON_self_exp = -44,
    NON_lambda = -45,
    NON_point = -46,
    NON_import = -47,
    NON_chose = -48,
    NON_svar = -49,
} token_type;

typedef union token_data
{
    char *text;
    int i_number;
    double d_number;
    struct statement *statement_value;
    struct if_list *if_list_base;
    struct parameter *parameter_list;
} token_data;


typedef struct token
{
    token_type type;  // token的类型，是数字、变量、关键字、符号
    enum {
        text = 1,
        d_number,
        i_number,
        statement_value,
        if_list_base,
        parameter_list,
        empty,
    } data_type;  // data的数据类型
    token_data data;
    int tab;  // 缩进
} token;

// 解析token链表，FILO
typedef struct token_node
{
    int max_index;
    int seek;  // 现在读取的位置，当max_index == seek的时候调用lexical读取token
    int max_size;
    struct token *token_list;  // 记录token的FILO
} token_node;

struct token_node *make_token_node();
void add_node(struct token_node *, struct token);
struct token pop_node(struct token_node *);
void safe_get_token(p_status *, struct token_node *);
void back_token(token_node *);

#endif