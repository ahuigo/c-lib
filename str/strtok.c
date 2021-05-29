#include "apue.h"
#include "errno.h"

int main(int argc, char *argv[]){
    char *str = "a:;22:;33";
    char *token = strtok(str, ":;");
	printf("%s\n", token);
	while ( (token = strtok(NULL, ":;")) != NULL)
		printf("%s\n", token);

}
