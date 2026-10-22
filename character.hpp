#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <string>


class Character {

public:

    //constructors

    Character();
    Character(std::string name, int max_health, int min_attack, int max_attack);

    // Getter functions

    std::string get_name() const;
    int get_health() const;
    int get_max_health() const;
    int get_min_attack() const;
    int get_max_attack() const;


    // members

    bool is_alive() const;
    int heal();
    int attack(Character& opponent) const;

private:
    std::string name;
    int health;
    int max_health;
    int min_attack;
    int max_attack;

    friend std::ostream& operator<<(std::ostream& out, const Character& c);
};

// non_member function

void make_turn(Character& active, Character& opponent);
void fight(Character& c1, Character& c2);

std::ostream& operator<<(std::ostream& out, const Character& c);


#endif //CHARACTER_HPP