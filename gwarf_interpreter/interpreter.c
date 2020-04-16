#include <stdio.h>
#include <stdlib.h>
#include "../paser/y.tab.c"
#include <math.h>

// running code
GWARF_result while_func(statement *, var_list *);
GWARF_result operation_func(statement *, var_list *, var_list *);
GWARF_result add_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sub_func(GWARF_result, GWARF_result, var_list *);
GWARF_result mul_func(GWARF_result, GWARF_result, var_list *);
GWARF_result div_func(GWARF_result, GWARF_result, var_list *);
GWARF_result pow_func(GWARF_result, GWARF_result, var_list *);
GWARF_result log_func(GWARF_result, GWARF_result, var_list *);
GWARF_result sqrt_func(GWARF_result, GWARF_result, var_list *);
GWARF_result assigment_func(char *, GWARF_result, var_list *, int);
GWARF_result equal_func(GWARF_result, GWARF_result, var_list *, int);
GWARF_result if_func(if_list *, var_list *);
GWARF_result for_func(statement *, var_list *);
GWARF_result negative_func(GWARF_result, var_list *);
GWARF_result call_back(statement *, var_list *);
GWARF_result call_back_core(GWARF_result, var_list *, parameter *);
int len_only_double(double num);
int len_double(double num);
int len_int(int num);
int len_intx(unsigned int num);

GWARF_value to_int(GWARF_value, var_list *the_var);
GWARF_value to_double(GWARF_value value, var_list *the_var);
GWARF_value to_bool_(GWARF_value value, var_list *the_var);
GWARF_value to_str(GWARF_value value, var_list *the_var);
bool to_bool(GWARF_value);
GWARF_result get__value__(GWARF_value *base_the_var, var_list *the_var);

int get_var_list_len(var_list *);
var_list *copy_var_list(var_list *);
var_list * append_by_var_list(var_list *, var_list *);

GWARF_result block_func(statement *, var_list *);

// math
double log_(double, double);
double log_(double base, double num){  // 自己定义一次log
    return log(num) / log(base);
}

double sqrt_(double, double);
double sqrt_(double base, double num){  // 定义根号sqrt
    return pow(base, (1 / num));
}

// bool[bool逻辑转换]
bool to_bool(GWARF_value value){
    double bool_double = 1;  // if bool_double == 0则返回false其他返回true
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
    if(bool_double){
        return true;
    }
    else{
        return false;
    }
}

// ---- parameter func[形参]
parameter *make_parameter_name(char *name){
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    tmp->u.name = malloc(sizeof(name));
    strcpy(tmp->u.name, name);
    return tmp;
}

void append_parameter_name(char *name, parameter *parameter_base){
    parameter *tmp = parameter_base;  // iter var
    while(1){
        if (tmp->next == NULL){  // the last
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    parameter *new_tmp = make_parameter_name(name);
    tmp->next = new_tmp;
}

// ---- parameter func[实参]
parameter *make_parameter_value(statement *value){
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    tmp->u.value = value;
    return tmp;
}

void append_parameter_value(statement *value, parameter *parameter_base){
    parameter *tmp = parameter_base;  // iter var
    while(1){
        if (tmp->next == NULL){  // the last
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    parameter *new_tmp = make_parameter_value(value);
    tmp->next = new_tmp;
}

parameter *add_parameter_value(statement *value, parameter *parameter_base){
    parameter *new_tmp = make_parameter_value(value);
    new_tmp->next = parameter_base;
    return new_tmp;
}

parameter *pack_value_parameter(GWARF_value value){  // 把value封装成参数
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    statement *statement_tmp = malloc(sizeof(statement));
    statement_tmp->type = base_value;
    statement_tmp->code.base_value.value = value;
    tmp->u.value = statement_tmp;
    return tmp;
}

statement *pack_call_name(char *name, statement *from){  // 快速生成call back函数的the_statment
    statement *tmp = make_statement();
    tmp->type = base_var;
    tmp->code.base_var.var_name = name;
    tmp->code.base_var.from = from;
    return tmp;
}

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

// --------------default_var

default_var *make_default_var(){  // make_default_var
    default_var *tmp;
    tmp = malloc(sizeof(default_var));  // get an address for default_var
    tmp->next = NULL;
    return tmp;
}

default_var *make_default_var_base(){  // if
    default_var *tmp = make_default_var();
    tmp->name = "";
    tmp->from = 0;
    return tmp;
}

void append_default_var_base(char *name ,int from, default_var *base_default_var){  // elif
    default_var *start = base_default_var;
    while(1){
        if (!strcmp(start->name, name)){  // if tmp->name == name , strcmp will return 0, if not strcmp return not 0
            return;  // 不可以二次设置
        }
        if (start->next == NULL){  // not var name *name
            break;
        }
        start = start->next;  // get the next to iter
    }
    default_var *tmp = make_default_var();
    tmp->name = name;
    tmp->from = from;
    start->next = tmp;
    return;
}

int get_default(char *name, default_var *base_default_var){  // get the address
    default_var *tmp = base_default_var;  // iter var
    if(tmp == NULL){
        return 0;
    }
    while(1){
        if (!strcmp(tmp->name, name)){  // if tmp->name == name , strcmp will return 0, if not strcmp return not 0
            return tmp->from;
        }
        if (tmp->next == NULL){  // not var name *name
            return 0;
        }
        tmp = tmp->next;  // get the next to iter
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
    tmp->default_list = make_default_var_base();
    return tmp;
}

var_list *make_var_base(var *gloabl_var){  // make the base for global_var
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

var_list *append_by_var_list(var_list *back_var_list, var_list *var_list_base){  // make var_list[FILO]
    var_list *start = back_var_list;
    while(1){
        if(start->next == NULL){  // to the last
            break;
        }
        start = start->next;
    }
    start->next = var_list_base;
    return back_var_list;
}

var_list *free_var_list(var_list *var_list_base){  // free one var_list[FILO]
    var_list *tmp = var_list_base->next;
    if(tmp==NULL){
        return var_list_base;
    }
    free(var_list_base);
    return tmp;
}

int get_var_list_len(var_list *var_base){
    var_list *start = var_base;
    int tmp = 0;
    while(1){
        if(start->next == NULL){
            break;
        }
        start = start->next;
        tmp += 1;
    }
    return tmp;
}

var *find_var(var_list *var_base,int from, char *name){  // find var by func get_var in var_list[iter to find]
    var_list *start = var_base;
    var *return_var;
    from += get_default(name, var_base->default_list);
    for(int i = 0;i < from;i+= 1){
        if(start->next == NULL){
            break;
        }
        start = start->next;
    }
    // printf("name = %s, from = %d, address = %x\n", name, from, start->var_base);
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
        // printf("find on name = %s, from = %d, address = %x\n", name, from, start->var_base);
        return return_var;  //get var success can or can't next
    }
}

void add_var(var_list *var_base,int from, char *name, GWARF_value value){  // add var by func append_var in var_list[iter to find]
    var_list *start = var_base;
    var *return_var;
    from += get_default(name, var_base->default_list);
    for(int i = 0;i < from;i+= 1){
        if(start->next == NULL){
            break;
        }
        start = start->next;
    }
    // printf("----var add address = %d----\n", start);
    append_var(name, value, start->var_base);
}

var_list *copy_var_list(var_list *var_list_base){  // 复制一条var链到另一个内存地址上[base不复制]
    var_list *start = malloc(sizeof(var_list_base)), *tmp;
    memcpy(start, var_list_base, sizeof(var_list_base));  // 复制base节点
    tmp = start;  // 记录base节点
    while(1){  // 复制var_list链
        if((start == NULL) || (start->next == NULL)){
            break;
        }
        puts("F1");
        var_list *next_tmp = malloc(sizeof(start->next));
        memcpy(next_tmp, start->next, sizeof(start->next));  // 复制到新的地方
        start->next = next_tmp;  // 应用新的地方
        start = start->next;
    }
    return tmp;
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
        case call:
            return_value = call_back(the_statement, the_var);
            break;
        case while_cycle:
            puts("----while code----");
            return_value = while_func(the_statement, the_var);
            puts("----stop while code----");
            if(return_value.u == return_def){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case for_cycle:
            puts("----for code----");
            return_value = for_func(the_statement, the_var);
            puts("----for while code----");
            if(return_value.u == return_def){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
                return_value.value.type = NULL_value;
                return_value.value.value.int_value = 0;
            }
            break;
        case if_branch:
            puts("----if code----");
            return_value = if_func(the_statement->code.if_branch.done, the_var);
            puts("----stop if code----");
            if(return_value.u == return_def){  // while循环不需要返回值[避免GWARF_value 进入 the_var]
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
        case base_var:{    // because the var tmp, we should ues a {} to make a block[name space] for the tmp var;
            int from = 0;
            if(the_statement->code.base_var.from == NULL){
                from = 0;
            }
            else{
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.base_var.from, the_var, false);
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
            var *tmp = find_var(the_var, from, (the_statement->code).base_var.var_name);
            if(tmp == NULL){
                return_value.u = name_no_found;  // nameerror
                printf("name not found [%s]\n", (the_statement->code).base_var.var_name);
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
            puts("----point----");
            GWARF_value base_the_var = traverse((the_statement->code).point.base_var, the_var, false).value;
            if(base_the_var.type == CLASS_value){  // is class so that can use "."
                puts("func: point");
                return_value = traverse((the_statement->code).point.child_var, base_the_var.value.class_value->the_var, false);
            }
            else if(base_the_var.type == OBJECT_value){
                puts("func: point");
                return_value = traverse((the_statement->code).point.child_var, base_the_var.value.object_value->the_var, false);
            }
            else{  // 其他类型
                goto the_break;
            }
            return_value.father = malloc(sizeof(return_value.father));  // 记录father的值
            *(return_value.father) = base_the_var;
            puts("----stop point----");
            return_value.value = to_object(return_value.value, the_var);
            the_break: break;
        }
        case def:{
            GWARF_result func_value;
            func *func_tmp = malloc(sizeof(func));

            func_tmp->done = the_statement->code.def.done;
            func_tmp->parameter_list = the_statement->code.def.parameter_list;
            func_tmp->the_var = copy_var_list(the_var);
            func_tmp->type = customize;  // func by user
            if(login_var != the_var){  // 定义为类方法
                func_tmp->is_class = 1;
            }
            else{
                func_tmp->is_class = 0;
            }

            func_value.value.type = FUNC_value;
            func_value.value.value.func_value = func_tmp;

            assigment_func(the_statement->code.def.name, func_value, login_var, 0);  // 注册函数到指定的位置
            // 无返回值
            break;
        }
        case set_class:{
            puts("----set class----");
            GWARF_result class_value;
            class_object *class_tmp = malloc(sizeof(class_object));

            class_tmp->the_var = make_var_base(make_var());  // make class var list
            class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
            class_value.value.type = CLASS_value;
            class_value.value.value.class_value = class_tmp;

            statement *tmp = the_statement->code.set_class.done;
            GWARF_result result;
            while(1){
                if(tmp == NULL){
                    break;  // off
                }
                read_statement(tmp, the_var, class_tmp->the_var);
                tmp = tmp->next;
            }

            assigment_func(the_statement->code.set_class.name, class_value, login_var, 0);  // 注册class 的 位置
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
            return_value.u = code_return;
            if(the_statement->code.return_code.times == NULL){
                return_value.return_times = 0;
            }
            else{
                int int_tmp;
                GWARF_result tmp_result, tmp_object = traverse(the_statement->code.return_code.times, the_var, false);
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
                return_value.value = to_object(traverse(the_statement->code.return_code.value, the_var, false).value, the_var);
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
                value.value.value.int_value -= 1;
                if(value.value.value.int_value < 0){
                    value.u = statement_end;  // 正常设置[正常语句结束]
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
            condition = to_bool(traverse(start->condition, the_var, false).value);
            if(rego || (condition)){  // condition run success or rego(condition won't do) bug rewent can
                if_restart:
                puts("----if----");
                value = traverse(start->done, the_var, true);
                puts("----stop if----");

                // restarted操作
                if(value.u == code_restarted){
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
    // printf("----address = %d----\n", the_var);
    var *tmp = make_var();  // base_var
    the_var = append_var_list(tmp, the_var);
    // printf("----new address = %d----\n", the_var);
    bool condition;
    if(the_statement->code.for_cycle.first != NULL){
        traverse(the_statement->code.for_cycle.first, the_var, false); // first to do
    }
    while (1){
        if(the_statement->code.for_cycle.condition != NULL){  // 检查是否存在循环条件
            condition = to_bool(traverse(the_statement->code.for_cycle.condition, the_var, false).value);
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
            printf("cycle_break(broken) %f\n", value.value.value.int_value);
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
            traverse(the_statement->code.for_cycle.after, the_var, false);
        }
        // continue操作
        if((value.u == cycle_continue) || (value.u == code_continued)){
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
    the_var = free_var_list(the_var);  // free the new var
    return value;
}

// -----------------block func

GWARF_result block_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value, condition;
    again: 
    puts("----block----");
    value = traverse(the_statement->code.code_block.done, the_var, true);
    puts("----stop block----");

    // restart操作[和continue效果相同]
    if(value.u == code_restarted){
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
        if(value.value.value.int_value <= 0){
            value.u = statement_end;  // 正常设置[正常语句结束]
        }
        else{
            value.value.value.int_value -= 1;
        }
    }
    return value;
}

// -----------------while func

GWARF_result while_func(statement *the_statement, var_list *the_var){  // read the statement list with case to run by func
    GWARF_result value;
    // printf("----address = %d----\n", the_var);
    var *tmp = make_var();  // base_var
    the_var = append_var_list(tmp, the_var);
    // printf("----new address = %d----\n", the_var);
    bool condition;
    while (1){
        condition = to_bool(traverse(the_statement->code.while_cycle.condition, the_var, false).value);
        printf("while condition = %d\n", condition);
        if(!condition){
            break;
        }
        restart_again: 
        puts("----while----");
        value = traverse(the_statement->code.while_cycle.done, the_var, false);
        puts("----stop while----");

        // break的操作
        if((value.u == cycle_break) || (value.u == code_broken)){
            printf("cycle_break(broken) %f\n", value.value.value.int_value);
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

        // restart的操作
        if((value.u == cycle_restart) || (value.u == code_restarted)){
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
    the_var = free_var_list(the_var);  // free the new var
    return value;
}

// -----------------operation func

GWARF_result operation_func(statement *the_statement, var_list *the_var, var_list *login_var){  // read the statement list with case to run by func
    GWARF_result value, left_result, right_result;
    int func_type = the_statement->code.operation.type;
    if((func_type != ASSIGMENT_func) && (func_type != NEGATIVE_func)){  // don't run because I don't need[if it's and func ,it will be run twice]
        left_result = traverse((*the_statement).code.operation.left_exp, the_var, false);
    }
    right_result = traverse((*the_statement).code.operation.right_exp, the_var, false);
    switch (func_type)  // 获取运算类型
    {
        case ADD_func:
            value = add_func(left_result, right_result, the_var);
            printf("value.value.type = %d\n", value.value.type);
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
        case NEGATIVE_func:
            value = negative_func(right_result, the_var);
            break;
        case ASSIGMENT_func:{  // because the var char, we should ues a {} to make a block[name space] for the tmp var;
            if((the_statement->code.operation.left_exp)->type == base_var){  // 通过base_var赋值
                char *left = (the_statement->code.operation.left_exp)->code.base_var.var_name;  // get var name but not value
                int from = 0;
                if((the_statement->code.operation.left_exp)->code.base_var.from == NULL){
                    from = 0;
                }
                else{
                    GWARF_result tmp_result, tmp_object = traverse((the_statement->code.operation.left_exp)->code.base_var.from, the_var, false);
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

                value = assigment_func(left, right_result, login_var, from);
            }
            else if((the_statement->code.operation.left_exp)->type == point){  // 通过point赋值
                printf("(the_statement->code).point.base_var = %u\n", (the_statement->code.operation.left_exp)->code.point.base_var);
                GWARF_value base_the_var = traverse((the_statement->code.operation.left_exp)->code.point.base_var, the_var, false).value;  // 不用取value
                if(((the_statement->code.operation.left_exp)->code.point.child_var)->type == base_var){
                    char *left = ((the_statement->code.operation.left_exp)->code.point.child_var)->code.base_var.var_name;
                    int from = 0;
                    if(((the_statement->code.operation.left_exp)->code.point.child_var)->code.base_var.from == NULL){
                        from = 0;
                    }
                    else{
                        GWARF_result tmp_result, tmp_object = traverse(((the_statement->code.operation.left_exp)->code.point.child_var)->code.base_var.from, the_var, false);
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
                    value = assigment_func(left, right_result, base_the_var.value.object_value->the_var, from);
                }
                else{
                    goto the_else;
                }
            }
            else{ 
                the_else: puts("Bad Assigment");
            }
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
        default:
            break;
    }
    value.u = statement_end;  // 正常设置[正常语句结束]
    value.value = to_object(value.value, the_var);  // 返回类型是object[不下放到add func等]
    return value;
}

GWARF_result call_back(statement *the_statement, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result get = traverse(the_statement->code.call.func, the_var, false), tmp_x, result;
    tmp_x = call_back_core(get, the_var, the_statement->code.call.parameter_list);
    result.value = to_object(tmp_x.value, the_var);  // 返回类型是object
    return result;
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
        var *tmp = make_var();  // base_var
        the_var = append_var_list(tmp, the_var);
        // printf("----new address = %d----\n", the_var);

        if(func_->type == customize){  // 用户定义的方法
            if(tmp_x == NULL){
                puts("No tmp_x");
                goto no_tmp_x;  // 无形参
            }
            GWARF_result father;
            if(func_->is_class  == 1){
                father.value = *(get.father);
                assigment_func(tmp_x->u.name, father, the_var, 0);
                if (tmp_x->next == NULL){  // the last
                    goto no_tmp_x;
                }
                tmp_x = tmp_x->next;  // get the next to iter
            }
            while(1){
                GWARF_result tmp = traverse(tmp_s->u.value, the_var, false);
                assigment_func(tmp_x->u.name, tmp, the_var, 0);
                if ((tmp_x->next == NULL)||(tmp_s->next == NULL)){  // the last
                    break;
                }
                tmp_x = tmp_x->next;  // get the next to iter
                tmp_s = tmp_s->next;
            }
            no_tmp_x: 
            puts("----start func----");
            result = traverse(func_->done, the_var, false);  // 执行func_value->done
            if(result.u == code_return){
                if(result.return_times <= 0){
                    result.u = return_def;
                }
                else{
                result.return_times -= 1; 
                }
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
        object_tmp->the_var = append_by_var_list(make_var_base(make_var()), object_tmp->cls);
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

            // // printf("----address = %d----\n", the_var);
            var *tmp = make_var();  // base_var
            the_var = append_var_list(tmp, the_var);
            // // printf("----new address = %d----\n", the_var);

            if(func_->type == customize){  // 用户定义的方法
                if(tmp_x == NULL){
                    puts("No tmp_x");
                    goto no_tmp_x_init;  // 无形参
                }
                GWARF_result father;
                father.value.type = OBJECT_value;
                father.value.value.object_value = object_tmp;
                if(func_->is_class  == 1){
                    assigment_func(tmp_x->u.name, father, the_var, 0);
                    if (tmp_x->next == NULL){  // the last
                        goto no_tmp_x_init;
                    }
                    tmp_x = tmp_x->next;  // get the next to iter
                }
                while(1){
                    GWARF_result tmp = traverse(tmp_s->u.value, the_var, false);
                    assigment_func(tmp_x->u.name, tmp, the_var, 0);
                    if ((tmp_x->next == NULL)||(tmp_s->next == NULL)){  // the last
                        break;
                    }
                    tmp_x = tmp_x->next;  // get the next to iter
                    tmp_s = tmp_s->next;
                }
                no_tmp_x_init: 
                puts("----start func----");
                traverse(func_->done, the_var, false);  // 执行func_value->done
                puts("----stop start func----");
            }
            else{
                GWARF_result tmp_get;
                GWARF_value father;
                father.type = OBJECT_value;
                father.value.object_value = object_tmp;
                tmp_get.father = &father;
                result = func_->paser(func_, tmp_s, the_var, tmp_get, old_var_list);
            }
            the_var = free_var_list(the_var);  // free the new var
        }
        // 记录返回值
        result.u = return_def;
        result.value = tmp;

    }
    return result;
}

// ---------  ADD
GWARF_result add_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for add and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for add
    if(left_result.value.type == OBJECT_value){  // 调用左add方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;
        get.value = find_var(call_var, 0, "__add__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
    }
    else if(right_result.value.type == OBJECT_value){  // 调用右add方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__add__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
    }
    else{
        // 理论上用户是不可以直接调用下面的基类的，计算过程中万物皆类
        if(left_result.value.type == NULL_value){
            return_value.value = right_result.value;  // NULL加法相当于0
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL加法相当于0
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = return_def;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value + right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value + right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value + right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value + right_result.value.value.int_value);
        }
        else if((left_result.value.type == STRING_value) && (right_result.value.type == STRING_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = STRING_value;
            char *l = left_result.value.value.string;
            char *r = right_result.value.value.string;
            return_value.value.value.string = malloc(strlen(l) + strlen(r));  // 创建新空间
            strcpy(return_value.value.value.string, l);  // 复制字符串
            strcat(return_value.value.value.string, r);  // 追加字符串
        }
        
    }
    return return_value;
}

// ---------  SUB
GWARF_result sub_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for sub and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for sub
    if(left_result.value.type == OBJECT_value){  // 调用左sub方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__sub__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
    }
    else if(right_result.value.type == OBJECT_value){  // 调用右sub方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__sub__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
    }
    else{
        if(left_result.value.type == NULL_value){
            return negative_func(right_result, the_var);  // NULL减法相当于0
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL减法相当于0
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = return_def;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value - right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value - right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value - right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value - right_result.value.value.int_value);
        }
    }
    return return_value;
}

// ---------  negative
GWARF_result negative_func(GWARF_result right_result, var_list *the_var){  // the func for sub and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for sub
    if(right_result.value.type == NULL_value){  // 返回bool true
        return_value.u = return_def;
        return_value.value.type = BOOL_value;
        return_value.value.value.bool_value = true;
    }
    else if(right_result.value.type == INT_value){  // all is INT
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = (int)(-1 * right_result.value.value.int_value);
    }
    else if(right_result.value.type == BOOL_value){
        return_value.u = return_def;
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
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)(-1 * right_result.value.value.double_value);
    }
    else if(right_result.value.type == STRING_value){  // 字符串
        return_value.u = return_def;
        return_value.value.type = STRING_value;
        char *r = right_result.value.value.string;
        return_value.value.value.string = malloc(strlen(r));  // 创建新空间
        char *tmp = malloc(strlen(r));
        strcpy(tmp, r);  // 复制字符串
        for(int i=0;i<strlen(tmp);i += 1){
            return_value.value.value.string[i] = tmp[strlen(tmp) - i - 1];  // 反转
        }
    }
    return return_value;
}

// ---------  MUL
GWARF_result mul_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for mul and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for mul
    if(left_result.value.type == OBJECT_value){  // 调用左mul方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__mul__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
    }
    else if(right_result.value.type == OBJECT_value){  // 调用右mul方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__mul__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
    }
    else{
        if(left_result.value.type == NULL_value){
            return_value.value = right_result.value;  // NULL乘法相当于1
        }
        else if(right_result.value.type == NULL_value){
            return_value.value = left_result.value;  // NULL乘法相当于1
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
            return_value.u = return_def;
            return_value.value.type = INT_value;
            return_value.value.value.int_value = (int)(left_result.value.value.int_value * right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value * right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.int_value * right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (double)(left_result.value.value.double_value * right_result.value.value.int_value);
        }
        else if((left_result.value.type == INT_value) && (right_result.value.type == STRING_value)){  // all is NUMBER
            return_value.u = return_def;
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
            }
        }
        else if((left_result.value.type == STRING_value) && (right_result.value.type == INT_value)){  // all is NUMBER
            return_value.u = return_def;
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
            }
            
        }
    }
    return return_value;
}

// ---------  DIV
GWARF_result div_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == OBJECT_value){  // 调用左div方法
        GWARF_result get;
        GWARF_value base_the_var = left_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__div__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(right_result.value));
    }
    else if(right_result.value.type == OBJECT_value){  // 调用右div方法
        GWARF_result get;
        GWARF_value base_the_var = right_result.value;  // 只有一个参数
        var_list *call_var = base_the_var.value.object_value->the_var;

        get.value = find_var(call_var, 0, "__div__")->value;
        get.father = &base_the_var;  // 设置father
        return_value = call_back_core(get, the_var, pack_value_parameter(left_result.value));
    }
    else{
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
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;  // 除 无int
            return_value.value.value.double_value = ((double)left_result.value.value.int_value / (double)right_result.value.value.int_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (left_result.value.value.double_value / right_result.value.value.double_value);
        }
        else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = ((double)left_result.value.value.int_value / right_result.value.value.double_value);
        }
        else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
            return_value.u = return_def;
            return_value.value.type = NUMBER_value;
            return_value.value.value.double_value = (left_result.value.value.double_value / (double)right_result.value.value.int_value);
        }
    }
    return_result: return return_value;
}

// ---------  POW
GWARF_result pow_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == NULL_value){
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = 1;
    }
    else if(right_result.value.type == NULL_value){
        return_value.value = left_result.value;  // NULL乘方相当于1
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = (int)pow((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)pow(left_result.value.value.double_value, right_result.value.value.double_value);
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)pow((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)pow((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
    }
    return return_value;
}

// ---------  LOG
GWARF_result log_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == NULL_value){
        return_value.value = left_result.value;  // 返回NULL
    }
    else if(right_result.value.type == NULL_value){
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = 0;
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = (int)log_((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)log_(left_result.value.value.double_value, right_result.value.value.double_value);
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)log_((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)log_((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
    }
    return return_value;
}

// ---------  SQRT
GWARF_result sqrt_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var){  // the func for div and call from read_statement_list
    GWARF_result return_value;  // the result by call read_statement_list with left and right; value is the result for div
    if(left_result.value.type == NULL_value){
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = 0;
    }
    else if(right_result.value.type == NULL_value){
        return_value.value = right_result.value;  // 返回NULL
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
        return_value.u = return_def;
        return_value.value.type = INT_value;
        return_value.value.value.int_value = (int)sqrt_((double)left_result.value.value.int_value, (double)right_result.value.value.int_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)sqrt_(left_result.value.value.double_value, right_result.value.value.double_value);
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)sqrt_((double)left_result.value.value.int_value, (double)right_result.value.value.double_value);
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is NUMBER
        return_value.u = return_def;
        return_value.value.type = NUMBER_value;
        return_value.value.value.double_value = (double)sqrt_((double)left_result.value.value.double_value, (double)right_result.value.value.int_value);
    }
    return return_value;
}

// ---------  ASSIGMENT
GWARF_result assigment_func(char *left, GWARF_result right_result, var_list *the_var, int from){  // the func for assigment and call from read_statement_list
    add_var(the_var, from, left, right_result.value);
    return right_result;
}

// ---------  EQUAL
GWARF_result equal_func(GWARF_result left_result, GWARF_result right_result, var_list *the_var, int type){  // the func for equal and call from read_statement_list
    GWARF_result return_value;
    int return_bool = false;
    return_value.u = return_def;
    if(left_result.value.type == NULL_value || right_result.value.type == NULL_value){
        return_bool = false;  // 无论什么都返回false NULL != NULL
    }
    else if((left_result.value.type == INT_value || left_result.value.type == BOOL_value) && (right_result.value.type == INT_value || right_result.value.type == BOOL_value)){  // all is INT
        return_value.value.type = INT_value;
        if ((left_result.value.value.int_value == right_result.value.value.int_value) && (type == 0)){  // 如果相等
            return_bool = true;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.int_value > right_result.value.value.int_value) && (type == 1)){  // 如果大于
            return_bool = true;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.int_value < right_result.value.value.int_value) && (type == 2)){  // 如果小于
            return_bool = true;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.int_value >= right_result.value.value.int_value) && (type == 3)){  // 如果大于等于
            return_bool = true;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.int_value <= right_result.value.value.int_value) && (type == 4)){  // 如果小于等于
            return_bool = true;  // 返回1 否则(默认)为0
        }
        if ((left_result.value.value.int_value != right_result.value.value.int_value) && (type == 5)){  // 如果不相等
            return_bool = true;  // 返回1 否则(默认)为0
        }
    }
    else if((left_result.value.type == NUMBER_value) && (right_result.value.type == NUMBER_value)){  // all is NUMBER
        return_value.value.type = INT_value;
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
        return_value.value.type = INT_value;
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
        return_value.value.type = INT_value;
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
    return return_value;
}

// --------- traverse[iter]
GWARF_result traverse(statement *the_statement, var_list *the_var, bool new){  // traverse the statement
    statement *tmp = the_statement;
    GWARF_result result, result2;
    if(the_statement == NULL){
        result.u = statement_end;  // 正常设置[正常语句结束]
        result.value.type = NUMBER_value;  // 默认设置
        result.value.value.double_value = 0;  // 默认设置
        goto return_back;
    }
    bool lock = false;
    if(new){  // need to make new var
        // printf("----address = %d----\n", the_var);
        var *tmp = make_var();  // base_var
        the_var = append_var_list(tmp, the_var);
        // printf("----new address = %d----\n", the_var);
    }
    while(1){
        if(tmp == NULL){
            break;  // off
        }
        result2 = read_statement_list(tmp, the_var);

        // 错误停止
        if(result2.u == name_no_found){
            puts("STOP:: Name No Found!");
            exit(1);  // 停止运行
        }

        if((result2.u == cycle_break) || (result2.u == code_broken)){  // don't next the statement and return the result [the while_func[or for func] will get the result and stop cycle]
            puts("----break or broken----");
            result = result2;
            break;
            }
        if((result2.u == cycle_continue) || (result2.u == code_continued) || (result2.u == cycle_restart) || (result2.u == code_restarted)){
            printf("----continue/continued or restart/restarted----[%d]\n", result2.u);
            result = result2;
            break;
        }

        if(result2.u == code_return){
            printf("----return----\n");
            result = result2;
            break;
        }

        if(result2.u == code_rego){
            puts("----rego----");  // rego now
            result = result2;
            break;
        }

        if(result2.u == code_rewent){
            lock = true;  // keep the result is rewent for return
            result = result2;
        }

        if(!lock){
            result = result2;
        }
        tmp = tmp->next;
    }
    if(new){  // need to make new var
        the_var = free_var_list(the_var);  // free the new var
    }
    return_back: return result;
}

GWARF_result traverse_global(statement *the_statement, var_list *the_var){  // traverse the statement[not break、broken、and others]
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

// ------official func
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
        break;
    }
    default:
        break;
    }
    return_result: return return_value;
}

// TODO:: __add__等方法对于输入参数需要辨别是否为NUMBER_value而非CLASS_value[更佳的做法是调用__add__时使用to_object]
void int_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("int", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
}

GWARF_result int_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
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
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value");
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


void double_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("double", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
}

GWARF_result double_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
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
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value");
            return_value.value = tmp->value;  // 取得用于计算的数值
            break;
        }
        case __add__func:{
            GWARF_result reight_tmp, left_tmp;
            GWARF_value base_the_var = traverse(tmp_s->u.value, out_var, false).value;  // 只有一个参数
            reight_tmp = get__value__(&base_the_var, the_var);
            left_tmp.value = find_var(login_var, 0, "value")->value;
            // printf("add_func:: out_var = %x\n", out_var);
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

void str_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("str", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
}

GWARF_result str_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
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
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value");
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

void bool_login_official(var_list *the_var, GWARF_result (*paser)(func *, parameter *, var_list *, GWARF_result, var_list *)){
    // 创建对象[空对象]
    puts("----set class----");
    GWARF_result class_value;
    class_object *class_tmp = malloc(sizeof(class_object));

    class_tmp->the_var = make_var_base(make_var());  // make class var list
    class_tmp->out_var = append_by_var_list(class_tmp->the_var, copy_var_list(the_var));  // make class var list with out var
    class_value.value.type = CLASS_value;
    class_value.value.value.class_value = class_tmp;

    assigment_func("bool", class_value, the_var, 0);  // 注册class 的 位置
    puts("----stop set class----");

    // 注册函数
    int a[][2] = {{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}};
    char *name[] = {"__init__", "__value__", "__add__", "__sub__", "__mul__","__div__"};

    int lenth = sizeof(a)/sizeof(a[0]);
    for(int i = 0;i < lenth;i+=1){
        login_official_func(a[i][0], a[i][1], class_tmp->the_var, name[i], paser);
    }
}

GWARF_result bool_official_func(func *the_func, parameter *tmp_s, var_list *the_var, GWARF_result father, var_list *out_var){  // out_var是外部环境, the_var是self内部环境
    GWARF_result return_value;
    var_list *login_var;
    return_value.u = return_def;
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
            break;
        }
        case __value__func:{  // 若想实现运算必须要有这个方法
            var *tmp = find_var(login_var, 0, "value");
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
    GWARF_result reight_tmp, get;
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
            goto return_result;  // 如果类型不是object或者class
        }
        get.value = find_var(call_var, 0, "__value__")->value;  // TODO:: 需要检查__value__是否存在
        get.father = base_the_var;  // 设置father
        reight_tmp = call_back_core(get, the_var, NULL);

        base_the_var = &(reight_tmp.value);  // 重复获取__value__[直到类型不是object或class]
    }
    return_result: return reight_tmp;
}

GWARF_value to_object(GWARF_value value, var_list *the_var){  // 用于计算的get__value__统一核心
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

// TODO::增加类型检查[break、broken]，设置func和NULL均为object，设置object无__add___等方法时的操作