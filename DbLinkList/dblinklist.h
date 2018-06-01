#pragma once

#include <stddef.h>

typedef char DbLinkType;

typedef struct DbLinkNode{
  DbLinkType data;
  struct DbLinkNode* prev;
  struct DbLinkNode* next;
}DbLinkNode;

DbLinkNode* DbCreat(DbLinkType value);//创建新的双链表节点

void DbLinkInit(DbLinkNode** phead);//初始化双链表

void DbLinkPrint(DbLinkNode* head);//打印双链表

void DbLinkPushBack(DbLinkNode* head, DbLinkType value);//尾部插入

void DbLinkPushFront(DbLinkNode* head, DbLinkType value);//头部插入

void DbLinkPopBack(DbLinkNode* head);//尾部删除

void DbLinkPopFront(DbLinkNode* head);//头部删除

DbLinkNode* DbLinkFind(DbLinkNode* head, DbLinkType to_find);//查找某个元素

void DbLinkInsert(DbLinkNode* pos, DbLinkType value);//在pos位置之前插入一个元素

void DbLinkInsertAfter(DbLinkNode* pos,DbLinkType value);//在pos位置之后插入一个元素

void DbLinkErase(DbLinkNode* head,DbLinkNode* pos);//删除pos位置元素

void DbLinkRemove(DbLinkNode* head,DbLinkType to_delete);//删除双链表元素，只删除第一次出现的

void DbLinkRemoveAll(DbLinkNode* head,DbLinkType to_delete);//删除链表中所有to_delete

size_t DbLinkSize(DbLinkNode* head);//计算链表大小

int DbLinkEmpty(DbLinkNode* head);//判断链表是否为空






