#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "seqstack.h"

// 注：以下排序算法皆为升序排序

void Swap(int* a, int* b)
{
  int tmp = *a;
  *a = *b;
  *b =tmp;
}

///////////////////////////////////////////////////////////
// 冒泡排序
// 时间复杂度 ：O(N ^ 2)
// 空间复杂度 ：O(1)
// 排序稳定程度 ：稳定
///////////////////////////////////////////////////////////

void BubbleSort(int array[], int size) // 冒泡排序
{
  if (size <= 1) {
    return;
  }

  int bound = 0; // 定义边界为 bound 
  for (; bound < size; ++bound) {
    int cur = size - 1;
    for (; cur > bound; --cur) { // 让排序从后往前排序
      if (array[cur] < array[cur - 1]) {
        Swap(&array[cur], &array[cur - 1]);
      }
    }
  } // end for (; bound < size; ++bound)
  return;
}

///////////////////////////////////////////////////////////
// 选择排序
// 时间复杂度 ：O(N^2)
// 空间复杂度 ：O(1)
// 排序稳定程度 ：不稳定
///////////////////////////////////////////////////////////

void SelectSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  int bound = 0; // 此时 bound 代表的是擂台，选择排序就是一个打擂台的过程
  for (; bound < size; ++bound) {
    int cur = bound + 1;
    for (; cur < size; ++cur) {
      if (array[bound] > array[cur]) { // 如果能够进入这个 if 那就是擂台打赢了，交换擂主
        Swap(&array[bound], &array[cur]);
      }
    }
  } // end for (; bound < size; ++bound)
  return;
}

///////////////////////////////////////////////////////////
// 插入排序
// 时间复杂度 ：O(N^2)
// 空间复杂度 ：O(1)
// 排序稳定程度 ：稳定
///////////////////////////////////////////////////////////

void InsertSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  int bound = 0;
  for (; bound < size; ++bound) { // 定义有序区间为 [0, bound)
    int bound_value = array[bound]; // 此处 bound_value 的值就是待插入的值
    int cur = bound - 1;
    while (bound_value < array[cur] && cur >= 0) { // 判断待插入的值与前面有序区间的值的大小
      array[cur + 1] = array[cur]; 
      cur--;
    }
    array[cur + 1] = bound_value; // 最终找到了 bound_value 真正的位置，进行插入
  }
  return;
}

///////////////////////////////////////////////////////////
// 堆排序
// 时间复杂度 ：O(N * log N)
// 空间复杂度 ：O(1)
// 排序稳定程度 ：不稳定
///////////////////////////////////////////////////////////

void AdjustDown(int array[], int parent, int size) // 下沉式调整
{
  int child = 2 * parent + 1;
  while (child < size) {
    if ((child + 1) < size && array[child] < array[child + 1]) {
      child = child + 1;
    }
    if (array[parent] < array[child]) {
      Swap(&array[parent], &array[child]);
      parent = child;
      child = 2 * parent + 1;
    } else {
      break;
    }
  } // end while (1)
  return;
}

void HeapCreate(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  int parent = (size - 1 - 1) / 2;

  for (; parent >= 0; parent--) {
    AdjustDown(array, parent, size);
  }
  return;
}

void HeapPop(int array[], int heap_bound)
{
  Swap(&array[0], &array[heap_bound - 1]);
  AdjustDown(array, 0, heap_bound - 1);
}

void HeapSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  HeapCreate(array, size); // 创建堆

  int i = 0;
  for (; i < size; ++i) {
    // 由于每次删除堆的元素后
    // 堆的范围就变了
    // 所以这里定义一个 heap_bound 
    // 来确定堆的范围
    int heap_bound = size - i;
    HeapPop(array, heap_bound);
  }
  return;
}

///////////////////////////////////////////////////////////
// 希尔排序
// 时间复杂度 ：希尔排序的时间复杂度取决于步长 gap 的设定，
//              对于希尔序列来说，时间复杂度为 O(N ^ 2)，
//              如果选择最优序列可以达到 O(N ^ 1.3)
// 空间复杂度 ：O(1)
// 排序稳定程度 ：不稳定
///////////////////////////////////////////////////////////

void ShellSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }
  // 这里利用希尔序列作为希尔排序的步长 
  // 希尔序列 2 4 8 16...
  int gap = size;
  
  // 注：在使用步长时，一定要从 size 开始向下除
  // 不能用 2^N 这样来计算
  // 因为不一定 2^N 刚好等于 size
  
  for (; gap > 0; gap /= 2) { 
    int cur = 0;
    for(; cur < gap; ++cur) {
      int bound = cur + gap;
      for(; bound < size; bound += gap) {
        int bound_value = array[bound];
        int index = bound - gap;
        while (index >= 0 && bound_value < array[index]) {
          array[index + gap] = array[index];
          index -= gap;
        }
        array[index + gap] = bound_value;
      } // end for (; bound < size; ++bound)
    }
  } // end for (; gdp <= size; gap *= 2)
  return;
}

///////////////////////////////////////////////////////////
// 归并排序
// 时间复杂度 ：O(N * log N)
// 空间复杂度 ：O( N )
// 排序稳定程度 ：稳定 (其实归并排序的稳定程度由代码可以控制)
///////////////////////////////////////////////////////////

void MergeArray(int array[], int beg, int mid, int end, int* tmp)
{
  int index = beg;
  int cur1 = beg;
  int cur2 = mid;
  while (cur1 < mid && cur2 < end) {
    if (array[cur1] < array[cur2]) {
      tmp[index++] = array[cur1++];
    } else {
      tmp[index++] = array[cur2++];
    }
  }
  while (cur1 < mid) {
    tmp[index++] = array[cur1++];
  }
  while (cur2 < end) {
    tmp[index++] = array[cur2++];
  }
  memcpy(array + beg, tmp + beg, (end - beg)*sizeof(int));
  return;
}

void _MergeSort(int array[], int beg, int end, int* tmp)
{
  if (beg >= end - 1) {
    return;
  }

  int mid = beg + (end - beg) / 2;
  _MergeSort(array, beg, mid, tmp);
  _MergeSort(array, mid , end, tmp);
  MergeArray(array, beg, mid, end, tmp);
}

void MergeSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }
  
  int* tmp = (int*)malloc(sizeof(int) * size);
  _MergeSort(array, 0, size, tmp);
  free(tmp);
  tmp = NULL;
}

///////////////////////////////////////////////////////////
// 快速排序
// 时间复杂度 ：快速排序的时间复杂度平均为 O(N * log N) 最坏情况下是 O(N ^ 2)
// 空间复杂度 ：空间复杂度最坏情况下是 O(N)
// 排序稳定程度 : 不稳定
///////////////////////////////////////////////////////////

int DigValue(int array[], int beg, int end) // 挖坑法
{
  int cur_value = array[end];
  int left = beg;
  int right = end;

  while (left < right) {
    while (left < right && array[left] <= cur_value) {
      ++left;
    }
    if (left < right) {
      array[right] = array[left];
      --right;
    }
    
    while (left < right && array[right] >= cur_value) {
      --right;
    }
    if (left < right) {
      array[left] = array[right];
      ++left;
    }
  }
  array[right] = cur_value;
  return right;
}

int ExchangeValue(int array[], int beg, int end) // 左右指针交换法
{
  int cur_value = array[end];
  int left = beg;
  int right = end;

  while (left < right) {
    while (left < right && array[left] <= cur_value) {
      ++left;
    }
    while (left < right && array[right] >= cur_value) {
      --right;
    }
    if (left < right) {
      Swap(&array[left], &array[right]);
    }
  }
  Swap(&array[left], &array[end]);
  return left;
}

void _QuickSort(int array[], int beg, int end)
{
  if (beg >= end) {
    return;
  }

  int mid = ExchangeValue(array, beg, end);
  // int mid = DigValue(array, beg, end);
  _QuickSort(array, beg, mid - 1);
  _QuickSort(array, mid + 1, end);
  return;
}

void QuickSort(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  int beg = 0;
  int end = size - 1;
  _QuickSort(array, beg, end);
  return;
}

///////////////////////////////////////////////////////////
// 非递归版本的归并排序
///////////////////////////////////////////////////////////

void MergeSortByLoop(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  int size_bound = 1;
  int* tmp = (int*)malloc(sizeof(int) * size);
  for (; size_bound < size; size_bound *= 2) {
    int i = 0;
    for (; i < size; i += 2 * size_bound) {
      int beg = i;
      int mid = beg + size_bound;
      int end = mid + size_bound;
      
      // 如果此时的 mid 超过了 size 
      // 那么就意味着此时的区间只剩下了一个
      // 即 [beg, mid) 那么这个时候 
      // mid 需要置为 size 防止越界
      if (mid >= size) { 
        mid = size;
      }
      
      // 这里同理，如果 end 超过了 size 
      // 那么就是第二段的区域的元素个数低于第一段
      // 也需要将 end 置为 size
      if (end >= size) {
        end = size;
      }
      MergeArray(array, beg, mid, end, tmp);
    } // end for (; i < size; i += 2 * size_bound)
  }
  return;
}

///////////////////////////////////////////////////////////
// 非递归版本的归并排序
///////////////////////////////////////////////////////////

void QuickSortByLoop(int array[], int size)
{
  if (size <= 1) {
    return;
  }

  SeqStack stack;
  SeqStackInit(&stack);
  int beg = 0;
  int end = size - 1;
  SeqStackPush(&stack, beg);
  SeqStackPush(&stack, end);

  while (1) {
    int ret = SeqStackGetFront(&stack, &end);
    if (ret == 0) {
      break;
    }
    SeqStackPop(&stack);
    SeqStackGetFront(&stack, &beg);
    SeqStackPop(&stack);

    int mid = ExchangeValue(array, beg, end);
    SeqStackPush(&stack, beg);
    SeqStackPush(&stack, mid - 1);
    SeqStackPush(&stack, mid + 1);
    SeqStackPush(&stack, end);
  }
  return;
}

/////////////////////////////////////////////////////////
// 测试代码
/////////////////////////////////////////////////////////

#if 0

void SortPrint(int array[], int size)
{
  int i = 0;
  for (; i < size; ++i) {
    printf("%d ",array[i]);
  }
  printf("\n");
  return;
}
 
int main()
{
  int array[10] = {3,4,1,7,4,8,9,5,2,0};
  int size = sizeof(array)/sizeof(array[0]);

  // BubbleSort(array, size); // 测试冒泡排序
  // SelectSort(array, size); // 测试选择排序
  // InsertSort(array, size); // 测试插入排序
  // HeapSort(array, size); // 测试堆排序
  // ShellSort(array, size); // 测试希尔排序
  // MergeSort(array, size); // 测试归并排序
  // QuickSort(array, size); // 测试快速排序
  // MergeSortByLoop(array, size); // 测试归并排序非递归版本
  // QuickSortByLoop(array, size); // 测试快速排序非递归版本

  SortPrint(array, size); // 为了测试方便，利用打印查看排序的结果

  return 0;
}

#endif

