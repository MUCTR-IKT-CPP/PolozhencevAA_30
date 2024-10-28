#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <random>
#include <cmath>
#include <climits>
#include <iomanip> // Для std::setw и std::setfill

using namespace std;

/*
 * Базовый класс для бойцов.
 */
class Fighter {
protected:
    string fighterName; // Имя бойца
    int healthPoints;   // Текущее здоровье бойца
    int defenseArmor;   // Броня бойца
    int extraDamage;    // Бонусный урон
    int attackSpeed;    // Инициатива бойца
    bool isFighterAlive; // Статус живости бойца
    int teamID;          // Номер команды, к которой принадлежит боец
    int posX, posY;      // Позиция бойца на поле (координаты)

/*
     * Конструктор для создания бойца.
     *
     * @param name Имя бойца.
     * @param health Здоровье бойца.
     * @param armor Броня бойца.
     * @param damage Бонусный урон.
     * @param speed Инициатива бойца.
     * @param team Номер команды.
     * @param xPos Позиция по оси X.
     * @param yPos Позиция по оси Y.
     */
public:
    Fighter(string name, int health, int armor, int bonusDamage, int initiative, int teamNum, int xPos, int yPos)
        : fighterName(name), healthPoints(health), defenseArmor(armor), extraDamage(bonusDamage), attackSpeed(initiative), isFighterAlive(true), teamID(teamNum), posX(xPos), posY(yPos) {}

    virtual ~Fighter() {}

    virtual void attack(Fighter& enemy) = 0;
    virtual void move(int targetX, int targetY) = 0;
    bool alive() const { return isFighterAlive; }

    void receiveDamage(int damage) {
        healthPoints -= damage;
        if (healthPoints <= 0) {
            healthPoints = 0;
            isFighterAlive = false;
        }
    }

    const string& getName() const { return fighterName; }
    int getTeamID() const { return teamID; }
    int getArmor() const { return defenseArmor; }
    int getHealth() const { return healthPoints; }
    int getX() const { return posX; }
    int getY() const { return posY; }
    int getInitiative() const { return attackSpeed; }

    void setPosition(int xPos, int yPos) {
        posX = xPos;
        posY = yPos;
    }

    friend ostream& operator<<(ostream& os, const Fighter& fighter) {
        os << left << setw(15) << fighter.fighterName
           << left << setw(10) << fighter.teamID
           << left << setw(10) << fighter.healthPoints
           << left << setw(10) << fighter.defenseArmor
           << left << setw(10) << fighter.extraDamage
           << left << setw(10) << fighter.attackSpeed
           << (fighter.isFighterAlive ? "Да" : "Нет");
        return os;
    }
};

/*
     * Конструктор для создания воина.
     *
     * @param name Имя воина.
     * @param health Здоровье воина.
     * @param armor Броня воина.
     * @param damage Бонусный урон.
     * @param speed Инициатива воина.
     * @param team Номер команды.
     * @param xPos Позиция по оси X.
     * @param yPos Позиция по оси Y.
     */
class Warrior : public Fighter {
public:
    Warrior(string name, int health, int armor, int bonusDamage, int initiative, int teamNum, int xPos, int yPos)
        : Fighter(name, health, armor, bonusDamage, initiative, teamNum, xPos, yPos) {}

    void attack(Fighter& enemy) override {
        if (!enemy.alive()) return;
        int damage = max(1, (rand() % 20 + 1) + extraDamage - enemy.getArmor());
        cout << fighterName << " (Команда " << teamID << ") наносит урон: " << damage << " на "
             << enemy.getName() << " (Команда " << enemy.getTeamID() << ")\n";
        enemy.receiveDamage(damage);
        cout << enemy.getName() << " (Команда " << enemy.getTeamID() << ") осталось здоровья: "
             << enemy.getHealth() << "\n";
    }

    void move(int targetX, int targetY) override {
        setPosition(targetX, targetY);
        cout << fighterName << " движется к врагу.\n";
    }
};
class Archer : public Fighter {
    /*
     * Конструктор для создания лучника.
     *
     * @param name Имя лучника.
     * @param health Здоровье лучника.
     * @param armor Броня лучника.
     * @param damage Бонусный урон.
     * @param speed Инициатива лучника.
     * @param team Номер команды.
     * @param xPos Позиция по оси X.
     * @param yPos Позиция по оси Y.
     */
public:
    Archer(string name, int health, int armor, int bonusDamage, int initiative, int teamNum, int xPos, int yPos)
        : Fighter(name, health, armor, bonusDamage, initiative, teamNum, xPos, yPos) {}

    void attack(Fighter& enemy) override {
        if (!enemy.alive()) return;
        int damage = max(1, (rand() % 20 + 1) + extraDamage - enemy.getArmor());
        cout << fighterName << " (Команда " << teamID << ") стреляет в " << enemy.getName()
             << " (Команда " << enemy.getTeamID() << ") и наносит " << damage << " урона.\n";
        enemy.receiveDamage(damage);
        cout << enemy.getName() << " (Команда " << enemy.getTeamID() << ") осталось здоровья: "
             << enemy.getHealth() << "\n";
    }

    void move(int targetX, int targetY) override {
        setPosition(targetX, targetY);
        cout << fighterName << " движется к врагу.\n";
    }
};

class Mage : public Fighter {
public:
/*
     * Конструктор для создания мага.
     *
     * @param name Имя мага.
     * @param health Здоровье мага.
     * @param armor Броня мага.
     * @param damage Бонусный урон.
     * @param speed Инициатива мага.
     * @param team Номер команды.
     * @param xPos Позиция по оси X.
     * @param yPos Позиция по оси Y.
     */
    Mage(string name, int health, int armor, int bonusDamage, int initiative, int teamNum, int xPos, int yPos)
        : Fighter(name, health, armor, bonusDamage, initiative, teamNum, xPos, yPos) {}

    void attack(Fighter& enemy) override {
        if (!enemy.alive()) return;
        int damage = max(1, (rand() % 20 + 1) + extraDamage - enemy.getArmor());
        cout << fighterName << " (Команда " << teamID << ") колдует на " << enemy.getName()
             << " (Команда " << enemy.getTeamID() << ") и наносит " << damage << " урона.\n";
        enemy.receiveDamage(damage);
        cout << enemy.getName() << " (Команда " << enemy.getTeamID() << ") осталось здоровья: "
             << enemy.getHealth() << "\n";
    }

    void move(int targetX, int targetY) override {
        setPosition(targetX, targetY);
        cout << fighterName << " движется к врагу.\n";
    }
};

class Team {
private:
    vector<unique_ptr<Fighter>> teamFighters; // Список бойцов в команде

public:
    void addFighter(unique_ptr<Fighter> fighter) {
        teamFighters.push_back(move(fighter));
    }

    vector<unique_ptr<Fighter>>& getFighters() {
        return teamFighters;
    }

    bool hasAliveFighters() const {
        return any_of(teamFighters.begin(), teamFighters.end(), [](const unique_ptr<Fighter>& fighter) {
            return fighter->alive();
        });
    }

    Fighter* findNearestEnemy(Fighter& fighter) {
        Fighter* closestEnemy = nullptr;
        int minimumDistance = INT_MAX;

        for (const auto& enemy : teamFighters) {
            if (enemy->alive()) {
                int distance = calculateDistance(fighter, *enemy);
                if (distance < minimumDistance) {
                    minimumDistance = distance;
                    closestEnemy = enemy.get();
                }
            }
        }

        return closestEnemy;
    }

    static int calculateDistance(const Fighter& a, const Fighter& b) {
        return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
    }

    void sortByInitiative() {
        sort(teamFighters.begin(), teamFighters.end(), [](const unique_ptr<Fighter>& a, const unique_ptr<Fighter>& b) {
            return a->getInitiative() > b->getInitiative();
        });
    }

    void displayFighters() const {
        cout << left << setw(15) << "Имя"
             << left << setw(10) << "Команда"
             << left << setw(10) << "Здоровье"
             << left << setw(10) << "Броня"
             << left << setw(10) << "Бонус"
             << left << setw(10) << "Инициатива"
             << "Жив" << endl;

        cout << string(75, '-') << endl;

        for (const auto& fighter : teamFighters) {
            cout << *fighter;
            cout << endl;
        }

        cout << string(75, '-') << endl;
    }
};

Team createTeam(int teamSize, int teamID) {
    Team team;
    for (int i = 0; i < teamSize; ++i) {
        int fighterType = rand() % 3;
        if (fighterType == 0) {
            team.addFighter(unique_ptr<Warrior>(new Warrior("Воин___" + to_string(i + 1), 100, 10, 5, rand() % 20 + 1, teamID, 0, 0)));
        } else if (fighterType == 1) {
            team.addFighter(unique_ptr<Archer>(new Archer("Лучник_" + to_string(i + 1), 80, 5, 8, rand() % 20 + 1, teamID, 1, 1)));
        } else {
            team.addFighter(unique_ptr<Mage>(new Mage("Маг____" + to_string(i + 1), 60, 3, 10, rand() % 20 + 1, teamID, 2, 2)));
        }
    }
    return team;
}

/*
 * Функция для создания команды бойцов указанного размера.
 *
 * @param teamSize Размер команды.
 * @param teamNum Номер команды.
 * @return Возвращает созданную команду.
 */
void battleTeams(Team& team1, Team& team2) {
    while (team1.hasAliveFighters() && team2.hasAliveFighters()) {
        team1.sortByInitiative();
        team2.sortByInitiative();

        cout << "\n--- Бой ---\n";
        team1.displayFighters();
        team2.displayFighters();

        for (auto& fighter : team1.getFighters()) {
            if (fighter->alive()) {
                Fighter* target = team2.findNearestEnemy(*fighter);
                if (target) {
                    int distance = Team::calculateDistance(*fighter, *target);
                    if (distance > 1) {
                        fighter->move(target->getX(), target->getY());
                    } else {
                        fighter->attack(*target);
                    }
                }
            }
        }

        for (auto& fighter : team2.getFighters()) {
            if (fighter->alive()) {
                Fighter* target = team1.findNearestEnemy(*fighter);
                if (target) {
                    int distance = Team::calculateDistance(*fighter, *target);
                    if (distance > 1) {
                        fighter->move(target->getX(), target->getY());
                    } else {
                        fighter->attack(*target);
                    }
                }
            }
        }

        cout << "\n\n--- Следующий раунд ---\n\n";
    }

    if (team1.hasAliveFighters()) {
        cout << "Команда 1 победила!\n";
    } else {
        cout << "Команда 2 победила!\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Создаем две команды бойцов
    Team team1 = createTeam(5, 1);
    Team team2 = createTeam(5, 2);

    // Запускаем бой между командами
    battleTeams(team1, team2);

    return 0;
}
