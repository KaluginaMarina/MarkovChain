#include <stdio.h>
#include <stdlib.h>
#include "for_string.h"

int main() {
    char str[15];
    read_file("test.txt", str);
    write_console(str);
    write_file("test1.txt", str);
    return(0);
}