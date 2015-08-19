/*************************************************************************
	> File Name: list.c
	> Note: 
	> Created Time: 2015年08月19日 星期三 09时41分06秒
 ************************************************************************/

#include<stdio.h>
#include"../_h/list.h"
#include"../_h/struct.h"
int main()
{
    user_Node *list;//链表头节点
    int fd;    //文件描述符
    int number = 1;     //判断read是否结束
    user_Node *pNew;//指向新节点的指针
    //生成链表
    List_Creat(list);    //创建链表
    //把数据读入链表
    fd = open("../File/_user.txt",O_RDONLY|O_CREAT);
    while(1) {
        pNew = (user_Node)malloc(sizeof(user_Node));
        number = read(fd, pNew->data, sizeof(pNew->data));
        if(number == 0) {
            break;
        }
        List_Insert(pNew);
    }
    //把链表中的数据存入文件
    user_Node *pWrite = list;   //写入文件的指针
    while(pWrite != NULL) {
        write(fd, pWrite->data, sizeof(pWrite->data));
        pWrite = pWrite->Next;
    }

}
