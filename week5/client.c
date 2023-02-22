// Made by Evsey Antonovich, e.antonovich@innopolis.university
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT	 2000
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	const message[MAXLINE];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n;
	socklen_t len;

	while (1) {
		int num = 0;
		scanf("%d", &num);
		sprintf((char *) message, "%d", num);
		sendto(sockfd, (const char *)message, strlen(message),
			   MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			   sizeof(servaddr));

		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *) &servaddr,
					 &len);
		buffer[n] = '\0';
		printf("%s\n", buffer);
		if (strcmp(buffer, "WIN") == 0 || strcmp(buffer, "LOSE") == 0) {
			break;
		}

	}
	close(sockfd);
	return 0;
}
