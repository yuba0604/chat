#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>
#include"struct.h"

//��������
List_Create()
{
    list=(user_Node)malloc(sizeof(user_Node));
}
//ͷ�巨����ڵ�
List_Insert(user_Node *pNew)
{
    pNew->next=list;
    list=pNew;
}
#endif /* LIST_H_ */
