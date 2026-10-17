#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double> h = {0.0, 48.0, 93.0, 128.0, 142.0, 150.0, 138.0, 112.0, 72.0, 18.0};
    vector<double> smoothed(h.size());

    smoothed[0] = h[0];
    smoothed[h.size() - 1] = h[h.size() - 1];

    for (size_t i = 1; i + 1 < h.size(); i++) {
        smoothed[i] = (h[i - 1] + h[i] + h[i + 1]) / 3.0;
    }

    cout << "Исходная\tСглаженная" << endl;
    for (size_t i = 0; i < h.size(); i++) {
        cout << h[i] << "\t\t" << smoothed[i] << endl;
    }

    return 0;
}
