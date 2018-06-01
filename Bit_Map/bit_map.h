#pragma once

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define BitMapType uint64_t

typedef struct BitMap {
  BitMapType* data;
  uint64_t capacity;
} BitMap;//定义位图

void BitMapInit(BitMap* bm);//初始化位图

void BitMapSet(BitMap* bm, uint64_t index);//设置某一位为1

void BitMapUnSet(BitMap* bm, uint64_t index);//设置某一位为0

int BitMapTest(BitMap* bm, uint64_t index);//测验某一位是不是1

void BitMapDestroy(BitMap* bm);//销毁位图

void BitMapFill(BitMap* bm);//全部置为1

void BitMapEmpty(BitMap* bm);//全部置为0
