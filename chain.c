#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "chain.h"

struct graph {
    size_t size_graph;
    char** v_graph;
    double** e_graph;
} graph;

struct graph* create_new_machine_graph_file(FILE *file){
    return load_graph(file);
}

struct graph* create_new_machine(FILE *file){
    char* str = read_file(file);
    if (str == NULL){
        return NULL;
    }
    struct graph* graph = graph_create(strlen(str));
    if (graph == NULL){
        return NULL;
    }
    create_machine(str, graph);
    return graph;
}

char* generate(struct graph const* graph){
    size_t buf = graph->size_graph * 250;
    char* str = (char*)malloc(buf * sizeof(char));
    *str = '\0';
    int ind = 0;
    while(1){
        double rand_v = (double)rand()/RAND_MAX;
        if (graph->e_graph[ind][0] >= rand_v){
            str = strcat(str, graph->v_graph[0]);
            str = do_res_string(str);
            return str;
        }
        for (int i = 1; i < graph->size_graph; ++i){
            if (graph->e_graph[ind][i-1] < rand_v && graph->e_graph[ind][i] >= rand_v){
                str = strcat(str, graph->v_graph[i]);
                str = strcat(str, " ");
                ind = i;
                if (strlen(str) >= buf - 250){
                    free(str);
                    return NULL;
                }
                break;
            }
        }
    }
}

char* read_file(FILE *f){
    long n = 0;
    int c;

    check_fsize(f);
    size_t sz = get_file_size(f);

    char* str = (char*)malloc(sz * sizeof(char) + 1);

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
        if  (*str_cur == ' ' && find_char_in_template(*(str_cur + 1), ".,?!-:;")){

            if (*(str_cur + 2) != '\0' && char_in_interval(*(str_cur + 3), 'a', 'z') &&
                find_char_in_template(*(str_cur + 1), ".?!")){
                *(str_cur + 3) = (*(str_cur + 3) - (char)'a') + (char)'A';
            }

            ++str_cur;
            continue;
        }
        *res_cur = *str_cur;
        ++str_cur;
        ++res_cur;
    }

    if (char_in_interval(*result, 'a', 'z')){
        *result = (*result - (char)'a') + (char)'A';
    }
    *res_cur = '\0';
    return result;
}

bool check_fsize(FILE *f){
    if (f == NULL){
        return false;
    }

    size_t sz = get_file_size(f);

    if (sz >= 25000){
        fprintf(stderr, "Внимание: файл содержит %ld символов.\n", sz);
        char c = 'N';
        printf("Вы уверены, что хотите продолжить? (y, N)\n");
        scanf("%s", &c);
        if ( !(c == 'Y' || c == 'y')) {
            exit(EXIT_SUCCESS);
        }
        if (sz >= 50000) {
            printf("Я Вас предупреждала...\n");
        }
    }
    return true;
}

size_t get_file_size(FILE *f){
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    return (size_t)sz;
}