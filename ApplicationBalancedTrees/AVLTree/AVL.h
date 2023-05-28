//
// Created by ezequ on 07/05/2023.
//

#ifndef AVL_H
#define AVL_H
#include <iostream>
#include "Node.h"
#include <vector>
#include "../Person/Person.h"

template <typename N, typename D>
class avl_tree {
private:
    Node<N, D>* _root { nullptr };
    int height(Node<N, D>*);
    int balance(Node<N, D>*);
    Node<N, D>* rightRotation(Node<N, D>*);
    Node<N, D>* leftRotation(Node<N, D>*);
    Node<N, D>* _add(Node<N, D>*, N, D);
    Node<N, D>* fixup_node(Node<N, D>*, N);
    Node<N, D>* _remove(Node<N, D>*, N);
    Node<N, D>* _remove_successor(Node<N, D>*, Node<N, D>*);
    Node<N, D>* fixup_deletion(Node<N, D>*);
    void _bshow(Node<N, D>*, std::string) const;
    Node<N, D>* _clear(Node<N, D>*);
    int _size(Node<N, D>*);
    void _inorder(Node<N, D>*);
    D _searchByCPF(Node<N, D>*, N);
    void _searchByName(Node<N, D>*, N, std::vector<D>*);
    void _searchByBirthdate(Node<N, D>*, N, N, std::vector<D>*);

public:
    avl_tree() = default;
    avl_tree(const avl_tree&) = delete;
    avl_tree& operator=(const avl_tree&) = delete;
    void add(N, D);
    void remove(N);
    void bshow() const;
    void clear();
    int size();
    void inorder();
    D searchByCPF(N);
    std::vector<D>* searchByName(N);
    std::vector<D>* searchByBirthdate(N, N);

    void print(Node<N, D>*);
    ~avl_tree();
};

/**
 * avl_tree<N>::height function returns the height of node.
 * @param node
 * @return node height
 */
template <typename N, typename  D>
int avl_tree<N, D>::height(Node<N, D> *node) {
    return (node == nullptr) ? 0 : node->height;
}

/**
 * avl_tree<N>::balance function calculates the balancing factor of node.
 * @param node
 * @return node balancing factor
 */
template <typename N, typename  D>
int avl_tree<N, D>::balance(Node<N, D> *node) {
    return height(node->right) - height(node->left);
}

/**
 * avl_tree<N, D>::rightRotation function performs the right rotation of node p
 * @param p
 * @return new root of tree previously rooted in p
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::rightRotation(Node<N, D> *p) {
    Node<N, D>* u = p->left;
    p->left = u->right;
    u->right = p;

    // update the height of the nodes
    p->height = 1 + std::max(height(p->left), height(p->right));
    u->height = 1 + std::max(height(u->left), height(u->right));
    return u;   // new root
}

/**
 * avl_tree<N, D>::leftRotation function performs the left rotation of node p
 * @param p
 * @return new root of tree previously rooted in p
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::leftRotation(Node<N, D> *p) {
    Node<N, D>* u = p->right;
    p->right = u->left;
    u->left = p;

    // update the height of the nodes
    p->height = 1 + std::max(height(p->left), height(p->right));
    u->height = 1 + std::max(height(u->left), height(u->right));
    return u;   // new root
}

/**
 * avl_tree<N, D>::add function adds a key to the tree
 * along with its respective data.
 * @param key
 * @param data
 */
template <typename N, typename  D>
void avl_tree<N, D>::add(N key, D data) {
    _root = _add(_root, key, data);
}

/**
 * private helper function avl_tree<N, D>::_add adds key to the tree
 * rooted at node p, along with its corresponding data.
 * @param p
 * @param key
 * @param data
 * @return a new node with key key if key is not in
 * the tree or the node whose key is key, otherwise.
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::_add(Node<N, D> *p, N key, D data) {
    if (p == nullptr)   // empty subtree
        return new Node(key, data, 1);
    if (key < p->key)
        p->left = _add(p->left, key, data);
    else
        p->right = _add(p->right, key, data);
    p = fixup_node(p, key); // regulates the p node
    return p;
}

/**
 * function avl_tree<N, D>::fixup_node adjusts node p if it is unbalanced.
 * @param p
 * @param key
 * @return the regulated p node
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::fixup_node(Node<N, D> *p, N key) {
    // updates the height of the p node
    p->height = 1 + std::max(height(p->left), height(p->right));
    // getting the balance of p node
    int bal = balance(p);

    if (bal < -1 && key < p->left->key)             // Case 1(a): right rotation
        return rightRotation(p);
    else if (bal < -1 && key > p->left->key) {      // Case 1(b): double right rotation
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    else if (bal > 1 && key >= p->right->key)        // Case 2(a): left rotation
        return leftRotation(p);
    else if (bal > 1 && key <= p->right->key) {      // Case 2(b): double left rotation
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }
    return p;
}

/**
 * avl_tree<N, D>::remove function removes the key from the tree.
 * @param key
 */
template <typename N, typename  D>
void avl_tree<N, D>::remove(N key) {
    _root = _remove(_root, key);
}

/**
 * private helper function avl_tree<N, D>::remove removes the key from the tree
 * rooted at node.
 * @param key
 * @param node
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::_remove(Node<N, D> *node, N key) {
    if (node == nullptr)    // node not exists
        return nullptr;
    if (key < node->key)
        node->left = _remove(node->left, key);
    else if (key > node->key)
        node->right = _remove(node->right, key);
        // node found
    else if (node->right == nullptr) {  // no right child
        Node<N, D>* child = node->left;
        delete node;
        return child;
    }
    else    // has a right child: exchange for the successor
        node->right = _remove_successor(node, node->right);

    // update height of node and regulates node
    node = fixup_deletion(node);
    return node;
}

template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::_remove_successor(Node<N, D> *root, Node<N, D> *node) {
    if (node->left != nullptr)
        node->left = _remove_successor(root, node->left);
    else {
        root->key = node->key;
        Node<N, D>* aux = node->right;
        delete node;
        return aux;
    }
    // update height of node and regulates node
    node = fixup_deletion(node);
    return node;
}

template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::fixup_deletion(Node<N, D> *node) {
    node->height = 1 + std::max(height(node->left), height(node->right));

    int bal = balance(node);

    // node may be out of order, there are 4 cases to consider
    if (bal > 1 && balance(node->right) >= 0)
        return leftRotation(node);
    else if (bal > 1 && balance(node->right) < 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    else if (bal < -1 && balance(node->left) <= 0)
        return rightRotation(node);
    else if (bal < -1 && balance(node->left) > 0) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    return node;
}

template <typename N, typename  D>
D avl_tree<N, D>::searchByCPF(N key) {
    return _searchByCPF(_root, key);
}

template <typename N, typename  D>
D avl_tree<N, D>::_searchByCPF(Node<N, D> *node, N key) {
    if (node == nullptr)
        return nullptr;
    else if (node->key == key)
        return node->data;
    else if (key > node->key)
        return _searchByCPF(node->right, key);
    else
        return _searchByCPF(node->left, key);
}

template <typename N, typename  D>
std::vector<D> *avl_tree<N, D>::searchByName(N key) {
    std::vector<D>* people = new std::vector<D>;
    _searchByName(_root, key, people);
    return people;
}

// Auxiliare functions
bool isPrefix(const std::string& str, const std::string& prefix) {
    if (prefix.length() > str.length())
        return false;
    return str.compare(0, prefix.length(), prefix) == 0;
}

std::string toLowerCase(const std::string& str) {
    std::string lowercaseStr = str;
    for (char& c : lowercaseStr)
        c = std::tolower(c);
    return lowercaseStr;
}

template <typename N, typename  D>
void avl_tree<N, D>::_searchByName(Node<N, D> *node, N key, std::vector<D>* people) {
    if (node == nullptr)
        return;
    else if (isPrefix(toLowerCase(node->key), toLowerCase(key))) {    // prefix or equal
        people->push_back(node->data);
        _searchByName(node->left, key, people);
        _searchByName(node->right, key, people);
    }
    else if (toLowerCase(key) < toLowerCase(node->key)) {
        _searchByName(node->left, key, people);
    }
    else
        _searchByName(node->right, key, people);
}

template <typename N, typename  D>
std::vector<D> *avl_tree<N, D>::searchByBirthdate(N startDate, N endDate) {
    std::vector<D>* people = new std::vector<D>;
    _searchByBirthdate(_root, startDate, endDate, people);
    return people;
}

template <typename N, typename  D>
void avl_tree<N, D>::_searchByBirthdate(Node<N, D> *node, N startDate, N endDate, std::vector<D> *people) {
    if (node == nullptr)
        return;
    else if (node->key >= startDate && node->key <= endDate) {    //
        people->push_back(node->data);
        _searchByBirthdate(node->left, startDate, endDate, people);
        _searchByBirthdate(node->right, startDate, endDate, people);
    }
    else if (node->key < startDate) {
        _searchByBirthdate(node->right, startDate, endDate, people);
    }
    else
        _searchByBirthdate(node->left, startDate, endDate, people);
}


/**
 * public function avl_tree<N, D>::clear clears all tree nodes
 */
template <typename N, typename  D>
void avl_tree<N, D>::clear() {
    _root = _clear(_root);
}

/**
 * private helper function avl_tree<N, D>::_clear clears all tree.
 * @param node
 * @return nullptr
 */
template <typename N, typename  D>
Node<N, D> *avl_tree<N, D>::_clear(Node<N, D> *node) {
    if (node != nullptr) {
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
}

/**
 * function avl_tree<N, D>::~avl_tree frees the tree from memory.
 */
template <typename N, typename  D>
avl_tree<N, D>::~avl_tree() {
    clear();
}

/**
 * avl_tree<N, D>::bshow function prints the tree in a friendly format.
 */
template <typename N, typename  D>
void avl_tree<N, D>::bshow() const {
    _bshow(_root, "");
}

/**
 * private helper function avl_tree<N, D>::bshow prints the tree in a friendly format.
 * @param node
 * @param inheritance
 */
template <typename N, typename  D>
void avl_tree<N, D>::_bshow(Node<N, D> *node, std::string inheritance) const {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->right , inheritance + "r");
    for(int i = 0; i < (int) inheritance.size() - 1; i++)
        std::cout << (inheritance[i] != inheritance[i + 1] ? "│   " : "    ");
    if(inheritance != "")
        std::cout << (inheritance.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        _bshow(node->left, inheritance + "l");
}

template <typename N, typename  D>
void avl_tree<N, D>::print(Node<N, D> *node) {
    std::cout << *(node->data) << std::endl;
}

template <typename N, typename  D>
int avl_tree<N, D>::size() {
    return _size(_root);
}

template <typename N, typename  D>
int avl_tree<N, D>::_size(Node<N, D> *node) {
    if (node == nullptr)
        return 0;
    return 1 + _size(node->left) + _size(node->right);
}

template <typename N, typename  D>
void avl_tree<N, D>::inorder() {
    _inorder(_root);
//    std::cout << std::endl;
}

template <typename N, typename  D>
void avl_tree<N, D>::_inorder(Node<N, D> *node) {
    if (node != nullptr) {
        _inorder(node->left);
        std::cout << node->key << " ";
        _inorder(node->right);
    }
}


#endif // AVL_H
