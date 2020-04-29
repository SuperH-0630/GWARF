#include"token.h"
void print_node(token_node *list, char *from);

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
    print_node(list, "add_token");
}

token pop_node(token_node *list){  // 弹出一个node
    list->max_index -= 1;
    list->seek -= 1;
    token tmp = list->token_list[list->seek];  // 返回的是seek
    for(int i = list->seek + 1;i <= list->max_index;i += 1){
        memcpy(list->token_list + i - 1, list->token_list + i, sizeof(token));  // 往回复制
    }
    fprintf(status_log, "[debug][grammar]  pop a token[seek : %d, index : %d]\n", list->seek, list->max_index);
    print_node(list, "pop_token");
    return tmp;
}

void safe_get_token(int *status, token_node *list){
    if(list->seek < list->max_index){  // 有回退
        fprintf(status_log, "[debug][grammar]  get token seek += 1 : %d, index : %d\n", list->seek, list->max_index);
        list->seek += 1;
        print_node(list, "safe_get_token(move seek)");
    }
    else{  // 有回退绝对不可以get_token
        token tmp = get_token(status);
        fprintf(status_log, "[debug][grammar]  get token type : %d; data type : %d\n", tmp.type, tmp.data_type);
        add_node(list, tmp);
        print_node(list, "safe_get_token(get token)");
    }
}

void back_token(token_node *list){
    list->seek -= 1;  // 回退
    fprintf(status_log, "[debug][grammar]  back a token[seek : %d, index : %d]\n", list->seek, list->max_index);
    print_node(list, "back_token");
}

void print_node(token_node *list, char *from){  // 把FILO输出到 status_log
    static int count = 0;
    fprintf(token_log, "[debug][token : [%3d]]  token list[from %30s] :: ", count, from);
    fprintf(status_log, "[debug][token : [%3d]]\n", count);
    count += 1;
    int max = list->max_size;  // 迭代次数
    for(int i = 0; i < max; i += 1){
        if(i < list->max_index){  // 在范围内
            fprintf(token_log, "<token : %d ", list->token_list[i].type);
            if(i == list->seek){  // seek指针所在位置
                fprintf(token_log, "[seek] ");
            }
            else if(i + 1 == list->seek){
                fprintf(token_log, "[pop] ");
            }
            switch (list->token_list[i].data_type)
            {
            case text:
                fprintf(token_log, "data(text) ： %s ", list->token_list[i].data.text);
                break;
            case i_number:
                fprintf(token_log, "data(i_number) ： %d ", list->token_list[i].data.i_number);
                break;
            case d_number:
                fprintf(token_log, "data(d_number) ： %f ", list->token_list[i].data.d_number);
                break;
            case if_list_base:
                fprintf(token_log, "data(if_list_base) ： if_list_base on %x", list->token_list[i].data.if_list_base);
                break;
            case parameter_list:
                fprintf(token_log, "data(parameter_list) ： parameter_list on %x", list->token_list[i].data.parameter_list);
                break;
            case statement_value:
                fprintf(token_log, "data(statement_value) ： %d on %x ", list->token_list[i].data.statement_value->type, list->token_list[i].data.statement_value);
                break;
            default:
                break;
            }
            fprintf(token_log, "num = %d>", i);
        }
        else if(i == list->max_index && i == list->seek){
            fprintf(token_log, "<NULL [index/seek] num = %d>", i);
        }
        else if(i == list->max_index){
            fprintf(token_log, "<NULL [index] num = %d>", i);
        }
        else{
            fprintf(token_log, "<NULL num = %d>", i);
        }
        fprintf(token_log, " - ");
    }
    fprintf(token_log, " ||- END\n");
}