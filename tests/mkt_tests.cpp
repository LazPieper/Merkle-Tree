#include "../code/merkle_tree.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // creates a merkle tree
    MKT merkle_tree;
    // set of data -- in this case, transactioons
    vector<string> transactions = {
        "0x1233252 sends 1 bitcoin to 0x456352", 
        "0x432235 sends 6 bitcoin to 0x343352", 
        "0x435634 sends 34 bitcoin to ox23453254", 
        "0x2342354 sends 43 bitcoin to 0x904375438", 
        "0x8329057 sends 905 bitcoin to 0x230954",
        "0x340543045 sends 324 bitcoin to 0x38457345",
        "0x345353454 sends 2 bitcoin to 0x7943984",
        "0x345435 sends 95646 bitcoin to 0x3454354656577"
        };
    // builds tree
    for (int i = 0 ; i < transactions.size(); i++) {
        merkle_tree.insert_data(transactions[i]);
    }
    // updates all non-leaf nodes' hashes
    merkle_tree.build_tree(merkle_tree.get_root());
    // test the other functions
    mkt_node* root = merkle_tree.get_root();
    string root_hash = merkle_tree.get_root()->hash;
    cout << root_hash << endl;
    cout << merkle_tree.contains(root, root_hash) << endl;
    cout << merkle_tree.size(root) << endl;
    vector<string> Bitcoin;
    merkle_tree.to_vector(root, Bitcoin);
    cout << "All hashes in the Bitcoin blockchain:" << endl;
    for (int i = 0; i < Bitcoin.size(); i++) {
        cout << "Hash " << i << ": " << Bitcoin[i] << " -> " << endl;
    }
    return 0;
}
