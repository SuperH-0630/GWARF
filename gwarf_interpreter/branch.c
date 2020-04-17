#include<stdio.h>
// #include "interpreter.h"

if_list *make_base_if();
if_list *make_if(statement *, statement *);
if_list *append_elif(if_list *, if_list *);

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