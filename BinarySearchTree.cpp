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
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
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
 */
void BinarySearchTree::Insert(Bid bid) {
    /// root pointer does not point to a node
    if (root == nullptr)
        root = new Node(bid);
    /// add the bid to the appropriate location in the tree
    else
        this->addNode(root, bid);
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    /// Start searching from root node
    Node* curNode = root;
    
    while (curNode != nullptr) {
        /// If current node's bidId matches
        if (curNode->bid.bidId == bidId) {
            return curNode->bid;
        }
        /// bidId is lesser than current node's bidId
        if (curNode->bid.bidId > bidId) {
            curNode = curNode->left;
        }
        /// bidId is greater than current node's bidId
        else
            curNode = curNode->right;
    }
    
    Bid bid;
    return bid;
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
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    /// Find the bid's spot in the Tree by recursive searching the nodes for its appropriate location
    /// Add node to left subtree
    if (node->bid.bidId > bid.bidId) {
        if (node->left == nullptr)
            node->left = new Node(bid);
        else
            this->addNode(node->left, bid);
    }
    /// Add node to right subtree
    else {
        if (node->right == nullptr)
            node->right = new Node(bid);
        else
            this->addNode(node->right, bid);
    }
}

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

Node* BinarySearchTree::removeNode(Node* curNode, string bidId) {
    /// Avoid program crash in case root node is null
    if (curNode == nullptr) {
        cout << endl << "Bid " << bidId << " not found." << endl;
        return curNode;
    }
    /// Recurse left subtree
    if (curNode->bid.bidId > bidId)
        curNode->left = removeNode(curNode->left, bidId);
    /// Recurse right subtree
    else if (curNode->bid.bidId < bidId)
        curNode->right = removeNode(curNode->right, bidId);
    /// Node matches, remove node
    else {
        /// Leaf node
        if (curNode->left == nullptr && curNode->right == nullptr) {
            delete curNode;
            curNode = nullptr;
            cout << endl << "Bid " << bidId << " removed." << endl;
        }
        /// Node to be deleted has a left child
        else if (curNode->left != nullptr && curNode->right == nullptr) {
            Node* temp = curNode;
            curNode = curNode->left;
            delete temp;
            cout << endl << "Bid " << bidId << " removed." << endl;
        }
        /// Node to be deleted has a right child
        else if (curNode->left == nullptr && curNode->right != nullptr) {
            Node* temp = curNode;
            curNode = curNode->right;
            delete temp;
            cout << endl << "Bid " << bidId << " removed." << endl;
        }
        /// Node to be deleted has two children
        else {
            Node* temp = curNode->right;
            while (temp->left != nullptr)
                temp = temp->left;
            curNode->bid = temp->bid;
            curNode->right = removeNode(curNode->right, temp->bid.bidId);
        }
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

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                bst->DisplayBid(bid);
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
