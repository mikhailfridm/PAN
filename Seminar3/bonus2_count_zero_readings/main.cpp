#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<double> accel = {2.3, 0.0, 1.5, 0.0, 3.2, 0.0, 4.1, 2.8, 0.0};

    int zeroCount = count(accel.begin(), accel.end(), 0.0);

    cout << "Нулевых показаний датчика: " << zeroCount << endl;

    return 0;
}
