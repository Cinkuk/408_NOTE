#include <iostream>
#include <map>
#include <stack>
#define MAXSIZE 100
typedef std::string Type;

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


//bool bracket_pair(std::string);
std::string expression_infix2post(std::string);
double calculate_infix(std::string);

int main()
{
    using namespace std;
    string s1 {"((([([()])])))"};
    string s2 {"{{[()[]]}}"};
    string s3 {"[][](]"};
    //cout << bracket_pair(s1) << endl;
    //cout << bracket_pair(s2) << endl;
    //cout << bracket_pair(s3) << endl;
    //cout << "expression cvt" << endl;
    string s4 {"123 + 45 * 67 / (89 - 12) * 3 + 456 * (78 - 9)"}; // 123 45 67 * 89 12 - / 3 * + 456 78 9 - * +
    cout << expression_infix2post(s4) << endl;
    cout << calculate_infix(s4) << endl;

    return 0;
}

/*
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
*/

std::string expression_infix2post(std::string e)
{
    using namespace std;
    string post {""};
    SqStack stack;
    InitialStack(stack);

    int n = e.length();
    int begin, end; // split string
    begin = end = 0;
    string temp, top;
    int flag; //0: operator, 1: digit, 2: bracket

    vector<char> operators {'+', '-', '*', '/'};
    vector<char> digits {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    map<string, int> precedence {
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2},
    };

    while (end < n) {
        // split expression 
        auto it = find(operators.begin(), operators.end(), e[end]);
        if (it != operators.end()) { // operator
            temp = e[end]; end++;
            flag = 0;
        }
        else if (e[end] == ' ') { // space
            end++; 
            continue;
        }
        else if (e[end] == '(' || e[end] == ')') { // bracket
            temp = e[end]; end++;
            flag = 2;
        }
        else { //digit
            begin = end;
            while (end < n && find(digits.begin(), digits.end(), e[end]) != digits.end())
                end++;
            temp = e.substr(begin, end - begin); // (end - 1) - begin + 1
            flag = 1;
        }

        // action 
        if (flag == 2) { // bracket
            if (temp == "(") Push(stack, temp);
            else {
                GetTop(stack, top);
                while (top != "(") {
                    post += " "; post += top;
                    Pop(stack, top); GetTop(stack, top);
                } // while
                Pop(stack, top); // pop '('
            } //else
        }
        else if (flag == 1) { // digit
            post += " "; post += temp;
        }
        else { // operator
            while (!StackEmpty(stack)) {
                GetTop(stack, top);
                if (top == "(") break;
                if (precedence[top] >= precedence[temp]) {
                    post += " "; post += top;
                    Pop(stack, top);
                }
                else break;
            }
            Push(stack, temp);      
        }
    }

    // clear stack
    while (!StackEmpty(stack)) {
        Pop(stack, top);
        post += " "; post += top;
    }
    return post;
}

double calculate_infix(std::string infix)
{
    using namespace std;

    string post = expression_infix2post(infix);
    stack<double> stk;
    int n = post.length();
    string temp;
    double X, Y;
    int begin, end;
    begin = end = 0;

    vector<char> operators {'+', '-', '*', '/'};
    vector<char> digits {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    while (end < n) {
        // split expression 
        auto it = find(operators.begin(), operators.end(), post[end]);
        if (it != operators.end()) { // operator
            temp = post[end]; end++;
            Y = stk.top(); stk.pop();
            X = stk.top(); stk.pop();
            if (temp == "+") stk.push(X + Y);
            else if (temp == "-") stk.push(X - Y);
            else if (temp == "*") stk.push(X * Y);
            else if (temp == "/") stk.push(X / Y);

        }
        else if (post[end] == ' ') { // space
            end++; 
            continue;
        }
        else { //digit
            begin = end;
            while (end < n && find(digits.begin(), digits.end(), post[end]) != digits.end())
                end++;
            temp = post.substr(begin, end - begin); // (end - 1) - begin + 1
            stk.push(stod(temp));
        }
    }
    return stk.top();
}