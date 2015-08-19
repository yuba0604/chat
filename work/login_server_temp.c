/*************************************************************************
	> File Name: login_server_temp.c
	> Note: 
	> Created Time: 2015年08月17日 星期一 10时07分37秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include"../_h/struct.h"
#include"../_h/list.h"
int login_server_temp(user_message user) 
{
    int     rtn;    //返回值
    user_Node *pRead;   //用于从链表中读取数据的指针

    pRead = list;
    while( pRead != NULL ) {
        if(strcmp( pRead->data.username, user.username ) == 0) {
            if(strcmp( pRead->data.password, user.password ) == 0) {
                rtn = 1;    //用户名和密码都正确
            } else {
                rtn = -1;   //用户名存在, 密码不正确
            }
            break;
        } else {
            rtn = -2;   //用户名不存在
        }
        pRead=pRead->next;
    }
    return rtn;
}
int main()
{
    
}
