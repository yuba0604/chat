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
int signup_server_temp(user_message user, user_Node *list)
{
    user_Node *p;
    p = (user_Node *)malloc( sizeof(user_Node) );
    strcpy( p->data.username, user.username );
    strcpy( p->data.password, user.password );
    List_AddTail( list, *p);
}
int main()
{
    
}
