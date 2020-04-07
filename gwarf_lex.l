%{
    #include<stdio.h>
    #include"y.tab.h"
%}
%s COMMENT STRING_TEXT
%%
<INITIAL>"while" {return WHILE;}

<INITIAL>"(" {return LB;}
<INITIAL>")" {return RB;}
<INITIAL>"{" {return LP;}
<INITIAL>"}" {return RP;}

<INITIAL>">" {return MORE;}
<INITIAL>"<" {return LESS;}
<INITIAL>"=" {return EQ;}
<INITIAL>"+" {return ADD;}
<INITIAL>"-" {return SUB;}
<INITIAL>"*" {return MUL;}
<INITIAL>\\ {return DIV;}
<INITIAL>"^" {return POW;}

<INITIAL>"#" {BEGIN COMMENT;}
<INITIAL>' {BEGIN STRING_TEXT;}
<INITIAL>\" {BEGIN STRING_TEXT;}
<INITIAL>[1-9][0-9]*(\.[0-9]+)?|0 {
    yylval.double_value = atoi(yytext);
    return NUMBER;
    }
<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.string_value = yytext;
    return VAR;
    }
<INITIAL>\n {return STOP;}

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