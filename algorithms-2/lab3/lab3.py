import random
import time
from collections import deque
from typing import List

# python lab3.py

# Этот код представляет собой реализацию двух типов очередей: 
# через односвязный список (LinkedQueue) и через два стека (TwoStackQueue). 
# Далее, в нем выполняются различные тесты для этих очередей.

# Очередь через односвязный список
class LinkedQueue:
    # Вложенный класс для представления узла очереди
    class Node:
        def __init__(self, value):
            self.data = value 
            self.next = None # Указатель 

    # Инициализация пустой очереди
    def __init__(self):
        self.head = None 
        self.rear = None
        self.size = 0 # Размер очереди

     # Метод добавления элемента в очередь
    def push(self, value):
        new_node = self.Node(value) # Создаем новый узел с переданным значением
        if self.rear:
            self.rear.next = new_node
        else:
             # Если очередь пуста, новый узел будет и началом, и концом
            self.head = new_node
        self.rear = new_node # Новый узел становится концом очереди
        self.size += 1

    # Метод извлечения элемента из очереди
    def dequeue(self):
        # Если очередь пуста, выбрасываем исключение
        if self.empty():
            raise IndexError("Queue is empty")
        # Временная переменная для удаления первого элемента
        temp = self.head
        # Смещаем начало очереди на следующий элемент
        self.head = self.head.next
        if not self.head:
            self.rear = None
        # Удаляем временный элемент
        del temp
        self.size -= 1

    # Метод для получения первого элемента без удаления
    def peek(self):
        # Если очередь пуста, выбрасываем исключение
        if self.empty():
            raise IndexError("Queue is empty")
        return self.head.data

    # Метод проверки пустоты очереди
    def empty(self):
        return self.size == 0

    # Метод для получения размера очереди
    def count(self):
        return self.size

    # Превращает ваш односвязный список в итератор
    def __iter__(self):
        current = self.head
        while current:
            yield current.data
            current = current.next

# Класс для представления человека
class Person:
    def __init__(self, last_name, first_name, middle_name, birth_year):
        self.last_name = last_name
        self.first_name = first_name
        self.middle_name = middle_name
        self.birth_year = birth_year


# Тест 1: статистика для очереди из 1000 чисел
def test1():
    queue = LinkedQueue()  # Создаем пустую очередь
    random.seed(time.time())  # Инициализируем генератор случайных чисел
    sum_val = 0
    min_val = float('inf')
    max_val = float('-inf')
    
    for _ in range(1000):
        value = random.randint(-1000, 1000) # Генерируем случайное число
        queue.push(value) # Добавляем его в очередь
        sum_val += value # Считаем сумму всех чисел
        min_val = min(min_val, value) # Определяем минимум
        max_val = max(max_val, value)  # Определяем максимум
    
    average = sum_val / queue.count() # Вычисляем среднее значение
    print("Queue statistics:")
    print(f"Sum: {sum_val}")
    print(f"Average: {average}")
    print(f"Min: {min_val}")
    print(f"Max: {max_val}")

# Тест 2: проверка операций вставки и изъятия на 10 строковых элементах
def test2():
    queue = LinkedQueue() # Создаем очередь
    words = ["orange", "blueberry", "strawberry", "peach", "plum", "apricot", "pear", "mango", "watermelon", "pineapple"]
    
    print("Enqueuing elements:")
    for word in words:
        queue.push(word) # Добавляем слова в очередь
        print(word, end=" ")

    print("\nDequeuing elements:")
    while not queue.empty(): # Пока очередь не пуста
        print(queue.peek(), end=" ") # Выводим первый элемент
        queue.dequeue() # Удаляем его
    print("\nTest2 completed.")

# Тест 3: работа с очередью из 100 структур Person
def test3():
    queue = LinkedQueue() # Создаем очередь
    names = ["Daniel", "Sophia", "Liam", "Olivia", "Ethan"]  
    last_names = ["Miller", "Davis", "Wilson", "Moore", "Thomas"]
    random.seed(time.time())
    
    for _ in range(100):
        person = Person(random.choice(last_names), random.choice(names), "", random.randint(1980, 2020))
        queue.push(person) # Добавляем случайных людей

    filtered_queue = LinkedQueue()
    count_excluded = 0
    while not queue.empty():
        person = queue.peek()
        queue.dequeue()
        if person.birth_year < 1994 or person.birth_year > 2004:
            filtered_queue.push(person)  # Оставляем только тех, кто НЕ родился с 1994 по 2004
        else:
            count_excluded += 1 # Считаем исключенных

    print(f"Test3: Excluded count: {count_excluded}")

    reversed_queue = LinkedQueue()
    while not filtered_queue.empty():
        person = filtered_queue.peek()
        filtered_queue.dequeue()
        reversed_queue.push(person)  # Разворачиваем очередь

    print("Test3 completed.")


# Шаблонная очередь через два стека
class TwoStackQueue:
    def __init__(self):
        self.input_stack = []
        self.output_stack = []
        self.size = 0

    # Добавляет элемент в очередь
    def push(self, value):
        self.input_stack.append(value)
        self.size += 1

    # Удаляет первый элемент из очереди
    def dequeue(self):
        if self.empty():
            raise IndexError("Queue is empty")
        if not self.output_stack:
            self.transfer_to_output()
        self.output_stack.pop()
        self.size -= 1

    # Возвращает первый элемент в очереди без удаления
    def peek(self):
        if self.empty():
            raise IndexError("Queue is empty")
        if not self.output_stack:
            self.transfer_to_output()
        return self.output_stack[-1]

    # Проверяет, пуста ли очередь
    def empty(self):
        return self.size == 0

    # Возвращает количество элементов в очереди
    def count(self):
        return self.size

    # Переносит элементы из input_stack в output_stack, меняя их порядок
    def transfer_to_output(self):
        while self.input_stack:
            self.output_stack.append(self.input_stack.pop())


# Тест 1 для TwoStackQueue
def test1_two_stack():
    queue = TwoStackQueue()
    random.seed(time.time())
    sum_val = 0
    min_val = float('inf')
    max_val = float('-inf')
    
    for _ in range(1000):
        value = random.randint(-1000, 1000)
        queue.push(value)
        sum_val += value
        min_val = min(min_val, value)
        max_val = max(max_val, value)
    
    average = sum_val / queue.count()
    print("TwoStackQueue statistics:")
    print(f"Sum: {sum_val}")
    print(f"Average: {average}")
    print(f"Min: {min_val}")
    print(f"Max: {max_val}")

# Тест 2 для TwoStackQueue
def test2_two_stack():
    queue = TwoStackQueue()
    words = ["orange", "pear", "mango", "plum", "peach", "apricot", "blueberry", "strawberry", "watermelon", "pineapple"]
    
    print("Enqueuing elements (TwoStackQueue):")
    for word in words:
        queue.push(word)
        print(word, end=" ")

    print("\nDequeuing elements (TwoStackQueue):")
    while not queue.empty():
        print(queue.peek(), end=" ")
        queue.dequeue()
    print("\nTest2_TwoStack completed.")

# Тест 3 для TwoStackQueue
def test3_two_stack():
    queue = TwoStackQueue()
    names = ["Daniel", "Sophia", "Liam", "Olivia", "Ethan"]  
    last_names = ["Miller", "Davis", "Wilson", "Moore", "Thomas"]
    random.seed(time.time())
    
    for _ in range(100):
        person = Person(random.choice(last_names), random.choice(names), "", random.randint(1980, 2020))
        queue.push(person)

    filtered_queue = TwoStackQueue()
    count_excluded = 0
    while not queue.empty():
        person = queue.peek()
        queue.dequeue()
        if person.birth_year < 1994 or person.birth_year > 2004:
            filtered_queue.push(person)
        else:
            count_excluded += 1

    print(f"Test3_TwoStack: Excluded count: {count_excluded}")

    reversed_queue = TwoStackQueue()
    while not filtered_queue.empty():
        person = filtered_queue.peek()
        filtered_queue.dequeue()
        reversed_queue.push(person)

    print("Test3_TwoStack completed.")


# Тест скорости для LinkedQueue
def test_linked_queue_speed(elements):
    queue = LinkedQueue() # Создаём экземпляр очереди на связном списке
    
    # Засекаем время выполнения операции добавления элементов
    start = time.time()
    for i in range(elements):
        queue.push(i)   # Добавляем элементы в очередь
    push_time = (time.time() - start) * 1_000_000   # Конвертируем в микросекунды

    # Засекаем время выполнения операции удаления элементов
    start = time.time()
    while not queue.empty():
        queue.dequeue()  # Удаляем элементы из очереди
    dequeue_time = (time.time() - start) * 1_000_000 # Конвертируем в микросекунды

    print(f"push time: {push_time} microseconds")
    print(f"Dequeue time: {dequeue_time} microseconds")

def test_two_stack_queue_speed(elements):
    queue = TwoStackQueue() # Создаём экземпляр очереди, реализованной через два стека
    
    # Засекаем время выполнения операции добавления элементов
    start = time.time()
    for i in range(elements):
        queue.push(i)   # Добавляем элементы в очередь
    push_time = (time.time() - start) * 1_000_000   # Конвертируем в микросекунды

    # Засекаем время выполнения операции удаления элементов
    start = time.time()
    while not queue.empty():
        queue.dequeue() # Удаляем элементы из очереди
    dequeue_time = (time.time() - start) * 1_000_000    # Конвертируем в микросекунды

    print(f"push time for TwoStackQueue: {push_time} microseconds")
    print(f"Dequeue time for TwoStackQueue: {dequeue_time} microseconds")


def main():
    print("Testing LinkedQueue:")
    test1()
    test2()
    test3()

    print("\nTesting TwoStackQueue:")
    test1_two_stack()
    test2_two_stack()
    test3_two_stack()

    ELEMENTS = 10000

    print(f"Performance comparison for {ELEMENTS} elements:")
    test_linked_queue_speed(ELEMENTS)
    test_two_stack_queue_speed(ELEMENTS)

if __name__ == "__main__":
    main()
