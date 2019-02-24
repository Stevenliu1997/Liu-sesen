#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define Buffer_Length 1024
#define Serve_Port 6666 	//define the port for the two to connect
#define LISTENQ 10		//define the biggest number of clients
#define AMOUNT 10

int main(int argc,char* argv[]){
    struct sockaddr_in server_addr,client_addr;
    int listenfd,connfd;
    socklen_t client_addr_len = sizeof(struct sockaddr);
    char buf[Buffer_Length];
    //define the space for message
    int n;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    //to get the socket
    if (listenfd == -1)
    {
        perror("created failed");
        exit(1);
    }
    //failed to get socket
    bzero(&server_addr,sizeof(server_addr));
    //set server_addr to 0
    server_addr.sin_family = AF_INET;
    //set domain with ipv4 protocals
    server_addr.sin_port = htons(Serve_Port);
    //set the server port
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //set the ip address
    if (bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
    {
        perror("");
        exit(1);
    }
    // try to bind the ip address and port to the socket.if failed,return with -1
    listen(listenfd,LISTENQ);
    //set the biggest number of connection, and listen to the connection

    fd_set allset,rset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    int maxfd = listenfd;
    while (1) {
        rset = allset;
        select(maxfd+1, &rset, NULL, NULL, NULL);
        // todo1
        for (int i = 0;i < AMOUNT; i++) {
            if (FD_ISSET(listenfd,&rset)) {
                connfd = accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len);
                maxfd = connfd > maxfd?connfd:listenfd;
                FD_SET(connfd, &allset);
            }
        }
        // first
        if (FD_ISSET(connfd, &rset)) {
            memset(buf, 0, Buffer_Length);
            n = recv(connfd, buf, Buffer_Length, 0);
            if (n >0) {
                buf[n] = '\0';
                printf("%s\n",buf);
                if(strcmp(buf,"exit") == 0){
                    if(close(listenfd) == -1)
                    {
                        perror("fail to close");
                        exit(1);
                    }
                    puts("tcp server is closed\n");
                }
                printf("input the reply");
                gets(buf);
                if(strcmp(buf,"exit") == 0){
                    if(close(listenfd) == -1)
                    {
                        perror("fail to close");
                        exit(1);
                    }
                    puts("tcp server is closed\n");
                }
                n = send(connfd, buf, strlen(buf),0);
                if(n == -1){
                    perror("failed to reply");
                    exit(1);
                }
            } else {
                close(connfd);
            }
        }
        // second
    }
    return EXIT_SUCCESS;
}

