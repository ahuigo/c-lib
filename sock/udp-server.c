/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socklib.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr,cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	printf("Accepting connections: localhost:%d\n", SERV_PORT);
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i,n;
	socklen_t cliaddr_len;
	while(1){
		cliaddr_len = sizeof(cliaddr);
		n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if(n == -1)
			perr_exit("recvfrom error");
		printf("Received from %s as port %d \n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
		for(i=0;i<n;i++){
			buf[i] = toupper(buf[i]);
		}
		sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, cliaddr_len);
	}
}

