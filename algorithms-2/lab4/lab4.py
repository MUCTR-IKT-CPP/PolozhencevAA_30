import random 
import time  
import matplotlib.pyplot as plt  
from collections import deque  # Импортируем deque для очереди в BFS

# Класс для представления графа
class Graph:
    def __init__(self, vertices, directed=False):
        # Инициализация графа с заданным количеством вершин и направленностью
        self.vertices = vertices  # Количество вершин
        self.directed = directed  # Направленность графа
        self.adjacency_matrix = [[0] * vertices for _ in range(vertices)]  # Матрица смежности (по умолчанию все рёбра отсутствуют)

    def add_edge(self, u, v):
        # Добавление ребра между вершинами u и v
        if u != v:  # Избегаем самопетель
            self.adjacency_matrix[u][v] = 1  # Устанавливаем ребро от u к v
            if not self.directed:  # Если граф неориентированный, добавляем обратное ребро
                self.adjacency_matrix[v][u] = 1

    def get_adjacency_matrix(self):
        # Возвращаем матрицу смежности
        return self.adjacency_matrix

    def get_incidence_matrix(self):
        # Генерация матрицы инцидентности
        edges = sum(row.count(1) for row in self.adjacency_matrix)  # Подсчёт количества рёбер
        matrix = [[0] * edges for _ in range(self.vertices)]  # Инициализация матрицы инцидентности
        edge_index = 0  # Индекс для рёбер

        # Заполнение матрицы инцидентности
        for i in range(self.vertices):
            for j in range(self.vertices):
                if self.adjacency_matrix[i][j]:
                    matrix[i][edge_index] = 1  # Вершина i инцидентен ребру
                    matrix[j][edge_index] = -1 if self.directed else 1  # Вершина j инцидентен ребру
                    edge_index += 1

        return matrix

    def get_adjacency_list(self):
        # Возвращаем список смежности
        return [[j for j in range(self.vertices) if self.adjacency_matrix[i][j]] for i in range(self.vertices)]

    def get_edge_list(self):
        # Возвращаем список рёбер
        return [(i, j) for i in range(self.vertices) for j in range(self.vertices) if self.adjacency_matrix[i][j]]

    def bfs(self, start, end):
        # Реализация поиска в ширину (BFS)
        queue = deque([start])  # Очередь для BFS
        visited = [False] * self.vertices  # Массив посещённых вершин
        visited[start] = True  # Отмечаем начальную вершину как посещённую
        parent = [-1] * self.vertices  # Массив для восстановления пути

        while queue:
            node = queue.popleft()  # Извлекаем вершину из очереди
            if node == end:  # Если достигли конечной вершины
                path = []  # Список для пути
                while node != -1:
                    path.append(node)
                    node = parent[node]  # Восстанавливаем путь
                return list(reversed(path))  # Возвращаем путь в правильном порядке

            # Обход всех соседей текущей вершины
            for neighbor in range(self.vertices):
                if self.adjacency_matrix[node][neighbor] and not visited[neighbor]:
                    queue.append(neighbor)
                    visited[neighbor] = True
                    parent[neighbor] = node

        return []  # Если путь не найден

    def dfs(self, start, end):
        # Реализация поиска в глубину (DFS)
        stack = [start]  # Стек для DFS
        visited = [False] * self.vertices  # Массив посещённых вершин
        visited[start] = True  # Отмечаем начальную вершину как посещённую
        parent = [-1] * self.vertices  # Массив для восстановления пути

        while stack:
            node = stack.pop()  # Извлекаем вершину из стека
            if node == end:  # Если достигли конечной вершины
                path = []  # Список для пути
                while node != -1:
                    path.append(node)
                    node = parent[node]  # Восстанавливаем путь
                return list(reversed(path))  # Возвращаем путь в правильном порядке

            # Обход всех соседей текущей вершины
            for neighbor in range(self.vertices):
                if self.adjacency_matrix[node][neighbor] and not visited[neighbor]:
                    stack.append(neighbor)
                    visited[neighbor] = True
                    parent[neighbor] = node

        return []  # Если путь не найден


# Класс для генерации случайных графов
class GraphGenerator:
    def __init__(self, min_vertices, max_vertices, min_edges, max_edges, max_degree, max_inout_degree, directed):
        self.min_vertices = min_vertices  # Минимальное количество вершин
        self.max_vertices = max_vertices  # Максимальное количество вершин
        self.min_edges = min_edges  # Минимальное количество рёбер
        self.max_edges = max_edges  # Максимальное количество рёбер
        self.max_degree = max_degree  # Максимальная степень вершины
        self.max_inout_degree = max_inout_degree  # Максимальная входная/выходная степень
        self.directed = directed  # Направленность графа

    def generate_graph(self, vertices, edges):
        # Генерация графа с заданным количеством вершин и рёбер
        graph = Graph(vertices, self.directed)  # Создаём граф
        edge_count = 0  # Счётчик рёбер

        # Пока не добавим все рёбра
        while edge_count < edges:
            u, v = random.randint(0, vertices - 1), random.randint(0, vertices - 1)  # Генерация случайных рёбер
            if u != v and graph.adjacency_matrix[u][v] == 0:  # Если рёбер между u и v ещё нет
                # Проверяем, не превышают ли степени вершин максимально допустимые
                out_degree = sum(graph.adjacency_matrix[u])  # Степень вершины u
                in_degree = sum(row[v] for row in graph.adjacency_matrix)  # Степень вершины v

                if out_degree < self.max_degree and in_degree < self.max_inout_degree:
                    graph.add_edge(u, v)  # Добавляем ребро в граф
                    edge_count += 1  # Увеличиваем счётчик рёбер

        return graph  # Возвращаем сгенерированный граф


# Основная часть программы
if __name__ == "__main__":
    # Задание начальных параметров
    initial_vertices = 5
    initial_edges = 8
    step_vertices = 5
    step_edges = 10
    max_degree = 4
    max_inout_degree = 4
    is_directed = False  # Направленность графа

    # Инициализация генератора графов
    generator = GraphGenerator(initial_vertices, initial_vertices + step_vertices * 9, initial_edges,
                               initial_edges + step_edges * 9, max_degree, max_inout_degree, is_directed)

    # Списки для хранения данных для построения графика
    bfs_times = []
    dfs_times = []
    vertex_counts = []

    # Генерация графов с увеличением количества вершин и рёбер
    for i in range(10):
        vertices = initial_vertices + i * step_vertices  # Количество вершин
        edges = initial_edges + i * step_edges  # Количество рёбер

        graph = generator.generate_graph(vertices, edges)  # Генерация графа

        print(f"\n=== Граф {i + 1} ===")
        print(f"Вершины: {vertices}, Рёбра: {edges}")

        # Вывод матрицы смежности
        print("\nМатрица смежности:")
        for row in graph.get_adjacency_matrix():
            print(" ".join(map(str, row)))

        # Вывод списка смежности
        print("\nСписок смежности:")
        for idx, neighbors in enumerate(graph.get_adjacency_list()):
            print(f"{idx} -> {', '.join(map(str, neighbors))}")

        # Выбираем случайные вершины для поиска пути
        start, end = random.randint(0, vertices - 1), random.randint(0, vertices - 1)
        print(f"\nПоиск пути между {start} и {end}...")

        # Замер времени выполнения BFS
        start_time = time.time()
        bfs_path = graph.bfs(start, end)
        bfs_time = time.time() - start_time

        # Замер времени выполнения DFS
        start_time = time.time()
        dfs_path = graph.dfs(start, end)
        dfs_time = time.time() - start_time

        # Вывод результатов поиска пути
        if bfs_path:
            print("BFS путь:", " → ".join(map(str, bfs_path)))
        else:
            print("BFS не нашёл путь")

        if dfs_path:
            print("DFS путь:", " → ".join(map(str, dfs_path)))
        else:
            print("DFS не нашёл путь")

        # Вывод времени выполнения алгоритмов
        print(f"BFS занял {bfs_time:.6f} сек, DFS занял {dfs_time:.6f} сек.")
        print("=" * 30)

        bfs_times.append(bfs_time)
        dfs_times.append(dfs_time)
        vertex_counts.append(vertices)

    plt.plot(vertex_counts, bfs_times, marker='o', label="BFS")
    plt.plot(vertex_counts, dfs_times, marker='s', label="DFS")
    plt.xlabel("Количество вершин")
    plt.ylabel("Время выполнения (сек.)")
    plt.legend()
    plt.title("Сравнение скорости работы BFS и DFS")
    plt.grid()
    plt.show()
