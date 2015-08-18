/*************************************************************************
	> File Name: Server.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 20时44分40秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>
//#include<pthread.h>
#include"../_h/struct.h"
#define SERV_PORT 4096
#define LISTENQ   10    //队列最长为10
int main(void)
{
    int                 sock_fd;                //套接字描述符
    struct sockaddr_in  cli_addr, serv_addr;    //客户端地址 服务器地址
    socklen_t           cli_len;                //客户端
    pthread_t           *thread;                //线程指针
    int                 i;
    user_message        user;                //客户端发送的数据包
    sock_fd = socket( AF_INET, SOCK_STREAM, 0);
    
    memset( &serv_addr, 0, sizeof(struct sockaddr_in) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));

    listen(sock_fd, LISTENQ);

    cli_len = sizeof(struct sockaddr_in);
    while(1) {
        sock_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
        printf("accept a client, ip:%s\n", inet_ntoa(cli_addr.sin_addr));
        //pthread_create()
        recv(sock_fd, &user, sizeof(user_message), 0);
        for(i=0;i<MAXSIZE; i++){
            printf("%c",user.username[i]);
        }
        printf("\n");
        break;
    }
}
int login_server(user_message user) //登陆函数
{
    int     fd;     //文件描述符
    int     rtn;    //返回值
    int     number; //获取read()的返回值, 判断是否读到文件尾部
    user_Node   buf;//存放从文件中读取的数据

    fd = open("../File/_user.txt", RDONLY);
    number = 2;     //使number进入循环
    while( number != 0 ) {
        if( number = read(fd, &buf.data, sizeof(user_Node)) ) {     //读取文件
            if( strcmp( user.username, buf.data.username ) == 0 ) {     //判断用户名是否一致
                if( strcmp( user.password, buf.data.password ) == 0 ) { //判断密码是否一致
                    rtn = 1;                //用户名和密码都正确
                } else {
                    rtn = -1;               //用户名存在, 密码不正确
                }
            } else {
                rtn = -2;               //用户名不存在
            }
        } /*else {
            //读文件失败, 写入错误日志
        }*/
    }
    close(fd);
    return rtn;
}
int signup_server(user_message user, user_Node *list) //注册函数
{
    int rtn;    //返回值
    user_Node *p;
    p = (user_Node *)malloc( sizeof(user_Node) );
    strcpy( p->data.username, user.username );
    strcpy( p->data.password, user.password );
    List_AddTail( list, *p);
    return 2;    //注册成功
}
