#include<bits/stdc++.h>
using namespace std;

// 参数
const int maxgen = 200;     // 最大代数
const int sizepop = 100;    // 种群数目
const double pcross = 0.6;  // 交叉概率
const double pmutation = 0.1;// 变异概率
const int lenchrom = 14;    // 染色体长度（城市数）

//测试用例
vector<pair<double, double>> city_pos = {
    {16.47,96.10},{16.47,94.44},{20.09,92.54},{22.39,93.37},
    {25.23,97.24},{22.00,96.05},{20.47,97.02},{17.20,96.29},
    {16.30,97.38},{14.05,98.12},{16.53,97.38},{21.52,95.59},
    {19.41,97.13},{20.09,92.55}
}; 

vector<vector<int>> chrom;
vector<int> best_result;
double min_distance;

// 种群初始化
void init() {
    chrom.resize(sizepop);
    for(int i = 0; i < sizepop; ++i) {
        vector<int>& chr = chrom[i];
        chr.resize(lenchrom);
        iota(chr.begin(), chr.end(), 1);
        
        // 随机打乱
        random_shuffle(chr.begin(), chr.end());
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
    double min_val = arr[0];
    for(int i = 1; i < arr.size(); ++i) {
        if(arr[i] < min_val) {
            min_val = arr[i];
            idx = i;
        }
    }
    return {idx, min_val};
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

// 选择
void Choice(vector<vector<int>>& pop) {
    const int pop_size = pop.size();
    vector<double> fit(pop_size, 0.0);
    vector<double> cum_prob(pop_size, 0.0);
    double sum_fit = 0.0;
    
    // 计算适应度和总适应度
    for (int j = 0; j < pop_size; j++) {
        double len = pathlen(pop[j]);
        fit[j] = 1.0 / (len + 1e-10);
        sum_fit += fit[j];
    }
    
    cum_prob[0] = fit[0] / sum_fit;
    for (int j = 1; j < pop_size; j++) {
        cum_prob[j] = cum_prob[j-1] + fit[j] / sum_fit;
    }
    
    // 轮盘赌选择
    vector<vector<int>> new_pop(pop_size);
    for (int i = 0; i < pop_size; i++) {
        double pick = (double)rand() / RAND_MAX;
        int selected = 0;
        for (int j = 0; j < pop_size; j++) {
            if (pick <= cum_prob[j]) {
                selected = j;
                break;
            }
        }
        new_pop[i] = pop[selected];
    }
    
    pop.swap(new_pop);
}

// 交叉 - 使用部分映射交叉(PMX)
void Cross(vector<vector<int>>& pop) {
    for(int i = 0; i < pop.size(); i += 2) {
        if(i + 1 >= pop.size()) break;
        
        double pick = (double)rand() / RAND_MAX;
        if(pick > pcross) continue;
        
        vector<int>& parent1 = pop[i];
        vector<int>& parent2 = pop[i+1];
        
        // 随机生成两个交叉点
        int pos1 = rand() % lenchrom;
        int pos2 = rand() % lenchrom;
        while(pos1 == pos2) {
            pos2 = rand() % lenchrom;
        }
        if(pos1 > pos2) swap(pos1, pos2);
        
        // 创建子代
        vector<int> child1(lenchrom, -1);
        vector<int> child2(lenchrom, -1);
        
        // 复制交叉段
        for(int j = pos1; j <= pos2; j++) {
            child1[j] = parent1[j];
            child2[j] = parent2[j];
        }
        
        // 填充剩余位置
        for(int j = 0; j < lenchrom; j++) {
            if(j >= pos1 && j <= pos2) continue;
            
            // 为child1填充
            int city = parent2[j];
            while(find(child1.begin(), child1.end(), city) != child1.end()) {
                int index = find(parent1.begin(), parent1.end(), city) - parent1.begin();
                city = parent2[index];
            }
            child1[j] = city;
            
            // 为child2填充
            city = parent1[j];
            while(find(child2.begin(), child2.end(), city) != child2.end()) {
                int index = find(parent2.begin(), parent2.end(), city) - parent2.begin();
                city = parent1[index];
            }
            child2[j] = city;
        }
        
        // 替换父代
        parent1 = child1;
        parent2 = child2;
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

// 精英保留策略
void elitism(vector<vector<int>>& pop, const vector<int>& best_chrom) {
    // 找到当前种群中最差的个体
    int worst_idx = 0;
    double worst_len = pathlen(pop[0]);
    for(int i = 1; i < pop.size(); ++i) {
        double len = pathlen(pop[i]);
        if(len > worst_len) {
            worst_len = len;
            worst_idx = i;
        }
    }
    
    // 用历史最优替换最差个体
    pop[worst_idx] = best_chrom;
}

int main() {
    srand((unsigned)time(nullptr));
    
    // 初始化种群
    init();
    best_result.resize(lenchrom);
    
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
    clock_t start = clock();
    for(int gen = 0; gen < maxgen; ++gen) {
        // 选择
        Choice(chrom);
        
        // 交叉
        Cross(chrom);
        
        // 变异
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
        
        // 精英保留
        elitism(chrom, best_result);
        
        // 可选：输出当前代的最优解
        if((gen + 1) % 50 == 0) {
            cout << "第" << gen + 1 << ": 最短路径 = " << min_distance << endl;
        }
    }
    clock_t finish = clock();
    double duration = double(finish - start) / CLOCKS_PER_SEC;
    
    // 输出结果
    cout << "\n=== TSP Solution ===" << endl;
    cout << "Best tour: ";
    for(size_t j = 0; j < best_result.size(); ++j) { 
        cout << best_result[j];
        if(j < best_result.size() - 1) cout << "->";
    }
    // 回到起点形成闭环
    cout << "->" << best_result[0] << endl;
    
    cout << "Shortest distance: " << min_distance << endl;
    cout << "Found at generation: " << best_fit_gen << endl;
    cout << "Total generations: " << maxgen << endl;
    cout << "花费: " << duration << " seconds" << endl;
    
    return 0;
}
