%{
    #include<stdio.h>
    #include"y.tab.h"
    int indentation = 0;
    int tmp_indentation = 0;
    int last_token;
    int different = 0;
    int flat = 0;
    int is_last = 0;  // 是否\n
    int is_stop = 0;  // 针对}需要返回一个}的同时返回一个STOP
%}
%s COMMENT STRING_TEXT INDENTATION
%%
<INITIAL>^"    " {
    return INDENTA;
    }
<INITIAL>[\n]+"    "[\n]* {
    return INDENTA;
    }
<INITIAL>"    " {
    if(tmp_indentation > 0){
        return INDENTA;
    }
}
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
<INITIAL>"for" {return FOR;}
<INITIAL>"," {return COMMA;}
<INITIAL>":" {return COLON;}
<INITIAL>"default" {return DEFAULT;}
<INITIAL>"global" {return GLOBAL;}
<INITIAL>"nonlocal" {return NONLOCAL;}
<INITIAL>"block" {return BLOCK;}
<INITIAL>"in" {return IN;}

<INITIAL>"import" {return IMPORT;}
<INITIAL>"include" {return INCLUDE;}

<INITIAL>"(" {return LB;}
<INITIAL>")" {return RB;}
<INITIAL>[\n]*\{[\n]* {return LP;}
<INITIAL>"}" {return RP;}

<INITIAL>"**=" {return APOW;}
<INITIAL>"++" {return FADD;}
<INITIAL>"--" {return FSUB;}
<INITIAL>"+=" {return AADD;}
<INITIAL>"-=" {return ASUB;}
<INITIAL>"//=" {return AINTDIV;}
<INITIAL>"/=" {return ADIV;}
<INITIAL>"*=" {return AMUL;}
<INITIAL>"%=" {return AMOD;}
<INITIAL>">=" {return MOREEQ;}
<INITIAL>"<=" {return LESSEQ;}
<INITIAL>"!=" {return NOTEQ;}
<INITIAL>">" {return MORE;}
<INITIAL>"<" {return LESS;}
<INITIAL>"==" {return EQUAL;}
<INITIAL>"=" {return EQ;}
<INITIAL>"**" {return POW;}
<INITIAL>"log" {return LOG;}
<INITIAL>"sqrt" {return SQRT;}
<INITIAL>"+" {return ADD;}
<INITIAL>"-" {return SUB;}
<INITIAL>"*" {return MUL;}
<INITIAL>"%" {return MOD;}
<INITIAL>"//" {return INTDIV;}
<INITIAL>"/" {return DIV;}
<INITIAL>"[" {return LI;}
<INITIAL>"]" {return RI;}

<INITIAL>"#" {BEGIN COMMENT;}
<INITIAL>' {BEGIN STRING_TEXT;}
<INITIAL>\" {BEGIN STRING_TEXT;}

<INITIAL>"try" {return TRY;}
<INITIAL>[\n]*except {return EXCEPT;}
<INITIAL>"as" {return AS;}
<INITIAL>"raise" {return RAISE;}
<INITIAL>"throw" {return THROW;}
<INITIAL>"True" {return TRUE;}
<INITIAL>"False" {return FALSE;}
<INITIAL>"None" {return NULL_token;}
<INITIAL>"def" {return DEF;}
<INITIAL>"return" {return RETURN;}
<INITIAL>"class" {return CLASS;}
<INITIAL>"&&" {return AND;}
<INITIAL>"||" {return OR;}
<INITIAL>"!" {return NOT;}

<INITIAL>"&" {return BITAND;}
<INITIAL>"|" {return BITOR;}
<INITIAL>"^" {return BITNOTOR;}
<INITIAL>"~" {return BITNOT;}
<INITIAL>"<<" {return BITLEFT;}
<INITIAL>">>" {return BITRIGHT;}

<INITIAL>"." {return POINT;}

<INITIAL>[1-9][0-9]*\.[0-9]+ {
    yylval.double_value = atof(yytext);
    return NUMBER;
    }
<INITIAL>[1-9][0-9]*|0 {
    yylval.double_value = atof(yytext);
    return INT;
    }
<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.string_value = yytext;
    return VAR;
    }
<INITIAL>\n {return STOPN;}
<INITIAL>";" {return STOPF;}
<INITIAL>" " ;
<INITIAL>. {printf("other text = [%s];\n", yytext);}

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
int yylex_self(void){
    again: 
    if(flat == 0){
        int result = yylex();  // 正常执行yylex的模式
        printf("return result = %d\n", result);
        if((result == 0) && (indentation != 0)){  // 上一个是\n，这一行已经没有缩进了
            printf("FFFF\n");
            flat = 2;  // 进入返回模式
            last_token = STOPN;  // 记录堆积的token[再次之后不再执行yylex]
            different = indentation;  // tmp_indentation = 0了已经
            is_last = 0;
            is_stop = 0; // 清零
            goto again;  // 回到顶部
        }
        else if(result == INDENTA){  // 返回缩进
            flat = 1;  // 进入缩进模式
            tmp_indentation += 1;  // 缩进+1
            is_last = 0;
            goto again;  // 回到顶部
        }
        else if((is_last) && (indentation != 0)){  // 上一个是\n，这一行已经没有缩进了
            flat = 2;  // 进入返回模式
            last_token = result;  // 记录堆积的token[再次之后不再执行yylex]
            different = indentation;  // tmp_indentation = 0了已经
            is_last = 0;
            is_stop = 0; // 清零
            goto again;  // 回到顶部
        }

        if(result == STOPN){
            is_last = 1; // 已经是\n
        }
        return result;  // 返回值
    }
    else if(flat == 1){
        int result = yylex();
        if(result != INDENTA){  // 返回缩进
            flat = 2;  // 进入返回模式
            last_token = result;  // 记录堆积的token[再次之后不再执行yylex]
            different = indentation - tmp_indentation;  // 如果>1，则缩进少了，返回}，如果小于1则缩进多了返回{
            is_stop = 0; // 清零
            goto again;  // 回到顶部
        }
        else{
            tmp_indentation += 1;  // 缩进+1
            goto again;  // 回到顶部
        }
    }
    else if(flat == 2){
        if(different < 0){
            different += 1;
            puts("return {");
            return LP;
        }
        else if(different > 0){
            if(is_stop){
                different -= 1;  // 只有STOP才-1 保证了最后一个必须输出STOP
                is_stop = 0;  // 下一个不输出STOP了
                puts("return STOPN");
                return STOPN;
            }
            else{
                is_stop = 1;
                puts("return }");
                return RP;
            }
        }
        else{  // RP或者LP返回完毕
            indentation = tmp_indentation;  // 使用当前tmp
            tmp_indentation = 0;  // 清0
            flat = 0;  // 回到正常模式
            printf("return result = %d\n", last_token);
            return last_token;
        }
    }
}