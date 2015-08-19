/*************************************************************************
	> File Name: sign_up_server_temp.c
	> Note: 
	> Created Time: 2015年08月17日 星期一 16时14分20秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include"../_h/struct.h"
#include"../_h/list.h"
int signup_server_temp(user_message user)
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
int main()
{
    
}
