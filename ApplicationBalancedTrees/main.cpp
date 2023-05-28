#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "AVLTree/AVL.h"
#include "Person/Person.cpp"
#include "Date/Date.h"
#include "CPF/CPF.h"

using namespace std;

vector<Person*> read_csv() {
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file ("data.csv", ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            row.clear();

            stringstream str(line);

            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
        cout<<"Could not open the file\n";

    vector<Person*> people;

    for (int i = 1; i <= 300; i++) {
        CPF cpf = CPF::fromString(content[i][0]);
        string firstName = content[i][1];
        string lastName = content[i][2];
        Date data = Date::fromString(content[i][3]);
        string hometown = content[i][4];

        Person* person = new Person(cpf, firstName, lastName, data, hometown);
        people.push_back(person);
    }
    return people;
}

void printMenu() {
    cout << "Bem vindo ao sistema." << endl;
    cout << "Escolha uma opção e digite seu respectivo código: " << endl;

    cout << "  1. Mostrar todas as pessoas" << endl;
    cout << "  2. Pesquisar por CPF" << endl;
    cout << "  3. Pesquisar por Nome" << endl;
    cout << "  4. Pesquisar por intervalo de data" << endl;
    cout << "  5. Sair" << endl;
}

bool outputOption() {
    cin.ignore();
    string input;
    cout << "\nDigite ENTER para voltar ao menu " << endl;
    getline(cin, input);
    return input.empty() ? true : false;
}


int main() {
    // Terminal settings
    // system("chcp 65001 > nul");

    // load people
    vector<Person*> people = read_csv();

    // load data
    avl_tree<CPF, Person*> cpf_tree;
    avl_tree<string, Person*> name_tree;
    avl_tree<Date, Person*> date_tree;

    for (auto person : people) {
        cpf_tree.add(person->getCpf(), person);
        name_tree.add(person->getFirstName() + " " + person->getLastName(), person);
        date_tree.add(person->getBirthdate(), person);
    }

    while (true) {
        printMenu();
        char c{};
        cin >> c;

        if (c == '1') {
            cout << "Informação das Pessoas: " << endl;
            for (auto person : people) {
                cout << (*person) << endl;
            }

            if (outputOption()) {
                continue;
            }

        }
        else if (c == '2') {
            cout << "Informe o numero do CPF (só os numeros): \n> ";
            cin.ignore();
            string input;
            getline(cin, input);
            Person* cpfSearch = cpf_tree.searchByCPF(CPF::fromString(input));
            if (cpfSearch == nullptr) {
                cout << "CPF: " << input << " não encontrado" << endl;
            }
            else {
                cout << "\nResultados: " << endl;
                cout << (*cpfSearch) << endl;
            }

            if (outputOption()) {

                continue;
            }
        }
        else if (c == '3') {
            cout << "Informe o nome da pessoa: \n> ";
            cin.ignore();
            string input;
            getline(cin, input);
            vector<Person*>* nameSearch = name_tree.searchByName(input);
            cout << "\nResultados: " << endl;
            if (nameSearch->empty()) 
                cout << "Nenhum resultado encontrado par o nome: " << input << endl;
            else {
                for (auto person : (*nameSearch)) 
                    cout << (*person) << endl;
            }
            

            if (outputOption()) {

                continue;
            }
        }
        else if (c == '4') {
            cout << "Informe a data de inicio (formato MM/DD/AAAA): \n> ";
            string input1;
            cin >> input1;
            cin.ignore();
            cout << "Informe a data final (formato MM/DD/AAAA): \n> ";
            string input2;
            cin >> input2;
            vector<Person*>* dateSearch = date_tree.searchByBirthdate(Date::fromString(input1), Date::fromString(input2));
            if (dateSearch->empty()) 
                cout << "Nenhum resultado encontrado" << endl;
            else {
                cout << "\nResultados: " << endl;
                for (auto person : (*dateSearch)) 
                    cout << (*person) << endl;
            }
            

            if (outputOption()) {

                continue;
            }
        }
        else if (c == '5') {
            break;
        }
        else {
            cout << "Opção inválida, tente novamente" << endl;
        }
    }

    return 0;
}
