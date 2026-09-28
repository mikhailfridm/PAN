#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a_y, h;

    cout << "Вертикальное ускорение a_y (м/с^2): ";
    cin >> a_y;
    cout << "Заданная высота h (м): ";
    cin >> h;

    if (a_y <= 0) {
        cout << "Ошибка: ускорение должно быть положительным, набор высоты невозможен." << endl;
        return 1;
    }
    if (h <= 0) {
        cout << "Ошибка: высота должна быть положительной." << endl;
        return 1;
    }

    double t = sqrt(2 * h / a_y);

    cout << "Время набора высоты t = " << t << " с" << endl;

    return 0;
}
