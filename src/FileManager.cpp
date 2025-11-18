#include "FileManager.h"
#include "BST.h"
#include <fstream>
#include <iostream>

//
// ---------------------------------------------------------------
// Wczytywanie liczb z pliku tekstowego
// ---------------------------------------------------------------
//
std::vector<int> FileManager::readNumbersFromText(const std::string& path) {
    std::vector<int> numbers;
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << path << "\n";
        return numbers;
    }

    int value;
    while (file >> value) {
        numbers.push_back(value);
    }

    return numbers;
}

//
// ---------------------------------------------------------------
// Zapis drzewa do pliku tekstowego (przebieg inorder)
// ---------------------------------------------------------------
//
bool FileManager::writeTreeToText(const std::string& path, const BST& tree) {
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << path << "\n";
        return false;
    }

    // Pobieramy wartości w kolejności inorder
    std::vector<int> values = tree.inorderTraversal();

    for (int v : values) {
        file << v << " ";
    }

    return true;
}

//
// ---------------------------------------------------------------
// Zapis drzewa do pliku binarnego (przebieg preorder)
// ---------------------------------------------------------------
//
bool FileManager::writeTreeToBinary(const std::string& path, const BST& tree) {
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku binarnego do zapisu: " << path << "\n";
        return false;
    }

    // Pobieramy wartości w przebiegu preorder
    std::vector<int> preorder = tree.preorderTraversal();
    size_t size = preorder.size();

    // Najpierw zapisujemy liczbę elementów
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Zapisujemy wszystkie liczby
    for (int v : preorder) {
        file.write(reinterpret_cast<const char*>(&v), sizeof(v));
    }

    return true;
}

//
// ---------------------------------------------------------------
// Odczyt drzewa z pliku binarnego
// ---------------------------------------------------------------
//
bool FileManager::readTreeFromBinary(const std::string& path, BST& tree) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku binarnego do odczytu: " << path << "\n";
        return false;
    }

    size_t size = 0;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size == 0) {
        // Plik pusty → drzewo też będzie puste
        return true;
    }

    std::vector<int> values(size);

    // Wczytujemy wszystkie zapisane liczby
    for (size_t i = 0; i < size; i++) {
        file.read(reinterpret_cast<char*>(&values[i]), sizeof(int));
    }

    // Czyścimy obecne drzewo i odbudowujemy je na nowo
    tree.clear();

    for (int v : values) {
        tree.insert(v);
    }

    return true;
}
