#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "interpreter.h"

#define print_lv(lv) \
for(int i=0;i<lv;i++){ \
fprintf(tree_info, "    "); \
} \
fprintf(tree_info, "%d-", lv);

#define print_t(str, t_statement) \
do{ \
print_lv(lv + 1); \
fprintf(tree_info, str); \
traverse_tree(t_statement, lv + 2); \
}while(0);

#define print_p(str, t_statement) \
do{ \
print_lv(lv + 1); \
fprintf(tree_info, str); \
parameter_tree(t_statement, lv + 2); \
}while(0);

#define print_i(str, t_statement) \
do{ \
print_lv(lv + 1); \
fprintf(tree_info, str); \
if_tree(t_statement, lv + 2); \
}while(0);

void print_statement(statement *the_statement, int lv){  // read the statement list with case to run by func
    print_lv(lv);
    switch (the_statement->type)
    {
        case operation:  // 表达式运算
            fprintf(tree_info, "[operation](type = %d)\n", the_statement->code.operation.type);

            print_t("left\n", the_statement->code.operation.left_exp);
            print_t("right\n", the_statement->code.operation.left_exp);
            break;
        case chose_exp:{
            fprintf(tree_info, "[chose_exp]\n");

            print_t("condition\n", the_statement->code.chose_exp.condition);
            print_t("true_do\n", the_statement->code.chose_exp.true_do);
            print_t("false_do\n", the_statement->code.chose_exp.false_do);
            break;
        }
        case call:
            fprintf(tree_info, "[call]\n");

            print_t("func\n", the_statement->code.call.func);

            print_p("parameter_list\n", the_statement->code.call.parameter_list);
            break;
        case while_cycle:
            fprintf(tree_info, "[while_cycle]%s\n",  (the_statement->code.while_cycle.first_do ? "(do ... while)" : "(while ... )"));

            print_t("condition\n", the_statement->code.while_cycle.condition);
            print_t("done\n", the_statement->code.while_cycle.done);
            print_t("else_do\n", the_statement->code.while_cycle.else_do);
            break;
        case for_cycle:
            fprintf(tree_info, "[for_cycle]\n");

            print_t("condition\n", the_statement->code.for_cycle.condition);
            print_t("first\n", the_statement->code.for_cycle.first);
            print_t("after\n", the_statement->code.for_cycle.after);
            print_t("done\n", the_statement->code.for_cycle.done);
            print_t("else_do\n", the_statement->code.for_cycle.else_do);
            break;
        case for_in_cycle:
            fprintf(tree_info, "[for in ]\n");

            print_t("var\n", the_statement->code.for_in_cycle.var);
            print_t("iter\n", the_statement->code.for_in_cycle.iter);
            print_t("done\n", the_statement->code.for_in_cycle.done);
            print_t("else_do\n", the_statement->code.for_in_cycle.else_do);
            break;
        case if_branch:
            fprintf(tree_info, "[if branch]\n");
            
            print_i("done", the_statement->code.if_branch.done)
            break;
        case pack_eq:
            fprintf(tree_info, "[pack_eq]\n");

            print_p("left\n", the_statement->code.pack_eq.left);
            print_p("right\n", the_statement->code.pack_eq.right);
            break;
        case base_value:
            fprintf(tree_info, "[base_value](type = %d)(token = %d)(value = ", the_statement->code.base_value.value.type, the_statement->code.base_value.value.lock_token);
            switch (the_statement->code.base_value.value.type)
            {
            case NULL_value:
                fprintf(tree_info, "<None>[None show]");
                break;
            case INT_value:
                fprintf(tree_info, "%d[int not show]", the_statement->code.base_value.value.value.int_value);
                break;
            case NUMBER_value:
                fprintf(tree_info, "%f[double not show]", the_statement->code.base_value.value.value.double_value);
                break;
            case STRING_value:
                fprintf(tree_info, "'%s'[str not show]", the_statement->code.base_value.value.value.string);
                break;
            case FUNC_value:
                fprintf(tree_info, "%x[func show]", the_statement->code.base_value.value.value.func_value);
                break;
            case CLASS_value:
                fprintf(tree_info, "%x[class show]", the_statement->code.base_value.value.value.class_value);
                break;
            case OBJECT_value:
                fprintf(tree_info, "%x[object show]", the_statement->code.base_value.value.value.object_value);
                break;
            case LIST_value:
                fprintf(tree_info, "%x[list not show]", the_statement->code.base_value.value.value.list_value);
                break;
            case DICT_value:
                fprintf(tree_info, "%x[list not show]", the_statement->code.base_value.value.value.dict_value);
                break;
            default:
                fprintf(tree_info, "WRONG!!!");
                break;
            }
            fprintf(tree_info, ")\n");
            break;
        case base_tuple:{
            fprintf(tree_info, "[base_tuple]\n");

            print_p("value\n", the_statement->code.base_tuple.value);
            break;
        }
        case base_list:{
            fprintf(tree_info, "[base_list]\n");

            print_p("value\n", the_statement->code.base_list.value);
            break;
        }
        case base_dict:{
            fprintf(tree_info, "[base_dict]\n");

            print_p("value\n", the_statement->code.base_dict.value);
            break;
        }
        case slice:{
            fprintf(tree_info, "[slice]\n");

            print_t("base_var\n", the_statement->code.slice.base_var);
            print_p("value\n", the_statement->code.slice.value);
            break;
        }
        case base_var:{  // 访问变量
            fprintf(tree_info, "[base_var](name = %s)(token = %d)\n", the_statement->code.base_var.var_name, the_statement->code.base_var.lock_token);

            print_t("from\n", the_statement->code.base_var.from);
            break;
        }
        case base_svar:{
            fprintf(tree_info, "[base_svar](token = %d)\n", the_statement->code.base_svar.lock_token);

            print_t("var\n", the_statement->code.base_svar.var);
            print_t("from\n", the_statement->code.base_svar.from);
            break;
        }
        case point:{
            fprintf(tree_info, "[point]\n");

            print_t("base\n", the_statement->code.point.base_var);
            print_t("child\n", the_statement->code.point.child_var);
            break;
        }
        case down:{
            fprintf(tree_info, "[down]\n");

            print_t("base_var\n", the_statement->code.down.base_var);
            print_p("child_var\n", the_statement->code.down.child_var);
            break;
        }
        case def:{
            fprintf(tree_info, "[def](type = %d, is_inline = %d)\n", the_statement->code.def.type, the_statement->code.def.is_inline);

            print_t("var(name)\n", the_statement->code.def.var);
            print_p("parameter_list\n", the_statement->code.def.parameter_list);
            print_t("setup\n", the_statement->code.def.setup);
            print_t("done\n", the_statement->code.def.done);
            break;
        }
        case lambda_func:{
            fprintf(tree_info, "[lambda_func]\n");

            print_p("parameter_list\n", the_statement->code.lambda_func.parameter_list);
            print_t("done\n", the_statement->code.lambda_func.done);
            break;
        }
        case set_class:{
            fprintf(tree_info, "[set_class]\n");

            print_t("var(name)\n", the_statement->code.set_class.var);
            print_p("father_list\n", the_statement->code.set_class.father_list);
            print_t("done\n", the_statement->code.set_class.done);
            break;
        }
        case break_cycle:
            fprintf(tree_info, "[break_cycle]\n");
            print_t("times\n", the_statement->code.break_cycle.times);
            break;
        case broken:
            fprintf(tree_info, "[broken]\n");
            print_t("times\n", the_statement->code.broken.times);
            break;
        case continue_cycle:
            fprintf(tree_info, "[continue_cycle]\n");
            print_t("times\n", the_statement->code.continue_cycle.times);
            break;
        case continued:
            fprintf(tree_info, "[continued]\n");
            print_t("times\n", the_statement->code.continued.times);
            break;
        case restart:
            fprintf(tree_info, "[restart]\n");
            print_t("times\n", the_statement->code.restart.times);
            break;
        case restarted:
            fprintf(tree_info, "[restarted]\n");
            print_t("times\n", the_statement->code.restarted.times);
            break;
        case return_code:
            fprintf(tree_info, "[return_code]\n");
            print_t("value\n", the_statement->code.return_code.value);
            print_t("times\n", the_statement->code.return_code.times);
            break;
        case rewent:
            fprintf(tree_info, "[rewent]\n");
            break;
        case rego:
            fprintf(tree_info, "[rego]\n");
            break;
        case set_default:{
            fprintf(tree_info, "[set_default] [var(name) = %s]\n", the_statement->code.set_default.name);
            print_t("times\n", the_statement->code.set_default.times);
            break;
        }
        case set_global:{
            fprintf(tree_info, "[set_global] [var(name) = %s]\n", the_statement->code.set_global.name);
            break;
        }
        case set_nonlocal:{
            fprintf(tree_info, "[set_nonlocal] [var(name) = %s]\n", the_statement->code.set_nonlocal.name);
            break;
        }
        case code_block:
            fprintf(tree_info, "[code_block]\n");
            print_t("done\n", the_statement->code.code_block.done);
            break;
        case try_code:
            fprintf(tree_info, "[try_code]\n");

            print_t("try\n", the_statement->code.try_code.try);
            print_t("except\n", the_statement->code.try_code.except);
            print_t("var\n", the_statement->code.try_code.var);
            print_t("else_do\n", the_statement->code.try_code.else_do);
            print_t("finally_do\n", the_statement->code.try_code.finally_do);
            break;
        case raise_e:
            fprintf(tree_info, "[raise_e]\n");

            print_t("info\n", the_statement->code.raise_e.info);
            print_t("done\n", the_statement->code.raise_e.done);
            break;
        case throw_e:
            fprintf(tree_info, "[throw_e]\n");

            print_t("done\n", the_statement->code.throw_e.done);
            break;
        case import_class:  // import xxx as xxx 语句
            fprintf(tree_info, "[import_class]\n");

            print_t("file\n", the_statement->code.import_class.file);
            print_t("var\n", the_statement->code.import_class.var);
            break;
        case include_import:  // include xxx
            fprintf(tree_info, "[include_import]\n");

            print_t("file\n", the_statement->code.include_import.file);
            break;
        case assert_e:
            fprintf(tree_info, "[assert_e]\n");

            print_t("condition\n", the_statement->code.assert_e.condition);
            print_t("info\n", the_statement->code.assert_e.info);
            break;
        default:
            fprintf(tree_info, "[start]\n");
            break;
    }
    return_result: return;
}

void traverse_tree(statement *the_statement, int lv){
    statement *tmp = the_statement;
    if(the_statement == NULL){
        print_lv(lv);
        fprintf(tree_info, "NULL\n");
        goto return_back;
    }
    else{
    }
    while(1){
        if(tmp == NULL){
            break;
        }
        print_statement(tmp, lv);
        tmp = tmp->next;
    }
    return_back: return;
}

void parameter_tree(parameter *the_parameter, int lv){
    parameter *tmp = the_parameter;
    if(the_parameter == NULL){
        print_lv(lv);
        fprintf(tree_info, "NULL\n");
        goto return_back;
    }
    while(1){
        if(tmp == NULL){
            break;
        }
        print_lv(lv);
        fprintf(tree_info, "[parameter]\n");
        switch (tmp->type)
        {
        case only_value:
            print_t("value\n", tmp->u.value);
            break;
        case put_args:
            fprintf(tree_info, "[put_args](parameter)\n");
            print_t("value\n", tmp->u.value);
            break;
        case put_kwargs:
            fprintf(tree_info, "[put_kwargs](parameter)\n");
            print_t("value\n", tmp->u.value);
            break;
        case name_value:
            fprintf(tree_info, "[name_value](parameter)\n");
            print_t("value\n", tmp->u.value);
            print_t("var\n", tmp->u.var);
            break;
        default:
            break;
        }
        tmp = tmp->next;
    }
    return_back: return;
}

void if_tree(if_list *the_branch, int lv){
    if_list *tmp = the_branch;
    if(the_branch == NULL){
        print_lv(lv);
        fprintf(tree_info, "NULL\n");
        goto return_back;
    }
    while(1){
        if(tmp == NULL){
            break;
        }
        print_lv(lv);
        fprintf(tree_info, "[if node]\n");
        print_t("condition\n", tmp->condition);
        print_t("done\n", tmp->done);
        tmp = tmp->next;
    }
    return_back: return;
}