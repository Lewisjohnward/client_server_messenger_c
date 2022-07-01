#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define PORT 80

int main (int argc, char **argv)
{
    int sockfd, n;
    char ip[] = "142.250.200.14";
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

//    if (argc != 2)
//    {
//        return 1;
//    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("sockfd\n");

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
        printf("inet pton\n");

    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
        printf("connect \n");

    printf("hello\n");

    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            fprintf(stderr, "fputs err");
    }
    if (n < 0)
            fprintf(stderr, "read err");

    exit(0);
}

