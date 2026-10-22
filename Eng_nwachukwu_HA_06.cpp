#include <iostream>
#include <cstdlib>
#include <ctime>

#include "character.hpp"

using namespace std;

int main() {

    srand(time(nullptr));



    Character archer("Archer", 100, 10, 25);

    Character knight("Knight", 120, 15, 20);


    cout << "========================================"
         << endl;

    cout << "           CHARACTERS"
         << endl;

    cout << "========================================"
         << endl;

    cout << archer << endl;
    cout << knight << endl;

    cout << endl;


    fight(archer, knight);


    cout << endl;

    cout << "========================================"
         << endl;

    cout << "             FINAL STATE"
         << endl;

    cout << "========================================"
         << endl;

    cout << archer << endl;
    cout << knight << endl;

    return 0;
}

