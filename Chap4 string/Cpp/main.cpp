#include <iostream>

int Index(std::string, std::string);
void get_next(std::string, int[]);
int KMP_Index(std::string, std::string);
void get_nextval(std::string, int[]);
int KMP_val_Index(std::string, std::string);
void print_next(std::string, int[]);

int main () {
    std::string S {"abcdace"};
    std::string T {"abaabcaba"};
    std::cout << Index(S, T) << std::endl;
    std::cout << KMP_Index(S, T) << std::endl;
    std::cout << KMP_val_Index(S, T) << std::endl;
    //std::string T {"abaabcaba"};
    //int next[10];
    //get_next(T, next);
    //for (int i=1; i<10; i++) std::cout << next[i] << " " ;

    return 0;
}

// 主串S, 子串T
int Index(std::string S, std::string T)
{
    int i{1}; int j {1};
    while (i <= S.length() && j <= T.length()){
        if (S[i-1] == T[j-1]) { // 继续比较下一字符
            i++; j++;
        }
        else {
            i = i - j + 2; // i - j + 1 + 1
            j = 1;
        }
    } // while
    if (j > T.length()) return i - T.length(); // (i + 1) - T.len
    return 0;
}

void print_next(std::string S, int next[])
{
    for (int i=0; i < S.length(); i++)
        std::cout << S[i] << "\t";
    std::cout << std::endl;

    for (int i=0; i < S.length(); i++)
        std::cout << next[i+1] << "\t";
    std::cout << std::endl;
}

// 计算next
void get_next(std::string S, int next[])
{
    int i {1}; int j {0};
    next[1] = 0;
    while (i < S.length()){
        if (j == 0 || S[i-1] == S[j-1]){ // S[i-1] == S[next[i-1]]
            next[i+1] = j + 1; // next[i+1] = next[i] + 1
            i++; j++;
        }
        else j = next[j]; // S[i-1] != S[next[i-1]]; S[next[next[i-1]]]
    }
}

// 主串S, 子串T
int KMP_Index(std::string S, std::string T)
{
    int i {1}; int j {1};
    int next[T.length()+1];
    next[0] = -1;
    get_next(T, next);
    std::cout << "-----KMP-----" << std::endl;
    print_next(T, next);

    while (i <= S.length() && j <= T.length()){
        if (j == 0 || S[i-1] == T[j-1]){ // 比较下一位
            i++; j++; 
        }
        else j = next[j];
    } // while 
    if (j > T.length()) return i - T.length(); // (i + 1) - T.len
    return 0;
}

// 计算nextval
void get_nextval(std::string S, int nextval[])
{
    int i {1}; int j {0};
    nextval[1] = 0;
    while (i < S.length()){
        if (j == 0 || S[i-1] == S[j-1]) { // S[i-1] == S[nextval[i-1]]
            i++; j++;
            if (S[i-1] != S[j-1]) nextval[i] = j; // S[i] != S[nextval[i]]
            else nextval[i] = nextval[j]; // S[i] == S[nextval[i]], recursive
        } // if
        else j = nextval[j]; // S[i-1] != S[nextval[i-1]]; S[nextval[nextval[i-1]]]
    } // while
}

// 主串S, 子串T
int KMP_val_Index(std::string S, std::string T)
{
    int i {1}; int j {1};
    int nextval[T.length()+1];
    nextval[0] = -1;
    get_nextval(T, nextval);
    std::cout << "-----KMP val-----" << std::endl;
    print_next(T, nextval);

    while (i <= S.length() && j <= T.length()){
        if (j == 0 || S[i-1] == T[j-1]) { // 比较下一位
            i++; j++;
        }
        else j = nextval[j];
    } // while
    if (j > T.length()) return i - T.length();
    return 0;
}

