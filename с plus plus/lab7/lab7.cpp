#include <iostream>
#include <stdexcept>

/**
 * @brief Класс, представляющий очередь.
 * 
 * Этот класс реализует очередь с поддержкой динамического размера,
 * позволяя добавлять и удалять элементы, а также предоставляя итератор.
 *
 * @tparam T Тип элементов, хранящихся в очереди.
 */
template <typename T>
class Queue {
private:
    T* data;          ///< Массив для хранения элементов.
    int capacity;     ///< Емкость очереди.
    int front;        ///< Индекс первого элемента.
    int rear;         ///< Индекс последнего элемента.
    int count;        ///< Текущее количество элементов.

    /**
     * @brief Изменяет размер очереди, увеличивая ее емкость.
     */
    void resize() {
        int newCapacity = capacity * 2; // Увеличение емкости в 2 раза.
        T* newData = new T[newCapacity];

        // Копируем элементы в новый массив.
        for (int i = 0; i < count; ++i) {
            newData[i] = data[(front + i) % capacity];
        }

        delete[] data; // Удаляем старый массив.
        data = newData; // Указываем на новый массив.
        front = 0;      // Обновляем индексы.
        rear = count - 1;
        capacity = newCapacity; // Обновляем емкость.
    }

public:
    /**
     * @brief Конструктор по умолчанию для создания очереди с заданной емкостью.
     * 
     * @param size Начальная емкость очереди.
     */
    Queue(int size = 10) : capacity(size), front(0), rear(-1), count(0) {
        data = new T[capacity]; // Создание массива.
    }

    /**
     * @brief Деструктор для освобождения памяти.
     */
    ~Queue() {
        delete[] data; // Освобождаем массив.
    }

    /**
     * @brief Добавляет элемент в конец очереди.
     * 
     * @param item Элемент для добавления.
     */
    void enqueue(const T& item) {
        if (count == capacity) {
            resize(); // Увеличиваем размер, если очередь полна.
        }
        rear = (rear + 1) % capacity; // Позиционирование в круговой очереди.
        data[rear] = item; // Добавление элемента.
        count++; // Увеличиваем счетчик.
    }

    /**
     * @brief Удаляет элемент из начала очереди.
     * 
     * @throw std::out_of_range Если очередь пуста.
     */
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty"); // Проверка на пустую очередь.
        }
        front = (front + 1) % capacity; // Позиционирование в круговой очереди.
        count--; // Уменьшаем счетчик.
    }

    /**
     * @brief Получает первый элемент из очереди, не удаляя его.
     * 
     * @return T Первый элемент в очереди.
     * @throw std::out_of_range Если очередь пуста.
     */
    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty"); // Проверка на пустую очередь.
        }
        return data[front]; // Возврат первого элемента.
    }

    /**
     * @brief Проверяет, пуста ли очередь.
     * 
     * @return true Если очередь пуста.
     * @return false Если очередь не пуста.
     */
    bool isEmpty() const {
        return count == 0; // Проверка на пустоту.
    }

    /**
     * @brief Получает текущий размер очереди.
     * 
     * @return int Текущий размер очереди.
     */
    int size() const {
        return count; // Возврат текущего количества элементов.
    }

    /**
     * @brief Дружественная функция для перегрузки оператора вывода.
     * 
     * @param os Выходной поток.
     * @param queue Очередь, которую нужно вывести.
     * @return std::ostream& Ссылка на выходной поток.
     */
    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << "Queue { ";
        for (int i = 0; i < queue.count; ++i) {
            os << queue.data[(queue.front + i) % queue.capacity]; // Вывод элементов.
            if (i < queue.count - 1) {
                os << ", "; // Разделение элементов.
            }
        }
        os << " }";
        return os; // Возврат потока.
    }

    /**
     * @brief Класс-итератор для обхода очереди.
     */
    class Iterator {
    private:
        const Queue<T>& queue; ///< Ссылка на очередь.
        int index; ///< Индекс текущего элемента.

    public:
        /**
         * @brief Конструктор итератора.
         * 
         * @param q Очередь, которую нужно обойти.
         * @param idx Индекс текущего элемента.
         */
        Iterator(const Queue<T>& q, int idx) : queue(q), index(idx) {}

        /**
         * @brief Оператор неравенства.
         * 
         * @param other Другой итератор для сравнения.
         * @return true Если итераторы не равны.
         * @return false Если итераторы равны.
         */
        bool operator!=(const Iterator& other) const {
            return index != other.index; // Сравнение индексов.
        }

        /**
         * @brief Оператор разыменования.
         * 
         * @return T Текущий элемент.
         */
        T operator*() const {
            return queue.data[(queue.front + index) % queue.capacity]; // Возврат текущего элемента.
        }

        /**
         * @brief Оператор инкремента.
         * 
         * @return const Iterator& Ссылка на текущий итератор.
         */
        const Iterator& operator++() {
            index++; // Увеличиваем индекс.
            return *this; // Возврат текущего итератора.
        }
    };

    /**
     * @brief Возвращает итератор на первый элемент очереди.
     * 
     * @return Iterator Итератор на начало очереди.
     */
    Iterator begin() const {
        return Iterator(*this, 0); // Возврат итератора на начало.
    }

    /**
     * @brief Возвращает итератор на один элемент за последний элемент очереди.
     * 
     * @return Iterator Итератор на конец очереди.
     */
    Iterator end() const {
        return Iterator(*this, count); // Возврат итератора на конец.
    }
};

int main() {
    Queue<int> queue; // Создание экземпляра очереди.
    int choice, value; // Переменные для выбора и значения.

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать пустую очередь\n";
        std::cout << "2. Добавить элемент в конец очереди\n";
        std::cout << "3. Получить элемент из начала очереди\n";
        std::cout << "4. Удалить элемент из начала очереди\n";
        std::cout << "5. Проверка, пустая ли очередь\n";
        std::cout << "6. Получить размер очереди\n";
        std::cout << "7. Вывести очередь\n";
        std::cout << "8. Обойти очередь через итератор\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice; // Ввод выбора пользователя.

        switch (choice) {
            case 1: // Создать пустую очередь
                queue = Queue<int>();  // Сбрасываем очередь
                std::cout << "Создана пустая очередь.\n";
                break;
            case 2: // Добавить элемент в конец
                std::cout << "Введите элемент для добавления: ";
                std::cin >> value;
                queue.enqueue(value);
                std::cout << "Элемент " << value << " добавлен в очередь.\n";
                break;
            case 3: // Получить элемент из начала
                try {
                    std::cout << "Первый элемент в очереди: " << queue.peek() << "\n";
                } catch (const std::out_of_range& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 4: // Удалить элемент из начала
                try {
                    std::cout << "Удалён элемент: " << queue.peek() << "\n";
                    queue.dequeue();
                } catch (const std::out_of_range& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 5: // Проверка, пустая ли очередь
                if (queue.isEmpty()) {
                    std::cout << "Очередь пуста.\n";
                } else {
                    std::cout << "Очередь не пуста.\n";
                }
                break;
            case 6: // Получить размер очереди
                std::cout << "Размер очереди: " << queue.size() << "\n";
                break;
            case 7: // Вывести очередь
                std::cout << "Содержимое очереди: " << queue << "\n";
                break;
            case 8: // Обойти очередь через итератор
                std::cout << "Элементы очереди: ";
                for (auto el : queue) { // Цикл for-each
                    std::cout << el << " ";
                }
                std::cout << "\n";
                break;
            case 0: // Выход
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
