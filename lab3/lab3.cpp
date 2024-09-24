#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct String {
    int length;          // Длина строки
    char* characters;    // Указатель на массив символов

    // Конструктор для инициализации структуры
    String() : length(0), characters(nullptr) {}

    /* 
     * Метод для создания строки заданной длины.
     * Генерирует случайную строку из английских букв (заглавные и маленькие).
     * @param len - длина создаваемой строки.
     */
    void generateString(int len) {
        length = len;
        characters = new char[length + 1]; // +1 для символа конца строки

        // Генерация случайной строки
        for (int i = 0; i < length; ++i) {
            int randChoice = rand() % 52; // 26 букв в верхнем регистре + 26 в нижнем
            if (randChoice < 26) {
                characters[i] = 'A' + randChoice; // Заглавные буквы
            } else {
                characters[i] = 'a' + (randChoice - 26); // Маленькие буквы
            }
        }
        characters[length] = '\0'; // Завершающий символ
    }

    // Деструктор для освобождения памяти
    ~String() {
        delete[] characters;
    }
};

/* 
 * Подсчитывает количество повторений определенного символа в массиве строк.
 * @param strings - массив строк.
 * @param N - количество строк в массиве.
 * @param c - символ для подсчета.
 * @return Количество повторений символа.
 */
int countCharacterOccurrences(String* strings, int N, char c) {
    int count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < strings[i].length; ++j) {
            if (strings[i].characters[j] == c) {
                count++;
            }
        }
    }
    return count;
}

/* 
 * Ищет максимально длинную повторяющуюся последовательность символов в массиве строк.
 * @param strings - массив строк.
 * @param N - количество строк в массиве.
 * @return Максимально длинная повторяющаяся последовательность.
 */
std::string findLongestRepeatingSequence(String* strings, int N) {
    std::string longest;

    for (int i = 0; i < N; ++i) {
        std::string current;
        int maxCount = 0;
        int currentCount = 1;

        for (int j = 1; j < strings[i].length; ++j) {
            if (strings[i].characters[j] == strings[i].characters[j - 1]) {
                currentCount++;
            } else {
                currentCount = 1;
            }

            if (currentCount > maxCount) {
                maxCount = currentCount;
                current = std::string(1, strings[i].characters[j - 1]);
            }
        }

        if (current.length() > longest.length()) {
            longest = current;
        }
    }

    return longest;
}

/* 
 * Складывает все строки массива в одну итоговую строку.
 * @param strings - массив строк.
 * @param N - количество строк в массиве.
 * @return Итоговая строка.
 */
String concatenateStrings(String* strings, int N) {
    String result;
    result.length = 0;

    for (int i = 0; i < N; ++i) {
        result.length += strings[i].length;
    }

    result.characters = new char[result.length + 1]; // +1 для завершающего символа
    int index = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < strings[i].length; ++j) {
            result.characters[index++] = strings[i].characters[j];
        }
    }

    result.characters[result.length] = '\0'; // Завершающий символ
    return result;
}

/* 
 * Подсчитывает количество вхождений подстроки в массиве строк.
 * @param strings - массив строк.
 * @param N - количество строк в массиве.
 * @param substring - подстрока для подсчета вхождений.
 * @return Количество вхождений подстроки.
 */
int countSubstringOccurrences(String* strings, int N, const std::string& substring) {
    int count = 0;

    for (int i = 0; i < N; ++i) {
        std::string currentString(strings[i].characters);
        size_t pos = currentString.find(substring);

        while (pos != std::string::npos) {
            count++;
            pos = currentString.find(substring, pos + 1);
        }
    }

    return count;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    int N;
    std::cout << "Введите число N: ";
    std::cin >> N;

    // Массив строк типа "Строка"
    String* customStrings = new String[N];

    // Массив строк типа "std::string"
    std::string* stdStrings = new std::string[N];

    // Генерация строк и заполнение массивов
    for (int i = 0; i < N; ++i) {
        customStrings[i].generateString(50);
        stdStrings[i] = std::string(customStrings[i].characters); // Копирование в std::string

        // Вывод строк
        std::cout << "Строка " << (i + 1) << " (структура): " << customStrings[i].characters << std::endl;
        std::cout << "Строка " << (i + 1) << " (std::string): " << stdStrings[i] << std::endl;
    }

    // Меню для выбора действий
    int choice;
    do {
        std::cout << "\nВыберите действие:\n";
        std::cout << "1. Подсчитать количество повторений определенного символа\n";
        std::cout << "2. Найти максимальную повторяющуюся последовательность символов\n";
        std::cout << "3. Объединить все строки в одну\n";
        std::cout << "4. Подсчитать вхождения подстроки\n";
        std::cout << "5. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char c;
                std::cout << "Введите символ: ";
                std::cin >> c;
                int occurrences = countCharacterOccurrences(customStrings, N, c);
                std::cout << "Количество повторений символа '" << c << "': " << occurrences << std::endl;
                break;
            }
            case 2: {
                std::string longest = findLongestRepeatingSequence(customStrings, N);
                std::cout << "Максимально длинная повторяющаяся последовательность: " << longest << std::endl;
                break;
            }
            case 3: {
                String result = concatenateStrings(customStrings, N);
                std::cout << "Объединенная строка: " << result.characters << std::endl;
                delete[] result.characters; // Освобождение памяти
                break;
            }
            case 4: {
                std::string substring;
                std::cout << "Введите подстроку: ";
                std::cin >> substring;
                int count = countSubstringOccurrences(customStrings, N, substring);
                std::cout << "Количество вхождений подстроки '" << substring << "': " << count << std::endl;
                break;
            }
            case 5:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
        }
    } while (choice != 5);

    // Освобождение выделенной памяти
    delete[] customStrings;
    delete[] stdStrings;

    return 0;
}
