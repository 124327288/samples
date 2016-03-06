/************************************************************************

������

FUNCTIONS :
ListCreate			- ����һ���µ�����
ListInsertAt		- ����ڵ㵽����
ListPushFront		- ������ͷ������ڵ㡣
ListPushBack		- ������β������ڵ㡣
ListPopFront		- ɾ������ͷ���ڵ㡣
ListPopBack			- ɾ������β���ڵ㡣
ListGetFront		- ��õ�һ���ڵ�
ListGetBack			- ������һ���ڵ㡣
ListGetNodeAt		- ������Ż�ýڵ㡣
ListDeleteNodeAt	- �������ɾ���ڵ㡣
ListDestroy			- ɾ����������
ListDestroyAndFree	- ɾ�������������ͷ����ݡ�
ListClear			- ɾ�������е����нڵ㡣
ListClearAndFree	- ��������е����нڵ㣬���ͷ����ݡ�
ListGetSize			- ��õ�ǰ�����С���ڵ���������


************************************************************************/

#ifndef LIST_H
#define LIST_H

typedef struct _NODE
{
	void* data;
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST
{
 void* list_data;
 PNODE first;
}LIST, *PLIST;



PLIST ListCreate(void* list_data);
void NodeDistory(PNODE);
void ListPushBack(PLIST list, void* data);
void ListPushFront(PLIST list, void* data);
void* ListPopBack(PLIST list);
void* ListPopFront(PLIST list);
int ListInsertAt(PLIST list, unsigned int n, void* data);
void* ListDeleteAt(PLIST list, int n);
void ListClearAndFree(PLIST list);
void ListDistoryAndFree(PLIST list);
void ListDistory(PLIST list);
int ListSize(PLIST list);
void* ListGetAt(PLIST list, unsigned int n);

#endif