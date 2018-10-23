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

//есди rand = 0
char* generate(graph* graph){
    char* str = (char*)malloc(9999 * sizeof(char));
    srand (time( NULL));
    int ind = 0;
    while(1){
        double rand_v = (double)rand()/RAND_MAX;
        if (graph->e_graph[ind][0] >= rand_v){
            str = strcat(str, graph->v_graph[0]);
            return str;
        }
        int i;
        for (i = 1; i < graph->size_graph; ++i){
            if (graph->e_graph[ind][i-1] < rand_v && graph->e_graph[ind][i] >= rand_v){
                str = strcat(str, graph->v_graph[i]);
                str = strcat(str, " ");
                ind = i;
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