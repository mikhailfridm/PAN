#include <iostream>
using namespace std;

class RocketStage {
private:
    double thrust;
    double burnTime;
    double mass;

public:
    RocketStage(double thrust, double burnTime, double mass)
        : thrust(thrust), burnTime(burnTime), mass(mass) {}

    double getDeltaV() {
        return thrust * burnTime / mass;
    }

    void printInfo() {
        cout << "Ступень: тяга=" << thrust << " Н, время работы=" << burnTime
             << " с, масса=" << mass << " кг, dV=" << getDeltaV() << " м/с" << endl;
    }
};

int main() {
    RocketStage s1(5000, 10, 1000);
    RocketStage s2(7000, 8, 900);
    RocketStage s3(9000, 6, 800);

    s1.printInfo();
    s2.printInfo();
    s3.printInfo();

    double totalV = s1.getDeltaV() + s2.getDeltaV() + s3.getDeltaV();
    cout << "Итоговая скорость ракеты: " << totalV << " м/с" << endl;

    return 0;
}
