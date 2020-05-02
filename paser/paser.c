#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"../inter/interpreter.h"
#include "paser.h"
#include "lexical.c"
#include "tokenstream.c"
#include "syntax.c"

int parser(char *file_address){
    p_status paser_status = {.is_parameter = false, .is_func=false, .is_list=false, .is_dict=false, .is_left=false, .is_peq=false, .is_for=false};
    token_node *global_token_node = make_token_node();
    paser_status.global_paser = login_paser();  // 注册解释器[往global_paser写入数据]
    
    paser_status.file_p = fopen(file_address, "r");  // 打开文件
    safe_get_token(&paser_status, global_token_node);
    command_list(&paser_status, global_token_node);
    free_list(paser_status.global_paser);  // 释放解释器
    fclose(paser_status.file_p);
    return 0;
}
