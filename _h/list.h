#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>
#include"struct.h"

//��������
List_Init(user_Node *list, user_Node) {
    list=(user_Node)malloc(sizeof(user_Node));
    list->next=list->prev=list;
}
//����β�巨��listΪͷָ�룬newΪ�½ڵ�
List_AddTail(user_Node *list, user_Node *newNode)
{
    newNode->prev=list->prev;
    list->prev->next=newNode;
    newNode->next=list;
    list->prev=newNode;
}
//�ͷ�����list���������ݽ�㡣list Ϊ����ͷָ�룬list_node_tΪ����������
List_Free(user_Node *list, user_Node) 
{
    assert(NULL!=list);
    user_Node *tmpPtr;
    list->prev->next=NULL;
        while(NULL!=(tmpPtr=list->next)){
        list->next=tmpPtr->next;
        free(tmpPtr);
    }
    list->next=list->prev=list;
}
//��������list���ͷ��������ݽ�㼰ͷ��㡣 listΪ����ͷָ�룬tmpPtrΪ��������ʱָ�����
List_Destroy(user_Node *list, user_Node) {
		assert(NULL!=list);
		List_Free(list, user_Node);
		free(list);
		list=NULL;
}
//����β�巨��listΪͷָ�룬newΪ�½ڵ�
List_AddTail(user_Node *list, user_Node newNode) {
    newNode->prev=list->prev;
    list->prev->next=newNode;
    newNode->next=list;
    list->prev=newNode;
}

#endif /* LIST_H_ */
