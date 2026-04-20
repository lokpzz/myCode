#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <limits>
#include <iomanip>  // 用于格式化输出路径长度

using namespace std;

// 城市结构体：存储坐标
struct City {
    double x, y;
};

// 粒子结构体：适配TSP的离散化定义
struct Particle {
    vector<int> path;          // 当前路径（城市索引序列）
    double fitness;            // 当前路径长度（适应度，越小越好）
    vector<int> pbest;         // 个体最优路径
    double pbest_fitness;      // 个体最优路径长度
    vector<pair<int, int>> velocity; // 速度：用交换对表示离散速度
};

// 计算两城市欧氏距离
double calculateDistance(const City& c1, const City& c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    return sqrt(dx*dx + dy*dy);
}

// 计算路径总长度（适应度函数）
double calculatePathLength(const vector<int>& path, const vector<City>& cities) {
    double total = 0.0;
    int n = path.size();
    for (int i = 0; i < n; ++i) {
        int curr = path[i];
        int next = path[(i+1)%n]; // 最后回到起点
        total += calculateDistance(cities[curr], cities[next]);
    }
    return total;
}

// PSO初始化：生成粒子群初始状态
void initializeParticles(vector<Particle>& particles, int num_particles, int num_cities, const vector<City>& cities) {
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < num_particles; ++i) {
        Particle p;
        // 初始化随机路径
        p.path.resize(num_cities);
        for (int j = 0; j < num_cities; ++j) p.path[j] = j;
        shuffle(p.path.begin(), p.path.end(), gen);
        // 计算初始适应度
        p.fitness = calculatePathLength(p.path, cities);
        // 初始化pbest为当前路径
        p.pbest = p.path;
        p.pbest_fitness = p.fitness;
        // 初始化速度（随机交换对，100城市时调大交换对数量，提升搜索能力）
        int vel_size = num_cities / 3;  // 100城市：交换对数量从1/2改为1/3，避免过度扰动
        p.velocity.resize(vel_size);
        for (int j = 0; j < vel_size; ++j) {
            uniform_int_distribution<> dis(0, num_cities-1);
            int a = dis(gen), b = dis(gen);
            p.velocity[j] = {a, b};
        }
        particles.push_back(p);
    }
}

// 应用速度更新路径（修复swap关键字冲突 + 正确访问pair）
void applyVelocity(vector<int>& path, const vector<pair<int, int>>& velocity) {
    for (const auto& swap_pair : velocity) {
        int idx1 = swap_pair.first;
        int idx2 = swap_pair.second;
        if (idx1 != idx2) { // 避免交换同一个位置，无意义操作
            std::swap(path[idx1], path[idx2]);
        }
    }
}

// 更新粒子速度（离散版：结合pbest和gbest，适配100城市）
void updateVelocity(Particle& p, const vector<int>& gbest, int num_cities, double c1 = 1.2, double c2 = 1.8) {
    // 100城市调优参数：c1略小（个体学习），c2略大（全局学习），加快收敛
    random_device rd;
    mt19937 gen(rd());
    
    // 清空旧速度，重新生成
    p.velocity.clear();
    int vel_size = num_cities / 3;  // 和初始化保持一致
    
    // 生成向pbest学习的交换对
    int pbest_learn = static_cast<int>(c1 * vel_size);
    for (int i = 0; i < pbest_learn; ++i) {
        uniform_int_distribution<> idx_dis(0, num_cities-1);
        int a = idx_dis(gen), b = idx_dis(gen);
        p.velocity.push_back({a, b});
    }
    
    // 生成向gbest学习的交换对
    int gbest_learn = static_cast<int>(c2 * vel_size);
    for (int i = 0; i < gbest_learn; ++i) {
        uniform_int_distribution<> idx_dis(0, num_cities-1);
        int a = idx_dis(gen), b = idx_dis(gen);
        p.velocity.push_back({a, b});
    }
    
    // 限制速度长度（对应Vmax截断）
    if (p.velocity.size() > vel_size) {
        p.velocity.resize(vel_size);
    }
}

// 主PSO求解TSP函数
vector<int> psoTSP(const vector<City>& cities, int num_particles = 100, int max_iter = 2000) {
    // 100城市调优：粒子数从50→100，迭代数从1000→2000，提升搜索广度和深度
    int num_cities = cities.size();
    vector<Particle> particles;
    
    // 1. 初始化粒子群
    initializeParticles(particles, num_particles, num_cities, cities);
    
    // 初始化全局最优（gbest）
    vector<int> gbest;
    double gbest_fitness = numeric_limits<double>::max();
    for (auto& p : particles) {
        if (p.fitness < gbest_fitness) {
            gbest_fitness = p.fitness;
            gbest = p.path;
        }
    }
    
    // 迭代优化（PSO核心闭环）
    for (int iter = 0; iter < max_iter; ++iter) {
        // 每轮迭代先重置全局最优的临时值
        double current_gbest_fitness = gbest_fitness;
        vector<int> current_gbest = gbest;
        
        for (auto& p : particles) {
            // 5. 先更新速度和位置（演化计算）
            updateVelocity(p, current_gbest, num_cities);
            applyVelocity(p.path, p.velocity);
            
            // 重新计算更新后的适应度
            p.fitness = calculatePathLength(p.path, cities);
            
            // 3. 更新pbest（个体最优）
            if (p.fitness < p.pbest_fitness) {
                p.pbest = p.path;
                p.pbest_fitness = p.fitness;
            }
            
            // 4. 更新gbest（全局最优）：仅用更新后的pbest判断
            if (p.pbest_fitness < current_gbest_fitness) {
                current_gbest_fitness = p.pbest_fitness;
                current_gbest = p.pbest;
            }
        }
        
        // 本轮所有粒子更新完成后，再更新全局最优
        gbest_fitness = current_gbest_fitness;
        gbest = current_gbest;
        
        // 每200代打印进度
        if (iter % 20 == 0) {
            cout << "迭代次数: " << setw(4) << iter 
                 << "  当前最优路径长度: " << fixed << setprecision(2) << gbest_fitness << endl;
        }
    }
    
    return gbest;
}

// 生成N个随机城市
vector<City> generateRandomCities(int num_cities) {
    vector<City> cities;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 100.0); // 坐标在0~100之间，避免距离过大/过小
    
    for (int i = 0; i < num_cities; ++i) {
        City c;
        c.x = dis(gen);
        c.y = dis(gen);
        cities.push_back(c);
    }
    return cities;
}

// 测试主函数
int main() {
    const int NUM_CITIES = 100;    // 固定100个城市
    const int NUM_PARTICLES = 100; // 粒子数：100
    const int MAX_ITER = 500;     // 迭代次数
    
    // 生成100个随机坐标的城市
    vector<City> cities = generateRandomCities(NUM_CITIES);
    cout << "已生成" << NUM_CITIES << "个随机城市，开始PSO优化TSP..." << endl;
    cout << "=============================================" << endl;
    
    // 调用PSO求解TSP
    vector<int> best_path = psoTSP(cities, NUM_PARTICLES, MAX_ITER);
    
    // 输出结果
    cout << "=============================================" << endl;
    cout << "\n最优路径（前20个城市 + 回到起点）: ";
    for (int i = 0; i < 100; ++i) {
        cout << best_path[i] << " -> ";
    }
    cout << best_path[0] << endl;
    
    // 输出最优路径长度（保留2位小数）
    double best_length = calculatePathLength(best_path, cities);
    cout << "\n100城市TSP最优路径长度: " << fixed << setprecision(2) << best_length << endl;
    cout << "\nPSO优化完成！" << endl;
    
    return 0;
}
