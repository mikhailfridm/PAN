#include <iostream>
using namespace std;

int main() {
    double T, L, D, m;

    cout << "Тяга двигателя T (Н): ";
    cin >> T;
    cout << "Подъемная сила L (Н): ";
    cin >> L;
    cout << "Сопротивление D (Н): ";
    cin >> D;
    cout << "Масса самолета m (кг): ";
    cin >> m;

    double a = (T - D) / m;

    cout << "Ускорение a = " << a << " м/с^2" << endl;

    if (a > 0.5) {
        cout << "Режим полета: набор высоты" << endl;
    } else if (a >= 0 && a <= 0.5) {
        cout << "Режим полета: горизонтальный полет" << endl;
    } else {
        cout << "Режим полета: снижение" << endl;
    }

    return 0;
}
