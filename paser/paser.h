#ifndef MEM_INCLUDE
#define MEM_INCLUDE

#define reset_status(status) {status.is_parameter=false,status.is_func=false,status.is_list=false,status.is_dict=false,status.is_left=true,status.is_peq=false,status.is_for=false,status.dict_to_enter=false,status.ignore_enter=false,status.is_slice=false;}

FILE *debug = NULL, *status_log = NULL, *token_log = NULL, *token_info = NULL;

typedef struct p_status
{
    bool is_parameter;  // parameter模式不匹配 = 
    bool is_func;  // func模式不匹配 ()
    bool is_call;
    bool is_list;  // 不匹配参数的POW和name_value
    bool is_dict;  // 不匹配参数的MUL和非only_value选项以及用:取代=
    bool is_left;  // 是否为最左边的公式
    bool is_peq;  // 正在使用解包赋值
    bool is_for;  // for循环，用于排除COMMA的使用[top_exp]
    FILE *file_p;
    struct word_paser **global_paser;
    bool ignore_enter;  // 忽略回车
    bool dict_to_enter;  // 检查stop的时候把"}"算上
    bool is_slice;  // slice使用:代替
} p_status;


#endif