#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "chain.h"

graph* create_new_machine_graph_file(char* filename){
    return load_graph(filename);
}

graph* create_new_machine(char* filename){
    char* str = read_file(filename);
    if (str == NULL){
        return NULL;
    }
    graph* graph = graph_create(strlen(str));
    if (graph == NULL){
        return NULL;
    }
    create_machine(str, graph);
    return graph;
}

char* generate(graph* graph){
    size_t buf = graph->size_graph * 250;
    char* str = (char*)malloc(buf * sizeof(char));
    *str = '\0';
    srand (time( NULL));
    int ind = 0;
    while(1){
        double rand_v = (double)rand()/RAND_MAX;
        if (graph->e_graph[ind][0] >= rand_v){
            str = strcat(str, graph->v_graph[0]);
            str = do_res_string(str);
            return str;
        }
        int i;
        for (i = 1; i < graph->size_graph; ++i){
            if (graph->e_graph[ind][i-1] < rand_v && graph->e_graph[ind][i] >= rand_v){
                str = strcat(str, graph->v_graph[i]);
                str = strcat(str, " ");
                ind = i;
                if (strlen(str) >= buf - 250){
                    free(str);
                    return NULL;
                }
                continue;
            }
        }
    }
}

char* read_file(char *fname){
    long n = 0;
    int c;

    FILE *f = fopen(fname, "r");
    if (f == NULL){
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);

    char* str = (char*)malloc(sz * sizeof(char));

    while(!feof(f)) {
        c = fgetc(f);
        *(str + n) = (char)c;
        ++n;
    }
    --n;
    *(str + n) = '\0';
    fclose(f);
    return str;
}

char* do_res_string(char* str){
    char* result = (char*)malloc(9999 * sizeof(char));
    char* str_cur = str;
    char* res_cur = result;
    while (*str_cur != '\0'){
        if  (*str_cur == ' ' &&
            (*(str_cur + 1) == '.' || *(str_cur + 1) == ',' || *(str_cur + 1) == '?' || *(str_cur + 1) == '!' ||
             *(str_cur + 1) == '-' || *(str_cur + 1) == ':' || *(str_cur + 1) == ';')){
            if (*(str_cur + 2) >= (char)'a' && *(str_cur + 2) <= (char)'z'){
                *(str_cur + 2) = (*(str_cur + 2) - (char)'a') + (char)'A';
            }
            ++str_cur;
            continue;
        }
        *res_cur = *str_cur;
        ++str_cur;
        ++res_cur;
    }
    if (*result >= (char)'a' && *result <= (char)'z'){
        *result = (*result - (char)'a') + (char)'A';
    }
    *res_cur = '\0';
    return result;
}