#include<stdio.h>
#include"gwarf_interpreter/interpreter.c"


int main(){
    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    var_list *the_var = make_var_base(global_inter->global_var);
    statement_base = make_statement_base(global_inter->global_code);
    GWARF_result father;

    login_official(the_var, official_func);  // 注册官方函数

    class_object *tmp_gobject = gobject_login_official(the_var, gobject_official_func, NULL);  // 注册goobject

    int_login_official(the_var, int_official_func, tmp_gobject->the_var);  // 注册int
    double_login_official(the_var, double_official_func, tmp_gobject->the_var);  // 注册double
    str_login_official(the_var, str_official_func, tmp_gobject->the_var);  // 注册str
    bool_login_official(the_var, bool_official_func, tmp_gobject->the_var);  // 注册bool

    parser("/home/songzihuan/test.gwf");
    printf("----start run----\n");
    traverse_global(global_inter->global_code, the_var);
    printf("code end...\n");
    return 0;
}