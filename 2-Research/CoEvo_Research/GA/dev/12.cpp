#include <iostream>
#include <cmath>
#include <iomanip>  // 用于控制输出格式

using namespace std;

// 定义我们的目标函数
double f(double x) {
    return x + 10 * sin(5 * x) + 7 * cos(4 * x);
}

int main() {
    // 1. 定义搜索参数
    double start = 0.0;      // 区间起点
    double end = 10.0;       // 区间终点
    double step = 0.001;     // 步长（越小越精确）

    // 2. 初始化变量
    double max_value = -1000000.0;  // 初始化为一个很小的数
    double max_x = start;           // 记录最大值对应的x
    int count = 0;                  // 计数器，记录计算了多少次

    // 3. 开始网格搜索
    cout << "开始搜索..." << endl;

    for (double x = start; x <= end; x += step) {
        double current_value = f(x);  // 计算当前点的函数值

        // 如果找到更大的值，更新记录
        if (current_value > max_value) {
            max_value = current_value;
            max_x = x;
        }
    }

    // 4. 输出最终结果
    cout << "\n=== 搜索结果 ===" << endl;
    cout << "总共计算了 " << count << " 个点" << endl;
    cout << "最大值点: x = " << fixed << setprecision(6) << max_x << endl;
    cout << "最大值: f(x) = " << fixed << setprecision(6) << max_value << endl;

    return 0;
}
