#include "BST.h"

int main() {
    BST tree;
    int choice, val;
    string filename;

    do {
        cout << "\n==== MENU ====\n";
        cout << "1. Dodaj element\n";
        cout << "2. Usuń element\n";
        cout << "3. Usuń całe drzewo\n";
        cout << "4. Szukaj drogi do elementu\n";
        cout << "5. Wyświetl drzewo graficznie (preorder/inorder/postorder)\n";
        cout << "6. Zapisz drzewo do pliku\n";
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

            case 3:
                tree.clear();
                cout << "Drzewo usunięte.\n";
                break;

            case 4:
                cout << "Podaj wartość: ";
                cin >> val;
                tree.findPath(val);
                break;

            case 5:
                cout << "Wybierz sposób wyświetlania drzewa:\n";
                cout << "1. Preorder\n2. Inorder\n3. Postorder\nWybierz: ";
                cin >> val;
                tree.displayGraphical(val);
                break;

            case 6:
                cout << "Nazwa pliku: ";
                cin >> filename;
                tree.saveToFile(filename);
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
