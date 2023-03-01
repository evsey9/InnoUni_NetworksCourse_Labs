#include <arpa/inet.h> // inet_addr()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 20000
#define SA struct sockaddr


#define SERVER_IP_ADDR "127.0.0.1"
#define SERVER_PORT 2001
#define SECRET_NUMBER 42

void func(int sockfd)
{
	char buff[MAX];
	int n;
	bzero(buff, sizeof(buff));
	printf("Enter your username: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
		;
	// Send the message to server:
	if(send(sockfd, buff, strlen(buff), 0) < 0){
		printf("Unable to send message\n");
		return;
	}
	bzero(buff, sizeof(buff));
	FILE* svgFile = fopen("image.svg", "w");
	for (int i = 0; i < 3; i++) {
		bzero(buff, sizeof(buff));
		if (recv(sockfd, buff, sizeof(buff), 0) < 0) {
			printf("Error while receiving server's msg\n");
			return;
		}
		fprintf(svgFile, "%s", buff);
	}
	fclose(svgFile);


}

int main()
{
	int sockfd;
	struct sockaddr_in servaddr;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDR);
	servaddr.sin_port = htons(SERVER_PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);
	printf("Message (probably) received!\n");
	// close the socket
	close(sockfd);
}