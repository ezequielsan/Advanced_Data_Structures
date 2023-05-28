//
// Created by ezequ on 11/05/2023.
//

#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <sstream>
#include <vector>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0) {};
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
    Date& operator=(const Date& date) {
        this->day = date.day;
        this->month = date.month;
        this->year = date.year;
        return *this;
    }
    friend bool operator<(const Date& date1, const Date& date2) {
        if (date1.year != date2.year)
            return date1.year < date2.year;
        else if (date1.month != date2.month)
            return date1.month < date2.month;
        else
            return date1.day < date2.day;
    }
    friend bool operator<=(const Date& date1, const Date& date2) {
        if (date1.year != date2.year)
            return date1.year <= date2.year;
        else if (date1.month != date2.month)
            return date1.month <= date2.month;
        else
            return date1.day <= date2.day;
    }
    friend bool operator>(const Date& date1, const Date& date2) {
        if (date1.year != date2.year)
            return date1.year > date2.year;
        else if (date1.month != date2.month)
            return date1.month > date2.month;
        else
            return date1.day > date2.day;
    }
    friend bool operator>=(const Date& date1, const Date& date2) {
        if (date1.year != date2.year)
            return date1.year >= date2.year;
        else if (date1.month != date2.month)
            return date1.month >= date2.month;
        else
            return date1.day >= date2.day;
    }
    friend bool operator==(const Date& date1, const Date& date2) {
        return (date1.day == date2.day) && (date1.month == date2.month) && (date1.year == date2.year);
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << date.month << "/" << date.day << "/" << date.year;
        return os;
    }
    static Date fromString(const std::string& str) {
        int day, month, year;
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, '/'))
            tokens.push_back(token);

        month = std::stoi(tokens[0]);
        day = std::stoi(tokens[1]);
        year = std::stoi(tokens[2]);

        return Date(day, month, year);
    }

};


#endif // DATE_H
