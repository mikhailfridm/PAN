#include <iostream>
using namespace std;

class NavigationSystem {
private:
    double x, y;
    double velocityX, velocityY;
    bool gpsAvailable;

public:
    NavigationSystem(double x, double y, double velocityX, double velocityY, bool gpsAvailable)
        : x(x), y(y), velocityX(velocityX), velocityY(velocityY), gpsAvailable(gpsAvailable) {}

    void integratePosition(double dt) {
        x += velocityX * dt;
        y += velocityY * dt;
    }

    void correctGPS(double realX, double realY) {
        if (gpsAvailable) {
            x = (x + realX) / 2.0;
            y = (y + realY) / 2.0;
        }
    }

    void printPosition() {
        cout << "Скорректированные координаты: (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    NavigationSystem nav(0, 0, 100, 50, true);
    nav.integratePosition(1);
    nav.correctGPS(110, 60);
    nav.printPosition();

    return 0;
}
