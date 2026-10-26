import matplotlib.pyplot as plt
import matplotlib.patches as patches

fig, ax = plt.subplots(figsize=(6, 9))
ax.set_xlim(0, 10)
ax.set_ylim(0, 24)
ax.axis("off")

BOX_COLOR = "#eef1f6"
EDGE_COLOR = "#2f5f8a"
TEXT_COLOR = "#16202b"

steps = [
    "Ввод исходных данных:\nвариант, ТТХ МС-21, атмосфера\nГОСТ 4401-81, аэродинамика, тяга ПД-14",
    "Построение сетки (V,H):\nV0..Vk, H0..Hk, n шагов",
    "Расчет весовых функций Δt, ΔGт\nдля 3 типов элементарных траекторий\nво всех узлах сетки",
    "Обратный проход от Sk к S0:\nJ(i,j) = min[ΔJ + J(сосед)]\n(принцип оптимальности Беллмана)",
    "Прямая трассировка\nоптимального пути от S0 к Sk",
    "Вывод: траектория H(V), графики\nα(L), H(L), Gт(L), итоговые t и Gт",
]

y_positions = [22, 18.4, 14.8, 11.2, 7.6, 4]

for (text, y) in zip(steps, y_positions):
    box = patches.FancyBboxPatch((1, y - 1.5), 8, 3,
                                  boxstyle="round,pad=0.15",
                                  linewidth=1.5, edgecolor=EDGE_COLOR, facecolor=BOX_COLOR)
    ax.add_patch(box)
    ax.text(5, y, text, ha="center", va="center", fontsize=10.5, color=TEXT_COLOR)

for i in range(len(y_positions) - 1):
    y1 = y_positions[i] - 1.5
    y2 = y_positions[i + 1] + 1.5
    ax.annotate("", xy=(5, y2), xytext=(5, y1),
                arrowprops=dict(arrowstyle="-|>", color=EDGE_COLOR, linewidth=1.5))

fig.tight_layout()
fig.savefig("plot_blockscheme.png", dpi=150)
print("Блок-схема сохранена.")
