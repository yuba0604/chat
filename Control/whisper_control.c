/*************************************************************************
	> File Name: whisper_control.c
	> Note: 
	> Created Time: 2015年08月20日 星期四 15时36分30秒
 ************************************************************************/

int whisper_control(char username[  ])
{
    pthread_t pid_send;
    int status;     //记录pthread_join的线程的返回值
    user_message user;
    user.flag = 3;  //3代表私聊
    strncpy(user.object_username, username, MAXSIZE);
    send(client_global_fd, &user, sizeof(user_Node), 0);
    pthread_create(pid_send, NULL, send_pthread, user);
    pthread_join(send_pthread, &status);
}

int *send_pthread(user_Node user)
{
    while(1) {
        gets("%s",&user->data.message); //if gets doesn't work, user scanf
        send(client_global_fd, &user->data, MESSAGE_SIZE, 0);
        if(message=="//chat exit") { //如果执行不成功加入'\n'
            send(client_global_fd, &user->data, MESSAGE_SIZE, 0);
            return;
        }
    }
}
