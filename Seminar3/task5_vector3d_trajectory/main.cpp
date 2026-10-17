#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Point {
    double x, y, z;
};

int main() {
    double vx = 30.0, vy = 20.0, vz = 40.0;
    double dt = 1.0, t_max = 5.0;

    vector<Point> traj;
    double x = 0.0, y = 0.0, z = 0.0;

    for (double t = dt; t <= t_max; t += dt) {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        traj.push_back({x, y, z});
    }

    cout << setw(8) << "t" << setw(10) << "x" << setw(10) << "y" << setw(10) << "z" << endl;
    for (size_t i = 0; i < traj.size(); i++) {
        double t = (i + 1) * dt;
        cout << setw(8) << t << setw(10) << traj[i].x << setw(10) << traj[i].y << setw(10) << traj[i].z << endl;
    }

    return 0;
}
