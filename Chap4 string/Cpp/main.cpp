#include <iostream>

int Index(std::string, std::string);
void get_next(std::string, int[]);
int KMP_Index(std::string, std::string);
void get_nextvl(std::string, int[]);
int KMP_val_Index(std::string, std::string);

int main () {
    std::string S {"abcdace"};
    std::string T {"abc"};
    std::cout << Index(S, T) << std::endl;
    std::cout << KMP_Index(S, T) << std::endl;
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

// 计算next
void get_next(std::string S, int next[])
{
    int i {1}; int j {0};
    next[1] = 0;
    while (i < S.length()){
        if (j == 0 || S[i-1] == S[j-1]){
            next[i+1] = j + 1; // next[i+1] = next[i] + 1
            i++; j++;
        }
        else j = next[j]; // next[next[i]]
    }
}

// 主串S, 子串T
int KMP_Index(std::string S, std::string T)
{
    int i {1}; int j {1};
    int next[T.length()+1];
    next[0] = -1;
    get_next(T, next);

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
void get_nextvl(std::string S, int[]);

// 主串S, 子串T
int KMP_val_Index(std::string S, std::string T);

