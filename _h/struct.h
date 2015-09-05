/*************************************************************************
	> File Name: struct.h
	> Note: 
	> Created Time: 2015年08月17日 星期一 10时17分02秒
 ************************************************************************/

#ifndef _STRUCT_H
#define _STRUCT_H
#define MAXSIZE 15
#define MESSAGE_SIZE 4096
typedef struct {
    int  flag;                 //存储何种操作
    int  status;               //存储是否在线
    int  authority;             //管理员权限
    char username[MAXSIZE];     //存储用户名
    char password[MAXSIZE];     //存储密码
    int  client_fd;             //客户端的套接字描述符
    char object_username[MAXSIZE];//私聊对象的用户名
    int  object_fd;             //私聊对象的套接字描述符
    char message[MESSAGE_SIZE];     //聊天消息
}user_message;     //用户结构体
struct usr_Node{        //链表节点
    user_message    data;
    struct usr_Node *next;
};
typedef struct usr_Node user_Node;
struct fd_A{
    int client_fd;
    int fd;
};
typedef struct fd_A fd_package;
#endif
