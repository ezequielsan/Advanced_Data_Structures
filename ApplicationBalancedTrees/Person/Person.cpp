//
// Created by ezequ on 12/05/2023.
//

#include "Person.h"

Person::Person(const CPF &cpf, const std::string &firstName, const std::string &lastName, const Date &birthdate,
       const std::string &hometown)
        : cpf(cpf), firstName(firstName), lastName(lastName), birthdate(birthdate),  hometown(hometown) {}

const CPF &Person::getCpf() const{
    return cpf;
}

const std::string &Person::getFirstName() const {
    return firstName;
}

const std::string &Person::getLastName() const {
    return lastName;
}

const Date &Person::getBirthdate() const {
    return birthdate;
}

const std::string &Person::getHometown() const {
    return hometown;
}

