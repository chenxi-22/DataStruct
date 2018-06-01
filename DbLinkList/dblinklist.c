#include <stdio.h>
#include <stdlib.h>

#include "dblinklist.h"

#define HEAD printf("-----------------%s-----------------\n",__FUNCTION__);

void DbLinkPrint(DbLinkNode* head)//打印双链表
{
  if(head == NULL)
  {
    return;//非法输入
  }
  DbLinkNode* cur = head->next;

  while(cur != head)
  {
    printf("[%c|%p]",cur->data,cur);
    cur = cur->next;
  }
  printf("\n");

  cur = head->prev;
  while(cur != head)
  {
    printf("[%c|%p]",cur->data,cur);
    cur = cur->prev;
  }
  printf("\n");
  printf("\n");
  printf("\n");

  return;
}

DbLinkNode* DbCreat(DbLinkType value)//创建新的双链表节点
{
  DbLinkNode* new_node = (DbLinkNode*)malloc(sizeof(DbLinkNode));
  new_node->next = new_node;
  new_node->prev = new_node;
  new_node->data = value;
  return new_node;
}

void DbLinkInit(DbLinkNode** phead)//初始化双链表
{
  if(phead == NULL)
  {
    return;//非法输入
  }

  *phead = DbCreat(0);
}

void DbLinkPushBack(DbLinkNode* head, DbLinkType value)//尾部插入
{
  if(head == NULL)
  {
    return;//非法输入
  }

  DbLinkNode* new_node = DbCreat(value);
  DbLinkNode* pre = head->prev;

  pre->next = new_node;
  new_node->prev = pre;
  head->prev = new_node;
  new_node->next = head;

  return;
}

void DbLinkPushFront(DbLinkNode* head, DbLinkType value)//头部插入
{
  if(head == NULL)
  {
    return;//非法输入
  }

  DbLinkNode* new_node = DbCreat(value);
  DbLinkNode* tmp = head->next;

  new_node->next = tmp;
  tmp->prev = new_node;
  head->next = new_node;
  new_node->prev = head;
  return;
}

void DbLinkPopBack(DbLinkNode* head)//尾部删除
{
  if(head == NULL)
  {
    return;
  }
  if(head->next == head)
  {
    return;
  }

  DbLinkNode* to_delete = head->prev;
  to_delete->prev->next = head;
  head->prev = to_delete->prev;
  free(to_delete);
  return;
}

void DbLinkPopFront(DbLinkNode* head)//头部删除
{
  if(head == NULL)
  {
    return;
  }
  if(head->next == head)
  {
    return;
  }

  DbLinkNode* to_delete = head->next;
  DbLinkNode* pre = to_delete->next;
  head->next = pre;
  pre->prev = head;
  free(to_delete);
  return;
}

DbLinkNode* DbLinkFind(DbLinkNode* head, DbLinkType to_find)//查找某个元素
{
  if(head == NULL)
  {
    return NULL;//非法输入
  }
  DbLinkNode* cur = head->next;

  while(cur != head)
  {
    if(cur->data == to_find)
    {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}

void DbLinkInsert(DbLinkNode* pos, DbLinkType value)//在pos位置之前插入一个元素
{
  if(pos == NULL)
  {
    return;
  }

  DbLinkNode* new_node = DbCreat(value);
  DbLinkNode* tmp = pos->prev;

  tmp->next = new_node;
  new_node->prev = tmp;
  new_node->next = pos;
  pos->prev = new_node;

  return;
}

void DbLinkInsertAfter(DbLinkNode* pos,DbLinkType value)//在pos位置之后插入一个元素
{
  if(pos == NULL)
  {
    return;//非法输入
  }

  DbLinkNode* new_node = DbCreat(value);
  DbLinkNode* tmp = pos->next;

  tmp->prev = new_node;
  new_node->next = tmp;
  pos->next = new_node;
  new_node->prev = pos;

  return;
}

void DbLinkErase(DbLinkNode* head,DbLinkNode* pos)//删除pos位置元素
{
  if(head == NULL || pos == NULL)
  {
    return;//非法输入
  }
  if(head->next == head)
  {
    return;//空链表
  }

  DbLinkNode* pos_next = pos->next;
  DbLinkNode* pos_prev = pos->prev;

  pos_next->prev = pos_prev;
  pos_prev->next = pos_next;
  free(pos);

  return;
}

void DbLinkRemove(DbLinkNode* head,DbLinkType to_delete)//删除双链表元素，只删除第一次出现的
{
  if(head == NULL)
  {
    return;
  }
  if(head->next == head)
  {
    return;
  }

  DbLinkNode* cur = head->next;

  while(cur != head)
  {
    if(cur->data == to_delete)
    {
      DbLinkErase(head,cur);
      return;
    }
    cur = cur->next;
  }

  return;
}

void DbLinkRemoveAll(DbLinkNode* head,DbLinkType to_delete)//删除链表中所有to_delete
{
  if(head == NULL)
  {
    return;
  }
  if(head->next == head)
  {
    return;
  }
  
  while(1)
  {
    DbLinkNode* pos_delete =  DbLinkFind(head,to_delete);

    if(pos_delete == NULL)
    {
      return;
    }
    DbLinkErase(head,pos_delete);
  }
}

size_t DbLinkSize(DbLinkNode* head)//计算链表大小
{
  if(head == NULL)
  {
    return -1;
  }

  size_t size = 0;
  DbLinkNode* cur = head->next;

  while(cur != head)
  {
    size++;
    cur = cur->next;
  }
  return size;
}

int DbLinkEmpty(DbLinkNode* head)//判断链表是否为空
{
  if(head == NULL)
  {
    return -1;
  }

  return head->next==head?0:1;
}

////////////////////////////////////////////////////////////////////////////
///测试代码                               //////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void TestPushBack()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushBack(head,'a');
  DbLinkPushBack(head,'b');
  DbLinkPushBack(head,'c');
  DbLinkPushBack(head,'d');
  DbLinkPrint(head);
}

void TestPushFront()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
}

void TestPopBack()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkPopBack(head);
  DbLinkPrint(head);
}

void TestPopFront()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkPopFront(head);
  DbLinkPrint(head);
}

void TestFind()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');

  DbLinkNode* ret = DbLinkFind(head,'b');
  printf("[%c|%p]\n",ret->data,ret);
  ret = DbLinkFind(head,'z');
  printf("%p\n",ret);
}

void TestInsert()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkNode* pos_b = DbLinkFind(head,'b');
  DbLinkInsert(pos_b,'z');
  DbLinkPrint(head);
}

void TestInsertAfter()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkNode* pos_b = DbLinkFind(head,'b');
  DbLinkInsertAfter(pos_b,'z');
  DbLinkPrint(head);
}

void TestErase()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkNode* pos_b = DbLinkFind(head,'b');
  DbLinkErase(head,pos_b);
  DbLinkPrint(head);
}

void TestRemove()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkRemove(head,'c');
  DbLinkPrint(head);
}

void TestRemoveAll()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'d');
  DbLinkPrint(head);
  DbLinkRemoveAll(head,'c');
  DbLinkPrint(head);
}

void TestSize()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPrint(head);
  size_t sz = DbLinkSize(head);
  printf("%lu\n",sz);
}

void TestEmpty()
{
  HEAD;
  DbLinkNode* head;
  DbLinkInit(&head);
  int n = DbLinkEmpty(head);
  printf("%d\n",n);
  DbLinkPushFront(head,'a');
  DbLinkPushFront(head,'b');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPushFront(head,'c');
  DbLinkPrint(head);
  n = DbLinkEmpty(head);
  printf("%d\n",n);
}

int main()
{
  TestPushBack();
  TestPushFront();
  TestPopBack();
  TestPopFront();
  TestFind();
  TestInsert();
  TestInsertAfter();
  TestErase();
  TestRemove();
  TestRemoveAll();
  TestSize();
  TestEmpty();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
}














