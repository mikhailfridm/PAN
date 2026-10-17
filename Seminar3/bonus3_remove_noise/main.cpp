#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<double> temp = {85.0, 90.0, -150.0, 95.0, 300.0, 88.0, 92.0, -200.0};

    auto newEnd = remove_if(temp.begin(), temp.end(), [](double t) { return t < -100.0 || t > 200.0; });
    temp.erase(newEnd, temp.end());

    cout << "Очищенные показания температуры:" << endl;
    for (double t : temp) {
        cout << t << endl;
    }

    return 0;
}
