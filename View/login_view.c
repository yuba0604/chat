/*************************************************************************
	> File Name: login_view.c
	> Note: 
	> Created Time: 2015年08月13日 星期四 15时41分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include"view.h"
#include"../Model/model.h"
#include"../_h/format.h"

char getch()
///自建getch函数, 用来以'*'显示密码
{
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

int get_password(char password[  ])
///get_password是输入密码的函数, 密码会赋给password, 输入的密码以*显示, 控制输入格式
{
    int     i = 0;  //i用来统计输入字符个数
    printf("密码(小于14位):");
    for(;i<14;i++){
        password[i] = getch();
        if(password[i] == '\n') {
            break;
        }
        if(password[i] == 127) { //键入删除键
            if(i == 0) {
                i--;
                continue;
            }
            printf("\b");
            printf(" ");
            printf("\b");
            i -= 2;
            continue;
        }
        if( i >= 14 ) {
            NEWLINE
            PADDING_30 printf("密码过长\n");
            return -1;
        }
        printf("*");
    }
    return 0;
}
int get_username(char username[  ])
///get_username是输入用户名的函数, 用户名会赋给username, 控制输入格式
{
    int     count = 0;//计算输入字符数
    printf("用户名(小于14位):");
    gets(username);
    if((count = sizeof(username)) > 15) {
        NEWLINE
        PADDING_30 printf("用户名过长\n");
        sleep(1);
        return -1;
    }
    return count-1;
}
int login_view(void)
///login_view是登陆界面函数
{
    int  rtn;
    char username[15] = "";
    char password[15] = "";
    system("clear");
    printf(" #             ############  ###########  #  ###       #\n");
    printf(" #             #          #  #            #  #  #      #\n");
    printf(" #             #          #  #            #  #   #     #\n");
    printf(" #             #          #  #            #  #    #    #\n");
    printf(" #             #          #  #    ######  #  #     #   #\n");
    printf(" #             #          #  #         #  #  #      #  #\n");
    printf(" #             #          #  #         #  #  #       # #\n");
    printf(" #             #          #  #         #  #  #        ##\n");
    printf(" ############  ############  ###########  #  #         #\n");
    PADDING_80
    NEWLINE
    NEWLINE
    if(get_username(username) == -1) {  //获得用户名
        return -1;
    }
    NEWLINE
    if(get_password(password) == -1) {  //获得密码
        return -1;
    }
    rtn = login_signup_model(username, password, 1); //1代表登陆操作
    if( rtn == 1 ) {//rtn == 1代表用户名和密码都正确
        NEWLINE;
        printf("登陆成功\n");
    } else if( rtn == -1 ) {//rtn == -1代表用户名存在, 密码不正确
        NEWLINE;
        PADDING_30 printf("登陆失败\n");
    } else if( rtn == -2 ) {//rtn == -2代表用户名不存在
        NEWLINE;
        PADDING_30 printf("用户不存在\n");
    }
    sleep(5);
    return 0;
}
