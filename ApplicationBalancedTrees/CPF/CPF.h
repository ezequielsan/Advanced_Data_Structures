//
// Created by ezequ on 15/05/2023.
//

#ifndef CPF_H
#define CPF_H
#include <iostream>
#include <string>
#include <algorithm>

class CPF {
private:
    unsigned  long long int cpf;

public:
    CPF(unsigned long long int cpf) : cpf(cpf) {}

    friend bool operator<(const CPF& cpf1, const CPF& cpf2) {
            return cpf1.cpf < cpf2.cpf;
    }
    friend bool operator<=(const CPF& cpf1, const CPF& cpf2) {
            return cpf1.cpf <= cpf2.cpf;
    }
    friend bool operator>(const CPF& cpf1, const CPF& cpf2) {
            return cpf1.cpf > cpf2.cpf;
    }
    friend bool operator>=(const CPF& cpf1, const CPF& cpf2) {
            return cpf1.cpf >= cpf2.cpf;
    }
    friend bool operator==(const CPF& cpf1, const CPF& cpf2) {
        return cpf1.cpf == cpf2.cpf;
    }
    friend std::ostream& operator<<(std::ostream& os, const CPF& cpf) {
        std::string cpf_str = std::to_string(cpf.cpf);
        cpf_str.insert(3, ".");
        cpf_str.insert(7, ".");
        cpf_str.insert(11, "-");
        os << cpf_str;
        return os;
    }

    static CPF fromString(std::string cpf) {
        unsigned long long int cpf_int;
        cpf.erase(remove(cpf.begin(), cpf.end(), '.'), cpf.end());
        cpf.erase(remove(cpf.begin(), cpf.end(), '-'), cpf.end());
        cpf_int = strtoll(cpf.c_str(), NULL, 10);
        return CPF(cpf_int);
    }

};


#endif // CPF_H
