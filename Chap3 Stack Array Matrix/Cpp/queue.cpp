#include <iostream>
#define MAXSIZE 10
typedef int Type;

typedef struct{
    Type data[MAXSIZE];
    int front, rear; // 队头和队尾指针
} SqQueue;

bool InitQueue(SqQueue &Q); // 初始化队列
bool QueueEmpty(SqQueue Q); // 判断队空
bool EnQueue(SqQueue &Q, Type x); // 元素x入队
bool DeQueue(SqQueue &Q, Type &x); // 元素出队并用x返回
bool GetHead(SqQueue Q, Type &x); // 读取队头元素并用x返回

// 初始化队列
bool InitQueue(SqQueue &Q)
{
    Q.front = Q.rear = 0;
    return true;
}

// 判断队空
bool QueueEmpty(SqQueue Q)
{
    return  Q.rear == Q.front;
}

// 元素x入队
bool EnQueue(SqQueue &Q, Type x)
{
    // if full
    if ((Q.rear + 1) % MAXSIZE == Q.front) return false;
    Q.data[Q.rear] = x; // enqueue
    Q.rear = (Q.rear + 1) % MAXSIZE; // update pointer
    return true;
}

// 元素出队并用x返回
bool DeQueue(SqQueue &Q, Type &x)
{
    // if empty
    if (Q.front == Q.rear) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE; //  update pointer
    return true;
}

// 读取队头元素并用x返回
bool GetHead(SqQueue Q, Type &x)
{
    // if empty 
    if (Q.front == Q.rear)  return false;
    x = Q.data[Q.front];
    return true;
}

typedef struct LinkNode{
    Type data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkQueue{
    LinkNode *front, *rear;
} LinkQueue;

// 初始化
bool InitQueue(LinkQueue &Q)
{
    LinkNode *head = new LinkNode;
    if (!head) return false; // not enough memory 
    head->next = nullptr;
    Q.front = Q.rear = head;
    return true;
}

// 判空
bool QueueEmpty(LinkQueue Q)
{
    return (Q.rear == Q.front);
}

// 元素x入队
bool EnQueue(LinkQueue &Q, Type x)
{
    LinkNode *node = new LinkNode;
    // new node
    if (!node) return false; // memory fail to allocate
    node->data = x;
    node->next = nullptr;
    // modify pointer
    Q.rear->next = node;
    Q.rear = node;
    return true;
}

// 出队, 并用x返回
bool DeQueue(LinkQueue &Q, Type &x)
{
    // if empty
    if (QueueEmpty(Q)) return false;
    LinkNode *p = Q.rear->next;
    x = p->data;
    // release node
    Q.rear->next = p->next;
    if (Q.rear == p) Q.rear = Q.front; // only one data node
    delete p;
    return true;
}