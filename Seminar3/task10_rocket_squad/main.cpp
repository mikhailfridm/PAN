#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x, y, z;
};

class Rocket {
private:
    double mass;
    double vx, vy, vz;
    double x, y, z;

public:
    Rocket(double mass, double vx, double vy, double vz)
        : mass(mass), vx(vx), vy(vy), vz(vz), x(0.0), y(0.0), z(0.0) {}

    void updatePosition(double dt) {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
    }

    void changeVelocity(double newVx, double newVy, double newVz) {
        vx = newVx;
        vy = newVy;
        vz = newVz;
    }

    Point getPosition() const {
        return {x, y, z};
    }
};

int main() {
    double dt = 1.0, T = 10.0;

    vector<Rocket> squad;
    squad.reserve(5);
    squad.emplace_back(1000, 10, 0, 50);
    squad.emplace_back(900, 15, -5, 40);
    squad.emplace_back(1100, 5, 10, 45);
    squad.emplace_back(950, -10, 0, 55);
    squad.emplace_back(1050, 0, 20, 35);

    vector<vector<Point>> trajectories(squad.size());

    for (double t = 0.0; t <= T; t += dt) {
        for (size_t i = 0; i < squad.size(); i++) {
            squad[i].updatePosition(dt);
            trajectories[i].push_back(squad[i].getPosition());
        }
    }

    cout << "Конечные положения ракет после " << T << " с полета:" << endl;
    for (size_t i = 0; i < squad.size(); i++) {
        Point p = squad[i].getPosition();
        cout << "Ракета " << i + 1 << ": x=" << p.x << " y=" << p.y << " z=" << p.z << endl;
    }

    return 0;
}
