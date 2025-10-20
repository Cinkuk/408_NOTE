#include <iostream>
#define MAXSIZE 100
typedef char Type;

typedef struct{
    Type data[MAXSIZE]; // 元素
    int top;            // 栈顶指针
}SqStack;

typedef struct LinkNode{
    Type data; // 数据域
    struct LinkNode *front, *rear; // 头尾指针
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


bool bracket_pair(std::string);

int main()
{
    using namespace std;
    string s1 {"((([([()])])))"};
    string s2 {"{{[()[]]}}"};
    string s3 {"[][](]"};
    cout << bracket_pair(s1) << endl;
    cout << bracket_pair(s2) << endl;
    cout << bracket_pair(s3) << endl;

    return 0;
}

bool bracket_pair(std::string s)
{   
    using namespace std;
    // initial stack
    SqStack stack;
    InitialStack(stack);
    vector <char> lbrackets {'(', '[', '{'};
    vector <char> rbrackets {')', ']', '}'};
    char e;

    for (char c : s)
    {
        auto it = find(lbrackets.begin(), lbrackets.end(), c);
        // left bracket
        if (it != lbrackets.end()) Push(stack, c); // push in stack
        // right brackt
        else {
            auto it = find(rbrackets.begin(), rbrackets.end(), c);
            if (it == rbrackets.end()) continue; // not a bracket
            GetTop(stack, e);
            // pair bracket
            if (c == ')' && e == '(') Pop(stack, e);
            else if (c == ']' && e == '[') Pop(stack, e);
            else if (c == '}' && e == '{') Pop(stack, e);
            else return false; // unpair bracket occur
        }
    }
    if (StackEmpty(stack)) return true;
    else return false;
}