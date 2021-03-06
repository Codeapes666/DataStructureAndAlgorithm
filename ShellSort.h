// 待排序记录的数据类型定义
#define MAXSIZE     100         // 顺序表的最大长度
#define OK          1
#define ERROR       0


typedef int KeyType;            // 定义关键字类型为整型
typedef int Status;

typedef struct
{
    KeyType key;                // 关键字项
} RedType;                      // 记录类型

typedef struct
{
    RedType r[MAXSIZE + 1];     // r[0]闲置或用做哨兵
    int length;                 // 顺序表长度
} SeqList;                      // 顺序表类型

// 希尔排序
// 当n在某个特定范围内，时间复杂度：O(n^1.3)
// 空间复杂度：O(1)
// 稳定性：不稳定
Status ShellSort(SeqList* L, int dk)
{
    // 增量变化
    for (dk = L->length / 2; dk >= 1; dk /= 2) {
        for (int i = dk + 1; i <= L->length; ++i) {
            // 需将L.r[i]插入有序增量子表
            if (L->r[i].key < L->r[i - dk].key) {
                // 暂存在L.r[0]
                L->r[0] = L->r[i];

                int j = 0;
                for (j = i -dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk) {
                    // 记录后移，直到找到插入位置
                    L->r[j + dk] = L->r[j];
                }

                // 将r[0]即原r[i]，插入到正确位置
                L->r[j + dk] = L->r[0];
            }
        }
    }

    return OK;
}