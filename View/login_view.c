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
//#include"../Model/model.h"

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
    int     i = 1;  //i用来统计输入字符个数
    printf("密码(小于14位):");
    while(1) {
        password[i] = getch();
        if(password[i] == '\n') {
            break;
        }
        printf("*");
        i++;
        if( i >= 14 ) {
            printf("\n密码过长\n");
            return -1;
        }
    }
    return 0;
}
int get_username(char username[  ])
///get_username是输入用户名的函数, 用户名会赋给username, 控制输入格式
{
    int     count = 0;//计算输入字符数
    int     ch_check;   //ch_check用来检测输入字符是否合法
    printf("用户名(小于14位, 只能使用数字或字母):");
    gets(username);
    if((count = sizeof(username)) > 15) {
        printf("用户名过长\n");
        sleep(1);
        return -1;
    }
    return count-1;
}
int login_view(void)
{
    char username[15] = "";
    char password[15] = "";
    system("clear");
    printf("#######  ########  #####       #     \n");
    printf("  #   #  #    #    #   #    #######  \n");
    printf("   ###    ## #     #  #        #     \n");
    printf("  ## ###### ##     #   # ############\n");
    printf(" #   #    #   ##   #    #      #     \n");
    printf("#    ######     #  #####       #     \n");
    printf("    #      #       #      #    #   # \n");
    printf("     #    #        #      #    #   # \n");
    printf(" ##############    #      ########## \n");
    PADDING_80
    NEWLINE
    NEWLINE
    if(get_username(username) == -1) {
        return -1;
    }
    NEWLINE
    if(get_password(password) == -1) {
        return -1;
    }
    //login_model(username, password);
    NEWLINE;
    PADDING_30 printf("登陆成功\n");
    sleep(1);
    return 0;
}
