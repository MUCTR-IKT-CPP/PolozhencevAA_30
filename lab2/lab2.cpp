#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

/*
 * Заполняет двумерный массив случайными числами в диапазоне от 0 до 10 (включительно).
 *
 * @param matrix - указатель на двумерный массив.
 * @param size - размер массива (N).
 */
void fillMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 11;  // Генерация случайного числа от 0 до 10
        }
    }
}

/*
 * Выводит двумерный массив на экран.
 *
 * @param matrix - указатель на двумерный массив.
 * @param size - размер массива (N).
 */
void printMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << std::fixed << std::setprecision(2) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*
 * Сложение двух матриц A и B, результат записывается в C.
 *
 * @param matrixA - первая матрица.
 * @param matrixB - вторая матрица.
 * @param resultMatrix - матрица для хранения результата.
 * @param size - размер матриц (N).
 */
void addMatrices(double** matrixA, double** matrixB, double** resultMatrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

/*
 * Умножение двух матриц A и B, результат записывается в C.
 *
 * @param matrixA - первая матрица.
 * @param matrixB - вторая матрица.
 * @param resultMatrix - матрица для хранения результата.
 * @param size - размер матриц (N).
 */
void multiplyMatrices(double** matrixA, double** matrixB, double** resultMatrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

/*
 * Транспонирование матрицы A, результат записывается в B.
 *
 * @param matrixA - матрица для транспонирования.
 * @param transposedMatrix - матрица для хранения результата.
 * @param size - размер матриц (N).
 */
void transposeMatrix(double** matrixA, double** transposedMatrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            transposedMatrix[j][i] = matrixA[i][j];
        }
    }
}

/*
 * Вычисление определителя матрицы A.
 *
 * @param matrixA - матрица для которой вычисляется определитель.
 * @param size - размер матрицы.
 * @return Определитель матрицы.
 */
double calculateDeterminant(double** matrixA, int size) {
    if (size == 1) {
        return matrixA[0][0];
    }
    if (size == 2) {
        return matrixA[0][0] * matrixA[1][1] - matrixA[0][1] * matrixA[1][0];
    }

    double determinant = 0.0;
    for (int p = 0; p < size; ++p) {
        double** tempMatrix = new double*[size - 1];
        for (int i = 0; i < size - 1; ++i) {
            tempMatrix[i] = new double[size - 1];
        }
        for (int i = 1; i < size; ++i) {
            int j_temp = 0;
            for (int j = 0; j < size; ++j) {
                if (j == p) continue;
                tempMatrix[i - 1][j_temp] = matrixA[i][j];
                j_temp++;
            }
        }
        determinant += (p % 2 == 0 ? 1 : -1) * matrixA[0][p] * calculateDeterminant(tempMatrix, size - 1);
        for (int i = 0; i < size - 1; ++i) {
            delete[] tempMatrix[i];
        }
        delete[] tempMatrix;
    }
    return determinant;
}

/*
 * Освобождение памяти двумерного массива.
 *
 * @param matrix - указатель на двумерный массив.
 * @param size - размер массива (N).
 */
void freeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/*
 * Главная функция.
 */
int main() {
    srand(static_cast<unsigned>(time(0))); // Инициализация генератора случайных чисел

    int N;
    std::cout << "Введите размерность матриц: ";
    std::cin >> N;

    // Выделение памяти для 3 двумерных массивов
    double** matrixA = new double*[N];
    double** matrixB = new double*[N];
    double** resultMatrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrixA[i] = new double[N];
        matrixB[i] = new double[N];
        resultMatrix[i] = new double[N];
    }

    // Заполнение массивов случайными числами
    fillMatrix(matrixA, N);
    fillMatrix(matrixB, N);

    std::cout << "Матрица A:\n";
    printMatrix(matrixA, N);

    std::cout << "Матрица B:\n";
    printMatrix(matrixB, N);

    int choice;

    // Бесконечный цикл для выбора операции
    while (true) {
        std::cout << "Выберите операцию:\n";
        std::cout << "1. Сложение матриц\n";
        std::cout << "2. Умножение матриц\n";
        std::cout << "3. Транспонирование матрицы A\n";
        std::cout << "4. Транспонирование матрицы B\n";
        std::cout << "5. Поиск определителя матрицы A\n";
        std::cout << "6. Поиск определителя матрицы B\n";
        std::cout << "0. Выход\n";  // Опция выхода из программы
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addMatrices(matrixA, matrixB, resultMatrix, N);
                std::cout << "Результат сложения матриц A и B:\n";
                printMatrix(resultMatrix, N);
                break;
            case 2:
                multiplyMatrices(matrixA, matrixB, resultMatrix, N);
                std::cout << "Результат умножения матриц A и B:\n";
                printMatrix(resultMatrix, N);
                break;
            case 3:
                transposeMatrix(matrixA, resultMatrix, N);
                std::cout << "Результат транспонирования матрицы A:\n";
                printMatrix(resultMatrix, N);
                break;
            case 4:
                transposeMatrix(matrixB, resultMatrix, N);
                std::cout << "Результат транспонирования матрицы B:\n";
                printMatrix(resultMatrix, N);
                break;
            case 5:
                std::cout << "Определитель матрицы A: " << calculateDeterminant(matrixA, N) << std::endl;
                break;
            case 6:
                std::cout << "Определитель матрицы B: " << calculateDeterminant(matrixB, N) << std::endl;
                break;
            case 0:  // Выход из программы
                std::cout << "Выход из программы." << std::endl;
                freeMatrix(matrixA, N);
                freeMatrix(matrixB, N);
                freeMatrix(resultMatrix, N);
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
        }
    }

    return 0;
}
