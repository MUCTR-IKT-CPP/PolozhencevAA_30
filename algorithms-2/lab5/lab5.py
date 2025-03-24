import random
import time
import matplotlib.pyplot as plt

# для запуска python lab5.py
# Вариант 4. Построить минимальное остовное дерево взвешенного связного неориентированного графа с помощью алгоритма Краскала.

# ---------- Класс графа ----------
class Graph:
    def __init__(self, num_nodes: int):
        """Инициализация графа с заданным количеством узлов."""
        self.num_nodes = num_nodes  # Количество вершин в графе
        self.edges = []  # Список рёбер в формате (узел_1, узел_2, вес)
        self.adjacency_matrix = [[0] * num_nodes for _ in range(num_nodes)]  # Матрица смежности

    def add_edge(self, node1: int, node2: int, weight: int):
        """Добавление ребра в граф (в обе стороны, так как граф неориентированный)."""
        self.edges.append((node1, node2, weight))
        self.edges.append((node2, node1, weight))  # Дублируем для неориентированного графа
        self.adjacency_matrix[node1][node2] = weight
        self.adjacency_matrix[node2][node1] = weight

    def generate_random_graph(self, min_edges_per_node: int, weight_range: tuple = (1, 20)):
        """Генерация случайного связного графа с минимумом рёбер на вершину."""
        for i in range(self.num_nodes - 1):
            weight = random.randint(*weight_range)
            self.add_edge(i, i + 1, weight)

        for node in range(self.num_nodes):
            num_edges = random.randint(min_edges_per_node, self.num_nodes - 1)
            connected_nodes = set(v for u, v, _ in self.edges if u == node)  # Уже связанные узлы

            while len(connected_nodes) < num_edges:
                random_node = random.randint(0, self.num_nodes - 1)
                if node != random_node and random_node not in connected_nodes:
                    weight = random.randint(*weight_range)
                    self.add_edge(node, random_node, weight)
                    connected_nodes.add(random_node)

    def print_adjacency_matrix(self):
        """Вывод матрицы смежности в консоль."""
        for row in self.adjacency_matrix:
            print(" ".join(f"{weight:2}" for weight in row))


# Функция для поиска минимального остовного дерева (MST) с помощью алгоритма Краскала
def kruskal_algorithm(graph: Graph):
    """Алгоритм Краскала для поиска минимального остовного дерева."""
    sorted_edges = sorted(graph.edges, key=lambda edge: edge[2])  # Сортируем рёбра по весу
    parent = list(range(graph.num_nodes))  # Родительские узлы для объединения
    rank = [0] * graph.num_nodes  # Ранги для балансировки объединения
    mst_result = []  # Список рёбер остовного дерева

    def find_root(node):
        """Функция поиска сжатия пути."""
        if parent[node] != node:
            parent[node] = find_root(parent[node])
        return parent[node]

    def union_sets(node1, node2):
        """Объединяет два множества."""
        root1 = find_root(node1)
        root2 = find_root(node2)

        if root1 != root2:
            if rank[root1] > rank[root2]:
                parent[root2] = root1
            elif rank[root1] < rank[root2]:
                parent[root1] = root2
            else:
                parent[root2] = root1
                rank[root1] += 1

    # Обрабатываем рёбра и добавляем в MST, если они не образуют цикл
    for node1, node2, weight in sorted_edges:
        if find_root(node1) != find_root(node2):
            mst_result.append((node1, node2, weight))
            union_sets(node1, node2)

    return mst_result


# Функция для тестирования алгоритма и записи результатов в файл
def test_kruskal():
    """Функция для тестирования алгоритма Краскала и записи результатов."""
    node_sizes = [10, 20, 50, 100]  # Различные размеры графов
    min_edges_list = [3, 4, 10, 20]  # Минимальное количество рёбер на вершину
    test_iterations = 5  # Количество запусков для усреднения времени
    test_results = []  # Хранение результатов

    output_file = "output.txt"  # Имя файла для сохранения результатов
    with open(output_file, "w", encoding="utf-8") as file:
        for num_nodes, min_edges in zip(node_sizes, min_edges_list):
            execution_times = []  # Список для хранения времени выполнения

            for _ in range(test_iterations):
                # Генерируем случайный граф
                test_graph = Graph(num_nodes)
                test_graph.generate_random_graph(min_edges)

                # Записываем матрицу смежности в файл
                file.write(f"\nГраф с {num_nodes} вершинами:\n")
                for row in test_graph.adjacency_matrix:
                    file.write(" ".join(f"{weight:2}" for weight in row) + "\n")

                # Запускаем алгоритм Краскала и замеряем время
                start_time = time.time()
                mst = kruskal_algorithm(test_graph)
                elapsed_time = time.time() - start_time
                execution_times.append(elapsed_time)

                # Записываем MST и время выполнения в файл
                file.write(f"\nМинимальное остовное дерево (MST): {mst}\n")
                file.write(f"Время выполнения: {elapsed_time:.5f} сек\n")

            # Усредняем время выполнения
            avg_time = sum(execution_times) / len(execution_times)
            test_results.append((num_nodes, avg_time))

        # Записываем итоговые средние результаты в файл
        file.write("\nСреднее время выполнения:\n")
        for nodes, avg in test_results:
            file.write(f"{nodes} вершин: {avg:.5f} сек\n")

    # Построение графика времени выполнения
    plt.figure(figsize=(10, 6))
    plt.plot([r[0] for r in test_results], [r[1] for r in test_results], label="Алгоритм Краскала", marker="o")
    plt.xlabel("Количество вершин (N)")
    plt.ylabel("Время выполнения (секунды)")
    plt.title("Производительность алгоритма Краскала")
    plt.legend()
    plt.grid()
    plt.show()


# Запуск тестов
test_kruskal()