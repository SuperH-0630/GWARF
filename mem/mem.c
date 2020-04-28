#undef malloc
#undef calloc
#undef free
#undef realloc
#undef memcpy


void *safe_calloc(size_t size, size_t num){
    void *tmp;
    tmp = calloc(size, num);
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
        puts("free Wrong!");
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