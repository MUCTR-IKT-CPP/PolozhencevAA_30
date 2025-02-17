#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/*
 * Шаблонный класс отсортированного вектора
 * Наследуется от std::vector и предоставляет методы для сортировки,
 * вставки и работы с элементами, сохраняя порядок.
 */
template <typename T>
class SortedVector : public std::vector<T> {
public:
    /*
     * Конструктор по умолчанию
     * Инициализирует пустой вектор
     */
    SortedVector() : std::vector<T>() {}

    /*
     * Конструктор с инициализацией через std::initializer_list
     *
     * @param init список инициализации, содержащий элементы вектора.
     * Выполняет сортировку элементов по возрастанию.
     */
    SortedVector(std::initializer_list<T> init) : std::vector<T>(init) {
        sortAscending();
    }

    /*
     * Метод для сортировки элементов вектора по возрастанию
     */
    void sortAscending() {
        std::sort(this->begin(), this->end());
    }

    /*
     * Метод для сортировки элементов вектора по убыванию
     */
    void sortDescending() {
        std::sort(this->begin(), this->end(), std::greater<T>());
    }

    /*
     * Метод для подсчета количества элементов, делящихся нацело на заданное число
     *
     * @param divisor делитель.
     * @return количество элементов, которые делятся нацело на divisor.
     */
    int countDivisibleBy(int divisor) const {
        return std::count_if(this->begin(), this->end(),
                             [divisor](const T& elem) { return elem % divisor == 0; });
    }

    /*
     * Перегруженный метод insert для вставки элемента, сохраняя порядок
     * Выполняет сортировку вектора, если он не отсортирован
     *
     * @param value значение, которое нужно вставить в вектор.
     */
    void insert(const T& value) {
        if (!std::is_sorted(this->begin(), this->end())) {
            std::cout << "Вектор не отсортирован. Сортировка по возрастанию...\n";
            sortAscending();
        }
        auto pos = std::lower_bound(this->begin(), this->end(), value);
        std::vector<T>::insert(pos, value);
    }

    /*
     * Перегруженный метод insert для вставки элемента в определенную позицию
     *
     * @param position позиция вектора, перед которой будет вставлен элемент.
     * @param value значение для вставки.
     */
    void insert(size_t position, const T& value) {
        if (position <= this->size()) {
            std::vector<T>::insert(this->begin() + position, value);
        } else {
            std::cerr << "Неверная позиция" << std::endl;
        }
    }

    /*
     * Метод для вывода всех уникальных перестановок элементов вектора
     * Использует std::next_permutation для генерации перестановок
     */
    void printPermutations() {
        sortAscending();
        std::cout << "Перестановки элементов вектора:\n";
        do {
            std::copy(this->begin(), this->end(), std::ostream_iterator<T>(std::cout, " "));
            std::cout << "\n";
        } while (std::next_permutation(this->begin(), this->end()));
    }

    /*
     * Дружественная функция для перегрузки оператора вывода в поток
     *
     * @param os поток вывода.
     * @param vec объект SortedVector для вывода.
     * @return поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const SortedVector<T>& vec) {
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
        return os;
    }
};

/*
 * Главная функция программы, предоставляющая меню для работы с SortedVector
 */
int main() {
    SortedVector<int> vec = {1, 2, 3};
    bool running = true;

    while (running) {
        std::cout << "\nТекущий вектор: " << vec << "\n";
        std::cout << "Выберите действие:\n";
        std::cout << "1. Подсчитать количество элементов, делящихся на заданное число\n";
        std::cout << "2. Отсортировать по возрастанию\n";
        std::cout << "3. Отсортировать по убыванию\n";
        std::cout << "4. Вставить новый элемент в определенную позицию\n";
        std::cout << "5. Вставить элемент в первую допустимую позицию, сохраняя порядок\n";
        std::cout << "6. Вывести все уникальные перестановки\n";
        std::cout << "7. Выход\n";
        std::cout << "Введите ваш выбор: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int divisor;
                std::cout << "Введите число: ";
                std::cin >> divisor;
                int count = vec.countDivisibleBy(divisor);
                std::cout << "Количество элементов, делящихся на " << divisor << ": " << count << "\n";
                break;
            }
            case 2:
                vec.sortAscending();
                std::cout << "Отсортировано по возрастанию.\n";
                break;
            case 3:
                vec.sortDescending();
                std::cout << "Отсортировано по убыванию.\n";
                break;
            case 4: {
                int position, value;
                std::cout << "Введите позицию для вставки (начиная с 0): ";
                std::cin >> position;
                std::cout << "Введите значение для вставки: ";
                std::cin >> value;
                vec.insert(position, value);
                std::cout << "Вставлено значение " << value << " на позицию " << position << ".\n";
                break;
            }
            case 5: {
                int value;
                std::cout << "Введите значение для вставки: ";
                std::cin >> value;
                vec.insert(value);
                std::cout << "Вставлено значение " << value << " с сохранением порядка.\n";
                break;
            }
            case 6:
                vec.printPermutations();
                break;
            case 7:
                running = false;
                break;
            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
