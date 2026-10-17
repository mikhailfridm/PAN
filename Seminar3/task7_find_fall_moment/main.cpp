#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    double v0 = 50.0, g = 9.8, dt = 1.0, t_max = 12.0;

    vector<double> times, heights;
    for (double t = dt; t <= t_max; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        times.push_back(t);
        heights.push_back(h);
    }

    auto it = find_if(heights.begin(), heights.end(), [](double h) { return h <= 0.0; });

    if (it == heights.end()) {
        cout << "Падения не было в рассмотренном диапазоне времени." << endl;
    } else {
        size_t idx = distance(heights.begin(), it);
        cout << "Момент падения t = " << times[idx] << " с, высота = " << heights[idx] << " м" << endl;
    }

    return 0;
}
