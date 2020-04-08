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
%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE STOP POW
%type <statement_value> base_number second_number first_number top_exp
%%
command_list
    : command
    | command_list command
    ;

command
    : STOP
    | top_exp STOP
    {
        append_statement(global_inter->global_code, $1);
    }
    ;

top_exp
    : first_number
    {
        $$ = $1;
    }
    ;

first_number
    : second_number
    | first_number ADD second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = ADD_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | first_number SUB second_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = SUB_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

second_number
    : base_number
    | second_number MUL base_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = MUL_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    | second_number DIV base_number
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = operation;
        code_tmp->code.operation.type = DIV_func;
        code_tmp->code.operation.left_exp = $1;
        code_tmp->code.operation.right_exp = $3;
        $$ = code_tmp;
    }
    ;

base_number
    : NUMBER
    {
        statement *code_tmp =  make_statement();
        code_tmp->type = base_value;
        code_tmp->code.base_value.value.type = NUMBER;
        code_tmp->code.base_value.value.value.double_value = $1;
        $$ = code_tmp;
    }
    ;

%%
int yyerror(char const *str)
{
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int parser(void)
{
    yyin = fopen("/home/songzihuan/test.gwf","r");
    yyparse();
    return 0;
}