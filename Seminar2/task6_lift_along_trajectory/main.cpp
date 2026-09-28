#include <iostream>
using namespace std;

int main() {
    const int N = 5;
    double V[N], rho[N];
    double S, C_L;

    cout << "Площадь крыла S (м^2): ";
    cin >> S;
    cout << "Коэффициент подъемной силы C_L: ";
    cin >> C_L;

    for (int i = 0; i < N; i++) {
        cout << "Шаг " << i << " - скорость V (м/с): ";
        cin >> V[i];
        cout << "Шаг " << i << " - плотность воздуха rho (кг/м^3): ";
        cin >> rho[i];
    }

    cout << "\nШаг\tСкорость\tПлотность\tПодъемная сила" << endl;

    for (int i = 0; i < N; i++) {
        double L = 0.5 * rho[i] * V[i] * V[i] * S * C_L;
        cout << i << "\t" << V[i] << "\t\t" << rho[i] << "\t\t" << L << endl;
    }

    return 0;
}
