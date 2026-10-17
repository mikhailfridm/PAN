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

    auto newEnd = remove_if(heights.begin(), heights.end(), [](double h) { return h < 10.0; });
    heights.erase(newEnd, heights.end());

    cout << "Высоты не ниже 10 м:" << endl;
    for (double h : heights) {
        cout << h << endl;
    }

    return 0;
}
