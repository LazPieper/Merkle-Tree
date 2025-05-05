#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
// considering the complexity of building out SHA-256, I'm using a library from OpenSSL
// source: https://github.com/openssl/openssl/blob/master/crypto/sha/sha256.c
#include <openssl/sha.h>

using namespace std;

// because a merkle tree is similar in structure as a binary tree, I'm initializing the same structure
struct mkt_node {
    // instead of data being stored as an integer in each node, we'll have the hash value as a string
    string hash;
    mkt_node* left;
    mkt_node* right;
};

class MKT {
    public:
        // constructor
        MKT();
        // destructor
        ~MKT();
        // initializes a new node with its hash value
        mkt_node* init_node(string hash);
        // inserts new node
        void insert(mkt_node* new_node);
        // creates a new node with a hash value
        void insert_data(string data);
        // uses postorder traversal to update ancestors across the tree after adding a new node (since they are hashed based on their children)
        void build_tree(mkt_node* subt);
        // checks to see if the hash value exists within the tree, starting at the subtree
        bool contains(mkt_node* subt, string hash);
        // returns the number of nodes in the tree, starting at the subtree
        int size(mkt_node* subt);
        // searches the tree and returns the node with the given hash value
        mkt_node* get_node(mkt_node* subt, string hash);
        // returns the root pointer
        mkt_node* get_root();
        // a vector containing the hash values of each node
        void to_vector(mkt_node* subt, vector<string>& vec);
        // using SHA-256 to produce the hash value
        string sha256(const string& data);

    private:
        // pointer to the root node
        mkt_node* root;
};