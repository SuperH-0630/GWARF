#include<stdio.h>

#include "interpreter.h"

// --------------var[存储在hash_var节点上]

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

// --------------hash_var[存储在var_list节点上]

hash_var *make_hash_var(){  // 生成并初始化
    hash_var *tmp = NULL;

    tmp = malloc(sizeof(hash_var));
    tmp->hash = malloc((size_t)(sizeof(var) * MAX_SIZE));
    
    for(int i = 0; i < MAX_SIZE; i++){
        tmp->hash[i] = NULL;  // 初始化
    }
    return tmp;
}

unsigned int time33(char *key){
    unsigned int hash = 5381;
    while(*key){
        hash += (hash << 5 ) + (*key++);
    }
    return (hash & 0x7FFFFFFF) % MAX_SIZE;
}

int login_node(char *name, GWARF_value value, hash_var *the_hash_var){
    unsigned int index = time33(name);
    var *base_node = the_hash_var->hash[index];  // 根据下标拿base节点

    if(base_node == NULL){  // 生成基本节点
        the_hash_var->hash[index] = make_var();
        base_node = the_hash_var->hash[index];
    }
    append_var(name, value, base_node);
    return 0;
}

var *find_node(char *name, hash_var *the_hash_var){
    if(the_hash_var == NULL){
        return NULL;
    }

    unsigned int index = time33(name);
    var *base_node = the_hash_var->hash[index];  // 根据下标拿base节点

    if(base_node == NULL){  // 没有节点
        return NULL;
    }
    return get_var(name, base_node);
}

// --------------default_var[存储在var_list节点上]

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

//  --------------var_list[保存default_var和hash_var]

var_list *make_var_list(){  // make a empty var_list node
    var_list *tmp;
    tmp = malloc(sizeof(var_list));  // get an address for base var
    tmp->next = NULL;
    tmp->hash_var_base = NULL;
    tmp->default_list = make_default_var_base();
    return tmp;
}

var_list *make_var_base(hash_var *global_hash_var){  // make the base for global_var
    var_list *tmp = make_var_list();
    tmp->hash_var_base = global_hash_var;
    return tmp;
}


var_list *append_var_list(hash_var *global_hash_var, var_list *var_list_base){  // make var_list[FILO]
    var_list *tmp = make_var_list();
    tmp->hash_var_base = global_hash_var;
    tmp->next = var_list_base;
    return tmp;
}

var_list *append_by_var_list(var_list *back_var_list, var_list *var_list_base){  // 拼凑两个var_list
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
        return_var = find_node(name, start->hash_var_base);
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
    login_node(name, value, start->hash_var_base);
}

var_list *copy_var_list(var_list *var_list_base){  // 复制一条var链到另一个内存地址上[base不复制]
    var_list *start = malloc(sizeof(var_list_base)), *tmp;
    memcpy(start, var_list_base, sizeof(var_list_base));  // 复制base节点
    tmp = start;  // 记录base节点
    while(1){  // 复制var_list链
        if(var_list_base == NULL){  // 已经匹配到了最后一个
            break;
        }
        var_list *next_tmp = malloc(sizeof(var_list_base));
        memcpy(next_tmp, var_list_base, sizeof(var_list_base));  // 复制到新的地方
        start->next = next_tmp;  // 应用新的地方
        start = start->next;
        var_list_base = var_list_base->next;
    }
    return tmp;
}