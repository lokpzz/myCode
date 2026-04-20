#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <iomanip>   
using namespace std;
 
int main() {
    // 1. 初始化
    const double L1 = 2.0;    // 路径1长度
    const double L2 = 4.0;    // 路径2长度
    double tau1 = 1.0;        // 路径1初始信息素
    double tau2 = 1.0;        // 路径2初始信息素
    const double Q = 4.0;     // 信息素总量常数
    const int iter_num = 10;  // 迭代次数

    // 设置随机数种子，确保每次运行结果不同
    srand(static_cast<unsigned int>(time(nullptr)));

    // 迭代过程
    for (int i = 0; i < iter_num; ++i) {
        // 2. 计算选择概率
        double denominator = (tau1 / L1) + (tau2 / L2); // 概率分母
        double p1 = (tau1 / L1) / denominator;
        double p2 = (tau2 / L2) / denominator;

        // 3. 生成0-1之间的随机数，模拟蚂蚁选择路径
        double rand_val = static_cast<double>(rand()) / RAND_MAX;
        int selected_path = 0;

        if (rand_val < p1) {
            selected_path = 1;
            tau1 += Q / L1;  // 更新路径1的信息素
        } else {
            selected_path = 2;
            tau2 += Q / L2;  // 更新路径2的信息素
        }

        // 4. 打印每轮迭代结果（保留2位小数）
        cout << "迭代" << (i + 1) << ": 选路径" << selected_path
                  << ", 路径1信息素=" << fixed << setprecision(2) << tau1
                  << ", 路径2信息素=" << tau2 << endl;
    }

    // 输出最终最优路径
    cout << "\n最优路径：" << (tau1 > tau2 ? "路径1（长度2）" : "路径2（长度4）") << endl;

    return 0;
}
