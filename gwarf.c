#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paser/y.tab.c"
#include "inter/branch.c"
#include "inter/cfunc.c"
#include "inter/parameter.c"
#include "inter/statement.c"
#include "inter/var.c"

#include "inter/interpreter.c"


int main(){
    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    var_list *the_var = make_var_base(global_inter->global_var);
    statement_base = make_statement_base(global_inter->global_code);
    GWARF_result father;

    login_official(the_var, official_func);  // 注册官方函数

    class_object *tmp_object = object_login_official(the_var, object_official_func);  // 注册oobject
    class_object *tmp_gobject = gobject_login_official(the_var, gobject_official_func, tmp_object->the_var);  // 注册goobject

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