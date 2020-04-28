#include"token.h"
#include"lex.h"
#include "mem.h"

void factor(int *status, token_node *list);
void number(int *status, token_node *list);
void polynomial(int *status, token_node *list);

void paser_error(char *text);

/*
polynomial : factor
           | polynomial ADD factor
           | polynomial SUB factor
*/
void polynomial(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: polynomial\n", text);
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_polynomial){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);
        if(symbol.type == ADD_PASER || symbol.type == SUB_PASER){  // 模式2/3
            get_right_token(status, list, factor, right);  // 回调右边

            new_token.type = NON_polynomial;
            new_token.data_type = d_number;

            // 逻辑处理
            double l_num = left.data.d_number, r_num = right.data.d_number;

            if(symbol.type == ADD_PASER){
                new_token.data.d_number = l_num + r_num;
            }
            else{
                new_token.data.d_number = l_num - r_num;
            }
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return polynomial(status, list);  // 回调自己
        }
        else{  // 递归跳出
            printf("left.data.d_number = %f\n", left.data.d_number);
            fprintf(debug, "[info][grammar]  (polynomial)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (polynomial)back one token to (factor)\n");
        back_one_token(list, left);
        get_base_token(status, list, factor, new_token);

        new_token.type = NON_polynomial;
        add_node(list, new_token);
        return polynomial(status, list);  // 回调自己
    }
}

/*
factor : number
       | factor MUL number
       | factor DIV number
*/
void factor(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: factor\n", text);
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_factor){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == MUL_PASER || symbol.type == DIV_PASER){  // 模式2/3
            get_right_token(status, list, number, right);  // 回调右边

            new_token.type = NON_factor;
            new_token.data_type = d_number;

            // 逻辑操作
            double l_num = left.data.d_number, r_num;
            if(right.type == NON_dou){
                r_num = right.data.d_number;
            }
            else if(right.type == NON_int){
                r_num = (double)right.data.i_number;
            }

            if(symbol.type == MUL_PASER){
                new_token.data.d_number = l_num * r_num;
            }
            else{
                new_token.data.d_number = l_num / r_num;
            }
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return factor(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (factor)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (factor)back one token to (number)\n");
        back_one_token(list, left);
        get_base_token(status, list, number, new_token);

        if(new_token.type == NON_int){
            new_token.data.d_number = (double)new_token.data.i_number;
        }
        new_token.type = NON_factor;
        add_node(list, new_token);
        return factor(status, list);  // 回调自己
    }
}

/*
number : INT_PASER
       | DOUBLE_PASER
       | LB polynomial RB
*/
void number(int *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: number\n", text);
    token gett, new_token;

    gett = pop_node(list);  // 取得一个token

    if(gett.type == INT_PASER){  // int类型
        new_token.type = NON_int;
        new_token.data_type = i_number;
        new_token.data.i_number = atoi(gett.data.text);
        fprintf(status_log, "[info][grammar]  (number)get int number: %d\n", new_token.data.i_number);
    }
    else if(gett.type == DOUBLE_PASER){
        new_token.type = NON_dou;
        new_token.data_type = d_number;
        new_token.data.d_number = atof(gett.data.text);
        fprintf(status_log, "[info][grammar]  (number)get double number: %f\n", new_token.data.d_number);
    }
    else if(gett.type == LB_PASER){  // 模式3
        fprintf(status_log, "[info][grammar]  (number)get LB\n");
        get_right_token(status, list, polynomial, new_token);
        new_token.type = NON_dou;
        token rb;
        get_pop_token(status, list ,rb);
        if(rb.type != RB_PASER){  // 匹配失败
            paser_error("Don't get ')'");
        }
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (number)back one token\n");
        back_one_token(list, gett);
        return;
    }
    free(gett.data.text);  // 释放字符串
    fprintf(status_log, "[info][grammar]  (number)add one token\n");
    add_node(list, new_token);  // 压入节点
}

void paser_error(char *text){
    fprintf(status_log, "[error][grammar]  paser error : %s\n\n", text);
    exit(1);
}
