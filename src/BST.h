#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
using namespace std;

/*
    Klasa BST (Binary Search Tree) – implementacja drzewa binarnego
    wyszukiwania z funkcjami dodawania, usuwania, czyszczenia,
    zapisu do pliku tekstowego i binarnego, wyświetlania graficznego
    i ASCII oraz generowania list traversal (pre/in/postorder).
*/

class BST {
public: // <--- Node teraz publiczny
    struct Node {
        int value;
        shared_ptr<Node> left;
        shared_ptr<Node> right;

        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

private:
    shared_ptr<Node> root;

    // Funkcje rekurencyjne
    shared_ptr<Node> insert(shared_ptr<Node> node, int value);
    shared_ptr<Node> remove(shared_ptr<Node> node, int value);
    shared_ptr<Node> findMin(shared_ptr<Node> node);
    void clear(shared_ptr<Node>& node);

    void preorderList(shared_ptr<Node> node, vector<int>& out) const;
    void inorderList(shared_ptr<Node> node, vector<int>& out) const;
    void postorderList(shared_ptr<Node> node, vector<int>& out) const;

    bool findPath(shared_ptr<Node> node, int value, vector<int>& path);
    void saveToFile(shared_ptr<Node> node, ofstream& file);
    void writeBinary(shared_ptr<Node> node, ofstream& out);
    shared_ptr<Node> readBinary(ifstream& in);

    void displayGraphicalTree(shared_ptr<Node> node, int level, bool isLeft);
    void printAscii(shared_ptr<Node> node, string prefix, bool isLeft);

public:
    BST() : root(nullptr) {}
    ~BST() { clear(); }

    void insert(int value);
    void remove(int value);
    void clear();
    void findPath(int value);

    void displayGraphical(int mode);
    void displayGraphicalToStream(int mode, ostream& out);
    void displayAscii();
    void displayAsciiCentered();

    void saveToFile(const string& filename);
    void saveToFile(const string& filename, int mode, bool graphical);
    void loadFromTextFile(const string& filename);

    void serializeBinary(const string& filename);
    void deserializeBinary(const string& filename);

    vector<int> inorderTraversal() const;
    vector<int> preorderTraversal() const;
    vector<int> postorderTraversal() const;
};

#endif
