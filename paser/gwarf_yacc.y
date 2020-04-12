%{
    #include<stdio.h>
    #include"lex.yy.c"
    #include"../gwarf_interpreter/interprete.h"
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
}
%token <double_value> NUMBER INT
%token <string_value> STRING VAR
%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE POW LOG SQRT EQUAL MOREEQ LESSEQ NOTEQ BREAK IF ELSE ELIF BROKEN CONTINUE CONTINUED RESTART RESTARTED REGO REWENT RI LI DEFAULT FOR COMMA GLOBAL NONLOCAL INDENTA STOPN STOPF BLOCK
%type <statement_value> base_value base_var_token base_var_ element second_number first_number zero_number top_exp command third_number while_block while_exp break_exp if_block if_exp broken_exp break_token broken_token continue_token continue_exp
%type <statement_value> continued_exp continued_token restart_exp restart_token restarted_exp restarted_token default_token for_exp for_block global_token nonlocal_token block_exp block_block
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
    | while_block
    {   
        if($1 != NULL){
            statement *tmp = find_statement_list(0, statement_base);
            append_statement(tmp, $1);
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
    ;

top_exp
    : third_number
    {
        $$ = $1;
    }
    | base_var_ EQ top_exp
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ASSIGMENT_func;
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
    ;

zero_number
    : element
    | zero_number POW element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = POW_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | zero_number LOG element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = LOG_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | zero_number SQRT element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SQRT_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
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
    | LB top_exp RB
    {
        $$ = $2;
    }
    ;

base_value
    : NUMBER
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NUMBER_value;
        code_tmp->code.base_value.value.value.double_value = (double)$1;
        $$ = code_tmp;
    }
    | INT
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = INT_value;
        code_tmp->code.base_value.value.value.int_value = (int)$1;
        $$ = code_tmp;
    }
    | base_string
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = STRING_value;
        code_tmp->code.base_value.value.value.string = $1;
        $$ = code_tmp;
    }
    ;

base_var_
    : base_var_token
    | LI element RI base_var_token
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
    ;

while_block
    : while_exp block
    {
        statement_base = free_statement_list(statement_base);  // new statement_base (FILO)
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

block
    : LP command_list RP
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
    fprintf(stderr, "parser error near [%s] ;\n", yytext, yytext);
    return 0;
}

int parser(char *file)
{
    yyin = fopen(file,"r");
    yyparse();
    return 0;
}