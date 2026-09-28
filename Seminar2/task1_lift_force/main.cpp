#include <iostream>
using namespace std;

int main() {
    double S, V, rho, C_L;

    cout << "Площадь крыла S (м^2): ";
    cin >> S;
    cout << "Скорость полета V (м/с): ";
    cin >> V;
    cout << "Плотность воздуха rho (кг/м^3): ";
    cin >> rho;
    cout << "Коэффициент подъемной силы C_L: ";
    cin >> C_L;

    double L = 0.5 * rho * V * V * S * C_L;

    cout << "Подъемная сила L = " << L << " Н" << endl;

    return 0;
}
