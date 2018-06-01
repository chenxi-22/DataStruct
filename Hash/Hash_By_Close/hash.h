#pragma once

#include <stddef.h>

#define HASHMAXSIZE 1000

typedef int Keytype;
typedef int Valtype;

typedef size_t (*HashFun)(Keytype key);

typedef struct HashElem {
  Keytype key;
  Valtype val;
  struct HashElem* next;
} HashElem;

typedef struct HashTable {
  HashElem* data[HASHMAXSIZE];
  size_t size;
  HashFun fun;
} HashTable;

void HashInit(HashTable* ht, HashFun fun);//初始化哈希表

void HashInsert(HashTable* ht, Keytype key, Valtype val);//插入哈希表

void HashDestroy(HashTable* ht);//销毁哈希表

void HashRemove(HashTable* ht, Keytype key);//删除哈希表指定元素

int HashFind(HashTable* ht, Keytype key, Valtype* val);//查找哈希表内元素



