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
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include"../_h/struct.h"
#include"../_h/list.h"
#define SERV_PORT 4096
#define LISTENQ   10    //队列最长为10

int login_server(user_message user);//登陆函数
int signup_server(user_message user);//注册函数
int whisper_server(user_message user);//私聊函数
int group_server(user_message user);//群聊函数
user_Node *list; 	//链表的头指针
int main(void)
{
    int                 fd;                        //file fd
    int                 sock_fd, client_fd;       //套接字描述符
    struct sockaddr_in  serv_addr;               //服务器地址
    socklen_t           cli_len;                //客户端
    pthread_t           *thread;               //线程指针
    user_message        user;                 //客户端发送的数据包
    user_Node           pNew;                //new pointer


///打开服务器时创建链表从文件中读取数据,便于后续操作--------------------
    //创建链表
    List_Create(list);
    //把数据读入链表
    fd = open("../File/_user.txt",O_RDWR|O_CREAT);
    while(1) {
        pNew = (user_Node)malloc(sizeof(user_Node));
        number = read(fd, pNew->data, sizeof(pNew->data));
        if(number == 0) {
            break;
        }
        List_Insert(list, pNew);
    }
///读取完毕-------------------------------------------------------------
    
    sock_fd = socket( AF_INET, SOCK_STREAM, 0);//创建套接字
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //本程序将处理所有网络请求
    bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
    //转为监听套接字
    listen(sock_fd, LISTENQ);
    cli_len = sizeof(struct sockaddr_in);

    while(1) {
        client_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
        if(client_fd!=0 && client_fd!=1 && client_fd!= 2) {
            pthread_t pid;
            pthread_create(pid,NULL, client_pthread, client_fd);//创建线程处理客户端请求
            pthread_join(pid);//等待线程结束
        }
    }
}
int *client_pthread(client_fd)//处理客户端请求的线程函数
{
    int rtn;    //确定是否退出
    user_message user;
    recv(client_fd, &user, sizeof(user), 0);
    user.client_fd = client_fd;     //把套接字描述符传给结构体,便于传输返回值

    while(1) {
        switch(user.flag) {
            case 1:
            rtn = login_server(user);
            break;

            case 2:
            rtn = signup_server(user);
            break;

            case 3:
            rtn = whisper_server(user);
            break;

            case 4:
            rtn = group_server(user);
            break;
        }
    }
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
    send( user.client_fd, &rtn, sizeof(int), 0 );//发送代表结果的返回值
    return 0;
}

int signup_server(user_message user)  //注册函数
{
    int     rtn;        //返回值
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
        List_Insert(list, pNew_signup);
        //把链表中的数据存入文件
        user_Node *pWrite = list;   //写入文件的指针
        while(pWrite != NULL) {
            write(fd, pWrite->data, sizeof(pWrite->data));
            pWrite = pWrite->next;
        }
    }
    send( user.client_fd, &rtn, sizeof(int), 0 );//发送代表结果的返回值
    return 0;
}

int whisper_server(user_message user)   //聊天函数
{
    while(1) {
        recv(user.client_fd, &user.message, MESSAGE_SIZE, 0);

        if(user.message == "//chat exit") {     //退出聊天
            return 0;
        }
        user_Node *pFind_whisper;
        pFind_whisper = list->next;
        while(pFind_whisper->next != NULL) {
            if(pFind_whisper->data.username == user.object_username) {
                user.object_fd = pFind_whisper->data.client_fd;
                break;
            }
        }
        pFind_whisper = list->next;
        while(pFind_whisper->next != NULL) {
            if(pFind_whisper->data.client_fd == user.client_fd) {
                user.username = pFind_whisper->data.username;
                break;
            }
        }
        send(user.object_fd, &user, MESSAGE_SIZE, 0);
    }
}

int group_server(user_message user)     //群聊函数
{
    while(1) {
        recv(user.client_fd, &user, sizeof(user_message), 0);
        
        if(user.message == "//chat exit") {     //退出聊天
            return 0;
        }
        user_Node *pFind_group;
        pFind_group = list->next;
        while(pFind_group->next != NULL) {
            if(pFind_group->data.status == 1) {
                send(user.client_fd, &user, sizeof(user), 0);
            }
        }
    }
}
