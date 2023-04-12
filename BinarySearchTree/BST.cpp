#include <iostream>
#include "BST.h"
using namespace std;

/*
 * Esta funcao recebe um ponteiro para um node e libera
 * os nos da arvore enraizada nesse node. A funcao devolve
 * nullptr apos apagar a arvore enraizada em node
*/
Node* BST::_clear(Node *node) {
    if (node != nullptr) {
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = _clear(root);
}

/* 
 * Esta funcao recebe um ponteiro para node e uma key e:
 * (1) devolve nullptr caso key nao esteja na arvore;
 * (2) devolve um ponteiro para o no contendo key caso
 * contrario.
*/
Node* BST::_search(Node *node, int key) {
    if(node == nullptr || node->key == key) 
        return node;
    else if(node->key < key) 
        return _search(node->right, key);
    else 
        return _search(node->left, key);
}

bool BST::contains(int key) {
    return _search(root, key) != nullptr;
}

/*
 * Esta funcao insere o nó com chave key na arvore
 * enraizada em node , somente se a chave key nao for repetida.
 * Devolve um ponteiro para a raiz da nova árvore
 * enraizada em node.
*/
Node *_add(Node *node, int key) {
    if (node == nullptr) 
        return new Node(key, nullptr, nullptr);

    if (node->key < key)
        node->right = _add(node->right, key);
    else
        node->left = _add(node->left, key);

    return node;
}

void BST::add(int key) {
    root = _add(root, key);
}

/*
 * Recebe um ponteiro para a arvore enraizada em node e:
 *  (1) devolve o ponteiro para o no contendo o minimo ; ou
 *  (2) devolve nullptr se a arvore for vazia .
*/
Node *BST::_minimum(Node *node) {
    if (node != nullptr && node->left != nullptr) 
        return _minimum(node->left);
    else
        return node;
}

int BST::minimum() {
    if (root == nullptr) 
        throw std::runtime_error("error: empty tree");
    else 
        return _minimum(root)->key;
}

/*
 * Recebe um ponteiro para a arvore enraizada em node e:
 *  (1) devolve o ponteiro para o no contendo o minimo ; ou
 *  (2) devolve nullptr se a arvore for vazia .
*/
Node* BST::_maximum(Node *node) {
    if (node != nullptr && node->right != nullptr) 
        return _maximum(node->right);
    else 
        return node;
}

int BST::maximum() {
    if (root == nullptr)
        throw std::runtime_error("error: empty tree");
    else
        return _maximum(root)->key;
}

/*
 * Função que recebe um nó x e a raiz, node, de uma 
 * árvore e retorna o ancestral de x que é também seu 
 * sucessor
*/
Node* BST::_ancestral_sucessor(Node* x, Node* node) {
    Node* aux = root;
    Node* succ = root;

    while (aux->key != x->key) {
        if (aux->key > x->key) {
            aux = aux->left;
            if (aux->key > succ->key) 
                succ = aux;
        }
        else {
            aux = aux->right;
            if (aux->key > succ->key) 
                succ = aux;
        }
    }

    return succ->key == x->key ? nullptr : succ;
}

/* 
 * Devolve o ponteiro para o no sucessor do no x
 * passado como parametro. A funcao tambem recebe
 * como parametro a raiz da arvore (i.e node).
*/
Node* BST::_sucessor(Node* x, Node* node) {
    if (x == nullptr || node == nullptr)
        return nullptr;
    else if (x->right != nullptr) 
        return _minimum(x->right);
    else    
        return _ancestral_sucessor(x, node);
}

int BST::successor(int key) {
    Node* temp = _search(root, key);
    if (temp != nullptr) {
        Node* succ = _sucessor(temp, root);
        if (succ != nullptr)
            return succ->key;
        else 
            throw std::runtime_error("error: succesor not exists");
    }
    else
        throw std::runtime_error("error: key not exists");
}

/*
 * Função que recebe um nó x e a raiz, node, de uma 
 * árvore e retorna o ancestral de x que é também seu 
 * predecesor
*/
Node* BST::_ancestral_predecessor(Node* x, Node* node) {
    Node* aux = root;
    Node* pred = root;

    while (aux->key != x->key) {
        if (aux->key < x->key) 
            aux = aux->right;
        else 
            aux = aux->left;
        
        if (aux->key < pred->key) 
            pred = aux;
    }
    return pred->key == x->key ? nullptr : pred;
}

/* 
 * Devolve o ponteiro para o nó predecesor do nó x
 * passado como parametro. A funcao tambem recebe
 * como parametro a raiz da arvore (i.e node).
*/
Node* BST::_predecessor(Node* x, Node* node) {
    if (x == nullptr || node == nullptr)
        return nullptr;
    else if (x->left != nullptr) 
        return _maximum(x->left);
    else 
        return _ancestral_predecessor(x, node);
}

int BST::predecessor(int key) {
    Node* temp = _search(root, key);
    if (temp != nullptr) {
        Node* pred = _predecessor(temp, root);
        if (pred != nullptr) {
            return pred->key;
        }
        else 
            throw std::runtime_error("error: predecessor not exists");
    }   
    else
        throw std::runtime_error("error: key not exists");

    
    
}   

/* 
 * Recebe um ponteiro node para a raiz de uma arvore e
 * remove a raiz , rearranjando a arvore de modo que ela
 * continue sendo de busca . Devolve o endereco da nova raiz
*/
Node* BST::_removeRoot(Node *node) {
    Node *pai, *q;
    if (node->right == nullptr)
        q = node->left;
    else {
        pai = node;
        q = node->right;
        while (q->left != nullptr) {
            pai = q;
            q = q->left;
        }
        if (pai != node) {
            pai->left = q->right;
            q->right = node->right;
        }
        q->left = node->left;
    }
    delete node;
    return q;
}

Node* BST::_remove(int k, Node *node) {
    if (node == nullptr)    // Tree empty
        return nullptr;
    else if (k == node->key) // Found the node to be removed
        return _removeRoot(node);

    // We still haven't found the node
    if (k < node->key) 
        node->left = _remove(k, node->left);
    else
        node->right = _remove(k, node->right);

    return node;
}
    
/* 
 * Essa funcao recebe uma chave e remove o nó contendo
 * essa chave somente se ele existir na arvore
*/
void BST::remove(int key) {
    root = _remove(key, root);
}   

void BST::inorder() {
    _inorder(root);
}

void BST::_inorder(Node* node) {
    if (node != nullptr) {
        _inorder(node->left);
        cout << node->key << " ";
        _inorder(node->right);
    }
}