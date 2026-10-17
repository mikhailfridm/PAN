#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void generate(double v0, double g, double dt, double t_max, vector<double> &times, vector<double> &heights) {
    for (double t = dt; t <= t_max; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        times.push_back(t);
        heights.push_back(h);
    }
}

int main() {
    double g = 9.8, dt = 1.0, t_max = 12.0;

    vector<double> times1, heights1;
    vector<double> times2, heights2;
    generate(50.0, g, dt, t_max, times1, heights1);
    generate(70.0, g, dt, t_max, times2, heights2);

    auto maxIt1 = max_element(heights1.begin(), heights1.end());
    auto maxIt2 = max_element(heights2.begin(), heights2.end());
    size_t idxMax1 = distance(heights1.begin(), maxIt1);
    size_t idxMax2 = distance(heights2.begin(), maxIt2);

    auto fallIt1 = find_if(heights1.begin(), heights1.end(), [](double h) { return h <= 0.0; });
    auto fallIt2 = find_if(heights2.begin(), heights2.end(), [](double h) { return h <= 0.0; });

    cout << "Ракета 1: максимальная высота " << *maxIt1 << " м на t = " << times1[idxMax1] << " с";
    if (fallIt1 != heights1.end()) {
        size_t idxFall1 = distance(heights1.begin(), fallIt1);
        cout << ", упала на t = " << times1[idxFall1] << " с" << endl;
    } else {
        cout << ", всё ещё в воздухе" << endl;
    }

    cout << "Ракета 2: максимальная высота " << *maxIt2 << " м на t = " << times2[idxMax2] << " с";
    if (fallIt2 != heights2.end()) {
        size_t idxFall2 = distance(heights2.begin(), fallIt2);
        cout << ", упала на t = " << times2[idxFall2] << " с" << endl;
    } else {
        cout << ", всё ещё в воздухе" << endl;
    }

    cout << endl;
    if (*maxIt1 > *maxIt2) {
        cout << "Выше поднялась ракета 1" << endl;
    } else {
        cout << "Выше поднялась ракета 2" << endl;
    }

    if (fallIt1 != heights1.end() && fallIt2 != heights2.end()) {
        size_t idxFall1 = distance(heights1.begin(), fallIt1);
        size_t idxFall2 = distance(heights2.begin(), fallIt2);
        if (times1[idxFall1] > times2[idxFall2]) {
            cout << "Дольше в воздухе была ракета 1" << endl;
        } else {
            cout << "Дольше в воздухе была ракета 2" << endl;
        }
    }

    return 0;
}
