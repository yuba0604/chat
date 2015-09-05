/*************************************************************************
	> File Name: choose_view.c
	> Note: 
	> Created Time: 2015年08月20日 星期四 10时22分11秒
 ************************************************************************/


int choose_view(void)
{
    int flag;   
    system("clear");
    printf(" ##        ##        ##        ##        ##        ##       \n");
    printf("   ##        ##        ##        ##        ##        ##     \n");
    printf("     ##        ##        ##        ##        ##        ##   \n");
    printf("       ##        ##        ##        ##        ##        ## \n");
    printf("         #         #         #         #         #         #\n");
    printf("       ##        ##        ##        ##        ##        ## \n");
    printf("     ##        ##        ##        ##        ##        ##   \n");
    printf("   ##        ##        ##        ##        ##        ##     \n");
    printf(" ##        ##        ##        ##        ##        ##       \n");
    PADDING_80
    NEWLINE
    NEWLINE
    printf("当前在线用户:\n");
    online_control();
    PADDING_30 printf("1.私聊\n");
    NEWLINE
    PADDING_30 printf("2.群聊\n");
    NEWLINE
    PADDING_30 printf("3.退出\n");
    NEWLINE
    scanf("%d",flag);
    if( flag == 1 ) {
        whisper_view();
    } else if(flag == 2) {
        group_view();
    } else if(flag == 3) {
        return;
    }else {
        PADDING_30 printf("输入不合法\n");
        sleep(1);
    }
}
