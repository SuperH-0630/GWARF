%{
    #include<stdio.h>
%}

%union{
    int int_value;
    double double_value;
    char *string_value;
}
%token <double_value> NUMBER
%token <string_value> STRING VAR
%token ADD SUB DIV MUL EQ LESS MORE RB LB RP LP WHILE STOP POW
%type <double_value> base_number second_number first_number
%%
command_list
    : command
    | command_list command
    ;

command
    : top_exp STOP
    ;

top_exp
    : first_number
    {
        printf("%f\n", $1);
    }
    ;

first_number
    : second_number
    | first_number ADD second_number
    {
        $$ = $1 + $3;
    }
    | first_number SUB second_number
    {
        $$ = $1 - $3;
    }
    ;

second_number
    : base_number
    | second_number MUL base_number
    {
        $$ = $1 * $3;
    }
    | second_number DIV base_number
    {
        $$ = $1 / $3;
    }
    ;

base_number
    : NUMBER
    {
        $$ = $1;
    }
    ;

%%
extern int yylex (void);

int yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = stdin;
    yyparse();
    return 0;
}