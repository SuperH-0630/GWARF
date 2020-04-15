#include<stdio.h>
#include"gwarf_interpreter/interpreter.c"


int main(){
    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    var_list *the_var = make_var_base(global_inter->global_var);
    statement_base = make_statement_base(global_inter->global_code);
    login_official(the_var, official_func);  // 注册官方函数
    parser("/home/songzihuan/test.gwf");
    printf("----start run----\n");
    traverse_global(global_inter->global_code, the_var);
    printf("code end...\n");
    return 0;
}