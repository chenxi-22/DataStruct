#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef char LinkQueueType;

typedef struct LinkQueueNode{
  LinkQueueType data;
  struct LinkQueueNode* next;
}LinkQueueNode;

typedef struct LinkQueue{
  LinkQueueNode* head;
  LinkQueueNode* tail;
}LinkQueue;

void LinkQueueInit(LinkQueue* q);//初始化链式队列

void LinkQueuePush(LinkQueue* q, LinkQueueType value);//入队

void LinkQueuePop(LinkQueue* q);//出队

void DestroyLinkQueue(LinkQueue* q);//销毁队列

int LinkQueueGetFront(LinkQueue* q, LinkQueueType* value);//获取队首


