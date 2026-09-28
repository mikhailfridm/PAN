#include <iostream>
using namespace std;

int main() {
    const double g = 9.81;
    double m, L, D, T;

    cout << "Масса самолета m (кг): ";
    cin >> m;
    cout << "Подъемная сила L (Н): ";
    cin >> L;
    cout << "Сопротивление D (Н): ";
    cin >> D;
    cout << "Тяга двигателя T (Н): ";
    cin >> T;

    double a = (T - D) / m;
    double a_y = (L - m * g) / m;

    cout << "Ускорение по направлению движения a = " << a << " м/с^2" << endl;
    cout << "Вертикальное ускорение a_y = " << a_y << " м/с^2" << endl;

    return 0;
}
