#include <iostream>

typedef int Type;
using namespace std;

typedef struct DNode{
    Type data;
    DNode *prior, *next;
}DNode, *DLinkList;

typedef struct
{
    Type data;
    int next; // next: >0: pointer; -1: end of list; -2: available node
    int size;
}SNode, *SLinkList;

bool Initial_Dlink(DLinkList &);
bool ListInsert_forward(DLinkList &, int, Type);
bool ListInsert_forward_node(DNode* , Type);
bool ListInsert_backward(DLinkList&, int, Type);
bool ListInsert_backward_node(DNode* , Type);
bool ListDelete(DLinkList &, int);
void traverse_forward(DNode*);
void traverse_backward(DNode*);
bool Initial_SLinkList(SLinkList &, int);
bool SListInsert(SLinkList &, int, Type);
bool SListDelete(SLinkList &, int);
void Print_SList(SLinkList);

int main()
{
    cout << "----------Double Link List----------" << endl;
    DLinkList L;
    DNode* p;
    cout << Initial_Dlink(L) << endl;
    cout << "----------inserting forward----------" << endl;
    cout << ListInsert_forward(L, 1, 10) << endl;
    cout << ListInsert_forward(L, 100, 20) << endl;
    traverse_backward(L);
    p = L->next;
    cout << ListInsert_forward_node(p, 30) << endl;
    traverse_backward(L);
    traverse_forward(p);
    cout << "----------inserting backward----------" << endl;
    cout << ListInsert_backward(L, 1, 40) << endl;
    cout << ListInsert_backward(L, 9, 50) << endl;
    traverse_backward(L);
    p = L->next->next;
    cout << ListInsert_backward_node(p, 60) << endl;
    traverse_backward(L);
    traverse_forward(p);
    cout << "----------delete ndoe----------" << endl;
    cout << ListDelete(L, 1) << endl;
    cout << ListDelete(L, 100) << endl;;
    traverse_backward(L);

    cout << "----------Satatic Link List----------" << endl;
    SLinkList SL;
    cout << Initial_SLinkList(SL, 10) << endl;
    cout << "----------inserting----------" << endl;
    cout << SListInsert(SL, 1, 10) << endl;
    cout << SListInsert(SL, 1, 20) << endl;
    cout << SListInsert(SL, 3, 30) << endl;
    cout << SListInsert(SL, 2, 40) << endl;
    cout << SListInsert(SL, 10, 50) << endl;
    cout << "----------delete node----------" << endl;
    cout << SListDelete(SL, 2) << endl;
    cout << SListDelete(SL, 5) << endl;
    Print_SList(SL);

    return 0;
}

bool Initial_Dlink(DLinkList &L)
{
    DNode* head = new DNode;
    head->data = 0;
    head->prior = nullptr;
    head->next = nullptr;
    L = head;
    return true;
}

bool ListInsert_forward(DLinkList &L, int n, Type x)
{
    if (n < 1) return false; // n out of range
    DNode* node = new DNode;
    node->data = x;
    // handle n = 1 and list's length = 0
    if (!(L->next) && n == 1)
    {
        node->next = nullptr;
        node->prior = L;   
        L->next = node;
        return true;
    }
    DNode* p = L->next;
    int i {1};
    // search n-th node
    while (i < n && p)
    {
        p = p->next;
        i++;
    }
    if (i < n || !p) return false; // n out of range
    // insert forward
    p = p->prior; // point to previous node, n-1
    node->next = p->next;
    node->prior = p;
    p->next->prior = node;
    p->next = node;
    
    return true;
}

bool ListInsert_forward_node(DNode* node, Type x)
{
    /*
    NOT allow inserting node before head node
    */
    if (!(node->prior)) return false; // node is head node
    DNode* p = new DNode;
    p->data = x;
    p->next = node;
    p->prior = node->prior;
    node->prior->next = p;
    node->prior = p;

    return true;
}

bool ListInsert_backward(DLinkList &L, int n, Type x)
{
    if (n < 0) return false; // n out of range
    DNode* node = new DNode;
    node->data = x;
    // handle n == 0 and list's length = 0
    if (n == 0 && !(L->next))
    {
        node->next = nullptr;
        node->prior = L;
        L->next = node;
    }
    DNode* p = L->next;
    int i {1};
    // search n-th node
    while (i < n && p)
    {
        p = p->next;
        i++;
    }
    // n out of range
    if (i < n || p == L) return false;
    node->next = p->next;
    node->prior = p;
    p->next->prior = node;
    p->next = node;

    return true;
}

bool ListInsert_backward_node(DNode* node, Type x)
{
    DNode* p = new DNode;
    p->data = x;
    p->next = node->next;
    p->prior = node;
    node->next->prior = p;
    node->next = p;

    return true;
}

bool ListDelete(DLinkList &L, int n)
{
    if (n < 1) return false; // n out of range
    DNode* p = L->next;
    int i{1};
    while (i < n && p)
    {
        p = p->next;
        i++;
    }
    // n out of range
    if (i < n || !p) return false;
    p->next->prior = p->prior;
    p->prior->next = p->next;
    delete p;

    return true;
}

void traverse_forward(DNode* node)
{
    /*
    skip head node
    */
    DNode* p = node;
    while (p)
    {
        if (!(p->prior)) break;; // access head node; if allow to access head node, omment out this line
        cout << p->data << " ; ";
        p = p->prior;
    }
    cout << "end" << endl;
}

void traverse_backward(DNode* node)
{
    /*
    skip head node
    */
    DNode* p = node;
    while (p)
    {
        if (!(p->prior)) p = p->next; // access head node; if allow to access head node, comment out this line
        cout << p->data << " ; ";
        p = p->next;
    }
    cout << "end" << endl;
}

bool Initial_SLinkList(SLinkList &L, int capacity)
{
    L = new SNode[capacity];
    if (!L) return false; // not enough memory
    for (int i=0; i<capacity; i++) L[i].next = -2; // initial next field
    L[0].next = -1; // head node
    L->size = capacity;
    return true;
}

bool SListInsert(SLinkList &L, int n, Type x)
{
    if (n < 1) return false; // n out of range
    // find available node
    int node {-1};
    for (int i=1; i<L->size; i++)
    {
        if (L[i].next == -2) { node = i; break; }
    }
    if (node == -1) return false; // full list
    // find n-1 node 
    int prior {0}; int idx {0};
    while (idx < n - 1 && prior != -1)
    {
        prior = L[prior].next;
        idx++;
    }
    // invalid n
    if (idx < n - 1) return false; // invalid n

    // modify next and data field
    L[node].data = x;
    L[node].next = L[prior].next;
    L[prior].next = node;

    return true;
}

bool SListDelete(SLinkList &L, int n)
{
    // n out of range
    if (n < 1) return false;
    // find n-1
    int prior {0}; int cur = L[prior].next;
    int idx {0}; // order of prior
    while (idx < n-1 && prior != -1)
    {
        prior = cur;
        cur = L[cur].next;
        idx++;
    }
    if (idx < n - 1 || prior == -1) return false; // invalid n
    L[prior].next = L[cur].next; // modify pointer field in prior
    L[cur].next = -2; // delete n node

    return true;
}

void Print_SList(SLinkList L)
{
    cout << "-----Details of List-----" << endl;
    cout << "format: Data (next)" << endl;
    string data; int next;
    for (int i=0; i<L->size; i++)
    {
        next = L[i].next;
        data = next != -2 ? to_string(L[i].data) : "none";
        cout << data << "(" << next << ")" << " -> ";
    }
    cout << "end" << endl;
    cout << "-----order output-----" << endl;
    int p = L[0].next;
    while (p != -1)
    {
        cout << L[p].data << " -> ";
        p = L[p].next;
    }
    cout << "end" << endl;
}