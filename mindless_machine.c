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

//TODO написать эту функцию после всех функций для работы с графом
int str_parse(char* str, graph graph){

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

graph* graph_create(size_t sz){
    size_t i, j;
    graph* gr = (graph*)malloc(sizeof(gr));
    gr->size_graph = 0;
    gr->v_graph = (char**)malloc(sz * sizeof(char*));
    for (i = 0; i < sz; ++i){
        gr->v_graph[i] = (char*)malloc(sizeof(char) * 256);
    }
    gr->e_graph = (int**)malloc(sz * sizeof(int*));
    for (i = 0; i < sz; ++i){
        gr->e_graph[i] = (int*)malloc(sz * sizeof(int));
        for(j = 0; j < sz; ++j){
            gr->e_graph[i][j] = 0;
        }
    }
    return gr;
}

void graph_print(graph* graph){
    printf("\n======================================\n"
           "Колиество вершин: %lu\n\n"
           "Вершины графа: \n", graph->size_graph);
    size_t i, j;
    for (i = 0; i < graph->size_graph; ++i){
        printf("#%lu -- %s\n", i, graph->v_graph[i]);
    }
    printf("\n");
    for (i = 0; i < graph->size_graph; ++i){
        for (j = 0; j < graph->size_graph; ++j){
            printf("%d ", graph->e_graph[i][j]);
        }
        printf("\n");
    }
    printf("\n======================================\n");
}