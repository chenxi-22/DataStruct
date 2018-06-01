#include "seqqueue.h"

#define HEAD printf("=================%s===============\n",__FUNCTION__)

void SeqQueueInit(SeqQueue* q)//初始化顺序式队列
{
  if(q == NULL)
  {
    return;
  }

  q->head = 0;
  q->tail = 0;
  q->size = 0;

  return;
}

void DestroySeqQueue(SeqQueue* q)//销毁顺序式队列
{
  if(q == NULL)
  {
    return;
  }

  q->head = 0;
  q->tail = 0;
  q->size = 0;

  return;
}

void SeqQueuePush(SeqQueue* q, SeqQueueType value)//入顺序式队列
{
  if(q == NULL)
  {
    return;
  }
  if(q->size >= SQUEUEMAX)
  {
    return;
  }

  if(q->size == 0)
  {
    q->data[q->head] = value;
    ++q->tail;
    ++q->size;
  }
  else
  {
    q->data[q->tail++] = value;
    ++q->size;
  }

  if(q->tail >= SQUEUEMAX)
  {
    q->tail = 0;
  }

  return;
}

void SeqQueuePop(SeqQueue* q)//出顺序式队列
{
  if(q == NULL)
  {
    return;
  }
  if(q->size == 0)
  {
    return;
  }

  ++q->head;
  if(q->head >= SQUEUEMAX)
  {
    q->head = 0;
  }
  --q->size;

  return;
}

int SeqQueueGetFront(SeqQueue* q, SeqQueueType* value)//获取队首
{
  if(q == NULL || value == NULL)
  {
    return -1;
  }

  *value = q->data[q->head];
  return 1;
}

//////////////////////////////////////////////////////////////////
//测试函数
///
/////////////////////////////////////////////////////////////////

void SeqQueuePrint(SeqQueue* q)
{
  if(q == NULL)
  {
    return;
  }
  if(q->size == 0)
  {
    return;
  }

  size_t i = q->head;
  for(; i != q->tail; ++i)
  {
    if(i >= SQUEUEMAX)
    {
      i = 0;
    }
    printf("%c ",q->data[i]);
  }
  printf("\n");
}

void TestPush()
{
  HEAD;
  SeqQueue q;
  SeqQueueInit(&q);
  SeqQueuePush(&q,'a');
  SeqQueuePush(&q,'b');
  SeqQueuePush(&q,'c');
  SeqQueuePush(&q,'d');
  SeqQueuePrint(&q);
}

void TestPop()
{
  HEAD;
  SeqQueue q;
  SeqQueueInit(&q);
  SeqQueuePush(&q,'a');
  SeqQueuePush(&q,'b');
  SeqQueuePush(&q,'c');
  SeqQueuePush(&q,'d');
  SeqQueuePrint(&q);

  SeqQueuePop(&q);
  SeqQueuePrint(&q);
  SeqQueuePop(&q);
  SeqQueuePrint(&q);
  SeqQueuePop(&q);
  SeqQueuePrint(&q);
  SeqQueuePop(&q);
  SeqQueuePrint(&q);
}

void TestGetFront()
{
  HEAD;
  SeqQueue q;
  SeqQueueInit(&q);
  SeqQueuePush(&q,'a');
  SeqQueuePush(&q,'b');
  SeqQueuePush(&q,'c');
  SeqQueuePush(&q,'d');
  SeqQueuePrint(&q);
  
  SeqQueueType value;
  int ret = SeqQueueGetFront(&q,&value);
  printf("expected ret 1, actual %d\n",ret);
  printf("%c \n",value);
}

//int main()
//{
//  TestPush();
//  TestPop();
//  TestGetFront();
//
//  printf("\n");
//  printf("\n");
//  printf("\n");
//  printf("\n");
//  printf("\n");
//  return 0;
//}




