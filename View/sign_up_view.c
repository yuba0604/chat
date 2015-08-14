/*************************************************************************
	> File Name: sign_up_view.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 08时40分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"view.h"
#include"../Model/model.h"
int get_password_again(char password_again[  ])
///get_password_again是再次输入密码的函数, 密码会赋给password, 密码以*显示
///输入的密码以*显示, 控制输入格式
{
    int     i;  //i用来统计输入字符个数
    printf("再次输入密码(小于14位):");
    for(i=0;i<15;i++){
        password_again[i] = getch();
        if(password_again[i] == '\n') {
            break;
        }
        if(password_again[i] == 127) { //键入删除键
            printf("\b");
            printf(" ");
            printf("\b");
            i -= 2;
            continue;
        }
        if( i >= 14 ) {
            NEWLINE
            printf("密码过长\n");
            return -1;
        }
        printf("*");
    }
    return 0;
}
int check_password(char password[  ], char password_again[  ])
///check_password用来检查两次输入密码是否一致,password是第一次输入的密码, 
///password_again是第二次的, 控制输入格式
{
    if(( strcmp(password,password_again) ) != 0) {
        NEWLINE
        printf("两次密码输入不一致\n");
        return -1;
    }
    return 0;
}
int sign_up_view(void)
///sign_up_view是注册界面函数
{
    char username[15] = "";         //存放用户名
    char password[15] = "";         //存放第一次密码
    char password_again[15] = "";   //存放第二次密码
    system("clear");                //清屏
    printf(" ###########  #  ###########  ###       #  #         #  ###########\n");
    printf(" #            #  #            #  #      #  #         #  #         #\n");
    printf(" #            #  #            #   #     #  #         #  #         #\n");
    printf(" #            #  #            #    #    #  #         #  #         #\n");
    printf(" ###########  #  #    ######  #     #   #  #         #  ###########\n");
    printf("           #  #  #         #  #      #  #  #         #  #          \n");
    printf("           #  #  #         #  #       # #  #         #  #          \n");
    printf("           #  #  #         #  #        ##  #         #  #          \n");
    printf(" ###########  #  ###########  #         #  ###########  #          \n");
    PADDING_80
    NEWLINE
    NEWLINE
    if(get_username(username) == -1) {  //输入用户名, 在login_view.c中定义
        return -1;
    }
    NEWLINE
    if(get_password(password) == -1) {  //输入第一次密码, 在login_view.c中定义
        return -1;
    }
    NEWLINE
    if(get_password_again(password_again) == -1) {  //输入第二次密码
        return -1;
    }
    NEWLINE
    if(check_password(password, password_again) == -1) { //检查两次输入是否一致
        sleep(1);
        return -1;
    }

    //sign_up_model(username, password);
    NEWLINE;
    PADDING_30 printf("注册成功\n");
    sleep(1);
    return 0;
}
