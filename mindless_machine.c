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

int create_machine(char *str, graph *graph){
    if (str == NULL || graph == NULL){
        return -1;
    }
    str_to_down(str);
    str = str_replace_punct(str);
    char* str_prev = ".";
    str = strtok (str, " \n");
    while (str != NULL) {
        str = strtok (NULL, " ");
        graph_add_e_graph(str_prev, str, graph);
        str_prev = str;
    }
    graph->e_graph[0][0] = 0;
    graph_to_probability(graph);
    return 0;
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
        if (*cur_str == '.' || *cur_str == ',' || *cur_str == '?' || *cur_str == '!' || *cur_str == '-' || *cur_str == ':' || *cur_str == ';') {//TODO должно быть, можно сделать тут регулярку.Тут не все.
            *cur_res = ' ';
            ++cur_res;
        }
        if (*cur_str == '"' || *cur_str == '\n'){
            ++cur_str;
            *cur_res = ' ';
            ++cur_res;
        }
        *cur_res = *cur_str;
        ++cur_str;
        ++cur_res;
    }
    *cur_res = '\0';
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
    gr->e_graph = (double**)malloc(sz * sizeof(double *));
    for (i = 0; i < sz; ++i){
        gr->e_graph[i] = (double*)malloc(sz * sizeof(double));
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
            printf("%f ", graph->e_graph[i][j]);
        }
        printf("\n");
    }
    printf("\n======================================\n\n");
}

int graph_search_elem(char *str, graph const* graph){
    if (str == NULL || graph == NULL){
        return -2;
    }
    size_t i;
    for (i = 0; i < graph->size_graph; ++i){
        if (strcmp(graph->v_graph[i], str) == 0){
            return (int)i;
        }
    }
    return -1;
}

int graph_add_v_graph(char *str, graph* graph){
    if (str == NULL || graph == NULL){
        return -1;
    }
    int s = graph_search_elem(str, graph);
    if (s != -1){
        return s;
    }
    ++(graph->size_graph);
    graph->v_graph[graph->size_graph - 1] = str;
    return (int)graph->size_graph - 1;
}

int graph_add_e_graph(char *str_prev, char *str_cur, graph* graph){
    if(str_cur == NULL || str_prev == NULL || graph == NULL){
        return -1;
    }
    int i, j;
    i = graph_add_v_graph(str_prev, graph);
    j = graph_add_v_graph(str_cur, graph);

    ++(graph->e_graph[i][j]);
    return 0;
}

bool save_graph(char* filename, graph* graph){
    FILE* output_file = fopen(filename, "w+");
    if (output_file == NULL){
        return false;
    }
    size_t i, j;
    fprintf(output_file, "%lu\n", graph->size_graph);
    for (i = 0; i < graph->size_graph; ++i){
        fprintf(output_file, "%s\n", graph->v_graph[i]);
    }
    for(i = 0; i < graph->size_graph; ++i){
        for (j = 0; j < graph->size_graph; ++j){
            fprintf(output_file, "%lf ", graph->e_graph[i][j]);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
    return true;
}

graph* load_graph(char* filename){

    FILE* input_file = fopen(filename, "r");
    if (input_file == NULL){
        return NULL;
    }

    size_t sz, i, j;
    if (fscanf(input_file, "%lu", &sz) != 1){
        return NULL;
    }
    graph* graph = graph_create(sz);

    graph->size_graph = sz;
    for (i = 0; i < sz; ++i){
        fscanf(input_file, "%s", graph->v_graph[i]);
    }

    for (i = 0; i < sz; ++i){
        for (j = 0; j < sz; ++j){
            fscanf(input_file, "%lf", &graph->e_graph[i][j]);
        }
    }

    fclose(input_file);
    return graph;
}

bool graph_to_probability(graph *graph){
    if (graph == NULL){
        return false;
    }
    size_t i, j;
    for (i = 0; i < graph->size_graph; ++i){
        double sum = 0;
        for(j = 0; j < graph->size_graph; ++j){
            sum += graph->e_graph[i][j];
        }
        if (sum == 0) continue;
        for(j = 0; j < graph->size_graph; ++j){
            graph->e_graph[i][j] = graph->e_graph[i][j] / sum + ((j == 0)? 0 : graph->e_graph[i][j - 1]);
        }
    }
    return true;
}