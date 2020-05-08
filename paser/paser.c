#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include"../inter/interpreter.h"
#include "paser.h"
#include "lexical.c"
#include "tokenstream.c"
#include "syntax.c"

int parser(char *file_address, inter *global_inter){
    token_node *global_token_node = make_token_node();
    p_status paser_status;
    reset_status(paser_status);
    
    paser_status.global_paser = login_paser();  // 注册解释器[往global_paser写入数据]
    paser_status.file_p = fopen(file_address, "r");  // 打开文件
    if(paser_status.file_p == NULL){
        return 0;
    }
    if(setjmp(paser_status.buf)){
        return 1;
    }
    paser_status.statement_base = global_inter->global_code;
    safe_get_token(&paser_status, global_token_node);
    command_list(&paser_status, global_token_node);
    
    free_list(paser_status.global_paser);  // 释放解释器
    fclose(paser_status.file_p);
    return 0;
}
