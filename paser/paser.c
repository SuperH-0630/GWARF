#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"../inter/interpreter.h"
#include "paser.h"
#include "lexical.c"
#include "tokenstream.c"
#include "syntax.c"


void do_exit();
void setup();

int parser(char *file_address){
    p_status paser_status = {.is_parameter = false, .is_func=false, .is_list=false, .is_dict=false, .is_left=false, .is_peq=false, .is_for=false};
    paser_status.global_paser = login_paser();  // 注册解释器[往global_paser写入数据]
    setup(file_address);
    safe_get_token(&paser_status, global_token_node);
    command_list(&paser_status, global_token_node);
    do_exit();
    free_list(paser_status.global_paser);  // 释放解释器
    return 0;
}

void setup(char *file){
    file_p = fopen(file, "r");  // 打开文件
    debug = fopen("./debug.log", "w");  // 设置debug的位置
    status_log = fopen("./status.log", "w");  // 设置debug的位置
    token_log = fopen("./token.log", "w");  // 设置debug的位置
    token_info = fopen("./tokenINFO.log", "w");  // 设置debug的位置
    global_token_node = make_token_node();
}

void do_exit(void){
    fprintf(debug, "[info][paser]  stop run\n");
    fclose(file_p);
    fclose(debug);
    fclose(status_log);
}
