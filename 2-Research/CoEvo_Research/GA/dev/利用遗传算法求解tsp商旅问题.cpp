#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

// -------------------------- 1. 全局参数配置（可按需调整） --------------------------
const int CITY_NUM = 100;          // 城市数量（测试用10，可扩展到50/100）
const int POPULATION_SIZE = 500;   // 种群规模
const int MAX_GENERATIONS = 1000;  // 最大迭代次数
const double CROSSOVER_RATE = 0.85; // 交叉概率
const double MUTATION_RATE = 0.1;  // 变异概率
const int tournamentSize = 5;      //多元锦标赛单次抽取数

// -------------------------- 2. 数据结构定义 --------------------------
// 城市结构体
struct City {
    int id;         // 城市编号
    double x;       // x坐标
    double y;       // y坐标
    City(int id_, double x_, double y_) : id(id_), x(x_), y(y_) {}
};

// 路径（染色体）类型：城市索引的排列（如[2,0,1,3]）
typedef vector<int> Path;

// -------------------------- 3. 工具函数 --------------------------
/**
 * @brief 生成随机城市坐标（范围：0~100）
 * @return 城市列表
 */
vector<City> beginCity() {
    vector<City> cities;
    srand((unsigned)time(nullptr)); // 初始化随机数种子
    for (int i = 0; i < CITY_NUM; ++i) {
        double x = rand() % 100;
        double y = rand() % 100;
        cities.emplace_back(i, x, y);
    }
    return cities;
}

/**
 * @brief 计算两个城市的欧几里得距离
 * @param c1 城市1
 * @param c2 城市2
 * @return 距离
 */
double cityDistance(const City& c1, const City& c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    return sqrt(dx*dx + dy*dy);
}

/**
 * @brief 计算一条路径的总长度（含返回起点）
 * @param path 路径（城市索引排列）
 * @param cities 城市列表
 * @return 总长度
 */
double PathLength(const Path& path, const vector<City>& cities) {
    double totalLen = 0.0;
    // 遍历路径中相邻城市
    for (int i = 0; i < path.size(); ++i) {
        int curr = path[i];
        int next = path[(i+1) % path.size()]; // 最后一个城市返回起点
        totalLen += cityDistance(cities[curr], cities[next]);
    }
    return totalLen;
}

/**
 * @brief 计算路径的适应度（路径长度的倒数，避免除零）
 * @param path 路径
 * @param cities 城市列表
 * @return 适应度值
 */
double Fitness(const Path& path, const vector<City>& cities) {
    double len = PathLength(path, cities);
    return 1.0 / (len + 1e-6); // 加极小值避免除零
}

/**
 * @brief 初始化种群：生成POPULATION_SIZE个合法路径（无重复城市）
 * @param cities 城市列表
 * @return 初始种群
 */
vector<Path> initPopulation(const vector<City>& cities) {
    vector<Path> population;
    Path basePath;
    // 生成基础路径：0,1,2,...,CITY_NUM-1
    for (int i = 0; i < CITY_NUM; ++i) {
        basePath.push_back(i);
    }
    // 随机打乱基础路径生成种群
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        Path newPath = basePath;
        random_shuffle(newPath.begin(), newPath.end()); // 随机打乱
        population.push_back(newPath);
    }
    return population;
}

/**
 * @brief 锦标赛选择：从种群中选最优个体（TSP专用）
 * @param population 待选择的种群（路径集合）
 * @param cities 城市列表（用于计算路径适应度）
 * @param tournamentSize 锦标赛规模（推荐3~5）
 * @return 选中的最优路径
 */
Path Selection(const vector<Path>& population, const vector<City>& cities) {
    // 1. 随机选 tournamentSize 个候选个体（可重复选，即“有放回抽样”）
    vector<Path> candidates;
    for (int i = 0; i < tournamentSize; ++i) {
        int randIdx = rand() % population.size();  // 随机选一个个体的索引
        candidates.push_back(population[randIdx]);
    }

    // 2. 从候选中选最优个体（TSP中路径长度越短，适应度越高）
    Path bestCandidate = candidates[0];
    double minLen = PathLength(bestCandidate, cities);  // 最优路径长度（越小越好）
    
    for (const auto& cand : candidates) {
        double len = PathLength(cand, cities);
        if (len < minLen) {  // TSP核心：路径更短则更优
            minLen = len;
            bestCandidate = cand;
        }
    }

    return bestCandidate;
}
/**
 * @brief 顺序交叉（OX）：TSP专用交叉，保证子代无重复城市
 * @param parent1 父代1
 * @param parent2 父代2
 * @return 交叉后的子代
 */
Path orderCrossover(const Path& parent1, const Path& parent2) {
    if (rand() > CROSSOVER_RATE * RAND_MAX) {
        return parent1; // 不交叉，直接返回父代1
    }

    Path child(CITY_NUM, -1); // 初始化子代，-1表示未填充
    // 1. 随机选交叉区间[start, end]
    int start = rand() % CITY_NUM;
    int end = rand() % CITY_NUM;
    if (start > end) swap(start, end);

    // 2. 复制父代1的交叉区间到子代
    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    // 3. 按父代2的顺序填充剩余位置（去重）
    int idx = 0; // 父代2的遍历索引
    for (int i = 0; i < CITY_NUM; ++i) {
        if (child[i] != -1) continue; // 跳过已填充位置
        // 找父代2中不在子代的城市
        while (find(child.begin(), child.end(), parent2[idx]) != child.end()) {
            idx++;
        }
        child[i] = parent2[idx];
        idx++;
    }
    return child;
}

/**
 * @brief 逆序变异：随机反转一段路径，保证合法性
 * @param path 待变异的路径
 * @return 变异后的路径
 */
Path reverseMutation(const Path& path) {
    Path newPath = path;
    if (rand() > MUTATION_RATE * RAND_MAX) {
        return newPath; // 不变异，直接返回
    }

    // 随机选变异区间[start, end]
    int start = rand() % CITY_NUM;
    int end = rand() % CITY_NUM;
    if (start > end) swap(start, end);

    // 反转区间内的城市顺序
    reverse(newPath.begin() + start, newPath.begin() + end + 1);
    return newPath;
}

/**
 * @brief 找到种群中的最优路径（长度最短）
 * @param population 种群
 * @param cities 城市列表
 * @return 最优路径+路径长度
 */
pair<Path, double> findBestPath(const vector<Path>& population, const vector<City>& cities) {
    Path bestPath = population[0];
    double minLen = PathLength(bestPath, cities);

    for (const auto& path : population) {
        double len = PathLength(path, cities);
        if (len < minLen) {
            minLen = len;
            bestPath = path;
        }
    }
    return make_pair(bestPath, minLen);
}

// -------------------------- 4. 主函数 --------------------------
int main() {
    // 1. 生成随机城市（可替换为自定义城市坐标）
    vector<City> cities = beginCity();
    cout << "===== 城市坐标 =====" << endl;
    for (const auto& city : cities) {
        cout << "城市" << city.id << ": (" << city.x << ", " << city.y << ")" << endl;
    }

    // 2. 初始化种群
    vector<Path> population = initPopulation(cities);
    Path bestPathOverall;       // 全局最优路径
    double minLenOverall = 1e9; // 全局最优路径长度

    // 3. 迭代进化
    cout << "\n===== 迭代过程 =====" << endl;
    for (int gen = 0; gen < MAX_GENERATIONS; ++gen) {
        // 生成新一代种群
        vector<Path> newPopulation;
        while (newPopulation.size() < POPULATION_SIZE) {
            // 多元锦标赛选择父代
            Path parent1 = Selection(population, cities);
            Path parent2 = Selection(population, cities);

            // 交叉生成子代
            Path child = orderCrossover(parent1, parent2);

            // 变异
            child = reverseMutation(child);

            // 添加到新种群
            newPopulation.push_back(child);
        }

        // 更新种群
        population = newPopulation;

        // 记录当代最优
        pair<Path, double> bestPair = findBestPath(population, cities);
        Path bestPathCurr = bestPair.first;
        double minLenCurr = bestPair.second;
        
        if (minLenCurr < minLenOverall) {
            minLenOverall = minLenCurr;
            bestPathOverall = bestPathCurr;
        }

        // 每20代输出一次进度
        if ((gen + 1) % 20 == 0) {
            cout << "第" << gen + 1 << "代 | 最优路径长度：" << minLenCurr << endl;
        }
    }

    // 4. 输出最终结果
    cout << "\n===== 最终结果 =====" << endl;
    cout << "最优路径：";
    for (int cityId : bestPathOverall) {
        cout << cityId << " → ";
    }
    cout << bestPathOverall[0] << endl; // 回到起点
    cout << "最优路径长度：" << minLenOverall << endl;

    return 0;
}

