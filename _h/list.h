#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>
#include"struct.h"

//创建链表
void List_Create(user_Node *list)
{
    list=(user_Node*)malloc(sizeof(user_Node));
}
//头插法插入节点
void List_Insert(user_Node *list, user_Node *pNew)
{
    pNew->next=list;
    list=pNew;
}
#endif /* LIST_H_ */
