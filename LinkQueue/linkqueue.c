#include "linkqueue.h"

#define HEAD printf("=================%s================\n",__FUNCTION__)

void LinkQueueInit(LinkQueue* q)//初始化链式队列
{
  if(q == NULL)
  {
    return;
  }

  q->head = q->tail = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
  if(q -> head == NULL)
  {
    return;
  }
   
  q->head->next = NULL;
}

void LinkQueuePush(LinkQueue* q, LinkQueueType value)//入队
{
  if(q == NULL)
  {
    return;
  }
  if(q->head == NULL)
  {
    return;
  }

  LinkQueueNode* cur = q->head;

  LinkQueueNode* new_node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
  new_node->data = value;
  new_node->next = NULL;

  while(cur->next != NULL)
  {
    cur = cur->next;
  }
  cur->next = new_node;
  q->tail = new_node;
  return;
}

void LinkQueuePop(LinkQueue* q)//出队
{
  if(q == NULL)
  {
    return;
  }
  if(q->head == NULL || q->head->next == NULL)
  {
    return;
  }

  LinkQueueNode* cur = q->head;
  LinkQueueNode* to_delete = cur->next;
  cur->next = to_delete->next;
  free(to_delete);
  to_delete = NULL;

  return;
}

void DestroyLinkNode(LinkQueue* q)//销毁队列
{
  if(q == NULL)
  {
    return;
  }
  if(q->head == NULL)
  {
    return;
  }

  while(q->head != NULL)
  {
    q->tail = q->head->next;
    free(q->head);
    q->head = q->tail;
  }
  return;
}

int LinkQueueGetFront(LinkQueue* q, LinkQueueType* value)//获取队首
{
  if(q == NULL)
  {
    return -1;
  }
  if(q->head == NULL || q->head->next == NULL)
  {
    return -1;
  }
  
  *value = q->head->next->data;
  return 1;
}

////////////////////////////////////////////////////////////////////////
//测试代码
//////////////////////////////////////////////////////////////////////

void LinkQueuePrint(LinkQueue* q)
{
  if(q == NULL)
  {
    return;
  }
  if(q->head->next == NULL)
  {
    return;
  }

  LinkQueueNode* cur = q->head->next;
  while(cur != NULL)
  {
    printf("%c ",cur->data);
    cur = cur->next;
  }
  printf("\n");
}

void TestPush()
{
  HEAD;
  LinkQueue q;
  LinkQueueInit(&q);
  LinkQueuePush(&q,'a');  
  LinkQueuePrint(&q);
  LinkQueuePush(&q,'b');  
  LinkQueuePrint(&q);
  LinkQueuePush(&q,'c');  
  LinkQueuePrint(&q);
  LinkQueuePush(&q,'d');  
  LinkQueuePrint(&q);
}

void TestPop()
{
  HEAD;
  LinkQueue q;
  LinkQueueInit(&q);
  LinkQueuePush(&q,'a');  
  LinkQueuePush(&q,'b');  
  LinkQueuePush(&q,'c');  
  LinkQueuePush(&q,'d');  
  LinkQueuePrint(&q);
  LinkQueuePop(&q);
  LinkQueuePrint(&q);
}

void TestGetFront()
{
  HEAD;
  LinkQueue q;
  LinkQueueType value;

  LinkQueueInit(&q);
  int ret = LinkQueueGetFront(&q,&value);
  printf("expected ret -1, actual ret %d\n",ret);
  LinkQueuePush(&q,'a');  
  LinkQueuePush(&q,'b');  
  LinkQueuePush(&q,'c');  
  LinkQueuePush(&q,'d');  
  LinkQueuePrint(&q);

  ret = LinkQueueGetFront(&q,&value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value a, actual value %c\n",value);
}

int main()
{
  TestPush();
  TestPop();
  TestGetFront();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
}






