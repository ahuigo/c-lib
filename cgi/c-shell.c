/**
 * c shell
 */
#include <stdio.h>
#include <stdlib.h>
 
char* str_join(char *str1, char *str2);
char* html_response(char *res, char *buf);
   
int main(void) {
    char buf[1024];
    putenv("QUERY=id=1");
    //suprocess: sscanf(getenv("QUERY"),"id=%d", &id)
    FILE *stream = popen("python3 -c 'import os;print(os.getenv(\"QUERY\"))'","r");
    fread(buf,sizeof(char),sizeof(buf),stream);
    printf("%s", buf);
    return 0;
}
