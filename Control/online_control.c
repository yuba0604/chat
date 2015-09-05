/*************************************************************************
	> File Name: online_control.c
	> Note: 
	> Created Time: 2015年09月04日 星期五 21时42分25秒
 ************************************************************************/

int online_control()
{
    user_message user;
    int rtn = 1;
    user.flag = 5;//5代表查询在线用户
    send(client_global_fd, &user, sizeof(user_Node), 0);
    while(1) {
        rtn = recv(client_global_fd, &user, sizeof(user_Node), 0);
        if(rtn == 0 || rtn == -1) {
            break;
        }
        printf("%s\n",user.username);
    }
}
