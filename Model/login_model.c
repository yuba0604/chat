/*************************************************************************
	> File Name: login_model.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 15时22分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include"../Control/control.h"
int login_model(char username[  ], char password[  ])
{
    user_message package;
    strncpy(package.username, username, MAXSIZE);
    strncpy(package.password, password, MAXSIZE);

    return login_control(package);
}
