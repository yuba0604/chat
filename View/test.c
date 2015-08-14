#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
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
int main()
{
    int i;
    char string[100];
    for(i=0;i<5;i++){
        string[i]=getch();
    }
    printf("finish\n");
    for(i=0;i<5;i++){
        printf("%c\n",string[i]);
    }
}
