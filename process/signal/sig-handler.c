    #include "apue.h"
    #include "sys/wait.h"

    void sig_int(int signo){
        printf("interrupt sino: %d\n", signo);
    }
    int main(void){
        char buf[MAXLINE];
        int status;
        pid_t pid;
        if (signal(SIGINT, sig_int) == SIG_ERR){
            err_sys("signal error");
        }
        while(fgets(buf,MAXLINE, stdin)!=NULL){
            if(buf[strlen(buf)-1]=='\n'){
                buf[strlen(buf)-1]=0;
            }
            if((pid=fork())<0){
                err_sys("fork error");
            }else if(pid==0){
                execlp(buf,buf, NULL);
                err_ret("couldn't exec: %s", buf);
                exit(127);
            }
            if((pid=waitpid(pid, &status, 0))<0){
                err_sys("waitpid error");
            }
            printf("%% ");
        }
        exit(0);
    }
