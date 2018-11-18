#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include "mindless_machine.h"
#include "chain.h"

#define FLAG_LOAD_FILE 1
#define FLAG_SAVE_GRAPH 2
#define FLAG_AMOUNT 4

int main(int argc, char *argv[]) {
    int flags = 0, opt = 0;
    int n = 1;
    srand ((unsigned)time( NULL));
    while ((opt = getopt(argc, argv, "sln")) != -1) {
        switch (opt) {
            case 's':
                flags |= FLAG_SAVE_GRAPH;
                break;
            case 'l':
                flags |= FLAG_LOAD_FILE;
                break;
            case 'n':
                flags |= FLAG_AMOUNT;
                char *p;
                n = (int)strtol(argv[optind], &p, 10);
                if (errno != 0 || *p != '\0' || n > INT_MAX) {
                    fprintf(stderr, "Неверное значение n.\n");
                    exit(EXIT_FAILURE);
                }
                printf("Количество предложений: %d\n\n", n);
                ++optind;
                break;
            default:
                fprintf(stderr, "Используйте: %s [-l] [-s] [-n NUM] FILE\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(argv[optind] == NULL){
        fprintf(stderr, "Не введено имя файла.\n");
        exit(EXIT_FAILURE);
    }
    char* filename = argv[optind];

    graph* graph;
    if ((flags & FLAG_LOAD_FILE) != 0){
        filename[strlen(filename) - 4] = '\0';
        graph = create_new_machine_graph_file(filename);
        if (graph == NULL){
            fprintf(stderr, "Неверное имя файла или граф не был сохранен.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        graph = create_new_machine(filename);
        if (graph == NULL){
            fprintf(stderr, "Неверное имя файла.\n");
            exit(EXIT_FAILURE);
        }
    }


    char* str;
    for (int i = 0; i < n; ++i){
        str = generate(graph);
        while (str == NULL){
            str = generate(graph);
        }
        printf("%s\n", str);
    }

    if ((flags & FLAG_SAVE_GRAPH) != 0) {
        if ((flags & FLAG_LOAD_FILE) == 0) {
            filename[strlen(filename) - 4] = '\0';
            save_graph(filename, graph);
        }
    }
    exit(EXIT_SUCCESS);
}