#include "SeqList.h"
#include <stdio.h>

#define HEAD printf("----------%s----------\n",__FUNCTION__)

void SeqListPrint( SeqList* seqlist)//打印顺序表
{
	if( NULL == seqlist )
	{
		//非法输入
		return;
	}
	printf("顺序表中元素有%lu个 \n",seqlist->size);

	if( 0 == seqlist->size)
	{
		return;
	}

	size_t i = 0;
	for( ; i < seqlist->size; ++i)
	{
		printf("[%c] ",seqlist->data[i]);
	}
	printf("\n");
}

void SeqListInit(SeqList* seqlist)//初始化顺序表
{
	if( NULL == seqlist )
	{   //非法输入
		return;
	}

	seqlist->size = 0;
}


void SeqListPushBack( SeqList* seqlist , Seqtype value)//在顺序表尾插入
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}

	if( seqlist->size >= SeqListMax)//判断顺序表是否满
	{
		printf("顺序表已满\n");
		return;
	}

	++seqlist->size;
	seqlist->data[seqlist->size-1] = value;
}

void SeqListPopBack( SeqList* seqlist)//在顺序表尾部删除一个元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}

	if( 0 == seqlist->size)
	{
		printf("该顺序表为空顺序表\n");//判断该顺序表是否为空顺序表
		return;
	}

	--seqlist->size;
}

void SeqListPushFront( SeqList* seqlist, Seqtype value)//在顺序表头部插入一个元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}

	if( seqlist->size >= SeqListMax)//判断顺序表是否已满
	{
		printf("顺序表已满\n");
		return;
	}

	++seqlist->size;
	size_t i = seqlist->size-1;

	for( ; i > 0; --i)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[0] = value;
}

void SeqListPopFront( SeqList* seqlist)//在顺序表头部删除一个元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	if( 0 == seqlist->size)//判断顺序表是否为空顺序表
	{
		printf("该顺序表为空顺序表\n");
		return;
	}

	size_t i = 0;

	for( ; i < seqlist->size; ++i)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	--seqlist->size;
}

void SeqListInsert( SeqList* seqlist, size_t pos, Seqtype value)//在顺序表pos位置插入一个元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	if( seqlist->size >= SeqListMax)//判断顺序表是否已满
	{
		printf("该顺序表已满\n");
		return;
	}
	if( pos > seqlist->size)//判断插入位置是否合适
	{
		printf("插入位置越界\n");
		return;
	}

	if( 0 == pos)
	{
		SeqListPushFront(seqlist, value);
		return;
	}

	++seqlist->size;
	size_t i = seqlist->size-1;

	for( ; i-1 >= pos; --i)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[pos] = value;
}

void SeqListErase( SeqList* seqlist, size_t pos)//在顺序表的pos位置删除一个元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	if( 0 == seqlist->size)
	{
		printf("该顺序表是空顺序表\n");
		return;
	}
	if( pos >= seqlist->size)
	{
		printf("删除位置越界\n");
		return;
	}
	
	size_t i = pos;
	
	for( ; i+1 < seqlist->size; ++i)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	--seqlist->size;
}	

int SeqListGet( SeqList* seqlist, size_t pos, Seqtype* value)//在顺序表中获取pos位置的元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return 0;
	}
	if( pos >= seqlist->size)
	{
		return 0;
	}
	*value = seqlist->data[pos];
	return 1;
}

void SeqListChange( SeqList* seqlist, size_t pos, Seqtype value)//在顺序表中修改pos位置的元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	if( pos >= seqlist->size)
	{
		printf("无法修改越界位置的元素\n");
		return;
	}

	seqlist->data[pos] = value;
}

size_t SeqListFind( SeqList* seqlist, Seqtype value)//在顺序表中查找指定元素的下标(只找第一次出现的)
{
	if( NULL == seqlist)
	{
		//非法输入
		return -1;
	}
	size_t i = 0;

	for( ; i < seqlist->size; ++i)
	{
		if( value == seqlist->data[i])
		{
			return i;
		}
	}
	return (size_t)-1;
}

void SeqListRemove( SeqList* seqlist,Seqtype value)//在顺序表中删除value，只删除第一次出现的
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	size_t pos = SeqListFind(seqlist,value);	
	SeqListErase(seqlist,pos);
}

void SeqListRemoveAll( SeqList* seqlist, Seqtype value)//在顺序表中删除value，删除所有出现的
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	while(1)
	{
		if( -1 == (int)SeqListFind(seqlist,value))
		{
			break;
		}
		size_t pos = SeqListFind(seqlist,value);
		SeqListErase(seqlist,pos);
	}
}

void SeqListRemoveAllEX( SeqList* seqlist, Seqtype value)//在顺序表中删除value，删除所有出现的
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	size_t i = 0;

	for( ; i < seqlist->size; ++i)
	{
		if( value == seqlist->data[i])
		{
			SeqListErase(seqlist,i);
			i--;
		}
	}
}

void SeqListSwap(Seqtype* a,Seqtype* b)
{
	Seqtype tmp = *a;
	*a = *b;
	*b = tmp;
}

void SeqListBubbleSort( SeqList* seqlist)//冒泡排序顺序表内的元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	size_t i = 0;
	size_t j = 0;

	for( ; i < seqlist->size-1; ++i)
	{
		for( j = 0 ; j < seqlist->size-1-i; j++)
		{
			if(seqlist->data[j] > seqlist->data[j+1])
			{
				SeqListSwap(&seqlist->data[j],&seqlist->data[j+1]);
			}
		}
	}
}

int Greater(Seqtype a, Seqtype b)
{
	return a>b?1:0;
}

int Less(Seqtype a, Seqtype b)
{
	return a<b?1:0;
}

void SeqListBubbleSortEX( SeqList* seqlist, Cmp cmp)//冒泡排序顺序表内的元素EX
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	size_t i = 0;
	size_t j = 0;

	for( ; i < seqlist->size-1; ++i)
	{
		for( j = 0 ; j < seqlist->size-1-i; j++)
		{
			if(cmp(seqlist->data[j], seqlist->data[j+1]))
			{
				SeqListSwap(&seqlist->data[j],&seqlist->data[j+1]);
			}
		}
	}
}

void SeqListSelectSort( SeqList* seqlist)//选择排序顺序表内元素
{
	if( NULL == seqlist)
	{
		//非法输入
		return;
	}
	if(seqlist->size == 1)
	{
		return;
	}

	size_t count = 0;
	for( ; count < seqlist->size; ++count)
	{
		size_t cur = count+1;
		for( ; cur < seqlist->size; ++cur)
		{
			if(seqlist->data[count] > seqlist->data[cur])
			{
				SeqListSwap(&seqlist->data[count],&seqlist->data[cur]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//测试代码
//////////////////////////////////////////////////////////////////////////////////////////////

void TestSeqPushBack()//测试顺序表尾部插入函数
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListPushBack(&seqlist,'g');
	SeqListPrint(&seqlist);
}

void TestSeqInit()//测试顺序表初始化函数
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPrint(&seqlist);
}

void TestSeqPopBack()//测试顺序表尾部删除一个元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPopBack(&seqlist);
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListPrint(&seqlist);
}

void TestSeqPushFront()//测试顺序表头部插入一个元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist, 'z');
	SeqListPrint(&seqlist);
}

void TestSeqPopFront()//测试顺序表头部删除一个元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPopFront(&seqlist);
	SeqListPrint(&seqlist);
}

void TestSeqInsert()//测试顺序表pos位置插入一个元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListInsert(&seqlist, 0, 'u');
	SeqListPrint(&seqlist);
}

void TestSeqErase()//测试删除顺序表pos位置的元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListPushFront(&seqlist, 'z');
	SeqListErase(&seqlist, 0);
	SeqListErase(&seqlist, 10);
	SeqListPrint(&seqlist);
}

void TestSeqGet()//测试获取顺序表中pos位置的元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	Seqtype value;
	int ret = SeqListGet(&seqlist, 3, &value);
	printf("如果找到返回1，没找到返回0\n");
	printf("%d\n",ret);
	int ret1 = SeqListGet(&seqlist, 9, &value);
	printf("%d\n",ret1);
}

void TestSeqChange()//测试修改顺序表中pos位置的元素
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListPushBack(&seqlist,'a');
	SeqListChange(&seqlist, 3, '8');
	SeqListChange(&seqlist, 10, '8');
	SeqListPrint(&seqlist);
}

void TestSeqFind()//测试查找顺序表中指定元素的下标
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	printf("如果找到返回下标，如果没找到返回-1\n");
	size_t ret = SeqListFind(&seqlist, '0');
	printf("%ld\n",ret);
	ret = SeqListFind(&seqlist, 'c');
	printf("%lu\n",ret);
}

void TestRemove()//测试给元素内容，来删除元素，只删除第一个出现的
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListRemove(&seqlist, 'a');
	SeqListPrint(&seqlist);
}

void TestRemoveAll()//测试给元素内容，来删除元素，删除所有
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListRemoveAll(&seqlist,'a');
	SeqListPrint(&seqlist);
}

void TestRemoveAllEX()//测试给元素内容，来删除元素，删除所有EX
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListRemoveAllEX(&seqlist,'a');
	SeqListPrint(&seqlist);
}

void TestBubbleSort()//测试冒泡排序
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'z');
	SeqListPushBack(&seqlist,'x');
	SeqListPushBack(&seqlist,'t');
	SeqListPushBack(&seqlist,'m');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListBubbleSort(&seqlist);
	SeqListPrint(&seqlist);
}

void TestBubbleSortEX()//测试冒泡排序EX
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'z');
	SeqListPushBack(&seqlist,'x');
	SeqListPushBack(&seqlist,'t');
	SeqListPushBack(&seqlist,'m');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListBubbleSortEX(&seqlist, Greater);
	SeqListPrint(&seqlist);
	SeqListBubbleSortEX(&seqlist, Less);
	SeqListPrint(&seqlist);
	
}

void TestSelectSort()
{
	HEAD;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'z');
	SeqListPushBack(&seqlist,'x');
	SeqListPushBack(&seqlist,'t');
	SeqListPushBack(&seqlist,'m');
	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'e');
	SeqListPushBack(&seqlist,'f');
	SeqListSelectSort(&seqlist);	
	SeqListPrint(&seqlist);
}

void Test()//测试函数
{
	TestSeqInit();
	TestSeqPushBack();
	TestSeqPopBack();
	TestSeqPushFront();
	TestSeqPopFront();
	TestSeqInsert();
	TestSeqErase();
	TestSeqGet();
	TestSeqChange();
	TestSeqFind();
	TestRemove();
	TestRemoveAll();
	TestRemoveAllEX();
	TestBubbleSort();
	TestBubbleSortEX();
	TestSelectSort();
}

int main()
{
	Test();
	
	return 0;
}
