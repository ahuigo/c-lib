#include "apue.h"
#include "errno.h"

int main(int argc, char *argv[]){
    execlp("/usr/local/bin/echoraw", "arg0", "arg1",NULL);
    printf("not output\n");
    exit(0);
}
