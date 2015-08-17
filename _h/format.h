/*************************************************************************
	> File Name: format.h
	> Note: 
	> Created Time: 2015年08月17日 星期一 10时21分26秒
 ************************************************************************/

#ifndef _FORMAT_H
#define _FORMAT_H

///以'='填充一行
#define PADDING_80 for(int i = 0; i < 80; i++){printf("=");}
///以' '填充30px, 使选项置于正中央
#define PADDING_30 for(int i = 0; i < 30; i++){printf(" ");}
///换一行
#define NEWLINE    printf("\n");

#endif
