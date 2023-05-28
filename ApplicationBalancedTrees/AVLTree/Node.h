//
// Created by ezequ on 07/05/2023.
//

#ifndef NODE_H
#define NODE_H
#include <iostream>

template <typename T, typename R>
class Node {
private:
    T key;          // node key
    R data;         // data pointer
    int height;     // node height
    Node* left;     // left child pointer
    Node* right;    // right child pointer

public:
    // Constructor
    Node(T key, R data, int height, Node *left = nullptr, Node *right = nullptr) :
        key(key), data(data), height(height), left(left), right(right) {}

    ~Node() {
//        std::cout << key << " deleted" << std::endl;
    }

    template<typename N, typename D>
    friend class avl_tree;
};

#endif // NODE_H
