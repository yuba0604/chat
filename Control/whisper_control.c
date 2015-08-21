/*************************************************************************
	> File Name: whisper_control.c
	> Note: 
	> Created Time: 2015年08月20日 星期四 15时36分30秒
 ************************************************************************/

int whisper_control(char username[  ])
{
    send(client_global_fd,&username,MAXSIZE,0);

}
