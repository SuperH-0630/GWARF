#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "interpreter.h"

double log_(double base, double num){  // 自己定义一次log
    return log(num) / log(base);
}

double sqrt_(double base, double num){  // 定义根号sqrt
    return pow(base, (1 / num));
}

bool is_space(GWARF_result *tmp){  // 使用指针是不想复制数据
    if(tmp->u == cycle_break || tmp->u == code_broken || tmp->u == cycle_continue || tmp->u == code_continued || 
            tmp->u == cycle_restart || tmp->u == code_restarted || tmp->u == code_rego || tmp->u == code_rewent){
        return true;
    }
    if(tmp->u == return_def && tmp->return_times != 0){  // return def
        return true;
    }
    return false;
}

bool is_error(GWARF_result *tmp){  // 判断是否为error
    if(tmp->u == error){
        return true;
    }
    return false;
}

bool to_bool(GWARF_value value){
    double bool_double = 1;  // if bool_double == 0则返回false其他返回true
    if(value.type == OBJECT_value){  // 调用左add方法
        bool_double = to_bool(get__bool__(&value, NULL).value);  // 实际上不需要the_var参数链[没有实参]
    }
    else{
        if(value.type == INT_value || value.type == BOOL_value){
            bool_double = (double)value.value.int_value;
        }
        else if(value.type == NUMBER_value){
            bool_double = value.value.double_value;
        }
        else if(value.type == STRING_value){
            bool_double = (double)strlen(value.value.string);
        }
        else if(value.type == NULL_value){
            bool_double = 0;
        }
    }
    // 返回值
    if(bool_double){
        return true;
    }
    else{
        return false;
    }
}


GWARF_result read_statement(statement *the_statement, var_list *the_var, var_list *login_var){  // read the statement list with case to run by func
    if(login_var == NULL){
        login_var = the_var;
    }
    GWARF_result return_value;
    return_value.u = statement_end;  // 正常设置[正常语句结束]
    return_value.value.type = NULL_value;  // 默认设置
    return_value.value.value.int_value = 0;  // 默认设置
    switch (the_statement->type)
    {
        case operation:  // 表达式运算
            puts("----code----");
            return_value = operation_func(the_statement, the_var, login_var);
            if((return_value.value.type == INT_value)){
                printf("operation value = %d\n", return_value.value.value.int_value);
            }
            else if(return_value.value.type == BOOL_value){
                if(return_value.value.value.bool_value){
                    printf("operation value = true\n");
                }
                else{
                    printf("operation value = false\n");
                } 
            }
            else if(return_value.value.type == NUMBER_value){
                printf("operation value = %f\n", return_value.value.value.double_value);
            }
            else if(return_value.value.type == NULL_value){
                printf("operation value = None\n");
            }
            else if(return_value.value.type == STRING_value){
                printf("operation value = %s\n", return_value.value.value.string);
            }
            else{
                printf("operation value = other[%d]\n", return_value.value.type);
            }
            puts("----stop code----");
            break;
        case chose_exp:{
            GWARF_result tmp_result = traverse(the_statement->code.chose_exp.condition, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                break;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                break;
            }
            if(to_bool(tmp_result.value)){
                return_value = traverse(the_statement->code.chose_exp.true_do, the_var, false);
            }
            else{
                return_value = traverse(the_statement->code.chose_exp.false_do, the_var, false);
            }
            if(!(is_error(&return_value) || is_space(&return_value))){  // Name Error错误
                return_value.value = to_object(return_value.value, the_var);
            }
            break;
        }
        case call:
            return_value = call_back(the_statement, the_var);
            break;
        case while_cycle:
            puts("----while code----");
            return_value = while_func(the_statement, the_var);
            puts("----stop while code----");
            if(return_value.u == statement_end){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case for_cycle:
            puts("----for code----");
            return_value = for_func(the_statement, the_var);
            puts("----for while code----");
            if(return_value.u == statement_end){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case for_in_cycle:
            puts("----for code----");
            return_value = forin_func(the_statement, the_var);
            puts("----for while code----");
            if(return_value.u == statement_end){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case if_branch:
            puts("----if code----");
            return_value = if_func(the_statement->code.if_branch.done, the_var);
            puts("----stop if code----");
            if(return_value.u == statement_end){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case base_value:  // get value[所有字面量均为这个表达式]
            return_value.value = (the_statement->code).base_value.value;  // code
            if((return_value.value.type == INT_value) || (return_value.value.type == BOOL_value)){
                printf("get value = %d\n", return_value.value.value.int_value);
            }
            else if(return_value.value.type == NUMBER_value){
                printf("get value = %f\n", return_value.value.value.double_value);
            }
            else if(return_value.value.type == NULL_value){
                printf("get value = None\n");
            }
            else if(return_value.value.type == STRING_value){
                printf("get value = %s\n", return_value.value.value.string);
            }
            else{
                printf("get value = other[%d]\n", return_value.value.type);
            }
            // base_value返回字面量 -> 主要返回object类型，还会返回GWARF_value的其他类型供生成object类型
            break;
        case base_list:  // get value[所有字面量均为这个表达式]
            return_value.value = parameter_to_list(the_statement->code.base_list.value, the_var);  // code
            break;
        case base_dict:  // get value[所有字面量均为这个表达式]
            return_value.value = parameter_to_dict(the_statement->code.base_dict.value, the_var);  // code
            break;
        case slice:{  // get value[所有字面量均为这个表达式]
            GWARF_result tmp_result = traverse((the_statement->code).slice.base_var, the_var, false), get;  // 把a[1:2:3]的a取出来
            if(is_error(&tmp_result)){  // Name Error错误
                return_value = tmp_result;
                goto the_break_slice;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto the_break_slice;
            }

            GWARF_value base_the_var = tmp_result.value;

            if(base_the_var.type == CLASS_value){  // is class so that can use "."
                var *tmp = find_var(base_the_var.value.class_value->the_var, 0, "__slice__");
                if(tmp != NULL){
                    get.value = tmp->value;
                    get.father = &base_the_var;  // 设置father
                    return_value = call_back_core(get, the_var, the_statement->code.slice.value);
                    goto the_break_slice;
                }
            }
            else if(base_the_var.type == OBJECT_value){
                var *tmp = find_var(base_the_var.value.object_value->the_var, 0, "__slice__");
                if(tmp != NULL){
                    get.value = tmp->value;
                    get.father = &base_the_var;  // 设置father
                    return_value = call_back_core(get, the_var, the_statement->code.slice.value);
                    goto the_break_slice;
                }
            }

            the_break_slice: 
            return_value.value = to_object(return_value.value, the_var);
            // printf("return_value.value.type = %d\n", return_value.value);
            break;
        }
        case base_var:{    // because the var tmp, we should ues a {} to make a block[name space] for the tmp var;
            int from = 0;
            if(the_statement->code.base_var.from == NULL){
                from = 0;
            }
            else{
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.base_var.from, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    from = 0;
                }
                else if(is_space(&tmp_object)){
                    from = 0;
                }
                else{
                    tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                    if(tmp_result.value.type == INT_value){
                        from = tmp_result.value.value.int_value;
                    }
                    else if(tmp_result.value.type == NUMBER_value){
                        from = (int)tmp_result.value.value.double_value;
                    }
                    else{
                        from = 0;
                    }
                }
            }
            var *tmp = find_var(the_var, from, (the_statement->code).base_var.var_name);
            if(tmp == NULL){  // 输出name error[共两处会输出]
                char *tmp = malloc((size_t)( 21 + strlen(the_statement->code.base_var.var_name) ));
                sprintf(tmp, "name not found [%s]\n", the_statement->code.base_var.var_name);
                return_value = to_error(tmp, "NameException", the_var);
            }
            else
            {
                return_value.value = tmp->value;  // get_var
                if((return_value.value.type == INT_value) || (return_value.value.type == BOOL_value)){
                    printf("var value = %d\n", return_value.value.value.int_value);
                }
                else if(return_value.value.type == NUMBER_value){
                    printf("var value = %f\n", return_value.value.value.double_value);
                }
                else if(return_value.value.type == NULL_value){
                    printf("var value = None\n");
                }
                else if(return_value.value.type == STRING_value){
                    printf("var value = %s\n", return_value.value.value.string);
                }
                else{
                    printf("var value = other[%d]\n", return_value.value.type);
                }
            }
            break;
        }
        case point:{
            GWARF_result tmp_result = traverse((the_statement->code).point.base_var, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                return_value = tmp_result;
                goto the_break;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto the_break;
            }

            GWARF_value base_the_var = tmp_result.value;
            if(base_the_var.type == CLASS_value){  // is class so that can use "."
                return_value = traverse((the_statement->code).point.child_var, base_the_var.value.class_value->the_var, false);
            }
            else if(base_the_var.type == OBJECT_value){
                return_value = traverse((the_statement->code).point.child_var, base_the_var.value.object_value->the_var, false);
            }
            else{  // 其他类型
                goto the_break;
            }
            if(is_error(&return_value)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                goto the_break;
            }
            else if(is_space(&return_value)){
                goto the_break;
            }

            return_value.father = malloc(sizeof(return_value.father));  // 记录father的值
            *(return_value.father) = base_the_var;

            the_break: 
            return_value.value = to_object(return_value.value, the_var);
            break;
        }
        case down:{
            GWARF_result tmp_result = traverse((the_statement->code).down.base_var, the_var, false), get;
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                return_value = tmp_result;
                goto the_break_down;
            }
            else if(is_space(&tmp_result)){
                return_value = tmp_result;
                goto the_break_down;
            }

            GWARF_value base_the_var = tmp_result.value;

            if(base_the_var.type == CLASS_value){  // is class so that can use "."
                GWARF_result child_value = traverse((the_statement->code).down.child_var, the_var, false);  // 作为参数
                var *tmp = find_var(base_the_var.value.class_value->the_var, 0, "__down__");
                if(tmp != NULL){
                    get.value = tmp->value;
                    get.father = &base_the_var;  // 设置father
                    return_value = call_back_core(get, the_var, pack_value_parameter(child_value.value));
                    goto the_break_down;
                }
            }
            else if(base_the_var.type == OBJECT_value){
                GWARF_result child_value = traverse((the_statement->code).down.child_var, the_var, false);  // 作为参数
                var *tmp = find_var(base_the_var.value.object_value->the_var, 0, "__down__");
                if(tmp != NULL){
                    get.value = tmp->value;
                    get.father = &base_the_var;  // 设置father
                    return_value = call_back_core(get, the_var, pack_value_parameter(child_value.value));
                    goto the_break_down;
                }
            }

            the_break_down: 
            return_value.value = to_object(return_value.value, the_var);  // call_back_core 返回值是object
            break;
        }
        case def:{
            GWARF_result func_value;
            func *func_tmp = malloc(sizeof(func));

            func_tmp->done = the_statement->code.def.done;
            func_tmp->parameter_list = the_statement->code.def.parameter_list;
            func_tmp->the_var = copy_var_list(the_var);
            func_tmp->type = customize;  // func by user
            if(login_var != the_var){  // 定义为类方法
                func_tmp->is_class = true;
            }
            else{
                func_tmp->is_class = false;
            }
            func_tmp->is_lambda = false;

            func_value.value.type = FUNC_value;
            func_value.value.value.func_value = func_tmp;

            assignment_statement(the_statement->code.def.var, the_var, login_var, func_value);  // 注册函数到指定的位置
            // 无返回值
            break;
        }
        case lambda_func:{
            func *func_tmp = malloc(sizeof(func));

            func_tmp->done = the_statement->code.lambda_func.done;
            func_tmp->parameter_list = the_statement->code.lambda_func.parameter_list;
            func_tmp->the_var = copy_var_list(the_var);
            func_tmp->type = customize;  // func by user
            func_tmp->is_class = false;
            func_tmp->is_lambda = true;

            return_value.value.type = FUNC_value;
            return_value.value.value.func_value = func_tmp;
            return_value.u = statement_end;
            break;
        }
        case set_class:{
            puts("----set class----");
            GWARF_result class_value;
            class_object *class_tmp = malloc(sizeof(class_object));

            class_tmp->the_var = make_var_base(make_hash_var());  // make class var list
            class_value.value.type = CLASS_value;
            class_value.value.value.class_value = class_tmp;

            // 获取father  -- append_by_var_list[拼凑]
            GWARF_result father_tmp;
            parameter *tmp_s = the_statement->code.set_class.father_list;
            if(tmp_s != NULL){
                while(1){
                    father_tmp = traverse(tmp_s->u.value, the_var, false);  // 执行
                    if(is_error(&father_tmp)){  // Name Error错误
                        // puts("STOP:: Name No Found!");
                        return_value = father_tmp;
                        break;
                    }
                    else if(is_space(&father_tmp)){
                        return_value = father_tmp;
                        break;
                    }
                    if(father_tmp.value.type == CLASS_value){  // 可以通过class继承, 也可以通过object.cls继承
                        append_by_var_list(class_tmp->the_var, father_tmp.value.value.class_value->the_var);
                    }
                    else if(father_tmp.value.type == OBJECT_value){
                        append_by_var_list(class_tmp->the_var, father_tmp.value.value.object_value->cls);
                    }
                    if (tmp_s->next == NULL){  // the last
                        break;
                    }
                    tmp_s = tmp_s->next;
                }
            }
            else{
                var *object_tmp = find_var(the_var, 0, "object");
                if(object_tmp != NULL){
                    father_tmp.value = object_tmp->value;
                    append_by_var_list(class_tmp->the_var, father_tmp.value.value.class_value->the_var);
                }
                else{
                    // TODO::返回error -> var_list错误
                }
            }

            class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  //TODO::class_tmp->out_var = copy_var_list(the_var);
            // 执行done
            statement *tmp = the_statement->code.set_class.done;
            GWARF_result result;
            while(1){
                if(tmp == NULL){
                    break;  // off
                }
                read_statement(tmp, the_var, class_tmp->the_var);
                tmp = tmp->next;
            }

            assignment_statement(the_statement->code.set_class.var, the_var,login_var, class_value);  // 注册class 的 位置
            puts("----stop set class----");
            // 无返回值
            break;
        }
        case break_cycle:
            return_value.u = cycle_break;
            return_value.value.type = INT_value;
            if(the_statement->code.break_cycle.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.break_cycle.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case broken:
            return_value.u = code_broken;
            return_value.value.type = INT_value;
            if(the_statement->code.broken.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.broken.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case continue_cycle:
            return_value.u = cycle_continue;
            return_value.value.type = INT_value;
            if(the_statement->code.continue_cycle.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.continue_cycle.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case continued:
            return_value.u = code_continued;
            return_value.value.type = INT_value;
            if(the_statement->code.continued.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.continued.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case restart:
            return_value.u = cycle_restart;
            return_value.value.type = INT_value;
            if(the_statement->code.restart.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.restart.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case restarted:
            return_value.u = code_restarted;
            return_value.value.type = INT_value;
            if(the_statement->code.restarted.times == NULL){
                return_value.value.value.int_value = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.restarted.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.value.value.int_value = int_tmp;
            }
            break;
        case return_code:
            return_value.u = return_def;
            if(the_statement->code.return_code.times == NULL){
                return_value.return_times = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.return_code.times, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    int_tmp = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    int_tmp = (int)tmp_result.value.value.double_value;
                }
                else{
                    int_tmp = 0;
                }
                return_value.return_times = int_tmp;
            }
            if(the_statement->code.return_code.value == NULL){  // return NULL
                return_value.value.type = NULL_value;
                return_value.value.value.double_value = 0;
            }
            else{
                GWARF_result tmp_result = traverse(the_statement->code.return_code.value, the_var, false);
                if(is_error(&tmp_result)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_result;
                    break;
                }
                else if(is_space(&tmp_result)){
                    return_value = tmp_result;
                    break;
                }
                return_value.value = to_object(tmp_result.value, the_var);
            }
            break;
        case rewent:
            return_value.u = code_rewent;  // rego but not now
            break;
        case rego:
            return_value.u = code_rego;  // rego now
            break;
        case set_default:{
            char *name = the_statement->code.set_default.name;
            int base_from = 0;
            GWARF_result tmp_result, tmp_object = traverse(the_statement->code.set_default.times, the_var, false);
            if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return_value = tmp_object;
                    break;
                }
                else if(is_space(&tmp_object)){
                    return_value = tmp_object;
                    break;
                }
            tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
            if(tmp_result.value.type == INT_value){
                base_from = tmp_result.value.value.int_value;
            }
            else if(tmp_result.value.type == NUMBER_value){
                base_from = (int)tmp_result.value.value.double_value;
            }
            else{
                base_from = 0;
            }

            append_default_var_base(name, base_from, the_var->default_list);
            printf("set_default for %s\n", name);
            break;
        }
        case set_global:{
            char *name = the_statement->code.set_global.name;
            int base_from = get_var_list_len(the_var);
            append_default_var_base(name, base_from, the_var->default_list);
            printf("global for %s\n", name);
            break;
        }
        case set_nonlocal:{
            char *name = the_statement->code.set_global.name;
            append_default_var_base(name, 1, the_var->default_list);
            printf("nonlocal for %s\n", name);
            break;
        }
        case code_block:
            puts("----block code----");
            return_value = block_func(the_statement, the_var);
            puts("----stop block code----");
            break;
        case try_code:
            return_value = try_func(the_statement, the_var);
            break;
        case raise_e:
            return_value = raise_func(the_statement, the_var, true);
            break;
        case throw_e:
            return_value = raise_func(the_statement, the_var, false);
            break;
        case import_class:  // import xxx as xxx 语句
            return_value = import_func(the_statement, the_var);
            break;
        case include_import:  // import xxx as xxx 语句
            return_value = include_func(the_statement, the_var);
            break;
        case assert_e:  // import xxx as xxx 语句
            return_value = assert_func(the_statement, the_var);
            break;
        default:
            puts("default");
            break;
    }
    return return_value;
}

// -----------------include func
GWARF_result include_func(statement *the_statement, var_list *the_var){
    GWARF_result return_value;
    statement *file_statement = the_statement->code.include_import.file;

    GWARF_value file = to_str(traverse(file_statement, the_var, false).value, the_var);

    // TODO:: 使用链表来存储
    inter *old_global = global_inter;  // 保存旧迭代器
    statement_list *old_statement_base = statement_base;  // 保存statement_base

    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    free(global_inter->global_var);  // 不需要新的the_var
    global_inter->global_var = the_var->hash_var_base;
    statement_base = make_statement_base(global_inter->global_code);
    
    parser(file.value.string);
    printf("----start run----\n");
    traverse_global(global_inter->global_code, the_var);
    printf("code end...\n");

    global_inter = old_global;  // 变回旧迭代器
    statement_base = old_statement_base;  // 变回statement_base

    return_value.u = statement_end;
    return_value.value.type = NULL_value;
    return_value.value.value.int_value = 0;
    return return_value;
}

// -----------------import func
GWARF_result import_func(statement *the_statement, var_list *the_var){
    GWARF_result return_value;
    statement *file_statement = the_statement->code.import_class.file;
    
    GWARF_value file = to_str(traverse(file_statement, the_var, false).value, the_var);

    // TODO:: 使用链表来存储
    inter *old_global = global_inter;  // 保存旧迭代器
    statement_list *old_statement_base = statement_base;  // 保存statement_base

    global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
    var_list *new_the_var = make_var_base(global_inter->global_var);
    statement_base = make_statement_base(global_inter->global_code);
    
    login(new_the_var);
    
    parser(file.value.string);
    printf("----start run----\n");
    traverse_global(global_inter->global_code, new_the_var);
    printf("code end...\n");

    global_inter = old_global;  // 保存旧迭代器
    statement_base = old_statement_base;  // 保存statement_base

    GWARF_result import_result;
    import_result.value.type = CLASS_value;
    
    class_object *class_tmp = malloc(sizeof(class_object));
    class_tmp->the_var = new_the_var;  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var

    import_result.value.value.class_value = class_tmp;
    assignment_statement(the_statement->code.import_class.var, the_var, the_var, import_result);

    return_value.u = statement_end;
    return_value.value.type = NULL_value;
    return_value.value.value.int_value = 0;
    return return_value;
}

// -----------------if func

GWARF_result if_func(if_list *if_base, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    if_list *start;
    again: start = if_base;
    bool rego = false;  // switch...case...
    while(1){
        if(start->condition  == NULL){  // else
            else_restart:
            puts("----else----");
            value = traverse(start->done, the_var, true);
            puts("----stop else----");
            
            // restarted操作
            // TODO::可以检查值类型，如果不正确则是解释器错误
            if(value.u == code_restarted){
                if(value.value.type != INT_value){
                    // printf("Code Warrning: Bad Type Number for restart(ed), reset to zero");
                    value.value.type = INT_value;
                    value.value.value.int_value = 0;
                }
                if(value.value.value.int_value <= 0){
                    puts("----restarted real----");
                    value.u = statement_end;
                    goto else_restart;
                }
                else{
                    value.value.value.int_value -= 1;
                    break;
                }
            }

            // continued操作
            if(value.u == code_continued){
                if(value.value.type != INT_value){
                    // printf("Code Warrning: Bad Type Number for continue(ed), reset to zero");
                    value.value.type = INT_value;
                    value.value.value.int_value = 0;
                }
                if(value.value.value.int_value <= 0){
                    puts("----if continue real----");
                    value.u = statement_end;
                    goto again;
                }
                else{
                    value.value.value.int_value -= 1;
                }
                break;
            }

            // broken操作
            if(value.u == code_broken){
                if(value.value.type != INT_value){
                    // printf("Code Warrning: Bad Type Number for break(broken), reset to zero");
                    value.value.type = INT_value;
                    value.value.value.int_value = 0;
                }
                if(value.value.value.int_value <= 0){
                    value.u = statement_end;  // 正常设置[正常语句结束]
                }
                else{
                    value.value.value.int_value -= 1;
                }
                break;
            }

            // rego操作
            // else层的rego和rewent是可以往上层遗传的[也就是else如果显式指定rego和rewent是会遗传的，但是如果是if或elif指定rego是不会遗传的]
            if((value.u == code_rewent) || (value.u == code_rego)){
                ;
            }

            break;  // else not next and don't need rego
        }
        else{  // not else
            bool condition;
            GWARF_result tmp_result = traverse(start->condition, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                value = tmp_result;
                break;
            }
            else if(is_space(&tmp_result)){
                value = tmp_result;
                break;
            }

            condition = to_bool(tmp_result.value);
            printf("if condition = %d\n", condition);
            if(rego || (condition)){  // condition run success or rego(condition won't do) bug rewent can
                if_restart:
                puts("----if----");
                value = traverse(start->done, the_var, true);
                puts("----stop if----");

                // restarted操作
                if(value.u == code_restarted){
                    if(value.value.type != INT_value){
                        // printf("Code Warrning: Bad Type Number for restart(ed), reset to zero");
                        value.value.type = INT_value;
                        value.value.value.int_value = 0;
                    }
                    if(value.value.value.int_value <= 0){
                        puts("----restarted real----");
                        value.u = statement_end;
                        goto if_restart;
                    }
                    else{
                        value.value.value.int_value -= 1;
                        break;
                    }
                }
                
                // continued操作 [设在在rewent和rego前面]
                if(value.u == code_continued){
                    if(value.value.type != INT_value){
                        // printf("Code Warrning: Bad Type Number for continue(ed), reset to zero");
                        value.value.type = INT_value;
                        value.value.value.int_value = 0;
                    }
                    if(value.value.value.int_value <= 0){
                        puts("----if continue real----");
                        value.u = statement_end;
                        goto again;
                    }
                    else{
                        value.value.value.int_value -= 1;
                    }
                    break;
                }

                // broken操作
                if(value.u == code_broken){
                    if(value.value.type != INT_value){
                        // printf("Code Warrning: Bad Type Number for break(broken), reset to zero");
                        value.value.type = INT_value;
                        value.value.value.int_value = 0;
                    }
                    value.value.value.int_value -= 1;
                    if(value.value.value.int_value < 0){
                        value.u = statement_end;  // 正常设置[正常语句结束]
                    }
                    break;
                }
                
                // rego操作
                if((value.u == code_rewent) || (value.u == code_rego)){
                    value.u = statement_end;  // 设置为正常语句
                    rego = true;
                }

                // not restarted -> if is rego
                if(!rego){
                    break;  // don't rego
                }
            }
        }
        if(start->next  == NULL){  // not next
            break;
        }
        start = start->next;
    }
    if((value.u == cycle_continue) || (value.u == cycle_restart) || (value.u == cycle_break)){  // if不处理也不计入层次 同break一样
        ;
    }
    return value;
}

// -----------------for func
GWARF_result for_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    hash_var *tmp = make_hash_var();  // base_var
    the_var = append_var_list(tmp, the_var);
    bool condition;
    if(the_statement->code.for_cycle.first != NULL){
        GWARF_result tmp_result = traverse(the_statement->code.for_cycle.first, the_var, false); // first to do
        if(is_error(&tmp_result)){  // Name Error错误
            // puts("STOP:: Name No Found!");
            value = tmp_result;
            return value;
        }
        else if(is_space(&tmp_result)){
            value = tmp_result;
            return value;
        }
    }
    while (1){
        if(the_statement->code.for_cycle.condition != NULL){  // 检查是否存在循环条件
            GWARF_result tmp_result = traverse(the_statement->code.for_cycle.condition, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                value = tmp_result;
                goto return_value;
            }
            else if(is_space(&tmp_result)){
                value = tmp_result;
                goto return_value;
            }
            condition = to_bool(tmp_result.value);
            printf("for condition = %d\n", condition);
            if(!condition){
                break;
            }
        }
        restart_again: 
        puts("----for----");
        value = traverse(the_statement->code.for_cycle.done, the_var, false);

        //break操作
        if((value.u == cycle_break) || (value.u == code_broken)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;  // 正常设置[正常语句结束]
            }
            else{
                value.value.value.int_value -= 1;
            }
            break;  // break don't need after do
        }
        puts("----stop for----");

        // after do
        if(the_statement->code.for_cycle.after != NULL){
            GWARF_result tmp_result = traverse(the_statement->code.for_cycle.after, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                value = tmp_result;
                goto return_value;
            }
            else if(is_space(&tmp_result)){
                value = tmp_result;
                goto return_value;
            }
        }
        // continue操作
        if((value.u == cycle_continue) || (value.u == code_continued)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                puts("----continue real----");
                value.u = statement_end;
                continue;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }

        // restart操作
        if((value.u == cycle_restart) || (value.u == code_restarted)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                puts("----restart real----");
                value.u = statement_end;
                goto restart_again;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }
    }
    return_value: 
    the_var = free_var_list(the_var);  // free the new var
    return value;
}

// -----------------assert func
GWARF_result assert_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result error_value;
    GWARF_value info;

    GWARF_result tmp_result = traverse(the_statement->code.assert_e.condition, the_var, false);
    if(is_error(&tmp_result)){  // Name Error错误
        error_value = tmp_result;
        goto return_value;
    }
    else if(is_space(&tmp_result)){
        error_value = tmp_result;
        goto return_value;
    }
    if(to_bool(tmp_result.value)){
        error_value.u = statement_end;
        error_value.value.type = NULL_value;
        error_value.value.value.int_value = 0;
        goto return_value;
    }

    GWARF_result tmp_info = traverse(the_statement->code.assert_e.info, the_var, false);
    if(is_error(&tmp_info)){  // 遇到错误->执行except语句[不需要再检查break...]
        error_value = tmp_info;
        goto return_value;  // raise执行时发生错误
    }
    if(is_space(&tmp_info)){
        error_value = tmp_info;
        goto return_value;
    }

    info = to_str(tmp_info.value, the_var);
    error_value = to_error(info.value.string , "AssertException", the_var);
    error_value.u = error;

    return_value: return error_value;
}

// -----------------raise func
GWARF_result raise_func(statement *the_statement, var_list *the_var, bool not_class){  // read the statement list with case to run by func
    GWARF_result error_value;
    GWARF_value info;

    if(not_class){  // raise
        error_value = traverse(the_statement->code.raise_e.done, the_var, false);
        info = to_str(traverse(the_statement->code.raise_e.info, the_var, false).value, the_var);
    }
    else{  // raise
        GWARF_value tmp;
        tmp.type = STRING_value;
        tmp.value.string = "throw by user";
        error_value = traverse(the_statement->code.throw_e.done, the_var, false);
        info = to_str(tmp, the_var);
    }

    // restart操作[和continue效果相同]

    if(is_error(&error_value)){  // 遇到错误->执行except语句[不需要再检查break...]
        goto return_value;  // raise执行时发生错误
    }
    if(is_space(&error_value)){
        goto return_value;
    }

    error_value.u = error;
    error_value.error_info = info.value.string;

    if(error_value.value.type == OBJECT_value){
        ;  // 本身就是object
    }
    else if(error_value.value.type == CLASS_value && not_class){  // class类型
        error_value.value = call_back_core(error_value, the_var, pack_value_parameter(info)).value;
    }
    else{
        error_value.value = to_object(error_value.value, the_var);  // 直接返回
    }

    return_value: return error_value;
}

// -----------------try func
GWARF_result try_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;

    hash_var *tmp = make_hash_var();  // base_var
    the_var = append_var_list(tmp, the_var);

    again: 
    puts("----try----");
    value = traverse(the_statement->code.try_code.try, the_var, false);
    puts("----stop try----");

    // restart操作[和continue效果相同]

    if(is_error(&value)){  // 遇到错误->执行except语句[不需要再检查break...]
        assignment_statement(the_statement->code.try_code.var, the_var, the_var, value);
        puts("----except----");
        value = traverse(the_statement->code.try_code.except, the_var, false);
        puts("----stop except----");
    }

    if(value.u == code_restarted){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            puts("----restarted real----");
            value.u = statement_end;
            goto again;
        }
        else{
            value.value.value.int_value -= 1;
        }
    }
    
    // continued操作
    if(value.u == code_continued){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            puts("----block continue real----");
            value.u = statement_end;
            goto again;
        }
        else{
            value.value.value.int_value -= 1;
        }
    }

    // broken操作
    if(value.u == code_broken){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            value.u = statement_end;  // 正常设置[正常语句结束]
        }
        else{
            value.value.value.int_value -= 1;
        }
    }
    the_var = free_var_list(the_var);  // free the new var
    return value;
}


// -----------------block func

GWARF_result block_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    again: 
    puts("----block----");
    value = traverse(the_statement->code.code_block.done, the_var, true);
    puts("----stop block----");

    // restart操作[和continue效果相同]
    if(value.u == code_restarted){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            puts("----restarted real----");
            value.u = statement_end;
            goto again;
        }
        else{
            value.value.value.int_value -= 1;
        }
    }
    
    // continued操作
    if(value.u == code_continued){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            puts("----block continue real----");
            value.u = statement_end;
            goto again;
        }
        else{
            value.value.value.int_value -= 1;
        }
    }

    // broken操作
    if(value.u == code_broken){
        if(value.value.type != INT_value){
            value.value.type = INT_value;
            value.value.value.int_value = 0;
        }
        if(value.value.value.int_value <= 0){
            value.u = statement_end;  // 正常设置[正常语句结束]
        }
        else{
            value.value.value.int_value -= 1;
        }
    }
    return value;
}

// -----------------forin func

GWARF_result forin_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    hash_var *tmp = make_hash_var();  // base_var
    the_var = append_var_list(tmp, the_var);
    
    GWARF_result tmp_result = traverse(the_statement->code.for_in_cycle.iter, the_var, false);  // 取得迭代器
    if(is_error(&tmp_result)){  // Name Error错误
        // puts("STOP:: Name No Found!");
        value = tmp_result;
        goto return_value;
    }
    else if(is_space(&tmp_result)){
        value = tmp_result;
        goto return_value;
    }
    
    // puts("[tag 1]goto for in");
    GWARF_value iter_value = get__iter__(&(tmp_result.value), the_var).value;  // 获取迭代object，一般是返回self
    while (1){
        GWARF_result tmp_next = get__next__(&(iter_value), the_var);// 执行__next__的返回值
        if(is_error(&tmp_next)){  // TODO:: 检查是否为IterException
            value.u = statement_end;
            value.value.type = NULL_value;
            value.value.value.int_value = 0;
            break;  // goto return_value;
        }
        else{
            assignment_statement(the_statement->code.for_in_cycle.var, the_var, the_var,tmp_next);  // 赋值
        }
        restart_again: 
        puts("----for in----");
        value = traverse(the_statement->code.for_in_cycle.done, the_var, false);
        puts("----stop for in----");

        // break的操作
        if((value.u == cycle_break) || (value.u == code_broken)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;  // 正常设置[正常语句结束]
            }
            else{
                value.value.value.int_value -= 1;
            }
            break;
        }

        // continue的操作
        if((value.u == cycle_continue) || (value.u == code_continued)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;
                continue;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }

        // restart的操作
        if((value.u == cycle_restart) || (value.u == code_restarted)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;
                goto restart_again;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }
    }
    return_value: 
    the_var = free_var_list(the_var);  // free the new var
    return value;
}

// -----------------while func

GWARF_result while_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    bool do_while = the_statement->code.while_cycle.first_do;  // 如果是do_while 则返回true

    hash_var *tmp = make_hash_var();  // base_var
    the_var = append_var_list(tmp, the_var);

    bool condition;
    while (1){
        if(!do_while){  // do_while 为 true的时候跳过条件检查
            GWARF_result tmp_result = traverse(the_statement->code.while_cycle.condition, the_var, false);
            if(is_error(&tmp_result)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                value = tmp_result;
                goto return_value;
            }
            else if(is_space(&tmp_result)){
                value = tmp_result;
                goto return_value;
            }
            condition = to_bool(tmp_result.value);
            printf("while condition = %d\n", condition);
            if(!condition){
                break;
            }
        }
        else{
            do_while = false;  // 只有第一次循环可以跳过检查
        }
        
        restart_again: 
        puts("----while----");
        value = traverse(the_statement->code.while_cycle.done, the_var, false);
        puts("----stop while----");

        // break的操作
        if((value.u == cycle_break) || (value.u == code_broken)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;  // 正常设置[正常语句结束]
            }
            else{
                value.value.value.int_value -= 1;
            }
            break;
        }

        // continue的操作
        if((value.u == cycle_continue) || (value.u == code_continued)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;
                continue;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }

        // restart的操作
        if((value.u == cycle_restart) || (value.u == code_restarted)){
            if(value.value.type != INT_value){
                value.value.type = INT_value;
                value.value.value.int_value = 0;
            }
            if(value.value.value.int_value <= 0){
                value.u = statement_end;
                goto restart_again;
            }
            else{
                value.value.value.int_value -= 1;
                break;
            }
        }
    }
    return_value: 
    the_var = free_var_list(the_var);  // free the new var
    return value;
}

// -----------------operation func

GWARF_result operation_func(statement *the_statement, var_list *the_var, var_list *login_var){  // read the statement list with case to run by func
    GWARF_result value, left_result, right_result;
    int func_type = the_statement->code.operation.type;
    if(func_type != ASSIGnMENT_func && func_type != AND_func && func_type != OR_func)
    {
        left_result = traverse(the_statement->code.operation.left_exp, the_var, false);  // NEGATIVE_func等的left为NULL相当与不执行
        if(is_error(&left_result)){
            return left_result;
        }
        else if(is_space(&left_result)){
            return left_result;
        }
    }
    right_result = traverse(the_statement->code.operation.right_exp, the_var, false);
    if(is_error(&right_result))
    {
        return right_result;
    }
    else if(right_result.u != return_def && is_space(&right_result)){
        return right_result;
    }

    switch (func_type)  // 获取运算类型
    {
        case ADD_func:
            value = add_func(left_result, right_result, the_var);
            break;
        case SUB_func:
            value = sub_func(left_result, right_result, the_var);
            break;
        case MUL_func:
            value = mul_func(left_result, right_result, the_var);
            break;
        case DIV_func:
            value = div_func(left_result, right_result, the_var);
            break;
        case AADD_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, add_func(left_result, right_result, the_var));
            break;
        case ASUB_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, sub_func(left_result, right_result, the_var));
            break;
        case AMUL_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, mul_func(left_result, right_result, the_var));
            break;
        case ADIV_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, div_func(left_result, right_result, the_var));
            break;
        case AMOD_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, mod_func(left_result, right_result, the_var));
            break;
        case AINTDIV_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, int_div_func(left_result, right_result, the_var));
            break;
        case APOW_func:
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, pow_func(left_result, right_result, the_var));
            break;
        case LADD_func:  // a++
            right_result.u = statement_end;
            right_result.value.type = INT_value;
            right_result.value.value.int_value = 1;
            assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, add_func(left_result, right_result, the_var));
            value = left_result;  // 先返回值，后自增
            break;
        case FADD_func:  // ++a
            left_result.u = statement_end;
            left_result.value.type = INT_value;
            left_result.value.value.int_value = 1;
            value = assignment_statement(the_statement->code.operation.right_exp, the_var, login_var, add_func(left_result, right_result, the_var));  // 先自增，后返回值
            break;
        case LSUB_func:  // a--
            right_result.u = statement_end;
            right_result.value.type = INT_value;
            right_result.value.value.int_value = 1;
            assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, sub_func(left_result, right_result, the_var));
            value = left_result;  // 先返回值，后自增
            break;
        case FSUB_func:  // --a
            left_result.u = statement_end;
            left_result.value.type = INT_value;
            left_result.value.value.int_value = 1;
            value = assignment_statement(the_statement->code.operation.right_exp, the_var, login_var, sub_func(right_result, left_result, the_var));  // 先自增，后返回值
            break;
        case NEGATIVE_func:
            value = negative_func(right_result, the_var);
            break;
        case ASSIGnMENT_func:{  // because the var char, we should ues a {} to make a block[name space] for the tmp var;
            value = assignment_statement(the_statement->code.operation.left_exp, the_var, login_var, right_result);
            break;
        }
        case EQUAL_func:
            value = equal_func(left_result, right_result, the_var, 0);
            break;
        case MORE_func:
            value = equal_func(left_result, right_result, the_var, 1);
            break;
        case LESS_func:
            value = equal_func(left_result, right_result, the_var, 2);
            break;
        case MOREEQ_func:
            value = equal_func(left_result, right_result, the_var, 3);
            break;
        case LESSEQ_func:
            value = equal_func(left_result, right_result, the_var, 4);
            break;
        case NOTEQ_func:
            value = equal_func(left_result, right_result, the_var, 5);
            break;
        case POW_func:
            value = pow_func(left_result, right_result, the_var);
            break;
        case LOG_func:
            value = log_func(left_result, right_result, the_var);
            break;
        case SQRT_func:
            value = sqrt_func(left_result, right_result, the_var);
            break;
        case AND_func:
            value = and_func(the_statement->code.operation.left_exp, the_statement->code.operation.right_exp, the_var);
            break;
        case OR_func:
            value = or_func(the_statement->code.operation.left_exp, the_statement->code.operation.right_exp, the_var);
            break;
        case NOT_func:
            value = not_func(right_result, the_var);
            break;
        case MOD_func:
            value = mod_func(left_result, right_result, the_var);
            break;
        case INTDIV_func:
            value = int_div_func(left_result, right_result, the_var);
            break;
        case BITAND_func:
            value = bit_and_func(left_result, right_result, the_var);
            break;
        case BITOR_func:
            value = bit_or_func(left_result, right_result, the_var);
            break;
        case BITNOTOR_func:
            value = bit_notor_func(left_result, right_result, the_var);
            break;
        case BITRIGHT_func:
            value = bit_right_func(left_result, right_result, the_var);
            break;
        case BITLEFT_func:
            value = bit_left_func(left_result, right_result, the_var);
            break;
        case BITNOT_func:
            value = bit_not_func(right_result, the_var);
            break;
        default:
            break;
    }
    value.u = statement_end;  // 正常设置[正常语句结束]
    value.value = to_object(value.value, the_var);  // 返回类型是object[不下放到add func等]
    return value;
}

GWARF_result assignment_statement(statement *the_statement, var_list *the_var, var_list *login_var, GWARF_result right_result){
    GWARF_result value;
    value.u = statement_end;
    value.value.type = NULL_value;
    value.value.value.int_value = 0;
    if(right_result.value.type == OBJECT_value || right_result.value.type == CLASS_value){
        right_result = get__assignment__(&(right_result.value), the_var);
        if(is_error(&right_result)){  // Name Error错误
            return right_result;
        }
        else if(is_space(&right_result)){
            return right_result;
        }
    }

    if(the_statement->type == base_var){  // 通过base_var赋值
        char *left = the_statement->code.base_var.var_name;  // get var name but not value
        int from = 0;
        if(the_statement->code.base_var.from == NULL){
            from = 0;
        }
        else{
            GWARF_result tmp_result, tmp_object = traverse(the_statement->code.base_var.from, the_var, false);
            if(is_error(&tmp_object)){  // Name Error错误
                // puts("STOP:: Name No Found!");
                return tmp_object;
            }
            else if(is_space(&tmp_object)){
                return tmp_object;
            }
            tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
            if(tmp_result.value.type == INT_value){
                from = tmp_result.value.value.int_value;
            }
            else if(tmp_result.value.type == NUMBER_value){
                from = (int)tmp_result.value.value.double_value;
            }
            else{
                from = 0;
            }
        }

        value = assignment_func(left, right_result, login_var, from);
    }
    else if(the_statement->type == point){  // 通过point赋值
        GWARF_result tmp_result = traverse(the_statement->code.point.base_var, the_var, false);  // 不用取value
        if(is_error(&tmp_result)){  // Name Error错误
            // puts("STOP:: Name No Found!");
            return tmp_result;
        }
        else if(is_space(&tmp_result)){
            return tmp_result;
        }
        GWARF_value base_the_var = tmp_result.value;  // 不用取value
        if((the_statement->code.point.child_var)->type == base_var){
            char *left = (the_statement->code.point.child_var)->code.base_var.var_name;
            int from = 0;
            if((the_statement->code.point.child_var)->code.base_var.from == NULL){
                from = 0;
            }
            else{
                GWARF_result tmp_result, tmp_object = traverse((the_statement->code.point.child_var)->code.base_var.from, the_var, false);
                if(is_error(&tmp_object)){  // Name Error错误
                    // puts("STOP:: Name No Found!");
                    return tmp_object;
                }
                else if(is_space(&tmp_object)){
                    return tmp_object;
                }
                tmp_result = get__value__(&(tmp_object.value), the_var);  // 从object中提取value
                if(tmp_result.value.type == INT_value){
                    from = tmp_result.value.value.int_value;
                }
                else if(tmp_result.value.type == NUMBER_value){
                    from = (int)tmp_result.value.value.double_value;
                }
                else{
                    from = 0;
                }
            }
            value = assignment_func(left, right_result, base_the_var.value.object_value->the_var, from);
        }
        else{
            goto the_else;
        }
    }
    else if(the_statement->type == down){  // 通过down赋值
        GWARF_result tmp_result = traverse(the_statement->code.down.base_var, the_var, false), get;  // 不用取value
        if(is_error(&tmp_result)){  // Name Error错误
            // puts("STOP:: Name No Found!");
            return tmp_result;
        }
        else if(is_space(&tmp_result)){
            return tmp_result;
        }
        GWARF_value base_the_var = tmp_result.value;  // 不用取value
        if(base_the_var.type == CLASS_value){  // is class so that can use "."
            GWARF_result child_value = traverse(the_statement->code.down.child_var, the_var, false);  // 作为参数
            var *tmp = find_var(base_the_var.value.class_value->the_var, 0, "__set__");
            if(tmp != NULL){
                get.value = tmp->value;
                get.father = &base_the_var;  // 设置father
                parameter *tmp = pack_value_parameter(child_value.value);
                tmp->next = pack_value_parameter(right_result.value);
                value = call_back_core(get, the_var, tmp);
                goto the_else;
            }
        }
        else if(base_the_var.type == OBJECT_value){
            GWARF_result child_value = traverse(the_statement->code.down.child_var, the_var, false);  // 作为参数
            var *tmp = find_var(base_the_var.value.object_value->the_var, 0, "__set__");
            if(tmp != NULL){
                get.value = tmp->value;
                get.father = &base_the_var;  // 设置father
                parameter *tmp = pack_value_parameter(child_value.value);
                tmp->next = pack_value_parameter(right_result.value);
                value = call_back_core(get, the_var, tmp);
            }
            else{
                goto the_else;
            }
        }
        else{
            goto the_else;
        }
    }
    else{ 
        the_else: puts("Bad Assignment");
    }
    return value;
}

GWARF_result call_back(statement *the_statement, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result get = traverse(the_statement->code.call.func, the_var, false), result;
    if(is_error(&get)){  // Name Error错误
        // puts("STOP:: Name No Found!");
        return get;
    }
    else if(is_space(&get)){
        return get;
    }
    result = call_back_core(get, the_var, the_statement->code.call.parameter_list);
    result.value = to_object(result.value, the_var);  // 返回类型是object
    return result;
}

GWARF_result login_var(var_list *the_var, var_list *old_var_list, parameter *tmp_x, parameter *tmp_s){
    GWARF_result return_result;
    return_result.u = statement_end;
    return_result.value.type = NULL_value;
    return_result.value.value.int_value = 0;

    int assignment_type = 0;  // 0-根据tmp_x进行赋值，1-根据tmp_s赋值
    var_list *tmp_var = make_var_base(make_hash_var());  // 为1-模式准备

    while(1){
        if ((tmp_x == NULL)&&(tmp_s == NULL)){  // the last
            break;
        }
        if(assignment_type == 0){  // 对位赋值
            if ((tmp_x == NULL)&&(tmp_s != NULL)){  // 参数过多
                printf("Warning!!!\n");
                break;
            }
            else if ((tmp_x != NULL)&&(tmp_s == NULL)){  // 使用默认值
                while(1){  // 如果是name_value类型则继续赋值
                    if(tmp_x == NULL){
                        break;
                    }
                    else if(tmp_x->type == name_value){
                        GWARF_result tmp = traverse(tmp_x->u.value, the_var, false);  // 执行形参
                        if(is_error(&tmp) || is_space(&tmp)){
                            return tmp;
                        }
                        assignment_func(tmp_x->u.name, tmp, the_var, 0);
                        tmp_x = tmp_x->next;  // get the next to iter
                    }
                    else if(tmp_x->type == put_args){  // args默认为[]
                        GWARF_result func_result;
                        var *list_init;
                        func_result.u = statement_end;
                        list_init = find_var(old_var_list, 0, "list");
                        if(list_init != NULL){
                            func_result.value = list_init->value;
                        }
                        assignment_func(tmp_x->u.name, call_back_core(func_result, old_var_list, NULL), the_var, 0);
                        tmp_x = tmp_x->next;  // get the next to iter
                    }
                    else{
                        printf("warning!!!\n");
                        break;
                    }

                }
                break;
            }
        }
        else if(assignment_type == 1){  // 根据实参  a = b 来赋值
            if ((tmp_x != NULL)&&(tmp_s == NULL)){  // 实参录入完毕
                while(1){
                    if(tmp_x == NULL){
                        break;  // 形参录入完毕
                    }
                    var *tmp_x_var = find_var(tmp_var, 0, tmp_x->u.name);
                    if(tmp_x_var != NULL){
                        GWARF_result tmp_result;
                        tmp_result.value = tmp_x_var->value;
                        assignment_func(tmp_x->u.name, tmp_result, the_var, 0);
                    }
                    else if(tmp_x->type == name_value){
                        GWARF_result tmp = traverse(tmp_x->u.value, the_var, false);  // 执行形参
                        if(is_error(&tmp) || is_space(&tmp)){
                            return tmp;
                        }
                        assignment_func(tmp_x->u.name, tmp, the_var, 0);
                    }
                    else{
                        printf("Warning!!!");
                        break;
                    }
                    tmp_x = tmp_x->next;
                }
                break;
            }
        }

        GWARF_result tmp = traverse(tmp_s->u.value, old_var_list, false);  // 不需要取__value__
        if(is_error(&tmp)){
            return tmp;
        }
        else if(is_space(&tmp)){
            return tmp;
        }

        if(assignment_type == 1 || tmp_s->type == name_value){
            if(tmp_s->type != name_value){
                printf("Warning!!!");  // 进入了模式1, 但不是name_value
                break;
            }
            assignment_type = 1;
            assignment_func(tmp_s->u.name, tmp, tmp_var, 0);  // 先赋值到tmp_var上
            tmp_s = tmp_s->next;
        }
        else if(tmp_s->type == put_args){  // assignment_type不在1模式
            parameter *before = tmp_s, *after = tmp_s->next;
            GWARF_value iter_value = get__iter__(&(tmp.value), old_var_list).value;  // 获取迭代object，一般是返回self
            while (1){
                GWARF_result tmp_next = get__next__(&(iter_value), old_var_list);// 执行__next__的返回值
                if(is_error(&tmp_next)){  // TODO:: 检查是否为IterException
                    break;  // goto return_value;
                }
                if(is_space(&tmp_next)){  // TODO:: 检查是否为IterException
                    return tmp_next;
                }
                before->next = pack_value_parameter(tmp_next.value);
                before = before->next;
            }
            before->next = after;
            tmp_s = tmp_s->next;  // 实参去下一位, 形参不变
        }
        else if(assignment_type == 0 && tmp_x->type == put_args){
            // 放入list中
            GWARF_result list_tmp;
            list_tmp.value = to_object(parameter_to_list(tmp_s, old_var_list), old_var_list);
            assignment_func(tmp_x->u.name, list_tmp, the_var, 0);
            assignment_type = 1;  // 进入根据实参赋值模式
            tmp_x = tmp_x->next;
            while(1){
                if(tmp_s == NULL){
                    break;
                }
                if(tmp_s->type != only_value){
                    break;
                }
                tmp_s = tmp_s->next;
            }
        }
        else if(assignment_type == 0){
            assignment_func(tmp_x->u.name, tmp, the_var, 0);
            tmp_x = tmp_x->next;  // get the next to iter
            tmp_s = tmp_s->next;
        }
    }
    return return_result;
}

GWARF_result call_back_core(GWARF_result get, var_list *the_var, parameter *tmp_s){  // the func for add and call from read_statement_list
    GWARF_result result;
    var_list *old_var_list = the_var;
    if(get.value.type == FUNC_value){
        func *func_ = get.value.value.func_value;
        parameter *tmp_x = func_->parameter_list;
        the_var = func_->the_var;
        // tmp_x:形参，tmp_s:实参

        // printf("----address = %d----\n", the_var);
        hash_var *tmp = make_hash_var();  // base_var
        the_var = append_var_list(tmp, the_var);
        // printf("----new address = %d----\n", the_var);

        if(func_->type == customize){  // 用户定义的方法
            // 赋值self
            GWARF_result father;
            if(func_->is_class){
                if(get.father != NULL){
                    father.value = *(get.father);
                    assignment_func(tmp_x->u.name, father, the_var, 0);
                    tmp_x = tmp_x->next;  // get the next to iter
                }
                else{
                    printf("Warning!!!\n");
                    // TODO:: 抛出错误
                }
            }

            GWARF_result tmp_return = login_var(the_var, old_var_list, tmp_x, tmp_s);
            if(tmp_return.u != statement_end){
                the_var = free_var_list(the_var);  // free the new var
                return tmp_return;
            }

            puts("----start func----");
            result = traverse(func_->done, the_var, false);  // 执行func_value->done
            if(is_error(&result)){  // Name Error错误
                the_var = free_var_list(the_var);  // free the new var
                return result;
            }
            else if(is_space(&result)){
                the_var = free_var_list(the_var);  // free the new var
                return result;
            }

            if(func_->is_lambda){
                result.return_times = 0;
                result.u = return_def;
            }
            puts("----stop start func----");
        }
        else{
            result = func_->paser(func_, tmp_s, the_var, get, old_var_list);
        }
        the_var = free_var_list(the_var);  // free the new var
    }
    else if(get.value.type == CLASS_value){  // 生成实例
        the_object *object_tmp = malloc(sizeof(the_object));  // 生成object的空间
        object_tmp->cls = get.value.value.class_value->the_var;
        object_tmp->the_var = append_by_var_list(make_var_base(make_hash_var()), object_tmp->cls);
        GWARF_value tmp;
        tmp.type = OBJECT_value;
        tmp.value.object_value = object_tmp;

        // 执行__init__
        var *init_tmp = find_var(object_tmp->cls, 0, "__init__");
        if(init_tmp != NULL){  // 找到了__init__
            func *func_ = init_tmp->value.value.func_value;
            parameter *tmp_x = func_->parameter_list;
            the_var = func_->the_var;
            // tmp_x:形参，tmp_s:实参

            hash_var *tmp = make_hash_var();  // base_var
            the_var = append_var_list(tmp, the_var);

            if(func_->type == customize){  // 用户定义的方法
                GWARF_result father;
                father.value.type = OBJECT_value;
                father.value.value.object_value = object_tmp;
                if(func_->is_class  == 1){
                    assignment_func(tmp_x->u.name, father, the_var, 0);
                    tmp_x = tmp_x->next;  // get the next to iter
                }

                GWARF_result tmp_return = login_var(the_var, old_var_list, tmp_x, tmp_s);
                if(tmp_return.u != statement_end){
                    the_var = free_var_list(the_var);  // free the new var
                    return tmp_return;
                }

                puts("----start func----");
                {
                    GWARF_result tmp = traverse(func_->done, the_var, false);  // 执行func_value->done
                    if(is_error(&tmp)){  // Name Error错误
                        // puts("STOP:: Name No Found!");\
                        the_var = free_var_list(the_var);  // free the new var
                        return tmp;
                    }
                    else if(is_space(&tmp)){
                        the_var = free_var_list(the_var);  // free the new var
                        return tmp;
                    }
                }
                puts("----stop start func----");
            }
            else{
                GWARF_result tmp_get;
                GWARF_value father;
                father.type = OBJECT_value;
                father.value.object_value = object_tmp;
                tmp_get.father = &father;
                GWARF_result tmp = func_->paser(func_, tmp_s, the_var, tmp_get, old_var_list);   // 返回值不记录
                if(is_error(&tmp)){  // Name Error错误
                    the_var = free_var_list(the_var);  // free the new var
                    // puts("STOP:: Name No Found!");
                    return tmp;
                }
                else if(is_space(&tmp)){
                    the_var = free_var_list(the_var);  // free the new var
                    return tmp;
                }
            }
            the_var = free_var_list(the_var);  // free the new var
        }
        // 记录返回值
        result.u = statement_end;
        result.value = tmp;
    }
    else if(get.value.type == OBJECT_value){  // 调用__call__方法
        // 执行__init__
        var *call_tmp = find_var(get.value.value.object_value->the_var, 0, "__call__");
        if(call_tmp != NULL){  // 找到了__init__
            func *func_ = call_tmp->value.value.func_value;
            parameter *tmp_x = func_->parameter_list;
            the_var = func_->the_var;
            // tmp_x:形参，tmp_s:实参

            // // printf("----address = %d----\n", the_var);
            hash_var *tmp = make_hash_var();  // base_var
            the_var = append_var_list(tmp, the_var);
            // // printf("----new address = %d----\n", the_var);

            if(func_->type == customize){  // 用户定义的方法
                GWARF_result father;
                father.value.type = OBJECT_value;
                father.value.value.object_value = get.value.value.object_value;
                if(func_->is_class  == 1){
                    assignment_func(tmp_x->u.name, father, the_var, 0);
                    tmp_x = tmp_x->next;  // get the next to iter
                }

                GWARF_result tmp_return = login_var(the_var, old_var_list, tmp_x, tmp_s);
                if(tmp_return.u != statement_end){
                    the_var = free_var_list(the_var);  // free the new var
                    return tmp_return;
                }

                puts("----start func----");
                result = traverse(func_->done, the_var, false);  // 执行func_value->done
                if(is_error(&result)){  // Name Error错误
                    the_var = free_var_list(the_var);  // free the new var
                    return result;
                }
                else if(is_space(&result)){
                    the_var = free_var_list(the_var);  // free the new var
                    return result;
                }

                if(func_->is_lambda){
                    result.return_times = 0;
                    result.u = return_def;
                }
                puts("----stop start func----");
            }
            else{  // 官方方法
                GWARF_result tmp_get;
                GWARF_value father;
                father.type = OBJECT_value;
                father.value.object_value = get.value.value.object_value;
                tmp_get.father = &father;
                GWARF_result tmp = func_->paser(func_, tmp_s, the_var, tmp_get, old_var_list);   // 返回值不记录
                if(is_error(&tmp)){  // Name Error错误
                    the_var = free_var_list(the_var);  // free the new var
                    // puts("STOP:: Name No Found!");
                    return tmp;
                }
                else if(is_space(&tmp)){
                    the_var = free_var_list(the_var);  // free the new var
                    return tmp;
                }
            }
            the_var = free_var_list(the_var);  // free the new var
        }
    }
    if(result.u == return_def){
        if(result.return_times <= 0){
            result.u = statement_end;
        }
        else{
            result.return_times -= 1; 
        }
    }
    return result;
}

// ---------  AND
GWARF_result and_func(statement *left_statement, statement *right_statement, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for and
    return_value.u = statement_end;
    return_value.value.type = BOOL_value;

    bool left = to_bool(traverse(left_statement, the_var, false).value), right;
    if(left){
        right = to_bool(traverse(right_statement, the_var, false).value);
        if(right){
            return_value.value.value.bool_value = true;
        }
        else{
            return_value.value.value.bool_value = false;
        }
    }
    else{
        return_value.value.value.bool_value = false;
    }
    return_back: return return_value;
}

// ---------  OR
GWARF_result or_func(statement *left_statement, statement *right_statement, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for and
    return_value.u = statement_end;
    return_value.value.type = BOOL_value;

    bool left = to_bool(traverse(left_statement, the_var, false).value), right;
    if(left){
        return_value.value.value.bool_value = true;
    }
    else{
        right = to_bool(traverse(right_statement, the_var, false).value);
        if(right){
            return_value.value.value.bool_value = true;
        }
        else{
            return_value.value.value.bool_value = false;
        }
    }
    return_back: return return_value;
}

// ---------  NOT
GWARF_result not_func(GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for and
    return_value.u = statement_end;
    return_value.value.type = BOOL_value;
    bool right = to_bool(right_result.value);
    if(right)
    {
        return_value.value.value.bool_value = false;
    }
    else{
        return_value.value.value.bool_value = true;
    }
    return_back: return return_value;
}

// ---------  BITAND &
GWARF_result bit_and_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitand__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitand__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;  // NULL相当于0
            left_result.value.value.int_value = 0;  // NULL相当于0
        }
        else if(right_result.value.type == NULL_value){
            right_result.value.type = INT_value;  // NULL相当于0
            right_result.value.value.int_value = 0;  // NULL相当于0
        }

        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value & right_result.value.value.int_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value & (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value & (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value & right_result.value.value.int_value;
        }
    }
    return_back: return return_value;
}

// ---------  BITOR |
GWARF_result bit_or_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitor__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitor__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;  // NULL相当于0
            left_result.value.value.int_value = 0;  // NULL相当于0
        }
        else if(right_result.value.type == NULL_value){
            right_result.value.type = INT_value;  // NULL相当于0
            right_result.value.value.int_value = 0;  // NULL相当于0
        }

        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value | right_result.value.value.int_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value | (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value | (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value | right_result.value.value.int_value;
        }
    }
    return_back: return return_value;
}


// ---------  BITNOTOR ^
GWARF_result bit_notor_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitnotor__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitnotor__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;  // NULL相当于0
            left_result.value.value.int_value = 0;  // NULL相当于0
        }
        else if(right_result.value.type == NULL_value){
            right_result.value.type = INT_value;  // NULL相当于0
            right_result.value.value.int_value = 0;  // NULL相当于0
        }

        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value ^ right_result.value.value.int_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value ^ (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value ^ (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value ^ right_result.value.value.int_value;
        }
    }
    return_back: return return_value;
}

// ---------  BITLEFT <<
GWARF_result bit_left_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitleft__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitleftr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;  // NULL相当于0
            left_result.value.value.int_value = 0;  // NULL相当于0
        }
        else if(right_result.value.type == NULL_value){
            right_result.value.type = INT_value;  // NULL相当于0
            right_result.value.value.int_value = 0;  // NULL相当于0
        }

        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value << right_result.value.value.int_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value << (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value << (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value << right_result.value.value.int_value;
        }
    }
    return_back: return return_value;
}

// ---------  BITRIGHT >>
GWARF_result bit_right_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitright__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitrightr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;  // NULL相当于0
            left_result.value.value.int_value = 0;  // NULL相当于0
        }
        else if(right_result.value.type == NULL_value){
            right_result.value.type = INT_value;  // NULL相当于0
            right_result.value.value.int_value = 0;  // NULL相当于0
        }

        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value >> right_result.value.value.int_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value >> (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = left_result.value.value.int_value >> (int)right_result.value.value.double_value;
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)left_result.value.value.double_value >> right_result.value.value.int_value;
        }
    }
    return_back: return return_value;
}

// ---------  BITNOT ~
GWARF_result bit_not_func(GWARF_result right_result, var_list *the_var){  // the func for negative and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for negative
    if(right_result.value.type == OBJECT_value){  // 调用右sub方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__bitnot__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.bool_value = 1;
        }
    }
    else{
        if(right_result.value.type == NULL_value){  // 返回bool true
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = 1;
        }
        else if(right_result.value.type == INT_value){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ~right_result.value.value.int_value;
        }
        else if(right_result.value.type == BOOL_value){
            return_value.u = statement_end;
            return_value.value.type = BOOL_value;
            if(right_result.value.value.bool_value)
            {
                return_value.value.value.bool_value = false;
            }
            else{
                return_value.value.value.bool_value = true;
            }
        }
        else if(right_result.value.type == NUMBER_value){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ~((int)right_result.value.value.double_value);
        }
    }
    return return_value;
}

// ---------  ADD
GWARF_result add_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value, get;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__add__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
        // goto next if
    }
    if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__add__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }

    {
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value = right_result.value;  // NULL加法相当于0
        }
        else if(right_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value = left_result.value;  // NULL加法相当于0
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value + right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value + right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value + right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value + right_result.value.value.int_value);
        }
        else if((left_result.value.type == STRING_value) && (right_result.value.type == STRING_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = STRING_value;
            char *l = left_result.value.value.string;
            char *r = right_result.value.value.string;
            return_value.value.value.string = malloc(strlen(l) + strlen(r));  // 创建新空间
            strcpy(return_value.value.value.string, l);  // 复制字符串
            strcat(return_value.value.value.string, r);  // 追加字符串
        }
        
    }
    return_back: return return_value;
}

// ---------  SUB
GWARF_result sub_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for sub and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for sub
    if(left_result.value.type == OBJECT_value){  // 调用左sub方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__sub__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右sub方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__subr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            return_value.u = statement_end;
            return negative_func(right_result, the_var);  // NULL减法相当于0
        }
        else if(right_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value = left_result.value;  // NULL减法相当于0
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value - right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value - right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value - right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value - right_result.value.value.int_value);
        }
    }
    return_back: return return_value;
}

// ---------  negative
GWARF_result negative_func(GWARF_result right_result, var_list *the_var){  // the func for negative and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for negative
    if(right_result.value.type == OBJECT_value){  // 调用右sub方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__negative__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value.type = BOOL_value;
            return_value.value.value.bool_value = true;
        }
    }
    else{
        if(right_result.value.type == NULL_value){  // 返回bool true
            return_value.u = statement_end;
            return_value.value.type = BOOL_value;
            return_value.value.value.bool_value = true;
        }
        else if(right_result.value.type == INT_value){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(-1 * right_result.value.value.int_value);
        }
        else if(right_result.value.type == BOOL_value){
            return_value.u = statement_end;
            return_value.value.type = BOOL_value;
            if(right_result.value.value.bool_value)
            {
                return_value.value.value.bool_value = false;
            }
            else{
                return_value.value.value.bool_value = true;
            }
        }
        else if(right_result.value.type == NUMBER_value){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(-1 * right_result.value.value.double_value);
        }
        else if(right_result.value.type == STRING_value){  // 字符串
            return_value.u = statement_end;
            return_value.value.type = STRING_value;
            char *r = right_result.value.value.string;
            return_value.value.value.string = malloc(strlen(r));  // 创建新空间
            char *tmp = malloc(strlen(r));
            strcpy(tmp, r);  // 复制字符串
            for(int i=0;i<strlen(tmp);i += 1){
                return_value.value.value.string[i] = tmp[strlen(tmp) - i - 1];  // 反转
            }
        }
    }
    return_back: return return_value;
}

// ---------  MUL
GWARF_result mul_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for mul and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for mul
    if(left_result.value.type == OBJECT_value){  // 调用左mul方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__mul__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右mul方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__mul__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            return_value.value = right_result.value;  // NULL乘法相当于1
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL乘法相当于1
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value * right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value * right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value * right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value * right_result.value.value.int_value);
        }
        else if((left_result.value.type == INT_value) && (right_result.value.type == STRING_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = STRING_value;
            int l = left_result.value.value.int_value;
            char *r = right_result.value.value.string;
            if(l == 0){
                return_value.value.value.string = (char *)malloc(0);  // NULL string
            }
            else if(l > 0){
                return_value.value.value.string = malloc(strlen(r) * l);  // 创建新空间
                strcpy(return_value.value.value.string, r);  // 复制字符串
                l -= 1;
                for(;l>0;l -= 1){
                    strcat(return_value.value.value.string, r);  // 追加字符串
                }
            }
            else{
                return_value.value.value.string = malloc(strlen(r) * (-l));  // 创建新空间
                char *tmp = malloc(strlen(r) * (-l));
                strcpy(tmp, r);  // 复制字符串
                l += 1;
                for(;l<0;l += 1){
                    strcat(tmp, r);  // 追加字符串
                }
                for(int i=0;i<strlen(tmp);i += 1){
                    return_value.value.value.string[i] = tmp[strlen(tmp) - i - 1];  // 反转
                }
                free(tmp);
            }
        }
        else if((left_result.value.type == STRING_value) && (right_result.value.type == INT_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = STRING_value;
            int l = right_result.value.value.int_value;
            char *r = left_result.value.value.string;
            if(l == 0){
                return_value.value.value.string = (char *)malloc(0);  // NULL string
            }
            else if(l > 0){
                return_value.value.value.string = malloc(strlen(r) * l);  // 创建新空间
                strcpy(return_value.value.value.string, r);  // 复制字符串
                l -= 1;
                for(;l>0;l -= 1){
                    strcat(return_value.value.value.string, r);  // 追加字符串
                }
            }
            else{
                return_value.value.value.string = malloc(strlen(r) * (-l));  // 创建新空间
                char *tmp = malloc(strlen(r) * (-l));
                strcpy(tmp, r);  // 复制字符串
                l += 1;
                for(;l<0;l += 1){
                    strcat(tmp, r);  // 追加字符串
                }
                for(int i=0;i<strlen(tmp);i += 1){
                    return_value.value.value.string[i] = tmp[strlen(tmp) - i - 1];  // 反转
                }
                free(tmp);
            }
            
        }
    }
    return_back: return return_value;
}

// ---------  DIV
GWARF_result div_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左div方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__div__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右div方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__divr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;
            left_result.value.value.int_value = 1;
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL除发相当于1
            goto return_result;
        }
        // 此处不是else if
        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;  // 除 无int
            return_value.value.value.double_value = ((double)left_result.value.value.int_value / (double)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (left_result.value.value.double_value / right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = ((double)left_result.value.value.int_value / right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (left_result.value.value.double_value / (double)right_result.value.value.int_value);
        }
    }
    return_back: return_result: return return_value;
}

// ---------  MOD_func
GWARF_result mod_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左div方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__mod__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右div方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__modr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;
            left_result.value.value.int_value = 1;
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL除 相当于1
            goto return_result;
        }
        // 此处不是else if
        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (left_result.value.value.int_value % right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ((int)left_result.value.value.double_value % (int)right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (left_result.value.value.int_value % (int)right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ((int)left_result.value.value.double_value % right_result.value.value.int_value);
        }
    }
    return_back: return_result: return return_value;
}

// ---------  int_div[整除]
GWARF_result int_div_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左div方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__idiv__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右div方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__idivr__");  // 整除
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            left_result.value.type = INT_value;
            left_result.value.value.int_value = 1;
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL除发相当于1
            goto return_result;
        }
        // 此处不是else if
        if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;  // 除 无int
            return_value.value.value.int_value = ((int)left_result.value.value.int_value / (int)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ((int)left_result.value.value.double_value / (int)right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ((int)left_result.value.value.int_value / (int)right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = ((int)left_result.value.value.double_value / (int)right_result.value.value.int_value);
        }
    }
    return_back: return_result: return return_value;
}

// ---------  POW
GWARF_result pow_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左pow方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__pow__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右pow方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__powr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = 1;
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL乘方相当于1
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)pow((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)pow(left_result.value.value.double_value, right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)pow((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)pow((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
        }
    }
    return_back: return return_value;
}

// ---------  LOG
GWARF_result log_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左log方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__log__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右log方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__logr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            return_value.value = left_result.value;  // 返回NULL
        }
        else if(right_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = 0;
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)log_((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)log_(left_result.value.value.double_value, right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)log_((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)log_((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
        }
    }
    return_back: return return_value;
}

// ---------  SQRT
GWARF_result sqrt_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左sqrt方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__sqrt__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右sqrt方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, "__sqrtr__");
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value = left_result.value;
        }
        goto return_back;
    }
    {
        if(left_result.value.type == NULL_value){
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = 0;
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = right_result.value;  // 返回NULL
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = statement_end;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)sqrt_((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)sqrt_(left_result.value.value.double_value, right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)sqrt_((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = statement_end;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)sqrt_((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
        }
    }
    return_back: return return_value;
}

// ---------  ASSIGnMENT
GWARF_result assignment_func(char *left, GWARF_result right_result, var_list *the_var, int from){  // the func for assignment and call from read_statement_list
    add_var(the_var, from, left, right_result.value);
    return right_result;
}

// ---------  EQUAL
GWARF_result equal_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var, int type){  // the func for equal and call from read_statement_list
    GWARF_result return_value;
    int return_bool = false;
    char *left_func_list[] = {"__eq__", "__more__", "__less__", "__eqmore__", "__eqless__","__noteq__"};  // bool 运算符
    char *right_func_list[] = {"__eq__", "__more__", "__less__", "__eqmore__", "__eqless__","__noteq__"};  // bool 运算符

    if(left_result.value.type == OBJECT_value){  // 调用左div方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, left_func_list[type]);
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
            goto return_back;
        }
    }
    if(right_result.value.type == OBJECT_value){  // 调用右div方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        var *tmp = find_var(call_var, 0, right_func_list[type]);
        if(tmp != NULL){
            get.value = tmp->value;
            get.father = &base_the_var;  // 设置father
            return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
        }
        else{
            return_value.u = statement_end;
            return_value.value.value.bool_value = true;
            return_value.value.type = BOOL_value;
        }
        goto return_back;
    }
    else{
        return_value.u = statement_end;
        if(left_result.value.type == NULL_value || right_result.value.type == NULL_value){
            return_bool = false;  // 无论什么都返回false NULL != NULL
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            if ((left_result.value.value.int_value == right_result.value.value.int_value) && (type == 0)){  // 如果相等:: __eq__
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value > right_result.value.value.int_value) && (type == 1)){  // 如果大于::__more__
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value < right_result.value.value.int_value) && (type == 2)){  // 如果小于::__less__
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value >= right_result.value.value.int_value) && (type == 3)){  // 如果大于等于::__eqmore__
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value <= right_result.value.value.int_value) && (type == 4)){  // 如果小于等于::__eqless__
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value != right_result.value.value.int_value) && (type == 5)){  // 如果不相等::__noteq__
                return_bool = true;  // 返回1 否则(默认)为0
            }
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            if ((left_result.value.value.double_value == right_result.value.value.double_value) && (type == 0)){  // 如果相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value > right_result.value.value.double_value) && (type == 1)){  // 如果大于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value < right_result.value.value.double_value) && (type == 2)){  // 如果小于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value >= right_result.value.value.double_value) && (type == 3)){  // 如果大于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value <= right_result.value.value.double_value) && (type == 4)){  // 如果小于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value != right_result.value.value.double_value) && (type == 5)){  // 如果不相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            if ((left_result.value.value.double_value == right_result.value.value.int_value) && (type == 0)){  // 如果相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value > right_result.value.value.int_value) && (type == 1)){  // 如果大于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value < right_result.value.value.int_value) && (type == 2)){  // 如果小于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value >= right_result.value.value.int_value) && (type == 3)){  // 如果大于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value <= right_result.value.value.int_value) && (type == 4)){  // 如果小于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.double_value != right_result.value.value.int_value) && (type == 5)){  // 如果不相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            if ((left_result.value.value.int_value == right_result.value.value.double_value) && (type == 0)){  // 如果相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value > right_result.value.value.double_value) && (type == 1)){  // 如果大于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value < right_result.value.value.double_value) && (type == 2)){  // 如果小于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value >= right_result.value.value.double_value) && (type == 3)){  // 如果大于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value <= right_result.value.value.double_value) && (type == 4)){  // 如果小于等于
                return_bool = true;  // 返回1 否则(默认)为0
            }
            if ((left_result.value.value.int_value != right_result.value.value.double_value) && (type == 5)){  // 如果不相等
                return_bool = true;  // 返回1 否则(默认)为0
            }
        }
        return_value.value.value.bool_value = return_bool;
        return_value.value.type = BOOL_value;
    }
    return_back: return return_value;
}

// --------- traverse[iter]
GWARF_result traverse(statement *the_statement, var_list *the_var, bool new){  // traverse the statement
    statement *tmp = the_statement;
    GWARF_result result, result2;
    if(the_statement == NULL){
        result.u = statement_end;  // 正常设置[正常语句结束]
        result.value.type = NULL_value;  // 默认设置
        result.value.value.int_value = 0;  // 默认设置
        goto return_back;
    }
    bool lock = false;
    if(new){  // need to make new var
        hash_var *tmp = make_hash_var();  // base_var
        the_var = append_var_list(tmp, the_var);
    }
    while(1){
        if(tmp == NULL){
            break;  // off
        }
        result2 = read_statement_list(tmp, the_var);

        // 错误停止
        if(result2.u == error){  // Name Error错误
            // puts("STOP:: Name No Found!");
            result = result2;
            break;
        }
        // TODO::rewent语句得优化一下 设置result2.is_rewent值
        if(result2.u == return_def && result2.return_times != 0){  // return def
            result2.return_times -= 1;
        }
        else if(result2.u == code_rewent){
            lock = true;  // keep the result is rewent for return
            result = result2;
        }
        else if(is_space(&result2)){
            result = result2;
            break;
        }
        
        if(!lock){
            result = result2;
        }
        else{
            puts("local");
        }
        tmp = tmp->next;
    }
    if(new){  // need to make new var
        the_var = free_var_list(the_var);  // free the new var
    }
    return_back: return result;
}

GWARF_result traverse_global(statement *the_statement, var_list *the_var){  // traverse the statement[not break、broken、and others] but error
    statement *tmp = the_statement;
    GWARF_result result;
    while(1){
        if(tmp == NULL){
            break;  // off
        }
        result = read_statement_list(tmp, the_var);
        if(result.u == error){  // Name Error错误
            printf("%s", result.error_info);
            break;
        }
        tmp = tmp->next;
    }
    return result;
}

inter *get_inter(){
    inter *tmp;
    tmp = malloc(sizeof(inter));  // get an address for base var
    tmp->global_var = make_hash_var();
    tmp->global_code = make_statement();
    return tmp;
}