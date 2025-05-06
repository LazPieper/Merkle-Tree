#include "../code/merkle_tree.h"

MKT::MKT() {
    // initalize pointer to root
    root = nullptr;
}

MKT::~MKT() {
    
}

mkt_node* MKT::init_node(string data) {
    // creates a new node pointer
    mkt_node* new_node = new mkt_node;
    // computes and inserts hash
    new_node->hash = sha256(data);
    // initializes each of its children as null pointers
    new_node->left = nullptr;
    new_node->right = nullptr;
    // return newly initialized node
    return new_node;
}

void MKT::insert(mkt_node* new_node) {
        // initializes parent node
    mkt_node* parent = nullptr;
    // if no root exists, the new node will become the root
    if (root == nullptr) { 
        root = new_node; 
        return;
    }
    else {
        // we need to use breadth-first search in the merkle tree to ensure we check each "level" of the tree
        // source: https://xlinux.nist.gov/dads/HTML/MerkleTree.html
        queue<mkt_node*> Q;
        // begin with root in the queue
        Q.push(root);
        // while loop to look for the new node's rightful home
        while (!Q.empty()) {
            // references the root to start; later on, it references whichever node is at the front of the queue
            mkt_node* current_node = Q.front();
            // removes it from queue so we can check the next node if this one doesn't pan out
            Q.pop();
            // checks if the left child is available
            if (current_node->left == nullptr) {
                // if so, places the new node there
                current_node->left = new_node;
                // updates parent
                parent = current_node;
                return;
            }
            // if not, adds the left child to the queue
            else { Q.push(current_node->left); }
            // checks to see if the right node is available
            if (current_node->right == nullptr) {
                // if so, places the new node there
                current_node->right = new_node;
                // updates parent
                parent = current_node;
                return;
            }
            // if not, adds the right child to queue
            else { Q.push(current_node->right); }
        }
        // updates parent node's hash to have the combined hashes of its children
        if (parent != nullptr) {
            // creates an empty string for children's hashes to be input
            string combined = "";
            // checks if there's a left child and if so, adds the left child's hash to the string
            if (parent->left) { combined += parent->left->hash; }
            // checks if there's a right child and if so, adds the right child's hash to the string
            if (parent->right) { combined += parent->right->hash; }
            // hashes the combined hashes
            parent->hash = sha256(combined);
        }
    }
}

void MKT::insert_data(string data) {
    // initializes the new node with its data
    mkt_node* new_node = init_node(data);
    // inserts the node into the merkle tree
    insert(new_node);
    return;
}

void MKT::build_tree(mkt_node* subt) {
    // checks to see if empty
     if (subt == nullptr) { 
        return;
    }
    // processes left subtree first through recursion
    build_tree(subt->left);
    // process right subtree next through recursion
    build_tree(subt->right);
    // updates the parent node after all else is updated below it
    // checks to see if parent node (subtree) has at least one child
    if (subt->left != nullptr || subt->right != nullptr) {
        string combined = "";
        if (subt->left) { combined += subt->left->hash; }
        if (subt->right) { combined += subt->right->hash; }
        subt->hash = sha256(combined);
    }
}

bool MKT::contains(mkt_node* subt, string hash) {
    // checks to see if the subtree is empty first
    if (subt == nullptr) { return false; }
    // checks to see if subtree has hash
    if (subt->hash == hash) { return true; }
    // recursively checks each of its children
    return contains(subt->left, hash) || contains(subt->right, hash);
}

int MKT::size(mkt_node* subt) {
    // if we start where there is no node, then the size is simply 0
    if (subt == nullptr) { return 0; }
    // if the initial node exists then we know there's at least 1 node
    // recursively checks children and and for each recursion, it adds 1 to the size that already exists
    return 1 + size(subt->left) + size(subt->right);
}

mkt_node* MKT::get_node(mkt_node* subt, string hash) {
    // operates similar to contains but outputs a node instead of a boolean
    if (subt == nullptr) { return nullptr; }
    if (subt->hash == hash) { return subt; }
    // can't use recursion here in the same way as boolean so have to separate left and right
    mkt_node* left_node = get_node(subt->left, hash);
    // does the same check for null
    // if it's not null, then we return the left node to recurse through the function from the top
    if (left_node != nullptr) { return left_node; }
    // same for right
    mkt_node* right_node = get_node(subt->right, hash);
    if (right_node != nullptr) { return right_node; }
    // if hash isn't found
    return nullptr;
}

mkt_node* MKT::get_root() {
    // nothing crazy
    return root;
}

void MKT::to_vector(mkt_node* subt, vector<string>&vec) {
    // uses BFS like insert()
    // checks to see if tree isn't empty
    if (subt == nullptr) { return; }
    else {
        queue<mkt_node*> Q;
        Q.push(subt);
        while (!Q.empty()) {
            mkt_node* current_node = Q.front();
            Q.pop();
            // insert hash into vector
            vec.push_back(current_node->hash);
            // business as usual with some shortcuts
            if (current_node->left != nullptr) {
                // checks if left child contains a node and if so, adds to queue
                Q.push(current_node->left);
            }
            if (current_node->right != nullptr) {
                Q.push(current_node->right);
            }
        }
    }
}
// this is NOT my implementation of SHA-256, but for the sake of the project I included it so the MKT could properly function
// source: https://terminalroot.com/how-to-generate-sha256-hash-with-cpp-and-openssl/
string MKT::sha256(const string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);

    stringstream ss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}
