#include <stdio.h>
#include <stdlib.h>
// #include "interprete.h"
#include "../paser/y.tab.c"

// running code
GWARF_result operation_func(statement *, var_list *);
GWARF_result add_func(GWARF_result, GWARF_result, var_list *);

// ------------------------- var func

var *make_var(){  // make var with base
    var *tmp;
    tmp = malloc(sizeof(var));  // get an address for base var
    tmp->name = "";  // can't get the name for the real var
    tmp->next = NULL;
    return tmp;
}

void append_var(char *name, GWARF_value value, var *base_var){
    int break_ = 1;  // get var[2] or not[1]
    var *tmp = base_var;  // iter var
    while(1){
        if (tmp->name == name){
            break_ = 2;
            break;
        }
        if (tmp->next == NULL){  // not var name *name
            break_ = 1;
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    if(break_ == 2){
        tmp->value = value;
        return;
    }
    var *new_tmp;
    new_tmp = make_var();  // make a new var
    tmp->next = new_tmp;
    new_tmp->name = name;
    new_tmp->value = value;
}

void free_var(var *base_var){  // free the address
    var *tmp = base_var;  // iter var
    while(1){
        if (tmp->next == NULL){  // the last
            free(tmp);
            break;
        }
        var *tmp_2 = tmp;
        tmp = tmp->next;
        free(tmp_2);
    }
}

var *get_var(char *name, var *base_var){  // get the address
    var *tmp = base_var;  // iter var
    while(1){
        if (tmp->name == name){
            return tmp;
        }
        if (tmp->next == NULL){  // not var name *name
            return NULL;
        }
        tmp = tmp->next;  // get the next to iter
    }
}

void del_var(char *name, var *base_var){  // free an address
    var *tmp = base_var, *last_tmp=NULL;  // iter var
    while(1){
        if (tmp->name == name){
            if(last_tmp != NULL){
                last_tmp->next = tmp->next;  // if tmp->next is NULL last_tmp->next is NULL too
            }
            free(tmp);
            return;
        }
        if (tmp->next == NULL){  // not var name *name
            return;
        }
        tmp = tmp->next;  // get the next to iter
        last_tmp = tmp;
    }
}

// ------------------------- statement list

statement *make_statement(){  // make statement
    statement *tmp;
    tmp = malloc(sizeof(statement));  // get an address for base var
    tmp->next = NULL;
    tmp->type = start;
    return tmp;
}

statement *append_statement(statement *base_statement, statement *new_tmp){  // make statement next
    statement *tmp = base_statement;  // iter var
    while(1){
        if (tmp->next == NULL){  // not var name *name
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    tmp->next = new_tmp;
    return new_tmp;
}

// ------------------------- run code

GWARF_result read_statement_list(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result return_value;
    switch (the_statement->type)
    {
        case operation:  // 表达式运算
            return_value = operation_func(the_statement, the_var);
            printf("operation value = %f\n", return_value.value.value.double_value);
            break;
        case 4:
            return_value.value = (the_statement->code).base_value.value;  // code
            break;
        default:
            return_value.value.value.double_value = 10086;
            break;
    }
    return return_value;
}

GWARF_result operation_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value, left_result, right_result;
    left_result = traverse((*the_statement).code.operation.left_exp, the_var);
    right_result = traverse((*the_statement).code.operation.right_exp, the_var);
    switch (the_statement->code.operation.type)  // 获取运算类型
    {
        case ADD_func:
            value = add_func(left_result, right_result, the_var);
            break;
        default:
            break;
    }
    return value;
}

GWARF_result add_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for add
    
    // 计算左右表达式的值
    // void traverse(statement *the_statement, var_list *the_var)

    if((left_result.value.type = NUMBER_value) && (right_result.value.type = NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = left_result.value.value.double_value + right_result.value.value.double_value;  // 数值相加运算
    }

    return return_value;
}

GWARF_result traverse(statement *the_statement, var_list *the_var){  // traverse the statement
    statement *tmp = the_statement;
    GWARF_result result;
    while(1){
        if(tmp == NULL){
            break;  // off
        }
        result = read_statement_list(tmp, the_var);
        tmp = tmp->next;
    }
    return result;
}

// -------inter func
inter *get_inter(){
    inter *tmp;
    tmp = malloc(sizeof(inter));  // get an address for base var
    tmp->global_var = make_var();
    tmp->global_code = make_statement();
    return tmp;
}

// int main(){
//     global_inter = get_inter();  // 拿全局解释器[并声明全局变量]
//     parser();
//     var_list *the_var;
//     printf("----start run----\n");
//     traverse(global_inter->global_code, the_var);
//     printf("code end...\n");
//     return 0;
// }
