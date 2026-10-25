// Курсовое ДЗ "ПАН": построение оптимальной программной траектории ЛА
// Вариант 5: самолет МС-21, Max P = 100%, H0=300м/V0=300км/ч -> Hk=6000м/Vk=500км/ч
// Метод: динамическое программирование на сетке (V,H)

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

// Стандартная атмосфера, ГОСТ 4401-81 (аппроксимация барометрической формулой
// для тропосферы, H <= 11000 м)
class Atmosphere {
private:
    double T0;  // температура на уровне моря, К
    double p0;  // давление на уровне моря, Па
    double g0;  // ускорение свободного падения, м/с^2
    double L;   // температурный градиент, К/м
    double R;   // газовая постоянная воздуха, Дж/(кг*К)
    double k;   // показатель адиабаты воздуха

public:
    Atmosphere() : T0(288.15), p0(101325.0), g0(9.80665), L(0.0065), R(287.05287), k(1.4) {}

    double getTemperature(double H) { return T0 - L * H; }

    double getPressure(double H) {
        double T = getTemperature(H);
        return p0 * pow(T / T0, g0 / (L * R));
    }

    double getDensity(double H) {
        return getPressure(H) / (R * getTemperature(H));
    }

    double getSoundSpeed(double H) {
        return sqrt(k * R * getTemperature(H));
    }
};

// Аэродинамика МС-21, крейсерская конфигурация (закрылки убраны).
// Cy(alpha) - линейная аппроксимация по Рис.3 методички.
// Cx(Cy) = Cx0 + A*Cy^2 - парабола поляры (Рис.4), коэффициент A подобран так,
// чтобы максимальное качество Kmax = Cy/Cx совпадало с данным в методичке
// значением Kmax = 18.1 (Рис.5).
class Aerodynamics {
private:
    double S;         // площадь крыла, м^2
    double Cy0;        // коэффициент подъемной силы при alpha = 0
    double CyAlpha;    // производная Cy по alpha, 1/град
    double CyMax;      // допустимый максимум Cy (срыв потока)
    double alphaCrit;  // критический угол атаки, град (крейсерская конфигурация)
    double Cx0;        // коэффициент сопротивления при Cy = 0
    double A;          // коэффициент индуктивного сопротивления

public:
    Aerodynamics(double S)
        : S(S), Cy0(0.47), CyAlpha(0.0735), CyMax(1.5), alphaCrit(14.0),
          Cx0(0.0275), A(0.0277) {}

    // Cy, необходимый для создания подъемной силы Y при скорости V на плотности rho
    double getCyFromLift(double Y, double rho, double V) {
        return Y / (0.5 * rho * V * V * S);
    }

    double getCx(double Cy) {
        return Cx0 + A * Cy * Cy;
    }

    double getDrag(double Cy, double rho, double V) {
        return getCx(Cy) * 0.5 * rho * V * V * S;
    }

    double getAngleOfAttack(double Cy) {
        return (Cy - Cy0) / CyAlpha;
    }

    bool isStalling(double Cy) {
        return Cy > CyMax || getAngleOfAttack(Cy) > alphaCrit;
    }
};

// Силовая установка - 2 х ПД-14.
// Тяга P(H,M) - кусочно-линейная интерполяция между опорными высотными кривыми
// H=0, H=5000 и H=10000 м (Рис.6 методички), каждая кривая линейна по M.
// Удельный расход Ср взят типовым для ПД-14 (в методичке для МС-21 не дан).
class Engine {
private:
    double Cp;           // удельный расход топлива, кг топл./(кгс*ч)
    double maxPPercent;  // процент тяги от номинала по варианту задания
    double g0;

public:
    Engine(double maxPPercent) : Cp(0.555), maxPPercent(maxPPercent), g0(9.80665) {}

    // суммарная тяга двух двигателей, кгс
    double getThrustKgf(double H, double M) {
        double P0 = 26000.0 - 20000.0 * M;   // опорная кривая H = 0
        double P5 = 13667.0 - 6667.0 * M;    // опорная кривая H = 5000 м
        double P10 = 6200.0 - 800.0 * M;     // опорная кривая H = 10000 м

        double P;
        if (H <= 5000.0) {
            P = P0 + (P5 - P0) * (H / 5000.0);
        } else {
            P = P5 + (P10 - P5) * ((H - 5000.0) / 5000.0);
        }
        return P * (maxPPercent / 100.0);
    }

    double getThrust(double H, double M) {
        return getThrustKgf(H, M) * g0;
    }

    // расход топлива, кг/с (dm/dt = -P*Cp/3600 из уравнения математической модели)
    double getFuelFlow(double H, double M) {
        return getThrustKgf(H, M) * Cp / 3600.0;
    }
};

// Результат расчета одной элементарной траектории: время и расход топлива
// на переход из одного узла сетки в соседний.
struct Segment {
    bool feasible;
    double dt;
    double dfuel;
    double sinTheta;  // синус угла наклона траектории на участке (для разгона = 0)
    double alpha;     // угол атаки в средней точке участка, град
};

const double G = 9.80665;
const double MASS = 70000.0;  // взлетная масса МС-21, кг (принята постоянной в пределах маневра)

// Расчет элементарной траектории между узлами (V1,H1) и (V2,H2).
// Параметры (rho, M, P, X) берутся в средней точке участка - по методичке
// шаг сетки выбирается так, чтобы внутри элементарной подобласти эти величины
// менялись незначительно.
// Подъемная сила принята равной весу (Y = m*g, cos(Theta) ~= 1) - упрощение,
// обычное для малых углов наклона траектории.
//
// type 0 "разгон"       (H = const, Theta = 0):      m*dV/dt = P - X
// type 1 "подъем"       (V = const, dV/dt = 0):       sin(Theta) = (P-X)/(m*g)
// type 2 "подъем-разгон" (Theta = const, dH/dV = K):   sin(Theta) = K*(P-X)/(m*(V+K*g))
Segment computeSegment(int type, double V1, double H1, double V2, double H2,
                        Atmosphere &atm, Aerodynamics &aero, Engine &engine) {
    Segment seg;
    seg.feasible = false;

    double Vm = (V1 + V2) / 2.0;
    double Hm = (H1 + H2) / 2.0;
    double rho = atm.getDensity(Hm);
    double a = atm.getSoundSpeed(Hm);
    double M = Vm / a;
    double P = engine.getThrust(Hm, M);

    double Cy = aero.getCyFromLift(MASS * G, rho, Vm);
    if (aero.isStalling(Cy)) return seg;
    double X = aero.getDrag(Cy, rho, Vm);

    if (type == 0) {
        double excess = P - X;
        if (excess <= 0) return seg;
        seg.dt = MASS * (V2 - V1) / excess;
        seg.sinTheta = 0.0;
    } else if (type == 1) {
        double excess = P - X;
        if (excess <= 0) return seg;
        double sinTheta = excess / (MASS * G);
        if (sinTheta >= 1.0) return seg;
        seg.dt = (H2 - H1) / (Vm * sinTheta);
        seg.sinTheta = sinTheta;
    } else {
        double K = (H2 - H1) / (V2 - V1);
        double sinTheta = K * (P - X) / (MASS * (Vm + K * G));
        if (sinTheta <= 0 || sinTheta >= 1.0) return seg;
        double excess = P - X - MASS * G * sinTheta;
        if (excess <= 0) return seg;
        seg.dt = MASS * (V2 - V1) / excess;
        seg.sinTheta = sinTheta;
    }

    seg.dfuel = engine.getFuelFlow(Hm, M) * seg.dt;
    seg.alpha = aero.getAngleOfAttack(Cy);
    seg.feasible = true;
    return seg;
}

// Метод динамического программирования: обратный проход от конечной точки Sk
// к начальной S0 (принцип оптимальности Беллмана), затем прямая трассировка
// найденного оптимального пути от S0 к Sk.
void solveAndPrint(bool useFuelCriterion, const vector<double> &V, const vector<double> &H,
                    vector<vector<Segment>> &segA, vector<vector<Segment>> &segB,
                    vector<vector<Segment>> &segC, const string &csvFile) {
    int n = (int)V.size() - 1;
    double INF = numeric_limits<double>::infinity();

    vector<vector<double>> J(n + 1, vector<double>(n + 1, INF));  // минимальная стоимость пути из узла до Sk
    vector<vector<int>> dir(n + 1, vector<int>(n + 1, -1));       // оптимальный тип участка из узла
    J[n][n] = 0.0;

    // обходим узлы по убыванию диагонали (i+j), чтобы к моменту расчета узла
    // (i,j) все узлы, в которые из него можно попасть, были уже обработаны
    for (int s = 2 * n - 1; s >= 0; s--) {
        int iMin = max(0, s - n);
        int iMax = min(n, s);
        for (int i = iMin; i <= iMax; i++) {
            int j = s - i;

            double best = INF;
            int bestType = -1;

            if (i < n && segA[i][j].feasible) {
                double c = (useFuelCriterion ? segA[i][j].dfuel : segA[i][j].dt) + J[i + 1][j];
                if (c < best) { best = c; bestType = 0; }
            }
            if (j < n && segB[i][j].feasible) {
                double c = (useFuelCriterion ? segB[i][j].dfuel : segB[i][j].dt) + J[i][j + 1];
                if (c < best) { best = c; bestType = 1; }
            }
            if (i < n && j < n && segC[i][j].feasible) {
                double c = (useFuelCriterion ? segC[i][j].dfuel : segC[i][j].dt) + J[i + 1][j + 1];
                if (c < best) { best = c; bestType = 2; }
            }

            J[i][j] = best;
            dir[i][j] = bestType;
        }
    }

    cout << "\n=== Критерий: " << (useFuelCriterion ? "минимум расхода топлива" : "минимум времени") << " ===\n";

    if (J[0][0] == INF) {
        cout << "Траектория не найдена (нет допустимого пути на сетке)." << endl;
        return;
    }

    cout << setw(10) << "V, км/ч" << setw(10) << "H, м" << setw(14) << "режим"
         << setw(12) << "t, с" << setw(14) << "топливо, кг" << endl;

    int i = 0, j = 0;
    double totalT = 0, totalFuel = 0, totalL = 0;
    string names[3] = {"разгон", "подъем", "подъем-разгон"};

    ofstream csv(csvFile);
    csv << "V_kmh,H_m,L_m,alpha_deg,t_s,fuel_kg\n";
    csv << V[i] * 3.6 << "," << H[j] << "," << totalL << ",0," << totalT << "," << totalFuel << "\n";

    cout << setw(10) << V[i] * 3.6 << setw(10) << H[j] << setw(14) << "старт"
         << setw(12) << totalT << setw(14) << totalFuel << endl;

    while (i < n || j < n) {
        int type = dir[i][j];
        Segment seg = (type == 0 ? segA[i][j] : (type == 1 ? segB[i][j] : segC[i][j]));

        double Vm = (V[i] + (type == 1 ? V[i] : V[i + 1])) / 2.0;
        double cosTheta = sqrt(1.0 - seg.sinTheta * seg.sinTheta);
        totalL += Vm * cosTheta * seg.dt;
        totalT += seg.dt;
        totalFuel += seg.dfuel;

        if (type == 0) i++;
        else if (type == 1) j++;
        else { i++; j++; }

        cout << setw(10) << V[i] * 3.6 << setw(10) << H[j] << setw(14) << names[type]
             << setw(12) << totalT << setw(14) << totalFuel << endl;

        csv << V[i] * 3.6 << "," << H[j] << "," << totalL << "," << seg.alpha << ","
            << totalT << "," << totalFuel << "\n";
    }

    cout << "\nИтого: время маневра t = " << totalT << " с (" << totalT / 60.0 << " мин), "
         << "расход топлива = " << totalFuel << " кг, дальность L = " << totalL / 1000.0 << " км" << endl;
}

int main() {
    // исходные данные варианта 5
    double V0 = 300.0 / 3.6;
    double Vk = 500.0 / 3.6;
    double H0 = 300.0;
    double Hk = 6000.0;
    int n = 20;  // число шагов сетки по V и по H

    vector<double> V(n + 1), H(n + 1);
    for (int i = 0; i <= n; i++) V[i] = V0 + (Vk - V0) * i / n;
    for (int j = 0; j <= n; j++) H[j] = H0 + (Hk - H0) * j / n;

    Atmosphere atm;
    Aerodynamics aero(113.0);
    Engine engine(100.0);

    // веса (стоимости) элементарных траекторий трех типов для всех узлов сетки:
    // segA - "разгон", segB - "подъем", segC - "подъем-разгон"
    vector<vector<Segment>> segA(n + 1, vector<Segment>(n + 1));
    vector<vector<Segment>> segB(n + 1, vector<Segment>(n + 1));
    vector<vector<Segment>> segC(n + 1, vector<Segment>(n + 1));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i < n) segA[i][j] = computeSegment(0, V[i], H[j], V[i + 1], H[j], atm, aero, engine);
            if (j < n) segB[i][j] = computeSegment(1, V[i], H[j], V[i], H[j + 1], atm, aero, engine);
            if (i < n && j < n) segC[i][j] = computeSegment(2, V[i], H[j], V[i + 1], H[j + 1], atm, aero, engine);
        }
    }

    solveAndPrint(true, V, H, segA, segB, segC, "trajectory_fuel.csv");
    solveAndPrint(false, V, H, segA, segB, segC, "trajectory_time.csv");

    return 0;
}
