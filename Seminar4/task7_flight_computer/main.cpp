#include <iostream>
using namespace std;

class FlightComputer {
private:
    double altitude;
    double velocity;
    double fuel;
    double thrust;
    double time;

public:
    FlightComputer(double altitude, double velocity, double fuel, double thrust)
        : altitude(altitude), velocity(velocity), fuel(fuel), thrust(thrust), time(0.0) {}

    void simulateStep(double dt) {
        velocity += (thrust / 1000.0 - 9.8) * dt;
        altitude += velocity * dt;
        fuel -= dt * 2;
        time += dt;
    }

    void printStatus() {
        cout << "t=" << time << "c: высота=" << altitude << "м, скорость="
             << velocity << "м/с, топливо=" << fuel << endl;
    }
};

int main() {
    FlightComputer fc(0, 0, 100, 12000);
    for (int i = 0; i < 5; i++) {
        fc.simulateStep(0.5);
        fc.printStatus();
    }

    return 0;
}
