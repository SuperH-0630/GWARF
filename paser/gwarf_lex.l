%{
    #include<stdio.h>
    #include"y.tab.h"
%}
%s COMMENT STRING_TEXT
%%
<INITIAL>"while" {return WHILE;}
<INITIAL>"if" {return IF;}
<INITIAL>[\n]*elif {return ELIF;}
<INITIAL>[\n]*else(\(\))? {return ELSE;}
<INITIAL>"break" {return BREAK;}
<INITIAL>"broken" {return BROKEN;}
<INITIAL>"continue" {return CONTINUE;}
<INITIAL>"restart" {return RESTART;}
<INITIAL>"restarted" {return RESTARTED;}
<INITIAL>"continued" {return CONTINUED;}
<INITIAL>"rego" {return REGO;}
<INITIAL>"rewent" {return REWENT;}


<INITIAL>"(" {return LB;}
<INITIAL>")" {return RB;}
<INITIAL>[\n]*\{[\n]* {return LP;}
<INITIAL>"}" {return RP;}

<INITIAL>">=" {return MOREEQ;}
<INITIAL>"<=" {return LESSEQ;}
<INITIAL>"!=" {return NOTEQ;}
<INITIAL>">" {return MORE;}
<INITIAL>"<" {return LESS;}
<INITIAL>"==" {return EQUAL;}
<INITIAL>"=" {return EQ;}
<INITIAL>"+" {return ADD;}
<INITIAL>"-" {return SUB;}
<INITIAL>"*" {return MUL;}
<INITIAL>"/" {return DIV;}
<INITIAL>"^" {return POW;}
<INITIAL>"[" {return LI;}
<INITIAL>"]" {return RI;}
<INITIAL>"default" {return DEFAULT;}

<INITIAL>"#" {BEGIN COMMENT;}
<INITIAL>' {BEGIN STRING_TEXT;}
<INITIAL>\" {BEGIN STRING_TEXT;}
<INITIAL>[1-9][0-9]*(\.[0-9]+)?|0 {
    yylval.double_value = atof(yytext);
    return NUMBER;
    }
<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.string_value = yytext;
    return VAR;
    }

<INITIAL>" " ;
<INITIAL>;?\n {return STOP;}
<INITIAL>";" {return STOP;}
<INITIAL>. {printf("text = [%s];\n", yytext);}

<COMMENT>\n {BEGIN INITIAL;}
<COMMENT>"#" {BEGIN INITIAL;}
<COMMENT>. ;

<STRING_TEXT>' {BEGIN INITIAL;}
<STRING_TEXT>\" {BEGIN INITIAL;}
<STRING_TEXT>\n {
    yylval.string_value = yytext;
    return STRING;
    }
<STRING_TEXT>. {
    yylval.string_value = yytext;
    return STRING;
    }
%%
int yywrap(void) {
    return 1;
}
// int main(){
//     yylex();
//     return 0;
// }