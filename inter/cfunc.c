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

GWARF_value to_object(GWARF_value value, var_list *the_var){  // 把GWARF_value封装成objct
    GWARF_result return_value;
    if((value.type == CLASS_value) || (value.type == OBJECT_value) || (value.type == FUNC_value) || (value.type == NULL_value)){  // 可以直接返回
        return value;
    }
    GWARF_result func_result;
    if(value.type == NUMBER_value){
        func_result.value = find_var(the_var, 0, "double")->value;
    }
    else if(value.type == INT_value){
        func_result.value = find_var(the_var, 0, "int")->value;
    }
    else if(value.type == BOOL_value){
        func_result.value = find_var(the_var, 0, "bool")->value;
    }
    else if(value.type == STRING_value){
        func_result.value = find_var(the_var, 0, "str")->value;
    }
    else{
        return value;
    }
    return call_back_core(func_result, the_var, pack_value_parameter(value)).value;
}


void login_official_func(int type, int is_class, var_list *the_var, char *name, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){  // 注册单个official func
    GWARF_result func_value;
    func *func_tmp = malloc(sizeof(func));

    func_tmp->done = NULL;
    func_tmp->parameter_list = NULL;
    func_tmp->the_var = copy_var_list(the_var);
    func_tmp->type = official;
    func_tmp->official_func = type;
    func_tmp->is_class = is_class;
    func_tmp->paser = paser;

    func_value.value.type = FUNC_value;
    func_value.value.value.func_value = func_tmp;
    assigment_func(name, func_value, the_var, 0);  // 注册函数到指定的位置
}

void login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){
    // {{official_func_type, is_class}}
    int a[][2] = {{1,0}};
    // {login_name}
    char *name[] = {"print"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], the_var, name[i], paser);
    }
}


// global 全局内置函数解析器
GWARF_result official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){
    GWARF_result return_value;
    return_value.u = return_def;
    return_value.return_times = 0;
    switch (the_func->official_func)
    {
    case printf_func:{  // printf something
        if(tmp_s == NULL){  // 没有东西要打印
            goto return_result;
        }
        while(1){
            GWARF_result tmp = traverse(tmp_s->u.value, out_var, false);
            if((tmp.value.type == INT_value)){
                printf("%d", tmp.value.value.int_value);
            }
            else if(tmp.value.type == BOOL_value){
                if(tmp.value.value.bool_value){
                    printf("true");
                }
                else{
                    printf("false");
                } 
            }
            else if(tmp.value.type == NUMBER_value){
                printf("%f", tmp.value.value.double_value);
            }
            else if(tmp.value.type == NULL_value){
                printf("<-None->");
            }
            else if(tmp.value.type == STRING_value){
                printf("'%s'", tmp.value.value.string);
            }
            else if(tmp.value.type == FUNC_value){
                printf("<-function on %u->", tmp.value.value.func_value);
            }
            else if(tmp.value.type == CLASS_value){
                printf("<-class on %u->", tmp.value.value.class_value);
            }
            else if(tmp.value.type == OBJECT_value){
                printf("<-object on %u->", tmp.value.value.object_value);
            }
            else{
                printf("var value = other\n");
            }
            if (tmp_s->next == NULL){  // the last
                break;
            }
            tmp_s = tmp_s->next;
        }
        printf("\n");  // 换行
        return_value.u = statement_end;
        break;
    }
    default:
        break;
    }
    return_result: return return_value;
}

class_object *object_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){  // 内置对象继承的类
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));
    class_tmp->the_var = make_var_base(make_var());  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("object", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");


    // 注册函数
    int a[][2] = {{3,1}};
    char *name[] = {"__value__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result object_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    switch (the_func->official_func)
    {
        case __value__func:{  // 若想实现运算必须要有这个方法
            return_value.value.type = STRING_value;  // 取得用于计算的数值
            return_value.value = to_str(*(father.father), out_var);
            break;
        }
    }
    return_result: return return_value;
}

class_object *gobject_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){  // 内置对象继承的类
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // 一切类都需要继承object类[包括set class如果tmp_s == NULL则需要继承object]
    }

    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("gobject", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,1}, {9,1}, {10,1}, {11,1}, {12,1}, {13,1}, {14,1}, {15,1}, {16,1}, {17,1}, {3,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__","__eq__", "__more__", "__less__", "__eqmore__", "__eqless__","__noteq__", "__pow__", "__log__","__sqrt__","__negative__","__bool__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result gobject_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    else{
        printf("NO login, father type = %d\n", father.father->type);
    }
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp;
            tmp.value.type = INT_value;
            tmp.value.value.int_value = 0;
            assigment_func("value", tmp, login_var, 0);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value");  // gobject类的value存储在self.value中
            return_value.value = tmp->value;  // 取得用于计算的数值
            break;
        }
        case __add__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = add_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __sub__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = sub_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __mul__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = mul_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __div__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = div_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __eq__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 0);
            break;
        }
        case __more__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 1);
            break;
        }
        case __less__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 2);
            break;
        }
        case __eqmore__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 3);
            break;
        }
        case __eqless__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 4);
            break;
        }
        case __noteq__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = equal_func(left_tmp, reight_tmp, out_var, 5);
            break;
        }
        case __pow__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = pow_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __log__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = log_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __sqrt__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = sqrt_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __negative__func:{
            GWARF_result left_tmp;
            left_tmp.value = find_var(login_var, 0, "value")->value;
            return_value = negative_func(left_tmp, out_var);
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

class_object *int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // int、double、str等内置类需要继承gobject类
    }

    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("int", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    else{
        printf("NO login, father type = %d\n", father.father->type);
    }
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp;
            tmp.value = to_int(traverse(tmp_s->u.value, out_var, false).value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            assigment_func("value", tmp, login_var, 0);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to int[底层实现]
GWARF_value to_int(GWARF_value value, var_list *the_var){
    if((value.type == INT_value)){
        return value;  // 直接返回数据
    }

    GWARF_value return_number;
    return_number.type = INT_value;

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_int(get__value__(&value, the_var).value, the_var);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            return_number.value.int_value = value.value.bool_value;
        }
        else if(value.type == NUMBER_value){
            return_number.value.int_value = (int)value.value.double_value;
        }
        else if(value.type == STRING_value){
            return_number.value.int_value = atoi(value.value.string);
        }
        else{
            return_number.value.int_value = 0;
        }
    }
    return return_number;
}


class_object *double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // 一切类都需要继承object类[包括set class如果tmp_s == NULL则需要继承object]
    }

    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("double", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    else{
        printf("NO login, father type = %d\n", father.father->type);
    }
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp;
            tmp.value = to_double(traverse(tmp_s->u.value, out_var, false).value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            assigment_func("value", tmp, login_var, 0);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to double[底层实现]
GWARF_value to_double(GWARF_value value, var_list *the_var){
    if((value.type == NUMBER_value)){
        return value;  // 直接返回数据
    }

    GWARF_value return_number;
    return_number.type = NUMBER_value;

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_double(get__value__(&value, the_var).value, the_var);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            return_number.value.double_value = (double)value.value.bool_value;
        }
        else if(value.type == INT_value){
            return_number.value.double_value = (double)value.value.int_value;
        }
        else if(value.type == STRING_value){
            return_number.value.double_value = (double)atof(value.value.string);
        }
        else{
            return_number.value.double_value = 0;
        }
    }
    return return_number;
}

class_object *str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // 一切类都需要继承object类[包括set class如果tmp_s == NULL则需要继承object]
    }
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("str", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    else{
        printf("NO login, father type = %d\n", father.father->type);
    }
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp;
            tmp.value = to_str(traverse(tmp_s->u.value, out_var, false).value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            assigment_func("value", tmp, login_var, 0);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to str[底层实现]
GWARF_value to_str(GWARF_value value, var_list *the_var){
    if((value.type == STRING_value)){
        return value;  // 直接返回数据
    }

    GWARF_value return_number;
    return_number.type = STRING_value;

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_str(get__value__(&value, the_var).value, the_var);  // 递归
    }
    else{
        if(value.type == BOOL_value){
            if(value.value.bool_value){
                return_number.value.string = "true";
            }
            else{
                return_number.value.string = "false";
            }
        }
        else if(value.type == INT_value){
            size_t size = (size_t)(2 + len_int(value.value.int_value));
            return_number.value.string = (char *)malloc(size);
            snprintf(return_number.value.string, size, "%d", value.value.int_value);
        }
        else if(value.type == NUMBER_value){
            size_t size = (size_t)(2 + len_double(value.value.double_value));
            return_number.value.string = (char *)malloc(size);
            snprintf(return_number.value.string, size, "%f", value.value.double_value);
        }
        else if(value.type == NULL_value){
            return_number.value.string = "<-None->";
        }
        else if(value.type == FUNC_value){
            size_t size = (size_t)(20 + len_intx((unsigned int)value.value.func_value));  // 转换为无符号整形数字
            return_number.value.string = (char *)malloc(size);
            snprintf(return_number.value.string, size, "<-function on %u->", value.value.func_value);
        }
        else if(value.type == CLASS_value){
            size_t size = (size_t)(16 + len_intx((unsigned int)value.value.class_value));
            return_number.value.string = (char *)malloc(size);
            snprintf(return_number.value.string, size, "<-class on %u->", value.value.class_value);
        }
        else{
            printf("var value = other\n");
        }
    }
    return return_number;
}

class_object *bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // 一切类都需要继承object类[包括set class如果tmp_s == NULL则需要继承object]
    }
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("bool", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}};
    char *name[] = {"__init__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
    return_value.return_times = 0;
    if(father.father->type == CLASS_value){  // is class so that can use "."
        login_var = father.father->value.class_value->the_var;
    }
    else if(father.father->type == OBJECT_value){
        login_var = father.father->value.object_value->the_var;
    }
    else{
        printf("NO login, father type = %d\n", father.father->type);
    }
    switch (the_func->official_func)
    {
        case __init__func:{  // printf something
            GWARF_result tmp;
            tmp.value = to_bool_(traverse(tmp_s->u.value, out_var, false).value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            assigment_func("value", tmp, login_var, 0);  // 注册到self
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

// to bool[底层实现]
GWARF_value to_bool_(GWARF_value value, var_list *the_var){
    if((value.type == BOOL_value)){
        return value;  // 直接返回数据
    }

    GWARF_value return_number;
    return_number.type = BOOL_value;

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_bool_(get__value__(&value, the_var).value, the_var);  // 递归
    }
    else{
        return_number.value.bool_value = to_bool(value);  // 转换成bool
    }
    return return_number;
}

GWARF_result get__value__(GWARF_value *base_the_var, var_list *the_var){  // 用于计算的get__value__统一核心
    return run_func(base_the_var, the_var, "__value__");
}

GWARF_result get__bool__(GWARF_value *base_the_var, var_list *the_var){  // 用于计算的get__value__统一核心
    return run_func(base_the_var, the_var, "__bool__");
}

GWARF_result run_func(GWARF_value *base_the_var, var_list *the_var, char *name){  // 无参数func->直到返回GWARF_value[not class]
    GWARF_result reight_tmp, get;
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
        get.value = find_var(call_var, 0, name)->value;  // TODO:: 需要检查__value__是否存在
        get.father = base_the_var;  // 设置father
        reight_tmp = call_back_core(get, the_var, NULL);
        times = reight_tmp.return_times;
        base_the_var = &(reight_tmp.value);  // 重复获取__value__[直到类型不是object或class]
    }
    return_result: return reight_tmp;
}
