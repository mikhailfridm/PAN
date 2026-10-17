#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;

int main() {
    vector<double> coords = {0.0, 5.0, 12.0, 20.0, 15.0, 25.0, 18.0};

    vector<double> diffs(coords.size());
    adjacent_difference(coords.begin(), coords.end(), diffs.begin());

    double totalPath = accumulate(diffs.begin() + 1, diffs.end(), 0.0,
        [](double sum, double d) { return sum + abs(d); });

    cout << "Суммарный путь ракеты: " << totalPath << " м" << endl;

    return 0;
}
