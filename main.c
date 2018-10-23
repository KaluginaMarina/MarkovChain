#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindless_machine.h"
#include "chain.h"

int main() {

//    graph* gr = graph_create(10);
//    gr->size_graph = 3;
//    gr->v_graph[0] = "i";
//    gr->v_graph[1] = "Markov's";
//    gr->v_graph[2] = "chain";
//    gr->e_graph[0][1] = 1;
//    gr->e_graph[1][2] = 1;
//
//    graph_print(gr);
//
//    char* str1 = "chain";
//    char* str2 = "hello";
//    printf("Строка %s -- %d элемент графа\n", str1, graph_search_elem(str1, gr));
//    printf("Строка %s -- %d элемент графа\n\n", str2, graph_search_elem(str2, gr));
//
//    printf("Добавим вершину %s\n", str2);
//    graph_add_v_graph(str2, gr);
//    graph_print(gr);
//
//    printf("Строка %s -- %d элемент графа\n", str2, graph_search_elem(str2, gr));
//
//
//    graph_add_e_graph("hello", "i", gr);
//
//    printf("\nДобавили отношение %s --> %s", gr->v_graph[3], gr->v_graph[0]);
//
//    graph_print(gr);
//
//    printf("Загрузили граф в graph.txt и снова его считали:");
//    save_graph("graph.txt", gr);
//    gr = load_graph("graph.txt");
//    graph_print(gr);

    graph* grgr = create_new_machine("lev_tolstoy_100.txt");
//    if (grgr == NULL) {
//        printf("NULL");
//    } else graph_print(grgr);

    printf("%s\n", generate(grgr));

//    graph* graph1 = graph_create(100);
//    char* str_ = (char*)malloc(100 * sizeof(char));
//    read_string(str_);
//    create_machine(str_, graph1);
//    graph_print(graph1);
    return(0);
}