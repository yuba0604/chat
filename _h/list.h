#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <assert.h>
#include"struct.h"

//创建链表
List_Init(user_Node *list, user_Node) {
    list=(user_Node)malloc(sizeof(user_Node));
    list->next=list->prev=list;
}
//链表尾插法，list为头指针，new为新节点
List_AddTail(user_Node *list, user_Node *newNode)
{
    newNode->prev=list->prev;
    list->prev->next=newNode;
    newNode->next=list;
    list->prev=newNode;
}
//释放链表list中所有数据结点。list 为链表头指针，list_node_t为链表结点类型
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
//销毁链表list，释放所有数据结点及头结点。 list为链表头指针，tmpPtr为链表结点临时指针变量
List_Destroy(user_Node *list, user_Node) {
		assert(NULL!=list);
		List_Free(list, user_Node);
		free(list);
		list=NULL;
}
//链表尾插法，list为头指针，new为新节点
List_AddTail(user_Node *list, user_Node newNode) {
    newNode->prev=list->prev;
    list->prev->next=newNode;
    newNode->next=list;
    list->prev=newNode;
}

#endif /* LIST_H_ */
