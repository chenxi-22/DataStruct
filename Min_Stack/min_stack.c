#include <stdio.h>
#include "seqstack.h"

typedef struct Min_SeqStack {
  SeqStack stack; 
}Min_SeqStack;

void Min_SeqStackPrint(Min_SeqStack* s)
{
  if(s == NULL) {
    return;
  }

  size_t i = 0;
  for(; i < s->stack.size; i++) {
    printf("%c ", s->stack.data[i]);
  }
  printf("\n");
}

void Min_SeqStackInit(Min_SeqStack* s)
{
  if(s == NULL) {
    return;
  }
  SeqStackInit(&s->stack);
  return;
}

void Min_SeqStackPush(Min_SeqStack* s, SeqStackType value)
{
  if(s == NULL) {
    return;
  }

  SeqStackType top;
  SeqStackType min;


  if(s->stack.size == 0) {
    SeqStackPush(&s->stack, value);   
    SeqStackPush(&s->stack, value);   
  } else {
    SeqStackGetFront(&s->stack, &top);
    min = top < value ? top : value;
    SeqStackPush(&s->stack, value);
    SeqStackPush(&s->stack, min);
  }
  return;
}

void Min_SeqStackPop(Min_SeqStack* s)
{
  if(s == NULL) {
    return;
  }
  if(s->stack.size == 0) {
    return;
  }
  SeqStackPop(&s->stack);
  SeqStackPop(&s->stack);
}

int Min_SeqStackTop(Min_SeqStack* s, SeqStackType* value)
{
  if(s == NULL) {
    return -1;
  }
  if(s->stack.size == 0) {
    return -1;
  }
  return SeqStackGetFront(&s->stack, value);
}

int main()
{
  Min_SeqStack s;
  Min_SeqStackInit(&s); 
  Min_SeqStackPush(&s, 'a');
  Min_SeqStackPush(&s, 'c');
  Min_SeqStackPush(&s, 'd');
  Min_SeqStackPush(&s, 's');
  Min_SeqStackPrint(&s);
  SeqStackType value;
  Min_SeqStackTop(&s, &value);
  Min_SeqStackPrint(&s);
  printf("%c\n", value);

  Min_SeqStackPop(&s);
  Min_SeqStackPrint(&s);
  Min_SeqStackTop(&s, &value);
  printf("%c\n", value);

  Min_SeqStackPop(&s);
  Min_SeqStackPrint(&s);
  Min_SeqStackTop(&s, &value);
  printf("%c\n", value);

  Min_SeqStackPop(&s);
  Min_SeqStackPrint(&s);
  Min_SeqStackTop(&s, &value);
  printf("%c\n", value);

  return 0;
}

