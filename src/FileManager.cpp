#include "FileManager.h"
#include "BST.h"
#include <fstream>
#include <iostream>

std::vector<int> FileManager::readNumbersFromText(const std::string& path) {
    std::vector<int> numbers;
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << path << "\n";
        return numbers;
    }

    int value;
    while (file >> value) {
        numbers.push_back(value);
    }

    return numbers;
}
