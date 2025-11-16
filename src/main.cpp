#include "BST.h"

int main() {
    BST tree;
    int choice, val;
    string filename;

    do {
        cout << "\n==== MENU ====\n";
        cout << "1. Dodaj element\n";
        cout << "2. Usuń element\n";
        cout << "0. Wyjście\n";
        cout << "Wybierz: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Podaj wartość: ";
                cin >> val;
                tree.insert(val);
                break;

            case 2:
                cout << "Podaj wartość: ";
                cin >> val;
                tree.remove(val);
                break;

            case 0:
                cout << "Koniec programu.\n";
                break;

            default:
                cout << "Niepoprawny wybór.\n";
        }
    } while (choice != 0);

    return 0;
}
