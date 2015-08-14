/*************************************************************************
	> File Name: Server.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 20时44分40秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define SERV_PORT 4096
#define LISTENQ   10

void server(void)
{
    int                 sock_fd;
    struct sockaddr_in  serv_addr;

    sock_fd = socket( AF_INET, SOCK_STREAM, 0);
    
    memset( &serv_addr, 0, sizeof(struct sockaddr_in) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));

    listen(sock_fd, LISTENQ);
}
