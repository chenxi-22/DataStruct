#include "seqstack.h"


void SeqStackInit(SeqStack* stack)//初始化栈
{
  if(stack == NULL)
  {
    return;
  }

  stack->size = 0;
  stack->capacity = 1000;
  stack->data = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
  return;
}

void SeqStackSet(SeqStack* stack)//扩容
{
  if(stack == NULL)
  {
    return;
  }
  if(stack->size < stack->capacity)
  {
    return;
  }

  SeqStackType* new_data = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType)*2+1);
  size_t i = 0;

  for(; i < stack->size; ++i)//拷贝原来的内容
  {
    new_data[i] = stack->data[i];
  }
  free(stack->data);
  stack->data = new_data;

  return;
}

void SeqStackPush(SeqStack* stack, SeqStackType value)//入栈
{
  if(stack == NULL)
  {
    return;
  }

  if(stack->size >= stack->capacity)
  {
    SeqStackSet(stack);//扩容
  }

  stack->data[stack->size++] = value;
  return;
}

void SeqStackPop(SeqStack* stack)//出栈
{
  if(stack == NULL)
  {
    return;
  }
  if(stack->size == 0)
  {
    return;
  }

  --stack->size;
}

void DestroyStack(SeqStack* stack)//销毁栈
{
  if(stack == NULL)
  {
    return;
  }

  stack->size = 0;
  free(stack->data);
  return;
}

int SeqStackGetFront(SeqStack* stack, SeqStackType* value)//取栈顶元素
{
  if(stack == NULL || value == NULL)
  {
    return 0;
  }
  if(stack->size == 0)
  {
    return 0;
  }

  *value = stack->data[stack->size-1];
  return 1;
}

void SeqStackAssign(SeqStack* from, SeqStack* to)//赋值栈
{
  if(from == NULL || to == NULL) {
    return;
  }

  size_t i = 0;

  to->capacity = from->capacity;
  to->size = from->size;
  to->data = (SeqStackType*)malloc(to->capacity * sizeof(SeqStackType));

  for(; i < to->size; ++i) {
    to->data[i] = from->data[i];
  }

  return;
}

void SeqStackPrintShort(SeqStack* stack)//打印最短路径
{
  if(stack == NULL) {
    return;
  }
  
  size_t i = 0;
  for(; i < stack->size; ++i) {
    printf("(%d,%d)\n",stack->data[i].row, stack->data[i].col);
  }
  printf("\n");
}

