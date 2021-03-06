/*************************************************************************
	> File Name: login_control.c
	> Note: 
	> Created Time: 2015年08月14日 星期五 15时16分33秒
 ************************************************************************/
int client_global_fd;//全局的套接字描述符
int login_signup_control(user_message user)
{
    int     conn_fd;
    int     recv_buf;       //接收函数的返回值
    struct sockaddr_in serv_addr;    //定义套接字地址
    memset(&sock, 0, sizeof(struct sockaddr_in));   //清空地址所在内存区域
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(SERV_PORT);  //设置端口号
    serv_addr.sin_addr.s_addr = inet_addr("192.168.20.139");     //设置地址

    
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);//创建一个TCP套接字
    client_global_fd = conn_fd;     //把套接字描述符变成全局的
    user.sock_fd = conn_fd;     //把套接字描述符存进结构体
    connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));     //在conn_fd上创建一个连接
    send(conn_fd, &user, sizeof(user_message), 0);           //发送数据
    recv(conn_fd, &recv_buf, sizeof(recv_buf), 0);
    
    close(conn_fd);
    return recv_buf;
}
