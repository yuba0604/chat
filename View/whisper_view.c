/*************************************************************************
	> File Name: whisper_view.c
	> Note: 
	> Created Time: 2015年08月20日 星期四 09时44分01秒
 ************************************************************************/

int *recv_pthread_view()
{
    user_Node user;
    while(1) {
        recv(client_global_fd, &user, sizeof(user_Node), 0);
        printf("|%80s|\n",user.username);
        printf("%80s\n",user.message);
    }
}
int whisper_view(void)
{
    pthread_create();
    char username[MAXSIZE];
    system("clear");
    printf(" #   ###   #  #         #  #  ###########  ###########  ###########  ###########\n");
    printf(" #   # #   #  #         #  #  #            #         #  #            #         #\n");
    printf(" #   # #   #  #         #  #  #            #         #  #            #         #\n");
    printf(" #   # #   #  #         #  #  #            #         #  #            #         #\n");
    printf(" #   # #   #  ###########  #  ###########  ###########  ###########  ###########\n");
    printf(" #   # #   #  #         #  #            #  #            #            ###        \n");
    printf(" #   # #   #  #         #  #            #  #            #            #  ##      \n");
    printf(" #   # #   #  #         #  #            #  #            #            #    ##    \n");
    printf(" ##### #####  #         #  #  ###########  #            ###########  #      ####\n");
    PADDING_80
    NEWLINE
    printf("请输入对方用户名:");
    scanf("%s",username);
    printf("输入'//chat exit'以退出聊天\n");
    whisper_control(char username[  ]);
}
