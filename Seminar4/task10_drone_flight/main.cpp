#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class DroneFlight {
private:
    vector<double> x, y;
    double totalDistance;

public:
    DroneFlight() : totalDistance(0.0) {}

    void addPoint(double newX, double newY) {
        if (!x.empty()) {
            double dx = newX - x.back();
            double dy = newY - y.back();
            totalDistance += sqrt(dx * dx + dy * dy);
        }
        x.push_back(newX);
        y.push_back(newY);
    }

    double getTotalDistance() {
        return totalDistance;
    }

    void printPath() {
        cout << "Точки маршрута:" << endl;
        for (size_t i = 0; i < x.size(); i++) {
            cout << "(" << x[i] << ", " << y[i] << ")" << endl;
        }
    }
};

int main() {
    DroneFlight d;
    d.addPoint(0, 0);
    d.addPoint(3, 4);
    d.addPoint(6, 8);
    d.printPath();
    cout << "Пройдено: " << d.getTotalDistance() << " м" << endl;

    return 0;
}
