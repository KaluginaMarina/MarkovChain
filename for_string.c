#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include "for_string.h"

int read_string (char *str) {
    char s = ' ';
    int n = 0;

    if (str == NULL) {
        return -2;
    }

    while (s != '\n') {
        scanf("%c", &s);
        *(str + n) = s;
        ++n;
        if (n > N) {
            return -1;
        }
    }

    --n;
    *(str + n) = '\0';
    return n;
}


int write_console(char *str) {

    char *cur = str;
    if (str == NULL) {
        return -1;
    }

    while (*cur != '\0') {
        printf("%c", *cur);
        ++cur;
    }
    return 0;
}

int read_file(char *fname, char *str){
    int n = 0, c;
    FILE *f = fopen(fname, "r");
    if (f == NULL){
        return -2;
    }

    while(!feof(f)) {
        c = fgetc(f);
        if (n >= N){
            return -1;
        }
        *(str + n) = (char)c;
        ++n;
    }
    --n;
    *(str + n) = '\0';
    fclose(f);
    return n;
}

int write_file(char *fname, char *str){
    char *cur = str;
    FILE *f = fopen(fname, "w+");
    if (str == NULL) {
        return -1;
    }
    while (*cur != '\0') {
        fprintf(f, "%c", *cur);
        ++cur;
    }
    return(0);
}