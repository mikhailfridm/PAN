#include <iostream>
using namespace std;

struct Aircraft {
    double mass;
    double S;
    double thrust;
    double C_D;
    double C_L;
};

int main() {
    int N;
    cout << "Количество самолетов N: ";
    cin >> N;

    double V, rho;
    cout << "Скорость полета V (м/с): ";
    cin >> V;
    cout << "Плотность воздуха rho (кг/м^3): ";
    cin >> rho;

    Aircraft *planes = new Aircraft[N];

    for (int i = 0; i < N; i++) {
        cout << "\nСамолет " << (i + 1) << endl;
        cout << "  Масса (кг): ";
        cin >> planes[i].mass;
        cout << "  Площадь крыла S (м^2): ";
        cin >> planes[i].S;
        cout << "  Тяга (Н): ";
        cin >> planes[i].thrust;
        cout << "  Коэффициент сопротивления C_D: ";
        cin >> planes[i].C_D;
        cout << "  Коэффициент подъемной силы C_L: ";
        cin >> planes[i].C_L;
    }

    cout << "\nРезультаты:\n";
    int leaderIndex = -1;
    double maxAccel = -1e18;

    for (int i = 0; i < N; i++) {
        double L = 0.5 * rho * V * V * planes[i].S * planes[i].C_L;
        double D = 0.5 * rho * V * V * planes[i].S * planes[i].C_D;
        double a = (planes[i].thrust - D) / planes[i].mass;

        cout << "Самолет " << (i + 1) << ": L=" << L << " Н, D=" << D
             << " Н, a=" << a << " м/с^2" << endl;

        if (a > maxAccel) {
            maxAccel = a;
            leaderIndex = i;
        }
    }

    cout << "\nНаибольшее ускорение у самолета " << (leaderIndex + 1)
         << " (a = " << maxAccel << " м/с^2)" << endl;

    delete[] planes;

    return 0;
}
