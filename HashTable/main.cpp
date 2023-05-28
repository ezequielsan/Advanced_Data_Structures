#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Codification.h"
#include "HashTable.h"
using namespace std;

int main() 
{
    HashTable<std::string, float> ht (2, 1.0, 2.0, code_std_string);

    ht.add("atilio", 13);
    ht.add("erick", 14);
    ht.add("joana", 15);
    ht.add("joão", 1);
    ht.add("jo", 2);
    ht.add("j", 3);
    ht.add("a", 3);
    ht.add("b", 3);
    ht.add("c", 3);
    ht.add("d", 3);

    cout << boolalpha << ht.remove("ca") << endl;

    ht["atilio"] = 23;


    cout << ht.at("atilio") << endl;
    cout << ht.at("jo") << endl;
    cout << ht.at("j") << endl;

}
