// gcc getputc.c -lapue
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

#include "apue.h"

int main(void){
    int c;
    while ((c=getc(stdin)) !=EOF)
        if (putc(c, stdout)== EOF)
            err_sys("output error");
    if(ferror(stdin))
        err_sys("input error");

    exit(0);
}
