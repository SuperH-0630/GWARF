#ifndef MEM_INCLUDE
#define MEM_INCLUDE

#define reset_status(status) {status.not_match_eq=false,status.not_match_tuple=false,status.not_match_call=false,status.match_list=false,status.match_dict=false,status.is_left=true,status.is_peq=false,status.is_for=false,status.dict_to_enter=false,status.ignore_enter=false,status.is_slice=false,status.is_args=false;}

FILE *debug = NULL, *status_log = NULL, *token_log = NULL, *token_info = NULL;

typedef struct p_status
{
    bool not_match_eq;  // parameter模式不匹配 = 
    bool not_match_tuple;  // func模式不匹配 ()
    bool not_match_call;
    bool match_list;  // 不匹配参数的POW和name_value
    bool match_dict;  // 不匹配参数的MUL和非only_value选项以及用:取代=
    bool is_left;  // 是否为最左边的公式
    bool is_peq;  // 正在使用解包赋值
    bool is_for;  // for循环，用于排除COMMA的使用[top_exp]
    bool ignore_enter;  // 忽略回车
    bool dict_to_enter;  // 检查stop的时候把"}"算上
    bool is_slice;  // slice使用:代替
    bool is_args;  // args不允许虚解包
    FILE *file_p;
    struct word_paser **global_paser;
} p_status;


#endif