#include "seqstack.h"

#define HEAD printf("===================%s====================\n",__FUNCTION__);

void SeqStackPrint(SeqStack* stack)//打印栈内元素
{
  if(stack == NULL)
  {
    return;
  }
  if(stack->size == 0)
  {
    return;
  }

  size_t i = 0;
  for(; i < stack->size; ++i)
  {
    printf("%d ",stack->data[i]);
  }
  printf("\n");
}

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


////////////////////////////////////////////////////////////
//测试函数
//
////////////////////////////////////////////////////////////

#if 0

void TestPush()
{
  HEAD;
  SeqStack stack;
  SeqStackInit(&stack);
  SeqStackPush(&stack, 'a');
  SeqStackPush(&stack, 'b');
  SeqStackPush(&stack, 'c');
  SeqStackPush(&stack, 'd');
  SeqStackPrint(&stack);
}

void TestPop()
{
  HEAD;
  SeqStack stack;
  SeqStackInit(&stack);
  SeqStackPush(&stack, 'a');
  SeqStackPush(&stack, 'b');
  SeqStackPush(&stack, 'c');
  SeqStackPush(&stack, 'd');
  SeqStackPrint(&stack);

  SeqStackPop(&stack);
  SeqStackPrint(&stack);
  SeqStackPop(&stack);
  SeqStackPrint(&stack);
  SeqStackPop(&stack);
  SeqStackPrint(&stack);
  SeqStackPop(&stack);
  SeqStackPrint(&stack);
}

void TestGetFront()
{
  HEAD;
  SeqStack stack;
  SeqStackInit(&stack);
  SeqStackPush(&stack, 'a');
  SeqStackPush(&stack, 'b');
  SeqStackPush(&stack, 'c');
  SeqStackPush(&stack, 'd');
  SeqStackPrint(&stack);

  SeqStackType value;
  int ret = SeqStackGetFront(&stack,&value);
  printf("expected ret 1, actual %d\n",ret);
  printf("expected value d, actual %c\n",value);
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
  printf("\n");

  return 0;
}

#endif













