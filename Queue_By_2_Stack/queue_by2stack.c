#include <stdio.h>
#include "seqstack.h"

typedef struct queue_by2stackInit {
  SeqStack input;//这个栈为桥梁栈
  SeqStack output;//这个为实际的队列栈
}queue_by2stack;

void queue_by2stackInit(queue_by2stack* q)//初始化新的队列
{
  if(q == NULL)
  {
    return;
  }
  SeqStackInit(&q->input);
  SeqStackInit(&q->output);
  return;
}

void queue_by2stackPush(queue_by2stack* q, SeqStackType value)//入队
{
  if(q == NULL) {
    return;
  }
  
  SeqStackType top;
  int ret;
  while(1) {
    ret = SeqStackGetFront(&q->output, &top);
    if(ret == -1) {
      break;
    }

    SeqStackPush(&q->input, top);
    SeqStackPop(&q->output);
  }

  SeqStackPush(&q->input, value);
  while(1) {
    ret = SeqStackGetFront(&q->input, &top);
    if(ret == -1) {
      break;
    }

    SeqStackPush(&q->output, top);
    SeqStackPop(&q->input);
  }
  return;
}

void queue_by2stackPop(queue_by2stack* q)//出队
{
  if(q == NULL) {
    return;
  }

  SeqStackPop(&q->output);
  return;
}

int queue_by2stackTop(queue_by2stack* q, SeqStackType* value)//取队首元素
{
  if(q == NULL || value == NULL)
  {
    return -1;
  }
  if(q->output.size == 0) {
    return -1;
  }

  SeqStackGetFront(&q->output, value);
  return 1;
}

void queue_by2stackPrint(queue_by2stack* q)
{
  if(q == NULL) {
    return;
  }

  size_t i = 0;
  for(; i < q->output.size; ++i) {
    printf("%c ", q->output.data[i]);
  }
  printf("\n");
}

int main()
{
  queue_by2stack q;
  queue_by2stackInit(&q);
  queue_by2stackPush(&q, 'a');
  queue_by2stackPush(&q, 'b');
  queue_by2stackPush(&q, 'c');
  queue_by2stackPush(&q, 'd');

  queue_by2stackPrint(&q);
  SeqStackType value;
  int ret; 
  ret = queue_by2stackTop(&q,&value);
  printf("expected ret 1, actual ret %d\n",ret);
  printf("expected value a, actual value %c\n",value);

  queue_by2stackPop(&q);
  queue_by2stackPrint(&q);
  ret = queue_by2stackTop(&q,&value);
  printf("expected value b, actual value %c\n",value);
  printf("expected ret 1, actual %d\n",ret);

  queue_by2stackPop(&q);
  queue_by2stackPrint(&q);
  ret = queue_by2stackTop(&q,&value);
  printf("expected ret 1, actual %d\n",ret);
  printf("expected value c, actual value %c\n",value);

  queue_by2stackPop(&q);
  queue_by2stackPrint(&q);
  ret = queue_by2stackTop(&q,&value);
  printf("expected ret 1, actual %d\n",ret);
  printf("expected value d, actual value %c\n",value);

  queue_by2stackPop(&q);
  queue_by2stackPrint(&q);
  ret = queue_by2stackTop(&q,&value);
  printf("expected ret -1, actual %d\n",ret);

  return 0;
}
  



