#pragma once

#include <stdio.h>
#include <stddef.h>

#define HEAPMAX 1000

typedef char HeapType;

typedef int(*Compare)(int a, int b);//函数指针，来确定将来的堆是最大堆还是最小堆

typedef struct Heap{
  HeapType data[HEAPMAX];
  size_t size;
  Compare cmp;
}Heap;

void HeapInit(Heap* heap, Compare cmp);//初始化堆

void HeapInsert(Heap* heap, HeapType to_insert);//在堆中插入

int HeapRoot(Heap* heap, HeapType* root);//取堆顶元素

void HeapErase(Heap* heap);//删除堆顶元素

void HeapDestroy(Heap* heap);//销毁堆

void HeapCreat(Heap* heap, HeapType array[], size_t size);//根据一个数组创建堆

void HeapSort(HeapType array[], size_t size);//堆排

