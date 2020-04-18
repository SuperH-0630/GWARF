#undef malloc
#undef free
#undef realloc
#undef memcpy

void *safe_malloc(size_t size){
    void *tmp;
    tmp = malloc(size);
    memset(tmp, 0, size);  // 初始化[避免因为其他东西溢出，所以要初始化了]
    if(tmp != NULL){
        return tmp;
    }
    else{
        puts("malloc error");
        exit(1);
    }
}

void *safe_free(void *p){  // 安全的释放
    if(p == NULL){
        return p;  // p已经释放了
    }
    free(p);
    p = NULL;
    return p;
}

void *safe_realloc(void *p, size_t size){
    void *tmp;
    tmp = realloc(p, size);
    if(tmp != NULL){
        return tmp;
    }
    else{
        puts("realloc error");
        exit(1);
    }
}

void *safe_memcpy(void *p1, const void *p2, size_t size){
    void *tmp;
    tmp = memcpy(p1, p2, size);
    if(tmp != NULL){
        return tmp;
    }
    else{
        puts("memcpy error");
        exit(1);
    }
}