#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAXLINE 4096
#define PORT 80

int main (void)
{
    int sockfd, n;
    char ip[] = "93.184.216.34";
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("sockfd\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
        printf("inet pton\n");

    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
        printf("connect \n");

    char *message = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
    printf("message: %s\n", message);

    send(sockfd, message, strlen(message), 0);

    n = recv(sockfd, recvline, MAXLINE, 0);
    puts(recvline);
//    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
//    {
//        recvline[n] = 0;
//        if (fputs(recvline, stdout) == EOF)
//            fprintf(stderr, "fputs err");
//    }
//    if (n < 0)
//            fprintf(stderr, "read err");

    exit(0);
}
