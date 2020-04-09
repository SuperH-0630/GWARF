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
    void *statement_value;
}
%token <double_value> NUMBER
%token <string_value> STRING VAR
%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE STOP POW EQUAL MOREEQ LESSEQ NOTEQ BREAK
%type <statement_value> base_number base_var_ element second_number first_number top_exp command third_number while_block while_exp break_exp

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
    | break_exp STOP
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

base_var_
    : VAR
    {
        statement *code_tmp =  make_statement();
        code_tmp->code.base_var.var_name = malloc(sizeof($1));
        char *name_tmp = code_tmp->code.base_var.var_name;
        code_tmp->type = base_var;
        strcpy(name_tmp, $1);
        $$ = code_tmp;
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
    {
        printf("start-0\n");
    }
    ;

break_exp
    : BREAK
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = break_cycle;
        $$ = code_tmp;
    }
    ;

%%
int yyerror(char const *str)
{
    fprintf(stderr, "parser error near %s ;\n", yytext, yytext);
    return 0;
}

int parser(char *file)
{
    yyin = fopen(file,"r");
    yyparse();
    return 0;
}