#include <iostream>
#define MAXSIZE 10

typedef int Type;
using namespace std;


// 静态分配
typedef struct
{
    Type data[MAXSIZE];
    int maxsize; // 最大长度, 为了方便操作加上, 若保证能访问宏定义MAXSIZE可以省略
    int length; // 当前长度
}SqList;

// 动态分配
typedef struct
{
    Type *data;
    int maxsize; // 当前最大长度
    int length; // 当前长度
}SeqList;

void Initial(SqList &);
bool Initial(SeqList &);
bool DestroyList(SeqList &);
bool IncreaseList(SeqList &, int );
template <typename T> int Length(T);
template <typename T> int LocateElem(T, Type);
template <typename T> Type GetElem(T, int);
template <typename T> bool ListInsert(T &, int, Type);
template <typename T> bool ListDelete(T &, int, Type &);
template <typename T> void PrintList(T);
template <typename T> bool Empty(T);

int SeqListTest ()
{
    cout << "---------静态分配-----------" << endl;
    SqList L;
    cout << "初始化" << endl;
    Initial(L);
    cout << Length(L) << endl;
    cout << Empty(L) << endl;
    cout << "插入" << endl;
    cout << ListInsert(L, 1, 10) << endl;
    cout << ListInsert(L, 15, 16) << endl;
    ListInsert(L, 1, 15);
    ListInsert(L, 2, 13);
    PrintList(L);
    cout << "按值查找" << endl;
    cout << LocateElem(L, 13) << endl;
    cout << LocateElem(L, 99) << endl;
    cout << "按位查找" << endl;
    cout << GetElem(L, 1) << endl;
    cout << GetElem(L, 10) << endl;
    cout << (GetElem(L, 10) == -INT_MAX) << endl;
    cout << "删除元素" << endl;
    PrintList(L);
    int e {};
    cout << ListDelete(L, 2, e) << endl;
    cout << e << endl;
    cout << ListDelete(L, 9, e) << endl;
    cout << Empty(L) << endl;

    cout << "---------动态分配-----------" << endl;
    SeqList Le;
    cout << "初始化" << endl;
    Initial(Le);
    cout << Length(Le) << endl;
    cout << Empty(Le) << endl;
    cout << "插入" << endl;
    cout << ListInsert(Le, 1, 10) << endl;
    cout << ListInsert(Le, 15, 16) << endl;
    ListInsert(Le, 1, 15);
    ListInsert(Le, 2, 13);
    PrintList(Le);
    cout << "按值查找" << endl;
    cout << LocateElem(Le, 13) << endl;
    cout << LocateElem(Le, 99) << endl;
    cout << "按位查找" << endl;
    cout << GetElem(Le, 1) << endl;
    cout << GetElem(Le, 10) << endl;
    cout << (GetElem(Le, 10) == -INT_MAX) << endl;
    cout << "删除元素" << endl;
    PrintList(Le);
    cout << ListDelete(Le, 2, e) << endl;
    cout << e << endl;
    cout << ListDelete(Le, 9, e) << endl;
    cout << Empty(Le) << endl;
    cout << "扩展" << endl;
    cout << Le.maxsize << endl;
    for (int i=0; i<Le.maxsize; i++) 
        Le.data[i] = i;
    Le.length = Le.maxsize;
    PrintList(Le);
    cout << ListInsert(Le, 1, 11) << endl;
    cout << IncreaseList(Le, 5) << endl;
    cout << Le.maxsize << endl;
    cout << ListInsert(Le, 1, 99) << endl;
    PrintList(Le);

    return 0;
}

// 初始化静态分配顺序表
void Initial(SqList &L)
{
    L.maxsize = MAXSIZE;
    L.length = 0;
}

// 初始化动态分配顺序表
bool Initial(SeqList &L)
{
    L.maxsize = MAXSIZE;
    L.length = 0;
    if ((L.data = new Type[MAXSIZE]))
        return true;
    return false;
}

// 销毁动态分配顺序表
bool DestroyList(SeqList &L)
{
    L.maxsize = 0;
    L.length = 0;
    delete L.data; // free space
    return true;
}

// 扩展表
bool IncreaseList(SeqList &L, int n)
{
    n += L.maxsize; // new data size
    if (Type* new_data = new Type[n]) // try to request space
    {
        for (int i=0; i<L.length; i++) // move elements
            new_data[i] = L.data[i];
        delete L.data; // free space
        L.data = new_data; // change data pointer
        L.maxsize = n; // new data size
        return true;
    }
    else return false;
}

// 按值查找
template <typename T>
int LocateElem(T L, Type e)
{
    // return order of elemet
    for (int i=0; i<L.length; i++)
        if (L.data[i] == e) return i+1;
    return -1;
}

// 按位查找
template <typename T>
Type GetElem(T L, int i)
{
    // param i: order of element
    if (i > L.length) // out of range
        return -INT_MAX;
    else return L.data[i-1];
}

// 插入元素
template <typename T>
bool ListInsert(T &L, int i, Type e)
{
    // param i: order of element
    // invalid i
    if (i < 1 || i > L.maxsize || L.length == L.maxsize)
        return false;
    for (int j=L.length; j>=i; j--) // move element [i, length] backward
        L.data[j] = L.data[j-1];
    L.data[i-1] = e; // insert element
    L.length++; // update length
    return true;
}

// 删除元素
template <typename T>
bool ListDelete(T &L, int i, Type &e)
{
    // param i: order of element
    if (i < 1 || i > L.length) // invalid i
        return false;
    e = L.data[i-1]; // save deleting element
    for (int j=i; j<L.length; j++) // move element[i+1, length] forward
        L.data[j-1] = L.data[j];
    L.length--; // update length
    return true;
}

// 表长
template <typename T>
int Length(T L)
{
    return L.length;
}

// 打印表
template <typename T>
void PrintList(T L)
{
    for (int i=0; i<L.length; i++)
        cout << L.data[i] << " ";
    cout << endl;
}

// 判空
template <typename T>
bool Empty(T L)
{
    return (L.length == 0);
}