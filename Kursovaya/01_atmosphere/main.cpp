#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Atmosphere {
private:
    double T0;
    double p0;
    double g0;
    double L;
    double R;
    double k;

public:
    Atmosphere()
        : T0(288.15), p0(101325.0), g0(9.80665), L(0.0065), R(287.05287), k(1.4) {}

    double getTemperature(double H) {
        return T0 - L * H;
    }

    double getPressure(double H) {
        double T = getTemperature(H);
        return p0 * pow(T / T0, g0 / (L * R));
    }

    double getDensity(double H) {
        double p = getPressure(H);
        double T = getTemperature(H);
        return p / (R * T);
    }

    double getSoundSpeed(double H) {
        double T = getTemperature(H);
        return sqrt(k * R * T);
    }
};

int main() {
    Atmosphere atm;

    cout << setw(8) << "H, м" << setw(12) << "T, K" << setw(14) << "p, Па"
         << setw(14) << "rho, кг/м3" << setw(12) << "a, м/с" << endl;

    for (double H = 0; H <= 6000; H += 500) {
        cout << setw(8) << H
             << setw(12) << atm.getTemperature(H)
             << setw(14) << atm.getPressure(H)
             << setw(14) << atm.getDensity(H)
             << setw(12) << atm.getSoundSpeed(H)
             << endl;
    }

    return 0;
}
