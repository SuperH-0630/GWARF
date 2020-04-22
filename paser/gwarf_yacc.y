%{
    #include<stdio.h>
    #include"lex.yy.c"

    #ifndef _INTERPRETER_H
    #include"../inter/interpreter.h"
    #endif
    
    #define yylex yylex_self
    extern int yylex (void);
    // 此处声明：定义的token：INDENTA不会在yacc中被使用，但将会在lex中被使用
%}

%union{
    int int_value;
    double double_value;
    char *string_value;
    struct statement *statement_value;
    struct if_list *if_list_base;
    struct parameter *parameter_list;
}
%token <double_value> NUMBER INT
%token <string_value> STRING VAR

%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE POW LOG SQRT EQUAL MOREEQ LESSEQ NOTEQ BREAK IF ELSE ELIF BROKEN CONTINUE CONTINUED RESTART RESTARTED REGO REWENT RI LI DEFAULT FOR COMMA GLOBAL NONLOCAL INDENTA STOPN STOPF BLOCK FALSE TRUE
%token NULL_token DEF RETURN CLASS POINT COLON TRY EXCEPT AS RAISE THROW IMPORT INCLUDE IN AND OR NOT MOD INTDIV AADD ASUB AMUL ADIV AMOD AINTDIV FADD FSUB APOW BITAND BITOR BITNOT BITNOTOR BITRIGHT BITLEFT PASS DO

%type <statement_value> base_value base_var_token base_var_ element second_number first_number zero_number top_exp command third_number while_block while_exp break_exp if_block if_exp broken_exp break_token broken_token continue_token continue_exp
%type <statement_value> continued_exp continued_token restart_exp restart_token restarted_exp restarted_token default_token for_exp for_block global_token nonlocal_token block_exp block_block call_number def_block def_exp return_exp return_token
%type <statement_value> eq_number class_block class_exp slice_arguments_token try_block try_exp try_token raise_exp import_exp include_exp bool_number bit_number bit_move do_while_block

%type <parameter_list> formal_parameter arguments slice_arguments

%type <string_value> base_string

%type <if_list_base> elif_exp
%%
command_block
    : command_list
    ;

command_list
    : command
    {
        if($1 != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, $1);
        }
    }
    | command_list command
    {   
        if($2 != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, $2);
        }
    }
    ;

command
    : top_exp stop_token
    {
        $$ = $1;
    }
    | while_block stop_token
    {   
        $$ = $1;
    }
    | if_block stop_token
    {
        $$ = $1;
    }
    | break_exp stop_token
    {
        $$ = $1;
    }
    | broken_exp stop_token
    {
        $$ = $1;
    }
    | continue_exp stop_token
    {
        $$ = $1;
    }
    | continued_exp stop_token
    {
        $$ = $1;
    }
    | restart_exp stop_token
    {
        $$ = $1;
    }
    | restarted_exp stop_token
    {
        $$ = $1;
    }
    | REGO stop_token
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        $$ = code_tmp;
    }
    | REWENT stop_token
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        $$ = code_tmp;
    }
    | default_token stop_token
    {
        $$ = $1;
    }
    | global_token stop_token
    {
        $$ = $1;
    }
    | for_block stop_token
    {
        $$ = $1;
    }
    | nonlocal_token stop_token
    {
        $$ = $1;
    }
    | block_block stop_token
    {
        $$ = $1;
    }
    | def_block stop_token
    {
        $$ = $1;
    }
    | return_exp stop_token
    {
        $$ = $1;
    }
    | class_block stop_token
    {
        $$ = $1;
    }
    | try_block stop_token
    {
        $$ = $1;
    }
    | raise_exp stop_token
    {
        $$ = $1;
    }
    | import_exp stop_token
    {
        $$ = $1;
    }
    | include_exp stop_token
    {
        $$ = $1;
    }
    | do_while_block stop_token
    {
        $$ = $1;
    }
    ;

top_exp
    : eq_number
    {
        $$ = $1;
    }
    ;

eq_number
    : bit_number
    | eq_number EQ bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGMENT_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number AADD bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AADD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number ASUB bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASUB_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number AMUL bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMUL_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number ADIV bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number AMOD bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AMOD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number AINTDIV bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AINTDIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number APOW bit_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = APOW_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | eq_number FADD
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LADD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = NULL;
        $$ = code_tmp;
    }
    | FADD eq_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FADD_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = $2;
        $$ = code_tmp;
    }
    | eq_number FSUB
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LSUB_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = NULL;
        $$ = code_tmp;
    }
    | FSUB eq_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = FSUB_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = $2;
        $$ = code_tmp;
    }
    ;

bit_number
    : bit_move
    | bit_number BITAND bit_move
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITAND_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        puts("NOT FUNC");
        $$ = code_tmp;
    }
    | bit_number BITOR bit_move
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITOR_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | bit_number BITNOTOR bit_move
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOTOR_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        puts("NOT FUNC");
        $$ = code_tmp;
    }
    | BITNOT bit_move
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITNOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = $2;
        $$ = code_tmp;
    }
    ;

bit_move
    : bool_number
    | bit_move BITRIGHT bool_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITRIGHT_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        puts("NOT FUNC");
        $$ = code_tmp;
    }
    | bit_move BITLEFT bool_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = BITLEFT_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

bool_number
    : third_number
    | NOT third_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOT_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = $2;
        puts("NOT FUNC");
        $$ = code_tmp;
    }
    | bool_number AND third_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = AND_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | bool_number OR third_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = OR_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

third_number
    : second_number
    | third_number EQUAL second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = EQUAL_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | third_number MORE second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MORE_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | third_number LESS second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESS_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | third_number MOREEQ second_number
        {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOREEQ_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | third_number LESSEQ second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LESSEQ_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | third_number NOTEQ second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NOTEQ_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

second_number
    : first_number
    | second_number ADD first_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | second_number SUB first_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

first_number
    : zero_number
    | first_number MUL zero_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | first_number DIV zero_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | first_number MOD zero_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MOD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | first_number INTDIV zero_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = INTDIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

zero_number
    : call_number
    | zero_number POW call_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = POW_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | zero_number LOG call_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LOG_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | zero_number SQRT call_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SQRT_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

call_number
    : element
    | element LB RB
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = $1;
        code_tmp->code.call.parameter_list = NULL;
        $$ = code_tmp;
    }
    | element LB arguments RB
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = $1;
        code_tmp->code.call.parameter_list = $3;
        $$ = code_tmp;
    }
    | element LI slice_arguments RI
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = slice;
        code_tmp->code.slice.base_var = $1;
        code_tmp->code.slice.value = $3;
        $$ = code_tmp; 
    }
    ;

element
    : base_value
    | base_var_
    | SUB element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = NEGATIVE_func;
        code_tmp->code.operation.left_exp = NULL;
        code_tmp->code.operation.right_exp = $2;
        $$ = code_tmp;
    }
    | element POINT element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = point;
        code_tmp->code.point.base_var = $1;
        code_tmp->code.point.child_var = $3;
        $$ = code_tmp; 
    }
    | element LI element RI
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = down;
        code_tmp->code.down.base_var = $1;
        code_tmp->code.down.child_var = $3;
        $$ = code_tmp; 
    }
    | LB top_exp RB
    {
        $$ = $2;
    }
    ;

base_value
    : NUMBER
    {
        // 调用double内置类的构造函数
        GWARF_value tmp_value;
        tmp_value.type = NUMBER_value;
        tmp_value.value.double_value = (double)$1;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("double", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        $$ = code_tmp;
    }
    | INT
    {
        GWARF_value tmp_value;
        tmp_value.type = INT_value;
        tmp_value.value.int_value = (int)$1;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("int", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        $$ = code_tmp;
    }
    | base_string
    {
        GWARF_value tmp_value;
        tmp_value.type = STRING_value;
        tmp_value.value.string = $1;  // base_string已经动态生成内存了

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("str", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        $$ = code_tmp;
    }
    | TRUE
    {
        GWARF_value tmp_value;
        tmp_value.type = BOOL_value;
        tmp_value.value.bool_value = true;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("bool", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        $$ = code_tmp;
    }
    | FALSE
    {
        GWARF_value tmp_value;
        tmp_value.type = BOOL_value;
        tmp_value.value.bool_value = false;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("bool", NULL);
        code_tmp->code.call.parameter_list = pack_value_parameter(tmp_value);
        $$ = code_tmp;
    }
    | LI arguments RI
    {
        parameter *tmp;
        tmp = malloc(sizeof(parameter));  // get an address for base var
        tmp->next = NULL;
        statement *statement_tmp = malloc(sizeof(statement));
        statement_tmp->type = base_list;
        statement_tmp->code.base_list.value = $2;
        tmp->u.value = statement_tmp;

        statement *code_tmp =  make_statement();
        code_tmp->type = call;
        code_tmp->code.call.func = pack_call_name("list", NULL);
        code_tmp->code.call.parameter_list = tmp;

        $$ = code_tmp;
    }
    | NULL_token
    {
        // NULL代表空值，是GWARF_value
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NULL_value;
        code_tmp->code.base_value.value.value.int_value = 0;
        $$ = code_tmp;
    }
    ;

base_var_
    : base_var_token
    | LI top_exp RI base_var_token
    {
        $4->code.base_var.from = $2;
        $$ = $4;
    }
    ;

base_var_token
    : VAR
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof($1));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        code_tmp->code.base_var.from = NULL;
        strcpy(name_tmp, $1);
        $$ = code_tmp;
    }
    ;

base_string
    : STRING
    {
        // STRING is char * which the len is 1
        char *tmp = malloc(sizeof($1));
        strcpy(tmp, $1);
        $$ = tmp;
    }
    | base_string STRING
    {
        char *tmp = realloc($1, strlen($1) + strlen($2));  // get address
        strcat(tmp, $2);
        $$ = tmp;
    }
    ;

nonlocal_token
    : NONLOCAL base_var_token
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_nonlocal;
        code_tmp->code.set_nonlocal.name = malloc(sizeof($2->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_nonlocal.name;
        strcpy(name_tmp, $2->code.base_var.var_name);
        free($2->code.base_var.var_name);
        free($2);
        $$ = code_tmp;
    }
    ;

global_token
    : GLOBAL base_var_token
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_global;
        code_tmp->code.set_global.name = malloc(sizeof($2->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_global.name;
        strcpy(name_tmp, $2->code.base_var.var_name);
        free($2->code.base_var.var_name);
        free($2);
        $$ = code_tmp;
    }
    ;

default_token
    : DEFAULT base_var_token element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = set_default;
        code_tmp->code.set_default.times = $3;
        code_tmp->code.set_default.name = malloc(sizeof($2->code.base_var.var_name));
        char *name_tmp = code_tmp->code.set_default.name;
        strcpy(name_tmp, $2->code.base_var.var_name);
        free($2->code.base_var.var_name);
        free($2);
        $$ = code_tmp;
    }
    ;

if_block
    : if_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        $$ = $1;
    }
    | if_block elif_exp block
    {
        append_elif($2, $1->code.if_branch.done);
        $$ = $1;
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
    ;

elif_exp
    : ELIF LB top_exp RB
    {
        statement *done_tmp =  make_statement();
        $$ = make_if($3, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
    | ELSE
    {
        statement *done_tmp =  make_statement();
        $$ = make_if(NULL, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
    }
    ;

if_exp
    : IF LB top_exp RB
    {
        statement *if_tmp =  make_statement(), *done_tmp =  make_statement();
        if_tmp->type = if_branch;
        if_tmp->code.if_branch.done = make_if($3, done_tmp);
        statement_base = append_statement_list(done_tmp, statement_base);  // new statement_base (FILO)
        $$ = if_tmp;
    }
    ;

block_block
    : block_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
    ;

block_exp
    : BLOCK
    {
        statement *block_tmp =  make_statement();
        block_tmp->type = code_block;
        block_tmp->code.code_block.done = make_statement();
        statement_base = append_statement_list(block_tmp->code.code_block.done, statement_base);  // new statement_base (FILO)
        $$ = block_tmp;
    }
    ;

for_block
    : for_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
    ;

for_exp
    : FOR LB COMMA COMMA RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB top_exp COMMA COMMA RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = $3;  // 只有初始化
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB COMMA top_exp COMMA RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = $4;  // 只有条件
        for_tmp->code.for_cycle.after = NULL;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB COMMA COMMA top_exp RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;
        for_tmp->code.for_cycle.condition = NULL;
        for_tmp->code.for_cycle.after = $5;  // 只有后置操作
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB top_exp COMMA COMMA top_exp RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = $3;
        for_tmp->code.for_cycle.condition = NULL;  // 无条件
        for_tmp->code.for_cycle.after = $6;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB top_exp COMMA top_exp COMMA RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = $3;
        for_tmp->code.for_cycle.condition = $5;
        for_tmp->code.for_cycle.after = NULL;  //无后置操作
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB COMMA top_exp COMMA top_exp RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = NULL;  //无初始化
        for_tmp->code.for_cycle.condition = $4;
        for_tmp->code.for_cycle.after = $6;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB top_exp COMMA top_exp COMMA top_exp RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_cycle;
        for_tmp->code.for_cycle.first = $3;
        for_tmp->code.for_cycle.condition = $5;
        for_tmp->code.for_cycle.after = $7;
        for_tmp->code.for_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    | FOR LB element IN top_exp RB
    {
        statement *for_tmp =  make_statement();
        for_tmp->type = for_in_cycle;
        for_tmp->code.for_in_cycle.iter = $5;
        for_tmp->code.for_in_cycle.var = $3;
        for_tmp->code.for_in_cycle.done = make_statement();
        statement_base = append_statement_list(for_tmp->code.for_in_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = for_tmp;
    }
    ;

include_exp
    : INCLUDE top_exp
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = include_import;
        import_tmp->code.include_import.file = $2;
        $$ = import_tmp;
    }
    ;

import_exp
    : IMPORT top_exp AS element
    {
        statement *import_tmp =  make_statement();
        import_tmp->type = import_class;
        import_tmp->code.import_class.file = $2;

        import_tmp->code.import_class.var = $4;

        $$ = import_tmp;
    }
    ;

raise_exp
    : RAISE top_exp top_exp
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = raise_e;
        raise_tmp->code.raise_e.done = $2;
        raise_tmp->code.raise_e.info = $3;
        $$ = raise_tmp;
    }
    | THROW top_exp
    {
        statement *raise_tmp =  make_statement();
        raise_tmp->type = throw_e;
        raise_tmp->code.throw_e.done = $2;
        $$ = raise_tmp;
    }
    ;

try_block
    : try_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        $$ = $1;
    }
    ;

try_exp
    : try_token block EXCEPT AS element
    {
        statement_base = free_statement_list(statement_base);  // out statement_base (FILO)

        $1->code.try_code.var = $5;  

        $1->code.try_code.except = make_statement();
        statement_base = append_statement_list($1->code.try_code.except, statement_base);  // new statement_base (FILO)
        $$ = $1;
    }
    ;

try_token
    : TRY
    {
        statement *try_tmp =  make_statement();
        try_tmp->type = try_code;
        try_tmp->code.try_code.try = make_statement();
        statement_base = append_statement_list(try_tmp->code.try_code.try, statement_base);  // new statement_base (FILO)
        $$ = try_tmp;
    }
    ;

do_while_block
    : DO block while_exp
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        $3->code.while_cycle.first_do = true;
        $$ = $3;
    }
    | DO block stop_token while_exp
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        $4->code.while_cycle.first_do = true;
        $$ = $4;
    }
    ;

while_block
    : while_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
        $1->code.while_cycle.first_do = false;
        $$ = $1;
    }
    ;

while_exp
    : WHILE LB top_exp RB
    {
        statement *while_tmp =  make_statement();
        while_tmp->type = while_cycle;
        while_tmp->code.while_cycle.condition = $3;
        while_tmp->code.while_cycle.done = make_statement();
        statement_base = append_statement_list(while_tmp->code.while_cycle.done, statement_base);  // new statement_base (FILO)
        $$ = while_tmp;
    }
    ;

class_block
    : class_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
    ;

class_exp
    : CLASS  element LB RB
    {   
        //无参数方法
        statement *class_tmp =  make_statement();
        class_tmp->type = set_class;

        class_tmp->code.set_class.var = $2;

        class_tmp->code.set_class.father_list = NULL;
        class_tmp->code.set_class.done = make_statement();
        statement_base = append_statement_list(class_tmp->code.set_class.done, statement_base);  // new statement_base (FILO)

        $$ = class_tmp;
    }
    | CLASS  element LB arguments RB
    {   
        //无参数方法
        statement *class_tmp =  make_statement();
        class_tmp->type = set_class;

        class_tmp->code.set_class.var = $2;

        class_tmp->code.set_class.done = make_statement();
        class_tmp->code.set_class.father_list = $4;  // set father
        statement_base = append_statement_list(class_tmp->code.set_class.done, statement_base);  // new statement_base (FILO)

        $$ = class_tmp;
    }
    ;

def_block
    : def_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
    }
    ;

def_exp
    : DEF  element LB RB
    {   
        //无参数方法
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = $2;
        def_tmp->code.def.parameter_list = NULL;
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        $$ = def_tmp;
    }
    | DEF  element LB formal_parameter RB
    {   
        statement *def_tmp =  make_statement();
        def_tmp->type = def;

        def_tmp->code.def.var = $2;
        def_tmp->code.def.parameter_list = $4;
        def_tmp->code.def.done = make_statement();
        statement_base = append_statement_list(def_tmp->code.def.done, statement_base);  // new statement_base (FILO)

        $$ = def_tmp;
    }
    ;

formal_parameter
    : base_var_
    {
        $$ = make_parameter_name($1->code.base_var.var_name);
        free($1->code.base_var.var_name);
        free($1);
    }
    | formal_parameter COMMA base_var_
    {
        append_parameter_name($3->code.base_var.var_name, $1);
        $$ = $1;
    }

arguments
    : top_exp
    {
        $$ = make_parameter_value($1);
    }
    | arguments COMMA top_exp
    {
        append_parameter_value($3, $1);
        $$ = $1;
    }
    ;

slice_arguments
    : slice_arguments_token
    {
        $$ = make_parameter_value($1);
    }
    | slice_arguments slice_arguments_token
    {
        append_parameter_value($2, $1);
        $$ = $1;
    }
    | slice_arguments top_exp
    {
        append_parameter_value($2, $1);
        $$ = $1;
    }
    ;

slice_arguments_token
    : top_exp COLON
    {
        $$ = $1;
    }
    ;

block
    : LP command_list RP
    | LP block RP
    | LP PASS RP
    ;

return_exp
    : return_token
    | return_token top_exp
    {
        $1->code.return_code.value = $2;
        $$ = $1;
    }
    | return_token top_exp element
    {
        $1->code.return_code.value = $2;
        $1->code.return_code.times = $3;
        $$ = $1;
    }
    ;

return_token
    : RETURN
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = return_code;
        code_tmp->code.return_code.times = NULL;
        code_tmp->code.return_code.value = NULL;
        $$ = code_tmp;
    }
    ;

restarted_exp
    : restarted_token
    | restarted_token element
    {
        $1->code.restarted.times = $2;
        $$ = $1;
    }
    ;

restarted_token
    : RESTARTED
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restarted;
        code_tmp->code.restarted.times = NULL;
        $$ = code_tmp;
    }
    ;

restart_exp
    : restart_token
    | restart_token element
    {
        $1->code.restart.times = $2;
        $$ = $1;
    }
    ;

restart_token
    : RESTART
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = restart;
        code_tmp->code.restart.times = NULL;
        $$ = code_tmp;
    }
    ;

continued_exp
    : continued_token
    | continued_token element
    {
        $1->code.continued.times = $2;
        $$ = $1;
    }
    ;

continued_token
    : CONTINUED
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continued;
        code_tmp->code.continued.times = NULL;
        $$ = code_tmp;
    }
    ;

continue_exp
    : continue_token
    | continue_token element
    {
        $1->code.continue_cycle.times = $2;
        $$ = $1;
    }
    ;

continue_token
    : CONTINUE
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = continue_cycle;
        code_tmp->code.continue_cycle.times = NULL;
        $$ = code_tmp;
    }
    ;

break_exp
    : break_token
    | break_token element
    {
        $1->code.break_cycle.times = $2;
        $$ = $1;
    }
    ;

break_token
    : BREAK
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        code_tmp->code.break_cycle.times = NULL;
        $$ = code_tmp;
    }
    ;

broken_exp
    : broken_token
    | broken_token element
    {
        $1->code.broken.times = $2;
        $$ = $1;
    }

broken_token
    : BROKEN
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = broken;
        code_tmp->code.broken.times = NULL;
        $$ = code_tmp;
    }
    ;

stop_token
    : STOPN
    | STOPF
    | stop_token STOPF
    | stop_token STOPN
    ;

%%
int yyerror(char const *str)
{
    printf("[ERROR] %s in [%s];\ncontinue to run? [Y/n(default)]\n", str, yytext);
    if(getc(stdin) == 'Y'){
        return 0;
    }
    else{
        exit(1);
    }
}

int parser(char *file)
{
    yyin = fopen(file,"r");
    yyparse();
    return 0;
}