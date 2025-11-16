#pragma once
#include <string>
#include <vector>

class BST;

class FileManager {
public:
    static std::vector<int> readNumbersFromText(const std::string& path);
    static bool writeTreeToText(const std::string& path, const BST& tree);

    static bool writeTreeToBinary(const std::string& path, const BST& tree);
    static bool readTreeFromBinary(const std::string& path, BST& tree);
};
