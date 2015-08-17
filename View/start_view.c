/*************************************************************************
	> File Name: start_view.c
	> Note: 欢迎界面
	> Created Time: 2015年08月13日 星期四 14时27分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"view.h"
#include"../_h/format.h"


///进入程序的第一级菜单
int main(void)
{
    
    int ch_first;   //ch_first用来存储选项
    while(1) {
        ch_first = 0;
       // fflush(stderr);
        setbuf(stdin, NULL);
        system("clear");
        printf(" ###########  #         #     #####     ###########\n");
        printf(" #            #         #    #     #         #     \n");
        printf(" #            #         #   #       #        #     \n");
        printf(" #            #         #  #         #       #     \n");
        printf(" #            ###########  ###########       #     \n");
        printf(" #            #         #  #         #       #     \n");
        printf(" #            #         #  #         #       #     \n");
        printf(" #            #         #  #         #       #     \n");
        printf(" ###########  #         #  #         #       #     \n");
        PADDING_80
        NEWLINE
        NEWLINE
        PADDING_30 printf("[1].登陆\n");
        PADDING_30 printf("[2].注册\n");
        PADDING_30 printf("[3].退出\n");
        printf("==========\n");
        printf("请选择:\n");
        setbuf(stdin,NULL);
        scanf("%d",&ch_first);
        setbuf(stdin, NULL);
        switch(ch_first) {
            case 1:
                login_view();   //登陆界面函数
                break;
            case 2:
                signup_view(); //注册界面函数
                break;
            case 3:
                return 0;       //退出程序
            default:
                printf("\n输入有误, 请重新输入\n");
                break;
        }
    }
}
