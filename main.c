#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#include<termios.h>
#include"./View/view.h"
#include"./_h/format.h"
#include"./_h/struct.h"

#define SERV_PORT 4096
int client_global_fd;//全局的套接字描述符


char getch();
int get_password(char password[  ]);
int get_username(char username[  ]);
int login_view(void);
int get_password_again(char password_again[  ]);
int check_password(char password[  ], char password_again[  ]);
int signup_view(void);
int choose_view(void);
int whisper_view(void);
int group_view();
int login_signup_model(char username[  ], char password[  ], int flag);
int login_signup_control(user_message user);
int whisper_control(char username[  ]);
int group_control();
int online_control();

int *send_pthread(void *ur)
{
    user_Node* user = (user_Node*)ur;
    while(1) {
        gets(user->data.message); //if gets doesn't work, user scanf
        send(client_global_fd, &user->data, MESSAGE_SIZE, 0);
        if(user->data.message=="//chat exit") { //如果执行不成功加入'\n'
            send(client_global_fd, &user->data, MESSAGE_SIZE, 0);
            return 0;
        }
    }
}
int *recv_pthread_view()
{
    user_message user;
    while(1) {
        recv(client_global_fd, &user, sizeof(user_Node), 0);
        printf("|%80s|\n",user.username);
        printf("%80s\n",user.message);
    }
}

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
            system("clear");
            return 0;       //退出程序
            default:
            printf("\n输入有误, 请重新输入\n");
            break;
        }
    }
}
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
    if((count = sizeof(*username)) > 15) {
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
                    choose_view();     //跳转到聊天界面
                   } else if( rtn == -1 ) {//rtn == -1代表用户名存在, 密码不正确
                                           NEWLINE;
                                           PADDING_30 printf("登陆失败\n");
                                           sleep(5);
                                          } else if( rtn == -2 ) {//rtn == -2代表用户名不存在
                                                                  NEWLINE;
                                                                  PADDING_30 printf("用户不存在\n");
                                                                  sleep(5);
                                                                 }
    return 0;
}
int get_password_again(char password_again[  ])
///get_password_again是再次输入密码的函数, 密码会赋给password, 密码以*显示
///输入的密码以*显示, 控制输入格式
{
    int     i;  //i用来统计输入字符个数
    printf("再次输入密码(小于14位):");
    for(i=0;i<15;i++){
        password_again[i] = getch();
        if(password_again[i] == '\n') {
            break;
        }
        if(password_again[i] == 127) { //键入删除键
                                      printf("\b");
                                      printf(" ");
                                      printf("\b");
                                      i -= 2;
                                      continue;
                                     }
        if( i >= 14 ) {
            NEWLINE
            printf("密码过长\n");
            return -1;
        }
        printf("*");
    }
    return 0;
}
int check_password(char password[  ], char password_again[  ])
///check_password用来检查两次输入密码是否一致,password是第一次输入的密码, 
///password_again是第二次的, 控制输入格式
{
    if(( strcmp(password,password_again) ) != 0) {
        NEWLINE
        printf("两次密码输入不一致\n");
        return -1;
    }
    return 0;
}
int signup_view(void)
///signup_view是注册界面函数
{
    char username[15] = "";         //存放用户名
    char password[15] = "";         //存放第一次密码
    char password_again[15] = "";   //存放第二次密码
    system("clear");                //清屏
    printf(" ###########  #  ###########  ###       #  #         #  ###########\n");
    printf(" #            #  #            #  #      #  #         #  #         #\n");
    printf(" #            #  #            #   #     #  #         #  #         #\n");
    printf(" #            #  #            #    #    #  #         #  #         #\n");
    printf(" ###########  #  #    ######  #     #   #  #         #  ###########\n");
    printf("           #  #  #         #  #      #  #  #         #  #          \n");
    printf("           #  #  #         #  #       # #  #         #  #          \n");
    printf("           #  #  #         #  #        ##  #         #  #          \n");
    printf(" ###########  #  ###########  #         #  ###########  #          \n");
    PADDING_80
    NEWLINE
    NEWLINE
    if(get_username(username) == -1) {  //输入用户名, 在login_view.c中定义
                                      return -1;
                                     }
    NEWLINE
    if(get_password(password) == -1) {  //输入第一次密码, 在login_view.c中定义
                                      return -1;
                                     }
    NEWLINE
    if(get_password_again(password_again) == -1) {  //输入第二次密码
                                                  return -1;
                                                 }
    NEWLINE
    if(check_password(password, password_again) == -1) { //检查两次输入是否一致
                                                        sleep(1);
                                                        return -1;
                                                       }
    int rtn;
    rtn=login_signup_model(username, password,2);//参数2代表注册操作
    if(rtn == 2) {  //返回值2代表注册成功
                  NEWLINE
                  PADDING_30 printf("注册成功\n");
                 } else if(rtn == -3) {
                     NEWLINE
                     PADDING_30 printf("用户名已存在\n");
                 } else {
                     NEWLINE
                     PADDING_30 printf("注册失败\n");
                 }
    sleep(1);
    return 0;
}
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
        return 0;
    }else {
        PADDING_30 printf("输入不合法\n");
        sleep(1);
    }
}

int whisper_view(void)
{
    pthread_t whisper_pid;
    pthread_create(&whisper_pid, NULL, (void *)recv_pthread_view, NULL);
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
    whisper_control(username);
}
int group_view()
{
    system("clear");
    printf(" ###########  ###########  ###########  #         #  ###########\n");
    printf(" #            #         #  #         #  #         #  #         #\n");
    printf(" #            #         #  #         #  #         #  #         #\n");
    printf(" #            #         #  #         #  #         #  #         #\n");
    printf(" #    ######  ###########  #         #  #         #  ###########\n");
    printf(" #         #  ###          #         #  #         #  #          \n");
    printf(" #         #  #  ##        #         #  #         #  #          \n");
    printf(" #         #  #    ##      #         #  #         #  #          \n");
    printf(" ###########  #      ####  ###########  ###########  #          \n");
    PADDING_80
    NEWLINE
    group_control();
}
int login_signup_model(char username[  ], char password[  ], int flag)
{
    user_message user;
    strncpy(user.username, username, MAXSIZE);
    strncpy(user.password, password, MAXSIZE);
    user.flag = flag;

    return login_signup_control(user);
}

int login_signup_control(user_message user)
{
    int     conn_fd;
    int     recv_buf;       //接收函数的返回值
    struct sockaddr_in serv_addr;    //定义套接字地址
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));   //清空地址所在内存区域
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(SERV_PORT);  //设置端口号
    serv_addr.sin_addr.s_addr = inet_addr("192.168.20.139");     //设置地址


    conn_fd = socket(AF_INET, SOCK_STREAM, 0);//创建一个TCP套接字
    client_global_fd = conn_fd;     //把套接字描述符变成全局的
    user.client_fd = conn_fd;     //把套接字描述符存进结构体
    connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));     //在conn_fd上创建一个连接
    send(conn_fd, &user, sizeof(user_message), 0);           //发送数据
    recv(conn_fd, &recv_buf, sizeof(recv_buf), 0);

    close(conn_fd);
    return recv_buf;
}
int whisper_control(char username[  ])
{
    pthread_t pid_send;
    int status;     //记录pthread_join的线程的返回值
    user_message user;
    user.flag = 3;  //3代表私聊
    strncpy(user.object_username, username, MAXSIZE);
    send(client_global_fd, &user, sizeof(user_Node), 0);
    pthread_create(&pid_send, NULL, (void *)send_pthread, &user);

    pthread_join(pid_send, (void *)&status);
}

int group_control()
{
    pthread_t pid_send;
    int status;     //记录pthread_join的线程的返回值
    user_message user;
    user.flag = 4;  //4代表群聊
    user.status = 1;    //1代表在线
    send(client_global_fd, &user, sizeof(user_Node), 0);
    pthread_create(&pid_send, NULL,(void *)send_pthread, NULL);//send_pthread在whisper_control.c中定义
    pthread_join(pid_send, (void *)&status);
}
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
