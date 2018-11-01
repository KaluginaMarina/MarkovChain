#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindless_machine.h"
#include "chain.h"

int main() {
    graph* graph = create_new_machine_graph_file("tolstoy");
    //printf("%s\n", generate(graph));
    char* str = generate(graph);
    int i = 0;
    while (str == NULL){
        printf("%d\n", ++i);
        str = generate(graph);
    }
    printf("%s\n", str);
    return(0);
}