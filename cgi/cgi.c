/**
 * @author mengkang.net https://segmentfault.com/a/1190000009863108
 * curl 'http://localhost:9003/c-shell?id=1'
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#ifndef SIGCLD
#   define SIGCLD SIGCHLD
#endif
    
#define SERV_PORT 9003
 
char* str_join(char *str1, char *str2);
char* html_response(char *res, char *buf);
   
int main(void)
{
    int lfd, cfd;
    struct sockaddr_in serv_addr,clin_addr;
    socklen_t clin_len;
    char buf[1024],web_result[1024];
    FILE *cin;
  
    if((lfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("create socket failed");
        exit(1);
    }
      
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);
  
    if(bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind error");
        exit(1);
    }
  
    if(listen(lfd, 128) == -1)
    {
        perror("listen error");
        exit(1);
    }
     
    signal(SIGCLD,SIG_IGN);
   
    while(1)
    {
        clin_len = sizeof(clin_addr);
        if ((cfd = accept(lfd, (struct sockaddr *)&clin_addr, &clin_len)) == -1)
        {
            perror("接收错误\n");
            continue;
        }
 
        cin = fdopen(cfd, "r");
        //c-io-buffer.md 无缓冲
        setbuf(cin, (char *)0);
        // 或setbuf(cin, NULL);

        fgets(buf,1024,cin); //读取第一行
        printf("header:%s\n", buf);
 
        //============================ cgi 环境变量设置演示 ============================
         
        // 例如 "GET /c-shell?id=1 HTTP/1.1";
 
        char *delim = " ";
        char *p;
        char *method, *filename, *query_string;
        char *query_string_pre = "QUERY=";
 
        method = strtok(buf,delim);         // GET
        p = strtok(NULL,delim);             // /c-shell?id=1 
        filename = strtok(p,"?");           // /c-shell
         
        if (strcmp(filename,"/favicon.ico") == 0) {
            continue;
        }
 
        query_string = strtok(NULL,"?");    // id=1
        putenv(str_join(query_string_pre,query_string));
 
        //============================ cgi 环境变量设置演示 ============================
 
        int pid = fork();
  
        if (pid > 0)
        {
            close(cfd);
        }
        else if (pid == 0)
        {
            close(lfd);
            //FILE *stream = popen("./c-shell","r");
            FILE *stream = popen("echo $QUERY","r");
            fread(buf,sizeof(char),sizeof(buf),stream);
            html_response(web_result,buf);
            write(cfd,web_result,sizeof(web_result));
            pclose(stream);
            close(cfd);
            exit(0);
        }
        else
        {
            perror("fork error");
            exit(1);
        }
    }
   
    close(lfd);
       
    return 0;
}
 
char* str_join(char *str1, char *str2)
{
    char *result = malloc(strlen(str1)+strlen(str2)+1);
    if (result == NULL) exit (1);
    strcpy(result, str1);
    strcat(result, str2);
   
    return result;
}
 
char* html_response(char *res, char *buf)
{
    char *html_response_template = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\nContent-Length: %d\r\nServer: mengkang\r\n\r\n%s";
 
    sprintf(res,html_response_template,strlen(buf),buf);
     
    return res;
}
