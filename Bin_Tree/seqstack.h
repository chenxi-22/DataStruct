#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define FOR_TREE 0

#if FOR_TREE
typedef char SeqStackType;
#else
struct TreeNode;
typedef struct TreeNode* SeqStackType; 
#endif


typedef struct SeqStack{
  SeqStackType* data;
  size_t capacity;
  size_t size;
}SeqStack;


void SeqStackInit(SeqStack* stack);//初始化栈

void SeqStackPush(SeqStack* stack, SeqStackType value);//入栈

void SeqStackPop(SeqStack* stack);//出栈

void DestroyStack(SeqStack* stack);//销毁栈

int SeqStackGetFront(SeqStack* stack, SeqStackType* value);//取栈顶元素





