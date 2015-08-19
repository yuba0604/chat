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

user_Node *list; 	//链表的头指针
int main(void)
{
    int                 sock_fd;                //套接字描述符
    struct sockaddr_in  cli_addr, serv_addr;    //客户端地址 服务器地址
    socklen_t           cli_len;                //客户端
    pthread_t           *thread;                //线程指针
    int                 i;
    user_message        user;                //客户端发送的数据包
    sock_fd = socket( AF_INET, SOCK_STREAM, 0);
///打开服务器时创建链表从文件中读取数据,便于后续操作----------------------
    //创建链表
    List_Create();
    //把数据读入链表
    fd = open("../File/_user.txt",O_RDWR|O_CREAT);
    while(1) {
        pNew = (user_Node)malloc(sizeof(user_Node));
        number = read(fd, pNew->data, sizeof(pNew->data));
        if(number == 0) {
            break;
        }
        List_Insert(pNew);
    }
///读取完毕---------------------------------------------------------

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
///关闭服务器之前把修改过的链表存入文件---------------------------------
    //把链表中的数据存入文件
    user_Node *pWrite = list;   //写入文件的指针
    while(pWrite != NULL) {
        write(fd, pWrite->data, sizeof(pWrite->data));
        pWrite = pWrite->Next;
    }
///写入完毕---------------------------------------------------------
}
int login_server(user_message user) //登陆函数
{
    int     rtn;    //返回值
    user_Node *pRead_login;   //用于从链表中读取数据的指针

    pRead_login = list;
    while( pRead != NULL ) {
        if(strcmp( pRead_login->data.username, user.username ) == 0) {
            if(strcmp( pRead_login->data.password, user.password ) == 0) {
                rtn = 1;    //用户名和密码都正确
                pRead_login->data.status = 1;   //表示在线
            } else {
                rtn = -1;   //用户名存在, 密码不正确
            }
            break;
        } else {
            rtn = -2;   //用户名不存在
        }
        pRead_login=pRead_login->next;
    }
    return rtn;
}
int signup_server(user_message user)  //注册函数
{
    user_Node *pRead_signup;    //读链表的指针
    
    pRead_signup = list;
    while(pRead_signup != NULL) {
        if(strcmp( pRead_signup->data.username, user.username ) == 0) {
            rtn = -3;   //用户名已存在!不能注册
            break;
        } else {
            rtn = 2;    //用户名可用
        }
    }
    if( rtn == 2 ) {
        user_Node *pNew_signup;
        pNew_signup = (user_Node)malloc(sizeof(user_Node));
        List_Insert(pNew_signup);
    }
    return rtn;
}
