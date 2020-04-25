#include<stdio.h>

#include "interpreter.h"

parameter *make_parameter_name(statement *var){
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    tmp->u.var = var;
    tmp->type = only_value;
    return tmp;
}

parameter *append_parameter_name(statement *var, parameter *parameter_base){
    parameter *tmp = parameter_base;  // iter var
    while(1){
        if (tmp->next == NULL){  // the last
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    parameter *new_tmp = make_parameter_name(var);
    tmp->next = new_tmp;
    return new_tmp;
}

// ---- parameter func[实参]
parameter *make_parameter_value(statement *value){
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    tmp->type = only_value;
    tmp->u.value = value;
    return tmp;
}

parameter *append_parameter_value(statement *value, parameter *parameter_base){  // add at last
    parameter *tmp = parameter_base;  // iter var
    while(1){
        if (tmp->next == NULL){  // the last
            break;
        }
        tmp = tmp->next;  // get the next to iter
    }
    parameter *new_tmp = make_parameter_value(value);
    tmp->next = new_tmp;
    return new_tmp;
}

parameter *add_parameter_value(statement *value, parameter *parameter_base){  // add at first
    parameter *new_tmp = make_parameter_value(value);
    new_tmp->next = parameter_base;
    return new_tmp;
}

parameter *pack_value_parameter(GWARF_value value){  // 把value封装成参数
    parameter *tmp;
    tmp = malloc(sizeof(parameter));  // get an address for base var
    tmp->next = NULL;
    tmp->type = only_value;
    statement *statement_tmp = make_statement();
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
