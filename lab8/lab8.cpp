#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <map>

class Bullet {
public:
    enum class Type {
        Subsonic,
        Regular,
        Tracer
    };

    Bullet(Type type) : type(type) {}

    void shoot() const {
        // switch (type) {
        //     case Type::Subsonic:
        //         std::cout << "Выстрел из дозвукового патрона: Тихий звук.\n";
        //         break;
        //     case Type::Regular:
        //         std::cout << "Выстрел из обычного патрона: Стандартный звук.\n";
        //         break;
        //     case Type::Tracer:
        //         std::cout << "Выстрел из трассирующего патрона: Стандартный звук с эффектом подсветки.\n";
        //         break;
        // }
    }

    Type getType() const {
        return type;
    }

    std::string getTypeName() const {
        switch (type) {
            case Type::Subsonic: return "дозвуковой";
            case Type::Regular: return "обычный";
            case Type::Tracer: return "трассирующий";
            default: return "неизвестный";
        }
    }

private:
    Type type;
};

class Magazine {
public:
    Magazine() {}

    bool isEmpty() const {
        return bullets.empty();
    }

    Bullet takeBullet() {
        return extractBullet(); // Извлечение патрона с задержкой
    }

    void loadBullet(Bullet bullet) {
        bullets.push_back(bullet);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Время на зарядку патрона
    }

    void fillMagazine(const std::vector<Bullet>& bulletSet) {
        for (const Bullet& bullet : bulletSet) {
            if (bullets.size() < 30) { // Ограничение по количеству патронов в магазине
                loadBullet(bullet);
            } else {
                std::cout << "Магазин заполнен! Нельзя загрузить больше патронов.\n";
                break;
            }
        }
    }

    void clearMagazine() {
        while (!isEmpty()) {
            extractBullet(); // Разрядка магазина
        }
    }

    size_t getBulletCount() const {
        return bullets.size();
    }

    Bullet peekBullet() const {
        if (!isEmpty()) {
            return bullets.back(); // Вернуть последний патрон, не извлекая его
        }
        throw std::runtime_error("Магазин пуст!");
    }

private:
    std::vector<Bullet> bullets;

    Bullet extractBullet() {
        if (!isEmpty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Время на изъятие патрона
            Bullet bullet = bullets.back();
            bullets.pop_back();
            return bullet;
        }
        throw std::runtime_error("Магазин пуст!");
    }
};

class AmmoBox {
public:
    AmmoBox(Bullet::Type type, int count) : type(type), bulletCount(count) {}

    bool hasBullets() const {
        return bulletCount > 0;
    }

    int getBulletCount() const {
        return bulletCount;
    }

    void takeBullets(int count) {
        if (bulletCount >= count) {
            bulletCount -= count;
        } else {
            std::cout << "Недостаточно патронов в коробке, доступно: " << bulletCount << "\n";
            bulletCount = 0; // Обнуляем, если не хватает
        }
    }

    Bullet::Type getType() const {
        return type;
    }

    std::string getTypeName() const {
        return Bullet(type).getTypeName(); // Используем Bullet для получения имени типа
    }

private:
    Bullet::Type type;
    int bulletCount;
};

class Weapon {
public:
    Weapon(Magazine& mag, std::vector<AmmoBox>& boxes) : magazine(mag), ammoBoxes(boxes) {}

    void shoot() {
        // Перед выстрелом нужно зарядить патрон в ствол
        if (magazine.isEmpty()) {
            std::cout << "Нельзя стрелять: Магазин пуст!\n";
            return;
        }
        
        // Зарядка патрона в ствол
        Bullet bullet = magazine.takeBullet();
        chamber.loadBullet(bullet); // Теперь патрон в стволе

        // Теперь выстреливаем
        if (!chamber.isEmpty()) {
            Bullet chamberBullet = chamber.takeBullet();
            chamberBullet.shoot(); // Выполняем выстрел
            animateBulletFlight(chamberBullet); // Анимация полета патрона
        } else {
            std::cout << "Нельзя стрелять: Ствол пуст!\n";
        }
    }

    void emptyMagazine() {
        while (!magazine.isEmpty()) {
            shoot(); // Выстрелим все патроны в магазине
        }
    }

    void demonstrateAllBullets() {
        for (Bullet::Type type : {Bullet::Type::Subsonic, Bullet::Type::Regular, Bullet::Type::Tracer}) {
            Bullet bullet(type);
            bullet.shoot();
            animateBulletFlight(bullet);
        }
    }

    size_t getChamberBulletCount() const {
        return chamber.getBulletCount();
    }

    std::string getChamberBulletType() const {
        if (!chamber.isEmpty()) {
            return chamber.peekBullet().getTypeName(); // Используем peekBullet вместо takeBullet
        }
        return "нет патронов в стволе";
    }

    std::string getMagazineBulletType() const {
        if (!magazine.isEmpty()) {
            return magazine.peekBullet().getTypeName(); // Получаем тип последнего патрона в магазине
        }
        return "нет патронов в магазине";
    }

    void displayBulletInfo() const {
        std::cout << "Количество патронов в магазине: " << magazine.getBulletCount() << "\n";
        std::cout << "Количество патронов в стволе: " << getChamberBulletCount() << "\n";
        std::cout << "Тип патрона в стволе: " << getChamberBulletType() << "\n";
        std::cout << "Тип патрона в магазине: " << getMagazineBulletType() << "\n"; // Добавлено для отображения типа патронов в магазине
    }

    void loadMagazine() {
        if (!magazine.isEmpty()) {
            std::cout << "Разрядка магазина перед зарядкой...\n";
            magazine.clearMagazine(); // Разрядка магазина
        }

        while (true) {
            std::cout << "Выберите тип патронов для зарядки:\n";
            for (size_t i = 0; i < ammoBoxes.size(); ++i) {
                std::cout << i + 1 << ") " << ammoBoxes[i].getBulletCount() << " " << ammoBoxes[i].getTypeName() << " патронов\n";
            }
            int choice;
            std::cin >> choice;

            if (choice < 1 || choice > ammoBoxes.size()) {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                continue; // Снова запрашиваем выбор
            }

            AmmoBox& selectedBox = ammoBoxes[choice - 1];

            // Проверяем наличие патронов в выбранной коробке
            if (selectedBox.hasBullets()) {
                int bulletsToLoad = std::min(30, selectedBox.getBulletCount());
                for (int i = 0; i < bulletsToLoad; ++i) {
                    magazine.loadBullet(Bullet(selectedBox.getType())); // Загружаем патроны в магазин
                }
                selectedBox.takeBullets(bulletsToLoad); // Извлекаем патроны из коробки
                std::cout << "Магазин успешно заряжен патронами.\n";
                break; // Выходим из цикла после успешной зарядки
            } else {
                std::cout << "В выбранной коробке отсутствуют патроны. Попробуйте снова.\n";
            }
        }
    }

    void shootUntilEmpty() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(30, 50);
    int totalBullets = dist(gen);

    // Генерация коробки с патронами от 300 до 500 патронов
    std::vector<Bullet> newAmmo;

    // Генерация случайного типа патронов
    for (int i = 0; i < totalBullets; ++i) {
        Bullet::Type type = static_cast<Bullet::Type>(std::rand() % 3); // Случайный выбор типа
        newAmmo.push_back(Bullet(type));
    }

    // Переменные для статистики
    int totalFiredBullets = 0;
    int totalLoadedMagazines = 0;
    auto totalLoadingTime = std::chrono::milliseconds(0);
    auto totalShootingTime = std::chrono::milliseconds(0);
    std::map<Bullet::Type, int> bulletCountMap = {
        {Bullet::Type::Subsonic, 0},
        {Bullet::Type::Regular, 0},
        {Bullet::Type::Tracer, 0}
    };

    // Подсчет количества каждого типа патронов
    for (const auto& bullet : newAmmo) {
        bulletCountMap[bullet.getType()]++;
    }

    // Циклическая стрельба, пока в коробке есть патроны
    while (!newAmmo.empty()) {
        // Загрузка 30 патронов в магазин
        auto startLoadingTime = std::chrono::steady_clock::now(); // Время начала зарядки
        magazine.clearMagazine(); // Очистка старого магазина
        magazine.fillMagazine(newAmmo); // Заполнение магазина новыми патронами
        totalLoadedMagazines++; // Увеличиваем счетчик загруженных магазинов
        auto endLoadingTime = std::chrono::steady_clock::now(); // Время окончания зарядки
        totalLoadingTime += std::chrono::duration_cast<std::chrono::milliseconds>(endLoadingTime - startLoadingTime); // Суммируем время зарядки

        std::cout << "Магазин успешно заряжен: " << getMagazineBulletType() << " патронами.\n";

        // Циклическая стрельба, пока в магазине есть патроны
        auto startShootingTime = std::chrono::steady_clock::now(); // Время начала стрельбы
        while (!magazine.isEmpty()) {
            this->shoot(); // Выполнение выстрела
            totalFiredBullets++; // Увеличиваем счетчик отстрелянных патронов
        }
        auto endShootingTime = std::chrono::steady_clock::now(); // Время окончания стрельбы
        totalShootingTime += std::chrono::duration_cast<std::chrono::milliseconds>(endShootingTime - startShootingTime); // Суммируем время стрельбы

        // Удаляем использованные патроны
        newAmmo.erase(newAmmo.begin(), newAmmo.begin() + std::min(30, static_cast<int>(newAmmo.size())));
        std::cout << "Осталось патронов в коробке: " << newAmmo.size() << "\n";
    }

    // Вывод статистики после завершения стрельбы
    std::cout << "Статистика стрельбы:\n";
    std::cout << "Суммарное количество отстрелянных патронов: " << totalFiredBullets << "\n";
    std::cout << "Суммарное количество заряженных магазинов: " << totalLoadedMagazines << "\n";
    std::cout << "Суммарное время на зарядку патронов в магазин: " << totalLoadingTime.count() << " мс\n";
    std::cout << "Суммарное время стрельбы: " << totalShootingTime.count() << " мс\n";
    std::cout << "Количество патронов каждого типа:\n";
    std::cout << "  Дозвуковые: " << bulletCountMap[Bullet::Type::Subsonic] << "\n";
    std::cout << "  Обычные: " << bulletCountMap[Bullet::Type::Regular] << "\n";
    std::cout << "  Трассирующие: " << bulletCountMap[Bullet::Type::Tracer] << "\n";
    std::cout << "Все патроны исчерпаны.\n";
}




private:
    Magazine& magazine;
    Magazine chamber; // Ствол как отдельный магазин
    std::vector<AmmoBox>& ammoBoxes; // Вектор коробок с патронами

    void animateBulletFlight(const Bullet& bullet) {
        int flightTime = 0;  // Задержка между символами
        char movingSymbol;   // Символ для отображения

        // Определение символа и времени полета в зависимости от типа патрона
        switch (bullet.getType()) {
            case Bullet::Type::Subsonic:
                movingSymbol = '.';
                flightTime = 100; // Задержка 100 мс
                break;
            case Bullet::Type::Regular:
                movingSymbol = '*';
                flightTime = 200; // Задержка 200 мс
                break;
            case Bullet::Type::Tracer:
                movingSymbol = '-';
                flightTime = 300; // Задержка 300 мс
                break;
        }

        // Анимация полета патрона
        for (int i = 0; i < 10; ++i) { // 10 знаков для полета
            std::cout << movingSymbol;   // Отображаем символ
            std::cout.flush();           // Обеспечиваем немедленный вывод на экран
            std::this_thread::sleep_for(std::chrono::milliseconds(flightTime)); // Задержка перед следующим символом
        }
        std::cout << ">\n"; // Символ в конце полета
    }
};


// Обновляем меню
void displayMenu() {
    std::cout << "Выберите действие:\n";
    std::cout << "1) Извлечь патрон из магазина\n";
    std::cout << "2) Извлечь патрон из ствола\n";
    std::cout << "3) Зарядить магазин\n";
    std::cout << "4) Выстрелить из оружия\n";
    std::cout << "5) Выстрелить весь магазин\n";
    std::cout << "6) Демонстрация всех патронов\n";
    std::cout << "7) Процесс стрельбы (усложненный вариант)\n"; // Обновленный пункт меню
    std::cout << "0) Выход\n";
}

int main() {
    Magazine magazine;

    // Инициализация коробок с патронами
    std::vector<AmmoBox> ammoBoxes = {
        AmmoBox(Bullet::Type::Subsonic, 10),
        AmmoBox(Bullet::Type::Regular, 20),
        AmmoBox(Bullet::Type::Tracer, 5)
    };

    Weapon weapon(magazine, ammoBoxes);

    // Заполнение магазина из предустановленного набора патронов
    std::vector<Bullet> bulletSet = {
        Bullet(Bullet::Type::Subsonic),
        Bullet(Bullet::Type::Regular),
        Bullet(Bullet::Type::Tracer)
    };

    magazine.fillMagazine(bulletSet);

   while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (!magazine.isEmpty()) {
                    magazine.takeBullet();
                    std::cout << "Патрон извлечен из магазина.\n";
                } else {
                    std::cout << "Магазин пуст!\n";
                }
                break;
            case 2:
                if (!weapon.getChamberBulletCount()) {
                    std::cout << "В стволе нет патронов!\n";
                } else {
                    weapon.shoot(); // Выполнение выстрела
                    std::cout << "Патрон извлечен из ствола.\n";
                }
                break;
            case 3:
                weapon.loadMagazine(); // Перезарядка магазина
                break;
            case 4:
                weapon.shoot(); // Обычный выстрел
                break;
            case 5:
                weapon.emptyMagazine(); // Выстрелить весь магазин
                break;
            case 6:
                weapon.demonstrateAllBullets(); // Показать все патроны
                break;
            case 7:
                weapon.shootUntilEmpty(); // Запуск процесса стрельбы
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }

        // Вывод информации о количестве патронов после выполнения действия
        weapon.displayBulletInfo(); // Обновленный вывод информации
    }

    return 0;
}
