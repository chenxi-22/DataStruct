#pragma once

#include <stddef.h>

#define Seqtype	char

#define SeqListMax 1000

typedef struct SeqList{
	Seqtype data[SeqListMax];
	size_t size;
}SeqList;

//以下为函数声明

void SeqListPrint( SeqList* seqlsit);//打印顺序表

void SeqListInit( SeqList* seqlist);//初始化顺序表

void SeqListPushBack( SeqList* seqlist, Seqtype value);//在顺序表尾部插入一个元素 

void SeqListPopBack( SeqList* seqlist);//在顺序表尾部删除一个元素

void SeqListPushFront( SeqList* seqlist, Seqtype value);//在顺序表头部插入一个元素

void SeqListPopFront( SeqList* seqlist);//在顺序表头部删除一个元素

void SeqListInsert( SeqList* seqlist, size_t pos, Seqtype value);//在顺序表pos位置插入一个元素

void SeqListErase( SeqList* seqlist, size_t pos);//在顺序表的pos位置删除一个元素

int SeqListGet( SeqList* seqlist, size_t pos, Seqtype* value);//在顺序表中获取pos位置的元素

void SeqListChange( SeqList* seqlist, size_t pos, Seqtype value);//在顺序表中修改pos位置的元素

size_t SeqListFind( SeqList* seqlist, Seqtype value);//在顺序表中查找指定元素的下标(只找第一次出现的)

void SeqListRemove( SeqList* seqlist,Seqtype value);//在顺序表中删除value，只删除第一次出现的

void SeqListRemoveAll( SeqList* seqlist, Seqtype value);//在顺序表中删除value，删除所有出现的

void SeqListRemoveAllEX( SeqList* seqlist, Seqtype value);//在顺序表中删除value，删除所有出现的

void SeqListBubbleSort( SeqList* seqlist);//冒泡排序顺序表内的元素

typedef int (*Cmp)( Seqtype, Seqtype);

void SeqListBubbleSortEX( SeqList* seqlist, Cmp cmp);//冒泡排序顺序表内的元素
