#include <time.h>
#include <getopt.h>
#include "mindless_machine.h"
#include "chain.h"
#include "graphio.h"

int main(int argc, char *argv[]) {
    srand ((unsigned)time( NULL));
    int flags = parse_flags(argc, argv);

    if(argv[optind] == NULL){
        fprintf(stderr, "Не введено имя файла.\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[optind];

    struct graph* graph = create_graph(flags, filename);

    generate_text(graph);

    if ((flags & FLAG_SAVE_GRAPH) != 0) {
        graph_save(flags, filename, graph);
    }

    exit(EXIT_SUCCESS);
}