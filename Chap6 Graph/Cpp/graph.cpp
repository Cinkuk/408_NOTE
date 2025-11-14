#include <iostream>

#define MaxVertexNum 100

typedef char VertexType;
typedef int EdgeType;

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

struct MGgraph {
    VertexType vex[MaxVertexNum];                 // 顶点表
    EdgeType edge[MaxVertexNum][MaxVertexNum];    // 邻接矩阵(边表)
    int vexnum, arcnum;                           // 图当前的顶点数和边数
};

// 边表结点
struct ArcNode
{
    int adjvex;              // 该边指向的顶点
    struct ArcNode *nextarc; // 下一条边
};
// 顶点表结点
struct VNode
{
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一条边或者弧的指针
};
// 邻接表
struct ALGraph
{
    VNode vertices[MaxVertexNum];  // 边表
    int vexnum, arcnum;            // 顶点数和边数
};

void visit(ALGraph, int);
void visit(MGgraph, int);

bool visited[MaxVertexNum];
SqQueue Q;

void BFS (ALGraph G, int i)
{
    int v, w; // 工作结点
    ArcNode* p; // 用于访问邻接点
    // 访问初始结点
    visit(G, i);
    visited[i] = true;
    EnQueue(Q, i);
    while (!QueueEmpty(Q)) { 
        DeQueue(Q, v); // 队首结点
        for (p=G.vertices[v].firstarc; p; p=p->nextarc) { // 遍历全部邻接点
            w = p->adjvex;
            if (!visited[w]) { // 未被访问
                visit(G, w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }    
}

void BFS(MGgraph G, int i)
{
    int v, w; // 工作节点
    // 访问初始结点
    visit(G, i);
    visited[i] = true;
    EnQueue(Q, i);
    while (!QueueEmpty(Q)) {
        DeQueue(Q, v); // 队首结点
        for (w=0; w<G.vexnum; w++) { // 遍历全部邻接点
            if (!visited[w] && G.edge[v][w] == 1) { // 未被访问且<v, w>or(v, w)有边
                visit(G, w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void DFS(ALGraph G, int i)
{
    ArcNode* p; // 工作结点
    int j;
    visit(G, i);
    visited[i] = true;
    for (p=G.vertices[i].firstarc; p; p=p->nextarc) { // 访问全部邻接点
        j = p->adjvex;
        if (!visited[j]) // 未被访问
            DFS(G, j);
    }
}

void DFS (MGgraph G, int i)
{
    int j; // 工作顶点
    visit(G, i);
    visited[i] = true;
    for(j=0; j<G.vexnum; j++) { // 遍历各邻接点
        if (!visited[j] && G.edge[i][j] == 1) // 未被访问且有边
            DFS(G, j);
    }
}