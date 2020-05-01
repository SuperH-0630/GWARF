#ifndef MEM_INCLUDE
#define MEM_INCLUDE

struct word_paser **global_paser;  // 解析器，记录状态和text
FILE *debug = NULL, *status_log = NULL, *token_log = NULL, *token_info = NULL;
FILE *file_p = NULL;

typedef struct p_status
{
    bool is_parameter;  // parameter模式不匹配 = 
    bool is_func;  // func模式不匹配 ()
    bool is_list;  // 不匹配参数的POW和name_value
    bool is_dict;  // 不匹配参数的MUL和非only_value选项以及用:取代=
} p_status;


#endif