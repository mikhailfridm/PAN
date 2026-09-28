#include <iostream>
#include <cmath>
using namespace std;

struct Aircraft {
    int id;
    double mass;
    double thrust;
    double C_L;
    double C_D;
    double climbTime;
    bool canClimb;
};

int main() {
    const double g = 9.81;
    int n;

    cout << "Количество самолетов: ";
    cin >> n;

    double V, rho, S, h;
    cout << "Скорость полета V (м/с): ";
    cin >> V;
    cout << "Плотность воздуха rho (кг/м^3): ";
    cin >> rho;
    cout << "Площадь крыла S (м^2, одинаковая для всех): ";
    cin >> S;
    cout << "Целевая высота h (м): ";
    cin >> h;

    Aircraft *planes = new Aircraft[n];

    for (int i = 0; i < n; i++) {
        planes[i].id = i + 1;
        cout << "\nСамолет " << planes[i].id << endl;
        cout << "  Масса (кг): ";
        cin >> planes[i].mass;
        cout << "  Тяга (Н): ";
        cin >> planes[i].thrust;
        cout << "  Коэффициент подъемной силы C_L: ";
        cin >> planes[i].C_L;
        cout << "  Коэффициент сопротивления C_D: ";
        cin >> planes[i].C_D;

        double L = 0.5 * rho * V * V * S * planes[i].C_L;
        double a_y = (L - planes[i].mass * g) / planes[i].mass;

        if (a_y > 0) {
            planes[i].climbTime = sqrt(2 * h / a_y);
            planes[i].canClimb = true;
        } else {
            planes[i].canClimb = false;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            bool needSwap = false;

            if (!planes[j].canClimb && planes[j + 1].canClimb) {
                needSwap = true;
            } else if (planes[j].canClimb && planes[j + 1].canClimb && planes[j].climbTime > planes[j + 1].climbTime) {
                needSwap = true;
            }

            if (needSwap) {
                Aircraft temp = planes[j];
                planes[j] = planes[j + 1];
                planes[j + 1] = temp;
            }
        }
    }

    cout << "\nРезультаты (по возрастанию времени набора высоты):\n";
    for (int i = 0; i < n; i++) {
        cout << "Самолет " << planes[i].id << ": ";
        if (planes[i].canClimb) {
            cout << "t = " << planes[i].climbTime << " с" << endl;
        } else {
            cout << "не может набрать высоту" << endl;
        }
    }

    delete[] planes;

    return 0;
}
