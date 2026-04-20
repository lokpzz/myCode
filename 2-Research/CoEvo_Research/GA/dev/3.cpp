#include<bits/stdc++.h>
using namespace std;

// 参数
const int maxgen = 3000;     // 最大代数
const int sizepop = 1000;    // 种群数目
const double pcross = 0.8;  // 交叉概率
const double pmutation = 0.1;// 变异概率
const int lenchrom = 100;    // 染色体长度（城市数）

//测试用例
/* 
vector<pair<double, double>> city_pos = {
    {16.47,96.10},{16.47,94.44},{20.09,92.54},{22.39,93.37},
    {25.23,97.24},{22.00,96.05},{20.47,97.02},{17.20,96.29},
    {16.30,97.38},{14.05,98.12},{16.53,97.38},{21.52,95.59},
    {19.41,97.13},{20.09,92.55}
}; 
*/
vector<pair<double, double>> city_pos = {
    {20.81,94.87},{18.45,96.12},{22.33,93.56},{15.78,97.41},{19.98,92.89},
    {24.12,95.34},{17.65,98.00},{21.09,94.23},{16.87,96.78},{14.99,95.67},
    {23.45,97.12},{18.98,93.45},{25.11,96.89},{17.23,92.78},{20.56,95.90},
    {19.34,97.65},{22.87,94.98},{16.12,98.11},{24.89,93.23},{15.45,96.45},
    {21.78,92.98},{18.76,95.78},{23.98,94.12},{17.90,97.34},{20.12,96.56},
    {14.87,93.89},{22.45,97.89},{19.67,92.45},{25.34,95.12},{16.56,94.78},
    {20.98,98.01},{18.12,96.23},{24.56,93.78},{15.98,95.45},{21.34,97.90},
    {17.45,94.34},{23.12,96.67},{19.89,92.12},{22.78,95.89},{16.34,97.56},
    {24.23,94.45},{18.56,98.23},{20.78,93.56},{15.23,96.89},{23.89,92.78},
    {19.45,95.23},{21.67,97.45},{17.89,94.90},{25.45,93.12},{16.78,96.34},
    {22.12,98.34},{18.34,95.56},{24.78,97.67},{15.67,94.12},{20.34,92.90},
    {23.56,96.45},{19.12,98.56},{21.98,93.34},{17.12,95.78},{24.45,97.23},
    {16.98,94.89},{22.56,92.67},{18.89,96.90},{20.45,95.34},{15.89,97.78},
    {23.23,94.56},{19.78,92.89},{25.12,96.12},{17.56,98.45},{21.45,93.90},
    {16.23,95.67},{24.98,97.89},{18.23,94.23},{22.98,96.56},{20.67,92.45},
    {15.45,97.12},{23.78,95.89},{19.23,98.12},{21.89,94.78},{17.78,96.34},
    {24.67,93.56},{16.45,95.90},{22.34,97.45},{18.67,92.78},{20.23,96.89},
    {15.12,94.45},{23.67,98.23},{19.98,93.12},{21.23,95.78},{17.34,97.67},
    {25.23,94.90},{16.89,92.67},{22.78,96.45},{18.98,98.56},{20.89,93.34},
    {15.78,95.23},{23.45,97.90},{19.56,94.78},{21.12,96.12},{17.09,98.01}
};
vector<vector<int>> chrom(sizepop,vector<int>(lenchrom));
vector<int> best_result(lenchrom);
double min_distance;

// 种群初始化
void init() {
    for(int i = 0; i < sizepop; ++i) {
        vector<int>& chr = chrom[i];
        chr.resize(lenchrom);
        iota(chr.begin(), chr.end(), 1);
        
        // 随机打乱lenchrom/2次
        for(int k = 0; k < lenchrom/2; k++)
        {
            int pos1 = rand() % lenchrom;
            int pos2 = rand() % lenchrom;
            int temp = chrom[i][pos1];
            chrom[i][pos1] = chrom[i][pos2];
            chrom[i][pos2] = temp;
        }
    }
}

// 计算两个城市之间的距离
double distance(pair<double,double>& city1,pair<double,double>& city2) {
    double x1 = city1.first, y1 = city1.second;
    double x2 = city2.first, y2 = city2.second;
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

// 计算数组的最小值索引
pair<int, double> find_min(vector<double>& arr) {
    int idx = 0;
    double minval = arr[0];
    for(int i = 1; i < arr.size(); ++i) {
        if(arr[i] < minval) {
            minval = arr[i];
            idx = i;
        }
    }
    return {idx, minval};
}

// 计算单个个体的路径长度
double pathlen(const vector<int>& arr) {
    double total_len = 0.0;
    for(int i = 0; i < lenchrom - 1; ++i) {
        int idx1 = arr[i] - 1;
        int idx2 = arr[i+1] - 1;
        total_len += distance(city_pos[idx1], city_pos[idx2]);
    }
    // 回到起点
    int last_idx = arr.back() - 1;
    int first_idx = arr.front() - 1;
    total_len += distance(city_pos[last_idx], city_pos[first_idx]);
    return total_len;
}

//// 选择
//void Choice(vector<vector<int>>& pop) {
//    const int pop_size = pop.size();
//    vector<double> fit(pop_size, 0.0);
//    vector<double> cumpro(pop_size, 0.0);
//    double sum_fit = 0.0;
//    
//    // 计算适应度和总适应度
//    for (int j = 0; j < pop_size; j++) {
//        double len = pathlen(pop[j]);
//        fit[j] = 1.0 / (len + 1e-10);
//        sum_fit += fit[j];
//    }
//    
//    cumpro[0] = fit[0] / sum_fit;
//    for (int j = 1; j < pop_size; j++) {
//        cumpro[j] = cumpro[j-1] + fit[j] / sum_fit;
//    }
//    
//    // 轮盘赌选择
//    vector<vector<int>> new_pop(pop_size);
//    for (int i = 0; i < pop_size; i++) {
//        double pick = (double)rand() / RAND_MAX;
//        int selected = 0;
//        for (int j = 0; j < pop_size; j++) {
//            if (pick <= cumpro[j]) {
//                selected = j;
//                break;
//            }
//        }
//        new_pop[i] = pop[selected];
//    }
//    
//    pop.swap(new_pop);
//}

void Choice(vector<vector<int>>& pop) {
    const int pop_size = pop.size();
    const int tournament_size = 3;  // 锦标赛规模，可调整
    vector<vector<int>> new_pop(pop_size);
    
    // 预先计算所有个体的适应度
    vector<double> fitness(pop_size, 0.0);
    for (int i = 0; i < pop_size; i++) {
        double len = pathlen(pop[i]);
        fitness[i] = 1.0 / (len + 1e-10);
    }
    
    // 锦标赛选择
    for (int i = 0; i < pop_size; i++) {
        // 随机选择 tournament_size 个个体
        int best_index = -1;
        double best_fitness = -1.0;
        
        for (int j = 0; j < tournament_size; j++) {
            int random_index = rand() % pop_size;  // 随机选择一个个体
            if (fitness[random_index] > best_fitness || best_index == -1) {
                best_fitness = fitness[random_index];
                best_index = random_index;
            }
        }
        
        // 选择锦标赛中适应度最高的个体
        new_pop[i] = pop[best_index];
    }
    
    pop.swap(new_pop);
}
// 部分映射交叉
void Cross(vector<vector<int>>& pop) {
    for(int i = 0; i < pop.size(); i += 2) {
        if(i + 1 >= pop.size()) break;
        
        double pick = (double)rand() / RAND_MAX;
        if(pick > pcross) continue;
        
         // 选择两个父代
        int p1 = i;
        int p2 = i + 1;
        
        // 随机生成两个交叉点
        int pos1 = rand() % lenchrom;
        int pos2 = rand() % lenchrom;
        while(pos1 == pos2) {
            pos2 = rand() % lenchrom;
        }
        if(pos1 > pos2) swap(pos1, pos2);
        
        // 处理冲突
        int conflict1[lenchrom] = {0}, conflict2[lenchrom] = {0};
        int num1 = 0, num2 = 0;

        // 检查交叉区间外的冲突
        for(int j=0; j<lenchrom; j++)
        {
            if(j >= pos1 && j <= pos2) continue;
            // 检查p1的冲突
            for(int k=pos1; k<=pos2; k++)
            {
                if(chrom[p1][j] == chrom[p1][k])
                {
                    conflict1[num1++] = j;
                    break;
                }
            }
            // 检查p2的冲突
            for(int k=pos1; k<=pos2; k++)
            {
                if(chrom[p2][j] == chrom[p2][k])
                {
                    conflict2[num2++] = j;
                    break;
                }
            }
        }

        // 交换冲突位置的基因
        if(num1 == num2 && num1 > 0)
        {
            for(int j=0; j<num1; j++)
            {
                int idx1 = conflict1[j];
                int idx2 = conflict2[j];
                swap(chrom[p1][idx1], chrom[p2][idx2]);
            }
        }
    }
}

// 变异操作 - 使用交换变异
void mutation(vector<vector<int>>& pop) {
    for(int i = 0; i < pop.size(); ++i) {
        vector<int>& chr = pop[i];
        
        double pick = (double)rand() / RAND_MAX;
        if(pick > pmutation) continue;
        
        // 随机选择两个不同位置进行交换
        int pos1 = rand() % lenchrom;
        int pos2 = rand() % lenchrom;
        while(pos1 == pos2) {
            pos2 = rand() % lenchrom;
        }
        swap(chr[pos1], chr[pos2]);
    }
}

int main() {
    srand((unsigned)time(nullptr));
    clock_t start = clock();
    // 初始化种群
    init();
    
    // 计算初始种群的路径长度并找到最优解
    vector<double> distance_arr(sizepop);
    for(int i = 0; i < sizepop; ++i) {
        distance_arr[i] = pathlen(chrom[i]);
    }
    
    pair<int, double> best_idx = find_min(distance_arr);
    min_distance = best_idx.second;
    best_result = chrom[best_idx.first];
    int best_fit_gen = 0;
    
    // 进化迭代
    for(int gen = 0; gen < maxgen; ++gen) {
        Choice(chrom);
        Cross(chrom);
        mutation(chrom);
        
        // 更新距离数组并找到当前最优
        double current_best = min_distance;
        int current_best_idx = -1;
        for(int i = 0; i < sizepop; ++i) {
            distance_arr[i] = pathlen(chrom[i]);
            if(distance_arr[i] < current_best) {
                current_best = distance_arr[i];
                current_best_idx = i;
            }
        }
        
        // 更新全局最优
        if(current_best < min_distance) {
            min_distance = current_best;
            best_result = chrom[current_best_idx];
            best_fit_gen = gen + 1;
        }
        
        // 输出当前代的最优解
        if((gen + 1) % 10 == 0) {
            cout << "第" << gen + 1 << "代: 最短路径 = " << min_distance << endl;
        }
    }

    clock_t finish = clock();
    double duration = double(finish - start) / CLOCKS_PER_SEC;
    // 输出结果
    cout << "\n得到最短路径为:";
    for(size_t j = 0; j < best_result.size(); ++j) { 
        cout << best_result[j];
        if(j < best_result.size() - 1) cout << "->";
    }
    // 回到起点形成闭环
    cout << "->" << best_result[0] << endl;
    cout << "得到最短路径长度为:" << min_distance << endl;
    cout << "得到最短路径第一次出现在: " << best_fit_gen << endl;
    cout << "花费时间: " << duration << " s" << endl;
    return 0;
}
