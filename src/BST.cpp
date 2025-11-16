#include "BST.h"
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <limits>
#include <string>

// ======================================
// Wstawianie
// ======================================
shared_ptr<BST::Node> BST::insert(shared_ptr<Node> node, int value) {
    if (!node) return make_shared<Node>(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    return node;
}

void BST::insert(int value) {
    root = insert(root, value);
}

// ======================================
// Usuwanie
// ======================================
shared_ptr<BST::Node> BST::findMin(shared_ptr<Node> node) {
    while (node && node->left)
        node = node->left;
    return node;
}

shared_ptr<BST::Node> BST::remove(shared_ptr<Node> node, int value) {
    if (!node) return node;

    if (value < node->value)
        node->left = remove(node->left, value);
    else if (value > node->value)
        node->right = remove(node->right, value);
    else {
        if (!node->left)
            return node->right;
        if (!node->right)
            return node->left;

        shared_ptr<Node> temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(node->right, temp->value);
    }
    return node;
}

void BST::remove(int value) {
    root = remove(root, value);
}

// ======================================
// Czyszczenie
// ======================================
void BST::clear(shared_ptr<Node>& node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        node.reset();
    }
}

void BST::clear() {
    clear(root);
    root = nullptr;
}

// ======================================
// Traversale jako listy
// ======================================
void BST::preorderList(shared_ptr<Node> node, vector<int>& out) {
    if (!node) return;
    out.push_back(node->value);
    preorderList(node->left, out);
    preorderList(node->right, out);
}

void BST::inorderList(shared_ptr<Node> node, vector<int>& out) {
    if (!node) return;
    inorderList(node->left, out);
    out.push_back(node->value);
    inorderList(node->right, out);
}

void BST::postorderList(shared_ptr<Node> node, vector<int>& out) {
    if (!node) return;
    postorderList(node->left, out);
    postorderList(node->right, out);
    out.push_back(node->value);
}

// ======================================
// Znajdowanie ścieżki
// ======================================
bool BST::findPath(shared_ptr<Node> node, int value, vector<int>& path) {
    if (!node) return false;

    path.push_back(node->value);

    if (node->value == value)
        return true;

    if ((node->left && findPath(node->left, value, path)) ||
        (node->right && findPath(node->right, value, path)))
        return true;

    path.pop_back();
    return false;
}

void BST::findPath(int value) {
    vector<int> path;
    if (findPath(root, value, path)) {
        cout << "Ścieżka do " << value << ": ";
        for (int v : path) cout << v << " ";
        cout << endl;
    } else {
        cout << "Nie znaleziono elementu " << value << endl;
    }
}

// ======================================
// Zapis do pliku
// ======================================
void BST::saveToFile(shared_ptr<Node> node, ofstream& file) {
    if (!node) return;
    file << node->value << " ";
    saveToFile(node->left, file);
    saveToFile(node->right, file);
}

void BST::saveToFile(const string& filename) {
    // default: save as preorder list
    ofstream file(filename);
    if (!file) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return;
    }
    saveToFile(root, file);
    file.close();
    cout << "Zapisano do pliku: " << filename << endl;
}

void BST::saveToFile(const string& filename, int mode, bool graphical) {
    ofstream file(filename);
    if (!file) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return;
    }

    if (graphical) {
        // mode determines which traversal header to print (1-pre,2-in,3-post)
        displayGraphicalToStream(mode, file);
    } else {
        vector<int> trav;
        if (mode == 1) preorderList(root, trav);
        else if (mode == 2) inorderList(root, trav);
        else if (mode == 3) postorderList(root, trav);

        for (size_t i = 0; i < trav.size(); ++i) {
            if (i) file << " ";
            file << trav[i];
        }
        file << endl;
    }

    file.close();
    cout << "Zapisano do pliku: " << filename << endl;
}

// ======================================
// Rysowanie drzewa graficznie (top-down)
// Root is printed first, then children on subsequent indented lines
// ======================================
void BST::displayGraphicalTree(shared_ptr<Node> node, int level, bool isLeft) {
    if (!node) return;
    for (int i = 0; i < level; ++i)
        cout << "    ";

    if (level > 0)
        cout << (isLeft ? "/-- " : "\\-- ");

    cout << node->value << endl;

    displayGraphicalTree(node->left, level + 1, true);
    displayGraphicalTree(node->right, level + 1, false);
}

void BST::displayGraphical(int mode) {
    displayGraphicalToStream(mode, cout);
}

// Helper: print graphical representation to any output stream
void BST::displayGraphicalToStream(int mode, ostream& out) {
    out << "\n==== Drzewo graficzne ====" << endl;
    if (!root) {
        out << "(puste drzewo)" << endl;
        return;
    }

    vector<int> trav;
    if (mode == 1) {
        preorderList(root, trav);
        out << "Preorder: ";
    } else if (mode == 2) {
        inorderList(root, trav);
        out << "Inorder: ";
    } else if (mode == 3) {
        postorderList(root, trav);
        out << "Postorder: ";
    } else {
        out << "Traversale: ";
    }

    for (size_t i = 0; i < trav.size(); ++i) {
        if (i) out << " ";
        out << trav[i];
    }
    out << endl << endl;

    // Print tree top-down with horizontal spacing.
    unordered_map<Node*, pair<int,int>> pos; // Node* -> (x, depth)
    unordered_map<Node*, int> centerX; // Node* -> center column (for connector placement)
    int curX = 0;
    int maxDepth = 0;

    function<void(shared_ptr<Node>, int)> computePos = [&](shared_ptr<Node> n, int depth) {
        if (!n) return;
        computePos(n->left, depth + 1);
        pos[n.get()] = {curX++, depth};
        maxDepth = max(maxDepth, depth);
        computePos(n->right, depth + 1);
    };

    computePos(root, 0);

    if (pos.empty()) return;

    int spacing = 2;
    int rootCenter = 20;
    centerX[root.get()] = rootCenter;

    function<void(shared_ptr<Node>)> computeCenters = [&](shared_ptr<Node> n) {
        if (!n) return;
        int parentCenter = centerX[n.get()];
        if (n->left) {
            centerX[n->left.get()] = parentCenter - spacing;
            computeCenters(n->left);
        }
        if (n->right) {
            centerX[n->right.get()] = parentCenter + spacing;
            computeCenters(n->right);
        }
    };

    computeCenters(root);

    int minCenter = std::numeric_limits<int>::max();
    for (auto &c : centerX) minCenter = min(minCenter, c.second);
    int padding = 2;
    int shift = (minCenter < padding) ? (padding - minCenter) : 0;
    for (auto &c : centerX) c.second += shift;

    int maxCenter = 0;
    for (auto &c : centerX) maxCenter = max(maxCenter, c.second);
    int width = maxCenter + padding + 5;
    int height = maxDepth * 2 + 1;

    vector<string> rows(height, string(width, ' '));

    for (auto &p : pos) {
        Node* nptr = p.first;
        int depth = p.second.second;
        int cy = depth * 2;
        string val = to_string(nptr->value);
        int center = centerX[nptr];
        int start = center - (int)val.length() / 2;
        if (start < 0) start = 0;
        if (start + (int)val.length() >= width) {
            int extra = start + (int)val.length() - width + 1;
            for (auto &r : rows) r += string(extra, ' ');
            width += extra;
        }
        for (size_t k = 0; k < val.length(); ++k) rows[cy][start + k] = val[k];
    }

    function<void(shared_ptr<Node>)> drawConnectors = [&](shared_ptr<Node> n) {
        if (!n) return;
        Node* p = n.get();
        int py = pos[p].second * 2;
        if (n->left) {
            int cx = centerX[n->left.get()];
            int cy = py + 1;
            if (cy < height && cx >= 0 && cx < (int)rows[cy].size()) rows[cy][cx] = '/';
        }
        if (n->right) {
            int cx = centerX[n->right.get()];
            int cy = py + 1;
            if (cy < height && cx >= 0 && cx < (int)rows[cy].size()) rows[cy][cx] = '\\';
        }
        drawConnectors(n->left);
        drawConnectors(n->right);
    };

    drawConnectors(root);

    for (int r = 0; r < height; ++r) {
        string &line = rows[r];
        int end = (int)line.size() - 1;
        while (end >= 0 && line[end] == ' ') --end;
        if (end < 0) out << "\n";
        else out << line.substr(0, end + 1) << endl;
    }
}