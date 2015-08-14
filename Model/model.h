/*************************************************************************
	> File Name: model.h
	> Note: 
	> Created Time: 2015年08月14日 星期五 15时30分19秒
 ************************************************************************/

#ifndef _MODEL_H
#define _MODEL_H
#define MAXSIZE 15
typedef struct {
    char username[MAXSIZE];     //存储用户名
    char passworr[MAXSIZE];     //存储密码
    int  address[50];           //存储主机地址
    int  flags;                 //存储何种操作
} user_message;
int login_model(char username[  ], char password[  ]);
int sign_up_model(char username[  ], char password[  ]);
#endif
