#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
using namespace std;

class BST {
private:
    struct Node {
        int value;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    shared_ptr<Node> root;

    shared_ptr<Node> insert(shared_ptr<Node> node, int value);
    shared_ptr<Node> remove(shared_ptr<Node> node, int value);
    shared_ptr<Node> findMin(shared_ptr<Node> node);
    void clear(shared_ptr<Node>& node);

    void preorderList(shared_ptr<Node> node, vector<int>& out);
    void inorderList(shared_ptr<Node> node, vector<int>& out);
    void postorderList(shared_ptr<Node> node, vector<int>& out);

    bool findPath(shared_ptr<Node> node, int value, vector<int>& path);
    void saveToFile(shared_ptr<Node> node, ofstream& file);

    // Graficzne wyświetlanie
    void displayGraphicalTree(shared_ptr<Node> node, int level, bool isLeft);

public:
    BST() : root(nullptr) {}
    ~BST() { clear(); }

    void insert(int value);
    void remove(int value);
    void clear();
    void findPath(int value);

    void displayGraphical(int mode); // 1-pre, 2-in, 3-post
    void displayGraphicalToStream(int mode, ostream& out);

    void saveToFile(const string& filename);
    void saveToFile(const string& filename, int mode, bool graphical);
};

#endif
