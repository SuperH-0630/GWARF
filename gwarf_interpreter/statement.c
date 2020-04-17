#include<stdio.h>
// #include "interpreter.h"

statement *make_statement();
statement *append_statement(statement *, statement*);
statement_list *make_statement_list();
statement_list *make_statement_base(statement *);
statement_list *append_statement_list(statement *, statement_list *);
statement *find_statement_list(int, statement_list *);
statement_list *free_statement_list(statement_list *);

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