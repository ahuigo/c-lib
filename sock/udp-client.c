/*client.c*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*
#include "socklib.h"
*/

#define MAXLINE 80
#define SERV_PORT 8000

void perr_exit(const char *s){
        perror(s);
        exit(1);
}


void Bind(int fd, const struct sockaddr *sa, socklen_t salen) {
    if (bind(fd, sa, salen) < 0)
        perr_exit("bind error");
}

int main(int argc, char **argv) {
	int servfd;
	servfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in servaddr;
	socklen_t servaddr_len;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	int n;
	char buf[MAXLINE];
	while(fgets(buf, MAXLINE, stdin)){
		servaddr_len = sizeof(servaddr);
		n = sendto(servfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, servaddr_len);
		if(n<0){
			perr_exit("sendto error");
		}
		n = recvfrom(servfd, buf, MAXLINE, 0, NULL, 0);
		if(n<0){
			perr_exit("sendto error");
		}
		write(1, buf, n);
	}
	return 0;
}

