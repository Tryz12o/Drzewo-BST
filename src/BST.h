#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
using namespace std;

/**
 * @class BST
 * @brief Binary Search Tree implementation with comprehensive features
 * 
 * This class implements a Binary Search Tree (BST) with support for:
 * - Insertion and deletion of nodes
 * - Tree traversal (preorder, inorder, postorder)
 * - ASCII and graphical visualization
 * - Serialization to text and binary formats
 * - File I/O operations
 */
class BST {
public: 
    /**
     * @struct Node
     * @brief Node structure for the BST
     */
    struct Node {
        int value;                          ///< Node value
        shared_ptr<Node> left;              ///< Left subtree pointer
        shared_ptr<Node> right;             ///< Right subtree pointer

        /**
         * @brief Constructor for Node
         * @param val Initial value for the node
         */
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

private:
    shared_ptr<Node> root;                  ///< Root node of the tree

    // Recursive insertion helper
    /**
     * @brief Recursive insertion helper
     * @param node Current node
     * @param value Value to insert
     * @return Updated node pointer
     */
    shared_ptr<Node> insert(shared_ptr<Node> node, int value);
    
    // Recursive removal helper
    /**
     * @brief Recursive removal helper
     * @param node Current node
     * @param value Value to remove
     * @return Updated node pointer
     */
    shared_ptr<Node> remove(shared_ptr<Node> node, int value);
    
    // Find minimum node
    /**
     * @brief Find node with minimum value in subtree
     * @param node Root of subtree
     * @return Pointer to node with minimum value
     */
    shared_ptr<Node> findMin(shared_ptr<Node> node);
    
    // Clear recursive helper
    /**
     * @brief Recursive clear helper
     * @param node Current node to clear
     */
    void clear(shared_ptr<Node>& node);

    // Traversal helpers
    /**
     * @brief Preorder traversal helper
     * @param node Current node
     * @param out Output vector
     */
    void preorderList(shared_ptr<Node> node, vector<int>& out) const;
    
    /**
     * @brief Inorder traversal helper
     * @param node Current node
     * @param out Output vector
     */
    void inorderList(shared_ptr<Node> node, vector<int>& out) const;
    
    /**
     * @brief Postorder traversal helper
     * @param node Current node
     * @param out Output vector
     */
    void postorderList(shared_ptr<Node> node, vector<int>& out) const;

    /**
     * @brief Find path to a specific value
     * @param node Current node
     * @param value Value to find
     * @param path Vector to store the path
     * @return True if value found, false otherwise
     */
    bool findPath(shared_ptr<Node> node, int value, vector<int>& path);
    
    /**
     * @brief Save tree to file in preorder format
     * @param node Current node
     * @param file Output file stream
     */
    void saveToFile(shared_ptr<Node> node, ofstream& file);
    
    /**
     * @brief Write tree to binary format
     * @param node Current node
     * @param out Output binary stream
     */
    void writeBinary(shared_ptr<Node> node, ofstream& out);
    
    /**
     * @brief Read tree from binary format
     * @param in Input binary stream
     * @return Pointer to reconstructed subtree
     */
    shared_ptr<Node> readBinary(ifstream& in);

    /**
     * @brief Display tree graphically
     * @param node Current node
     * @param level Current depth level
     * @param isLeft Whether node is left child
     */
    void displayGraphicalTree(shared_ptr<Node> node, int level, bool isLeft);
    
    /**
     * @brief Print tree in ASCII format
     * @param node Current node
     * @param prefix Prefix string for formatting
     * @param isLeft Whether node is left child
     */
    void printAscii(shared_ptr<Node> node, string prefix, bool isLeft);

public:
    /**
     * @brief Default constructor
     * Initializes an empty BST
     */
    BST() : root(nullptr) {}
    
    /**
     * @brief Destructor
     * Automatically clears all nodes
     */
    ~BST() { clear(); }

    /**
     * @brief Insert a new value into the BST
     * @param value The value to insert
     */
    void insert(int value);
    
    /**
     * @brief Remove a value from the BST
     * @param value The value to remove
     */
    void remove(int value);
    
    /**
     * @brief Clear all nodes from the BST
     */
    void clear();
    
    /**
     * @brief Find and display the path to a specific value
     * @param value The value to search for
     */
    void findPath(int value);

    /**
     * @brief Display the tree graphically in the console
     * @param mode Traversal mode (1=Preorder, 2=Inorder, 3=Postorder)
     */
    void displayGraphical(int mode);
    
    /**
     * @brief Display the tree graphically to a stream
     * @param mode Traversal mode (1=Preorder, 2=Inorder, 3=Postorder)
     * @param out Output stream
     */
    void displayGraphicalToStream(int mode, ostream& out);
    
    /**
     * @brief Display the tree in ASCII format
     */
    void displayAscii();
    
    /**
     * @brief Display the tree in ASCII format, centered
     */
    void displayAsciiCentered();

    /**
     * @brief Save tree to text file in preorder format
     * @param filename The output filename
     */
    void saveToFile(const string& filename);
    
    /**
     * @brief Save tree to file with specific format
     * @param filename The output filename
     * @param mode Traversal mode (1=Preorder, 2=Inorder, 3=Postorder)
     * @param graphical If true, saves graphical representation
     */
    void saveToFile(const string& filename, int mode, bool graphical);
    
    /**
     * @brief Load tree from text file
     * @param filename The input filename
     */
    void loadFromTextFile(const string& filename);

    /**
     * @brief Serialize tree to binary file
     * @param filename The output binary filename
     */
    void serializeBinary(const string& filename);
    
    /**
     * @brief Deserialize tree from binary file
     * @param filename The input binary filename
     */
    void deserializeBinary(const string& filename);

    /**
     * @brief Get inorder traversal of the tree
     * @return Vector containing values in inorder sequence
     */
    vector<int> inorderTraversal() const;
    
    /**
     * @brief Get preorder traversal of the tree
     * @return Vector containing values in preorder sequence
     */
    vector<int> preorderTraversal() const;
    
    /**
     * @brief Get postorder traversal of the tree
     * @return Vector containing values in postorder sequence
     */
    vector<int> postorderTraversal() const;
};

#endif
