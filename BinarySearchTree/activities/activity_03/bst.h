#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
using namespace std;

/******************************
 * Definicao do struct Node
 ******************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    void preorder();  // --> Implementar
    void inorder();   // --> Implementar
    void clear();     // --> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
};

/***********************************
 * Implementacao da classe
 ***********************************/
BST::BST() {
    root = nullptr;
}
 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

BST::~BST() {
    clear();
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    if (root == nullptr) 
        root = new Node(k);
    else {
        Node* node = root;
        Node* parent = root;
        while (node != nullptr) {
            parent = node;
            if (k < node->key)
                node = node->left;
            else 
                node = node->right;
        }
        if (k > parent->key) 
            parent->right = new Node(k, nullptr, nullptr, parent);
        else 
            parent->left = new Node(k, nullptr, nullptr, parent);
    }
    return true;
}

// Funcao publica 'preorder'
// Percorre os nos da arvore em pre-ordem imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::preorder() {
    stack<Node*> stack;
    stack.push(root);
    while (stack.size() > 0) {
        Node* aux = stack.top();
        stack.pop();
        if (aux != nullptr) {
            cout << aux->key << " ";
            stack.push(aux->right);
            stack.push(aux->left);
        }
    }
}

// Funcao publica 'inorder'
// Percorre os nos da arvore em ordem simetrica imprimindo os 
// valores das chaves. Dica: use a estrutura de dados pilha (stack)
void BST::inorder() {
    stack<Node*> stack;
    Node* aux = root;
    
    while (aux != nullptr || !stack.empty()) {
        if (aux != nullptr) {
            stack.push(aux);
            aux = aux->left;
        }
        else {
            aux = stack.top();
            cout << aux->key << " ";
            aux = aux->right;
            stack.pop();
        }
    }  
}

// Funcao publica 'clear'
// Libera todos os nos da arvore deixando ela vazia.
// Dica: use a estrutura de dados pilha (stack)
void BST::clear() {
    stack<Node*> stack;
    stack.push(root);
    
    while (stack.size() > 0) {
        Node *aux = stack.top();
        stack.pop();
        if (aux != nullptr) {
            stack.push(aux->right);
            stack.push(aux->left);
            delete aux;
        }
    }
}

#endif 