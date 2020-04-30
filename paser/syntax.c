#include"token.h"
#include"lex.h"
#include"../inter/interpreter.h"

void factor(int *status, token_node *list);
void power(int *status, token_node *list);
void call_down(int *status, token_node *list);
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
void bool_and(int *status, token_node *list);
void bool_or(int *status, token_node *list);
void bool_not(int *status, token_node *list);
void eq_number(int *status, token_node *list);
void call_back_(int *status, token_node *list);
void def_(int *status, token_node *list);
void ctrl_(int *status, token_node *list);
void var_ctrl_(int *status, token_node *list);
void return_(int *status, token_node *list);
void formal_parameter(int *status, token_node *list);

void paser_error(char *text);

/*
command_list : command
             | command_list command
*/
void command_list(int *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: command_list\n", text);
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
        fprintf(status_log, "[info][grammar]  (command_list)out again\n");
        back_one_token(list, left);
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
    else if(left.type == IF_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (if)\n");
        back_one_token(list, left);
        get_base_token(status, list, if_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == FOR_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (for)\n");
        back_one_token(list, left);
        get_base_token(status, list, for_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == DEF_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (def_)\n");
        back_one_token(list, left);
        get_base_token(status, list, def_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == BREAK_PASER || left.type == BROKEN_PASER || left.type == CONTINUE_PASER || left.type == CONTINUED_PASER ||
            left.type == RESTART_PASER || left.type == RESTARTED_PASER || left.type == REGO_PASER || left.type == REWENT_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (ctrl_)\n");
        back_one_token(list, left);
        get_base_token(status, list, ctrl_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == GLOBAL_PASER || left.type == DEFAULT_PASER || left.type == NOLOCAL_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (var_ctrl_)\n");
        back_one_token(list, left);
        get_base_token(status, list, var_ctrl_, new_token);

        get_stop_token();
        push_statement(statement_base, new_token);
    }
    else if(left.type == RETURN_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (return_)\n");
        back_one_token(list, left);
        get_base_token(status, list, return_, new_token);

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
            back_again(list, next_t);  // 下一次读取需要用safe_get_token
        }
        new_token.type = NON_if;
        new_token.data_type = statement_value;
        new_token.data.statement_value = if_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        
        token tmp_enter;
        tmp_enter.type = ENTER_PASER;
        tmp_enter.data_type = empty;
        back_again(list, tmp_enter);  // push入一个ENTER
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
def_ : DEF LB RB block
*/
void def_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: def_\n");
    token def_t, lb_t, rb_t, block_t, name_t, parameter_t, new_token;
    parameter *p_list;

    def_t = pop_node(list);
    if(def_t.type == DEF_PASER){
        get_right_token(status,list,element,name_t);  // 避免了top_exp把括号捕捉为call_back，不过，可以使用list设置status参数从而让call_back不捕捉[未实现]
        if(name_t.type != NON_element){  // 不是表达式
            paser_error("Don't get 'element'");
        }
        get_pop_token(status, list, lb_t);
        if(lb_t.type != LB_PASER){
            printf("lb_t.type = %d\n", lb_t.type);
            paser_error("Don't get '('");
        }
        get_pop_token(status, list, rb_t);
        if(rb_t.type != RB_PASER){  // 带参数
            back_one_token(list, rb_t);
            get_base_token(status,list,formal_parameter,parameter_t);  // 不需要safe_get_token
            if(parameter_t.type != NON_parameter){
                paser_error("Don't get formal_parameter");
            }
            get_pop_token(status, list, rb_t);
            printf("rb_t.type = %d\n", rb_t.type);
            if(rb_t.type != RB_PASER){
                paser_error("Don't get ')'[1]");
            }
            p_list = parameter_t.data.parameter_list;
        }
        else{
            p_list = NULL;  // 没参数
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *def_tmp =  make_statement();
        def_tmp->type = def;
        def_tmp->code.def.var = name_t.data.statement_value;
        def_tmp->code.def.parameter_list = p_list;
        def_tmp->code.def.done = block_t.data.statement_value;

        new_token.type = NON_def;
        new_token.data_type = statement_value;
        new_token.data.statement_value = def_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, def_t);
        return;
    }
}

void formal_parameter(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: formal_parameter\n");
    token left, next, comma, before, eq, value_token, new_token;
    int mode = only_value;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_parameter){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (formal_parameter)reduce right\n");
        get_pop_token(status, list, comma);
        if(comma.type == COMMA_PASER){
            get_pop_token(status, list, before);
            if(before.type == MUL_PASER){
                mode = put_args;
            }
            else if(before.type == POW_PASER){
                mode = put_kwargs;
            }
            else{
                mode = only_value;
                back_again(list,before);  // 回退
            }

            get_right_token(status, list, element, next);
            if(next.type != NON_element){
                paser_error("Don't get a top_exp");
                return;
            }

            new_token = left;
            parameter *tmp = NULL;
            get_pop_token(status, list, eq);
            if(eq.type == EQ_PASER){  // name_value模式
                get_right_token(status, list, top_exp, value_token);
                if(value_token.type != NON_top_exp){
                    paser_error("Don't get a top_exp");
                    return;
                }
                tmp = append_parameter_name(next.data.statement_value, new_token.data.parameter_list);
                tmp->type = name_value;
                tmp->u.value = value_token.data.statement_value;
            }
            else{
                back_again(list,eq);  // 回退[如果使用back_one_token则会导致add_node在EQ的后面]
                tmp = append_parameter_value(next.data.statement_value, new_token.data.parameter_list);
                tmp->type = mode;
                tmp->u.var = tmp->u.value;
            }

            add_node(list, new_token);
            return formal_parameter(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (formal_parameter)out\n");
            back_one_token(list, left);
            back_again(list, comma);
            return;
        }
    }
    else if(left.type == POW_PASER || left.type == MUL_PASER){  // 模式1
        fprintf(status_log, "[info][grammar]  (formal_parameter)back one token to (top_exp)[**/*]\n");
        get_right_token(status, list, element, next);  // 不需要back_one_token
        if(next.type != NON_element){
            back_one_token(list, next);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_parameter;
        new_token.data_type = parameter_list;
        new_token.data.parameter_list = make_parameter_value(next.data.statement_value);
        new_token.data.parameter_list->u.var = new_token.data.parameter_list->u.value;
        if(left.type == POW_PASER){
            new_token.data.parameter_list->type = put_kwargs;
        }
        else{
            new_token.data.parameter_list->type = put_args;
        }
        add_node(list, new_token);
        return formal_parameter(status, list);  // 回调自己
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (formal_parameter)back one token to (top_exp)\n");
        back_one_token(list, left);
        get_base_token(status, list, element, next);
        if(next.type != NON_element){
            back_one_token(list, next);  // 往回[不匹配类型]
            return;
        }

        new_token.type = NON_parameter;
        new_token.data_type = parameter_list;

        parameter *tmp = NULL;
        get_pop_token(status, list, eq);
        if(eq.type == EQ_PASER){  // name_value模式
            get_right_token(status, list, top_exp, value_token);
            if(value_token.type != NON_top_exp){
                paser_error("Don't get a top_exp");
                return;
            }
            puts("DEFAULT");
            printf("next.data.statement_value.type = %d\n", next.data.statement_value->type);
            new_token.data.parameter_list = make_parameter_name(next.data.statement_value);
            new_token.data.parameter_list->u.value = value_token.data.statement_value;
            new_token.data.parameter_list->type = name_value;
        }
        else{
            back_again(list,eq);  // 回退[如果使用back_one_token则会导致add_node在EQ的后面]
            new_token.data.parameter_list = make_parameter_value(next.data.statement_value);
            new_token.data.parameter_list->u.var = new_token.data.parameter_list->u.value;
            new_token.data.parameter_list->type = only_value;
        }
        add_node(list, new_token);
        return formal_parameter(status, list);  // 回调自己
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
    again:
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
        fprintf(status_log, "[tag 1]\n");
        return;
    }
    if(lp_t.type == ENTER_PASER){
        get_pop_token(status,list,lp_t);
        goto again;
    }
    else{
        printf("lp_t.type = %d != %d\n", lp_t.type, LP_PASER);
        back_one_token(list, lp_t);
        return;
    }
}

// var_ctrl_ 包含诸如：global, nolocal，之类的
void var_ctrl_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: bit_not\n");
    token left, var, right, new_token;
    statement *times = NULL;
    char *var_name = NULL;

    left = pop_node(list);
    if(left.type == GLOBAL_PASER || left.type == DEFAULT_PASER || left.type == NOLOCAL_PASER){
        fprintf(status_log, "[info][grammar]  (ctrl_)reduce right\n");

        get_right_token(status, list, top_exp, var);  // 取得base_var
        if(var.type != NON_top_exp && var.data.statement_value->type != base_var){
            paser_error("Don't get var");
        }
        else{
            var_name = malloc(sizeof(var.data.statement_value->code.base_var.var_name));
            strcpy(var_name, var.data.statement_value->code.base_var.var_name);
            times = var.data.statement_value->code.base_var.from;
            // TODO:: 本质上没有完全释放
            free(var.data.statement_value->code.base_var.var_name);
            free(var.data.statement_value);
        }

        if(left.type == DEFAULT_PASER){  // 设置times
            get_right_token(status, list, top_exp, right);  // 回调右边
            if(right.type != NON_top_exp){
                back_again(list, right);  // 不是期望的数字
            }
            else{
                times = right.data.statement_value;
            }
        }
        // 逻辑操作
        new_token.type = NON_ctrl;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        switch (left.type)
        {
            case GLOBAL_PASER:
                code_tmp->type = set_global;
                code_tmp->code.set_global.name = var_name;
                break;
            case DEFAULT_PASER:
                code_tmp->type = set_default;
                code_tmp->code.set_default.name = var_name;
                code_tmp->code.set_default.times = times;
                break;
            case NOLOCAL_PASER:
                code_tmp->type = set_nonlocal;
                code_tmp->code.set_nonlocal.name = var_name;
                break;
            default:
                break;
        }
        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        back_one_token(list, left);
        return;
    }
}

void return_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: return_\n");
    token left, right, value, new_token;
    statement *times = NULL, *back_value = NULL;

    left = pop_node(list);
    if(left.type == RETURN_PASER){
        fprintf(status_log, "[info][grammar]  (return_)reduce right\n");

        get_right_token(status, list, top_exp, value);  // 回调右边
        if(value.type != NON_top_exp){
            back_again(list, value);  // 不是期望的数字，就默认使用NULL，并且回退
            times = NULL;
            back_value = NULL;
            goto not_times;
        }
        else{
            back_value = value.data.statement_value;
        }

        get_right_token(status, list, top_exp, right);  // 回调右边
        if(right.type != NON_top_exp){
            back_again(list, right);  // 不是期望的数字，就默认使用NULL，并且回退
            times = NULL;
        }
        else{
            times = right.data.statement_value;
        }

        not_times:
        new_token.type = NON_return;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        code_tmp->type = return_code;
        code_tmp->code.return_code.times = times;
        code_tmp->code.return_code.value = back_value;
        
        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        back_one_token(list, left);
        return;
    }
}

// ctrl_包含诸如：break，broken，之类的
void ctrl_(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: bit_not\n");
    token left, right, new_token;
    statement *times = NULL;

    left = pop_node(list);
    if(left.type == BREAK_PASER || left.type == BROKEN_PASER || left.type == CONTINUE_PASER || left.type == CONTINUED_PASER ||
       left.type == RESTART_PASER || left.type == RESTARTED_PASER || left.type == REGO_PASER || left.type == REWENT_PASER){
        fprintf(status_log, "[info][grammar]  (ctrl_)reduce right\n");

        if(left.type != REGO_PASER && left.type != REWENT_PASER){
            get_right_token(status, list, top_exp, right);  // 回调右边
            if(right.type != NON_top_exp){
                back_again(list, right);  // 不是期望的数字，就默认使用NULL，并且回退
                times = NULL;
            }
            else{
                times = right.data.statement_value;
            }
        }
        // 逻辑操作
        new_token.type = NON_ctrl;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        switch (left.type)
        {
            case BREAK_PASER:
                code_tmp->type = break_cycle;
                code_tmp->code.break_cycle.times = times;
                break;
            case BROKEN_PASER:
                code_tmp->type = broken;
                code_tmp->code.broken.times = times;
                break;
            case CONTINUE_PASER:
                code_tmp->type = continue_cycle;
                code_tmp->code.continue_cycle.times = times;
                break;
            case CONTINUED_PASER:
                code_tmp->type = continued;
                code_tmp->code.continued.times = times;
                break;
            case RESTART_PASER:
                code_tmp->type = restart;
                code_tmp->code.restart.times = times;
                break;
            case RESTARTED_PASER:
                code_tmp->type = restarted;
                code_tmp->code.restarted.times = times;
                break;
            case REGO_PASER:
                code_tmp->type = rego;
                break;
            case REWENT_PASER:
                code_tmp->type = rewent;
                break;
            default:
                break;
        }
        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        back_one_token(list, left);
        return;
    }
}

/*
top_exp : polynomial
*/

void top_exp(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: top_exp\n");
    token exp;
    get_base_token(status,list,eq_number,exp);
    if(exp.type != NON_eq){
        back_one_token(list, exp);
        return;
    }
    exp.type = NON_top_exp;
    add_node(list, exp);  // 压入节点
    return;
}

/*
eq_number : bool_or
          | eq_number AND bool_or
*/
void eq_number(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: eq_number\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_eq){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (eq_number)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == EQ_PASER){  // 模式2/3
            get_right_token(status, list, call_back_, right);  // 回调右边
            if(right.type != NON_call){
                paser_error("Don't get a call_back_");
            }
            // 逻辑操作
            new_token.type = NON_eq;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = ASSIGnMENT_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return eq_number(status, list);  // 回调自己
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
        fprintf(status_log, "[info][grammar]  (bool_or)back one token to (bool_and)\n");
        back_one_token(list, left);
        get_base_token(status, list, call_back_, new_token);
        if(new_token.type != NON_call){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_eq;
        add_node(list, new_token);
        return eq_number(status, list);  // 回调自己
    }
}

/*
call_back_ : bool_or
           | call_back_ LB RB
*/
void call_back_(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: call_back_\n");
    token left, symbol, rb_t, new_token, parameter_t;
    parameter *p_list;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_call){
        fprintf(status_log, "[info][grammar]  (call_back_)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == LB_PASER){

            get_pop_token(status, list, rb_t);
            if(rb_t.type != RB_PASER){  // 带参数
                back_again(list, rb_t);
                get_right_token(status,list,formal_parameter,parameter_t);
                if(parameter_t.type != NON_parameter){
                    paser_error("Don't get formal_parameter");
                }
                printf("rb_t.type = %d\n", rb_t.type);
                get_pop_token(status, list, rb_t);
                if(rb_t.type != RB_PASER){
                    paser_error("Don't get ')'[2]");
                }
                p_list = parameter_t.data.parameter_list;
            }
            else{
                p_list = NULL;  // 没参数
            }

            // 逻辑操作
            new_token.type = NON_call;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = call;
            code_tmp->code.call.func = left.data.statement_value;
            code_tmp->code.call.parameter_list = p_list;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return call_back_(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (call_back_)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (call_back_)back one token to (bool_or)\n");
        back_one_token(list, left);
        get_base_token(status, list, bool_or, new_token);
        if(new_token.type != NON_bool_or){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_call;
        add_node(list, new_token);
        return call_back_(status, list);  // 回调自己
    }
}

/*
bool_or : bool_and
        | bool_or AND bool_and
*/
void bool_or(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bool_or\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bool_or){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bool_or)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == OR_PASER){  // 模式2/3
            get_right_token(status, list, bool_and, right);  // 回调右边
            if(right.type != NON_bool_and){
                paser_error("Don't get a compare");
            }
            // 逻辑操作
            new_token.type = NON_bool_or;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = OR_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bool_or(status, list);  // 回调自己
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
        fprintf(status_log, "[info][grammar]  (bool_or)back one token to (bool_and)\n");
        back_one_token(list, left);
        get_base_token(status, list, bool_and, new_token);
        if(new_token.type != NON_bool_and){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bool_or;
        add_node(list, new_token);
        return bool_or(status, list);  // 回调自己
    }
}

/*
bool_and : bool_not
         | bool_and AND bool_not
*/
void bool_and(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bool_and\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bool_and){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bool_and)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == AND_PASER){  // 模式2/3
            get_right_token(status, list, bool_not, right);  // 回调右边
            if(right.type != NON_bool_not){
                paser_error("Don't get a bool_not");
            }
            // 逻辑操作
            new_token.type = NON_bool_and;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = AND_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return bool_and(status, list);  // 回调自己
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
        fprintf(status_log, "[info][grammar]  (bool_and)back one token to (compare)\n");
        back_one_token(list, left);
        get_base_token(status, list, bool_not, new_token);
        if(new_token.type != NON_bool_not){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bool_and;
        add_node(list, new_token);
        return bool_and(status, list);  // 回调自己
    }
}

/*
bool_not : compare
         | BITNOT bool_not
*/
void bool_not(int *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: negative\n");
    token left, right, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NOT_PASER){  // 模式2
        fprintf(status_log, "[info][grammar]  (bool_not)reduce right\n");

        get_right_token(status, list, bool_not, right);  // 回调右边
        if(right.type != NON_bool_not){
            paser_error("Don't get a bool_not");
        }
        // 逻辑操作
        new_token.type = NON_bool_not;
        new_token.data_type = statement_value;

        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = right.data.statement_value;

        new_token.data.statement_value = code_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (negative)back one token to (compare)\n");
        back_one_token(list, left);
        get_base_token(status, list, compare, new_token);
        if(new_token.type != NON_compare){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_bool_not;
        add_node(list, new_token);
        return;
    }
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

        get_right_token(status, list, negative, right);  // 回调右边
        if(right.type != NON_negative){
            paser_error("Don't get a negative");
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

        get_right_token(status, list, bit_not, right);  // 回调右边
        if(right.type != NON_bit_not){
            paser_error("Don't get a bit_not");
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
            get_right_token(status, list, call_down, right);  // 回调右边
            if(right.type != NON_call_down){
                paser_error("Don't get a call_down");
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
        get_base_token(status, list, call_down, new_token);
        if(new_token.type != NON_call_down){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_power;
        add_node(list, new_token);
        return power(status, list);  // 回调自己
    }
}

/*
call_down : element
          | call_down LI top_exp RI
*/
void call_down(int *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: call_down\n");
    token left, lb_t, rb_t, new_token, parameter_t;
    parameter *p_list;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_call_down){
        fprintf(status_log, "[info][grammar]  (call_down)reduce right\n");
        get_pop_token(status, list, lb_t);
        if(lb_t.type == LI_PASER){
            get_right_token(status, list, top_exp, parameter_t);  // 回调右边
            if(parameter_t.type != NON_top_exp){
                paser_error("Don't get a top_exp");
            }

            get_pop_token(status, list, rb_t);
            if(rb_t.type != RI_PASER){  // 带参数
                paser_error("Don't get ']'");
            }

            // 逻辑操作
            new_token.type = NON_call_down;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = down;
            code_tmp->code.down.base_var = left.data.statement_value;
            code_tmp->code.down.child_var = parameter_t.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return call_down(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (call_back_)out\n");
            back_one_token(list, left);
            back_again(list, lb_t);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (call_down)back one token to (element)\n");
        back_one_token(list, left);
        get_base_token(status, list, element, new_token);
        if(new_token.type != NON_element){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_call_down;
        add_node(list, new_token);
        return call_down(status, list);  // 回调自己
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
