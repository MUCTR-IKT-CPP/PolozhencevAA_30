#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

// Функция сортировки перемешиванием (шейкерная сортировка)
void shakerSort(vector<double>& arr, int& passCount, long long& swapCount) { // Заменили swapCount на long long
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;
    passCount = 0;
    swapCount = 0;
    
    while (swapped) {
        swapped = false;
        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
                swapCount++;
            }
        }
        if (!swapped) break;
        end--;
        passCount++;

        swapped = false;
        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
                swapCount++;
            }
        }
        start++;
        passCount++;
    }
}

// Функция генерации массива
vector<double> generateArray(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(-1.0, 1.0);
    vector<double> arr(size);
    for (auto& el : arr) {
        el = dist(gen);
    }
    return arr;
}

int main() {
    vector<int> sizes = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};
    const int seriesCount = 8;
    const int attemptsPerSeries = 20;
    
    ofstream file("sorting_results.csv");
    file << "ArraySize,Series,Attempt,Time,Passes,Swaps" << endl;
    
    for (int size : sizes) {
        cout << "Размер массива: " << size << "\n";
        
        for (int series = 0; series < seriesCount; ++series) {
            for (int attempt = 0; attempt < attemptsPerSeries; ++attempt) {
                vector<double> arr = generateArray(size);
                int passCount = 0;
                long long swapCount = 0; // long long для предотвращения переполнения
                auto startTime = high_resolution_clock::now();
                
                shakerSort(arr, passCount, swapCount);
                
                auto endTime = high_resolution_clock::now();
                double duration = duration_cast<microseconds>(endTime - startTime).count() / 1e6;
                
                // Проверяем, не ушел ли swapCount в отрицательное значение
                if (swapCount < 0) {
                    cerr << "Ошибка: swapCount отрицательный! size=" << size << ", series=" << series + 1 << ", attempt=" << attempt + 1 << "\n";
                }

                file << size << "," << series + 1 << "," << attempt + 1 << "," << duration << "," << passCount << "," << swapCount << endl;
                
                cout << "Серия " << series + 1 << ", попытка " << attempt + 1 
                     << ": Время = " << duration << " сек, проходов = " << passCount 
                     << ", обменов = " << swapCount << "\n";
            }
        }
        cout << "\n";
    }
    file.close();
    return 0;
}
