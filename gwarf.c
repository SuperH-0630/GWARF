#include<stdio.h>
#include"gwarf_interpreter/interpreter.c"


int main(){
    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    parser();
    var_list *the_var = make_var_base(global_inter->global_var);
    printf("----start run----\n");
    traverse(global_inter->global_code, the_var,false);
    printf("code end...\n");
    return 0;
}