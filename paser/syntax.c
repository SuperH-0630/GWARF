#include"token.h"
#include"lex.h"
#include"../inter/interpreter.h"

void factor(int *status, token_node *list);
void power(int *status, token_node *list);
void number(int *status, token_node *list);
void element(int *status, token_node *list);
void var_token(int *status, token_node *list);
void polynomial(int *status, token_node *list);
void bit_move(int *status, token_node *list);
void command(int *status, token_node *list);
void while_(int *status, token_node *list);
void if_(int *status, token_node *list);
void for_(int *status, token_node *list);
void elif_(int *status, token_node *list);
void block_(int *status, token_node *list);
void top_exp(int *status, token_node *list);
void negative(int *status, token_node *list);
void bit_not(int *status, token_node *list);
void bit_notor(int *status, token_node *list);
void bit_or(int *status, token_node *list);
void bit_and(int *status, token_node *list);
void compare(int *status, token_node *list);

void paser_error(char *text);

/*
command_list : command
             | command_list command
*/
void command_list(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: top_exp\n", text);
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
            printf("right.type = %d\n", right.type);
            fprintf(status_log, "[info][grammar]  (command_list)out\n");
            back_one_token(list, left);
            back_again(list, right);
            return;
        }
    }
    else if(left.type == EOF_token){  // 递归跳出的条件
        fprintf(status_log, "[info][grammar]  (command_list)out\n");
        return;
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (command_list)back one token to (command)\n");
        back_one_token(list, left);
        get_base_token(status, list, command, new_token);
        if(new_token.type != NON_command){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_command_list;
        add_node(list, new_token);
        return command_list(status, list);  // 回调自己
    }
}

/*
command : top_exp <ENTER>
*/
void command(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: command\n", text);
    token left, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token
    if(left.type == WHILE_PASER){  // 是while类型的数据
        fprintf(status_log, "[info][grammar]  (command)back one token to (while)\n");
        back_one_token(list, left);
        get_base_token(status, list, while_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    if(left.type == IF_PASER){  // 是while类型的数据
        fprintf(status_log, "[info][grammar]  (command)back one token to (if)\n");
        back_one_token(list, left);
        get_base_token(status, list, if_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    if(left.type == FOR_PASER){  // 是while类型的数据
        fprintf(status_log, "[info][grammar]  (command)back one token to (for)\n");
        back_one_token(list, left);
        get_base_token(status, list, for_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == ENTER_PASER){
        fprintf(status_log, "[info][grammar]  (command)back <ENTER>\n");
    }
    else if(left.type == EOF_token){
        fprintf(status_log, "[info][grammar]  (command)back <EOF>\n");
        back_one_token(list, left);
        goto return_back;
    }
    else{  // 表达式
        fprintf(status_log, "[info][grammar]  (command)back one token to (top_exp)\n");
        back_one_token(list, left);
        get_base_token(status, list, top_exp, new_token);
        if(new_token.type != NON_top_exp){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        get_stop_token();
        push_statement(statement_base, new_token);
    }

    new_token.type = NON_command;
    add_node(list, new_token);

    return_back: 
    return;  // 回调自己
}

/*
if_ : IF LB top_exp RB block
*/
void if_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: if_\n");
    token if_t, lb_t, exp_t, rb_t, block_t, next_t, child_t, new_token;
    if_t = pop_node(list);
    if(if_t.type == IF_PASER){
        get_pop_token(status, list, lb_t);
        if(lb_t.type != LB_PASER){
            paser_error("Don't get '('");
        }
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
        }
        get_pop_token(status, list, rb_t);
        if(rb_t.type != RB_PASER){
            paser_error("Don't get ')'");
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *if_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if(exp_t.data.statement_value, block_t.data.statement_value);

        // 检查else和elseif
        el_again: 
        get_pop_token(status,list,next_t);
        if(next_t.type == ENTER_PASER){  // 忽略Enter
            goto el_again;
        }
        printf("next_t.type = %d\n", next_t.type);
        if(next_t.type == ELIF_PASER || next_t.type == ELSE_PASER){  // elif
            back_one_token(list, next_t);
            get_base_token(status,list,elif_,child_t);
            if(child_t.type == NON_elif){
                append_elif(child_t.data.if_list_base, if_tmp->code.if_branch.done);
                goto el_again;
            }
        }
        else{
            back_one_token(list, next_t);
        }

        new_token.type = NON_if;
        new_token.data_type = statement_value;
        new_token.data.statement_value = if_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, if_t);
        return;
    }
}

/*
elif_ : ELIF LB top_exp RB block
*/
void elif_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: elif_\n");
    token elif_t, lb_t, exp_t, rb_t, block_t, next_t, new_token;
    elif_t = pop_node(list);
    if(elif_t.type == ELIF_PASER){
        get_pop_token(status, list, lb_t);
        if(lb_t.type != LB_PASER){
            paser_error("Don't get '('");
        }
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
        }
        get_pop_token(status, list, rb_t);
        if(rb_t.type != RB_PASER){
            paser_error("Don't get ')'");
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        if_list *if_tmp =  make_if(exp_t.data.statement_value, block_t.data.statement_value);

        new_token.type = NON_elif;
        new_token.data_type = if_list_base;
        new_token.data.if_list_base = if_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    if(elif_t.type == ELSE_PASER){  // else
        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        if_list *if_tmp =  make_if(NULL, block_t.data.statement_value);

        new_token.type = NON_elif;
        new_token.data_type = if_list_base;
        new_token.data.if_list_base = if_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, elif_t);
        return;
    }
}

/*
for_ : FOR LB top_exp COMMA top_exp COMMA top_exp RB block
*/
void for_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token for_t, exp_1, exp_2, exp_3, block_t, lb_t, rb_t, comma_t,new_token;
    statement *exp_a, *exp_b, *exp_c;
    for_t = pop_node(list);
    if(for_t.type == FOR_PASER){
        get_pop_token(status, list, lb_t);
        if(lb_t.type != LB_PASER){
            paser_error("Don't get '('");
        }

        get_pop_token(status, list, exp_1);
        if(exp_1.type == COMMA_PASER){
            exp_a = NULL;  // exp_1 = NULL;
        }
        else{
            back_one_token(list, exp_1);
            get_base_token(status,list,top_exp,exp_1);  // 不是使用right token，不需要执行safe_get_token
            if(exp_1.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            get_pop_token(status, list, comma_t);
            if(comma_t.type != COMMA_PASER){
                paser_error("Don't get ';' in for cycle");
            }
            exp_a = exp_1.data.statement_value;
        }

        get_pop_token(status, list, exp_2);
        if(exp_2.type == COMMA_PASER){
            exp_b = NULL;  // exp_1 = NULL;
        }
        else{
            back_one_token(list, exp_2);
            get_base_token(status,list,top_exp,exp_2);  // 不是使用right token，不需要执行safe_get_token
            if(exp_2.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            get_pop_token(status, list, comma_t);
            if(comma_t.type != COMMA_PASER){
                paser_error("Don't get ';' in for cycle");
            }
            exp_b = exp_2.data.statement_value;
        }

        get_pop_token(status, list, exp_3);
        if(exp_3.type == RB_PASER){
            exp_c = NULL;  // exp_1 = NULL;
            back_one_token(list, exp_3);
        }
        else{
            back_one_token(list, exp_3);
            get_base_token(status,list,top_exp,exp_3);  // 不是使用right token，不需要执行safe_get_token
            if(exp_3.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            exp_c = exp_3.data.statement_value;
        }

        get_pop_token(status, list, rb_t);
        if(rb_t.type != RB_PASER){
            paser_error("Don't get ')'");
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = exp_a;
        for_tmp->code.for_cycle.condition = exp_b;
        for_tmp->code.for_cycle.after = exp_c;
        for_tmp->code.for_cycle.done = block_t.data.statement_value;

        new_token.type = NON_for;
        new_token.data_type = statement_value;
        new_token.data.statement_value = for_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, for_t);
        return;
    }
}

/*
while_ : WHILE LB top_exp RB block
*/
void while_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token while_t, lb_t, exp_t, rb_t, block_t, new_token;
    while_t = pop_node(list);
    if(while_t.type == WHILE_PASER){
        get_pop_token(status, list, lb_t);
        if(lb_t.type != LB_PASER){
            paser_error("Don't get '('");
        }
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
        }
        get_pop_token(status, list, rb_t);
        if(rb_t.type != RB_PASER){
            paser_error("Don't get ')'");
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = exp_t.data.statement_value;
        while_tmp->code.while_cycle.done = block_t.data.statement_value;

        new_token.type = NON_while;
        new_token.data_type = statement_value;
        new_token.data.statement_value = while_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, while_t);
        return;
    }
}

/*
block_ : LP command_list RB
*/
void block_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: block_\n");
    token lp_t, rp_t, new_token, command_list_t;
    lp_t = pop_node(list);
    if(lp_t.type == LP_PASER){
        statement *block_tmp =  make_statement();
        statement_base = append_statement_list(block_tmp, statement_base);
        
        get_right_token(status,list,command_list,command_list_t);  // 要把command_list也弹出来

        statement_base = free_statement_list(statement_base);  // 重新释放
        get_pop_token(status, list, rp_t);
        if(rp_t.type != RP_PASER){
            paser_error("Don't get '}'");
        }
        new_token.type = NON_block;
        new_token.data_type = statement_value;
        new_token.data.statement_value = block_tmp;
        add_node(list, new_token);  // 压入节点
        return;
    }
    else{
        back_one_token(list, lp_t);
        return;
    }
}

/*
top_exp : polynomial
*/

void top_exp(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: top_exp\n");
    token exp;
    get_base_token(status,list,compare,exp);
    if(exp.type != NON_compare){
        back_one_token(list, exp);
        return;
    }
    exp.type = NON_top_exp;
    add_node(list, exp);  // 压入节点
    return;
}

void compare(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: polynomial\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_compare){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (polynomial)reduce right\n");
        get_pop_token(status, list, symbol);
        if(symbol.type == EQEQ_PASER || symbol.type == MOREEQ_PASER || symbol.type == LESSEQ_PASER ||
           symbol.type == MORE_PASER || symbol.type == LESS_PASER || symbol.type == NOTEQ_PASER){  // 模式2/3
            get_right_token(status, list, bit_notor, right);  // 回调右边
            if(right.type != NON_bit_notor){
                paser_error("Don't get a bit_notor");
            }
            new_token.type = NON_compare;
            new_token.data_type = statement_value;
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;

            if(symbol.type == EQEQ_PASER){
                code_tmp->code.operation.type = EQUAL_func;
            }
            else if(symbol.type == MOREEQ_PASER){
                code_tmp->code.operation.type = MOREEQ_func;
            }
            else if(symbol.type == LESSEQ_PASER){
                code_tmp->code.operation.type = LESSEQ_func;
            }
            else if(symbol.type == MORE_PASER){
                code_tmp->code.operation.type = MORE_func;
            }
            else if(symbol.type == LESS_PASER){
                code_tmp->code.operation.type = LESS_func;
            }
            else{
                code_tmp->code.operation.type = NOTEQ_func;
            }
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            new_token.data.statement_value = code_tmp;

            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return compare(status, list);  // 回调自己
        }
        else{  // 递归跳出
            fprintf(status_log, "[info][grammar]  (polynomial)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (polynomial)back one token to (factor)\n");
        back_one_token(list, left);
        get_base_token(status, list, bit_notor, new_token);
        if(new_token.type != NON_bit_notor){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_compare;
        add_node(list, new_token);
        return compare(status, list);  // 回调自己
    }
}

/*
bit_notor : bit_or
          | bit_notor BITOR bit_or
*/
void bit_notor(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bit_or\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_notor){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bit_or)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == BITNOTOR_PASER){  // 模式2/3
            get_right_token(status, list, bit_or, right);  // 回调右边
            if(right.type != NON_bit_or){
                paser_error("Don't get a bit_or");
            }
            // 逻辑操作
            new_token.type = NON_bit_notor;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = BITNOTOR_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bit_notor(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (bit_notor)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (bit_or)back one token to (bit_and)\n");
        back_one_token(list, left);
        get_base_token(status, list, bit_or, new_token);
        if(new_token.type != NON_bit_or){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bit_notor;
        add_node(list, new_token);
        return bit_notor(status, list);  // 回调自己
    }
}

/*
bit_or : bit_and
       | bit_or BITOR bit_and
*/
void bit_or(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bit_or\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_or){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bit_or)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == BITOR_PASER){  // 模式2/3
            get_right_token(status, list, bit_and, right);  // 回调右边
            if(right.type != NON_bit_and){
                paser_error("Don't get a bit_and");
            }
            // 逻辑操作
            new_token.type = NON_bit_or;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = BITOR_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bit_or(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (bit_or)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (bit_or)back one token to (bit_and)\n");
        back_one_token(list, left);
        get_base_token(status, list, bit_and, new_token);
        if(new_token.type != NON_bit_and){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bit_or;
        add_node(list, new_token);
        return bit_or(status, list);  // 回调自己
    }
}

/*
bit_and : bit_move
        | bit_and BITAND bit_move
*/
void bit_and(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bit_and\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_and){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == BITAND_PASER){  // 模式2/3
            get_right_token(status, list, bit_move, right);  // 回调右边
            if(right.type != NON_bit_move){
                paser_error("Don't get a bit_move");
            }
            // 逻辑操作
            new_token.type = NON_bit_and;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = BITAND_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bit_and(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (bit_and)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (bit_move)back one token to (factor)\n");
        back_one_token(list, left);
        get_base_token(status, list, bit_move, new_token);
        if(new_token.type != NON_bit_move){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bit_and;
        add_node(list, new_token);
        return bit_and(status, list);  // 回调自己
    }
}

/*
bit_move : power
         | bit_move BITRIGHT factor
         | bit_move BITLEFT factor
*/
void bit_move(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: factor\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_move){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == BITRIGHT_PASER || symbol.type == BITLEFT_PASER){  // 模式2/3
            get_right_token(status, list, polynomial, right);  // 回调右边
            if(right.type != NON_polynomial){
                paser_error("Don't get a polynomial");
            }
            // 逻辑操作
            new_token.type = NON_bit_move;
            new_token.data_type = statement_value;
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;

            if(symbol.type == BITRIGHT_PASER){
                code_tmp->code.operation.type = BITRIGHT_func;
            }
            else{
                code_tmp->code.operation.type = BITLEFT_func;
            }
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bit_move(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (bit_move)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (bit_move)back one token to (factor)\n");
        back_one_token(list, left);
        get_base_token(status, list, polynomial, new_token);
        if(new_token.type != NON_polynomial){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bit_move;
        add_node(list, new_token);
        return bit_move(status, list);  // 回调自己
    }
}


/*
polynomial : factor
           | polynomial ADD factor
           | polynomial SUB factor
*/
void polynomial(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: polynomial\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_polynomial){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (polynomial)reduce right\n");
        get_pop_token(status, list, symbol);
        if(symbol.type == ADD_PASER || symbol.type == SUB_PASER){  // 模式2/3
            get_right_token(status, list, factor, right);  // 回调右边
            if(right.type != NON_factor){
                paser_error("Don't get a factor");
            }
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
            fprintf(status_log, "[info][grammar]  (polynomial)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (polynomial)back one token to (factor)\n");
        back_one_token(list, left);
        get_base_token(status, list, factor, new_token);
        if(new_token.type != NON_factor){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_polynomial;
        add_node(list, new_token);
        return polynomial(status, list);  // 回调自己
    }
}

/*
factor : power
       | factor MUL power
       | factor DIV power
*/
void factor(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: factor\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_factor){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == MUL_PASER || symbol.type == DIV_PASER){  // 模式2/3
            get_right_token(status, list, negative, right);  // 回调右边
            if(right.type != NON_negative){
                paser_error("Don't get a value");
            }
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
        fprintf(status_log, "[info][grammar]  (factor)back one token to (element)\n");
        back_one_token(list, left);
        get_base_token(status, list, negative, new_token);
        if(new_token.type != NON_negative){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_factor;
        add_node(list, new_token);
        return factor(status, list);  // 回调自己
    }
}

/*
negative : bit_not
         | BITNOT bit_not
*/
void negative(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: negative\n");
    token left, right, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == SUB_PASER){  // 模式2
        fprintf(status_log, "[info][grammar]  (bit_not)reduce right\n");

        get_right_token(status, list, bit_not, right);  // 回调右边
        if(right.type != NON_bit_not){
            paser_error("Don't get a bit_not");
        }
        // 逻辑操作
        new_token.type = NON_negative;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NEGATIVE_func;

        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = right.data.statement_value;
        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (negative)back one token to (bit_not)\n");
        back_one_token(list, left);
        get_base_token(status, list, bit_not, new_token);
        if(new_token.type != NON_bit_not){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_negative;
        add_node(list, new_token);
        return;
    }
}

/*
bit_not : power
        | BITNOT power
*/
void bit_not(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: bit_not\n");
    token left, right, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == BITNOT_PASER){  // 模式2
        fprintf(status_log, "[info][grammar]  (bit_not)reduce right\n");

        get_right_token(status, list, power, right);  // 回调右边
        if(right.type != NON_power){
            paser_error("Don't get a power");
        }
        // 逻辑操作
        new_token.type = NON_bit_not;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOT_func;

        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = right.data.statement_value;
        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (bit_not)back one token to (power)\n");
        back_one_token(list, left);
        get_base_token(status, list, power, new_token);
        if(new_token.type != NON_power){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bit_not;
        add_node(list, new_token);
        return;
    }
}

/*
power : element
      | power POW element
      | power LOG element
      | power SQRT element
*/
void power(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: power\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_power){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (power)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == POW_PASER || symbol.type == LOG_PASER || symbol.type == SQRT_PASER){  // 模式2/3/4
            get_right_token(status, list, element, right);  // 回调右边
            if(right.type != NON_element){
                paser_error("Don't get a value");
            }
            // 逻辑操作
            new_token.type = NON_power;
            new_token.data_type = statement_value;
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;

            if(symbol.type == POW_PASER){
                code_tmp->code.operation.type = POW_func;
            }
            else if(symbol.type == LOG_PASER){
                code_tmp->code.operation.type = LOG_func;
            }
            else{
                code_tmp->code.operation.type = SQRT_func;
            }
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return power(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (power)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (power)back one token to (element)\n");
        back_one_token(list, left);
        get_base_token(status, list, element, new_token);
        if(new_token.type != NON_element){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_power;
        add_node(list, new_token);
        return power(status, list);  // 回调自己
    }
}

/*
element : number
        | LB top_exp RB
*/
void element(int *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: element\n");
    token gett, new_token;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == LB_PASER){  // 模式3
        fprintf(status_log, "[info][grammar]  (element)get LB\n");
        get_right_token(status, list, top_exp, new_token);
        if(new_token.type != NON_top_exp){
            paser_error("Don't get 'top_exp'");            
        }
        token rb;
        get_pop_token(status, list ,rb);
        if(rb.type != RB_PASER){  // 匹配失败
            paser_error("Don't get ')'");
        }
        new_token.type = NON_element;
        add_node(list, new_token);  // 压入节点
        return;
    }
    else if(gett.type == VAR_PASER){  // a
        back_one_token(list, gett);
        get_base_token(status, list, var_token, new_token);
        if(new_token.type != NON_base_var){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_element;
        add_node(list, new_token);
        return;
    }
    else if(gett.type == LI_PASER){  // [1]a或[1]列表或[1,2,3,4]列表
        back_one_token(list, gett);
        token exp_token, rb, tmp_var;
        get_right_token(status, list, top_exp, exp_token);
        if(exp_token.type != NON_top_exp){
            paser_error("Don't get 'top_exp'");            
        }
        get_pop_token(status, list ,rb);
        if(rb.type != RI_PASER){  // 匹配失败  TODO:: 检查是不是[1,2,3,4]的列表类型
            paser_error("Don't get ']'");
        }
        get_pop_token(status, list ,tmp_var);
        if(tmp_var.type == VAR_PASER){  // a
            back_one_token(list, tmp_var);
            get_base_token(status, list, var_token, new_token);
            if(new_token.type != NON_base_var){
                paser_error("Don't get var");
            }
            new_token.data.statement_value->code.base_var.from = exp_token.data.statement_value;
        }
        new_token.type = NON_element;
        add_node(list, new_token);
        return;
    }
    else{
        fprintf(status_log, "[info][grammar]  (element)back one token to (number)\n");
        back_one_token(list, gett);
        get_base_token(status, list, number, new_token);
        if(new_token.type != NON_base_value){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_element;
        add_node(list, new_token);
        return;

    }
}
/*
var_token : VAR
*/
void var_token(int *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: var_token\n");
    token gett, new_token;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == VAR_PASER){  // var类型
        new_token.type = NON_base_var;

        GWARF_value tmp_value;
        tmp_value.type = INT_value;
        tmp_value.value.int_value = atoi(gett.data.text);

        statement *code_tmp =  make_statement();
        code_tmp->type = base_var;
        code_tmp->code.base_var.var_name = gett.data.text;
        code_tmp->code.base_var.from = NULL;
        
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (var_token)out\n");
        add_node(list, new_token);  // 压入节点
        return;
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (var_token)back one token\n");
        back_one_token(list, gett);
        return;
    }
}

/*
number : INT_PASER
       | DOUBLE_PASER
       | LB top_exp RB
*/
void number(int *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: number\n");
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
    printf("[error][grammar]  paser error : %s\n\n", text);
    exit(1);
}
