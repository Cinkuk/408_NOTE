#include <iostream>
#define MAXSIZE 10
typedef int Type;

typedef struct{
    Type data[MAXSIZE]; // 元素
    int top;            // 栈顶指针
}SqStack;

typedef struct{
    Type data; // 数据域
    LinkNode *front, *rear; // 头尾指针
}LinkNode, LiStack;

bool InitialStack(SqStack&); // 初始化栈
bool StackEmpty(SqStack); // 判断栈是否为空
bool Push(SqStack&, Type); // 将x压入栈顶
bool Pop(SqStack&, Type&); // 从栈顶弹出元素, 用x返回
bool GetTop(SqStack, Type&); // 读取栈顶元素, 非空则用x返回
bool DestroyStack(SqStack&); // 销毁栈

// 初始化栈
bool InitialStack(SqStack &s)
{
    s.top = -1;
    return true;
}

// 判断栈是否为空
bool StackEmpty(SqStack s)
{
    return s.top == -1;
}

// 将x压入栈顶
bool Push(SqStack &s, Type x)
{
    if (s.top == MAXSIZE) return false; // full stack
    s.data[++s.top] = x;
    return true;
}

// 从栈顶弹出元素, 用x返回
bool Pop(SqStack &s, Type &x)
{
    if (s.top == -1) return false; // empty stack
    x = s.data[s.top--];
    return true;
}

// 读取栈顶元素, 非空则用x返回
bool GetTop(SqStack s, Type &x)
{
    if (s.top == -1) return false; // empty satck
    x = s.data[s.top];
    return true;
}


typedef struct{
    Type data[MAXSIZE];
    int front, rear; // 队头和队尾指针
} SqQueue;

bool InitQueue(SqQueue &Q); // 初始化队列
bool QueueEmoty(SqQueue Q); // 判断队空
bool EnQueue(SqQueue &Q, Type x); // 元素x入队
bool DeQueue(SqQueue &Q, Type &x); // 元素出队并用x返回
bool GetHead(SqQueue Q, Type &x); // 读取队头元素并用x返回