#include"token.h"
#include"lex.h"
#include"../inter/interpreter.h"

void factor(p_status *status, token_node *list);
void power(p_status *status, token_node *list);
void call_down(p_status *status, token_node *list);
void paser_value(p_status *status, token_node *list);
void element(p_status *status, token_node *list);
void var_token(p_status *status, token_node *list);
void polynomial(p_status *status, token_node *list);
void bit_move(p_status *status, token_node *list);
void command(p_status *status, token_node *list);
void while_(p_status *status, token_node *list);
void if_(p_status *status, token_node *list);
void for_(p_status *status, token_node *list);
void elif_(p_status *status, token_node *list);
void block_(p_status *status, token_node *list);
void top_exp(p_status *status, token_node *list);
void negative(p_status *status, token_node *list);
void bit_not(p_status *status, token_node *list);
void bit_notor(p_status *status, token_node *list);
void bit_or(p_status *status, token_node *list);
void bit_and(p_status *status, token_node *list);
void compare(p_status *status, token_node *list);
void bool_and(p_status *status, token_node *list);
void bool_or(p_status *status, token_node *list);
void bool_not(p_status *status, token_node *list);
void eq_number(p_status *status, token_node *list);
void call_back_(p_status *status, token_node *list);
void def_class(p_status *status, token_node *list);
void ctrl_(p_status *status, token_node *list);
void var_ctrl_(p_status *status, token_node *list);
void return_(p_status *status, token_node *list);
void formal_parameter(p_status *status, token_node *list);
void list_(p_status *status, token_node *list);
void dict_(p_status *status, token_node *list);
void hide_list(p_status *status, token_node *list);
void do_while_(p_status *status, token_node *list);
void try_(p_status *status, token_node *list);
void out_exception(p_status *status, token_node *list);
void self_exp(p_status *status, token_node *list);
void lambda_(p_status *status, token_node *list);
void attribute(p_status *status, token_node *list);
void import_include(p_status *status, token_node *list);
void chose_exp_(p_status *status, token_node *list);
void svar_token(p_status *status, token_node *list);
void paser_error(char *text);

/*
command_list : command
             | command_list command
*/
void command_list(p_status *status, token_node *list){  // 多项式
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
void command(p_status *old_status, token_node *list){  // 多项式
    p_status status;
    status = *old_status;
    status.is_left = false;  // is_left复位[只有top_exp会开启以及element会开启]
    fprintf(status_log, "[info][grammar]  mode status: command\n", text);
    token left, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token
    if(left.type == WHILE_PASER){  // 是while类型的数据
        fprintf(status_log, "[info][grammar]  (command)back one token to (while)\n");
        back_one_token(list, left);
        get_base_token(&status, list, while_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == IF_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (if)\n");
        back_one_token(list, left);
        get_base_token(&status, list, if_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == FOR_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (for)\n");
        back_one_token(list, left);
        get_base_token(&status, list, for_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == DEF_PASER || left.type == FUNC_PASER || left.type == CLASS_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (def_class)\n");
        back_one_token(list, left);
        get_base_token(&status, list, def_class, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == BREAK_PASER || left.type == BROKEN_PASER || left.type == CONTINUE_PASER || left.type == CONTINUED_PASER ||
            left.type == RESTART_PASER || left.type == RESTARTED_PASER || left.type == REGO_PASER || left.type == REWENT_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (ctrl_)\n");
        back_one_token(list, left);
        get_base_token(&status, list, ctrl_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == GLOBAL_PASER || left.type == DEFAULT_PASER || left.type == NOLOCAL_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (var_ctrl_)\n");
        back_one_token(list, left);
        get_base_token(&status, list, var_ctrl_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == IMPORT_PASER || left.type == INCLUDE_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (import_include)\n");
        back_one_token(list, left);
        get_base_token(&status, list, import_include, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == RETURN_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (return_)\n");
        back_one_token(list, left);
        get_base_token(&status, list, return_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == TRY_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (try_)\n");
        back_one_token(list, left);
        get_base_token(&status, list, try_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == DO_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (do/do...while)\n");
        back_one_token(list, left);
        get_base_token(&status, list, do_while_, new_token);

        get_stop_token(status, list);
        push_statement(statement_base, new_token);
    }
    else if(left.type == RAISE_PASER || left.type == THROW_PASER || left.type == ASSERT_PASER){
        fprintf(status_log, "[info][grammar]  (command)back one token to (out_exception)\n");
        back_one_token(list, left);
        get_base_token(&status, list, out_exception, new_token);

        get_stop_token(status, list);
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
        status.is_left = true;
        get_base_token(&status, list, top_exp, new_token);
        status.is_left = false;
        if(new_token.type != NON_top_exp){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        get_stop_token(status, list);
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
void if_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: if_\n");
    token if_t, exp_t, block_t, next_t, child_t, new_token;
    if_t = pop_node(list);
    if(if_t.type == IF_PASER){
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
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
void elif_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: elif_\n");
    token elif_t, exp_t, block_t, next_t, new_token;
    elif_t = pop_node(list);
    if(elif_t.type == ELIF_PASER){
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
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
void for_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: for_\n");
    token for_t, exp_1, exp_2, exp_3, block_t, comma_t,new_token;
    statement *exp_a, *exp_b, *exp_c;
    for_t = pop_node(list);
    if(for_t.type == FOR_PASER){
        bool is_for_in = false;  // 是否为for in模式


        get_pop_token(status, list, exp_1);
        if(exp_1.type == COMMA_PASER){
            exp_a = NULL;  // exp_1 = NULL;
        }
        else{
            back_one_token(list, exp_1);
            p_status new_status;
            new_status = *status;
            new_status.is_for = true;
            get_base_token(&new_status,list,top_exp,exp_1);  // 不是使用right token，不需要执行safe_get_token
            new_status.is_for = false;
            if(exp_1.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            get_pop_token(status, list, comma_t);
            if(comma_t.type == IN_PASER){  // for in 模式 -> exp1不可以为NULL
                is_for_in = true;
                exp_a = exp_1.data.statement_value;
                goto exp3;
            }
            else if(comma_t.type != COMMA_PASER){
                paser_error("Don't get ',' in for cycle");
            }
            exp_a = exp_1.data.statement_value;
        }

        get_pop_token(status, list, exp_2);
        if(exp_2.type == COMMA_PASER){
            exp_b = NULL;  // exp_1 = NULL;
        }
        else{
            back_one_token(list, exp_2);
            p_status new_status;
            new_status = *status;
            new_status.is_for = true;
            get_base_token(&new_status,list,top_exp,exp_2);  // 不是使用right token，不需要执行safe_get_token
            new_status.is_for = false;
            if(exp_2.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            get_pop_token(status, list, comma_t);
            if(comma_t.type != COMMA_PASER){
                paser_error("Don't get ',' in for cycle");
            }
            exp_b = exp_2.data.statement_value;
        }

        exp3:

        get_pop_token(status, list, exp_3);
        if(exp_3.type == COMMA_PASER){
            if(is_for_in){
                paser_error("Don't get iter object");
            }
            exp_c = NULL;  // exp_1 = NULL;
        }
        else{
            back_one_token(list, exp_3);
            p_status new_status;
            new_status = *status;
            if(!is_for_in) new_status.is_for = true;
            get_base_token(&new_status,list,top_exp,exp_3);  // 不是使用right token，不需要执行safe_get_token
            if(!is_for_in) new_status.is_for = false;
            if(exp_3.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            if(!is_for_in){  // for in 不需要匹配“,”
                get_pop_token(status, list, comma_t);
                if(comma_t.type != COMMA_PASER){
                    paser_error("Don't get ',' in for cycle");
                }
            }
            exp_c = exp_3.data.statement_value;
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *for_tmp =  make_statement();
        if(is_for_in){
            for_tmp->type = for_in_cycle;
            for_tmp->code.for_in_cycle.var = exp_a;
            for_tmp->code.for_in_cycle.iter = exp_c;
            for_tmp->code.for_in_cycle.done = block_t.data.statement_value;
        }
        else{
            for_tmp->type = for_cycle;
            for_tmp->code.for_cycle.first = exp_a;
            for_tmp->code.for_cycle.condition = exp_b;
            for_tmp->code.for_cycle.after = exp_c;
            for_tmp->code.for_cycle.done = block_t.data.statement_value;
        }

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
void def_class(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: def_\n");
    token def_t, lb_t, rb_t, block_t, name_t, parameter_t, new_token;
    parameter *p_list;

    def_t = pop_node(list);
    if(def_t.type == DEF_PASER || def_t.type == FUNC_PASER || def_t.type == CLASS_PASER){
        p_status new_status;
        new_status = *status;
        new_status.not_match_tuple = true;
        new_status.not_match_call = true;
        get_right_token(&new_status,list,top_exp,name_t);  // 避免了top_exp把括号捕捉为call_back，不过，可以使用list设置status参数从而让call_back不捕捉[未实现]
        if(name_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
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
            printf("parameter_t = %d\n", parameter_t.data.parameter_list->u.var->type);
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
        if(def_t.type == DEF_PASER || def_t.type == FUNC_PASER){
            def_tmp->type = def;
            def_tmp->code.def.var = name_t.data.statement_value;
            def_tmp->code.def.parameter_list = p_list;
            def_tmp->code.def.done = block_t.data.statement_value;
            def_tmp->code.def.type = (def_t.type == DEF_PASER) ? auto_func : function;
        }
        else{
            def_tmp->type = set_class;
            def_tmp->code.set_class.var = name_t.data.statement_value;
            def_tmp->code.set_class.father_list = p_list;
            def_tmp->code.set_class.done = block_t.data.statement_value;
        }

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

void formal_parameter(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: formal_parameter\n");
    token left, next, comma, before, eq, value_token, new_token;
    int mode = only_value;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_parameter){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (formal_parameter)reduce right\n");
        get_pop_token(status, list, comma);
        if(comma.type == (status->is_slice ? COLON_PASER : COMMA_PASER)){
            get_pop_token(status, list, before);
            if(before.type == MUL_PASER){
                if(status->match_dict){
                    paser_error("dict shouldn't get '*'");
                }
                mode = put_args;
            }
            else if(before.type == POW_PASER){
                if(status->match_list){
                    paser_error("list shouldn't get '*'");
                }
                mode = put_kwargs;
            }
            else{
                mode = only_value;
                back_again(list,before);  // 回退
            }
            p_status new_status;
            new_status = *status;
            new_status.not_match_eq = true;
            new_status.not_match_tuple = true;
            token tmp_next;
            get_right_token(&new_status, list, top_exp, tmp_next);
            if(tmp_next.type != NON_top_exp){  // 结尾分号 -> 虚解包
                if(!status->is_args){
                    back_again(list, tmp_next);
                    next.type = NON_top_exp;
                    next.data_type = statement_value;
                    next.data.statement_value = make_statement();  // NULL返回None
                }
                else{
                    paser_error("args shouldn't get * or ** with not var name");
                }
            }
            else{
                next = tmp_next;
            }

            new_token = left;
            parameter *tmp = NULL;
            get_pop_token(status, list, eq);
            printf("eq.type = %d   %d\n", eq.type, status->is_peq);
            if(eq.type == ((status->match_dict || status->is_peq) ? COLON_PASER : EQ_PASER)){  // name_value模式
                if(status->match_list){
                    paser_error("list shouldn't get '='");
                }
                p_status new_status;
                new_status = *status;
                if(!status->match_dict) new_status.not_match_eq = true;  // dict使用了 : 代替 = 
                new_status.not_match_tuple = true;
                get_right_token(&new_status, list, top_exp, value_token);
                if(value_token.type != NON_top_exp){
                    paser_error("Don't get a top_exp");
                    return;
                }
                tmp = append_parameter_name(next.data.statement_value, new_token.data.parameter_list);
                tmp->type = name_value;
                tmp->u.value = value_token.data.statement_value;
            }
            else{
                if(status->match_dict){
                    paser_error("dict should get ':'[1]");
                }
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
        p_status new_status;
        new_status = *status;
        new_status.not_match_eq = true;
        new_status.not_match_tuple = true;
        token tmp_next;
        get_right_token(&new_status, list, top_exp, tmp_next);
        if(tmp_next.type != NON_top_exp){  // 结尾分号 -> 虚解包
            if(!status->is_args){
                back_again(list, tmp_next);
                next.type = NON_top_exp;
                next.data_type = statement_value;
                next.data.statement_value = make_statement();  // NULL返回None
            }
            else{
                paser_error("args shouldn't get * or ** with not var name");
            }
        }
        else{
            next = tmp_next;
        }
        new_token.type = NON_parameter;
        new_token.data_type = parameter_list;
        new_token.data.parameter_list = make_parameter_value(next.data.statement_value);
        new_token.data.parameter_list->u.var = new_token.data.parameter_list->u.value;
        if(left.type == POW_PASER){
            if(status->match_list){
                paser_error("list shouldn't get '**'");
            }
            new_token.data.parameter_list->type = put_kwargs;
        }
        else{
            if(status->match_dict){
                paser_error("dict shouldn't get '*'");
            }
            new_token.data.parameter_list->type = put_args;
        }
        add_node(list, new_token);
        return formal_parameter(status, list);  // 回调自己
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (formal_parameter)back one token to (top_exp)\n");
        back_one_token(list, left);
        p_status new_status;
        new_status = *status;
        new_status.not_match_eq = true;
        new_status.not_match_tuple = true;
        get_base_token(&new_status, list, top_exp, next);
        if(next.type != NON_top_exp){
            back_one_token(list, next);  // 往回[不匹配类型]
            return;
        }

        new_token.type = NON_parameter;
        new_token.data_type = parameter_list;

        parameter *tmp = NULL;
        get_pop_token(status, list, eq);
        if(eq.type == ((status->match_dict || status->is_peq) ? COLON_PASER : EQ_PASER)){  // name_value模式
            if(status->match_list){
                paser_error("list shouldn't get '='");
            }
            p_status new_status;
            new_status = *status;
            new_status.not_match_tuple = true;
            if(!status->match_dict) new_status.not_match_eq = true;
            get_right_token(&new_status, list, top_exp, value_token);
            if(value_token.type != NON_top_exp){
                paser_error("Don't get a top_exp");
                return;
            }
            new_token.data.parameter_list = make_parameter_name(next.data.statement_value);
            new_token.data.parameter_list->u.value = value_token.data.statement_value;
            new_token.data.parameter_list->type = name_value;
        }
        else{
            if(status->match_dict){
                paser_error("dict should get ':'[2]");
            }
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
import “aaa” as AA 和 include 语句
*/
void import_include(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token type_t, str_t, as_t, var_t, new_token;
    type_t = pop_node(list);
    if(type_t.type == IMPORT_PASER || type_t.type == INCLUDE_PASER){
        get_right_token(status,list,top_exp,str_t);
        if(str_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get top_exp");
        }

        statement *tmp =  make_statement();
        if(type_t.type == IMPORT_PASER){  // import才有as top_exp
            get_pop_token(status, list, as_t);
            if(as_t.type != AS_PASER){
                paser_error("Don't get as");
            }

            get_right_token(status,list,top_exp,var_t);
            if(var_t.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get top_exp");
            }
            tmp->type = import_class;
            tmp->code.import_class.file = str_t.data.statement_value;
            tmp->code.import_class.var = var_t.data.statement_value;
        }
        else{
            tmp->type = include_import;
            tmp->code.include_import.file = str_t.data.statement_value;
        }

        new_token.type = NON_import;
        new_token.data_type = statement_value;
        new_token.data.statement_value = tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, type_t);
        return;
    }
}

/*
while_ : WHILE LB top_exp RB block
*/
void do_while_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token do_t, while_t, exp_t, block_t, new_token;
    do_t = pop_node(list);
    if(do_t.type == DO_PASER){
        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *tmp =  make_statement();

        get_pop_token(status, list, while_t);
        if(while_t.type != WHILE_PASER){  // block模式
            back_again(list,while_t);
            tmp->type = code_block;
            tmp->code.code_block.done = block_t.data.statement_value;
        }
        else{
            get_right_token(status,list,top_exp,exp_t);
            if(exp_t.type != NON_top_exp){  // 不是表达式
                paser_error("Don't get 'top_exp'");
            }
            tmp->type = while_cycle;
            tmp->code.while_cycle.condition = exp_t.data.statement_value;
            tmp->code.while_cycle.done = block_t.data.statement_value;
            tmp->code.while_cycle.first_do = true;
        }

        new_token.type = NON_do_while;
        new_token.data_type = statement_value;
        new_token.data.statement_value = tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, do_t);
        return;
    }
}

/*
while_ : WHILE LB top_exp RB block
*/
void while_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token while_t, exp_t, block_t, new_token;
    while_t = pop_node(list);
    if(while_t.type == WHILE_PASER){
        get_right_token(status,list,top_exp,exp_t);
        if(exp_t.type != NON_top_exp){  // 不是表达式
            paser_error("Don't get 'top_exp'");
        }

        get_right_token(status,list,block_,block_t);
        if(block_t.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = exp_t.data.statement_value;
        while_tmp->code.while_cycle.done = block_t.data.statement_value;
        while_tmp->code.while_cycle.first_do = false;

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
try_ : TRY block EXCEPT AS top_exp block
*/
void try_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: while_\n");
    token try_t, try_block, except_t, as_t, var_t, except_block, new_token;
    try_t = pop_node(list);
    if(try_t.type == TRY_PASER){
        get_right_token(status, list, block_, try_block);
        if(try_block.type != NON_block){
            paser_error("Don't get '{'");
        }

        except_again:
        get_pop_token(status,list,except_t);
        if(except_t.type == ENTER_PASER){
            goto except_again;
        }
        else if(except_t.type != EXCEPT_PASER){  // 不是except
            paser_error("Don't get 'except'");
        }

        get_pop_token(status,list,as_t);
        if(as_t.type != AS_PASER){  // 不是except
            paser_error("Don't get 'as'");
        }

        get_right_token(status, list, top_exp, var_t);
        if(var_t.type != NON_top_exp){
            paser_error("Don't get top_exp");
        }

        get_right_token(status,list,block_,except_block);
        if(except_block.type != NON_block){  // 不是表达式
            paser_error("Don't get '{'");
        }

        statement *try_tmp =  make_statement();
        try_tmp->type = try_code;
        try_tmp->code.try_code.try = try_block.data.statement_value;
        try_tmp->code.try_code.except = except_block.data.statement_value;
        try_tmp->code.try_code.var = var_t.data.statement_value;

        new_token.type = NON_try;
        new_token.data_type = statement_value;
        new_token.data.statement_value = try_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;
    }
    else{
        back_one_token(list, try_t);
        return;
    }
}

/*
block_ : LP command_list RB
*/
void block_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: block_\n");
    token lp_t, rp_t, new_token, command_list_t;
    lp_t = pop_node(list);
    again:
    if(lp_t.type == LP_PASER){
        statement *block_tmp =  make_statement();
        statement_base = append_statement_list(block_tmp, statement_base);
        
        p_status new_status = *status;  // 继承file_p等值
        reset_status(new_status);  // 不会影响 *staus
        new_status.dict_to_enter = true;
        get_right_token(&new_status,list,command_list,command_list_t);  // 要把command_list也弹出来

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
void var_ctrl_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: bit_not\n");
    token left, var, right, new_token;
    statement *times = NULL;
    char *var_name = NULL;

    left = pop_node(list);
    if(left.type == GLOBAL_PASER || left.type == DEFAULT_PASER || left.type == NOLOCAL_PASER){
        fprintf(status_log, "[info][grammar]  (ctrl_)reduce right\n");
        statement *base_tmp = NULL;

        again:
        {
            p_status new_status;
            new_status = *status;
            new_status.not_match_tuple = true;  // 不捕捉,
            get_right_token(&new_status, list, top_exp, var);  // 取得base_var
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
                get_right_token(&new_status, list, top_exp, right);  // 回调右边
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
            statement *code_tmp = make_statement();
            if(base_tmp == NULL){
                base_tmp = code_tmp;
            }
            else{
                append_statement(base_tmp, code_tmp);
            }
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
        }

        token comma_t;
        get_pop_token(status,list,comma_t);
        if(comma_t.type == COMMA_PASER){
            goto again;
        }
        else{
            back_again(list, comma_t);
        }

        new_token.data.statement_value = base_tmp;
        add_node(list, new_token);  // 压入节点[弹出3个压入1个]
        return;  // 回调自己
    }
    else{  // 模式1
        back_one_token(list, left);
        return;
    }
}

// raise throw 和 assert
void out_exception(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: out_exception\n");
    token left, exp1, exp2, new_token;

    left = pop_node(list);
    if(left.type == RAISE_PASER || left.type == THROW_PASER || left.type == ASSERT_PASER){
        fprintf(status_log, "[info][grammar]  (out_exception)reduce right\n");

        get_right_token(status, list, top_exp, exp1);  // 取得base_var
        if(exp1.type != NON_top_exp){
            paser_error("Don't get top_exp");
        }

        if(left.type != THROW_PASER){  // 设置times
            get_right_token(status, list, top_exp, exp2);  // 回调右边
            if(exp2.type != NON_top_exp){
                paser_error("Don't get top_exp");
            }
        }
        // 逻辑操作
        new_token.type = NON_exception;
        new_token.data_type = statement_value;
        statement *code_tmp =  make_statement();
        switch (left.type)
        {
            case RAISE_PASER:
                code_tmp->type = raise_e;
                code_tmp->code.raise_e.done = exp1.data.statement_value;
                code_tmp->code.raise_e.info = exp2.data.statement_value;
                break;
            case THROW_PASER:
                code_tmp->type = throw_e;
                code_tmp->code.throw_e.done = exp1.data.statement_value;
                break;
            case ASSERT_PASER:
                code_tmp->type = assert_e;
                code_tmp->code.assert_e.condition = exp1.data.statement_value;
                code_tmp->code.assert_e.info = exp2.data.statement_value;
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

void return_(p_status *status, token_node *list){
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
void ctrl_(p_status *status, token_node *list){
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

void top_exp(p_status *status, token_node *list){
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
void eq_number(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: eq_number\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_eq){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (eq_number)reduce right\n");
        get_pop_token(status, list, symbol);

        if((symbol.type == EQ_PASER && !status->not_match_eq) || symbol.type == AADD_PASER || symbol.type == ASUB_PASER || symbol.type == AMUL_PASER || symbol.type == ADIV_PASER|| 
            symbol.type == AMOD_PASER || symbol.type == AINTDIV_PASER || symbol.type == APOW_PASER){  // 模式2/3
            get_right_token(status, list, hide_list, right);  // 回调右边
            if(right.type != NON_hide_list){
                paser_error("Don't get a hide_list");
            }
            // 逻辑操作
            new_token.type = NON_eq;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            switch (symbol.type)
            {
            case EQ_PASER:
                code_tmp->code.operation.type = ASSIGnMENT_func;
                break;
            case AADD_PASER:
                code_tmp->code.operation.type = AADD_func;
                break;
            case ASUB_PASER:
                code_tmp->code.operation.type = ASUB_func;
                break;
            case AMUL_PASER:
                code_tmp->code.operation.type = AMUL_func;
                break;
            case ADIV_PASER:
                code_tmp->code.operation.type = ADIV_func;
                break;
            case AMOD_PASER:
                code_tmp->code.operation.type = AMOD_func;
                break;
            case AINTDIV_PASER:
                code_tmp->code.operation.type = AINTDIV_func;
                break;
            case APOW_PASER:
                code_tmp->code.operation.type = APOW_func;
                break;
            }
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
        fprintf(status_log, "[info][grammar]  (eq_number)back one token to (hide_list)\n");
        back_one_token(list, left);
        get_base_token(status, list, hide_list, new_token);  // hide_list会处理is_left
        if(new_token.type != NON_hide_list){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        if(status->is_left){  // 必须是在最左边 -> 进入解包赋值
            status->is_left = false;
            
            token comma, p_left, eq_t, p_right, tmp;
            parameter *the_right;
            get_pop_token(status, list,comma);
            if(comma.type == COMMA_PASER){  // a,b = [1,2]的赋值方式
                back_one_token(list, new_token);  // 先把new_token和comma一起回退
                back_again(list, comma);
                
                p_status new_status;
                new_status = *status;
                new_status.is_peq = true;
                get_base_token(&new_status,list,formal_parameter,p_left);
                if(p_left.type != NON_parameter){
                    paser_error("Dont get formal_parameter");
                }
                
                get_pop_token(status, list, eq_t);
                if(eq_t.type != EQ_PASER || status->not_match_eq){  // 变成hide_list
                    back_again(list, eq_t);
                    statement *code_tmp =  make_statement();
                    code_tmp->type = base_tuple;
                    code_tmp->code.base_tuple.value = p_left.data.parameter_list;
                    new_token.data.statement_value = code_tmp;
                    new_token.data_type = statement_value;
                    goto return_back;
                }

                get_pop_token(status,list,tmp);
                if(tmp.type == POW_PASER || tmp.type == MUL_PASER || tmp.type == COLON_PASER){
                    if(tmp.type != COLON_PASER){
                        back_again(list, tmp);
                    }
                    get_right_token(status,list,formal_parameter,p_right);
                    if(p_right.type != NON_parameter){
                        paser_error("Don't get formal_parameter");
                    }
                    the_right = p_right.data.parameter_list;
                }
                else{
                    back_again(list, tmp);
                    get_right_token(status,list,hide_list,p_right);  // 把后面匹配为list
                    if(p_right.type != NON_hide_list){
                        paser_error("Don't get hide_list");
                    }
                    the_right = make_parameter_value(p_right.data.statement_value);
                    the_right->type = put_args;
                    the_right->u.var = the_right->u.value;
                }

                new_token.data_type = statement_value;
                new_token.data.statement_value = make_statement();
                new_token.data.statement_value->type = pack_eq;
                new_token.data.statement_value->code.pack_eq.left = p_left.data.parameter_list;
                new_token.data.statement_value->code.pack_eq.right = the_right;
            }
            else{
                back_again(list, comma);  // 回退comma 使用back_again目的是让new_token在comma之前
            }
        }
        return_back:
        new_token.type = NON_eq;
        add_node(list, new_token);
        return eq_number(status, list);  // 回调自己
    }
}

void hide_list(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: hide_list\n");
    token exp;
    bool old_is_left = status->is_left;
    
    p_status new_status;
    new_status = *status;

    new_status.is_left = false;  // 接下去的运算 is_left均为false
    get_base_token(&new_status,list,lambda_,exp);
    new_status.is_left = old_is_left;
    if(exp.type != NON_lambda){
        back_one_token(list, exp);
        return;
    }
    if(!status->not_match_tuple && !status->is_left && !status->is_for){  // 几个会用到逗号的选项先排除
        token comma;
        get_pop_token(status,list,comma);
        if(comma.type == COMMA_PASER){
            token new_token;
            back_one_token(list, exp);
            back_again(list, comma);
            p_status new_status;
            new_status = *status;
            new_status.not_match_tuple = true;
            get_base_token(&new_status, list, formal_parameter, new_token);
            if(new_token.type != NON_parameter){
                paser_error("Don't get formal_parameter");
            }
            statement *code_tmp =  make_statement();
            code_tmp->type = base_tuple;
            code_tmp->code.base_tuple.value = new_token.data.parameter_list;
            exp.data.statement_value = code_tmp;
            exp.data_type = statement_value;
        }
        else{
            back_again(list, comma);
        }
    }
    exp.type = NON_hide_list;
    add_node(list, exp);  // 压入节点
    return;
}

void lambda_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: lambda_\n");
    token left, lambda_t, block_t, symbol, new_token;
    left = pop_node(list);
    if(left.type != NON_chose){
        back_one_token(list, left);
        get_base_token(status, list, chose_exp_, left);
        if(left.type != NON_chose){
            back_one_token(list, left);
            return;
        }
    }
    get_pop_token(status, list, lambda_t);
    if(lambda_t.type != LAMBDA_PASER){  // 不是lambda表达式
        left.type = NON_lambda;
        back_one_token(list, left);
        back_again(list, lambda_t);
        return;
    }

    get_right_token(status, list, block_, block_t);
    if(block_t.type != NON_block){
        paser_error("Do't get '{");
    }

    statement *lambda_tmp =  make_statement();
    lambda_tmp->type = lambda_func;

    if(left.data.statement_value->type == base_tuple){
        lambda_tmp->code.lambda_func.parameter_list = left.data.statement_value->code.base_tuple.value;
    }
    else{
        lambda_tmp->code.lambda_func.parameter_list = NULL;
    }
    free(left.data.statement_value);
    lambda_tmp->code.lambda_func.done = block_t.data.statement_value;
    new_token.type = NON_lambda;
    new_token.data_type = statement_value;
    new_token.data.statement_value = lambda_tmp;
    add_node(list, new_token);
    return;
}

// xxx if yyy else zzz
void chose_exp_(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: chose_exp\n");
    token left, if_t, else_t, condition, right, new_token;
    
    left = pop_node(list);
    if(left.type != NON_bool_or){
        back_one_token(list, left);
        get_base_token(status, list, bool_or, left);
        if(left.type != NON_bool_or){
            back_one_token(list, left);
            return;
        }
    }
    get_pop_token(status, list, if_t);
    if(if_t.type != IF_PASER){  // 不是if else表达式
        left.type = NON_chose;
        back_one_token(list, left);
        back_again(list, if_t);
        return;
    }

    get_right_token(status, list, bool_or, condition);
    if(condition.type != NON_bool_or){
        paser_error("Do't get condition");
    }

    get_pop_token(status, list, else_t);
    if(else_t.type != ELSE_PASER){  // 不是if else表达式
        paser_error("Do't get else");
        return;
    }

    get_right_token(status, list, bool_or, right);
    if(right.type != NON_bool_or){
        paser_error("Do't get bool or");
    }

    statement *chose_tmp =  make_statement();
    chose_tmp->type = chose_exp;
    chose_tmp->code.chose_exp.condition = condition.data.statement_value;
    chose_tmp->code.chose_exp.true_do = left.data.statement_value;
    chose_tmp->code.chose_exp.false_do = right.data.statement_value;
    
    new_token.type = NON_chose;
    new_token.data_type = statement_value;
    new_token.data.statement_value = chose_tmp;
    add_node(list, new_token);
    return;
}

/*
bool_or : bool_and
        | bool_or AND bool_and
*/
void bool_or(p_status *status, token_node *list){  // 因试分解
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
void bool_and(p_status *status, token_node *list){  // 因试分解
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
void bool_not(p_status *status, token_node *list){
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

void compare(p_status *status, token_node *list){  // 多项式
    fprintf(status_log, "[info][grammar]  mode status: compare\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_compare){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (compare)reduce right\n");
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
            fprintf(status_log, "[info][grammar]  (compare)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (compare)back one token to (bit_notor)\n");
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
void bit_notor(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bit_notor\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_notor){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bit_notor)reduce right\n");
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
        fprintf(status_log, "[info][grammar]  (bit_notor)back one token to (bit_and)\n");
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
void bit_or(p_status *status, token_node *list){  // 因试分解
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
void bit_and(p_status *status, token_node *list){  // 因试分解
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
void bit_move(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: bit_move\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_bit_move){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (bit_move)reduce right\n");
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
        fprintf(status_log, "[info][grammar]  (bit_move)back one token to (polynomial)\n");
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
void polynomial(p_status *status, token_node *list){  // 多项式
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
void factor(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: factor\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_factor){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (factor)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == MUL_PASER || symbol.type == DIV_PASER || symbol.type == INTDIV_PASER || symbol.type == MOD_PASER){  // 模式2/3
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
            else if(symbol.type == DIV_PASER){
                code_tmp->code.operation.type = DIV_func;
            }
            else if(symbol.type == INTDIV_PASER){
                code_tmp->code.operation.type = INTDIV_func;
            }
            else{
                code_tmp->code.operation.type = MOD_func;
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
         | SUB_PASER bit_not
         | ADD_PASER bit_not
*/
void negative(p_status *status, token_node *list){
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
        return;
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (negative)back one token to (bit_not)\n");
        if(left.type != ADD_PASER){  // 取正运算符
            back_one_token(list, left);
            get_base_token(status, list, bit_not, new_token);
        }
        else{  // 需要safe_get_token
            get_right_token(status, list, negative, new_token);
        }
        if(new_token.type != NON_bit_not && new_token.type != NON_negative){
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
void bit_not(p_status *status, token_node *list){
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
void power(p_status *status, token_node *list){
    fprintf(status_log, "[info][grammar]  mode status: power\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_power){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (power)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == POW_PASER || symbol.type == LOG_PASER || symbol.type == SQRT_PASER){  // 模式2/3/4
            get_right_token(status, list, self_exp, right);  // 回调右边
            if(right.type != NON_self_exp){
                paser_error("Don't get a self_exp");
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
        get_base_token(status, list, self_exp, new_token);
        if(new_token.type != NON_self_exp){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_power;
        add_node(list, new_token);
        return power(status, list);  // 回调自己
    }
}

/*
self_exp : hide_list
         | FADD self_exp
         | FSUB self_exp
         | self_exp FADD
         | self_exp FSUB
*/
void self_exp(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: self_exp\n");
    token left, right, new_token;
    parameter *p_list;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == FADD_PASER || left.type == FSUB_PASER){  // ++a和--a
        get_right_token(status, list, self_exp, right);  // 递归自己，比如----a匹配为--new_token，new_token匹配为--a
        if(right.type != NON_self_exp){
            paser_error("Don't get self_exp");
        }
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = (left.type == FADD_PASER) ? FADD_func : FSUB_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = right.data.statement_value;
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;
        new_token.type = NON_self_exp;
        add_node(list, new_token);  // 压入节点
        return;
    }
    else if(left.type == NON_self_exp){
        get_pop_token(status, list, right);
        if(right.type == FADD_PASER || right.type == FSUB_PASER){  // a++和a--
            statement *code_tmp =  make_statement();
            code_tmp->type = operation;
            code_tmp->code.operation.type = (right.type == FADD_PASER) ? LADD_func : LSUB_func;
            code_tmp->code.operation.left_exp = left.data.statement_value;
            code_tmp->code.operation.right_exp = NULL;
            new_token.data.statement_value = code_tmp;
            new_token.data_type = statement_value;
            new_token.type = NON_self_exp;
            add_node(list, new_token);  // 压入节点
            return self_exp(status, list);  // 回调自己，比如a----匹配为self_exp--，再匹配为self_exp
        }
        else{  // 跳出递归
            back_one_token(list, left);
            back_again(list, right);
            return;
        }
    }
    else{  // a--和a++
        back_one_token(list,left);
        get_base_token(status, list, attribute, new_token);
        if(new_token.type != NON_point){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_self_exp;
        add_node(list, new_token);
        return self_exp(status, list);  // 回调自己
    }
}

/*
attribute : bit_or
          | attribute POINT bit_or
*/
void attribute(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: attribute\n");
    token left, right, symbol, new_token;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_point){  // 模式2/3
        fprintf(status_log, "[info][grammar]  (attribute)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == POINT_PASER){  // 模式2/3
            get_right_token(status, list, call_down, right);  // 回调右边
            if(right.type != NON_call_down){
                paser_error("Don't get a call_down");
            }
            // 逻辑操作
            new_token.type = NON_point;
            new_token.data_type = statement_value;

            statement *code_tmp =  make_statement();
            code_tmp->type = point;
            code_tmp->code.point.base_var = left.data.statement_value;
            code_tmp->code.point.child_var = right.data.statement_value;
            
            new_token.data.statement_value = code_tmp;
            add_node(list, new_token);  // 压入节点[弹出3个压入1个]
            return attribute(status, list);  // 回调自己
        }
        else{  // 递归跳出
            // 回退，也就是让下一次pop的时候读取到的是left而不是symbol
            fprintf(status_log, "[info][grammar]  (attribute)out\n");
            back_one_token(list, left);
            back_again(list, symbol);
            return;
        }
    }
    else{  // 模式1
        fprintf(status_log, "[info][grammar]  (attribute)back one token to (call_down)\n");
        back_one_token(list, left);
        get_base_token(status, list, call_down, new_token);
        if(new_token.type != NON_call_down){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_point;
        add_node(list, new_token);
        return attribute(status, list);  // 回调自己
    }
}

/*
call_down : element
          | call_down LI top_exp RI
*/
void call_down(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: call_down\n");
    token left, lb_t, rb_t, new_token, parameter_t;
    parameter *p_list = NULL;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_call_down){
        fprintf(status_log, "[info][grammar]  (call_down)reduce right\n");
        get_pop_token(status, list, lb_t);
        if(lb_t.type == LI_PASER){
            p_status new_status;
            new_status = *status;
            new_status.not_match_tuple = true;
            get_right_token(&new_status, list, top_exp, parameter_t);  // 回调右边
            if(parameter_t.type != NON_top_exp){
                paser_error("Don't get a top_exp");
            }

            statement *code_tmp =  make_statement();
            get_pop_token(status, list, rb_t);
            if(rb_t.type == RI_PASER || rb_t.type == COMMA_PASER){  // a[1,2,3,4]模式
                back_one_token(list, parameter_t);
                back_again(list, rb_t);
                get_base_token(status,list,formal_parameter,parameter_t);
                if(parameter_t.type != NON_parameter){
                    paser_error("Don't get formal_parameter");
                }
                get_pop_token(status, list, rb_t);  // 把rb重新弹出来
                p_list = parameter_t.data.parameter_list;
                code_tmp->type = down;
                code_tmp->code.down.base_var = left.data.statement_value;
                code_tmp->code.down.child_var = p_list;
            }
            else if(rb_t.type == COLON_PASER){  // a[1,2,3,4]模式
                back_one_token(list, parameter_t);
                back_again(list, rb_t);
                p_status new_status;
                new_status = *status;
                new_status.is_slice = true;
                get_base_token(&new_status,list,formal_parameter,parameter_t);
                if(parameter_t.type != NON_parameter){
                    paser_error("Don't get formal_parameter");
                }
                get_pop_token(status, list, rb_t);  // 把rb重新弹出来
                if(rb_t.type != RI_PASER){
                    printf("rb_t.type = %d\n", rb_t.type);
                    goto error;
                }
                p_list = parameter_t.data.parameter_list;
                code_tmp->type = slice;
                code_tmp->code.slice.base_var = left.data.statement_value;
                code_tmp->code.slice.value = p_list;
            }
            else{
                free(code_tmp);
                error: paser_error("Don't get ']', ':' or ','");
            }

            // 逻辑操作
            new_token.type = NON_call_down;
            new_token.data_type = statement_value;
            
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
        fprintf(status_log, "[info][grammar]  (call_down)back one token to (call_back_)\n");
        back_one_token(list, left);
        get_base_token(status, list, call_back_, new_token);
        if(new_token.type != NON_call){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_call_down;
        add_node(list, new_token);
        return call_down(status, list);  // 回调自己
    }
}

/*
call_back_ : bool_or
           | call_back_ LB RB
*/
void call_back_(p_status *status, token_node *list){  // 因试分解
    fprintf(status_log, "[info][grammar]  mode status: call_back_\n");
    token left, symbol, rb_t, new_token, parameter_t;
    parameter *p_list;

    left = pop_node(list);  // 先弹出一个token   检查token的类型：区分是模式1,还是模式2/3
    if(left.type == NON_call){
        fprintf(status_log, "[info][grammar]  (call_back_)reduce right\n");
        get_pop_token(status, list, symbol);

        if(symbol.type == LB_PASER && !status->not_match_call){
            get_pop_token(status, list, rb_t);
            if(rb_t.type != RB_PASER){  // 带参数
                back_again(list, rb_t);
                p_status new_status = *status;  // 继承file_p等值
                reset_status(new_status);  // 不会影响 *staus
                new_status.not_match_tuple = true;
                new_status.is_left = false;
                new_status.is_args = true;
                get_right_token(&new_status,list,formal_parameter,parameter_t);
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
        fprintf(status_log, "[info][grammar]  (call_back_)back one token to (element)\n");
        back_one_token(list, left);
        get_base_token(status, list, element, new_token);
        if(new_token.type != NON_element){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_call;
        add_node(list, new_token);
        return call_back_(status, list);  // 回调自己
    }
}

/*
element : number
        | LB top_exp RB
*/
void element(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: element\n");
    token gett, new_token;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == LB_PASER){  // 模式3
        fprintf(status_log, "[info][grammar]  (element)get LB\n");
        p_status new_status = *status;  // 继承file_p等值
        reset_status(new_status);  // 不会影响 *staus
        new_status.ignore_enter = true;  // 括号内忽略回车
        get_right_token(&new_status, list, top_exp, new_token);
        if(new_token.type == RB_PASER){
            statement *code_tmp =  make_statement();  // 默认
            new_token.data_type = statement_value;
            new_token.data.statement_value = code_tmp;
            goto return_back;
        }
        else if(new_token.type != NON_top_exp){
            paser_error("Don't get 'top_exp'");            
        }
        token rb;
        get_pop_token(status, list ,rb);
        if(rb.type != RB_PASER){  // 匹配失败
            paser_error("Don't get ')'");
        }
        return_back:
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
    else if(gett.type == SVAR_PASER){  // a
        back_one_token(list, gett);
        get_base_token(status, list, svar_token, new_token);
        if(new_token.type != NON_svar){
            back_one_token(list, new_token);  // 往回[不匹配类型]
            return;
        }
        new_token.type = NON_element;
        add_node(list, new_token);
        return;
    }
    else if(gett.type == LP_PASER){  // dict
        back_one_token(list, gett);
        p_status new_status = *status;  // 继承file_p等值
        reset_status(new_status);  // 不会影响 *staus
        new_status.ignore_enter = true;  // 括号内忽略回车
        get_base_token(&new_status,list,dict_,new_token);  // 不需要safe_get_token
        if(new_token.type != NON_dict){
            paser_error("Don't get a dict_");
        }
        new_token.type = NON_element;
        add_node(list, new_token);
        return;
    }
    else if(gett.type == LI_PASER){  // [1]a或[1]列表或[1,2,3,4]列表
        token exp_token, rb, tmp_var;
        p_status new_status;
        new_status = *status;
        new_status.match_list = true;  // 防止top_exp收走逗号
        new_status.not_match_tuple = true;
        new_status.ignore_enter = true;  // 括号内忽略回车
        get_right_token(&new_status, list, top_exp, exp_token);
        if(exp_token.type == RI_PASER){  //可以认定为空list
            back_one_token(list, gett);
            back_again(list, exp_token);
            get_base_token(status,list,list_,new_token);  // 返回空列表
            if(new_token.type != NON_list){
                paser_error("Don't get a list_");
            }
            goto back;
        }
        else if(exp_token.type != NON_top_exp){
            paser_error("Don't get 'top_exp'");            
        }
        
        get_pop_token(status, list ,rb);
        if(rb.type == RI_PASER){  // 匹配失败  TODO:: 检查是不是[1,2,3,4]的列表类型
            get_pop_token(status, list ,tmp_var);
            if(tmp_var.type == VAR_PASER){  // a
                back_one_token(list, tmp_var);
                get_base_token(status, list, var_token, new_token);
                if(new_token.type != NON_base_var){
                    paser_error("Don't get var");
                }
                new_token.data.statement_value->code.base_var.from = exp_token.data.statement_value;
                goto back;
            }
            else if(tmp_var.type == SVAR_PASER){  // a
                back_one_token(list, tmp_var);
                get_base_token(status, list, svar_token, new_token);
                if(new_token.type != NON_svar){
                    paser_error("Don't get svar");
                }
                new_token.data.statement_value->code.base_svar.from = exp_token.data.statement_value;
                goto back;
            }
            else{
                // back again连用的时候要倒过来使用
                /* 原因：
                先back_one_token的时候，token流变成
                <之前的> - <A> - <NULL[seek/index]>
                先back_again的时候，token流变成
                <之前的> - <A> - <B[seek]> - <NULL[index]>
                再back_again的时候，token流变成
                <之前的> - <A> - <C[seek]> - <B> - <NULL[index]>

                其实还有一种解决方法：
                连用三次back_one_token
                然后再用两次back_token手动回退
                */
                back_one_token(list, gett);
                back_again(list, tmp_var);
                back_again(list, rb);
                back_again(list, exp_token);
                get_base_token(&new_status,list,list_,new_token);  // 不需要safe_get_token
                if(new_token.type != NON_list){
                    paser_error("Don't get a list_");
                }
                goto back;
            }
        }
        else{
            back_one_token(list, gett);
            back_again(list, rb);
            back_again(list, exp_token);
            get_base_token(&new_status,list,list_,new_token);  // 不需要safe_get_token
            if(new_token.type != NON_list){
                paser_error("Don't get a list_");
            }
            goto back;
        }

        back:
        new_token.type = NON_element;
        add_node(list, new_token);
        return;
    }
    else{
        fprintf(status_log, "[info][grammar]  (element)back one token to (paser_value)\n");
        back_one_token(list, gett);
        get_base_token(status, list, paser_value, new_token);
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
list_ : LI formal_parameter RI
*/
void list_(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: list_\n");
    token gett, list_core, ri_t, new_token;
    parameter *base = NULL;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == LI_PASER){  // var类型
        p_status new_status;
        new_status = *status;
        new_status.match_list = true;
        new_status.not_match_tuple = true;
        get_right_token(&new_status,list,formal_parameter,list_core);
        if(list_core.type == RI_PASER){  // 空列表
            base = NULL;
            goto make_list;
        }
        else if(list_core.type == NON_parameter){
            base = list_core.data.parameter_list;
        }
        else{
            paser_error("Don't get formal_parameter");
        }

        get_pop_token(status,list,ri_t);
        if(ri_t.type != RI_PASER){
            paser_error("Don't get ']'");
        }

        make_list:
        new_token.type = NON_list;

        statement *code_tmp =  make_statement();
        code_tmp->type = base_list;
        code_tmp->code.base_list.value = base;
        
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (list_)out\n");
        add_node(list, new_token);  // 压入节点
        return;
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (list_)back one token\n");
        back_one_token(list, gett);
        return;
    }
}

/*
dict_ : LP formal_parameter RP
*/
void dict_(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: dict_\n");
    token gett, dict_core, rp_t, new_token;
    parameter *base = NULL;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == LP_PASER){  // var类型
        p_status new_status;
        new_status = *status;
        new_status.match_dict = true;
        new_status.not_match_tuple = true;
        get_right_token(&new_status,list,formal_parameter,dict_core);

        if(dict_core.type == RP_PASER){  // 空列表
            base = NULL;
            goto make_dict;
        }
        else if(dict_core.type == NON_parameter){
            base = dict_core.data.parameter_list;
        }
        else{
            paser_error("Don't get formal_parameter");
        }

        get_pop_token(status,list,rp_t);
        if(rp_t.type != RP_PASER){
            paser_error("Don't get '}'");
        }

        make_dict:
        new_token.type = NON_dict;

        statement *code_tmp =  make_statement();
        code_tmp->type = base_dict;
        code_tmp->code.base_dict.value = base;
        
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (dict_)out\n");
        add_node(list, new_token);  // 压入节点
        return;
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (dict_)back one token\n");
        back_one_token(list, gett);
        return;
    }
}

void svar_token(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: svar_token\n");
    token gett, var_t, new_token;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == SVAR_PASER){  // var类型
        new_token.type = NON_svar;

        get_right_token(status, list, element, var_t);
        if(var_t.type != NON_element){
            paser_error("Don't get element[1]");
        }

        statement *code_tmp =  make_statement();
        code_tmp->type = base_svar;
        code_tmp->code.base_svar.var = var_t.data.statement_value;
        code_tmp->code.base_svar.from = NULL;
        
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;

        fprintf(status_log, "[info][grammar]  (svar_token)out\n");
        add_node(list, new_token);  // 压入节点
        return;
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (svar_token)back one token\n");
        back_one_token(list, gett);
        return;
    }
}

/*
var_token : VAR
*/
void var_token(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: var_token\n");
    token gett, new_token;

    gett = pop_node(list);  // 取得一个token
    if(gett.type == VAR_PASER){  // var类型
        new_token.type = NON_base_var;

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
*/
void paser_value(p_status *status, token_node *list){  // 数字归约
    fprintf(status_log, "[info][grammar]  mode status: paser_value\n");
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
    }
    else if(gett.type == STR_PASER){
        new_token.type = NON_base_value;

        GWARF_value tmp_value;
        tmp_value.type = STRING_value;
        if(gett.data.text == NULL){
            tmp_value.value.string = "";
        }
        else{
            tmp_value.value.string = gett.data.text;
        }
        printf("tmp_value.value.string = %s, %s\n", tmp_value.value.string, gett.data.text);
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("str", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;
        goto not_free;

        // printf("[info][grammar]  (paser_value)get str: %s\n", tmp_value.value.string);
    }
    else if(gett.type == TRUE_PASER || gett.type == FALSE_PASER){
        new_token.type = NON_base_value;

        GWARF_value tmp_value;
        tmp_value.type = BOOL_value;
        if(gett.type == TRUE_PASER){
            tmp_value.value.bool_value = true;
        }
        else{
            tmp_value.value.bool_value = false;
        }

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("bool", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;
    }
    else if(gett.type == NONE_PASER){
        new_token.type = NON_base_value;

        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NULL_value;
        code_tmp->code.base_value.value.value.int_value = 0;
        new_token.data.statement_value = code_tmp;
        new_token.data_type = statement_value;
    }
    else{  // 不是期望值
        fprintf(status_log, "[info][grammar]  (paser_value)back one token\n");
        back_one_token(list, gett);
        return;
    }
    free(gett.data.text);  // 释放字符串
    not_free:
    fprintf(status_log, "[info][grammar]  (paser_value)add one token\n");
    add_node(list, new_token);  // 压入节点
}

void paser_error(char *text){
    fprintf(status_log, "[error][grammar]  paser error : %s\n\n", text);
    printf("[error][grammar]  paser error : %s\n\n", text);
    exit(1);
}
