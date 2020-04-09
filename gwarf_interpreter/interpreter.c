#include <stdio.h>
#include <stdlib.h>
// #include "interprete.h"
#include "../paser/y.tab.c"

// running code
GWARF_result while_func(statement *, var_list *);
GWARF_result operation_func(statement *, var_list *);
GWARF_result add_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result assigment_func(char *, GWARF_result, var_list *);
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int);
GWARF_result if_func(if_list *, var_list *);

// ---- var func

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
        if (!strcmp(tmp->name, name)){
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

// ---- statement list

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

// ---- var_list

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
    for(int i = 0;i < 100;i+= 1){
        if(start->next == NULL){
            break;
        }
        start = start->next;
    }
    append_var(name, value, start->var_base);
}

// ---- statement_list
statement_list *make_statement_list(){  // make a empty var_list node
    statement_list *tmp;
    tmp = malloc(sizeof(statement_list));  // get an address for base var
    tmp->next = NULL;
    tmp->statement_base = NULL;
    return tmp;
}

statement_list *make_statement_base(statement *gloabl_code){
    statement_list *tmp = make_statement_list();
    tmp->statement_base = gloabl_code;
    return tmp;
}

statement_list *append_statement_list(statement *statement_base, statement_list *statment_list_base){  // make var_list[FILO]
    statement_list *tmp = make_statement_list();
    tmp->statement_base = statement_base;
    tmp->next = statment_list_base;
    return tmp;
}

statement *find_statement_list(int from, statement_list *statment_list_base){  // find var by func get_var in var_list[iter to find]
    statement_list *start = statment_list_base;
    for(int i = 0;i < from;i+= 1){
        if(start->next == NULL){
            break;
        }
        start = start->next;
    }
    return start->statement_base;
}

statement_list *free_statement_list(statement_list *statment_list_base){  // make var_list[FILO]
    statement_list *tmp = statment_list_base->next;
    if(tmp != NULL){
        free(statment_list_base);
        return tmp;
    }
    return statment_list_base;
}

// ---- if_list
if_list *make_base_if(){  // make base if
    if_list *tmp;
    tmp = malloc(sizeof(if_list));  // get an address for base var
    tmp->next = NULL;
    tmp->done = NULL;
    tmp->condition = NULL;
    return tmp;
}

if_list *make_if(statement *condition, statement *done_base){  // if
    if_list *tmp = make_base_if();
    tmp->done = done_base;
    tmp->condition = condition;
    return tmp;
}

if_list *append_elif(if_list *tmp ,if_list *base_if_list){  // elif
    if_list *start = base_if_list;
    while(1){
        if(start->next  == NULL){
            break;
        }
        start = start->next;
    }
    start->next = tmp;
    return tmp;
}

// ---- run code

GWARF_result read_statement_list(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result return_value;
    return_value.u = statement_end;  // 正常设置[正常语句结束]
    return_value.value.type = NUMBER_value;  // 默认设置
    return_value.value.value.double_value = 0;  // 默认设置
    switch (the_statement->type)
    {
        case operation:  // 表达式运算
            puts("----code----");
            return_value = operation_func(the_statement, the_var);
            printf("operation value = %f\n", return_value.value.value.double_value);
            puts("----stop code----");
            break;
        case while_cycle:
            puts("----while code----");
            return_value = while_func(the_statement, the_var);
            if((return_value.u == cycle_break) || (return_value.u == code_broken)){
                printf("cycle_break(broken) %f\n", return_value.value.value.double_value);
                return_value.value.value.double_value -= 1;
                if(return_value.value.value.double_value < 0){
                    return_value.u = statement_end;  // 正常设置[正常语句结束]
                }
            }
            printf("while operation value = %f\n", return_value.value.value.double_value);
            puts("----stop while code----");
            break;
        case if_branch:
            puts("----if code----");
            return_value = if_func(the_statement->code.if_branch.done, the_var);
            if(return_value.u == cycle_break){
                printf("cycle_break %f\n", return_value.value.value.double_value);
            }
            if(return_value.u == code_broken){
                printf("broken %f\n", return_value.value.value.double_value);
                return_value.value.value.double_value -= 1;
                if(return_value.value.value.double_value < 0){
                    return_value.u = statement_end;  // 正常设置[正常语句结束]
                }
            }
            printf("if type = %d\n", return_value.u);
            printf("if operation value = %f\n", return_value.value.value.double_value);
            puts("----stop if code----");
            break;
        case base_value:  // get value[所有字面量均为这个表达式]
            return_value.value = (the_statement->code).base_value.value;  // code
            printf("get value = %f\n", return_value.value.value.double_value);
            break;
        case base_var:{    // because the var tmp, we should ues a {} to make a block[name space] for the tmp var;
            var *tmp = find_var(the_var, 0, (the_statement->code).base_var.var_name);
            if(tmp == NULL){
                return_value.u = name_no_found;  // nameerror
            }
            else
            {
                return_value.value = tmp->value;  // get_var
                printf("var value = %f\n", return_value.value.value.double_value);
            }
            break;
        }
        case break_cycle:
            return_value.u = cycle_break;
            if(the_statement->code.break_cycle.times == NULL){
                return_value.value.value.double_value = 0;
            }
            else{
                return_value.value.value.double_value = traverse(the_statement->code.break_cycle.times, the_var, false).value.value.double_value;  // 执行语句，获得弹出层
            }
            printf("break num = %f\n", return_value.value.value.double_value);
            break;
        case broken:
            return_value.u = code_broken;
            if(the_statement->code.broken.times == NULL){
                return_value.value.value.double_value = 0;
            }
            else{
                return_value.value.value.double_value = traverse(the_statement->code.broken.times, the_var, false).value.value.double_value;  // 执行语句，获得弹出层
            }
            printf("broken num = %f\n", return_value.value.value.double_value);
            break;
        case continue_cycle:
            return_value.u = cycle_continue;
            if(the_statement->code.continue_cycle.times == NULL){
                return_value.value.value.double_value = 0;
            }
            else{
                return_value.value.value.double_value = traverse(the_statement->code.continue_cycle.times, the_var, false).value.value.double_value;  // 执行语句，获得弹出层
            }
            printf("continue num = %f\n", return_value.value.value.double_value);
            break;
        case continued:
            return_value.u = code_continued;
            if(the_statement->code.continued.times == NULL){
                return_value.value.value.double_value = 0;
            }
            else{
                return_value.value.value.double_value = traverse(the_statement->code.continued.times, the_var, false).value.value.double_value;  // 执行语句，获得弹出层
            }
            printf("continued num = %f\n", return_value.value.value.double_value);
            break;
        default:
            puts("default");
            break;
    }
    return return_value;
}

// -----------------if func

GWARF_result if_func(if_list *if_base, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    if_list *start;
    again: start = if_base;
    while(1){
        if(start->condition  == NULL){  // else
            puts("----else----");
            value = traverse(start->done, the_var, false);
            puts("----stop else----");
            break;
        }
        else{  // not else
            GWARF_result condition;
            condition = traverse(start->condition, the_var, false);
            if(condition.value.value.double_value){  // condition run success
                puts("----if----");
                value = traverse(start->done, the_var, false);
                puts("----stop if----");
                break;
            }
        }
        if(start->next  == NULL){  // not next
            break;
        }
        start = start->next;
    }
    if(value.u == cycle_continue){  // if不处理也不计入层次 同break一样
        ;
    }
    if(value.u == code_continued){
        if(value.value.value.double_value <= 0){
            puts("----if continue real----");
            value.u = statement_end;
            goto again;
        }
        else{
            value.value.value.double_value -= 1;
        }
    }
    return value;
}

// -----------------while func

GWARF_result while_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value, condition;
    while (1){
        condition = traverse((*the_statement).code.while_cycle.condition, the_var, false);
        printf("while condition = %f\n", condition.value.value.double_value);
        if(!condition.value.value.double_value){
            break;
        }
        puts("----while----");
        value = traverse((*the_statement).code.operation.right_exp, the_var, false);
        puts("----stop while----");
        if((value.u == cycle_break) || (value.u == code_broken)){  // break the while
            break;
        }
        printf("type = %d\n", value.u);
        if((value.u == cycle_continue) || (value.u == code_continued)){
            if(value.value.value.double_value <= 0){
                puts("----continue real----");
                value.u = statement_end;
                continue;
            }
            else{
                value.value.value.double_value -= 1;
                break;
            }
        }
    }
    return value;
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
    value.u = statement_end;  // 正常设置[正常语句结束]
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
        if((result.u == cycle_break) || (result.u == code_broken)){  // don't next the statement and return the result [the while_func[or for func] will get the result and stop cycle]
            puts("----break or broken----");
            break;
        }
        if((result.u == cycle_continue) || (result.u == code_continued)){
            puts("----continue or continued----");
            break;
        }
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
