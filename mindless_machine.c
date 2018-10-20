#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mindless_machine.h"

int read_string (char *str) {
    char s = ' ';
    int n = 0;

    if (str == NULL) {
        return -2;
    }

    while (s != '\n') {
        scanf("%c", &s);
        *(str + n) = s;
        ++n;
        if (n > N) {
            return -1;
        }
    }

    --n;
    *(str + n) = '\0';
    return n;
}


int write_console(char *str) {

    char *cur = str;
    if (str == NULL) {
        return -1;
    }

    while (*cur != '\0') {
        printf("%c", *cur);
        ++cur;
    }
    return 0;
}

int read_file(char *fname, char *str){
    int n = 0, c;
    FILE *f = fopen(fname, "r");
    if (f == NULL){
        return -2;
    }

    while(!feof(f)) {
        c = fgetc(f);
        if (n >= N){
            return -1;
        }
        *(str + n) = (char)c;
        ++n;
    }
    --n;
    *(str + n) = '\0';
    fclose(f);
    return n;
}

int write_file(char *fname, char *str){
    char *cur = str;
    FILE *f = fopen(fname, "w+");
    if (str == NULL) {
        return -1;
    }
    while (*cur != '\0') {
        fprintf(f, "%c", *cur);
        ++cur;
    }
    return(0);
}

int str_parse(char* str, char* v_graph, int** e_graph){

    str_to_down(str);
    str = str_replace_punct(str);

    char* prev = ".";

    str = strtok (str, " ");
    while (str != NULL) {
        str = strtok (NULL, " ");
    }
}



//TODO поддержка русских символов
bool str_to_down(char* str){
    if (str == NULL){
        return false;
    }
    char* cur = str;
    while (*cur != '\0'){
        if (*cur >= (char)'A' && *cur <= (char)'Z'){
            *cur = (*cur - (char)'A') + (char)'a';
        }
        ++cur;
    }
    return true;
}

char* str_replace_punct(char* str){
    char* res_str = (char*)malloc(2 * strlen(str) * sizeof(char)); //результирующая строка может быть максимум в 2 раа больше
    char* cur_str = str;
    char* cur_res = res_str;

    while(*cur_str != '\0'){
        if (*cur_str == '.' || *cur_str == ',' || *cur_str == '?' || *cur_str == '!' || *cur_str == '-' || *cur_str == ':') {//TODO должно быть, можно сделать тут регулярку.Тут не все.
            *cur_res = ' ';
            ++cur_res;
        }
        *cur_res = *cur_str;
        ++cur_str;
        ++cur_res;
    }
    free(str);
    return res_str;
}

