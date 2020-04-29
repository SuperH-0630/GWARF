#ifndef MEM_INCLUDE
#define MEM_INCLUDE

struct word_paser **global_paser;  // 解析器，记录状态和text
FILE *debug = NULL, *status_log = NULL, *token_log = NULL;
FILE *file_p = NULL;

#endif