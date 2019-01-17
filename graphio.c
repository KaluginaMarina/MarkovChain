#include <stdbool.h>
#include <stddef.h>
#include <getopt.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include "graphio.h"
#include "chain.h"
int N = 1;
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

int parse_flags(int argc, char *argv[]){
    int flags = 0, opt = 0;
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
                N = (int)strtol(argv[optind], &p, 10);
                if (errno != 0 || *p != '\0' || N > INT_MAX) {
                    fprintf(stderr, "Неверное значение N.\n");
                    exit(EXIT_FAILURE);
                }
                printf("Количество предложений: %d\n\n", N);
                ++optind;
                break;
            default:
                fprintf(stderr, "Используйте: %s [-l] [-s] [-n NUM] FILE\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    return flags;
}

struct graph* create_graph(int flags, char* filename) {
    struct graph* graph;
    if ((flags & FLAG_LOAD_FILE) != 0){
        filename[strlen(filename) - 4] = '\0';
        FILE *file = fopen(filename, "r");
        graph = create_new_machine_graph_file(file);
        if (graph == NULL){
            fprintf(stderr, "Неверное имя файла или граф не был сохранен.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        FILE *file = fopen(filename, "r");
        graph = create_new_machine(file);
        if (graph == NULL){
            fprintf(stderr, "Неверное имя файла.\n");
            exit(EXIT_FAILURE);
        }
    }
    return graph;
}

void generate_text(struct graph* graph){
    char* str;
    for (int i = 0; i < N; ++i){
        str = generate(graph);
        while (str == NULL){
            str = generate(graph);
        }
        printf("%s\n", str);
    }
}

void graph_save(int flags, char *filename, struct graph* graph){
    if ((flags & FLAG_LOAD_FILE) == 0) {
        filename[strlen(filename) - 4] = '\0';
        FILE* file = fopen(filename, "w+");
        save_graph(file, graph);
        fclose(file);
        printf("\nГраф был сохранен. Пользуйтесь ключем [-l] для загрузки сохраненного графа.\n");
    }
}