#pragma once

#include <stdio.h>
#include <stddef.h>

#define SQUEUEMAX 1000

//typedef char SeqQueueType;

struct TreeNode;
typedef struct TreeNode* SeqQueueType;

typedef struct SeqQueue{
  SeqQueueType data[SQUEUEMAX];
  size_t head;
  size_t tail;
  size_t size;
}SeqQueue;

SeqQueue q;

void SeqQueueInit(SeqQueue* q);//初始化顺序式队列

void SeqQueuePush(SeqQueue* q, SeqQueueType value);//入顺序式队列

void SeqQueuePop(SeqQueue* q);//出顺序式队列

void DestroySeqQueue(SeqQueue* q);//销毁顺序式队列

int SeqQueueGetFront(SeqQueue* q, SeqQueueType* value);//获取队首








