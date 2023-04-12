#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"

class BST { 
public:
    BST() = default;                        // Construtor default
    BST(const BST& t) = delete;             // Construtor de copia removido
    BST& operator=(const BST& t) = delete;  // Operador de atribuicao removido
    ~BST();                                 // Destrutor
    void add(int key);                      // Adicionar chave 
    void remove(int key);                   // Remover chave
    bool contains(int key);                 // A arvore contem esta chave?
    int minimum();                          // Devolve chave minima
    int maximum();                          // Devolve chave maxima
    int successor(int k);                   // Devolve chave sucessora de k
    int predecessor(int k);                 // Devolve chave antecessora de k
    void inorder();                         // Imprime as chaves em ordem simetrica

private:
    // Atributo privado
    Node *root {nullptr};

    // Funcoes-membro privadas
    Node *_search(Node *node, int key);
    Node *_clear(Node *node);
    Node *_minimum(Node *node);
    Node *_maximum(Node *node);
    Node *_ancestral_sucessor(Node *x, Node *raiz);
    Node *_ancestral_predecessor(Node *x, Node* raiz);
    Node *_sucessor(Node *x, Node *raiz);
    Node *_predecessor(Node *x, Node* raiz);
    Node *_remove(int k, Node *node);
    Node *_removeRoot(Node *node);
    void _inorder(Node *node);
};

#endif
