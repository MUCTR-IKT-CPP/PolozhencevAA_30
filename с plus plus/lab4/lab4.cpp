#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Перечисление для типов персонажей
enum CharacterType {
    SWORDSMAN,
    MAGE,
    ARCHER
};

// Базовый класс Персонаж
class Character {
public:
    virtual ~Character() {}
    virtual void display() const = 0;
};

// Класс Мечник
class Swordsman : public Character {
public:
    int strength;
    int endurance;
    int distance;
    int cost;

    Swordsman(int str, int endur, int dist, int cst)
        : strength(str), endurance(endur), distance(dist), cost(cst) {}

    void display() const override {
        std::cout << "Swordsman - Strength: " << strength << ", Endurance: " << endurance
                  << ", Distance: " << distance << ", Cost: " << cost << std::endl;
    }
};

// Класс Маг
class Mage : public Character {
public:
    int strength;
    int endurance;
    int distance;
    int cost;

    Mage(int str, int endur, int dist, int cst)
        : strength(str), endurance(endur), distance(dist), cost(cst) {}

    void display() const override {
        std::cout << "Mage - Strength: " << strength << ", Endurance: " << endurance
                  << ", Distance: " << distance << ", Cost: " << cost << std::endl;
    }
};

// Класс Стрелок
class Archer : public Character {
public:
    int strength;
    int endurance;
    int distance;
    int cost;

    Archer(int str, int endur, int dist, int cst)
        : strength(str), endurance(endur), distance(dist), cost(cst) {}

    void display() const override {
        std::cout << "Archer - Strength: " << strength << ", Endurance: " << endurance
                  << ", Distance: " << distance << ", Cost: " << cost << std::endl;
    }
};

// Класс Наемник
class Mercenary {
private:
    void* character;        // Указатель на пустоту для хранения персонажа
    CharacterType type;     // Переменная для хранения типа персонажа

public:
    Mercenary() : character(nullptr), type(SWORDSMAN) {}

    // Метод для установки персонажа и его типа
    void setCharacter(void* charPtr, CharacterType charType) {
        character = charPtr;
        type = charType;
    }

    // Метод для отображения информации о наемнике
    void display() const {
        switch (type) {
            case SWORDSMAN:
                static_cast<Swordsman*>(character)->display();
                break;
            case MAGE:
                static_cast<Mage*>(character)->display();
                break;
            case ARCHER:
                static_cast<Archer*>(character)->display();
                break;
            default:
                std::cout << "Unknown character type!" << std::endl;
                break;
        }
    }

    // Деструктор, который очищает память для персонажа
    ~Mercenary() {
        switch (type) {
            case SWORDSMAN:
                delete static_cast<Swordsman*>(character);
                break;
            case MAGE:
                delete static_cast<Mage*>(character);
                break;
            case ARCHER:
                delete static_cast<Archer*>(character);
                break;
        }
    }
};

// Класс Гильдия
class Guild {
private:
    std::vector<Mercenary> mercenaries;  // Список наемников в гильдии

public:
    // Метод для добавления наемника в гильдию
    void addMercenary(const Mercenary& mercenary) {
        mercenaries.push_back(mercenary);
    }

    // Метод для отображения всех наемников в гильдии
    void display() const {
        std::cout << "Guild contains the following mercenaries:\n";
        for (const auto& merc : mercenaries) {
            merc.display();
        }
    }

    // Метод для случайного заполнения гильдии
    void fillRandomly() {
        srand(time(0));

        // Обязательные наемники
        Swordsman* tank = new Swordsman(80, 200, 1, 700);  // Мечник-танк с высокой стойкостью
        Swordsman* highDamage = new Swordsman(150, 100, 1, 600);  // Мечник с высокой атакой

        Mage* midRangeMage = new Mage(130, 90, 3, 500);  // Маг средней дистанции
        Mage* longRangeMage = new Mage(120, 80, 4, 550); // Маг дальней дистанции

        Archer* midRangeArcher = new Archer(100, 160, 2, 450);  // Стрелок средней дистанции
        Archer* longRangeArcher = new Archer(90, 180, 3, 480);  // Стрелок дальней дистанции

        // Добавляем обязательных наемников
        Mercenary merc1, merc2, merc3, merc4, merc5, merc6;
        merc1.setCharacter(static_cast<void*>(tank), SWORDSMAN);
        merc2.setCharacter(static_cast<void*>(highDamage), SWORDSMAN);
        merc3.setCharacter(static_cast<void*>(midRangeMage), MAGE);
        merc4.setCharacter(static_cast<void*>(longRangeMage), MAGE);
        merc5.setCharacter(static_cast<void*>(midRangeArcher), ARCHER);
        merc6.setCharacter(static_cast<void*>(longRangeArcher), ARCHER);

        addMercenary(merc1);
        addMercenary(merc2);
        addMercenary(merc3);
        addMercenary(merc4);
        addMercenary(merc5);
        addMercenary(merc6);

        // Можно добавить еще случайных наемников, если нужно
    }
};

int main() {
    // Создаем гильдию
    Guild guild;

    // Заполняем гильдию случайными наемниками
    guild.fillRandomly();

    // Отображаем информацию о гильдии
    guild.display();

    return 0;
}
