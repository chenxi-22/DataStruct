#include <stdio.h>
#include "seqqueue.h"

typedef struct stack_by2queue{
  SeqQueue queue1;
  SeqQueue queue2;
}stack_by2queue;

void stack_by2queueInit(stack_by2queue* q)//初始化栈
{
  if(q == NULL)
  {
    return;
  }

  SeqQueueInit(&q->queue1);
  SeqQueueInit(&q->queue2);
  return;
}

void stack_by2queuePush(stack_by2queue* q, SeqQueueType value)//入栈
{
  if(q == NULL) {
    return;
  }
  if(q->queue1.size != 0) {
    SeqQueuePush(&q->queue1, value);
  } else {
    SeqQueuePush(&q->queue2, value);
  }
  return;
}

void stack_by2queuePop(stack_by2queue* q)//出栈
{
  if(q == NULL) {
    return;
  }
  if(q->queue1.size == 0 && q->queue2.size == 0) {
    return;
  }

  SeqQueueType top;

  while(1) {
    if(q->queue1.size != 0) {
      while(1)
      {
        if(q->queue1.size == 1) {
          SeqQueuePop(&q->queue1);
          return;
        }
        SeqQueueGetFront(&q->queue1, &top);
        SeqQueuePush(&q->queue2, top);
        SeqQueuePop(&q->queue1);
      }
    } else {
      while(1)
      {
        if(q->queue2.size == 1) {
          SeqQueuePop(&q->queue2);
          return;
        }
        SeqQueueGetFront(&q->queue2, &top);
        SeqQueuePush(&q->queue1, top);
        SeqQueuePop(&q->queue2);
      }
    }
  }
}

int stack_by2queueTop(stack_by2queue* q, SeqQueueType* value)//取栈顶元素
{
  if(q == NULL) {
    return -1;
  }
  if(q->queue1.size == 0 && q->queue2.size == 0) {
    return -1;
  }

  while(1) {
    if(q->queue1.size != 0) {
      while(1)
      {
        SeqQueueGetFront(&q->queue1, value);
        SeqQueuePush(&q->queue2, *value);
        SeqQueuePop(&q->queue1);
        if(q->queue1.size == 0) {
          return 1;
        }
      }
    } else {
      while(1)
      {
        SeqQueueGetFront(&q->queue2, value);
        SeqQueuePush(&q->queue1, *value);
        SeqQueuePop(&q->queue2);
        if(q->queue2.size == 0) {
          return 1;
        }
      }
    }
  }
}

void stack_by2queuePrint(stack_by2queue* q)
{
  if(q == NULL) {
    return;
  }

  size_t i = 0;

  if(q->queue1.size != 0) {
    for(i = q->queue1.head; i != q->queue1.tail; ++i) {
      if(i >= SQUEUEMAX) {
        i = 0;
      }
      printf("%c ",q->queue1.data[i]);
    }
  } else {
    for(i = q->queue2.head; i != q->queue2.tail; ++i) {
      if(i >= SQUEUEMAX) {
        i = 0;
      }
      printf("%c ",q->queue2.data[i]);
    }
  }
  printf("\n");

  return;
}

int main()
{
  stack_by2queue q;
  SeqQueueType value;
  int ret;
  stack_by2queueInit(&q);
  stack_by2queuePush(&q, 'a');
  stack_by2queuePush(&q, 'b');
  stack_by2queuePush(&q, 'c');
  stack_by2queuePush(&q, 'd');
  stack_by2queuePrint(&q);
  ret = stack_by2queueTop(&q, &value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value d, actual value %c\n",value);

  stack_by2queuePop(&q);
  stack_by2queuePrint(&q);
  ret = stack_by2queueTop(&q, &value);
  ret = stack_by2queueTop(&q, &value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value c, actual value %c\n",value);

  stack_by2queuePop(&q);
  stack_by2queuePrint(&q);
  ret = stack_by2queueTop(&q, &value);
  ret = stack_by2queueTop(&q, &value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value b, actual value %c\n",value);

  stack_by2queuePop(&q);
  stack_by2queuePrint(&q);
  ret = stack_by2queueTop(&q, &value);
  ret = stack_by2queueTop(&q, &value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value a, actual value %c\n",value);

  stack_by2queuePop(&q);
  stack_by2queuePrint(&q);
  ret = stack_by2queueTop(&q, &value);
  ret = stack_by2queueTop(&q, &value);
  printf("expected ret -1, actual ret %d\n",ret);

  return 0;
}

