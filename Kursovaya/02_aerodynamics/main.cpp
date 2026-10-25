#include <iostream>
#include <iomanip>
using namespace std;

class Aerodynamics {
private:
    double S;
    double Cy0;
    double CyAlpha;
    double CyMax;
    double alphaCrit;
    double Cx0;
    double A;

public:
    Aerodynamics(double S)
        : S(S), Cy0(0.47), CyAlpha(0.0735), CyMax(1.5), alphaCrit(14.0),
          Cx0(0.0275), A(0.0277) {}

    double getCyFromLift(double Y, double rho, double V) {
        return Y / (0.5 * rho * V * V * S);
    }

    double getCx(double Cy) {
        return Cx0 + A * Cy * Cy;
    }

    double getLift(double Cy, double rho, double V) {
        return Cy * 0.5 * rho * V * V * S;
    }

    double getDrag(double Cy, double rho, double V) {
        return getCx(Cy) * 0.5 * rho * V * V * S;
    }

    double getAngleOfAttack(double Cy) {
        return (Cy - Cy0) / CyAlpha;
    }

    bool isStalling(double Cy) {
        return Cy > CyMax || getAngleOfAttack(Cy) > alphaCrit;
    }
};

int main() {
    Aerodynamics aero(113.0);

    cout << setw(8) << "Cy" << setw(10) << "Cx" << setw(10) << "alpha" << setw(12) << "K=Cy/Cx" << endl;

    for (double Cy = 0.1; Cy <= 1.4; Cy += 0.1) {
        double Cx = aero.getCx(Cy);
        double alpha = aero.getAngleOfAttack(Cy);
        cout << setw(8) << Cy << setw(10) << Cx << setw(10) << alpha << setw(12) << Cy / Cx << endl;
    }

    double rho = 0.736116;
    double V = 139.0;
    double Y = 70000.0 * 9.81;

    double Cy = aero.getCyFromLift(Y, rho, V);
    double drag = aero.getDrag(Cy, rho, V);

    cout << "\nПри H=5000м, V=139м/с, Y=mg:" << endl;
    cout << "Cy=" << Cy << ", X=" << drag << " Н, срыв: " << (aero.isStalling(Cy) ? "да" : "нет") << endl;

    return 0;
}
