#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double m, D, h;
    double Tmin, Tmax, dT;

    cout << "Масса самолета m (кг): ";
    cin >> m;
    cout << "Сопротивление D (Н): ";
    cin >> D;
    cout << "Целевая высота h (м): ";
    cin >> h;
    cout << "Минимальная тяга Tmin (Н): ";
    cin >> Tmin;
    cout << "Максимальная тяга Tmax (Н): ";
    cin >> Tmax;
    cout << "Шаг тяги dT (Н): ";
    cin >> dT;

    double bestT = -1;
    double bestTime = -1;
    bool found = false;

    cout << "\n" << "Тяга (Н)" << "\t" << "Ускорение (м/с^2)" << "\t" << "Время набора (с)" << endl;

    for (double T = Tmin; T <= Tmax; T += dT) {
        double a = (T - D) / m;

        if (a > 0) {
            double t = sqrt(2 * h / a);
            cout << T << "\t\t" << a << "\t\t\t" << t << endl;

            if (!found || t < bestTime) {
                bestTime = t;
                bestT = T;
                found = true;
            }
        } else {
            cout << T << "\t\t" << a << "\t\t\t" << "набор высоты невозможен" << endl;
        }
    }

    if (found) {
        cout << "\nОптимальная тяга T = " << bestT << " Н, минимальное время набора высоты t = " << bestTime << " с" << endl;
    } else {
        cout << "\nНи при одном значении тяги набор высоты невозможен." << endl;
    }

    return 0;
}
