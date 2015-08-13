/*************************************************************************
	> File Name: 1ogin.c
	> Note: 登陆的界面
	> Created Time: 2015年08月12日 星期三 14时24分15秒
 ************************************************************************/

#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<string.h>

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


int get_password(char *password)
///get_password是输入密码的函数, 密码会赋给password, 输入的密码以*显示, 控制输入格式
{
    int     i = 0;  //i用来统计输入字符个数
    printf("密码(小于14位):");
    while(1) {
        password[i] = getch();
        if( (password[i] == '\n') ) {
            break;
        }
        printf("*");
        i++;
        if( i >= 14 ) {
            printf("\n密码过长\n");
            break;
        }
    }
}

int get_username(char *username)
///get_username是输入用户名的函数, 用户名会赋给username, 控制输入格式
{
    int     i = 0;
    int     temp;
    printf("用户名(小于14位, 只能用数字 字母 下划线):");
    while(1) {
        username[i] =getchar();
        temp = (int)username[i];
        if((temp>47&&temp<58)||(temp>64&&temp<91)||(temp>96&&temp<123)||(temp==95)){
            //判断输入的是否是数字 字母 下划线
            if( (username[i] == '\n') ) {
                break;
            }
            i++;
            if( i >= 14 ) {
                printf("用户名过长\n");
                break;
            }
        }
    }
}
int main()
//int login_view(char *username, char *password)
{   
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
    printf("\n");
    for(int i = 1; i <= 80; i++) {
        printf("=");
    }
    printf("\n");
    printf("\n");
    for(int i = 0; i < 30; i++) {
        printf(" ");
    }
    char *username;
    get_username(username);
    printf("%s\n",username);//这里是输入用户名的函数
    printf("\n");
    char *password;
    get_password(password);
    printf("\n%s\n",password);
}
