#include"token.h"

token_node *make_token_node(){
    token_node *tmp = (token_node *)malloc(sizeof(tmp));
    tmp->max_index = 0;
    tmp->seek = 0;
    tmp->max_size = 1;
    tmp->token_list = malloc(sizeof(token) * tmp->max_size);
    return tmp;
}

void add_node(token_node *list, token the_token){
    fprintf(status_log, "[debug][grammar]  add a token[seek : %d, index : %d, size : %d]\n", list->seek, list->max_index, list->max_size);
    if(list->max_size - list->max_index <= 1){
        list->max_size += 1;
        token *tmp = malloc(sizeof(token) * list->max_size);
        memcpy(tmp, list->token_list, sizeof(token) * (list->max_size));
        free(list->token_list);
        list->token_list = tmp;
    }

    if(list->seek < list->max_index){  // 有回退
        for(int i = list->max_index - 1;i >= list->seek;i -= 1){
            // printf("FFFF\n");
            memcpy(list->token_list + i + 1, list->token_list + i, sizeof(token));  // 往回复制
        }
    }

    list->token_list[list->seek] = the_token;
    list->max_index += 1;
    list->seek += 1;
    fprintf(status_log, "[debug][grammar]  after add a token[seek : %d, index : %d]\n", list->seek, list->max_index);
}

token pop_node(token_node *list){  // 弹出一个node
    list->max_index -= 1;
    list->seek -= 1;
    token tmp = list->token_list[list->seek];  // 返回的是seek
    for(int i = list->seek + 1;i <= list->max_index;i += 1){
        memcpy(list->token_list + i - 1, list->token_list + i, sizeof(token));  // 往回复制
    }
    fprintf(status_log, "[debug][grammar]  pop a token[seek : %d, index : %d]\n", list->seek, list->max_index);
    return tmp;
}

void safe_get_token(int *status, token_node *list){
    if(list->seek < list->max_index){  // 有回退
        fprintf(status_log, "[debug][grammar]  get token seek += 1 : %d, index : %d\n", list->seek, list->max_index);
        list->seek += 1;
    }
    else{  // 有回退绝对不可以get_token
        token tmp = get_token(status);
        fprintf(status_log, "[debug][grammar]  get token type : %d; data type : %d\n", tmp.type, tmp.data_type);
        add_node(list, tmp);
    }
}

void back_token(token_node *list){
    fprintf(status_log, "[debug][grammar]  back a token[seek : %d, index : %d]\n", list->seek, list->max_index);
    list->seek -= 1;  // 回退
}
