# Merkle-Tree
A C++ implementation of a merkle tree that employs Secure Hashing Algorithm 256 (SHA-256) for data integrity.

## Background
Verifying data integrity is a vital task in an increasingly in a digital world. A merkle tree serves to ensure that data is not corrupted or altered by employing a cryptographic hash function to connect every non-leaf node with its children by labeling the non-leaf node with a concatenation of the hashes of its children. This means that the root node is a hash compiled of all the previous hashes, and if the data within a node is corrupted or tampered with, it would also corrupt the chain of nodes connected to it, making any tampering immediately evident.

## How It Works
The merkle tree's header (`merkle_tree.h`) is constructed similarly to a binary-search tree such that its structure initializes a hash, as well as right and left node pointers. 

Its class contains functions for: initializing nodes, inserting nodes, inserting data, building a tree, checking if the tree contains a hash value, returning its size, getting a node, getting the root node, creating a vector of hashes, and finally a hash function (SHA-256).

SHA-256 takes any string of data and encrypts it into a hexadecimal, and is employed in the `init_node()` function upon initializing a new node.

Importantly, the `insert()` function employs a breadth-first search to insert new nodes into the tree. This allows the function to check each "level" of the tree for proper node placement, as this is vital for updating every ancestor node's hash value. After placing a new node in the tree, the function provides it with a hash value and re-hashes its parent node's hash value. This then propagates a series of re-hashes for every ancestor node along this subtree, all the way down to the root. This is done using the `build_tree()` function.

The `build_tree()` function has to take a different approach and employ a postorder traversal, because the function must begin at the leaf node and work its way up back to the root to re-hash it based on its children's new hash values. 

## Testing
The repository include a test file (`mkt_tests.cpp`) that demonstrates the different functions in the merkle tree in the following steps:
1. Creates a merkle tree with 8 sample bitcoin transactions.
2. Build the tree and updates all hashes.
3. Verifies the root hash can be found in the tree. 
4. Outputs the size of the tree.
5. Displays all hash values of the tree.

### OpenSSL Sources
The MKT includes the OpenSSL library for SHA-256.
Library source for `#include <openssl/sha.h>`: https://github.com/openssl/openssl/blob/master/crypto/sha/sha256.c
Implementation source: https://terminalroot.com/how-to-generate-sha256-hash-with-cpp-and-openssl/

### How to Build and Run Tests

#### Prerequisites
- C++11 compiler (clang++ or g++)
- OpenSSL development libraries

#### Installation on macOS
- Install Homebrew.
- Install OpenSSL using Homebrew: `brew install openssl`

#### Installation on Linux
- Install OpenSSL development libraries: `sudo apt-get install libssl-dev`

### Compiling and Running

#### macOS - Intel
```bash
clang++ -std=c++11 -o run_tests code/merkle_tree.cpp tests/mkt_tests.cpp -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto
```

#### macOS - Apple Silicon
```bash
clang++ -std=c++11 -o run_tests code/merkle_tree.cpp tests/mkt_tests.cpp -I/opt/homebrew/opt/openssl/include -L/opt/homebrew/opt/openssl/lib -lssl -lcrypto
```

#### Linux
```bash
g++ -std=c++11 -o run_tests code/merkle_tree.cpp tests/mkt_tests.cpp -lssl -lcrypto
```

#### Run the Tests
```bash
./run_tests
```
