//
// Created by ezequ on 08/05/2023.
//

#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <ctime>
#include <vector>
#include "../Date/Date.h"
#include "../CPF/CPF.h"

class Person {
private:
    CPF cpf;
    std::string firstName;
    std::string lastName;
    Date birthdate;
    std::string hometown;

public:
    Person(const CPF &, const std::string &, const std::string &, const Date &,
           const std::string &);
    const CPF &getCpf() const;
    const std::string &getFirstName() const;
    const std::string &getLastName() const;
    const Date &getBirthdate() const;
    const std::string &getHometown() const;
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << person.cpf << ", " << person.firstName << ", " << person.lastName << ", "
           << person.birthdate << ", " << person.hometown;
        return os;
    }
};

#endif //PERSON_H
