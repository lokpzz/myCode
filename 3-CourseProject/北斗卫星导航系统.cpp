#include <bits/stdc++.h>
using namespace std;
 
const int N = 100 + 10;
#define INF 0x3f3f3f3f

// 图的邻接矩阵结构
typedef struct {
    string vexs[N];  // 顶点数组 
    int arcs[N][N];  // 邻接矩阵
    int vexnum;      // 顶点数
    int arcnum;      // 边数
} AMGraph;

// 查找城市下标，找不到返回-1
int LocateVex(AMGraph G, string s) {
    for (int i = 1; i <= G.vexnum; ++i) 
        if (G.vexs[i] == s)  
            return i;
    return -1;
}

// 邻接矩阵创建无向带权图
void CreateUDN(AMGraph *G) {
    cout << "请输入顶点数和边数：" << endl;
    cin >> G->vexnum >> G->arcnum;

    cout << "请输入" << G->vexnum << "个城市名：" << endl;
    for (int i = 1; i <= G->vexnum; ++i) {
        cin >> G->vexs[i];
    }

    // 初始化邻接矩阵
    for (int i = 1; i <= G->vexnum; ++i) {
        for (int j = 1; j <= G->vexnum; ++j) {
            G->arcs[i][j] = (i == j) ? 0 : INF;
        }
    }

    // 输入边
    cout << "请输入" << G->arcnum << "条边（格式：城市A 城市B 距离）：" << endl;
    for (int i = 0; i < G->arcnum; ++i) {
        string sa, sb;
        int dist;
        cin >> sa >> sb >> dist;

        // 查找城市下标
        int a = LocateVex(*G, sa);
        int b = LocateVex(*G, sb);

        // 健壮性检查
        if (a == -1 || b == -1) {
            cout << "警告：城市" << (a == -1 ? sa : sb) << "不存在，跳过该边！" << endl;
            --i;  // 重新输入当前边
            continue;
        }
        //赋值
        G->arcs[a][b] = dist;
        G->arcs[b][a] = dist;
    }
}

// Dijkstra算法求最短路径 
//思路：关键就3步
//      1.进行初始化，dist[],set[],path[]
//      2.找出每次距离最短的节点
//      3.更新加入节点后的path
//2、3循环直到遍历完所有节点
void Djsp(AMGraph G, string s1, string s2) {
    // 定义三个数组 
    int dist[N], path[N], set[N];
    // 定义变量
    int be = LocateVex(G, s1);
    int end = LocateVex(G, s2);
    int min = INF;
    int u;  // 存储每次选中的最短路径顶点

    // 初始化
    for (int i = 1; i <= G.vexnum; i++) {
        dist[i] = G.arcs[be][i];
        set[i] = 0;
        path[i] = (G.arcs[be][i] < INF) ? be : -1;
    }
    set[be] = 1;
    path[be] = -1;

    // 循环2，3：逐步确定最短路径
    for (int i = 1; i <= G.vexnum; i++) {
        min = INF;
        // 2. 找出当前未加入集合的最短路径顶点u
        for (int j = 1; j <= G.vexnum; j++) { 
            if (set[j] == 0 && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        set[u] = 1; 
        if (u == end) break;  // 优化：终点已找到，提前退出

        // 3. 更新通过u的最短路径
        for (int v = 1; v <= G.vexnum; v++) {
            if (set[v] == 0 && dist[u] != INF && dist[u] + G.arcs[u][v] < dist[v]) {
                dist[v] = dist[u] + G.arcs[u][v]; 
                path[v] = u;
            }
        }
    }

    // 输出结果
    cout << "\n起点：" << s1 << "，终点：" << s2 << endl;
    if (dist[end] == INF) {
        cout << "结果：无可达路径！" << endl;
        return;
    }
    cout << "最短路径长度：" << dist[end] << endl;
    cout << "最短路径：";
    int stack[N], top = 0;
    int temp = end;
    // 回溯路径（从终点到起点）
    while (temp != -1) {
        stack[top++] = temp;
        temp = path[temp];
    }
    // 逆序输出（从起点到终点）
    for (int i = top - 1; i >= 0; i--) {
        cout << G.vexs[stack[i]];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

// 测试主函数
int main() {
    AMGraph G;
    CreateUDN(&G);  // 创建图

    string s1, s2;
    cout << "\n请输入两个城市名（起点 终点）：";
    cin >> s1 >> s2;
    Djsp(G, s1, s2);

    return 0;
}
