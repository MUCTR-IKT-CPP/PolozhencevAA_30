#include <iostream>
#include <vector>

/*
 * Нахождение простых чисел до числа n
 *
 * @param n предел поиска простых чисел.
 * @param is_prime вектор, в котором будет отмечено, какие числа являются простыми.
 */
void finding_prime_numbers(int n, std::vector<bool>& is_prime) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }
}

/*
 * Вывод простых чисел.
 *
 * @param is_prime вектор, который содержит информацию о том, является ли число простым.
 * @param n предел поиска простых чисел.
 */
void print_prime_numbers(const std::vector<bool>& is_prime, int n) {
    std::cout << "Простые числа до " << n << ": ";
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Введите число n: ";
    std::cin >> n;

    std::vector<bool> is_prime;

    finding_prime_numbers(n, is_prime);
    print_prime_numbers(is_prime, n);

    return 0;
}
