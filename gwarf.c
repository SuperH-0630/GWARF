#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem/mem.c"
#include "paser/paser.c"
#include "inter/branch.c"
#include "inter/cfunc.c"
#include "inter/parameter.c"
#include "inter/statement.c"
#include "inter/var.c"

#include "inter/interpreter.c"

void do_exit(void);
void setup();

void setup(){
    debug = fopen("./debug.log", "w");  // 设置debug的位置
    status_log = fopen("./status.log", "w");  // 设置debug的位置
    token_log = fopen("./token.log", "w");  // 设置debug的位置
    token_info = fopen("./tokenINFO.log", "w");  // 设置debug的位置
}

void do_exit(void){
    fclose(debug);
    fclose(status_log);
    fclose(token_log);
    fclose(token_info);
}

int main(){
    atexit(*do_exit);
    setup();
    inter *global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    var_list *the_var = make_var_base(global_inter->global_var);
    the_var->tag = run_class;
    
    login(the_var, global_inter);

    parser("/home/songzihuan/test.gwf", global_inter);
    printf("----start run----\n");
    traverse_global(global_inter->global_code, the_var, global_inter);
    printf("code end...\n");
    return 0;
}

void login(var_list *the_var, inter *global_inter){
    login_official(the_var, official_func, global_inter);  // 注册内置函数

    class_object *tmp_object = object_login_official(the_var, object_official_func, global_inter);  // 注册oobject
    class_object *tmp_gobject = gobject_login_official(the_var, gobject_official_func, tmp_object->the_var, global_inter);  // 注册goobject

    int_login_official(the_var, int_official_func, tmp_gobject->the_var, global_inter);  // 注册int
    double_login_official(the_var, double_official_func, tmp_gobject->the_var, global_inter);  // 注册double
    str_login_official(the_var, str_official_func, tmp_gobject->the_var, global_inter);  // 注册str
    bool_login_official(the_var, bool_official_func, tmp_gobject->the_var, global_inter);  // 注册bool
    
    class_object *tmp_tuple = tuple_login_official(the_var, tuple_official_func, tmp_gobject->the_var, global_inter);
    list_login_official(the_var, list_official_func, tmp_tuple->the_var, global_inter);  // 注册list
    dict_login_official(the_var, dict_official_func, tmp_tuple->the_var, global_inter);  // 注册dict

    // 注册错误类型
    class_object *tmp_BaseException = BaseException_login_official(the_var, BaseException_official_func, tmp_object->the_var, global_inter);
    class_object *tmp_Exception = Exception_login_official(the_var, tmp_BaseException->the_var, global_inter);
    NameException_login_official(the_var, tmp_Exception->the_var, global_inter);
    IterException_login_official(the_var, tmp_Exception->the_var, global_inter);
    AssertException_login_official(the_var, tmp_Exception->the_var, global_inter);
    AssignmentException_login_official(the_var, tmp_Exception->the_var, global_inter);
    IndexException_login_official(the_var, tmp_Exception->the_var, global_inter);
    KeyException_login_official(the_var, tmp_Exception->the_var, global_inter);
    ImportException_login_official(the_var, tmp_Exception->the_var, global_inter);
    IncludeException_login_official(the_var, tmp_Exception->the_var, global_inter);
    DivZeroException_login_official(the_var, tmp_Exception->the_var, global_inter);
    ValueException_login_official(the_var, tmp_Exception->the_var, global_inter);
    TypeException_login_official(the_var, tmp_Exception->the_var, global_inter);
    ArgsException_login_official(the_var, tmp_Exception->the_var, global_inter);
    SystemctlException_login_official(the_var, tmp_Exception->the_var, global_inter);
    VarException_login_official(the_var, tmp_Exception->the_var, global_inter);
}

// 合并编译：cd "/home/songzihuan/文档/CProject/gwarf/" && gcc gwarf.c -lm -o gwarf && "/home/songzihuan/文档/CProject/gwarf/"gwarf