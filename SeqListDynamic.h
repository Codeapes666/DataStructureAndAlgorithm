#include <stdio.h>
#include <stdlib.h>

#define InitSize 100	 // 定义线性表的初始长度
#define OK 0
#define ERROR 1

typedef int ElemType;

typedef struct 
{
	ElemType* data;		// 动态分配数组的指针		
	int MaxSize;	    // 线性表的最大容量
    int length;         // 线性表的当前长度
} SeqList;				// 动态分配数组顺序表的类型定义

// 初始化顺序表
int InitList(SeqList* L)
{
    L->data = (ElemType*)malloc(sizeof(ElemType) * InitSize);

    // 判断内存是否分配成功
    if (!(L->data)) {
        return ERROR;
    }

    // 内存分配成功，开始是空表，故长度置为0
    L->length = 0;

    // 初始化表的存储容量，即当前表最大的存储量
    L->MaxSize = InitSize;
}

// 求顺序表长度
int Length(SeqList L)
{
	return L.length;
}

// 插入操作
// 在顺序表L的第i（1 ≤ i ≤ length + 1）个位置插入新元素e
// 插入成功返回OK，插入失败返回ERROR
int ListInsert(SeqList* L, int i, ElemType e) 
{
    SeqList* pList;

    if (i < 1 || i > L->length + 1) {		// 判断i的范围是否有效
		return ERROR;
	}

	if (L->length >= L->MaxSize) {			
		
        pList->data = (ElemType*)realloc(L->data, (L->MaxSize + InitSize) * sizeof(ElemType)); 

        if (!(pList->data)) {
            return ERROR;
        }

        L->data = pList->data;
        L->MaxSize += InitSize;
    }
    if (i != L->length + 1) {
        for (int j = L->length - 1; j >= i - 1; --j) {
            *(L->data + j + 1) = *(L->data + j);
            // L->data[j + 1] = L->data[j];
        }
    }

    *(L->data + i - 1) = e;
    // L->data[i - 1] = e;

    ++L->length;

    return OK;

}

// 删除操作
// 删除顺序表L中第i（1 ≤ i ≤ length）个位置的元素
// 删除成功返回OK，删除失败返回ERROR。如删除成功，用e返回删除元素的值
int ListDelete(SeqList* L, int i, ElemType* e) 
{
    if (i < 1 || i > L->length) {			        // 判断i的范围是否有效
		return ERROR;
	}

    *e = *(L->data + i -1);
    // *e = L->data[i - 1];

    for (int j = i; j < L->length; ++j) {
		*(L->data + j - 1) = *(L->data + j);        // 将第i个位置之后的元素前移
        // L->data[j - 1] = L->data[j];
	}

	--L->length;							        // 线性表长度减1

	return OK;
}

// 按值查找
// 在顺序表L中查找第一个值等于e的元素，并返回其位序
int LocateElem(SeqList L, ElemType e) 
{
    if (L.length == 0) {
        return ERROR;
    }

    int i = 0;
	for (i = 0; i < L.length; ++i) {
		if (*(L.data + 1) == e) {
			return i + 1;					// 下表为i的元素等于e，返回其位序i+1
		}
	}

	return ERROR;							// 退出循环，说明查找失败
}

// 按位查找
// 获取表L中第i个位置的元素值
int GetElem(SeqList L, int i ,ElemType* e) 
{
    if (L.length == 0) {
        return ERROR;
    }
	if (i < 1 || i > L.length) {
		return ERROR;
	}

    *e = *(L.data + i - 1);

	return OK;
}

// 输出操作
int PrintList(SeqList L)
{
	if (L.length == 0) {
		return ERROR;
	}

    int i = 0;
	for (i = 0; i < L.length; ++i) {
		printf("data[%d] = %d\n", i, *(L.data + i));
	}

	printf("\n");

	return OK;
}

// 判空操作
int Empty(SeqList L)
{
	if (L.length == 0) {
		return OK;
	}

	return ERROR;
}

// 销毁操作
// 用malloc函数分配的空间在释放时是连续释放的，即将物理地址相邻的若干空间全部释放
// 所以顺序表销毁可以只释放基址，就会自动释放所有空间，而链表要一个一个的把节点删除
int DestroyList(SeqList* L)
{
    // 若当前表为空，直接return
    if (!(L->data)) {
        return ERROR;
    }

    // 释放内存
    free(L->data);

    // 指针置空
    L->data = NULL;

    return OK;
}

// 合并线性表A与B，时间复杂度O(lengthA x lengthB)
// 把在线性表B里，但不存在于线性表A的元素插入到A中，只改变A，不修改B
void Union(SeqList* SeqLA, SeqList SeqLB)
{
    int lengthA = SeqLA->length;
    int lengthB = SeqLB.length;

    // 在B里依次取每个数据元素，顺序在A中进行比较，若不存在则插入
    int i = 0;
    int e = 0;
    for (i = 1; i <= lengthB; ++i) {
        GetElem(SeqLB, i, &e);

        // 若A里没有这个元素
        if (!LocateElem(*SeqLA, e)) {
            
            // 插入到A的尾部
            // lengthA++;
            // ListInsert(SeqLA, lengthA, e);
            ListInsert(SeqLA, ++lengthA, e);
        }
    }

    DestroyList(&SeqLB);
}

// 合并线性表A与B，时间复杂度O(lengthA + lengthB)
// A、B的元素按值非递减有序的排列，要把A和B归并为一个新表C，
// 且C的元素依然是按照值非递减的有序排列
void MergeList(SeqList SeqLA, SeqList SeqLB, SeqList* SeqLC)
{
    //构造新表C
    InitList(SeqLC);

    int lengthA = SeqLA.length;
    int lengthB = SeqLB.length;
    int lengthC = SeqLC->length;

    int i = 1;          // i标记SeqLA
    int j = 1;          // j标记SeqLB
    int iSeqLA = 0;     // A表中的元素值
    int jSeqLB = 0;     // B表中的元素值

    while ((i <= lengthA) && (j <= lengthB)) {
        // 分别取得元素值，比较
        GetElem(SeqLA, i, &iSeqLA);
        GetElem(SeqLB, j, &jSeqLB);

        // SeqLA，SeqLB都是非递减排列
        if (iSeqLA <= jSeqLB) {
            // 总在末尾插入
            ListInsert(SeqLC, ++lengthC, iSeqLA);
            ++i;
        } else {
            ListInsert(SeqLC, ++lengthC, jSeqLB);
            ++j;
        }
    }

    // A、B不会同时比完，一定会有一个表完全插入到c之后，另一个表还有剩余
    while (i <= lengthA) {
        GetElem(SeqLA, i++, &iSeqLA);

        // 本来A、B就有序，直接全部插入到C末尾即可
        ListInsert(SeqLC, ++lengthC, iSeqLA);
    }
    
    while (j <= lengthB)
    {
        GetElem(SeqLB, j++, &jSeqLB);
        ListInsert(SeqLC, ++lengthB, jSeqLB);
    }
}