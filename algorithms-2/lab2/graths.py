import matplotlib.pyplot as plt
import numpy as np
import re

def read_results(file_name):
    data = {}
    pattern = re.compile(r"Размерность:\s*(\d+)\s+Время:\s*([\d.]+)\s+Количество вызовов рекурсии:\s*(\d+)\s+Глубина рекурсии:\s*(\d+)\s+Количество операций слияния:\s*(\d+)\s+Доп. память:\s*(\d+)")

    with open(file_name, 'r', encoding='utf-8') as file:
        for line in file:
            match = pattern.search(line)
            if match:
                dimension = int(match.group(1))
                time = float(match.group(2))
                recursion_calls = int(match.group(3))
                depth = int(match.group(4))
                merge_operations = int(match.group(5))
                memory_usage = int(match.group(6))

                if dimension not in data:
                    data[dimension] = {
                        "time": [],
                        "recursion_calls": [],
                        "depth": [],
                        "merge_operations": [],
                        "memory_usage": []
                    }
                data[dimension]["time"].append(time)
                data[dimension]["recursion_calls"].append(recursion_calls)
                data[dimension]["depth"].append(depth)
                data[dimension]["merge_operations"].append(merge_operations)
                data[dimension]["memory_usage"].append(memory_usage)

            else:
                print(f"Ошибка обработки строки: {line.strip()}")

    return data

def build_graphs(data):
    dimensions = sorted(data.keys())

    x = np.array(dimensions)
    y_on = x * np.log(x)

    C = max(max(data[dim]["time"]) for dim in dimensions) / max(y_on)
    y_on_scaled = C * y_on

    worst_times = [max(data[dim]["time"]) for dim in dimensions]

    plt.figure(figsize=(10, 6))
    plt.plot(dimensions, worst_times, label='Наихудшее время', marker='o')
    plt.plot(dimensions, y_on_scaled, label='O(N log N)', linestyle='--')
    plt.xlabel('Число элементов в массиве')
    plt.ylabel('Время выполнения (сек)')
    plt.title('Сравнение O(N log N) и наихудшего времени')
    plt.legend()
    plt.grid()
    plt.savefig("time_vs_on.png")
    plt.show()

    avg_times = [np.mean(data[dim]["time"]) for dim in dimensions]
    best_times = [min(data[dim]["time"]) for dim in dimensions]
    worst_times = [max(data[dim]["time"]) for dim in dimensions]

    plt.figure(figsize=(10, 6))
    plt.plot(dimensions, avg_times, label='Среднее время', marker='o')
    plt.plot(dimensions, best_times, label='Наилучшее время', marker='o')
    plt.plot(dimensions, worst_times, label='Наихудшее время', marker='o')
    plt.xlabel('Число элементов в массиве')
    plt.ylabel('Время выполнения (сек)')
    plt.title('Среднее, наилучшее и наихудшее время выполнения')
    plt.legend()
    plt.grid()
    plt.savefig("time_comparison.png")
    plt.show()

    avg_depth = [np.mean(data[dim]["depth"]) for dim in dimensions]
    best_depth = [min(data[dim]["depth"]) for dim in dimensions]
    worst_depth = [max(data[dim]["depth"]) for dim in dimensions]

    plt.figure(figsize=(10, 6))
    plt.plot(dimensions, avg_depth, label='Средняя глубина рекурсии', marker='o')
    plt.plot(dimensions, best_depth, label='Наилучшая глубина рекурсии', marker='o')
    plt.plot(dimensions, worst_depth, label='Наихудшая глубина рекурсии', marker='o')
    plt.xlabel('Число элементов в массиве')
    plt.ylabel('Глубина рекурсии')
    plt.title('Средняя, наилучшая и наихудшая глубина рекурсии')
    plt.legend()
    plt.grid()
    plt.savefig("recursion_depth_comparison.png")
    plt.show()

    dimensions = sorted(data.keys())

    best_memory = [min(data[dim]["memory_usage"]) for dim in dimensions]
    worst_memory = [max(data[dim]["memory_usage"]) for dim in dimensions]

    plt.figure(figsize=(10, 6))
    plt.plot(dimensions, best_memory, label='Наилучшее потребление памяти', marker='o', color='green')
    plt.plot(dimensions, worst_memory, label='Наихудшее потребление памяти', marker='o', color='red')
    plt.xlabel('Число элементов в массиве')
    plt.ylabel('Дополнительная память (байт)')
    plt.title('Наилучшее и наихудшее потребление дополнительной памяти')
    plt.legend()
    plt.grid()
    plt.savefig("memory_usage_comparison.png")
    plt.show()

    avg_calls = [np.mean(data[dim]["recursion_calls"]) for dim in dimensions]
    best_calls = [min(data[dim]["recursion_calls"]) for dim in dimensions]
    worst_calls = [max(data[dim]["recursion_calls"]) for dim in dimensions]

    plt.figure(figsize=(10, 6))
    plt.plot(dimensions, avg_calls, label='Среднее число вызовов', marker='o')
    plt.plot(dimensions, best_calls, label='Наилучшее число вызовов', marker='o')
    plt.plot(dimensions, worst_calls, label='Наихудшее число вызовов', marker='o')
    plt.xlabel('Число элементов в массиве')
    plt.ylabel('Количество вызовов рекурсии')
    plt.title('Среднее, наилучшее и наихудшее количество вызовов рекурсии')
    plt.legend()
    plt.grid()
    plt.savefig("recursion_calls_comparison.png")
    plt.show()

if __name__ == "__main__":
    results_file = "results.txt"
    data = read_results(results_file)
    build_graphs(data)
