// #include "mem.h"
#include "lex.h"
#include "token.h"

void match_int(char, word_paser *);
void match_double(char, word_paser *);
void match_text(char, word_paser *, char *);
void match_text_s(char, word_paser *, char *);
void match_var(char p, word_paser *paser);
void match_str(char p, word_paser *paser);
void match_comment(char p, word_paser *paser);
void match_enter(char p, word_paser *paser);

int is_in(int, p_status *status);
extern void paser_error(p_status *status, char *);

token get_token(p_status *status){
    token return_token;
    int s, *paser_status = &s;
    int index = 0;  // 记录index和是否遇到了EOF
    do{
        set_start(status->global_paser);
        *paser_status = paser(&index, status);  // 解析
    }while(is_in(index, status));

    if(!(*paser_status)){  // 匹配到eof
        return_token.type = EOF_token;
        return_token.data_type = empty;
        fprintf(debug, "[debug]token type = <EOF>\n\n");
        fprintf(status_log, "[info]token type = <EOF>\n");
    }
    else if(index == -2){
        paser_error(status, "lexical token error");
    }
    else{
        return_token.type = index;
        return_token.data_type = text;
        return_token.data.text = malloc(strlen(status->global_paser[index]->text));
        strcpy(return_token.data.text, status->global_paser[index]->text);
        fprintf(debug, "[debug]token type = %d\n\n", index);
        fprintf(status_log, "[info]token type = %d\n", index);
    }
    return return_token;
}

int is_in(int element, p_status *status){  // 检查某个值是否在数组中
    if(status->ignore_enter && element == ENTER_PASER){  // 忽略ENTER
        return 1;
    }
    int list[] = {SPACE_PASER,IGNORE_ENTER,COMMENT_PASER};
    int len = 3;
    for(int i=0;i<len;i++){
        if(list[i] == element){
            return 1;
        }
    }
    return 0;
}

int paser(int *index, p_status *status){
    word_paser **global_paser = status->global_paser;
    char p;
    int is_eof = 0;  // 考虑用status取代is_eof
    int count = 0;
    while(1){
        p = read_p(status);
        if(p == EOF){  // 遇到EOF[先不break]
            fprintf(debug, "[info][lexical]  p = <EOF>\n\n");
            is_eof = 1;
            if(count == 0){
                return 0;
            }
        }
        else{
            if(p == '\n'){
               fprintf(debug, "[info][lexical]  p = <Enter>\n\n"); 
            }
            else{
                fprintf(debug, "[info][lexical]  p = '"); 
                fputc(p, debug); 
                fputs("'\n\n", debug); 
            }
        }
        count += 1;
        // 执行解析器
        match_int(p, global_paser[INT_PASER]);
        match_double(p, global_paser[DOUBLE_PASER]);
        match_var(p, global_paser[VAR_PASER]);

        // 匹配注释
        match_comment(p, global_paser[COMMENT_PASER]);
        match_enter(p, global_paser[IGNORE_ENTER]);  // 忽略空格，匹配\ + <enter>，使用is_in忽略

        // 常规文本解析器
        match_text(p, global_paser[ENTER_PASER], "\n");
        match_text(p, global_paser[SPACE_PASER], " ");
        match_text(p, global_paser[ADD_PASER], "+");
        match_text(p, global_paser[SUB_PASER], "-");
        match_text(p, global_paser[MUL_PASER], "*");
        match_text(p, global_paser[DIV_PASER], "/");
        match_text_s(p, global_paser[INTDIV_PASER], "//");
        match_text_s(p, global_paser[AADD_PASER], "+=");
        match_text_s(p, global_paser[ASUB_PASER], "-=");
        match_text_s(p, global_paser[AMUL_PASER], "*=");
        match_text_s(p, global_paser[ADIV_PASER], "/=");
        match_text_s(p, global_paser[AINTDIV_PASER], "//=");
        match_text_s(p, global_paser[AMOD_PASER], "%=");
        match_text_s(p, global_paser[APOW_PASER], "**=");
        match_text_s(p, global_paser[ABITAND_PASER], "&=");
        match_text_s(p, global_paser[ABITOR_PASER], "|=");
        match_text_s(p, global_paser[ABITNOTOR_PASER], "^=");
        match_text_s(p, global_paser[ALEFT_PASER], "<<=");
        match_text_s(p, global_paser[ARIGHT_PASER], ">>=");
        match_text_s(p, global_paser[FADD_PASER], "++");
        match_text_s(p, global_paser[FSUB_PASER], "--");
        match_text_s(p, global_paser[ISLEFT_PASER], "<:=");
        match_text_s(p, global_paser[ISRIGHT_PASER], "=:>");
        match_text_s(p, global_paser[ILEFT_PASER], "<==");
        match_text_s(p, global_paser[IRIGHT_PASER], "==>");
        match_text_s(p, global_paser[BOOLNOTOR_PASER], "!==");
        match_text_s(p, global_paser[BOOLIS_PASER], "<=>");
        match_text(p, global_paser[BOOLSAND_PASER], "and");
        match_text(p, global_paser[BOOLSOR_PASER], "or");
        match_text(p, global_paser[MOD_PASER], "%");
        match_text(p, global_paser[LB_PASER], "(");
        match_text(p, global_paser[RB_PASER], ")");
        match_text(p, global_paser[WHILE_PASER], "while");
        match_text(p, global_paser[LP_PASER], "{");
        match_text(p, global_paser[RP_PASER], "}");
        match_text(p, global_paser[IF_PASER], "if");
        match_text(p, global_paser[ELIF_PASER], "elif");
        match_text(p, global_paser[ELSE_PASER], "else");
        match_text(p, global_paser[COLON_PASER], ":");
        match_text(p, global_paser[FOR_PASER], "for");
        match_text(p, global_paser[LI_PASER], "[");
        match_text(p, global_paser[RI_PASER], "]");
        match_text_s(p, global_paser[POW_PASER], "**");
        match_text(p, global_paser[LOG_PASER], "log");
        match_text(p, global_paser[SQRT_PASER], "sqrt");
        match_text(p, global_paser[BITNOT_PASER], "~");
        match_text(p, global_paser[BITRIGHT_PASER], ">>");
        match_text(p, global_paser[BITLEFT_PASER], "<<");
        match_text(p, global_paser[BITAND_PASER], "&");
        match_text(p, global_paser[BITOR_PASER], "|");
        match_text(p, global_paser[BITNOTOR_PASER], "^");
        match_text_s(p, global_paser[MORE_PASER], ">");
        match_text_s(p, global_paser[LESS_PASER], "<");
        match_text_s(p, global_paser[NOTEQ_PASER], "!=");
        match_text_s(p, global_paser[EQEQ_PASER], "==");
        match_text_s(p, global_paser[MOREEQ_PASER], ">=");
        match_text_s(p, global_paser[LESSEQ_PASER], "<=");
        match_text_s(p, global_paser[OR_PASER], "||");
        match_text_s(p, global_paser[AND_PASER], "&&");
        match_text(p, global_paser[NOT_PASER], "!");
        match_text(p, global_paser[EQ_PASER], "=");
        match_text(p, global_paser[DEF_PASER], "def");
        match_text(p, global_paser[COMMA_PASER], ",");
        match_text(p, global_paser[BREAK_PASER], "break");
        match_text(p, global_paser[BROKEN_PASER], "broken");
        match_text(p, global_paser[REGO_PASER], "rego");
        match_text(p, global_paser[REWENT_PASER], "rewent");
        match_text(p, global_paser[RESTART_PASER], "restart");
        match_text_s(p, global_paser[RESTARTED_PASER], "restarted");
        match_text(p, global_paser[CONTINUE_PASER], "continue");
        match_text_s(p, global_paser[CONTINUED_PASER], "continued");
        match_text(p, global_paser[GLOBAL_PASER], "global");
        match_text(p, global_paser[NOLOCAL_PASER], "nolocal");
        match_text(p, global_paser[DEFAULT_PASER], "default");
        match_text(p, global_paser[RETURN_PASER], "return");
        match_str(p, global_paser[STR_PASER]);
        match_text(p, global_paser[TRUE_PASER], "True");
        match_text(p, global_paser[FALSE_PASER], "False");
        match_text(p, global_paser[NONE_PASER], "None");
        match_text(p, global_paser[DO_PASER], "do");
        match_text(p, global_paser[IN_PASER], "in");
        match_text(p, global_paser[CLASS_PASER], "class");
        match_text(p, global_paser[TRY_PASER], "try");
        match_text(p, global_paser[EXCEPT_PASER], "except");
        match_text(p, global_paser[AS_PASER], "as");
        match_text(p, global_paser[RAISE_PASER], "raise");
        match_text(p, global_paser[THROW_PASER], "throw");
        match_text(p, global_paser[ASSERT_PASER], "assert");
        match_text_s(p, global_paser[LAMBDA_PASER], "->");
        match_text(p, global_paser[POINT_PASER], ".");
        match_text(p, global_paser[IMPORT_PASER], "import");
        match_text(p, global_paser[INCLUDE_PASER], "include");
        match_text(p, global_paser[SVAR_PASER], "$");
        match_text(p, global_paser[FUNC_PASER], "function");
        match_text(p, global_paser[CLS_PASER], "cls");
        match_text(p, global_paser[ACTION_PASER], "action");
        match_text(p, global_paser[SETUP_PASER], "setup");
        match_text(p, global_paser[INLINE_PASER], "inline");
        match_text(p, global_paser[PROTECT_PASER], "protect");
        match_text(p, global_paser[PUBLIC_PASER], "public");
        match_text(p, global_paser[PRIVATE_PASER], "private");
        match_text(p, global_paser[FINALLY_PASER], "finally");
        match_text(p, global_paser[IS_PASER], "is");
        match_text(p, global_paser[SEMICOLON_PASER], ";");

        *index = check_list(global_paser, p, status);  // 检查解析结果

        if(*index >= 0){  // index >= 0表示找到解析的结果[存在一个解析器存在结果，其他解析器没有结果]
            fprintf(debug, "[info][lexical]  get value = '%s' len = %d from %d\n\n", global_paser[*index]->text, strlen(global_paser[*index]->text),*index);
            fprintf(status_log, "[info][lexical]  get value = '%s' len = %d from %d\n", global_paser[*index]->text, strlen(global_paser[*index]->text),*index);
            break;
        }
        else if(*index == -2){  // -2表示全部解析器没有结果
            fprintf(debug, "[error][lexical]  Paser Wrong!\n\n");
            break;
        }
        else if(is_eof){  // 以上状况均不是，如果是eof仍要推出
            fprintf(debug, "[error][lexical]  EOF Paser Wrong!\n\n");
            return 0;
        }
        else{
            fprintf(debug, "[debug][lexical]  continue to paser\n\n");
        }
        // else情况：继续匹配
    }
    return 1;
}

char read_p(p_status *status){  // 读取一个字符
    return getc(status->file_p);
}

void back_p(char p, p_status *status){  // 回退一个字符
    if(p == EOF){
        fprintf(debug, "[info][lexical]  back_p <EOF>\n\n");
        return;
    }
    fseek(status->file_p, -1, 1);
    fprintf(debug, "[info][lexical]  back_p\n\n");
}

word_paser **login_paser(){
    word_paser **paser_list = malloc(sizeof(word_paser *) * MAX_PASER_SIZE);  // 指针数组的指针
    for(int i = 0;i < MAX_PASER_SIZE;i += 1){  // 申请内存并初始化
        paser_list[i] = malloc(sizeof(word_paser));
        paser_list[i]->status = START;
        paser_list[i]->text = NULL;
    }
    return paser_list;
}

void set_start(word_paser **paser_list){  // 初始化
    for(int i = 0;i < MAX_PASER_SIZE;i += 1){
        paser_list[i]->status = START;
        if(paser_list[i]->text != NULL){
            free(paser_list[i]->text);
        }
        paser_list[i]->text = NULL;
    }
    fprintf(debug, "[info][lexical]  set_start\n\n");
}

void free_list(word_paser **paser_list){  // 释放空间
    for(int i = 0;i < MAX_PASER_SIZE;i += 1){
        if(paser_list[i]->text != NULL){  // 释放text
            free(paser_list[i]->text);
            paser_list[i]->text = NULL;
        }
        free(paser_list[i]);  // 释放数组元素
    }
    free(paser_list);  // 释放数组本身
}

int check_list(word_paser **paser_list, char p, p_status *status){  // 检查结果
    // 统计数据
    int end_count = 0;
    int s_end_count = 0;  // 二级合并
    int not_count = 0;

    int end_index = 0;  // 最后一个匹配成功的解析器的index
    int s_end_index = 0;  // 最后一个匹配成功的解析器的index
    for(int i = 0;i < MAX_PASER_SIZE;i += 1){
        if(paser_list[i]->status == END){  // 统计END的次数
            end_count += 1;
            end_index = i;
        }
        else if(paser_list[i]->status == S_END){  // 统计END的次数
            s_end_count += 1;
            s_end_index = i;
        }
        else if(paser_list[i]->status == NOTMATCH){  // 统计END的次数
            not_count += 1;
        }
        fprintf(debug, "[debug][lexical]  check list : paser_list[%d]->status = %d\n", i, paser_list[i]->status);
    }
    fprintf(debug, "[debug][lexical]  check list : end_count = %d\n", end_count);
    fprintf(debug, "[debug][lexical]  check list : s_end_count = %d\n", s_end_count);
    fprintf(debug, "[debug][lexical]  check list : not_count = %d\n", not_count);
    fprintf(debug, "[debug][lexical]  check list : count all = %d\n\n", MAX_PASER_SIZE);

    if(end_count == 0 && s_end_count == 1){  // 晋升
        end_count = 1;
        s_end_count = 0;
        end_index = s_end_index;
    }
    else{
        not_count += s_end_count;  // 降级
    }

    // 需要往回放一个字符
    if((MAX_PASER_SIZE - not_count - end_count) == 0 && end_count == 1){  // 除了不匹配就是匹配成功，且只有一个成功
        back_p(p, status);  // 回退一个字符[所有匹配成功的都必须吞一个字符，然后再这里统一回退]
        return end_index;
    }
    if(MAX_PASER_SIZE == not_count){  // 全部匹配不正确，没有一个成功
        return -2;  // 错误
    }
    else{
        return -1;  // 需要继续匹配
    }
}

void match_int(char p, word_paser *paser){  // 匹配一个int
    if(USE){  // USE是判断STATUS的条件
        GET_LEN(paser);
        if(p <= '9' && p >= '0'){  // 是数字
            SET_TEXT(paser);  // 设置text
            paser->status = 1;
        }
        else{
            NO_MATCH(paser);  // 没有成功匹配的处理
        }
    }
    UNUSE_SET;  // if(USE)的else语句
}

void match_double(char p, word_paser *paser){  // 匹配一个double
    if(USE){
        GET_LEN(paser);
        if((p <= '9' && p >= '0') || (p == '.' && paser->status == 1)){  // 是数字
            if(paser->status == START){
                paser->text = (char *)malloc(sizeof(char));
                paser->status = 1;
            }
            else{
                paser->text = (char *)realloc(paser->text, sizeof(char) * (len + 2));
                if(p == '.'){
                    paser->status = 2; 
                }
            }
            paser->text[len] = p;
            paser->text[len + 1] = '\0';
        }
        else{
            if(paser->status == 2){  // 必须进入小数模式才可以
                paser->status = END;
            }
            else{  // 没有匹配上
                paser->status = NOTMATCH;
            }
        }
    }
    UNUSE_SET;
}

void match_str(char p, word_paser *paser){  // 匹配一个var字符串
    if(USE){
        GET_LEN(paser);
        if(paser->status == START){  // start模式先匹配'或者"
            if(p == '\''){
                paser->text = NULL;
                paser->status = 1;
            }
            else if(p == '\"'){
                paser->text = NULL;
                paser->status = 2;
            }
            else{
                paser->status = NOTMATCH;
            }
        }
        else{
            if((p != '\'' && paser->status == 1) || (p != '\"' && paser->status == 2)){  // 匹配到最后一个
                paser->text = (char *)realloc(paser->text, sizeof(char) * (len + 2));
                paser->text[len] = p;
                paser->text[len + 1] = '\0';
            }
            else{
                paser->status = WAIT_END;
            }
        }
    }
    UNUSE_SET;
}

void match_var(char p, word_paser *paser){  // 匹配一个var
    if(USE){
        GET_LEN(paser);
        if(paser->status == START){
            if(p == '_' || (p <= 'z' && p >= 'a') || (p <= 'Z' && p >= 'A')){
                paser->text = (char *)malloc(sizeof(char));
                paser->text[len] = p;
                paser->text[len + 1] = '\0';
                paser->status = 1;
            }
            else{
                paser->status = NOTMATCH;
            }
        }
        else{
            if(p == '_' || (p <= 'z' && p >= 'a') || (p <= '9' && p >= '0') || (p <= 'Z' && p >= 'A')){
                paser->text = (char *)realloc(paser->text, sizeof(char) * (len + 2));
                paser->text[len] = p;
                paser->text[len + 1] = '\0';
            }
            else{
                paser->status = S_END;
            }
        }
    }
    UNUSE_SET;
}

void match_comment(char p, word_paser *paser){  // 匹配一个注释
    if(USE){
        GET_LEN(paser);  // 设置len并且处理NULL
        if(paser->status == START){
            if(p == '#'){
                SET_TEXT(paser);  // 设置text
                paser->status = 1;
            }
            else{
                paser->status = NOTMATCH;
            }
        }
        else if(paser->status == 1){  // 如果是#!代表多行注释
            if(p == '!'){
                paser->status = 2;
            }
            else{
                paser->status = 3;
                if(p == '#'){  // 注释结束
                    paser->status = WAIT_END;
                }
                else if(p == '\n'){
                    paser->status = END;
                }
            }
        }
        else{
            if(p == '#'){  // 注释结束
                paser->status = WAIT_END;
            }
            else if(p == '\n' && paser->status == 3){
                paser->status = END;
            }
        }
    }
    UNUSE_SET;
}

void match_enter(char p, word_paser *paser){  // 匹配一个强力注释
    if(USE){
        GET_LEN(paser);  // 设置len并且处理NULL
        if(paser->status == START){
            if(p == '\\'){
                SET_TEXT(paser);  // 设置text
                paser->status = 1;
            }
            else{
                paser->status = NOTMATCH;
            }
        }
        else{
            if(p == '\n'){
                paser->status = WAIT_END;
            }
        }
    }
    UNUSE_SET;
}

void match_text(char p, word_paser *paser, char *text){  // 匹配换行符
    char *match = text;  // 待匹配字符串
    if(USE){
        GET_LEN(paser);  // 设置len并且处理NULL
        if(p == match[len]){  // 匹配成功
            SET_TEXT(paser);  // 设置text
            CHECK_END(paser);  // 设置是否完全匹配
        }
        else{
            paser->status = NOTMATCH;
        }
    }
    UNUSE_SET;
}

void match_text_s(char p, word_paser *paser, char *text){  // 匹配换行符
    char *match = text;  // 待匹配字符串
    if(USE){
        GET_LEN(paser);  // 设置len并且处理NULL
        if(p == match[len]){  // 匹配成功
            SET_TEXT(paser);  // 设置text
            CHECK_END(paser);  // 设置是否完全匹配
        }
        else{
            paser->status = NOTMATCH;
        }
    }
    else if(paser->status == WAIT_END){
        paser->status = S_END;
    }
    UNUSE_SET;
}