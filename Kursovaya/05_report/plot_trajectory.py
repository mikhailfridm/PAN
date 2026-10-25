import csv
import matplotlib.pyplot as plt

def load(path):
    rows = []
    with open(path) as f:
        reader = csv.DictReader(f)
        for r in reader:
            rows.append({k: float(v) for k, v in r.items()})
    return rows

data = load("trajectory_fuel.csv")

V = [r["V_kmh"] for r in data]
H = [r["H_m"] for r in data]
L = [r["L_m"] / 1000.0 for r in data]
alpha = [r["alpha_deg"] for r in data]
fuel = [r["fuel_kg"] for r in data]

LINE_COLOR = "#2f5f8a"
MARK_COLOR = "#c9622a"

plt.rcParams.update({
    "font.size": 11,
    "axes.edgecolor": "#888888",
    "axes.grid": True,
    "grid.color": "#dddddd",
    "grid.linewidth": 0.6,
})

fig, ax = plt.subplots(figsize=(7, 5))
ax.plot(V, H, color=LINE_COLOR, linewidth=2)
ax.scatter(V, H, color=MARK_COLOR, s=14, zorder=3)
ax.set_xlabel("Скорость V, км/ч")
ax.set_ylabel("Высота H, м")
ax.set_title("Оптимальная программная траектория МС-21 (вариант 5)")
fig.tight_layout()
fig.savefig("plot_trajectory_HV.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(7, 4))
ax.plot(L, alpha, color=LINE_COLOR, linewidth=2)
ax.scatter(L, alpha, color=MARK_COLOR, s=14, zorder=3)
ax.set_xlabel("Дальность L, км")
ax.set_ylabel("Угол атаки α, град")
ax.set_title("Изменение угла атаки по дальности")
fig.tight_layout()
fig.savefig("plot_alpha_L.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(7, 4))
ax.plot(L, H, color=LINE_COLOR, linewidth=2)
ax.scatter(L, H, color=MARK_COLOR, s=14, zorder=3)
ax.set_xlabel("Дальность L, км")
ax.set_ylabel("Высота H, м")
ax.set_title("Высота полета по дальности")
fig.tight_layout()
fig.savefig("plot_H_L.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(7, 4))
ax.plot(L, fuel, color=LINE_COLOR, linewidth=2)
ax.scatter(L, fuel, color=MARK_COLOR, s=14, zorder=3)
ax.set_xlabel("Дальность L, км")
ax.set_ylabel("Расход топлива, кг")
ax.set_title("Расход топлива по дальности")
fig.tight_layout()
fig.savefig("plot_fuel_L.png", dpi=150)
plt.close(fig)

print("Готово: 4 графика сохранены.")
