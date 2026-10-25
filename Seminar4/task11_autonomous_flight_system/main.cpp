#include <iostream>
#include <iomanip>
using namespace std;

class Engine {
private:
    double thrust;
    double fuelFlow;
    double fuel;

public:
    Engine(double thrust, double fuelFlow, double fuel)
        : thrust(thrust), fuelFlow(fuelFlow), fuel(fuel) {}

    double getThrust() const {
        return thrust;
    }

    bool hasFuel() const {
        return fuel > 0;
    }

    void burn(double dt) {
        if (hasFuel()) {
            fuel -= fuelFlow * dt;
            if (fuel < 0) fuel = 0;
        }
    }

    double getFuel() const {
        return fuel;
    }
};

class Navigation {
private:
    double altitude;
    double velocity;
    double acceleration;
    double mass;

public:
    Navigation(double altitude, double velocity, double mass)
        : altitude(altitude), velocity(velocity), acceleration(0.0), mass(mass) {}

    void update(double thrust, double dt) {
        acceleration = thrust / mass - 9.81;
        velocity += acceleration * dt;
        altitude += velocity * dt;
    }

    void printStatus(double time) const {
        cout << fixed << setprecision(2);
        cout << "t=" << time << "c | h=" << altitude << "м | v=" << velocity
             << "м/с | a=" << acceleration << "м/с^2" << endl;
    }
};

class AutonomousFlightSystem {
private:
    Engine engine;
    Navigation nav;
    double time;

public:
    AutonomousFlightSystem(Engine engine, Navigation nav)
        : engine(engine), nav(nav), time(0.0) {}

    void simulate(double dt, double totalTime) {
        while (time < totalTime && engine.hasFuel()) {
            engine.burn(dt);
            nav.update(engine.getThrust(), dt);
            nav.printStatus(time);
            time += dt;
        }
    }

    void printSummary() {
        cout << "--- Полет завершен ---" << endl;
        cout << "Оставшееся топливо: " << engine.getFuel() << " кг" << endl;
    }
};

int main() {
    Engine engine(20000, 50, 1000);
    Navigation nav(0, 0, 1000);
    AutonomousFlightSystem system(engine, nav);

    system.simulate(1.0, 5.0);
    system.printSummary();

    return 0;
}
