#ifndef TOKN_INCLUED
#define TOKN_INCLUED

#include "../inter/interpreter.h"

#define MAX_PASER_SIZE 10
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
    BAD_token = -2,
    EOF_token = -3,

    // 终结符
    NON_base_value = -4,
    NON_factor = -6,
    NON_polynomial = -7,
    NON_command = -8,
    NON_command_list = -9,
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