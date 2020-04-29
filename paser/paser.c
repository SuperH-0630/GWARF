#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"../inter/interpreter.h"
#include "paser.h"
#include "lexical.c"
#include "tokenstream.c"
#include "syntax.c"

int paser_status = 1;

void do_exit(void);
void setup();

int parser(char *file_address){
    atexit(*do_exit);
    setup(file_address);
    safe_get_token(&paser_status, global_token_node);
    command_list(&paser_status, global_token_node);
    return 0;
}

void setup(char *file){
    global_paser = login_paser();  // 注册解释器[往global_paser写入数据]
    file_p = fopen(file, "r");  // 打开文件
    debug = fopen("./debug.log", "w");  // 设置debug的位置
    status_log = fopen("./status.log", "w");  // 设置debug的位置
    token_log = fopen("./token.log", "w");  // 设置debug的位置
    global_token_node = make_token_node();
}

void do_exit(void){
    fprintf(debug, "[info][paser]  stop run\n");
    fclose(file_p);
    fclose(debug);
    fclose(status_log);

    free_list(global_paser);  // 释放解释器
}
