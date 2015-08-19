#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>
#include"struct.h"

//创建链表
List_Create()
{
    list=(user_Node)malloc(sizeof(user_Node));
}
//头插法插入节点
List_Insert(user_Node *pNew)
{
    pNew->next=list;
    list=pNew;
}
#endif /* LIST_H_ */
