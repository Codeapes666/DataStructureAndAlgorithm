#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXQSIZE    100             // 队列可能达到的最大长度
#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

Status Visit (ElemType e)
{
    printf("%d ", e);

    return OK;
}

// 队列的顺序存储结构
typedef struct 
{
    ElemType* base;                 // 存储空间的基地址
    int front;                      // 头指针
    int rear;                       // 尾指针
} SeqQueue;

// 为了解决“假溢出”问题，一个较巧妙的办法是将顺序队列变为一个环状空间，即循环队列
// 区分队空队满的两种处理方式：
// 1. 牺牲一个单元来区分队空和队满。
// 2. 类型中增设表示元素个数的数据成员。

// 队列的初始化
Status InitQueue (SeqQueue* Q)
{   
    // 为队列分配一个空间
    Q->base = (ElemType*)malloc(sizeof(ElemType) * MAXQSIZE);

    if (Q->base == NULL) {          // 空间分配失败
        exit(OVERFLOW);
    }

    Q->front = Q->rear = 0;         // 头指针和尾指针置为空，队列为空

    return OK;
}

// 销毁队列
Status DestroyQueue (SeqQueue* Q)
{   
    if (Q->base == NULL) {
        return ERROR;
    }

    free(Q->base);
    Q->base = NULL; 

    Q->front = Q->rear = 0;

    return OK;
}

// 清空队列
Status ClearQueue (SeqQueue* Q)
{
    if (Q->base == NULL) {
        return ERROR;
    }

    Q->front = Q->rear = 0;

    return OK;
}

// 判空
bool QueueEmpty (SeqQueue Q)
{
    if (Q.front == Q.rear) {
        return true;
    }

    return false;
}

// 求队列长度
int QueueLength (SeqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 取队头元素
ElemType GetHead (SeqQueue Q)
{
    if (Q.front != Q.rear) {                    // 队列非空
        return Q.base[Q.front];                 // 返回队头元素的值，队头指针不变
    }
}

// 入队
Status EnQueue (SeqQueue* Q, ElemType e)
{   
    // 尾指针在循环意义上加1后等于头指针，表明队满
    if ((Q->rear + 1) % MAXQSIZE == Q->front) {
        return ERROR;
    }

    Q->base[Q->rear] = e;                       // 新元素插入队尾
    Q->rear = (Q->rear + 1) % MAXQSIZE;         // 队尾指针加1

    return OK;
}

// 出队
Status DeQueue (SeqQueue* Q, ElemType* e)
{   
    // 队空
    if (Q->front == Q->rear) {
        return ERROR;
    }

    *e = Q->base[Q->front];                     // 保存队头元素
    Q->front = (Q->front + 1) % MAXQSIZE;       // 队头指针加1

    return OK;
}

// 遍历队列
Status QueueTraverse (SeqQueue Q, Status (*Visit)(ElemType))
{
    int i = Q.front;

    while (i != Q.rear) {
        Visit (Q.base[i]);
        i = (i + 1) % MAXQSIZE;
    }

    printf("\n");

    return OK;
}

