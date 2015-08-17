/*************************************************************************
	> File Name: login_model.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 15时22分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include"../Control/control.h"
#include"../_h/struct.h" //引入结构体和MAXSIZE
int login_signup_model(char username[  ], char password[  ], int flag)
{
    user_message user;
    strncpy(user.username, username, MAXSIZE);
    strncpy(user.password, password, MAXSIZE);
    user.flag = flag;

    return login_signup_control(user);
}
