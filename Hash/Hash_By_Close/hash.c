#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#define HEAD printf("\n===============%s=============\n",__FUNCTION__)

size_t Function(Keytype key) {
  return key % HASHMAXSIZE;
}

void HashInit(HashTable* ht, HashFun fun)//初始化哈希表
{
  if(ht == NULL) {
    return;
  }
  ht->size = 0;
  ht->fun = fun;

  size_t i = 0;
  for(; i < HASHMAXSIZE; ++i) {
    ht->data[i] = NULL;
  }
  return;
}

HashElem* CreateElem(Keytype key, Valtype val)
{
  HashElem* new_elem = (HashElem*)malloc(sizeof(HashElem));
  new_elem->key = key;
  new_elem->val = val;
  new_elem->next = NULL;
  return new_elem;
}

void HashInsert(HashTable* ht, Keytype key, Valtype val)//插入哈希表
{
  if(ht == NULL) {
    return;
  }
  size_t offset = ht->fun(key);
  HashElem* cur = ht->data[offset];
  while(cur != NULL) {
    if(cur->key == key) {
      return;
    }
    cur = cur->next;
  }
  HashElem* new_elem = CreateElem(key, val);
  new_elem->next = ht->data[offset];
  ht->data[offset] = new_elem;
  ++ht->size;
  return;
}

void Destroy(HashElem* cur)
{
  free(cur);
  cur = NULL;
}

void HashDestroy(HashTable* ht)//销毁哈希表
{
  if(ht == NULL) {
    return;
  }
  if(ht->size == 0) {
    return;
  }
  size_t i = 0;
  for(; i < HASHMAXSIZE; ++i) {
    HashElem* cur = ht->data[i];
    if(cur == NULL) {
      continue;
    }
    while(cur != NULL) {
      HashElem* pre = cur;
      Destroy(cur);
      cur = pre->next;
    }
  }
  ht->size = 0;
  ht->fun = NULL;
  return;
}

void HashRemove(HashTable* ht, Keytype key)//删除哈希表指定元素
{
  if(ht == NULL) {
    return;
  }

  size_t offset = ht->fun(key);
  HashElem* cur = ht->data[offset];
  HashElem* pre = NULL;

  while(cur != NULL) {
    if(cur->key == key) {
      break;
    }
    pre = cur;
    cur = cur->next;
  }
  if(cur == NULL) {
    return;
  }
  if(pre == NULL) {
    HashElem* tmp = ht->data[offset];
    ht->data[offset] = tmp->next;
    Destroy(tmp);
  } else {
    pre->next = cur->next;
    Destroy(cur);
  }
  return;
}

int HashFind(HashTable* ht, Keytype key, Valtype* val)//查找哈希表内元素
{
  if(ht == NULL) {
    return 0;
  }
  if(ht->size == 0) {
    return 0;
  }
  size_t offset = ht->fun(key);
  HashElem* cur = ht->data[offset];
  while(cur != NULL) {
    if(cur->key == key) {
      *val = cur->val;
      return 1;
    }
    cur = cur->next;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////
//测试代码
///////////////////////////////////////////////////////////////////////

void HashPrintInt(HashTable* ht, char* msg)
{
  printf("%s\n",msg);
  size_t i = 0;
  for(; i < HASHMAXSIZE; ++i) {
    HashElem* cur = ht->data[i];
    if(cur == NULL) {
      continue;
    }
    while(cur != NULL) {
      printf("%lu->[%d|%d]  ", i, cur->key, cur->val);
      cur = cur->next;
    }
  }
  printf("\n");
  return;
}

void TestDestroy()
{
  HEAD;
  HashTable ht;
  HashInit(&ht, Function);
  HashInsert(&ht, 1, 11);
  HashInsert(&ht, 1, 123);
  HashInsert(&ht, 1001, 15);
  HashInsert(&ht, 2, 13);
  HashInsert(&ht, 1002, 122);

  HashDestroy(&ht);
  printf("size expected 0, size actual %lu\n", ht.size);
  printf("fun expected NULL, size actual %p\n", ht.fun);
}

void TestInsert()
{
  HEAD;
  HashTable ht;
  HashInit(&ht, Function);
  HashInsert(&ht, 1, 11);
  HashInsert(&ht, 1, 123);
  HashInsert(&ht, 1001, 15);
  HashInsert(&ht, 2, 13);
  HashInsert(&ht, 1002, 122);

  HashPrintInt(&ht, "插入五个元素：");
}

void TestRemove()
{
  HEAD;
  HashTable ht;
  HashInit(&ht, Function);
  HashInsert(&ht, 1, 11);
  HashInsert(&ht, 1, 123);
  HashInsert(&ht, 1001, 15);
  HashInsert(&ht, 2, 13);
  HashInsert(&ht, 1002, 122);

  HashRemove(&ht, 1);
  HashRemove(&ht, 2);
  HashRemove(&ht, 2);
  HashPrintInt(&ht, "删除三个元素：");
}

void TestFind()
{
  HEAD;
  HashTable ht;
  HashInit(&ht, Function);
  HashInsert(&ht, 1, 11);
  HashInsert(&ht, 1, 123);
  HashInsert(&ht, 1001, 15);
  HashInsert(&ht, 2, 13);
  HashInsert(&ht, 1002, 122);

  Valtype val;
  int ret = HashFind(&ht, 1, &val);
  printf("ret expected 1, ret actual %d\n",ret);
  printf("val expected 11, val actual %d\n",val);
  ret = HashFind(&ht, 3, &val);
  printf("ret expected 0, ret actual %d\n",ret);
}

int main()
{
  TestInsert();
  TestDestroy();
  TestRemove();
  TestFind();

  return 0;
}
