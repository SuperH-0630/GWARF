%{
    #include<stdio.h>
    #include"lex.yy.c"
    #include"../gwarf_interpreter/interprete.h"
    extern int yylex (void);
%}

%union{
    int int_value;
    double double_value;
    char *string_value;
    struct statement *statement_value;
    struct if_list *if_list_base;
}
%token <double_value> NUMBER
%token <string_value> STRING VAR
%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE STOP POW EQUAL MOREEQ LESSEQ NOTEQ BREAK IF ELSE ELIF BROKEN CONTINUE CONTINUED RESTART RESTARTED REGO REWENT RI LI DEFAULT
%type <statement_value> base_number base_var_token base_var_ element second_number first_number top_exp command third_number while_block while_exp break_exp if_block if_exp broken_exp break_token broken_token continue_token continue_exp
%type <statement_value> continued_exp continued_token restart_exp restart_token restarted_exp restarted_token default_token
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
    : STOP
    {
        $$ = NULL;
    }
    | top_exp STOP
    {
        $$ = $1;
    }
    | while_block STOP
    {   
        $$ = $1;
    }
    | if_block STOP
    {
        $$ = $1;
    }
    | break_exp STOP
    {
        $$ = $1;
    }
    | broken_exp STOP
    {
        $$ = $1;
    }
    | continue_exp STOP
    {
        $$ = $1;
    }
    | continued_exp STOP
    {
        $$ = $1;
    }
    | restart_exp STOP
    {
        $$ = $1;
    }
    | restarted_exp STOP
    {
        $$ = $1;
    }
    | REGO STOP
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rego;
        $$ = code_tmp;
    }
    | REWENT STOP
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = rewent;
        $$ = code_tmp;
    }
    | default_token STOP
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
    : element
    | first_number MUL element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | first_number DIV element
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

element
    : base_number
    | base_var_
    | LB top_exp RB
    {
        $$ = $2;
    }
    ;

base_number
    : NUMBER
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NUMBER_value;
        code_tmp->code.base_value.value.value.double_value = $1;
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