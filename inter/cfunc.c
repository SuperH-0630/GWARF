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
    if((value.type == CLASS_value) || (value.type == OBJECT_value) || (value.type == FUNC_value) || (value.type == NULL_value)){  // 可以直接返回
        return value;
    }
    GWARF_result func_result;
    func_result.u = statement_end;
    func_result.value.type = NULL_value;
    func_result.value.value.int_value = 0;
    var *tmp;
    if(value.type == NUMBER_value){
        tmp = find_var(the_var, 0, "double");
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.type == INT_value){
        tmp = find_var(the_var, 0, "int");
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.type == BOOL_value){
        tmp = find_var(the_var, 0, "bool");
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.type == STRING_value){
        tmp = find_var(the_var, 0, "str");
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else if(value.type == LIST_value){
        tmp = find_var(the_var, 0, "list");
        if(tmp != NULL){
            func_result.value = tmp->value;
        }
    }
    else{
        return value;
    }
    return call_back_core(func_result, the_var, pack_value_parameter(value)).value;
}


GWARF_result to_error(char *error_info, char *error_type, var_list *the_var){  // 把GWARF_value封装成error
    GWARF_result func_result, return_result;
    GWARF_value tmp_value;

    tmp_value.type = STRING_value;
    tmp_value.value.string = error_info;

    func_result.u = statement_end;

    return_result.u = error;
    return_result.error_info = error_info;

    var *tmp = find_var(the_var, 0, error_type);

    if(tmp != NULL){
        func_result.value = tmp->value;
        return_result.value = call_back_core(func_result, the_var, pack_value_parameter(tmp_value)).value;
    }
    else{
        printf("NameError * 2\n");
        return_result.value.type = NULL_value;
        return_result.value.value.int_value = 0;
    }
    return return_result;
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
            if(is_error(&tmp)){  // Name Error错误
                return_value = tmp;
                goto return_result;
            }
            else if(is_space(&tmp)){
                return_value = tmp;
                goto return_result;
            }
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
    class_object *class_tmp = make_object(the_var, NULL);

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

class_object *make_object(var_list *the_var, var_list *father_var_list){
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    if(father_var_list != NULL){
        append_by_var_list(class_tmp->the_var, father_var_list);  // int、double、str等内置类需要继承gobject类
    }

    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    return class_tmp;
}

class_object *BaseException_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = make_object(the_var, father_var_list);
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("BaseException", class_value, the_var, 0);  // 注册class 的 位置
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

GWARF_result BaseException_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
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
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            tmp.value = to_str(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
            assigment_func("ErrorInfo", tmp, login_var, 0);  // 注册到self -> ErrorInfo
            return_value.u = statement_end;  // __init__没有return
            break;
        }
        default:
            break;
    }
    return_result: return return_value;
}

class_object *Exception_login_official(var_list *the_var, var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("Exception", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");
    return class_tmp;
}

class_object *NameException_login_official(var_list *the_var, var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("NameException", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");
    return class_tmp;
}

class_object *gobject_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){  // 内置对象继承的类
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = make_object(the_var, father_var_list);
    
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("gobject", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,1}, {9,1}, {10,1}, {11,1}, {12,1}, {13,1}, {14,1}, {15,1}, {16,1}, {17,1}, {3,1}, {21,1}, {22,1}, {18,1}, {19,1}, {20,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__","__eq__", "__more__", "__less__", "__eqmore__", "__eqless__","__noteq__", "__pow__", "__log__","__sqrt__","__negative__","__bool__","__subr__",
                    "__divr__", "__powr__", "__logr__","__sqrtr__"};

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
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = add_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __sub__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sub_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __subr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sub_func(reight_tmp, left_tmp, out_var);  // right和left反过来
            break;
        }
        case __mul__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = mul_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __div__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = div_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __divr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = div_func(reight_tmp, left_tmp, out_var);  // left和right反过来
            break;
        }
        case __eq__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 0);
            break;
        }
        case __more__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 1);
            break;
        }
        case __less__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 2);
            break;
        }
        case __eqmore__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 3);
            break;
        }
        case __eqless__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 4);
            break;
        }
        case __noteq__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = equal_func(left_tmp, reight_tmp, out_var, 5);
            break;
        }
        case __pow__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = pow_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __log__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = log_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __sqrt__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sqrt_func(left_tmp, reight_tmp, out_var);
            break;
        }
        case __powr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = pow_func(reight_tmp, left_tmp, out_var);
            break;
        }
        case __logr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = log_func(reight_tmp, left_tmp, out_var);
            break;
        }
        case __sqrtr__func:{
            GWARF_result reight_tmp, left_tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
            return_value = sqrt_func(reight_tmp, left_tmp, out_var);
            break;
        }
        case __negative__func:{
            GWARF_result left_tmp;
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                left_tmp.value = tmp->value;
            }
            else{
                left_tmp.value.type = NULL_value;
                left_tmp.value.value.int_value = 0;
            }
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
    class_object *class_tmp = make_object(the_var, father_var_list);
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
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            GWARF_value base_the_var = tmp.value;  // 只有一个参数
            tmp.value = to_int(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
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
    class_object *class_tmp = make_object(the_var, father_var_list);

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
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            tmp.value = to_double(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
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
    class_object *class_tmp = make_object(the_var, father_var_list);

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
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            tmp.value = to_str(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
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
    class_object *class_tmp = make_object(the_var, father_var_list);

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
            GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto return_result;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto return_result;
            }
            tmp.value = to_bool_(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
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


class_object *list_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *), var_list *father_var_list){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = make_object(the_var, father_var_list);

    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("list", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1},{23,1},{24,1},{25,1},{26,1}};
    char *name[] = {"__init__", "__len__", "__down__", "__set__", "__slice__"};  //  __len__是获取长度，__down__是获取下值，__set__是设置值，__slice__是切片

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
    return class_tmp;
}

GWARF_result list_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境, the_var是self内部环境
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
            if(tmp_s == NULL){  // 生成空列表
                GWARF_result tmp_result;
                GWARF_value list_tmp;
                list_tmp.type = LIST_value;
                list_tmp.value.list_value = malloc(sizeof(the_list));
                list_tmp.value.list_value->index = 0;
                list_tmp.value.list_value->list_value = malloc((size_t)0);
                tmp_result.value = list_tmp;
                assigment_func("value", tmp_result, login_var, 0);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            else{
                GWARF_result tmp, tmp_result = traverse(tmp_s->u.value, out_var, false);
                if(is_error(&tmp_result)){  // Name Error错误
                    return_value = tmp_result;
                    goto return_result;
                }
                else if(is_space(&tmp_result)){
                    return_value = tmp_result;
                    goto return_result;
                }
                tmp.value = to_list(tmp_result.value, out_var);  // 只有一个参数[要针对不同数据类型对此处作出处理]
                assigment_func("value", tmp, login_var, 0);  // 注册到self
                return_value.u = statement_end;  // __init__没有return
            }
            break;
        }
        case __len__func:{  // return index
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                return_value.value.type = INT_value;
                return_value.value.value.int_value = (int)(sizeof(tmp->value.value.list_value->list_value) / sizeof(GWARF_value));  // 获取长度
            }
            else{
                return_value.value.type = INT_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        case __down__func:{  // return index
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false);
                if(is_error(&tmp_result)){  // Name Error错误
                    return_value = tmp_result;
                    goto return_result;
                }
                else if(is_space(&tmp_result)){
                    return_value = tmp_result;
                    goto return_result;
                }
                GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
                get_value = get__value__(&base_the_var, the_var);
                get_value.value = to_int(get_value.value, out_var);
                // puts("NONE");
                return_value.value = tmp->value.value.list_value->list_value[get_value.value.value.int_value];
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        case __slice__func:{  // return index
            var *tmp = find_var(login_var, 0, "value");
            int len = (int)(sizeof(tmp->value.value.list_value->list_value) / sizeof(GWARF_value));
            int start, end;
            if(tmp != NULL){
                GWARF_result start_result = traverse(tmp_s->u.value, out_var, false), end_result;
                if(is_error(&start_result)){  // Name Error错误
                    return_value = start_result;
                    goto return_result;
                }
                else if(is_space(&start_result)){
                    return_value = start_result;
                    goto return_result;
                }

                start = to_int(get__value__(&(start_result.value), the_var).value, out_var).value.int_value;
                tmp_s = tmp_s->next;
                if(tmp_s != NULL){
                    end_result = traverse(tmp_s->u.value, out_var, false);
                    if(is_error(&end_result)){  // Name Error错误
                        return_value = end_result;
                        goto return_result;
                    }
                    else if(is_space(&end_result)){
                        return_value = end_result;
                        goto return_result;
                    }
                    end = to_int(get__value__(&(end_result.value), the_var).value, out_var).value.int_value;
                }
                else{
                    end = len;
                }

                return_value.value.type = LIST_value;
                return_value.value.value.list_value = malloc(sizeof(the_list));  // 申请list的空间
                return_value.value.value.list_value->list_value = malloc((size_t)((end - start) * sizeof(GWARF_value)));
                memcpy(return_value.value.value.list_value->list_value, (tmp->value.value.list_value->list_value + start), (size_t)((end - start) * sizeof(GWARF_value)));
                return_value.value.value.list_value->index = (end - len) - 1;
            }
            else{
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        }
        case __set__func:{  // return index
            var *tmp = find_var(login_var, 0, "value");
            if(tmp != NULL){
                GWARF_result get_value, tmp_result = traverse(tmp_s->u.value, out_var, false);
                if(is_error(&tmp_result)){  // Name Error错误
                    return_value = tmp_result;
                    goto return_result;
                }
                else if(is_space(&tmp_result)){
                    return_value = tmp_result;
                    goto return_result;
                }
                GWARF_value base_the_var = tmp_result.value;  // 只有一个参数
                get_value = get__value__(&base_the_var, the_var);
                get_value.value = to_int(get_value.value, out_var);

                tmp_s = tmp_s->next;
                GWARF_result new_value = traverse(tmp_s->u.value, out_var, false);
                if(is_error(&new_value)){  // Name Error错误
                    return_value = new_value;
                    goto return_result;
                }
                else if(is_space(&new_value)){
                    return_value = new_value;
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
    if(the_func->official_func == __slice__func){
    }
    return_result: return return_value;
}


GWARF_value to_list(GWARF_value value, var_list *the_var){
    if((value.type == LIST_value)){
        return value;  // 直接返回数据
    }

    GWARF_value return_number;
    return_number.type = LIST_value;

    if(value.type == OBJECT_value){  // 调用__value__方法
        return_number = to_list(get__value__(&value, the_var).value, the_var);  // 递归
    }
    else{
        return_number.value.list_value = malloc(sizeof(the_list));
        return_number.value.list_value->index = 1;
        return_number.value.list_value->list_value = malloc(sizeof(GWARF_value));
        return_number.value.list_value->list_value[0] = value;  // 保存value
    }
    return return_number;
}

GWARF_value parameter_to_list(parameter *tmp_s, var_list *the_var){  // 把parameter转换为list
    GWARF_value return_list;
    return_list.type = LIST_value;
    return_list.value.list_value = malloc(sizeof(the_list));
    return_list.value.list_value->list_value = malloc(0);
    int index = 0;
    GWARF_result result_tmp;
    while(1){
        if(tmp_s == NULL){
            break;
        }
        result_tmp = traverse(tmp_s->u.value, the_var, false);  // 不需要取__value__
        if(is_error(&result_tmp)){  // Name Error错误
            goto next;  // 直接指向下一个
        }
        else if(is_space(&result_tmp)){
            goto next;
        }
        index += 1;
        return_list.value.list_value->list_value = realloc(return_list.value.list_value->list_value, sizeof(GWARF_value) * index);  // 申请新空间
        return_list.value.list_value->list_value[index - 1] = result_tmp.value;  // 保存value
        next: tmp_s = tmp_s->next;  // 指向下一个
    }
    return_list.value.list_value->index = index;
    return return_list;
}


GWARF_result get__value__(GWARF_value *base_the_var, var_list *the_var){  // 用于计算的get__value__统一核心
    GWARF_result tmp = run_func(base_the_var, the_var, "__value__");
    if(is_error(&tmp)){
        tmp.u = statement_end;
        tmp.value.type = NULL_value;
        tmp.value.value.int_value = 0;
    }
    return tmp;
}

GWARF_result get__bool__(GWARF_value *base_the_var, var_list *the_var){  // 用于计算的get__value__统一核心
    GWARF_result tmp = run_func(base_the_var, the_var, "__bool__");
    if(is_error(&tmp)){
        tmp.u = statement_end;
        tmp.value.type = BOOL_value;
        tmp.value.value.bool_value = true;
    }
    return tmp;
}

GWARF_result run_func(GWARF_value *base_the_var, var_list *the_var, char *name){  // 无参数func->直到返回GWARF_value[not class]
    GWARF_result reight_tmp, get;
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
        var *tmp_var = find_var(call_var, 0, name);
        if(tmp_var != NULL){
            get.value = tmp_var->value;  // TODO:: 需要检查__value__是否存在
            get.father = base_the_var;  // 设置father
            reight_tmp = call_back_core(get, the_var, NULL);
            times = reight_tmp.return_times;
            base_the_var = &(reight_tmp.value);  // 重复获取__value__[直到类型不是object或class]
        }
        else{
            char *tmp = malloc((size_t)( 21 + strlen(name)) );
            sprintf(tmp, "name not found [%s]\n", name);
            reight_tmp = to_error(tmp, "NameException", the_var);
            goto return_result;
        }
    }
    return_result: return reight_tmp;
}
