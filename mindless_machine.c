#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mindless_machine.h"
#include "graphio.h"

struct graph {
size_t size_graph;
char** v_graph;
double** e_graph;
} graph;

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

int write_console(char const *str) {

    const char *cur = str;
    if (str == NULL) {
        return -1;
    }

    while (*cur != '\0') {
        printf("%c", *cur);
        ++cur;
    }
    return 0;
}

int write_file(char const *fname, char const *str){
    const char *cur = str;
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

int create_machine(char *str, struct graph *graph){
    if (str == NULL || graph == NULL){
        return -1;
    }
    str_to_down(str);
    str = str_replace_punct(str);
    char* str_prev = ".";
    str = strtok (str, " \n");
    while (str != NULL) {
        graph_add_e_graph(str_prev, str, graph);
        str_prev = str;
        str = strtok (NULL, " ");
    }
    graph->e_graph[0][0] = 0;
    graph_to_probability(graph);
    return 0;
}

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
        if (find_char_in_template(*cur_str, "\"\r\n\t")){
            ++cur_str;
            *cur_res = ' ';
            ++cur_res;
            continue;
        }

        if (!find_char_in_template(*cur_str, " \'") && !char_in_interval(*cur_str, 'a', 'z') &&
             !char_in_interval(*cur_str, 'A', 'Z') && !char_in_interval(*cur_str, '0', '9')){
            *cur_res = ' ';
            ++cur_res;
        }

        *cur_res = *cur_str;
        ++cur_res;
        if (*cur_str == '-'){
            *cur_res = ' ';
            ++cur_res;
        }
        ++cur_str;
    }
    *cur_res = '\0';
    free(str);
    return res_str;
}

struct graph* graph_create(size_t sz) {
    struct graph *gr = (struct graph *) malloc(sizeof(gr));
    gr->size_graph = 0;
    gr->v_graph = (char **) malloc(sz * sizeof(char *));
    for (size_t i = 0; i < sz; ++i) {
        gr->v_graph[i] = (char *) malloc(sizeof(char) * 256);
    }
    gr->e_graph = (double **) malloc(sz * sizeof(double *));
    for (size_t i = 0; i < sz; ++i) {
        gr->e_graph[i] = (double *) malloc(sz * sizeof(double));
        for (size_t j = 0; j < sz; ++j) {
            gr->e_graph[i][j] = 0;
        }
    }
    return gr;
}

int graph_search_elem(char const *str,  struct graph const* graph){
    if (str == NULL || graph == NULL){
        return -2;
    }
    for (size_t i = 0; i < graph->size_graph; ++i){
        if (strcmp(graph->v_graph[i], str) == 0){
            return (int)i;
        }
    }
    return -1;
}

int graph_add_v_graph(char const *str, struct graph* graph){
    if (str == NULL || graph == NULL){
        return -1;
    }
    int s = graph_search_elem(str, graph);
    if (s != -1){
        return s;
    }
    ++(graph->size_graph);
    graph->v_graph[graph->size_graph - 1] = (char*)str;
    return (int)graph->size_graph - 1;
}

int graph_add_e_graph(char const *str_prev, char const *str_cur, struct graph* graph){
    if(str_cur == NULL || str_prev == NULL || graph == NULL){
        return -1;
    }
    int i, j;
    i = graph_add_v_graph(str_prev, graph);
    j = graph_add_v_graph(str_cur, graph);

    ++(graph->e_graph[i][j]);
    return 0;
}

bool save_graph(FILE *output_file, struct graph const* graph){
    if (output_file == NULL){
        return false;
    }
    fprintf(output_file, "%lu\n", graph->size_graph);
    for (size_t i = 0; i < graph->size_graph; ++i){
        fprintf(output_file, "%s\n", graph->v_graph[i]);
    }
    for(size_t i = 0; i < graph->size_graph; ++i){
        for (size_t j = 0; j < graph->size_graph; ++j){
            fprintf(output_file, "%lf ", graph->e_graph[i][j]);
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
    return true;
}

struct graph* load_graph(FILE *input_file){

    if (input_file == NULL){
        return NULL;
    }

    size_t sz;
    if (fscanf(input_file, "%lu", &sz) != 1){
        return NULL;
    }
    struct graph* graph = graph_create(sz);

    graph->size_graph = sz;
    for (size_t i = 0; i < sz; ++i){
        fscanf(input_file, "%s", graph->v_graph[i]);
    }

    for (size_t i = 0; i < sz; ++i){
        for (size_t j = 0; j < sz; ++j){
            if (fscanf(input_file, "%lf", &graph->e_graph[i][j]) == EOF) {
                return NULL;
            }
        }
    }

    fclose(input_file);
    return graph;
}

bool graph_to_probability(struct graph *graph){
    if (graph == NULL){
        return false;
    }

    for (size_t i = 0; i < graph->size_graph; ++i) {
        graph->e_graph[i][i] = 0;
    }
    for (size_t i = 0; i < graph->size_graph; ++i){
        double sum = 0;
        for(size_t j = 0; j < graph->size_graph; ++j){
            sum += graph->e_graph[i][j];
        }
        if (sum == 0){
            graph->e_graph[i][0] = 1;
            sum = 1;
        }
        for(size_t j= 0; j < graph->size_graph; ++j){
            graph->e_graph[i][j] = graph->e_graph[i][j] / sum + ((j == 0)? 0 : graph->e_graph[i][j - 1]);
        }
    }
    return true;
}

bool find_char_in_template(char c, char const *template){
    if (template == NULL){
        return false;
    }
    const char *cur = template;
    while (*cur != '\0') {
        if (c == *cur){
            return true;
        }
        ++cur;
    }
    return false;
}

bool char_in_interval(char c, char start, char end){
    if (c >= start && c <= end){
        return true;
    }
    return false;
}