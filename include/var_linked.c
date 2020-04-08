#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef enum node_type{
    REAL = 1,
    INT,
    STRING,
    OBJECT,
    FIRST,
} node_type;


typedef union
    {
        double double_value;
        int int_value;
        char *string_value;
        void *object_value;
    } union_data;


typedef struct linked_node
{
    struct linked_node *next_link;
    struct linked_node *self_link;
    struct linked_node *last_link;
    char *name;
    node_type type;
    union_data data;
} linked_node;


linked_node *make_first_link();
void append(union_data data,node_type type, char *name, linked_node *first);
linked_node get_data(char *, linked_node *);
void free_all(linked_node *);
void print_all();
void to_free(void *);
void del(char *, linked_node *);


void del(char *name, linked_node *first){
    linked_node *last, *next, *self;
    linked_node *last_link = first;
    
    while (true){
        if (last_link->next_link == NULL){
            return;
        }
        if (last_link->last_link == NULL){
            last_link = (*last_link).next_link;
            continue;
        }
        else if (last_link->name == name){
            next = last_link->next_link;
            last = last_link->last_link;
            self = last_link;
            break;
        }
        last_link = (*last_link).next_link;
    }

    last->next_link = next;
    if(next != NULL){
        next->last_link = last;
    }
    to_free(self);
}


void free_all(linked_node *first){
    linked_node *next_link = first;
    while (true){
        if ((*next_link).next_link == NULL){
            to_free(next_link);
            break;
        }
        linked_node *tmp = (*next_link).next_link;
        to_free(next_link);
        next_link = tmp;
    }
}

void to_free(void *address){
    puts("-------------");
    printf("free : %u\n", address);
    free(address);
}

void print_all(linked_node *first){
    linked_node *last_link = first;
    puts("-------------");
    while (true){
        if ((*last_link).next_link == NULL){
            printf("address = %-9u, data = ",last_link);
            if ((*last_link).type == REAL){
                printf("%-7f",last_link->data.double_value);
            }else if ((*last_link).type == INT){
                printf("%-7d",last_link->data.int_value);
            }else if ((*last_link).type == STRING){
                printf("%-7s",last_link->data.string_value);
            }else if ((*last_link).type == OBJECT){
                printf("%-7d",last_link->data.object_value);
            }
            printf(", name = %-5s\n",(*last_link).name);
            break;
        }
        if (last_link->last_link == NULL){
            last_link = (*last_link).next_link;
            continue;
        }
        printf("address = %-9u, data = ",last_link);
        if ((*last_link).type == REAL){
            printf("%-7f",last_link->data.double_value);
        }else if ((*last_link).type == INT){
            printf("%-7d",last_link->data.int_value);
        }else if ((*last_link).type == STRING){
            printf("%-7s",last_link->data.string_value);
        }else if ((*last_link).type == OBJECT){
            printf("%-7d",last_link->data.object_value);
        }
        printf(", name = %-5s\n",(*last_link).name);
        last_link = (*last_link).next_link;
    }
}

linked_node get_data(char *name, linked_node *first){
    linked_node *last_link = first;
    while (true){
        if ((*last_link).next_link == NULL){  // 这个必须要在首位[如果链表为空]
            return (*first);
        }
        if ((*last_link).last_link == NULL){
            last_link = (*last_link).next_link;
            continue;
        }
        if ((*last_link).name == name){
            return (*last_link);
        }
        last_link = (*last_link).next_link;
    }
}

void append(union_data data,node_type type, char *name, linked_node *first){
    linked_node *last_link = first;
    int break_type = 1;
    while (true){
        if (last_link->next_link == NULL){  // 元素不存在
            if (last_link->name == name){  // 已经存在元素
                break_type = 2;
            }
            else{
                break_type = 1;
            }
            break;
        }
        if ((*last_link).last_link == NULL){  // 忽略首元素[不参与下面的匹配(上面得参与，不然会越界)]
            last_link = (*last_link).next_link;
            continue;
        }
        if (last_link->name == name){  // 已经存在元素
            break_type = 2;
            break;
        }
        last_link = last_link->next_link;
    }

    if(break_type == 2){
        last_link->data = data;
        return;
    }

    linked_node *new_link;
    new_link = malloc(sizeof(linked_node));
    if (new_link == NULL){
        return;
    }
    (*new_link).last_link = last_link;
    (*new_link).next_link = NULL;
    (*new_link).self_link = new_link;
    (*new_link).data = data;
    (*new_link).type = type;

    // 设置节点序号
    (*new_link).name = name;

    // 修改节点信息
    (*last_link).next_link = new_link;
}

linked_node *make_first_link(){
    linked_node *first;
    first = malloc(sizeof(linked_node));
    if (first == NULL){
        return NULL;
    }
    (*first).next_link = NULL;
    (*first).self_link = first;
    (*first).last_link = NULL;
    (*first).name = "";
    (*first).data.int_value = -1;
    (*first).type = FIRST;
    return first;
}
