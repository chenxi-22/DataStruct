#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//typedef char SeqStackType;

typedef struct Point {
  int row;
  int col;
}Point;

typedef Point SeqStackType;

typedef struct SeqStack{
  //SeqStackType* data;
  Point* data;
 ; size_t capacity;
  size_t size;
}SeqStack;

void SeqStackInit(SeqStack* stack);//初始化栈

void SeqStackPush(SeqStack* stack, SeqStackType value);//入栈

void SeqStackPop(SeqStack* stack);//出栈

void SeqStackAssign(SeqStack* from, SeqStack* to);//赋值栈

int SeqStackGetFront(SeqStack* stack, SeqStackType* value);//取栈顶元素

void SeqStackPrintShort(SeqStack* stack);//打印最短路径

