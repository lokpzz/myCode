#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// --- 结构体定义 ---
struct Point {
    double x, y;
};

// --- 常量与参数 ---
const int CITY_NUM = 20;   // 城市数量
const int ANT_NUM = 50;    // 蚂蚁数量
const int MAX_ITER = 100;  // 最大迭代次数
const double RHO = 0.1;    // 信息素挥发系数
const double ALPHA = 1.0;  // 信息素重要程度
const double BETA = 2.0;   // 启发函数重要程度
const double Q = 100.0;    // 信息素增量常数

// --- 城市坐标数据---
Point cities[CITY_NUM] = {
    {10, 20}, {30, 45}, {15, 60}, {40, 10}, {55, 30},
    {70, 50}, {20, 80}, {85, 15}, {90, 70}, {35, 35},
    {60, 85}, {10, 10}, {50, 60}, {80, 40}, {25, 25},
    {45, 90}, {95, 25}, {5, 55}, {65, 10}, {75, 80}
};

double pheromone[CITY_NUM][CITY_NUM];

// --- 核心辅助函数 ---

// 计算两点间距离
double get_dist(int i, int j) {
    double dx = cities[i].x - cities[j].x;
    double dy = cities[i].y - cities[j].y;
    return sqrt(dx * dx + dy * dy);
}

// 计算路径总长度
double calc_path_length(int path[]) {
    double length = 0.0;
    for (int i = 0; i < CITY_NUM; i++) {
        length += get_dist(path[i], path[(i + 1) % CITY_NUM]);
    }
    return length;
}

int main() {
    srand((unsigned int)time(NULL));

    // 初始化信息素
    for (int i = 0; i < CITY_NUM; i++) {
        for (int j = 0; j < CITY_NUM; j++) pheromone[i][j] = 1.0;
    }

    double global_best_len = 1e18;
    int global_best_path[CITY_NUM];

    // 迭代过程
    for (int iter = 0; iter < MAX_ITER; iter++) {
        int ant_path[ANT_NUM][CITY_NUM];
        bool ant_taboo[ANT_NUM][CITY_NUM] = {false};
        double ant_len[ANT_NUM];

        for (int k = 0; k < ANT_NUM; k++) {
            // 1. 随机放置蚂蚁
            int start = rand() % CITY_NUM;
            ant_path[k][0] = start;
            ant_taboo[k][start] = true;

            // 2. 蚂蚁移动
            for (int step = 1; step < CITY_NUM; step++) {
                int curr = ant_path[k][step - 1];
                double prob[CITY_NUM] = {0.0};
                double sum_prob = 0.0;

                for (int i = 0; i < CITY_NUM; i++) {
                    if (!ant_taboo[k][i]) {
                        double d = get_dist(curr, i);
                        // 避免除零，虽然坐标重合概率低
                        double eta = 1.0 / (d + 1e-9); 
                        prob[i] = pow(pheromone[curr][i], ALPHA) * pow(eta, BETA);
                        sum_prob += prob[i];
                    }
                }

                // 轮盘赌
                double r = (double)rand() / RAND_MAX * sum_prob;
                double acc = 0.0;
                int next_city = -1;
                for (int i = 0; i < CITY_NUM; i++) {
                    if (!ant_taboo[k][i]) {
                        acc += prob[i];
                        if (acc >= r) { next_city = i; break; }
                    }
                }
                if (next_city == -1) { // 补救措施，防止浮点数精度问题导致未选到城市
                    for(int i=0; i<CITY_NUM; i++) if(!ant_taboo[k][i]) { next_city = i; break; }
                }

                ant_path[k][step] = next_city;
                ant_taboo[k][next_city] = true;
            }

            // 3. 更新该代最优
            ant_len[k] = calc_path_length(ant_path[k]);
            if (ant_len[k] < global_best_len) {
                global_best_len = ant_len[k];
                for (int i = 0; i < CITY_NUM; i++) global_best_path[i] = ant_path[k][i];
            }
        }

        // 4. 信息素挥发
        for (int i = 0; i < CITY_NUM; i++) {
            for (int j = 0; j < CITY_NUM; j++) pheromone[i][j] *= (1 - RHO);
        }

        // 5. 信息素更新
        double delta = Q / global_best_len;
        for (int i = 0; i < CITY_NUM; i++) {
            int u = global_best_path[i];
            int v = global_best_path[(i + 1) % CITY_NUM];
            pheromone[u][v] += delta;
            pheromone[v][u] += delta;
        }

        if((iter + 1) % 10 == 0)
            cout << "迭代 " << (iter + 1) << ": 当前最短路径 = " << fixed << setprecision(2) << global_best_len << endl;
    }

    // --- 输出最终结果 ---
    cout << "\n==================== 最终结果 ====================" << endl;
    cout << "最短路径长度: " << global_best_len << endl;
    cout << "访问顺序 (坐标):" << endl;
    for (int i = 0; i < CITY_NUM; i++) {
        int id = global_best_path[i];
        cout << "(" << cities[id].x << "," << cities[id].y << ") -> ";
    }
    int start_id = global_best_path[0];
    cout << "(" << cities[start_id].x << "," << cities[start_id].y << ")" << endl;

    return 0;
}
