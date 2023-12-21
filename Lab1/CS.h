#pragma once
#include <string>
#include <iostream>

class CS
{
    int id;
public:
    static int MaxID; // статическое поле общее для всех объектов класса
    std::string name;
    double effective = work_workshops/workshops;
    int workshops;
    int work_workshops;

    CS();

    friend std::ostream& operator << (std::ostream& out, const CS& s);
    friend std::istream& operator >> (std::istream& in, CS& s);

};