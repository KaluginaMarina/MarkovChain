#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindless_machine.h"

int main() {

    char* str = (char*)malloc(50 * sizeof(char));
    read_string(str);

    str = str_replace_punct(str);

    printf("%s", str);

    return(0);
}