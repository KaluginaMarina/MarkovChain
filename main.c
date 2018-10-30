#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindless_machine.h"
#include "chain.h"

int main() {
    graph* grgr = create_new_machine("Bredberi.txt");
    printf("%s\n", generate(grgr));
    save_graph("Bredberi", grgr);
    return(0);
}