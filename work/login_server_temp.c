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
    int     fd;     //文件描述符
    int     rtn;    //返回值
    int     number; //获取read()的返回值, 判断是否读到文件尾部
    user_Node   buf;//存放从文件中读取的数据

    fd = open("../File/_user.txt", RDONLY);
    number = 2;     //使number进入循环
    while( number != 0 ) {
        if( number = read(fd, &buf.data, sizeof(user_Node)) ) {     //读取文件
            if( strcmp( user.username, buf.data.username ) == 0 ) {     //判断用户名是否一致
                if( strcmp( user.password, buf.data.password ) == 0 ) { //判断密码是否一致
                    rtn = 1;                //用户名和密码都正确
                } else {
                    rtn = -1;               //用户名存在, 密码不正确
                }
            } else {
                rtn = -2;               //用户名不存在
            }
        } /*else {
            //读文件失败, 写入错误日志
        }*/
    }
    close(fd);
    return rtn;
}
int main()
{
    
}
