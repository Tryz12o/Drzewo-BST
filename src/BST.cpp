#include "BST.h"
#include <queue>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <limits>
#include <string>
#include <iomanip>

// ======================================
// INSERT
// ======================================
shared_ptr<BST::Node> BST::insert(shared_ptr<Node> node, int value) {
    if (!node) return make_shared<Node>(value);
    if (value < node->value) node->left = insert(node->left, value);
    else if (value > node->value) node->right = insert(node->right, value);
    return node;
}

void BST::insert(int value) { root = insert(root, value); }

// ======================================
// REMOVE
// ======================================
shared_ptr<BST::Node> BST::findMin(shared_ptr<Node> node) {
    while (node && node->left) node = node->left;
    return node;
}

shared_ptr<BST::Node> BST::remove(shared_ptr<Node> node, int value) {
    if (!node) return node;
    if (value < node->value) node->left = remove(node->left, value);
    else if (value > node->value) node->right = remove(node->right, value);
    else {
        if (!node->left) return node->right;
        if (!node->right) return node->left;
        shared_ptr<Node> temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(node->right, temp->value);
    }
    return node;
}

void BST::remove(int value) { root = remove(root, value); }

// ======================================
// CLEAR
// ======================================
void BST::clear(shared_ptr<Node>& node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    node.reset();
}

void BST::clear() { clear(root); root = nullptr; }

// ======================================
// TRAVERSALS
// ======================================
void BST::preorderList(shared_ptr<Node> node, vector<int>& out) const {
    if (!node) return;
    out.push_back(node->value);
    preorderList(node->left, out);
    preorderList(node->right, out);
}

void BST::inorderList(shared_ptr<Node> node, vector<int>& out) const {
    if (!node) return;
    inorderList(node->left, out);
    out.push_back(node->value);
    inorderList(node->right, out);
}

void BST::postorderList(shared_ptr<Node> node, vector<int>& out) const {
    if (!node) return;
    postorderList(node->left, out);
    postorderList(node->right, out);
    out.push_back(node->value);
}

vector<int> BST::inorderTraversal() const { vector<int> v; inorderList(root,v); return v; }
vector<int> BST::preorderTraversal() const { vector<int> v; preorderList(root,v); return v; }
vector<int> BST::postorderTraversal() const { vector<int> v; postorderList(root,v); return v; }

// ======================================
// FIND PATH
// ======================================
bool BST::findPath(shared_ptr<Node> node, int value, vector<int>& path) {
    if (!node) return false;
    path.push_back(node->value);
    if (node->value == value) return true;
    if ((node->left && findPath(node->left,value,path)) || (node->right && findPath(node->right,value,path))) return true;
    path.pop_back();
    return false;
}

void BST::findPath(int value) {
    vector<int> path;
    if (findPath(root,value,path)) {
        cout << "Sciezka do " << value << ": ";
        for (int v : path) cout << v << " ";
        cout << endl;
    } else cout << "Nie znaleziono elementu " << value << endl;
}

// ======================================
// SAVE/LOAD TEXT
// ======================================
void BST::saveToFile(shared_ptr<Node> node, ofstream& file) {
    if (!node) return;
    file << node->value << " ";
    saveToFile(node->left,file);
    saveToFile(node->right,file);
}

void BST::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) { cerr << "Nie mozna otworzyc pliku!\n"; return; }
    saveToFile(root,file);
    file << endl;
    cout << "Zapisano do pliku: " << filename << endl;
}

void BST::saveToFile(const string& filename, int mode, bool graphical) {
    ofstream file(filename);
    if (!file) { cerr << "Nie mozna otworzyc pliku!\n"; return; }
    if (graphical) displayGraphicalToStream(mode,file);
    else {
        vector<int> trav;
        if(mode==1) preorderList(root,trav);
        else if(mode==2) inorderList(root,trav);
        else if(mode==3) postorderList(root,trav);
        for(size_t i=0;i<trav.size();i++){ if(i) file<<" "; file<<trav[i]; }
        file<<endl;
    }
    cout << "Zapisano do pliku: " << filename << endl;
}

void BST::loadFromTextFile(const string& filename) {
    ifstream file(filename);
    if(!file){ cerr << "Nie mozna otworzyc pliku!\n"; return; }
    clear();
    int val;
    while(file >> val) insert(val);
    cout << "Wczytano drzewo z pliku: " << filename << endl;
}

// ======================================
// BINARY SERIALIZATION
// ======================================
void BST::writeBinary(shared_ptr<Node> node, ofstream& out) {
    if(!node){ int marker=-1; out.write((char*)&marker,sizeof(marker)); return; }
    out.write((char*)&node->value,sizeof(node->value));
    writeBinary(node->left,out);
    writeBinary(node->right,out);
}

void BST::serializeBinary(const string& filename) {
    ofstream out(filename, ios::binary);
    if(!out){ cerr<<"Nie mozna otworzyc pliku BIN!\n"; return; }
    writeBinary(root,out);
    cout<<"Zapisano drzewo BIN do pliku: "<<filename<<endl;
}

shared_ptr<BST::Node> BST::readBinary(ifstream& in) {
    int val;
    if(!in.read((char*)&val,sizeof(val))) return nullptr;
    if(val==-1) return nullptr;
    shared_ptr<Node> node=make_shared<Node>(val);
    node->left=readBinary(in);
    node->right=readBinary(in);
    return node;
}

void BST::deserializeBinary(const string& filename) {
    ifstream in(filename, ios::binary);
    if(!in){ cerr<<"Nie mozna otworzyc pliku BIN!\n"; return; }
    clear();
    root=readBinary(in);
    cout<<"Wczytano drzewo BIN z pliku: "<<filename<<endl;
}

// ======================================
// GRAPHICAL DISPLAY
// ======================================
void BST::displayGraphicalTree(shared_ptr<Node> node,int level,bool isLeft){
    if(!node) return;
    for(int i=0;i<level;i++) cout<<"    ";
    if(level>0) cout<<(isLeft?"/-- ":"\\-- ");
    cout<<node->value<<endl;
    displayGraphicalTree(node->left,level+1,true);
    displayGraphicalTree(node->right,level+1,false);
}

void BST::displayGraphical(int mode){ displayGraphicalToStream(mode,cout); }

void BST::displayGraphicalToStream(int mode,ostream& out){
    out<<"\n==== Drzewo graficzne ====\n";
    if(!root){ out<<"(puste drzewo)\n"; return; }

    vector<int> trav;
    if(mode==1){ out<<"Preorder: "; preorderList(root,trav);}
    else if(mode==2){ out<<"Inorder: "; inorderList(root,trav);}
    else if(mode==3){ out<<"Postorder: "; postorderList(root,trav);}
    for(int v:trav) out<<v<<" "; out<<"\n\n";
    displayGraphicalTree(root,0,false);
}

// ======================================
// ASCII PRINT
// ======================================
void BST::printAscii(shared_ptr<Node> node, string prefix, bool isLeft){
    if(!node) return;
    cout<<prefix<<(isLeft?"├── ":"└── ")<<node->value<<endl;
    printAscii(node->left,prefix+(isLeft?"│   ":"    "),true);
    printAscii(node->right,prefix+(isLeft?"│   ":"    "),false);
}

void BST::displayAscii(){ 
    cout<<"\n==== ASCII Drzewo ====\n";
    printAscii(root,"",false);
}

// ======================================
// ASCII CENTERED
// ======================================
int treeHeight(shared_ptr<BST::Node> node) {
    if (!node) return 0;
    return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

void BST::displayAsciiCentered() {
    if (!root) { cout << "(puste drzewo)\n"; return; }

    int h = treeHeight(root);
    int width = (1 << h) * 3;
    vector<string> rows(h*2);

    queue<pair<shared_ptr<Node>, pair<int,int>>> q;
    q.push({root, {width/2,0}});

    while(!q.empty()){
        auto front = q.front(); q.pop();
        shared_ptr<Node> n = front.first;
        int x = front.second.first;
        int y = front.second.second;

        string val = to_string(n->value);
        if(rows[y].size()<width) rows[y].resize(width,' ');
        for(int i=0;i<val.size() && x+i<width;i++) rows[y][x+i]=val[i];

        if(n->left){
            int childX = x - width/(2<<(y/2+1));
            int childY = y+2;
            if(rows[y+1].size()<width) rows[y+1].resize(width,' ');
            rows[y+1][childX+1]='/';
            q.push({n->left,{childX,childY}});
        }

        if(n->right){
            int childX = x + width/(2<<(y/2+1));
            int childY = y+2;
            if(rows[y+1].size()<width) rows[y+1].resize(width,' ');
            rows[y+1][childX]='\\';
            q.push({n->right,{childX,childY}});
        }
    }

    cout<<"\n==== ASCII Drzewo (wyśrodkowane) ====\n";
    for(string &r : rows){
        while(!r.empty() && r.back()==' ') r.pop_back();
        cout<<r<<endl;
    }
}
