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

bool InitialStack(SqStack &s); // 初始化栈
bool StackEmpty(SqStack s); // 判断栈是否为空
bool Push(SqStack &s, Type x); // 将x压入栈顶
bool Pop(SqStack &s, Type &x); // 从栈顶弹出元素, 用x返回
bool GetTop(SqStack s, Type &x); // 读取栈顶元素, 非空则用x返回
bool DestroyStack(SqStack &s); // 销毁栈
