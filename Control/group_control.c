/*************************************************************************
	> File Name: group_control.c
	> Note: 
	> Created Time: 2015年09月04日 星期五 15时05分04秒
 ************************************************************************/

int group_control()
{
    pthread_t pid_send;
    int status;     //记录pthread_join的线程的返回值
    user_message user;
    user.flag = 4;  //4代表群聊
    user.status = 1;    //1代表在线
    send(client_global_fd, &user, sizeof(user_Node), 0);
    pthread_create(pid_send, NULL, send_pthread, NULL);//send_pthread在whisper_control.c中定义
    pthread_join(send_pthread, &status);
}
