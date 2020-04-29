#ifndef TOKN_INCLUED
#define TOKN_INCLUED

#include "../inter/interpreter.h"

#define MAX_PASER_SIZE 36
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
#define COMMA_PASER 16
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

#define get_stop_token()  \
do{ \
token stop; \
get_pop_token(status, list, stop); \
printf("stop.type = %d\n", stop.type); \
if(stop.type != ENTER_PASER && stop.type != EOF_token){ \
    paser_error("Don't get stop token or EOF"); \
} \
if(stop.type == EOF_token){ \
    back_one_token(list, stop); \
} \
}while(0);

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
    IF = IF_PASER,
    ELIF = ELIF_PASER,
    ELSE = ELSE_PASER,
    COMMA = COMMA_PASER,
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
        text,
        d_number,
        i_number,
        statement_value,
        if_list_base,
        parameter_list,
        empty,
    } data_type;  // data的数据类型
    token_data data;
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
void safe_get_token(int *, struct token_node *);
void back_token(token_node *);

token_node *global_token_node = NULL;

#endif