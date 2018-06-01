#include "bit_map.h"

#define HEAD printf("\n================%s===============\n",__FUNCTION__)

#define BitMapSize 100

uint64_t GetSize(uint64_t index)
{
  return index /(sizeof(BitMapType) * 8) + 1;
}

void BitMapInit(BitMap* bm)//初始化位图
{
  if(bm == NULL) {
    return;
  }
  bm->capacity = BitMapSize;
  uint64_t size = GetSize(bm->capacity);
  bm->data = (BitMapType*)malloc(sizeof(BitMapType) * size);
  memset(bm->data, 0, sizeof(BitMapType) * size);
  return;
}

//这里规定返回为0的时候测验失败。
//返回值为1的时候测试成功
int BitMapTest(BitMap* bm, uint64_t index)//测验某一位是不是1
{
  if(bm == NULL) {
    return 0;
  }
  uint64_t offset = GetSize(index);
  uint64_t size = index % (sizeof(BitMapType) * 8);

  uint64_t ret = (bm->data[offset] & (0x1ul << size));
  return ret > 0 ? 1 : 0;
}

void BitMapSet(BitMap* bm, uint64_t index)//设置某一位为1
{
  if(bm == NULL) {
    return;
  }
  //这里规定：
  //如果设置的位数高于总位数，那么这个时候设置失败
  if(index > bm->capacity) {
    return;
  }
  uint64_t offset = GetSize(index);
  uint64_t size = index % (sizeof(BitMapType) * 8);

  bm->data[offset] |= (0x1ul << size);
  return;
}

void BitMapUnSet(BitMap* bm, uint64_t index)//设置某一位为0
{
  if(bm == NULL) {
    return;
  }
  uint64_t offset = GetSize(index);
  uint64_t size = index % (sizeof(BitMapType) * 8);

  bm->data[offset] &= ~(0x1ul << size);
  return;
}

void BitMapDestroy(BitMap* bm)//销毁位图
{
  if(bm == NULL) {
    return;
  }
  bm->capacity = 0;
  free(bm->data);
  bm->data = NULL;
  return;
}

void BitMapFill(BitMap* bm)//全部置为1
{
  if(bm == NULL) {
    return;
  }
  memset(bm->data, 0xff, bm->capacity);
  return;
}

void BitMapEmpty(BitMap* bm)//全部置为0
{
  if(bm == NULL) {
    return;
  }
  memset(bm->data, 0, bm->capacity);
  return;
}

//////////////////////////////////////////////////////////////
//测试代码
//////////////////////////////////////////////////////////////

#if 1

void TestSet()
{
  HEAD;
  BitMap bm;
  BitMapInit(&bm);
  BitMapSet(&bm, 55);
  BitMapSet(&bm, 101);
  int ret = BitMapTest(&bm,101);
  printf("ret expected 0, actual %d\n",ret);

  ret = BitMapTest(&bm,55);
  printf("ret expected 1, actual %d\n",ret);
}

void TestUnSet()
{
  HEAD;
  BitMap bm;
  BitMapInit(&bm);
  BitMapSet(&bm, 55);
  int ret = BitMapTest(&bm,55);
  printf("ret expected 1, actual %d\n",ret);

  BitMapUnSet(&bm, 55);
  ret = BitMapTest(&bm,55);
  printf("ret expected 0, actual %d\n",ret);
}

void TestTest()
{
  HEAD;
  BitMap bm;
  BitMapInit(&bm);
  BitMapFill(&bm);
  int ret = BitMapTest(&bm,55);
  printf("ret expected 1, actual %d\n",ret);
  BitMapEmpty(&bm);
  ret = BitMapTest(&bm,55);
  printf("ret expected 0, actual %d\n",ret);
}

int main()
{
  TestSet();
  TestUnSet();
  TestTest();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");

  return 0;
}

#endif

