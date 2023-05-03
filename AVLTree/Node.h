#ifndef NODE_H
#define NODE_H

struct Node {
    // atributos
    int key;
    int height;
    Node *left;
    Node *right;

    // Construtor
    Node (int key, int height = 1, Node *left = nullptr, Node *right = nullptr)
        : key(key), height(height), left(left), right(right)
    {
    }
};

#endif 
