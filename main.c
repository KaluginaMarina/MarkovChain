#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindless_machine.h"

int main() {

    graph* gr = graph_create(3);
    gr->size_graph = 3;
    gr->v_graph[0] = "i";
    gr->v_graph[1] = "Markov's";
    gr->v_graph[2] = "chain";
    gr->e_graph[0][1] = 1;
    gr->e_graph[1][2] = 1;

    graph_print(gr);
    return(0);
}