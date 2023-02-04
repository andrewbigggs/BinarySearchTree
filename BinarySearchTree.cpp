//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : J, Andrew Biggs
// Version     : 2.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) : Node() {
        this->bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* getParent(Node* parent, Node* node);
    Node* removeNode(Node* parent, Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Node* Search(string bidId);
    void DisplayBid(Bid bid);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    this->preOrder(root);
}

/**
 * Insert a bid
 *
 *@param bid The bid to be inserted as a node in the tree
 */
void BinarySearchTree::Insert(Bid bid) {
    /// root pointer does not point to a node
    if (root == nullptr)
        root = new Node(bid);
    /// add the bid to the appropriate location in the tree
    else
        addNode(root, bid);
}

/**
 * Remove a bid
 *
 *@param bidId The bidId to be removed from the tree.
 */
void BinarySearchTree::Remove(string bidId) {
    Node* node = Search(bidId);
    Node* parent = getParent(root, node);
    this->removeNode(parent, node);
}

/**
 * Search for a bid
 *
 *@param bidId The bidId that will be checked against the tree's nodes' bidIds
 */
Node* BinarySearchTree::Search(string bidId) {
    /// Start searching from root node
    Node* curNode = root;
    
    while (curNode != nullptr) {
        /// If current node's bidId matches
        if (curNode->bid.bidId == bidId) {
            return curNode;
        }
        /// bidId is lesser than current node's bidId
        if (curNode->bid.bidId > bidId) {
            curNode = curNode->left;
        }
        /// bidId is greater than current node's bidId
        else
            curNode = curNode->right;
    }
    
    return nullptr;
}

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void BinarySearchTree::DisplayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param curNode Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* curNode, Bid bid) {
    /// Find the bid's spot in the Tree by recursive searching the nodes for its appropriate location
    /// Add node to left subtree
    if (curNode->bid.bidId > bid.bidId) {
        if (curNode->left == nullptr)
            curNode->left = new Node(bid);
        else
            this->addNode(curNode->left, bid);
    }
    /// Add node to right subtree
    else {
        if (curNode->right == nullptr)
            curNode->right = new Node(bid);
        else
            this->addNode(curNode->right, bid);
    }
}
/**
 * Inorder tree traversal (recursive)
 *
 *@param node Current node in tree
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    if (node->left != nullptr)
        inOrder(node->left);
        
    DisplayBid(node->bid);
    
    if (node->right != nullptr)
        inOrder(node->right);
}
/**
 * Post-order tree traversal (recursive)
 *
 *@param node Current node in tree
 */
void BinarySearchTree::postOrder(Node* node) {
    if (node == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    if (node->left != nullptr)
        postOrder(node->left);
    if (node->right != nullptr)
        postOrder(node->right);
    
    DisplayBid(node->bid);
}
/**
 * Pre-order tree traversal (recursive)
 *
 *@param node Current node in tree
 */
void BinarySearchTree::preOrder(Node* node) {
    if (node == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    
    DisplayBid(node->bid);
    
    if (node->left != nullptr)
        preOrder(node->left);
    if (node->right != nullptr)
        preOrder(node->right);
}

/**
 * Get parent node
 *
 *@param node Pointer to the node whose parent is ascertained
 */
Node* BinarySearchTree::getParent(Node* subTreeRoot, Node* node) {
    if (subTreeRoot == nullptr)
        return nullptr;
     
    if (subTreeRoot->left == node || subTreeRoot->right == node)
        return subTreeRoot;

    if (node->bid.bidId < subTreeRoot->bid.bidId)
        return getParent(subTreeRoot->left, node);
    return getParent(subTreeRoot->right, node);
}
/**
 * Removes node with bidId equal to string parameter (recursive)
 *
 *@param node The node to be deleted
 *@param parent The parent of the node to be deleted
*/
Node* BinarySearchTree::removeNode(Node* parent, Node* node) {
    /// Avoid program crash in case root node is null
    string bidId = node->bid.bidId;
    if (node == nullptr) {
        cout << endl << "Bid " << bidId << " not found." << endl;
        return node;
    }
    /// Node matches, remove node
    /// Node to be deleted has two children
    if (node->left != nullptr && node->right != nullptr) {
        Node* succNode = node->right;
        Node* successorParent = node;
        while (succNode->left != nullptr) {
            successorParent = succNode;
            succNode = succNode->left;
        }
        node->bid = succNode->bid;
        node->right = removeNode(successorParent, succNode);
    }
    /// Root node with 1 or 0 children
    else if (node == root) {
        if (node->left != nullptr)
            root = node->left;
        else
            root = node->right;
    }
    /// Internal node with left child only
    else if (node->left != nullptr) {
        /// Replace node with node's left child
        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
    }
    /// Leaf or internal node with right child only
    else {
        /// Replace node with node's right child
        if (parent->left == node)
            parent->left = node->right;
        else
            parent->right = node->right;
    }
    return nullptr;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;
    Node* node;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            cin >> bidKey;
            
            ticks = clock();
            
            node = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!node->bid.bidId.empty()) {
                bst->DisplayBid(node->bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            cin >> bidKey;
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
