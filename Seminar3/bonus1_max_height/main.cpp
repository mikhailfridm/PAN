#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    double v0 = 50.0, g = 9.8, dt = 1.0;

    vector<double> heights;
    for (double t = 0.0; ; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        if (h < 0) break;
        heights.push_back(h);
    }

    auto maxIt = max_element(heights.begin(), heights.end());
    size_t idx = distance(heights.begin(), maxIt);

    cout << "Максимальная высота: " << *maxIt << " м на t = " << idx * dt << " с" << endl;

    return 0;
}
