#include <iostream>

#define MaxVertexNum 100

typedef char VertexType;
typedef int EdgeType;

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
