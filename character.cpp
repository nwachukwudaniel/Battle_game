#include "character.hpp"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;


Character::Character()
    : name("Unknown"),
      health(100),
      max_health(100),
      min_attack(10),
      max_attack(20) {
}


Character::Character(string name, int max_health,
                     int min_attack, int max_attack)
    : name(name) {

    if (max_health <= 0) {
        this->max_health = 100;
    } else {
        this->max_health = max_health;
    }

    if (min_attack <= 0 || min_attack > max_attack) {
        this->min_attack = 10;
        this->max_attack = 20;
    } else {
        this->min_attack = min_attack;
        this->max_attack = max_attack;
    }

    health = this->max_health;
}

string Character::get_name() const {
    return name;
}

int Character::get_health() const {
    return health;
}

int Character::get_max_health() const {
    return max_health;
}

int Character::get_min_attack() const {
    return min_attack;
}

int Character::get_max_attack() const {
    return max_attack;
}

bool Character::is_alive() const {
    return health > 0;
}

int Character::heal() {

    int amount = 5 + rand() % 11;

    int old_health = health;

    health += amount;

    if (health > max_health) {
        health = max_health;
    }

    return health - old_health;
}


int Character::attack(Character& opponent) const {

    int damage = min_attack +
                 rand() % (max_attack - min_attack + 1);

    opponent.health -= damage;

    if (opponent.health < 0) {
        opponent.health = 0;
    }

    return damage;
}

ostream& operator<<(ostream& out, const Character& c) {

    out << c.name
        << " (health: "
        << c.health
        << "/"
        << c.max_health
        << ", attack: "
        << c.min_attack
        << "-"
        << c.max_attack
        << ")";

    return out;
}

void show_attack_animation() {

    cout << "   >>> ATTACK";

    for (int i = 0; i < 3; i++) {

        cout << ".";
        cout.flush();

        this_thread::sleep_for(
            chrono::milliseconds(300)
        );
    }

    cout << endl;

    cout << "   >>> HIT!" << endl;

    this_thread::sleep_for(
        chrono::milliseconds(400)
    );
}


void show_heal_animation() {

    cout << "   * HEALING";

    for (int i = 0; i < 3; i++) {

        cout << ".";
        cout.flush();

        this_thread::sleep_for(
            chrono::milliseconds(300)
        );
    }

    cout << endl;

    cout << "   * HEALTH RESTORED!" << endl;

    this_thread::sleep_for(
        chrono::milliseconds(400)
    );
}


void show_health_bar(const Character& character) {

    int max_health = character.get_max_health();
    int health = character.get_health();

    int bar_size = 20;

    int filled = (health * bar_size) / max_health;

    cout << "   "
         << character.get_name()
         << " [";

    for (int i = 0; i < bar_size; i++) {

        if (i < filled) {
            cout << "#";
        } else {
            cout << "-";
        }
    }

    cout << "] "
         << health
         << "/"
         << max_health
         << endl;
}

void make_turn(Character& active, Character& opponent) {

    cout << "----------------------------------------"
         << endl;

    cout << active.get_name()
         << "'s turn!"
         << endl;

    this_thread::sleep_for(
        chrono::milliseconds(500)
    );

    int action = 1 + rand() % 4;


    if (action == 1) {

        cout << active.get_name()
             << " chooses to heal!"
             << endl;

        show_heal_animation();

        int restored = active.heal();

        cout << active.get_name()
             << " heals: +"
             << restored
             << " health"
             << endl;

        show_health_bar(active);
    }


    else {

        cout << active.get_name()
             << " attacks "
             << opponent.get_name()
             << "!"
             << endl;

        show_attack_animation();

        int damage = active.attack(opponent);

        cout << active.get_name()
             << " attacks "
             << opponent.get_name()
             << ": "
             << damage
             << " damage"
             << endl;

        show_health_bar(opponent);
    }

    cout << endl;

    this_thread::sleep_for(
        chrono::milliseconds(500)
    );
}


void fight(Character& c1, Character& c2) {

    cout << endl;
    cout << "========================================"
         << endl;

    cout << "           BATTLE STARTS!"
         << endl;

    cout << "========================================"
         << endl;

    cout << endl;

    this_thread::sleep_for(
        chrono::milliseconds(1000)
    );


    Character* active = &c1;
    Character* opponent = &c2;


    while (c1.is_alive() && c2.is_alive()) {

        make_turn(*active, *opponent);


        if (!opponent->is_alive()) {

            cout << "----------------------------------------"
                 << endl;

            cout << opponent->get_name()
                 << " has been defeated!"
                 << endl;

            cout << "----------------------------------------"
                 << endl;

            break;
        }


        Character* temp = active;

        active = opponent;

        opponent = temp;
    }


    cout << endl;

    cout << "========================================"
         << endl;


    if (c1.is_alive()) {

        cout << "           "
             << c1.get_name()
             << " WINS!"
             << endl;

    } else {

        cout << "           "
             << c2.get_name()
             << " WINS!"
             << endl;
    }


    cout << "========================================"
         << endl;
}

