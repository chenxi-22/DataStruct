#include "heap.h"

#define HEAD printf("===================%s====================\n",__FUNCTION__);

void HeapPrintChar(Heap* heap)
{
  if(heap == NULL) {
    return;
  }
  size_t i = 0;
  for(; i < heap->size; ++i) {
    printf("%c ", heap->data[i]);
  }
  printf("\n");
}


int Greater(int a, int b)
{
  return a > b ? 1 : 0;
}

int Less(int a, int b)
{
  return a < b ? 1 : 0;
}

void HeapInit(Heap* heap, Compare cmp)//初始化堆
{
  if(heap == NULL) {
    return;
  }
  heap->size = 0;
  heap->cmp = cmp;
  return;
}

void Swap(HeapType* a, HeapType* b)
{
  HeapType tmp = *a;
  *a = *b;
  *b = tmp;
}

void HeapInsert(Heap* heap, HeapType to_insert)//在堆中插入
{
  if(heap == NULL) {
    return;
  }
  if(heap->size >= HEAPMAX) {
    return;
  }
  heap->data[heap->size] = to_insert;
  ++heap->size;
  size_t child = heap->size - 1;
  size_t parent = (child - 1) / 2;

  while(child >= 0 && child < heap->size &&
        parent >= 0 && parent < heap->size) {
    if(heap->data[child] > heap->data[parent]){
      Swap(&heap->data[child], &heap->data[parent]);
      child = parent;
      parent = (child - 1) / 2;
    } else {
      break;
    }
  }
  return;
}

int HeapRoot(Heap* heap, HeapType* root)//取堆顶元素
{
  if(heap == NULL) {
    return 0;
  }
  if(heap->size == 0) {
    return 0;
  }
  *root = heap->data[0];
  return 1;
}

void HeapErase(Heap* heap)//删除堆顶元素
{
  if(heap == NULL) {
    return;
  }
  if(heap->size == 0) {
    return;
  }
  Swap(&heap->data[heap->size - 1], &heap->data[0]);
  --heap->size;
  size_t parent = 0;
  size_t child = 2*parent + 1;

  while(child >= 0 && child< heap->size &&
        parent >= 0 && parent < heap->size) {
    if((child + 1) < heap->size){
      if(!heap->cmp(heap->data[child], heap->data[child+1])) {
        child = child + 1;
      }
    }
    if(heap->data[child] > heap->data[parent]) {
      Swap(&heap->data[child], &heap->data[parent]);
      parent = child;
      child = 2*parent + 1;
    } else {
      break;
    }
  }
  return;
}

void HeapDestroy(Heap* heap)//销毁堆
{
  if(heap == NULL) {
    return;
  }
  heap->size = 0;
  heap->cmp = NULL;
  return;
}

void HeapCreat(Heap* heap, HeapType array[], size_t size)//根据一个数组创建堆
{
  if(heap == NULL || array == NULL || size == 0) {
    return;
  }
  size_t i = 0;
  for(; i < size; ++i) {
    HeapInsert(heap, array[i]);
  }
  return;
}

void HeapSort(HeapType array[], size_t size)//堆排
{
  if(array == NULL || size == 0) {
    return;
  }
  Heap heap;
  HeapInit(&heap, Greater);
  HeapCreat(&heap, array, size);
  size_t i = 0;
  for(; i < size; ++i) {
    HeapErase(&heap);
  }
  heap.size = size;
  i = 0;
  for(; i < size; ++i) {
    array[i] = heap.data[i];
  }
  return;
}

/////////////////////////////////////////////////////////////////////////
///测试代码
/////////////////////////////////////////////////////////////////////////
void TestInsert()
{
  HEAD;
  Heap heap;
  HeapInit(&heap, Greater);
  HeapInsert(&heap, 'b');
  HeapInsert(&heap, 'z');
  HeapInsert(&heap, 'a');
  HeapInsert(&heap, 'f');
  HeapInsert(&heap, 'd');
  HeapInsert(&heap, 'c');
  HeapInsert(&heap, 'n');
  HeapPrintChar(&heap);
}

void TestRoot()
{
  HEAD;
  Heap heap;
  HeapInit(&heap, Greater);
  HeapInsert(&heap, 'b');
  HeapInsert(&heap, 'z');
  HeapInsert(&heap, 'a');
  HeapInsert(&heap, 'f');
  HeapInsert(&heap, 'd');
  HeapInsert(&heap, 'c');
  HeapInsert(&heap, 'n');
  HeapType root;
  int ret = HeapRoot(&heap, &root);
  printf("ret expected 1, ret actual %d\n",ret);
  printf("root expected z, root actual %c\n",root);
}

void TestErase()
{
  HEAD;
  Heap heap;
  HeapInit(&heap, Greater);
  HeapInsert(&heap, 'b');
  HeapInsert(&heap, 'z');
  HeapInsert(&heap, 'a');
  HeapInsert(&heap, 'f');
  HeapInsert(&heap, 'd');
  HeapInsert(&heap, 'c');
  HeapInsert(&heap, 'n');
  HeapPrintChar(&heap);
  printf("\n");
  HeapErase(&heap);
  HeapPrintChar(&heap);
  HeapErase(&heap);
  HeapPrintChar(&heap);
  HeapErase(&heap);
  HeapPrintChar(&heap);
}

void TestSort()
{
  HEAD;
  HeapType array[] = {'c', 'd', 'a', 'f', 'z', 'e'};
  size_t size = sizeof(array)/sizeof(array[0]);
  HeapSort(array, size);
  size_t i = 0;
  for(; i < size; ++i) {
    printf("%c ", array[i]);
  }
  printf("\n");
}

void TestCreat()
{
  HEAD;
  Heap heap;
  HeapInit(&heap, Greater);
  HeapType array[] = {'c', 'd', 'a', 'f', 'z', 'e'};
  size_t size = sizeof(array)/sizeof(array[0]);
  HeapCreat(&heap, array, size);
  HeapPrintChar(&heap);
}

int main()
{
  TestInsert();
  TestRoot();
  TestErase();
  TestCreat();
  TestSort();



  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");


  return 0;
}
