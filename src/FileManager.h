#pragma once
#include <string>
#include <vector>

class BST;

class FileManager {
public:
    // Wczytuje liczby z pliku tekstowego (oddzielone spacjami lub enterami)
    static std::vector<int> readNumbersFromText(const std::string& path);

    // Zapisuje drzewo do pliku tekstowego (przebieg inorder)
    static bool writeTreeToText(const std::string& path, const BST& tree);

    // Zapisuje drzewo do pliku binarnego
    static bool writeTreeToBinary(const std::string& path, const BST& tree);

    // Odczytuje drzewo z pliku binarnego i odbudowuje jego strukturę
    static bool readTreeFromBinary(const std::string& path, BST& tree);
};
