#include <iostream>
using namespace std;

double calcDrag(double rho, double V, double S, double C_D) {
    return 0.5 * rho * V * V * S * C_D;
}

int main() {
    double rho, V, S, C_D;

    cout << "Плотность воздуха rho (кг/м^3): ";
    cin >> rho;
    cout << "Скорость полета V (м/с): ";
    cin >> V;
    cout << "Площадь крыла S (м^2): ";
    cin >> S;
    cout << "Коэффициент сопротивления C_D: ";
    cin >> C_D;

    double D = calcDrag(rho, V, S, C_D);

    cout << "Аэродинамическое сопротивление D = " << D << " Н" << endl;

    return 0;
}
