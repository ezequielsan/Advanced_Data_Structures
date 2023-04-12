#include <iostream>
#include <string>
#include <sstream>
#include "BST.h"
using namespace std;

int main() {
    BST t;
    string skeys;
    int k;
    
    cout << "Digite as chaves separadas por espacos: ";
    getline(cin, skeys);
    stringstream ss { skeys };
    
    while(ss >> k) t.add(k);

    cout << "Menor chave: " << t.minimum() << endl;
    cout << "Maior chave: " << t.maximum() << endl;

    t.inorder(); // ordem simetrica
    cout << endl;

    cout << "sucessor de 8: " << t.successor(8) << endl;
    cout << "predecesor de 10: " << t.predecessor(10) << endl;

    t.remove(3);

    t.inorder(); // ordem simetrica
    cout << endl;

    return 0;
}
