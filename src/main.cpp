#include "BST.h"

int main(){
    BST tree;
    int choice,val;
    string filename;

    do{
        cout<<"\n==== MENU ====\n";
        cout<<"1. Dodaj element\n";
        cout<<"2. Usun element\n";
        cout<<"3. Usun cale drzewo\n";
        cout<<"4. Szukaj drogi do elementu\n";
        cout<<"5. Wyswietl drzewo graficznie\n";
        cout<<"6. Wyswietl ASCII-drzewo\n";
        cout<<"7. Zapisz drzewo do pliku TXT\n";
        cout<<"8. Wczytaj drzewo z pliku TXT\n";
        cout<<"9. Zapisz drzewo do pliku BIN\n";
        cout<<"10. Wczytaj drzewo z pliku BIN\n";
        cout<<"11. Wyswietl ASCII-drzewo wyśrodkowane\n";
        cout<<"0. Wyjscie\n";
        cout<<"Wybierz: "; cin>>choice;

        switch(choice){
            case 1: cout<<"Podaj wartosc: "; cin>>val; tree.insert(val); break;
            case 2: cout<<"Podaj wartosc: "; cin>>val; tree.remove(val); break;
            case 3: tree.clear(); cout<<"Drzewo usuniete.\n"; break;
            case 4: cout<<"Podaj wartosc: "; cin>>val; tree.findPath(val); break;
            case 5: 
                cout<<"Wybierz tryb (1-Preorder,2-Inorder,3-Postorder): "; cin>>val;
                tree.displayGraphical(val); break;
            case 6: tree.displayAscii(); break;
            case 7:
                cout<<"Nazwa pliku TXT: "; cin>>filename;
                cout<<"Wybierz tryb (1-Preorder,2-Inorder,3-Postorder): "; cin>>val;
                tree.saveToFile(filename,val,false); break;
            case 8:
                cout<<"Nazwa pliku TXT: "; cin>>filename;
                tree.loadFromTextFile(filename); break;
            case 9:
                cout<<"Nazwa pliku BIN: "; cin>>filename;
                tree.serializeBinary(filename); break;
            case 10:
                cout<<"Nazwa pliku BIN: "; cin>>filename;
                tree.deserializeBinary(filename); break;
            case 11: tree.displayAsciiCentered(); break;
            case 0: cout<<"Koniec programu.\n"; break;
            default: cout<<"Niepoprawny wybor.\n";
        }

    }while(choice!=0);

    return 0;
}
