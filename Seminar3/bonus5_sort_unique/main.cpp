#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<double> xCoords = {5.0, 3.0, 5.0, 8.0, 3.0, 1.0, 8.0, 2.0};

    sort(xCoords.begin(), xCoords.end());
    auto newEnd = unique(xCoords.begin(), xCoords.end());
    xCoords.erase(newEnd, xCoords.end());

    cout << "Координаты без дубликатов:" << endl;
    for (double x : xCoords) {
        cout << x << endl;
    }

    return 0;
}
