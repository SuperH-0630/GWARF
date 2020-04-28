#include"token.h"
#include"lex.h"
#include"../inter/interpreter.h"

void factor(int *status, token_node *list);
void number(int *status, token_node *list);
void polynomial(int *status, token_node *list);
void command(int *status, token_node *list);

void paser_error(char *text);

/*
command_list : command
             | command_list command
*/
void command_list(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: polynomial\n", text);
    token left, right, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_command_list){  // 模式2
        fprintf(status_log, "[info][grammar]  (command_list)reduce right\n");
        get_right_token(status, list, command, right);  // 回调右边
        
        if(right.type == NON_command){
            new_token.type = NON_command_list;
            new_token.data_type = empty;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return command_list(status, list);  // 回调自己
        }
        else{  // 递归跳出[EOF_token]
            fprintf(debug, "[info][grammar]  (command_list)out\n");
            back_one_token(list, left);  // 理论上不back也可以
            return;
        }
    }
    else if(left.type == EOF_token){  // 递归跳出的条件
        fprintf(debug, "[info][grammar]  (command_list)out\n");
        return;
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (command_list)back one token to (command)\n");
        back_one_token(list, left);
        get_base_token(status, list, command, new_token);

        new_token.type = NON_command_list;
        add_node(list, new_token);
        return command_list(status, list);  // 回调自己
    }
}

/*
command : polynomial <ENTER>
*/
void command(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: polynomial\n", text);
    token left, stop, new_token;

    new_token.type = NON_command;
    new_token.data_type = statement_value;
    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == ENTER_PASER){
        fprintf(status_log, "[info][grammar]  (command)back <ENTER>\n");
    }
    else if(left.type == EOF_token){
        fprintf(status_log, "[info][grammar]  (command)back <EOF>\n");
        back_one_token(list, left);
        goto return_back;
    }
    else{
        fprintf(status_log, "[info][grammar]  (command)back one token to (polynomial)\n");
        back_one_token(list, left);
        get_base_token(status, list, polynomial, new_token);

        get_pop_token(status, list, stop);
        if(stop.type != ENTER_PASER && stop.type != EOF_token){
            paser_error("Don't get stop token or EOF");
        }
        if(stop.type == EOF_token){
            back_one_token(list, stop);
        }

        statement *tmp = find_statement_list(0, statement_base);
        append_statement(tmp, new_token.data.statement_value);
    }
    add_node(list, new_token);

    return_back: 
    return;  // 回调自己
}

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
        fprintf(status_log, "[info][grammar]  (polynomial)reduce right\n");
        get_pop_token(status, list, symbol);
        if(symbol.type == ADD_PASER || symbol.type == SUB_PASER){  // 模式2/3
            get_right_token(status, list, factor, right);  // 回调右边

            new_token.type = NON_polynomial;
            new_token.data_type = statement_value;
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;

            if(symbol.type == ADD_PASER){
                code_tmp->code.operation.type = ADD_func;
            }
            else{
                code_tmp->code.operation.type = SUB_func;
            }
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            new_token.data.statement_value = code_tmp;

            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return polynomial(status, list);  // 回调自己
        }
        else{  // 递归跳出
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

            // 逻辑操作
            new_token.type = NON_factor;
            new_token.data_type = statement_value;
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;

            if(symbol.type == MUL_PASER){
                code_tmp->code.operation.type = MUL_func;
            }
            else{
                code_tmp->code.operation.type = DIV_func;
            }
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            new_token.data.statement_value = code_tmp;
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
        new_token.type = NON_base_value;

        GWARF_value tmp_value;
        tmp_value.type = INT_value;
        tmp_value.value.int_value = atoi(gett.data.text);

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("int", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (number)get int number: %d\n", tmp_value.value.int_value);
    }
    else if(gett.type == DOUBLE_PASER){
        new_token.type = NON_base_value;

        GWARF_value tmp_value;
        tmp_value.type = NUMBER_value;
        tmp_value.value.double_value = atof(gett.data.text);

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("double", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (number)get double number: %f\n", new_token.data.d_number);
    }
    else if(gett.type == LB_PASER){  // 模式3
        fprintf(status_log, "[info][grammar]  (number)get LB\n");
        get_right_token(status, list, polynomial, new_token);
        new_token.type = NON_base_value;
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
