#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib> // Для rand()
#include <ctime>   // Для time()
#include <algorithm> // Для std::max

class Zapchast {
protected:
    double replacementCost;  // Стоимость полной замены
    double repairCost;        // Стоимость починки
    double repairTime;        // Время, требуемое на починку
    double lifetime;          // Срок службы до полной замены (например, в часах)
    double wearLevel;         // Степень изношенности (от 0 до 100)

public:
    // Конструктор
    Zapchast(double rCost, double repCost, double repTime, double life)
        : replacementCost(rCost), repairCost(repCost), repairTime(repTime), lifetime(life), wearLevel(0) {}

    virtual bool isBroken() const {
        return wearLevel >= 100;
    }

    virtual void usePart(double usageIntensity) {
        wearLevel += usageIntensity;
        if (wearLevel > 100) {
            wearLevel = 100;
        }
    }

    double getRepairCost() const { return repairCost; } // Геттер для repairCost
    double getRepairTime() const { return repairTime; } // Геттер для repairTime
    virtual std::string getName() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Zapchast& z) {
        os << std::setw(20) << std::left << z.getName() 
           << std::setw(15) << z.replacementCost
           << std::setw(15) << z.repairCost
           << std::setw(15) << z.repairTime
           << std::setw(15) << z.lifetime
           << std::setw(10) << z.wearLevel << "%";
        return os;
    }

    virtual ~Zapchast() = default;
};

// Классы для запчастей
class Val : public Zapchast {
public:
    Val(double rCost, double repCost, double repTime, double life)
        : Zapchast(rCost, repCost, repTime, life) {}

    bool isBroken() const override {
        return wearLevel >= 80;
    }

    void usePart(double usageIntensity) override {
        wearLevel += usageIntensity * 1.5;
        if (wearLevel > 100) {
            wearLevel = 100;
        }
    }

    std::string getName() const override {
        return "Val";
    }
};

class Elektrodvigatel : public Zapchast {
public:
    Elektrodvigatel(double rCost, double repCost, double repTime, double life)
        : Zapchast(rCost, repCost, repTime, life) {}

    bool isBroken() const override {
        return wearLevel >= 90;
    }

    void usePart(double usageIntensity) override {
        wearLevel += usageIntensity * 1.2;
        if (wearLevel > 100) {
            wearLevel = 100;
        }
    }

    std::string getName() const override {
        return "Elektrodvigatel";
    }
};

class PanelUpravleniya : public Zapchast {
public:
    PanelUpravleniya(double rCost, double repCost, double repTime, double life)
        : Zapchast(rCost, repCost, repTime, life) {}

    bool isBroken() const override {
        return wearLevel >= 95;
    }

    void usePart(double usageIntensity) override {
        wearLevel += usageIntensity;
        if (wearLevel > 100) {
            wearLevel = 100;
        }
    }

    std::string getName() const override {
        return "Panel Upravleniya";
    }
};

class RezhushayaGolovka : public Zapchast {
public:
    RezhushayaGolovka(double rCost, double repCost, double repTime, double life)
        : Zapchast(rCost, repCost, repTime, life) {}

    bool isBroken() const override {
        return wearLevel >= 70;
    }

    void usePart(double usageIntensity) override {
        wearLevel += usageIntensity * 2;
        if (wearLevel > 100) {
            wearLevel = 100;
        }
    }

    std::string getName() const override {
        return "Rezhushaya Golovka";
    }
};

// Класс Станок
class Stanko {
private:
    std::vector<std::shared_ptr<Zapchast>> parts; // Набор запчастей
    double downtime; // Время простоя
    int brokenPartsCount; // Количество сломанных частей
    double repairCost; // Общая стоимость ремонта

public:
    Stanko() : downtime(0), brokenPartsCount(0), repairCost(0) {}

    void addPart(std::shared_ptr<Zapchast> part) {
        parts.push_back(part);
    }

    void useParts(double usageIntensity) {
        for (size_t i = 0; i < parts.size(); ++i) {
            parts[i]->usePart(usageIntensity);
        }
    }

    void work(double duration, double intensity) {
        for (double t = 0; t < duration; t += 1) { // Проходим по времени с шагом 1
            useParts(intensity); // Изнашиваем детали

            // Случайная вероятность поломки в процессе работы
            if (rand() % 100 < 5) { // 5% вероятность поломки
                int partIndex = rand() % parts.size(); // Случайно выбираем запчасть
                if (parts[partIndex]->isBroken()) {
                    brokenPartsCount++; // Увеличиваем счетчик поломок
                    repairCost += parts[partIndex]->getRepairCost(); // Увеличиваем стоимость ремонта с помощью геттера
                    downtime += parts[partIndex]->getRepairTime(); // Добавляем время ремонта
                    // Не удаляем сломанную запчасть
                }
            }
        }
    }

    int getBrokenPartsCount() const {
        return brokenPartsCount;
    }

    double getRepairCost() const {
        return repairCost;
    }

    double getDowntime() const {
        return downtime;
    }

    const std::vector<std::shared_ptr<Zapchast>>& getParts() const {
        return parts; // Добавлен геттер для доступа к запчастям
    }

    void printPartsTable() const {
        std::cout << std::setw(20) << std::left << "Part Name"
                  << std::setw(15) << "Replacement Cost"
                  << std::setw(15) << "Repair Cost"
                  << std::setw(15) << "Repair Time"
                  << std::setw(15) << "Lifetime"
                  << std::setw(10) << "Wear Level" << std::endl;

        std::cout << std::string(85, '-') << std::endl;

        for (const auto& part : parts) {
            std::cout << *part << std::endl; // Выводим информацию о запчастях
        }
    }

    virtual ~Stanko() = default;
};

// Класс Цеха
class Workshop {
private:
    std::vector<Stanko> machines; // Набор станков

public:
    void addStanko(const Stanko& stanko) {
        machines.push_back(stanko);
    }

    void simulateYear() {
        const int daysInYear = 365;
        const double hoursPerDay = 12;

        for (int month = 0; month < 12; ++month) {
            // Генерация случайной интенсивности работы (от 10 до 30)
            double intensity = rand() % 21 + 10; // Случайное значение от 10 до 30

            for (int day = 0; day < daysInYear / 12; ++day) { // 30 дней в месяце
                for (auto& machine : machines) {
                    machine.work(hoursPerDay, intensity);
                }
            }
        }
    }

    void printStatistics() const {
        int totalBrokenParts = 0;
        double totalRepairCost = 0;
        double totalDowntime = 0;
        double maxDowntime = 0;

        for (const auto& machine : machines) {
            totalBrokenParts += machine.getBrokenPartsCount();
            totalRepairCost += machine.getRepairCost();
            totalDowntime += machine.getDowntime();
            maxDowntime = std::max(maxDowntime, machine.getDowntime());
        }

        std::cout << "Статистика работы цеха за год:" << std::endl;
        std::cout << "Общее количество сломанных запчастей: " << totalBrokenParts << std::endl;
        std::cout << "Общая стоимость ремонта: " << totalRepairCost << std::endl;
        std::cout << "Общее время простоя: " << totalDowntime << std::endl;
        std::cout << "Максимальное время простоя: " << maxDowntime << std::endl;
    }

    void printAllMachines() const {
        for (const auto& machine : machines) {
            machine.printPartsTable(); // Выводим информацию о запчастях каждого станка
        }
    }
};

std::shared_ptr<Zapchast> createPart() {
    int partType;
    std::cout << "Выберите тип запчасти:" << std::endl;
    std::cout << "1. Val" << std::endl;
    std::cout << "2. Elektrodvigatel" << std::endl;
    std::cout << "3. Panel Upravleniya" << std::endl;
    std::cout << "4. Rezhushaya Golovka" << std::endl;
    std::cin >> partType;

    double replacementCost, repairCost, repairTime, lifetime;

    std::cout << "Введите стоимость полной замены: ";
    std::cin >> replacementCost;
    std::cout << "Введите стоимость починки: ";
    std::cin >> repairCost;
    std::cout << "Введите время, требуемое на починку: ";
    std::cin >> repairTime;
    std::cout << "Введите срок службы до полной замены (в часах): ";
    std::cin >> lifetime;

    switch (partType) {
        case 1:
            return std::make_shared<Val>(replacementCost, repairCost, repairTime, lifetime);
        case 2:
            return std::make_shared<Elektrodvigatel>(replacementCost, repairCost, repairTime, lifetime);
        case 3:
            return std::make_shared<PanelUpravleniya>(replacementCost, repairCost, repairTime, lifetime);
        case 4:
            return std::make_shared<RezhushayaGolovka>(replacementCost, repairCost, repairTime, lifetime);
        default:
            std::cout << "Неверный тип запчасти. Запчасть не добавлена." << std::endl;
            return nullptr;
    }
}

// Функция для работы с пользователем
void userInterface(Workshop& workshop) {
    int choice;
    do {
        std::cout << "\nВыберите действие:" << std::endl;
        std::cout << "1. Добавить станок" << std::endl;
        std::cout << "2. Показать информацию о станках" << std::endl;
        std::cout << "3. Симулировать работу цеха за год" << std::endl;
        std::cout << "4. Показать статистику работы цеха" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Stanko stanko;
                int numParts;
                std::cout << "Сколько запчастей хотите добавить? ";
                std::cin >> numParts;

                for (int i = 0; i < numParts; ++i) {
                    std::shared_ptr<Zapchast> part = createPart();
                    if (part) {
                        stanko.addPart(part);
                    }
                }

                workshop.addStanko(stanko);
                std::cout << "Станок добавлен." << std::endl;
                break;
            }
            case 2:
                workshop.printAllMachines();
                break;
            case 3:
                workshop.simulateYear();
                std::cout << "Симуляция работы цеха завершена." << std::endl;
                break;
            case 4:
                workshop.printStatistics();
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    } while (choice != 0);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    Workshop workshop;

    // Создание начальных станков и добавление запчастей
    for (int i = 0; i < 5; ++i) { // 5 станков
        Stanko stanko;
        stanko.addPart(std::make_shared<Val>(500, 100, 1.5, 200));
        stanko.addPart(std::make_shared<Elektrodvigatel>(1500, 300, 3, 300));
        stanko.addPart(std::make_shared<PanelUpravleniya>(200, 50, 1, 150));
        stanko.addPart(std::make_shared<RezhushayaGolovka>(300, 80, 2, 100));
        workshop.addStanko(stanko);
    }

    // Вызов функции для работы с пользователем
    userInterface(workshop);

    return 0;
}
