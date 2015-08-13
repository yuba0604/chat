/*************************************************************************
	> File Name: view.h
	> Note: 
	> Created Time: 2015年08月13日 星期四 15时37分13秒
 ************************************************************************/

#ifndef _VIEW_H
#define _VIEW_H

///以'='填充一行
#define PADDING_80 for(int i = 0; i < 80; i++){printf("=");}
///以' '填充30px, 使选项置于正中央
#define PADDING_30 for(int i = 0; i < 30; i++){printf(" ");}
///换一行
#define NEWLINE    printf("\n");

int login_view(void);
int sign_up_view(void);
int main_view(void);
int group_view(void);
int chat_view(void);
#endif
