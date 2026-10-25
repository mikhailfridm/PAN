#include <iostream>
#include <iomanip>
using namespace std;

class Engine {
private:
    double Cp;
    double maxPPercent;
    double g0;

public:
    Engine(double maxPPercent)
        : Cp(0.555), maxPPercent(maxPPercent), g0(9.80665) {}

    double getThrustKgf(double H, double M) {
        double P0 = 26000.0 - 20000.0 * M;
        double P5 = 13667.0 - 6667.0 * M;
        double P10 = 6200.0 - 800.0 * M;

        double P;
        if (H <= 5000.0) {
            P = P0 + (P5 - P0) * (H / 5000.0);
        } else {
            P = P5 + (P10 - P5) * ((H - 5000.0) / 5000.0);
        }

        return P * (maxPPercent / 100.0);
    }

    double getThrust(double H, double M) {
        return getThrustKgf(H, M) * g0;
    }

    double getFuelFlow(double H, double M) {
        double thrustKgf = getThrustKgf(H, M);
        return thrustKgf * Cp / 3600.0;
    }
};

int main() {
    Engine engine(100.0);

    cout << setw(8) << "H, м" << setw(8) << "M" << setw(14) << "P, кгс"
         << setw(14) << "P, Н" << setw(16) << "расход, кг/с" << endl;

    double Hs[] = {300, 2000, 4000, 6000};
    double Ms[] = {0.25, 0.3, 0.35, 0.4};

    for (double H : Hs) {
        for (double M : Ms) {
            cout << setw(8) << H << setw(8) << M
                 << setw(14) << engine.getThrustKgf(H, M)
                 << setw(14) << engine.getThrust(H, M)
                 << setw(16) << engine.getFuelFlow(H, M) << endl;
        }
    }

    return 0;
}
