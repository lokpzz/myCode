#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <limits>

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

// PSO初始化：生成粒子群初始状态（PSO第一步）
void initializeParticles(vector<Particle>& particles, int num_particles, int num_cities, const vector<City>& cities) {
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < num_particles; ++i) {
        Particle p;
        // 初始化随机路径
        p.path.resize(num_cities);
        for (int j = 0; j < num_cities; ++j) p.path[j] = j;
        shuffle(p.path.begin(), p.path.end(), gen);
        // 计算初始适应度（PSO第二步：适应度评价）
        p.fitness = calculatePathLength(p.path, cities);
        // 初始化pbest为当前路径（PSO第三步：pbest初始）
        p.pbest = p.path;
        p.pbest_fitness = p.fitness;
        // 初始化速度（随机交换对）
        int vel_size = num_cities / 2;
        p.velocity.resize(vel_size);
        for (int j = 0; j < vel_size; ++j) {
            uniform_int_distribution<> dis(0, num_cities-1);
            int a = dis(gen), b = dis(gen);
            p.velocity[j] = {a, b};
        }
        particles.push_back(p);
    }
}

// 应用速度更新路径（PSO第五步：演化计算-位置更新）
void applyVelocity(vector<int>& path, const vector<pair<int, int>>& velocity) {
    for (auto& swap : velocity) {
        swap(path[swap.first], path[swap.second]);
    }
}

// 更新粒子速度（离散版：结合pbest和gbest，PSO第五步：演化计算-速度更新）
void updateVelocity(Particle& p, const vector<int>& gbest, int num_cities, double c1 = 1.5, double c2 = 1.5) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    
    // 清空旧速度，重新生成
    p.velocity.clear();
    int vel_size = num_cities / 2;
    
    // 生成向pbest学习的交换对
    for (int i = 0; i < (int)(c1 * vel_size); ++i) {
        uniform_int_distribution<> idx_dis(0, num_cities-1);
        int a = idx_dis(gen), b = idx_dis(gen);
        p.velocity.push_back({a, b});
    }
    
    // 生成向gbest学习的交换对
    for (int i = 0; i < (int)(c2 * vel_size); ++i) {
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
vector<int> psoTSP(const vector<City>& cities, int num_particles = 50, int max_iter = 1000) {
    int num_cities = cities.size();
    vector<Particle> particles;
    
    // 1. 初始化粒子群（PSO第一步）
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
        for (auto& p : particles) {
            // 2. 适应度评价（已在初始化/更新后计算）
            // 3. 更新pbest（PSO第三步）
            if (p.fitness < p.pbest_fitness) {
                p.pbest = p.path;
                p.pbest_fitness = p.fitness;
            }
            
            // 4. 更新gbest（PSO第四步）
            if (p.pbest_fitness < gbest_fitness) {
                gbest_fitness = p.pbest_fitness;
                gbest = p.pbest;
            }
            
            // 5. 演化计算：更新速度和位置（PSO第五步）
            updateVelocity(p, gbest, num_cities);
            applyVelocity(p.path, p.velocity);
            
            // 重新计算更新后的适应度
            p.fitness = calculatePathLength(p.path, cities);
        }
        
        // 6. 终止判定（迭代次数达标则退出）
        if (iter % 100 == 0) { // 每100代打印进度
            cout << "迭代次数: " << iter << "  当前最优路径长度: " << gbest_fitness << endl;
        }
    }
    
    return gbest;
}

// 测试主函数
int main() {
    // 测试用例：5个城市的坐标
    vector<City> cities = {
        {0, 0}, {1, 2}, {3, 1}, {5, 4}, {2, 5}
    };
    
    // 调用PSO求解TSP
    vector<int> best_path = psoTSP(cities, 50, 1000);
    
    // 输出结果
    cout << "\n最优路径: ";
    for (int idx : best_path) {
        cout << idx << " -> ";
    }
    cout << best_path[0] << endl; // 回到起点
    cout << "最优路径长度: " << calculatePathLength(best_path, cities) << endl;
    
    return 0;
}