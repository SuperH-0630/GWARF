#include<stdio.h>

#include "interpreter.h"

int len_int(int num){
    int count = 1;  // 默认得有1位
    while(1){
        num = num / 10;
        if(num <= 0){
            break;
        }
        count += 1;
    }
    return count;
}

int len_only_double(double num){
    int count = 1;  // 默认得有1位
    while(1){
        num = num * 10;
        if(num - (int)num <= 0){
            break;
        }
        count += 1;
    }
    return count;
}

int len_double(double num){
    int count = 1, i = (int)num;
    count += len_int(i);
    count += len_only_double(num);
    return count;
}

int len_intx(unsigned int num){  // 16进制
    int count = 1;  // 默认得有1位
    while(1){
        num = num / 16;
        if(num <= 0){
            break;
        }
        count += 1;
    }
    return count;
}

GWARF_result to_object(GWARF_result value, inter *global_inter){  // 把GWARF_value封装成objct
    error_space(value, return_self, value);
    if((value.value.type == CLASS_value) || (value.value.type == OBJECT_value) || (value.value.type == FUNC_value) || (value.value.type == NULL_value)){  // 可以直接返回
        return_self: return value;
    }
    GWARF_result func_result = GWARF_result_reset;
    var_list *the_var = make_var_base(global_inter->global_var);
    var *tmp;
    if(value.value.type == NUMBER_value){
        tmp = find_var(the_var, 0, "double", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.value.type == INT_value){
        tmp = find_var(the_var, 0, "int", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.value.type == BOOL_value){
        tmp = find_var(the_var, 0, "bool", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.value.type == STRING_value){
        tmp = find_var(the_var, 0, "str", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.value.type == LIST_value){
        tmp = find_var(the_var, 0, "list", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.value.type == DICT_value){
        tmp = find_var(the_var, 0, "dict", NULL);
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else{
        free(the_var);
        return to_error("SystemctlError", "SystemctlException", global_inter);
    }
    GWARF_result return_tmp = call_back_core(func_result, the_var, pack_value_parameter(value.value), global_inter);
    value.value = return_tmp.value;
    free(the_var);
    return value;
}


GWARF_result to_tuple(GWARF_value value, inter *global_inter){  // 把GWARF_value封装成objct
    GWARF_result func_result = GWARF_result_reset;
    var_list *the_var = make_var_base(global_inter->global_var);
    var *tmp;
    tmp = find_var(the_var, 0, "tuple", NULL);
    if(tmp != NULL){
        func_result.value = tmp->value;
    }
    else{  // 应该报错 (TypeError)
        free(the_var);
        return to_error("[Systemctl]Can't Not Found Class : 'tuple'", "SystemctlException", global_inter);
    }
    GWARF_result return_tmp = call_back_core(func_result, the_var, pack_value_parameter(value), global_inter);
    free(the_var);
    return return_tmp;
}


GWARF_result get_object(parameter *tmp_s, char *name, var_list *the_var, inter *global_inter){  // 生成一个object
    GWARF_result func_result = GWARF_result_reset;
    func_result.u = statement_end;
    func_result.value.type = NULL_value;
    func_result.value.value.int_value = 0;
    var *tmp = find_var(the_var, 0, name, NULL);
    if(tmp != NULL){
        func_result.value = tmp->value;
    }
    else{
        return to_error("[Systemctl]Object Name Not Found", "SystemctlException", global_inter);
    }
    return call_back_core(func_result, the_var, tmp_s, global_inter);
}


GWARF_result to_error(char *error_info, char *error_type, inter *global_inter){  // 把GWARF_value封装成error
    fprintf(inter_info, "%s(%s)\n", error_type, error_info);
    GWARF_result func_result, return_result = GWARF_result_reset;
    GWARF_value tmp_value = GWARF_value_reset;
    var_list *the_var = make_var_base(global_inter->global_var);

    tmp_value.type = STRING_value;
    tmp_value.value.string = error_info;

    var *tmp = find_var(the_var, 0, error_type, NULL);

    if(tmp != NULL){
        func_result.value = tmp->value;
        return_result = call_back_core(func_result, the_var, pack_value_parameter(tmp_value), global_inter);
    }
    else{
        fprintf(inter_info, "NOT FOUND :: %s for %s", error_type, error_info);
        return_result.value.type = NULL_value;
        return_result.value.value.int_value = 0;
    }
    free(the_var);
    return_result.u = error;
    return_result.error_info = error_info;
    return return_result;
}


void login_official_func(int type, int is_class, var_list *the_var, char *name, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *)){  // 注册单个official func
    GWARF_result func_value = GWARF_result_reset;
    func *func_tmp = malloc(sizeof(func));

    func_tmp->done = NULL;
    func_tmp->parameter_list = NULL;
    func_tmp->the_var = copy_var_list(the_var);
    func_tmp->type = official;
    func_tmp->official_func = type;
    func_tmp->is_class = is_class;
    func_tmp->is_lambda = false;
    func_tmp->paser = paser;
    func_tmp->self = make_var_base(make_hash_var());
    func_tmp->self->tag = run_object;

    func_value.value.type = FUNC_value;
    func_value.value.value.func_value = func_tmp;
    assignment_func(name, func_value, the_var, 0, auto_public);  // 注册函数到指定的位置
}

void login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), inter *global_inter){
    int a[][2] = {{printf_func,0}};
    char *name[] = {"print"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], the_var, name[i], paser);
    }
}


// global 全局内置函数解析器
GWARF_result official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){
    GWARF_result return_value = GWARF_result_reset;
    return_value.u = return_def;
    return_value.return_times = 0;
    switch (the_func->official_func)
    {
    case printf_func:{  // printf something
        if(tmp_s == NULL){  // 没有东西要打印
            goto return_result;
        }
        char *str = malloc(0);
        while(1){
            GWARF_result tmp = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp, return_result, return_value);
            tmp = to_str(tmp.value, out_var, global_inter);
            error_space(tmp, return_result, return_value);
            str = realloc(str, strlen(str) + strlen(tmp.value.value.string) + 2);
            strcat(str, tmp.value.value.string);
            if (tmp_s->next == NULL){  // the last
                break;
            }
            tmp_s = tmp_s->next;
        }
        printf("%s\n", str);  // 换行
        return_value.u = statement_end;
        break;
    }
    default:
        break;
    }
    return_result: return return_value;
}

class_object *object_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), inter *global_inter){  // 内置对象继承的类
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, NULL);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("object", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    


    // 注册函数
    int a[][2] = {{3,1}, {__assignment__func, 1}};
    char *name[] = {"__value__", "__assignment__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}
#define NotFatherError \
else{ \
    to_error("Don't get base var", "ValueException", global_inter); \
}

GWARF_result object_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __value__func:{  // 若想实现运算必须要有这个方法
            size_t size;
            unsigned long int ad;
            if(father.father->type == CLASS_value){  // is class so that can use "."
                ad = (unsigned long int)father.father->value.class_value;
            }
            else if(father.father->type == OBJECT_value){
                ad = (unsigned long int)father.father->value.object_value;
            }
            size = (size_t)(9 + len_intx(ad));
            return_value.value.type = STRING_value;
            return_value.value.value.string = (char *)malloc(size);
            snprintf(return_value.value.value.string, size, "<-%u->", ad);
            break;
        }
        case __assignment__func:
            return_value.value = *(father.father);  // 返回self
            break;
    }
    return_result: return return_value;
}

class_object *make_object(var_list *the_var, var_list *father_var_list){
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_hash_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // int、double、str等内置类需要继承gobject类
    }

    // class_tmp->out_var = copy_var_list(the_var);  // make class var list with out var
    return class_tmp;
}

class_object *BaseException_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("BaseException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result BaseException_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;

    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            tmp = to_str(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            error_space(tmp, return_result, return_value);
            assignment_func("ErrorInfo", tmp, login_var, 0, auto_public);  // 不会权限不足
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

class_object *Exception_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("Exception", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *AssertException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("AssertException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *NameException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("NameException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *IterException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("IterException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *AssignmentException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("AssignmentException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *IndexException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("IndexException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *KeyException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("KeyException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *ImportException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("ImportException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *IncludeException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("IncludeException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *DivZeroException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("DivZeroException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *ValueException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("ValueException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *TypeException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("TypeException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *ArgsException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("ArgsException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *SystemctlException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("SystemctlException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *VarException_login_official(var_list *the_var, var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("VarException", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    
    return class_tmp;
}

class_object *gobject_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){  // 内置对象继承的类
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);
    
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("gobject", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}, {__value__func,1}, {__add__func,1}, {__sub__func,1}, {__mul__func,1},
                  {__div__func,1}, {__eq__func,1}, {__more__func,1}, {__less__func,1}, {__eqmore__func,1},
                  {__eqless__func,1}, {__noteq__func,1}, {__pow__func,1}, {__log__func,1}, {__sqrt__func,1},
                  {__negative__func,1}, {__value__func,1}, {__subr__func,1}, {__divr__func,1}, {__powr__func,1}, 
                  {__logr__func,1}, {__sqrtr__func,1}, {__idiv__func,1}, {__idivr__func,1}, {__mod__func,1},
                  {__modr__func,1},{__bitand__func,1}, {__bitor__func,1}, {__bitnotor__func,1}, {__bitright__func,1},
                  {__bitrightr__func,1}, {__bitleft__func,1}, {__bitleftr__func,1}, {__bitnot__func,1}};
    
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__",
                    "__div__","__eq__", "__more__", "__less__", "__eqmore__",
                    "__eqless__","__noteq__", "__pow__", "__log__","__sqrt__",
                    "__negative__","__bool__","__subr__","__divr__", "__powr__",
                    "__logr__","__sqrtr__", "__idiv__","__idivr__", "__mod__",
                    "__modr__","__bitand__", "__bitor__", "__bitnotor__","__bitright__",
                    "__bitrightr__","__bitleft__", "__bitleftr__","__bitnot__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result gobject_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp = GWARF_result_reset;
            tmp.value.type = INT_value;
            tmp.value.value.int_value = 0;
            assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value", NULL);  // gobject类的value存储在self.value中
            if(tmp != NULL){
                return_value.value = tmp->value;  // 取得用于计算的数值
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        case __add__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = add_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __sub__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sub_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __subr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sub_func(reight_tmp, left_tmp, out_var, global_inter);  // right和left反过来
            break;
        }
        case __mul__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            error_space(reight_tmp, return_result, return_value);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = mul_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __div__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = div_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __divr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = div_func(reight_tmp, left_tmp, out_var, global_inter);  // left和right反过来
            break;
        }
        case __eq__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);

            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 0, global_inter);
            break;
        }
        case __more__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 1, global_inter);
            break;
        }
        case __less__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 2, global_inter);
            break;
        }
        case __eqmore__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 3, global_inter);
            break;
        }
        case __eqless__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 4, global_inter);
            break;
        }
        case __noteq__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 5, global_inter);
            break;
        }
        case __pow__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = pow_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __log__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = log_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __sqrt__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sqrt_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __powr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = pow_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __logr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = log_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __sqrtr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sqrt_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __negative__func:{
            GWARF_result left_tmp = GWARF_result_reset;
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = negative_func(left_tmp, out_var, global_inter);
            break;
        }
        case __idiv__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = int_div_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __idivr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = int_div_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __mod__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = mod_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __modr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = mod_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }


        case __bitand__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_and_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __bitor__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_or_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __bitnotor__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_notor_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __bitleft__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_left_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __bitleftr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_left_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __bitright__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_right_func(left_tmp, reight_tmp, out_var, global_inter);
            break;
        }
        case __bitrightr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var, global_inter);
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_right_func(reight_tmp, left_tmp, out_var, global_inter);
            break;
        }
        case __bitnot__func:{
            GWARF_result left_tmp = GWARF_result_reset;
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = bit_not_func(left_tmp, out_var, global_inter);
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

class_object *int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("int", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}, {__assignment__func, 1}};
    char *name[] = {"__init__", "__assignment__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            GWARF_value base_the_var = tmp.value;  // 只有一个参数
            tmp = to_int(tmp_result.value,out_var,global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            error_space(tmp, return_result, return_value);
            assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        case __assignment__func:{
            // 不使用to_object，要保证赋值前后类型一致[to_object会受class重写的影响]
            if(father.father->type == OBJECT_value){
                the_object *object_tmp = malloc(sizeof(the_object));  // 生成object的空间
                object_tmp->cls = father.father->value.object_value->cls;
                object_tmp->the_var = append_by_var_list(make_var_base(make_hash_var()), object_tmp->cls);  // 生成实例

                // 执行__init__
                GWARF_result self_value = GWARF_result_reset;
                var *tmp = find_var(login_var, 0, "value", NULL);
                if(tmp != NULL){
                    self_value = to_int(tmp->value, out_var, global_inter);
                    error_space(self_value, return_result, return_value);
                }
                else{
                    self_value.value.type = INT_value;
                    self_value.value.value.int_value = 0;
                }
                assignment_func("value", self_value, object_tmp->the_var, 0, auto_public);  // 注册到新的object

                return_value.value.type = OBJECT_value;
                return_value.value.value.object_value = object_tmp;
            }
            else{
                return_value.value = *(father.father);  // 返回原值
            }
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to int[底层实现]
GWARF_result to_int(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = INT_value;

    if((value.type == INT_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_int(get__value__(&value, the_var, global_inter).value, the_var, global_inter);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            return_number.value.value.int_value = value.value.bool_value;
        }
        else if(value.type == NUMBER_value){
            return_number.value.value.int_value = (int)value.value.double_value;
        }
        else if(value.type == STRING_value){
            return_number.value.value.int_value = atoi(value.value.string);
        }
        else{  // 还有list等
            return_number.value.value.int_value = 0;
        }
    }
    return return_number;
}


class_object *double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("double", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}, {__assignment__func, 1}};
    char *name[] = {"__init__", "__assignment__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            tmp = to_double(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            error_space(tmp, return_result, return_value);
            assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        case __assignment__func:{
            // 不使用to_object，要保证赋值前后类型一致[to_object会受class重写的影响]
            if(father.father->type == OBJECT_value){
                the_object *object_tmp = malloc(sizeof(the_object));  // 生成object的空间
                object_tmp->cls = father.father->value.object_value->cls;
                object_tmp->the_var = append_by_var_list(make_var_base(make_hash_var()), object_tmp->cls);  // 生成实例

                // 执行__init__
                GWARF_result self_value = GWARF_result_reset;
                var *tmp = find_var(login_var, 0, "value", NULL);
                if(tmp != NULL){
                    self_value = to_double(tmp->value, out_var, global_inter);
                    error_space(self_value, return_result, return_value);
                }
                else{
                    self_value.value.type = NUMBER_value;
                    self_value.value.value.double_value = 0;
                }
                assignment_func("value", self_value, object_tmp->the_var, 0, auto_public);  // 注册到新的object

                return_value.value.type = OBJECT_value;
                return_value.value.value.object_value = object_tmp;
            }
            else{
                return_value.value = *(father.father);  // 返回原值
            }
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to double[底层实现]
GWARF_result to_double(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = NUMBER_value;
    if((value.type == NUMBER_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_double(get__value__(&value, the_var, global_inter).value, the_var, global_inter);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            return_number.value.value.double_value = (double)value.value.bool_value;
        }
        else if(value.type == INT_value || value.type == NULL_value){
            return_number.value.value.double_value = (double)value.value.int_value;
        }
        else if(value.type == STRING_value){
            return_number.value.value.double_value = (double)atof(value.value.string);
        }
        else{
            return_number = to_error("Get a Don't Support Type", "TypeException", global_inter);
        }
    }
    return return_number;
}

class_object *str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("str", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            tmp = to_str(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            error_space(tmp, return_result, return_value);
            assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to str[底层实现]
GWARF_result to_str(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = STRING_value;

    if((value.type == STRING_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_str(get__value__(&value, the_var, global_inter).value, the_var, global_inter);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            if(value.value.bool_value){
                return_number.value.value.string = (char *)malloc(6);
                strcpy(return_number.value.value.string, "true");
            }
            else{
                return_number.value.value.string = (char *)malloc(7);
                strcpy(return_number.value.value.string, "false");
            }
        }
        else if(value.type == INT_value){
            size_t size = (size_t)(2 + len_int(value.value.int_value));
            return_number.value.value.string = (char *)malloc(size);
            snprintf(return_number.value.value.string, size, "%d", value.value.int_value);
        }
        else if(value.type == NUMBER_value){
            size_t size = (size_t)(2 + len_double(value.value.double_value));
            return_number.value.value.string = (char *)malloc(size);
            snprintf(return_number.value.value.string, size, "%f", value.value.double_value);
        }
        else if(value.type == NULL_value){
            return_number.value.value.string = (char *)malloc(10);
            strcpy(return_number.value.value.string, "<-None->");
        }
        else if(value.type == FUNC_value){
            size_t size = (size_t)(20 + len_intx((unsigned long int)value.value.func_value));  // 转换为无符号整形数字
            return_number.value.value.string = (char *)malloc(size);
            snprintf(return_number.value.value.string, size, "<-function on %u->", value.value.func_value);
        }
        else if(value.type == CLASS_value){
            size_t size = (size_t)(16 + len_intx((unsigned long int)value.value.class_value));
            return_number.value.value.string = (char *)malloc(size);
            snprintf(return_number.value.value.string, size, "<-class on %u->", value.value.class_value);
        }
        else{  // 还有LIST等，其余报错
            return_number = to_error("Get a Don't Support Type", "TypeException", global_inter);
        }
    }
    return return_number;
}

// dict key 带有类型的前缀
GWARF_result to_str_dict(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = STRING_value;

    if((value.type == STRING_value)){
        size_t size = (size_t)(5 + strlen(value.value.string));
        return_number.value.value.string = calloc(sizeof(char), size);
        snprintf(return_number.value.value.string, size, "str_%s", value.value.string);
    }
    else if(value.type == OBJECT_value){  // 调用__value__方法
        GWARF_result tmp_str = to_str_dict(get__value__(&value, the_var, global_inter).value, the_var, global_inter);
        if(is_error(&tmp_str) || is_space(&tmp_str)){  // 返回error
            return tmp_str;
        }
        size_t size = strlen(tmp_str.value.value.string) + 2;
        return_number.value.value.string = calloc(sizeof(char), size);
        snprintf(return_number.value.value.string, size, "%s", tmp_str.value.value.string);
    }
    else{
        if(value.type == BOOL_value){
            if(value.value.bool_value){
                return_number.value.value.string = calloc(sizeof(char), 11);
                strcpy(return_number.value.value.string,  "bool_true");
            }
            else{
                return_number.value.value.string = calloc(sizeof(char), 12);
                strcpy(return_number.value.value.string,  "bool_false");
            }
        }
        else if(value.type == INT_value){
            size_t size = (size_t)(6 + len_int(value.value.int_value));
            return_number.value.value.string = calloc(sizeof(char), size);
            snprintf(return_number.value.value.string, size, "int_%d", value.value.int_value);
        }
        else if(value.type == NUMBER_value){
            size_t size = (size_t)(10 + len_double(value.value.double_value));
            return_number.value.value.string = calloc(sizeof(char), size);
            snprintf(return_number.value.value.string, size, "double_%f", value.value.double_value);
        }
        else if(value.type == FUNC_value){
            size_t size = (size_t)(29 + len_intx((unsigned long int)value.value.func_value));  // 转换为无符号整形数字
            return_number.value.value.string = calloc(sizeof(char), size);
            snprintf(return_number.value.value.string, size, "str_<-function on %u->", value.value.func_value);
        }
        else if(value.type == CLASS_value){  // class_value和func_value应该调用__name__
            size_t size = (size_t)(22 + len_intx((unsigned long int)value.value.class_value));
            return_number.value.value.string = calloc(sizeof(char), size);
            snprintf(return_number.value.value.string, size, "str_<-class on %u->", value.value.class_value);
        }
        else if(value.type == NULL_value){
            return_number.value.value.string = calloc(sizeof(char), 13);
            strcpy(return_number.value.value.string,  "none_<none>");
        }
        else{
            return_number = to_error("Get a Don't Support Type", "TypeException", global_inter);
        }
    }
    return_value: 
    return return_number;
}

bool start_with(char *str, char *start){
   int a = strlen(str),b = strlen(start);
   if(a <= b){ // 长度相等也不用检查
      return false;
   }
   else{
      for(int i = 0;i < b; i += 1){
         if(str[i] != start[i]){
            return false;
         }
      }
   }
   return true;
}

char *del_start(char *str, char *start){
   int a = strlen(str),b = strlen(start);
   if(a <= b){ // 长度相等也不用检查
      return NULL;
   }
   else{
      char *new = (char *)calloc(sizeof(char) ,a - b + 1);  // 预留一个空位
      strncpy(new, str+b, (a - b));
      return new;
   }
}

GWARF_value key_to_str(char *key){  // 复原key
    GWARF_value return_value = GWARF_value_reset;
    if(start_with(key, "str_")){
        return_value.type = STRING_value;
        return_value.value.string = del_start(key, "str_");
    }
    else if(start_with(key, "int_")){
        return_value.type = INT_value;
        return_value.value.int_value = atoi(del_start(key, "int_"));
    }
    else if(start_with(key, "double_")){
        return_value.type = NUMBER_value;
        return_value.value.double_value = atof(del_start(key, "double_"));
    }
    else if(!strcmp(key, "bool_true")){
        return_value.type = BOOL_value;
        return_value.value.bool_value = true;
    }
    else if(!strcmp(key, "bool_false")){
        return_value.type = BOOL_value;
        return_value.value.bool_value = false;
    }
    else{
        return_value.type = NULL_value;
        return_value.value.int_value = 0;
    }
    return return_value;
}

class_object *bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("bool", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1}, {__assignment__func, 1}};
    char *name[] = {"__init__", "__assignment__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
            error_space(tmp_result, return_result, return_value);
            tmp = to_bool_(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            error_space(tmp, return_result, return_value);
            assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        case __assignment__func:{
            // 不使用to_object，要保证赋值前后类型一致[to_object会受class重写的影响]
            if(father.father->type == OBJECT_value){
                the_object *object_tmp = malloc(sizeof(the_object));  // 生成object的空间
                object_tmp->cls = father.father->value.object_value->cls;
                object_tmp->the_var = append_by_var_list(make_var_base(make_hash_var()), object_tmp->cls);  // 生成实例

                // 执行__init__
                GWARF_result self_value = GWARF_result_reset;
                var *tmp = find_var(login_var, 0, "value", NULL);
                if(tmp != NULL){
                    self_value= to_bool_(tmp->value, out_var, global_inter);
                    error_space(self_value, return_result, return_value);
                }
                else{
                    self_value.value.type = BOOL_value;
                    self_value.value.value.double_value = false;
                }
                assignment_func("value", self_value, object_tmp->the_var, 0, auto_public);  // 注册到新的object

                return_value.value.type = OBJECT_value;
                return_value.value.value.object_value = object_tmp;
            }
            else{
                return_value.value = *(father.father);  // 返回原值
            }
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to bool[底层实现]
GWARF_result to_bool_(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = BOOL_value;
    
    if((value.type == BOOL_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法, 如果是class则调用__clsbool__，func则查看参数__bool__
        GWARF_result tmp_result = get__bool__(&value, the_var, global_inter);
        if(is_error(&tmp_result) || is_space(&tmp_result)){
            return tmp_result;
        }
        return_number = to_bool_(tmp_result.value, the_var, global_inter);
    }
    else{
        return_number.value.value.bool_value = to_bool(value, global_inter);  // 转换成bool
    }
    return return_number;
}

class_object *tuple_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("tuple", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1},{__len__func,1},{__down__func,1},{__slice__func,1},{__iter__func,1},{__next__func,1},{__in__func, 1}};
    char *name[] = {"__init__", "__len__", "__down__", "__slice__", "__iter__", "__next__","__in__"};  //  __len__是获取长度，__down__是获取下值，__slice__是切片

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result tuple_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            if(tmp_s == NULL){  // 生成空列表
                GWARF_result tmp_result = GWARF_result_reset;
                GWARF_value list_tmp = GWARF_value_reset;
                list_tmp.type = LIST_value;
                list_tmp.value.list_value = malloc(sizeof(the_list));
                list_tmp.value.list_value->index = 0;
                list_tmp.value.list_value->list_value = malloc((size_t)0);
                tmp_result.value = list_tmp;
                assignment_func("value", tmp_result, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            else if(tmp_s->next == NULL){  // 只有一个参数
                GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                tmp = to_list(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
                error_space(tmp, return_result, return_value);
                assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            else{
                GWARF_result tmp_result = GWARF_result_reset;
                tmp_result = parameter_to_list(tmp_s, out_var, global_inter);
                error_space(tmp_result, return_result,return_value);
                assignment_func("value", tmp_result, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            GWARF_result iter_value = GWARF_result_reset;
            iter_value.value.type = INT_value;
            iter_value.value.value.int_value = 0;
            assignment_func("iter_value", iter_value, login_var, 0, auto_public);  // 注册到self
            break;
        }
        case __len__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            return_value.value.type = INT_value;
            return_value.value.value.int_value = tmp->value.value.list_value->index;
            break;
        }
        case __iter__func:{  // return self
            GWARF_result iter_value = GWARF_result_reset;
            iter_value.value.type = INT_value;
            iter_value.value.value.int_value = 0;
            assignment_func("iter_value", iter_value, login_var, 0, auto_public);  // 注册到self

            return_value.value = *(father.father);
            break;
        }
        case __next__func:{  // return index
            var *tmp = find_var(login_var, 0, "iter_value", NULL);
            int iter_index, len;
            if(tmp == NULL){
                iter_index = 0;
            }
            else{
                GWARF_result int_tmp = to_int(tmp->value, out_var, global_inter);
                error_space(int_tmp, return_result, return_value);
                iter_index = int_tmp.value.value.int_value;
            }

            tmp = find_var(login_var, 0, "value", NULL);
            len = tmp->value.value.list_value->index;
            fprintf(inter_info, "len = %d, iter_index = %d\n", len, iter_index);
            if(iter_index >= len){  // 已经超出
                return_value = to_error("Max Iter", "IterException", global_inter);
            }
            else{
                return_value.value = tmp->value.value.list_value->list_value[iter_index];
                GWARF_result iter_value = GWARF_result_reset;
                iter_value.value.type = INT_value;
                iter_value.value.value.int_value = iter_index + 1;
                assignment_func("iter_value", iter_value, login_var, 0, auto_public);  // 注册到self
            }

            break;
        }
        case __down__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            int len = tmp->value.value.list_value->index;
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
                get_value = get__value__(&base_the_var, the_var, global_inter);
                error_space(get_value, return_result, return_value);
                get_value = to_int(get_value.value, out_var, global_inter);
                error_space(get_value, return_result, return_value);
                if(len - 1 < get_value.value.value.int_value){
                    return_value = to_error("Index To Max", "IndexException", global_inter);
                    goto return_result;
                }
                else if(get_value.value.value.int_value < 0){
                    return_value = to_error("Index To Min", "IndexException", global_inter);
                    goto return_result;
                }
                return_value.value = tmp->value.value.list_value->list_value[get_value.value.value.int_value];
            }
            else{
                return_value = to_error("Don't get List Value", "ValueException", global_inter);
                goto return_result;
            }
            break;
        }
        case __in__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            int len = tmp->value.value.list_value->index;
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                get_value = get__value__(&(tmp_result.value), the_var, global_inter);
                error_space(get_value, return_result, return_value);

                GWARF_result self = GWARF_result_reset, tmp_eq = GWARF_result_reset;
                for(int i = 0;i < len;i++){
                    self.value = tmp->value.value.list_value->list_value[i];
                    tmp_eq = equal_func(get_value, self, out_var, 0, global_inter);
                    error_space(tmp_eq, return_result, return_value);
                    if(tmp_eq.value.value.bool_value){  // 相等
                        return_value.value.type = BOOL_value;
                        return_value.value.value.bool_value = true;
                        goto return_result;  // return true
                    }
                }

                return_value.value.type = BOOL_value;
                return_value.value.value.bool_value = false;
            }
            else{
                return_value = to_error("Don't get List Value", "ValueException", global_inter);
                goto return_result;
            }
            break;
        }
        case __slice__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            int len = tmp->value.value.list_value->index;
            int start, end;
            if(tmp != NULL){
                GWARF_result start_result = traverse(tmp_s->u.value, out_var, false, global_inter), end_result, tmp_result;
                error_space(start_result, return_result, return_value);
                
                tmp_result = get__value__(&(start_result.value), the_var, global_inter);
                error_space(tmp_result, return_result, return_value);
                
                tmp_result = to_int(tmp_result.value, out_var, global_inter);
                error_space(tmp_result, return_result, return_value);
                
                start = tmp_result.value.value.int_value;
                tmp_s = tmp_s->next;
                if(tmp_s != NULL){
                    end_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                    error_space(end_result, return_result, return_value);
                    
                    GWARF_result tmp = get__value__(&(end_result.value), the_var, global_inter);
                    error_space(tmp, return_result, return_value);
                    
                    if(tmp.value.type != NULL_value){
                        tmp = to_int(tmp.value, the_var, global_inter);
                        error_space(tmp, return_result, return_value);
                        end = tmp.value.value.int_value;
                    }
                    else{
                        goto not_last;
                    }
                }
                else{
                    not_last:
                    end = len;
                }
                if(len < start || len < end || end < start){
                    return_value = to_error("Index To Max", "IndexException", global_inter);
                    goto return_result;
                }
                else if(end < 0 || start < 0){
                    return_value = to_error("Index To Min", "IndexException", global_inter);
                    goto return_result;
                }
                return_value.value.type = LIST_value;
                return_value.value.value.list_value = malloc(sizeof(the_list));  // 申请list的空间
                return_value.value.value.list_value->list_value = malloc((size_t)((end - start) * sizeof(GWARF_value)));
                memcpy(return_value.value.value.list_value->list_value, (tmp->value.value.list_value->list_value + start), (size_t)((end - start) * sizeof(GWARF_value)));
                return_value.value.value.list_value->index = end - start;
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        default:
            break;
    }
    return_result:
    return return_value;
}

class_object *list_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("list", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__set__func,1}};
    char *name[] = {"__set__"};  //  继承tuple

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result list_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __set__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            int len = tmp->value.value.list_value->index;
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                
                GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
                get_value = get__value__(&base_the_var, the_var, global_inter);
                error_space(get_value, return_result, return_value);
                
                get_value = to_int(get_value.value, out_var, global_inter);
                error_space(get_value, return_result, return_value);
                tmp_s = tmp_s->next;
                GWARF_result new_value = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(new_value, return_result, return_value);
                if(len - 1 < get_value.value.value.int_value){
                    return_value = to_error("Index To Max", "IndexException", global_inter);
                    goto return_result;
                }
                else if(get_value.value.value.int_value < 0){
                    return_value = to_error("Index To Min", "IndexException", global_inter);
                    goto return_result;
                }
                tmp->value.value.list_value->list_value[get_value.value.value.int_value] = new_value.value;
                tmp->value.value.list_value->index += 1;
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}


GWARF_result to_dict(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = DICT_value;
    if((value.type == DICT_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法
        GWARF_result tmp = get__value__(&value, the_var, global_inter);
        error_space(tmp, return_result, return_number);
        return_number = to_dict(tmp.value, the_var, global_inter);  // 递归
    }
    else{
        return to_error("Get a Don't Support Type", "TypeException", global_inter);
    }
    return_result: return return_number;
}

GWARF_result to_list(GWARF_value value, var_list *the_var, inter *global_inter){
    GWARF_result return_number = GWARF_result_reset;
    return_number.value.type = LIST_value;

    if((value.type == LIST_value)){
        return_number.value = value;
        return return_number;  // 直接返回数据
    }

    if(value.type == OBJECT_value){  // 调用__value__方法
        GWARF_result tmp_result = get__value__(&value, the_var, global_inter);
        if(is_space(&tmp_result) || is_error(&tmp_result)){
            return tmp_result;
        }
        return_number = to_list(tmp_result.value, the_var, global_inter);  // 递归
    }
    else{
        return to_error("Get a Don't Support Type", "TypeException", global_inter);
    }
    return return_number;
}

GWARF_result parameter_to_list(parameter *tmp_s, var_list *the_var, inter *global_inter){  // 把parameter转换为list
    GWARF_result return_list = GWARF_result_reset, result_tmp = GWARF_result_reset;
    return_list.value.type = LIST_value;
    return_list.value.value.list_value = malloc(sizeof(the_list));
    return_list.value.value.list_value->list_value = malloc(0);
    int index = 0;
    while(1){
        if(tmp_s == NULL){
            break;
        }
        if(tmp_s->type == put_args){  // 解包
            parameter *before = tmp_s, *after = tmp_s->next;

            GWARF_result tmp = traverse(tmp_s->u.value, the_var, false, global_inter);  // 不会和下面发生重复计算
            if(is_error(&tmp) || is_space(&tmp)){
                free(return_list.value.value.list_value->list_value);
                free(return_list.value.value.list_value);
                return tmp;
            }
            GWARF_result result_tmp = get__iter__(&(tmp.value), the_var, global_inter);
            if(is_error(&result_tmp) || is_space(&result_tmp)){
                free(return_list.value.value.list_value->list_value);
                free(return_list.value.value.list_value);
                return result_tmp;
            }
            GWARF_value iter_value = result_tmp.value;
            
            while (1){
                GWARF_result tmp_next = get__next__(&(iter_value), the_var, global_inter);
                if(is_error(&tmp_next) || is_space(&tmp_next)){  // TODO:: 检查是否为IterException
                    free(return_list.value.value.list_value->list_value);
                    free(return_list.value.value.list_value);
                    return tmp_next;  // TODO:: return 都需要实方内存
                }
                before->next = pack_value_parameter(tmp_next.value);
                before = before->next;
            }
            before->next = after;
            // 此处不需要“tmp_s = tmp_s->next;”  goto next已经包含
            goto next;
        }
        if(tmp_s->type != only_value){
            goto next;  // 跳过这一个
        }
        result_tmp = traverse(tmp_s->u.value, the_var, false, global_inter);  // 不需要取__value__
        if(is_error(&result_tmp) || is_space(&result_tmp)){  // Name Error错误
            free(return_list.value.value.list_value->list_value);
            free(return_list.value.value.list_value);
            return result_tmp;
        }
        index += 1;
        return_list.value.value.list_value->list_value = realloc(return_list.value.value.list_value->list_value, sizeof(GWARF_value) * index);  // 申请新空间
        return_list.value.value.list_value->list_value[index - 1] = result_tmp.value;  // 保存value
        next: tmp_s = tmp_s->next;  // 指向下一个
    }
    return_list.value.value.list_value->index = index;
    return return_list;
}

GWARF_result parameter_to_dict(parameter *tmp_s, var_list *the_var, inter *global_inter){  // 把parameter转换为list
    GWARF_result return_dict = GWARF_result_reset, result_tmp = GWARF_result_reset;
    return_dict.value.type = DICT_value;
    return_dict.value.value.dict_value = malloc(sizeof(the_dict));
    return_dict.value.value.dict_value->index = 0;
    return_dict.value.value.dict_value->dict_value = make_hash_var();
    return_dict.value.value.dict_value->name_list = malloc(sizeof(dict_key));
    return_dict.value.value.dict_value->name_list->key = "";
    return_dict.value.value.dict_value->name_list->next = NULL;

    int index = 0;
    var_list *tmp_var_list = make_var_base(return_dict.value.value.dict_value->dict_value);
    while(1){
        if(tmp_s == NULL){
            break;
        }
        if(tmp_s->type == put_kwargs){
            parameter *before = tmp_s, *after = tmp_s->next;
            GWARF_result tmp = traverse(tmp_s->u.value, the_var, false, global_inter);  // 不会和下面发生重复计算
            if(is_error(&tmp) || is_space(&tmp)){
                free(return_dict.value.value.dict_value->name_list);
                free(return_dict.value.value.dict_value);
                // TODO::还需要释放哈希表
                return tmp;
            }
            GWARF_result tmp_result = get__iter__(&(tmp.value), the_var, global_inter);
            if(is_error(&tmp_result) || is_space(&tmp_result)){
                free(return_dict.value.value.dict_value->name_list);
                free(return_dict.value.value.dict_value);
                // TODO::还需要释放哈希表
                return tmp_result;
            }
            GWARF_value iter_value = tmp_result.value;  // 获取迭代object，一般是返回self
            while (1){
                GWARF_result tmp_next = get__next__(&(iter_value), the_var, global_inter), tmp_next_down;// 执行__next__的返回值
                if(is_error(&tmp_next) || is_space(&tmp_next)){  // TODO:: 检查是否为IterException
                    goto next;  // goto return_value;
                }

                GWARF_result get = GWARF_result_reset;  // 不会和下面发生重复计算
                var_list *call_var = tmp.value.value.object_value->the_var;

                var *__down__tmp = find_var(call_var, 0, "__down__", NULL);
                if(__down__tmp != NULL){
                    get.value = __down__tmp->value;
                    get.father = &(tmp.value);  // 设置father
                    tmp_next_down = call_back_core(get, the_var, pack_value_parameter(tmp_next.value), global_inter);
                    if(is_error(&tmp_next_down) || is_space(&tmp_next_down)){
                        free(return_dict.value.value.dict_value->name_list);
                        free(return_dict.value.value.dict_value);
                        // TODO::还需要释放哈希表
                        return tmp_next_down;
                    }
                }
                else{
                    free(return_dict.value.value.dict_value->name_list);
                    free(return_dict.value.value.dict_value);
                    return to_error("Name Not Found __down__", "NameException", global_inter);
                }

                before->next = pack_value_parameter(tmp_next_down.value);
                before->next->u.var = make_statement();
                before->next->u.var->type = base_var;
                GWARF_result str_tmp = to_str(tmp_next.value, the_var, global_inter);
                if(is_error(&str_tmp) || is_space(&str_tmp)){
                    free(return_dict.value.value.dict_value->name_list);
                    free(return_dict.value.value.dict_value);
                    // TODO::还需要释放哈希表
                    return str_tmp;
                }
                before->next->u.var->code.base_var.var_name = str_tmp.value.value.string;
                before->next->u.var->code.base_var.from = NULL;
                before->next->type = name_value;
                before = before->next;
            }
            before->next = after;
            goto next;  // 跳过这一个
        }
        if(tmp_s->type != name_value){
            goto next;  // 跳过这一个
        }
        result_tmp = traverse(tmp_s->u.value, the_var, false, global_inter);  // 不需要取__value__
        if(is_error(&result_tmp) || is_space(&result_tmp)){  // Name Error错误
            free(return_dict.value.value.dict_value->name_list);
            free(return_dict.value.value.dict_value);
            // tmp_dict_name是链表，释放必须特别小心
            // TODO::还需要释放哈希表
            return result_tmp;
        }
        char *key;
        if(tmp_s->u.var->type == base_var){  // 设置key
            size_t size = (size_t)(13 + strlen(tmp_s->u.var->code.base_var.var_name));
            key = (char *)malloc(size);
            snprintf(key, size, "str_%s", tmp_s->u.var->code.base_var.var_name);
        }
        else{
            GWARF_result key_tmp = traverse(tmp_s->u.var, the_var, 0, global_inter);
            if(is_error(&key_tmp) || is_space(&key_tmp)){  // Name Error错误
                free(return_dict.value.value.dict_value->name_list);
                free(return_dict.value.value.dict_value);
                // TODO::还需要释放哈希表
                return key_tmp;
            }
            key = to_str_dict(key_tmp.value, the_var, global_inter).value.value.string;
        }
        login_node(key, result_tmp.value, return_dict.value.value.dict_value->dict_value, public);  // 插入
        dict_key *tmp_dict_name = return_dict.value.value.dict_value->name_list;
        while (1){  // 迭代
            if(!strcmp(tmp_dict_name->key, key)){  // 已经存在
                break;
            }
            else if(tmp_dict_name->next == NULL){
                tmp_dict_name->next = malloc(sizeof(dict_key));
                tmp_dict_name->next->next = NULL;
                tmp_dict_name->next->key = malloc(strlen(key));
                strcpy(tmp_dict_name->next->key, key);  // 复制key
                index += 1;  // 不存在才+1
                break;
            }
            tmp_dict_name = tmp_dict_name->next;
        }
        next: tmp_s = tmp_s->next;  // 指向下一个
    }
    return_dict.value.value.dict_value->index = index;
    return return_dict;
}

class_object *dict_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *,inter *), var_list *father_var_list, inter *global_inter){
    // 创建对象[空对象]
    
    GWARF_result class_value = GWARF_result_reset;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assignment_func("dict", class_value, the_var, 0, auto_public);  // 注册class 的 位置
    

    // 注册函数
    int a[][2] = {{__init__func,1},{__down__func,1},{__set__func,1},{__next__func,1},{__in__func,1}};
    char *name[] = {"__init__", "__down__", "__set__", "__next__", "__in__"};  //  继承tuple

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result dict_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var,inter *global_inter){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value = GWARF_result_reset;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    NotFatherError;
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            if(tmp_s == NULL){  // 生成空列表
                GWARF_result tmp_result = GWARF_result_reset;
                GWARF_value dict_tmp = GWARF_value_reset;
                dict_tmp.type = DICT_value;
                dict_tmp.value.dict_value = malloc(sizeof(the_dict));
                dict_tmp.value.dict_value->index = 0;
                dict_tmp.value.dict_value->dict_value = make_hash_var();
                dict_tmp.value.dict_value->name_list = malloc(sizeof(dict_key));
                dict_tmp.value.dict_value->name_list->key = "";
                dict_tmp.value.dict_value->name_list->next = NULL;
                tmp_result.value = dict_tmp;
                assignment_func("value", tmp_result, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            else if(tmp_s->next == NULL){  // 只有一个参数
                GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                tmp = to_dict(tmp_result.value, out_var, global_inter);  // 只有一个参数[要针对不同数据类型对此处作出处理]
                error_space(tmp, return_result, return_value);
                assignment_func("value", tmp, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            else{  // 有多个实参
                GWARF_result dict_tmp = GWARF_result_reset;
                dict_tmp = parameter_to_dict(tmp_s, out_var, global_inter);
                error_space(dict_tmp, return_result, return_value);

                assignment_func("value", dict_tmp, login_var, 0, auto_public);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }

            GWARF_result iter_value = GWARF_result_reset;
            iter_value.value.type = INT_value;
            iter_value.value.value.int_value = 0;
            assignment_func("iter_value", iter_value, login_var, 0, auto_public);  // 注册到self
            break;
        }
        case __next__func:{  // return index
            var *tmp = find_var(login_var, 0, "iter_value", NULL);
            int iter_index, len;
            if(tmp == NULL){
                iter_index = 0;
            }
            else{
                GWARF_result int_tmp = to_int(tmp->value, out_var, global_inter);
                error_space(int_tmp, return_result,return_value);
                iter_index = int_tmp.value.value.int_value;
            }

            tmp = find_var(login_var, 0, "value", NULL);
            len = tmp->value.value.dict_value->index;
            if(iter_index >= len){
                return_value = to_error("Max Iter", "IterException", global_inter);
                goto return_result;
            }
            else{
                dict_key *tmp_dict_key = tmp->value.value.dict_value->name_list->next;  // 忽略第一个点
                for(int i = 0;i < iter_index;i += 1){
                    if(tmp_dict_key == NULL){  // to_error
                        return_value = to_error("Max Iter", "IterException", global_inter);
                        goto return_result;  // 
                    }
                    tmp_dict_key = tmp_dict_key->next;
                }

                GWARF_result iter_value = GWARF_result_reset;
                iter_value.value.type = INT_value;
                iter_value.value.value.int_value = iter_index + 1;
                assignment_func("iter_value", iter_value, login_var, 0, auto_public);  // 注册到self
                return_value.value = key_to_str(tmp_dict_key->key);
            }

             break;
        }
        case __in__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                get_value = to_str_dict(tmp_result.value, out_var, global_inter);
                error_space(get_value, return_result, return_value);
                var *find_var = find_node(get_value.value.value.string, tmp->value.value.dict_value->dict_value);
                return_value.value.type = BOOL_value;
                if(find_var != NULL){  // not found
                    return_value.value.value.bool_value = true;
                }
                else{
                    return_value.value.value.bool_value = false;
                }
            }
            else{
                return_value = to_error("Don't get List Value", "ValueException", global_inter);
                goto return_result;
            }
            break;
        }
        case __down__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                get_value = to_str_dict(tmp_result.value, out_var, global_inter);
                error_space(get_value, return_result, return_value);
                var *find_var = find_node(get_value.value.value.string, tmp->value.value.dict_value->dict_value);
                if(find_var == NULL){  // not found
                    return_value = to_error("Dict key Not Found", "KeyException", global_inter);
                    goto return_result;
                }
                else{
                    return_value.value = find_var->value;
                }
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        case __set__func:{  // return index
            var *tmp = find_var(login_var, 0, "value", NULL);
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(tmp_result, return_result, return_value);
                get_value = to_str_dict(tmp_result.value, out_var, global_inter);
                error_space(get_value, return_result, return_value);
                tmp_s = tmp_s->next;
                GWARF_result new_value = traverse(tmp_s->u.value, out_var, false, global_inter);
                error_space(new_value, return_result, return_value);

                login_node(get_value.value.value.string, new_value.value, tmp->value.value.dict_value->dict_value, public);  // 插入
                dict_key *tmp_dict_name = tmp->value.value.dict_value->name_list;
                while (1){  // 迭代
                    if(!strcmp(tmp_dict_name->key, get_value.value.value.string)){  // 已经存在
                        break;
                    }
                    else if(tmp_dict_name->next == NULL){
                        tmp_dict_name->next = malloc(sizeof(dict_key));
                        tmp_dict_name->next->next = NULL;
                        tmp_dict_name->next->key = malloc(sizeof(get_value.value.value.string));
                        strcpy(tmp_dict_name->next->key, get_value.value.value.string);  // 复制key
                        tmp->value.value.dict_value->index += 1;  // 不存在才+1
                        break;
                    }
                    tmp_dict_name = tmp_dict_name->next;
                }
                
            }
            return_value.value.type = NULL_value;
            return_value.value.value.int_value = 0;
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

GWARF_result get__assignment__(GWARF_value *base_the_var, var_list *the_var, inter *global_inter){  // 获取__assignment__
    return run_func_core(base_the_var, the_var, "__assignment__", true,global_inter);
}

GWARF_result get__next__(GWARF_value *base_the_var, var_list *the_var, inter *global_inter){  // 获取__next__
    return run_func_core(base_the_var, the_var, "__next__", true,global_inter);
}

GWARF_result get__iter__(GWARF_value *base_the_var, var_list *the_var, inter *global_inter){  // 获取__iter__
    return run_func_core(base_the_var, the_var, "__iter__", true,global_inter);
}

GWARF_result get__value__(GWARF_value *base_the_var, var_list *the_var, inter *global_inter){  // 用于计算的get__value__统一核心
    return run_func(base_the_var, the_var, "__value__",global_inter);
}

GWARF_result get__bool__(GWARF_value *base_the_var, var_list *the_var, inter *global_inter){  // 获取__bool__  [所有转换为bool的object都执行这个]
    return run_func(base_the_var, the_var, "__bool__",global_inter);
}

GWARF_result run_func_core(GWARF_value *base_the_var, var_list *the_var, char *name, bool only, inter *global_inter){  // 无参数func->直到返回GWARF_value[not class]
    GWARF_result reight_tmp, get = GWARF_result_reset;
    reight_tmp.u = statement_end;
    int times = 0;
    var_list *call_var;
    while(1){
        if(base_the_var->type == CLASS_value){  // is class so that can use "."
            call_var = base_the_var->value.class_value->the_var;
        }
        else if(base_the_var->type == OBJECT_value){
            call_var = base_the_var->value.object_value->the_var;
        }
        else{
            reight_tmp.u = return_def;
            reight_tmp.value = *base_the_var;
            reight_tmp.return_times = times;
            goto return_result;  // 如果类型不是object或者class
        }
        var *tmp_var = find_var(call_var, 0, name, NULL);
        if(tmp_var != NULL){
            get.value = tmp_var->value;  // TODO:: 需要检查__value__是否存在
            get.father = base_the_var;  // 设置father
            reight_tmp = call_back_core(get, the_var, NULL, global_inter);
            error_space(reight_tmp, return_result, reight_tmp);
            if(only){  // 不需要重复获取，比如__iter__，__next__
                goto return_result;
            }
            else{
                times = reight_tmp.return_times;
                base_the_var = &(reight_tmp.value);  // 重复获取__value__[直到类型不是object或class]
            }
        }
        else{
            char *tmp = malloc((size_t)( 21 + strlen(name)) );
            sprintf(tmp, "Name Not Found [%s]\n", name);
            reight_tmp = to_error(tmp, "NameException", global_inter);
            goto return_result;
        }
    }
    return_result: return reight_tmp;
}
