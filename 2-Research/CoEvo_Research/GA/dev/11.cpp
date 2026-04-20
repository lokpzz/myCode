
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// 随机数生成器
random_device rd;//真随机数设备
mt19937 gen(rd());//梅森旋转算法生成器:提供高质量、可预测的伪随机数序列，用于控制遗传算法中的所用随机操作

// 目标函数
double f(double x) {
    return x + 10 * sin(5 * x) + 7 * cos(4 * x);
}

// 将二进制字符串转换为十进制数
double binary_to_double(const string& binary, double min_val, double max_val, int binary_length) {
    // 将二进制字符串转换为整数
    unsigned long value = 0;
    for (char bit : binary) {
        value = (value << 1) | (bit - '0');
    }

    // 映射到实际区间 [min_val, max_val]
    return min_val + (max_val - min_val) * value / ((1 << binary_length) - 1);
}

// 将十进制数转换为二进制字符串
string double_to_binary(double x, double min_val, double max_val, int binary_length) {
    // 映射到 [0, 2^binary_length - 1]
    unsigned long value = (x - min_val) * ((1 << binary_length) - 1) / (max_val - min_val);

    // 转换为二进制字符串
    string binary;
    for (int i = binary_length - 1; i >= 0; i--) {
        binary += ((value >> i) & 1) ? '1' : '0';
    }
    return binary;
}

// 初始化种群
vector<string> initialize_population(int population_size, int chromosome_length) {
    vector<string> population;
    uniform_int_distribution<int> dis(0, 1);

    for (int i = 0; i < population_size; i++) {
        string chromosome;
        for (int j = 0; j < chromosome_length; j++) {
            chromosome += (dis(gen) ? '1' : '0');
        }
        population.push_back(chromosome);
    }
    return population;
}

// 计算适应度
vector<double> calculate_fitness(const vector<string>& population,
    double min_val, double max_val,
    int chromosome_length) {
    vector<double> fitness_values;
    for (const auto& chromosome : population) {
        double x = binary_to_double(chromosome, min_val, max_val, chromosome_length);
        fitness_values.push_back(f(x));  // 函数值越大，适应度越好
    }
    return fitness_values;
}

// 选择操作（轮盘赌选择）：适应度高的个体更可能被选中
vector<string> selection(const vector<string>& population,
    const vector<double>& fitness_values) {
    vector<string> selected;
    uniform_real_distribution<double> dis(0.0, 1.0);

    // 计算总适应度
    double total_fitness = 0.0;
    for (double fitness : fitness_values) {
        total_fitness += fitness;
    }

    // 轮盘赌选择
    for (int i = 0; i < population.size(); i++) {
        double random_value = dis(gen) * total_fitness;
        double cumulative = 0.0;

        for (int j = 0; j < population.size(); j++) {
            cumulative += fitness_values[j];
            if (cumulative >= random_value) {
                selected.push_back(population[j]);
                break;
            }
        }
    }

    return selected;
}

// 交叉操作（单点交叉）：随机选择交叉点 交换后面的基因
void crossover(vector<string>& population, double crossover_rate) {
    uniform_real_distribution<double> dis(0.0, 1.0);
    uniform_int_distribution<int> point_dis(1, population[0].size() - 2);

    for (int i = 0; i < population.size(); i += 2) {
        if (i + 1 < population.size() && dis(gen) < crossover_rate) {
            int crossover_point = point_dis(gen);

            string& parent1 = population[i];
            string& parent2 = population[i + 1];

            // 交换基因
            string child1 = parent1.substr(0, crossover_point) +
                parent2.substr(crossover_point);
            string child2 = parent2.substr(0, crossover_point) +
                parent1.substr(crossover_point);

            population[i] = child1;
            population[i + 1] = child2;
        }
    }
}

// 变异操作：随机改变某些基因 用uniform_real_distribution/unifor_int_distribution函数进行生成指定范围内的均匀分布的随机浮点数
void mutation(vector<string>& population, double mutation_rate) {
    uniform_real_distribution<double> dis(0.0, 1.0);
    uniform_int_distribution<int> pos_dis(0, population[0].size() - 1);

    for (auto& chromosome : population) {
        for (char& bit : chromosome) {
            if (dis(gen) < mutation_rate) {
                bit = (bit == '0') ? '1' : '0';  //以一定的概率翻转每个比特位
            }
        }
    }
}

// 找到最佳个体
pair<double, double> find_best(const vector<string>& population,
    const vector<double>& fitness_values,
    double min_val, double max_val,
    int chromosome_length) {
    int best_index = 0;
    double best_fitness = fitness_values[0];

    for (int i = 1; i < fitness_values.size(); i++) {
        if (fitness_values[i] > best_fitness) {
            best_fitness = fitness_values[i];
            best_index = i;
        }
    }

    double best_x = binary_to_double(population[best_index], min_val, max_val, chromosome_length);
    return { best_x, best_fitness };
}

int main() {
    cout << "=== 遗传算法求解函数最大值 ===" << endl;
    cout << "函数: f(x) = x + 10*sin(5x) + 7*cos(4x)" << endl;
    cout << "区间: [0, 10]" << endl << endl;

    // 算法参数设置
    const int POPULATION_SIZE = 50;      // 种群大小
    const int CHROMOSOME_LENGTH = 20;    // 染色体长度（二进制位数）：越大精度越高
    const int MAX_GENERATIONS = 100;     // 最大迭代次数
    const double CROSSOVER_RATE = 0.8;   // 交叉概率
    const double MUTATION_RATE = 0.01;   // 变异概率：越大变异率越高
    const double MIN_VAL = 0.0;          // 区间最小值
    const double MAX_VAL = 10.0;         // 区间最大值

    // 初始化种群
    vector<string> population = initialize_population(POPULATION_SIZE, CHROMOSOME_LENGTH);

    // 运行遗传算法
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        // 计算适应度
        vector<double> fitness_values = calculate_fitness(population, MIN_VAL, MAX_VAL, CHROMOSOME_LENGTH);

        // 选择
        vector<string> selected = selection(population, fitness_values);

        // 交叉
        crossover(selected, CROSSOVER_RATE);

        // 变异
        mutation(selected, MUTATION_RATE);

        // 更新种群
        population = selected;
    }

    // 输出最终结果
    vector<double> final_fitness = calculate_fitness(population, MIN_VAL, MAX_VAL, CHROMOSOME_LENGTH);
    auto [best_x, best_fitness] = find_best(population, final_fitness, MIN_VAL, MAX_VAL, CHROMOSOME_LENGTH);

    cout << "\n=== 最终结果 ===" << endl;
    cout << "最优解: x = " << fixed << setprecision(6) << best_x << endl;
    cout << "最大值: f(x) = " << fixed << setprecision(6) << best_fitness << endl;
    cout << "染色体长度: " << CHROMOSOME_LENGTH << " 位" << endl;
    cout << "种群大小: " << POPULATION_SIZE << endl;
    cout << "迭代次数: " << MAX_GENERATIONS << endl;

    return 0;
}

