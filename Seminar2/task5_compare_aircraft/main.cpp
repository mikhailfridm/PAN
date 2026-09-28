#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double g = 9.81;
    const int N = 3;

    double m[N], S[N], T[N], C_L[N], C_D[N];
    double V, rho, h;

    cout << "Скорость полета V (м/с): ";
    cin >> V;
    cout << "Плотность воздуха rho (кг/м^3): ";
    cin >> rho;
    cout << "Целевая высота h (м): ";
    cin >> h;

    for (int i = 0; i < N; i++) {
        cout << "\nСамолет " << i + 1 << endl;
        cout << "  Масса m (кг): ";
        cin >> m[i];
        cout << "  Площадь крыла S (м^2): ";
        cin >> S[i];
        cout << "  Тяга T (Н): ";
        cin >> T[i];
        cout << "  Коэффициент подъемной силы C_L: ";
        cin >> C_L[i];
        cout << "  Коэффициент сопротивления C_D: ";
        cin >> C_D[i];
    }

    double time[N];
    bool canClimb[N];

    cout << "\nРезультаты:\n";
    for (int i = 0; i < N; i++) {
        double L = 0.5 * rho * V * V * S[i] * C_L[i];
        double D = 0.5 * rho * V * V * S[i] * C_D[i];
        double a_y = (L - m[i] * g) / m[i];

        cout << "Самолет " << i + 1 << ": L=" << L << " Н, D=" << D << " Н, a_y=" << a_y << " м/с^2";

        if (a_y > 0) {
            time[i] = sqrt(2 * h / a_y);
            canClimb[i] = true;
            cout << ", время набора высоты t=" << time[i] << " с" << endl;
        } else {
            canClimb[i] = false;
            cout << ", набор высоты невозможен (недостаточно подъемной силы)" << endl;
        }
    }

    int bestIndex = -1;
    for (int i = 0; i < N; i++) {
        if (canClimb[i]) {
            if (bestIndex == -1 || time[i] < time[bestIndex]) {
                bestIndex = i;
            }
        }
    }

    if (bestIndex != -1) {
        cout << "\nБыстрее всех набирает высоту: самолет " << bestIndex + 1
             << " (t=" << time[bestIndex] << " с)" << endl;
    } else {
        cout << "\nНи один самолет не может набрать высоту при заданных параметрах." << endl;
    }

    return 0;
}
