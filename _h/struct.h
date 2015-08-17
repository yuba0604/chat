/*************************************************************************
	> File Name: struct.h
	> Note: 
	> Created Time: 2015年08月17日 星期一 10时17分02秒
 ************************************************************************/

#ifndef _STRUCT_H
#define _STRUCT_H
#define MAXSIZE 15

typedef struct {
    int  flag;                 //存储何种操作
    int  sock_fd;               //存储套接字描述符, 方便创建线程时传参
    char username[MAXSIZE];     //存储用户名
    char password[MAXSIZE];     //存储密码
} user_message;     //用来登陆, 注册的结构体
struct usr_Node{
    user_message    data;
    struct usr_Node *next;
    struct usr_Node *prev;
};
typedef struct usr_Node user_Node;
#endif
