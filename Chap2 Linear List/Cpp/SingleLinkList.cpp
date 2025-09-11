#include <iostream>

using namespace std;

typedef int Type;

typedef struct LNode{
    Type data;
    LNode* next;
}LNode, *LinkList;

bool InitList(LinkList &);
bool InitList_nohead(LinkList &);
// 默认带头结点
int Length(LinkList);
void Print(LinkList);
bool Empty(LinkList);
LNode* GetElem(LinkList, int);
LNode* LocateElem(LinkList, Type);
bool ListInsert_forward(LinkList &, int, Type);
bool ListInsert_backward(LinkList &, int, Type);
bool ListInsert_forward_node(LNode* , Type); // 只给出节点, 前插
bool ListInsert_backward_node(LNode* , Type); // 只给出节点, 尾插
bool ListDelete(LinkList &, int, Type &);
bool ListDestroy(LinkList &);
// 下面两个建立单链表的函数用于使用Type[]的元素建立链表
LinkList BuildList_HeadInsert(Type[], int);
LinkList BuildList_TailInsert(Type[], int);

int SingleLinkList_main()
{
    LinkList L;
    InitList(L);
    Print(L);
    cout << Empty(L) << endl;
    Type a[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Head Insert" << endl;
    L = BuildList_HeadInsert(a, 10);
    Print(L);
    cout << ListDestroy(L) << endl;
    cout << "Tail Insert" << endl;
    L = BuildList_TailInsert(a, 10);
    Print(L);
    cout << ListInsert_forward(L, 2, 99) << endl;
    cout << ListInsert_forward(L, 100, 88) << endl;
    Print(L);
    cout << ListInsert_backward(L, 2, 101) << endl;
    cout << ListInsert_backward(L, 101, 102) << endl;
    Print(L);
    LNode* node;
    cout << "按位查找, 第3个" << endl;
    node = GetElem(L, 3);
    cout << node->data << endl;
    cout << "按位查找, 第100个" << endl;
    node = GetElem(L, 100);
    cout << (node == nullptr) << endl;
    cout << "按值查找, 值为7" << endl;
    node = LocateElem(L, 7);
    cout << node->data << endl;
    cout << "按值查找, 值为123" << endl;
    node = LocateElem(L, 123);
    cout << (node == nullptr) << endl;

    return 0;
}

// 带头结点
bool InitList(LinkList &L)
{
    L = new LNode;
    L->next = nullptr;
    return true;
}

// 不带头结点
bool Initial_nohead(LinkList &L)
{
    L = nullptr;
    return true;
}

int Length(LinkList L)
{
    int n {0};
    LNode *p = L->next;
    while (p->next != nullptr)
    {
        n++;
        p = p->next;
    }
    return n;
}

void Print(LinkList L)
{
    LNode *p = L->next;
    while (p)
    {
        cout << p->data << " -> ";
        p = p->next;
    }
    cout << "end" << endl;
}

bool Empty(LinkList L)
{
    if (L->next) return false;
    else return true;
}

// 按位查询
LNode* GetElem(LinkList L, int n)
{
    /*
    n : 位序
    */
    int i {0}; // 头结点计数为0
    LNode* p = L;
    while (p && i < n)
    {
        p = p->next;
        i++;
    }
    return p;
}

// 按值查询
LNode* LocateElem(LinkList L, Type x)
{
    /*
    返回目标结点指针
    找不到则返回空指针
    */
    LNode* p = L->next;
    while (p && p->data != x)
        p = p->next;
    return p;
}

// 给定位序
bool ListInsert_forward(LinkList &L, int n, Type x)
{
    int i {0};
    LNode* p = L;
    // find n-1 
    while(p->next && i < n-1)
    {
        p = p->next;
        i++;
    }
    if (p->next)
    {
        // new node
        LNode *node = new LNode;
        node->data = x;   
        // modify pointer
        node->next = p->next;
        p->next = node;
        return true;
    }
    else return false;
}

// 给定结点
bool ListInsert_forward_node(LNode* node, Type x)
{
    if (node)
    {
        LNode* s = new LNode;
        s->data = x;
        s->next = node->next;
        node->next = s;
        // swap data
        Type t = node->data;
        node->data = s->data;
        s->data = t;
        return true;
    }
    else return false;
}

// 给定位序
bool ListInsert_backward(LinkList &L, int n, Type x)
{
    int i {0};
    LNode *p = L;
    // find n
    while (p && i < n)
    {
        p = p->next;
        i++;
    }
    if (p)
    {
        LNode *node = new LNode;
        node->data = x;
        node->next = p->next;
        p->next = node;
        return true;
    }
    else return false;
}

// 给定结点
bool ListInsert_backward_node(LNode* node, Type x)
{
    if (node)
    {
        LNode *p = new LNode;
        p->data = x;
        p->next = node->next;
        node->next = p;
        return true;
    }
    else return false;
}

// 给定位序
bool ListDelete(LinkList &L, int n, Type &e)
{
    /*
    delete n-th node
    copy data to e
    */
   int i {0};
   LNode *p = L;
   // find n - 1
   while (p && i < n-1)
   {
        p = p->next;
        i++;
    }
    if (p->next && i == n-1)
    {
        LNode *t = p->next;
        p->next = t->next;
        e = t->data;
        delete t;
        return true;   
    }
    else return false;
}

bool ListDestroy(LinkList &L)
{
    /*
    retain head node
    */
   LNode *p = L->next;
   LNode *q;
   while (p)
   {
        q = p->next;
        delete p;
        p = q;
    }
    L->next = nullptr;
    return true;
}

LinkList BuildList_HeadInsert(Type x[], int n)
{
    LNode *L = new LNode;
    L->next = nullptr;
    for(int i=0; i<n; ++i)
    {
        LNode *s = new LNode;
        s->data = x[i];
        s->next = L->next;
        L->next = s;
    }
    return L;
}

LinkList BuildList_TailInsert(Type x[], int n)
{
    LNode *L = new LNode;
    LNode *end = L;
    for (int i=0; i<n; ++i)
    {
        LNode *s = new LNode;
        s->data = x[i];
        end->next = s;
        end = s;
    }
    end->next = nullptr;
    return L;
}