#include <stdio.h>
#include <stdlib.h>
// #include "interprete.h"
#include "../paser/y.tab.c"

// running code
GWARF_result operation_func(statement *, var_list *);
GWARF_result add_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result assigment_func(char *, GWARF_result, var_list *);
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int type);

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
    var *new_tmp = make_var();
    tmp->next = new_tmp;
    new_tmp->name = malloc(sizeof(name));
    strcpy(new_tmp->name, name);
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
        if (!strcmp(tmp->name, name)){  // if tmp->name == name , strcmp will return 0, if not strcmp return not 0
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

// ------------------------- var_list

var_list *make_var_list(){  // make a empty var_list node
    var_list *tmp;
    tmp = malloc(sizeof(var_list));  // get an address for base var
    tmp->next = NULL;
    tmp->var_base = NULL;
    return tmp;
}

var_list *make_var_base(var *gloabl_var){
    var_list *tmp = make_var_list();
    tmp->var_base = gloabl_var;
    return tmp;
}


var_list *append_var_list(var *var_base, var_list *var_list_base){  // make var_list[FILO]
    var_list *tmp = make_var_list();
    tmp->var_base = var_base;
    tmp->next = var_list_base;
    return tmp;
}

var *find_var(var_list *var_base,int from, char *name){  // find var by func get_var in var_list[iter to find]
    var_list *start = var_base;
    var *return_var;
    for(int i = 0;i < from;i+= 1){
        if(start->next = NULL){
            break;
        }
        start = start->next;
    }
    while (1)
    {
        return_var = get_var(name, start->var_base);
        if((return_var == NULL) && (start->next == NULL)){  // don't get the var and not next
            return NULL;
        }
        else if((return_var == NULL) && (start->next != NULL)){  // don't get the var but can next
            start = start->next;
            continue;
        }
        return return_var;  //get var success can or can't next
    }
}

void add_var(var_list *var_base,int from, char *name, GWARF_value value){  // add var by func append_var in var_list[iter to find]
    var_list *start = var_base;
    var *return_var;
    for(int i = 0;i < from;i+= 1){
        if(start->next = NULL){
            break;
        }
        start = start->next;
    }
    append_var(name, value, start->var_base);
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
        case base_value:
            return_value.value = (the_statement->code).base_value.value;  // code
            printf("get value = %f\n", return_value.value.value.double_value);
            break;
        case base_var:{    // because the var tmp, we should ues a {} to make a block[name space] for the tmp var;
            var *tmp = find_var(the_var, 0, (the_statement->code).base_var.var_name);
            if(tmp == NULL){
                return_value.u = wrong;  // not var
            }
            else
            {
                return_value.value = tmp->value;  // get_var
                printf("var value = %f\n", return_value.value.value.double_value);
            }
            break;
        }
        default:
            puts("default");
            break;
    }
    return return_value;
}

// -----------------operation func

GWARF_result operation_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value, left_result, right_result;
    left_result = traverse((*the_statement).code.operation.left_exp, the_var, false);
    right_result = traverse((*the_statement).code.operation.right_exp, the_var, false);
    switch (the_statement->code.operation.type)  // 获取运算类型
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
        case ASSIGMENT_func:{  // because the var char, we should ues a {} to make a block[name space] for the tmp var;
            char *left = (the_statement->code.operation.left_exp)->code.base_var.var_name;  // get var name but not value
            value = assigment_func(left, right_result, the_var);
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
        default:
            break;
    }
    return value;
}

// ---------  ADD
GWARF_result add_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for add
    if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = left_result.value.value.double_value + right_result.value.value.double_value;  // 数值相加运算
    }
    return return_value;
}

// ---------  SUB
GWARF_result sub_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for sub and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for sub
    if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = left_result.value.value.double_value - right_result.value.value.double_value;  // 数值相减运算
    }
    return return_value;
}

// ---------  MUL
GWARF_result mul_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for mul and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for mul
    if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = left_result.value.value.double_value * right_result.value.value.double_value;  // 数值相乘运算
    }
    return return_value;
}

// ---------  DIV
GWARF_result div_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = left_result.value.value.double_value / right_result.value.value.double_value;  // 数值相除运算
    }
    return return_value;
}

// ---------  ASSIGMENT
GWARF_result assigment_func(char *left, GWARF_result right_result, var_list *the_var){  // the func for assigment and call from read_statement_list
    add_var(the_var, 0, left, right_result.value);
    return right_result;
}

// ---------  EQUAL
GWARF_result equal_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var, int type){  // the func for equal and call from read_statement_list
    GWARF_result return_value;
    double return_bool = 0;
    return_value.u = return_def;
    if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.value.type = NUMBER_value;
        if ((left_result.value.value.double_value == right_result.value.value.double_value) && (type == 0)){  // 如果相等
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.double_value > right_result.value.value.double_value) && (type == 1)){  // 如果大于
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.double_value < right_result.value.value.double_value) && (type == 2)){  // 如果小于
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.double_value >= right_result.value.value.double_value) && (type == 3)){  // 如果大于等于
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.double_value <= right_result.value.value.double_value) && (type == 4)){  // 如果小于等于
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.double_value != right_result.value.value.double_value) && (type == 5)){  // 如果不相等
            return_bool = 1;  // 返回1 否则(默认)为0
        }
        return_value.value.value.double_value = return_bool;  // 数值相加运算
    }
    return return_value;
}

// --------- traverse[iter]
GWARF_result traverse(statement *the_statement, var_list *the_var, bool new){  // traverse the statement
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
