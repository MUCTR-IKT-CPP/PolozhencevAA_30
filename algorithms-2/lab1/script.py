import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Читаем данные из CSV
df = pd.read_csv("sorting_results.csv")

# Группируем данные по размеру массива
grouped = df.groupby("ArraySize")

# Вычисляем статистику
sizes = sorted(df["ArraySize"].unique())
worst_times = grouped["Time"].max()
best_times = grouped["Time"].min()
avg_times = grouped["Time"].mean()
avg_swaps = grouped["Swaps"].mean()
avg_passes = grouped["Passes"].mean()

# Вычисление O(N²) с подбором константы c
N_squared = np.array(sizes) ** 2
c = max(worst_times / N_squared) * 1.1  # Выбираем c так, чтобы график O(N²) был выше
o_n2 = c * N_squared

# График наихудшего случая vs O(N²)
plt.figure(figsize=(10, 6))
plt.plot(sizes, worst_times, label="Наихудшее время", marker="o")
plt.plot(sizes, o_n2, label="O(N²)", linestyle="--")
plt.xlabel("Размер массива")
plt.ylabel("Время (сек)")
plt.legend()
plt.title("Сравнение наихудшего времени выполнения с O(N²)")
plt.grid()
plt.show()

# График лучшего, среднего и худшего случая
plt.figure(figsize=(10, 6))
plt.plot(sizes, best_times, label="Наилучшее время", marker="o")
plt.plot(sizes, avg_times, label="Среднее время", marker="o")
plt.plot(sizes, worst_times, label="Наихудшее время", marker="o")
plt.xlabel("Размер массива")
plt.ylabel("Время (сек)")
plt.legend()
plt.title("Сравнение времени выполнения (лучший, средний, худший случаи)")
plt.grid()
plt.show()

# График среднего количества обменов
plt.figure(figsize=(10, 6))
plt.plot(sizes, avg_swaps, label="Среднее количество обменов", marker="o", color="red")
plt.xlabel("Размер массива")
plt.ylabel("Количество обменов")
plt.legend()
plt.title("Среднее количество обменов значений")
plt.grid()
plt.show()

# График количества проходов по массиву
plt.figure(figsize=(10, 6))
plt.plot(sizes, avg_passes, label="Среднее количество проходов", marker="o", color="green")
plt.xlabel("Размер массива")
plt.ylabel("Количество проходов")
plt.legend()
plt.title("Среднее количество проходов по массиву")
plt.grid()
plt.show()
