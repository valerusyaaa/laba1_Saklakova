#pragma once
#include <string>
#include <iostream>


class Truba
{
    int id;
public:
    static int MaxID; // статическое поле общее для всех объектов класса
    std::string name;
    double lenght;
    double diam;
    bool repair = true;

    Truba(); //конструктор по умолчанию
    //Truba(std::string name);
    //Truba(const Truba& t);
    //Truba(Truba&& t);
    //~Truba(); //деструктор
    //std::string GetName() const;
    //void SetName(std::string);

    friend std::ostream& operator << (std::ostream& out, const Truba& t);
    friend std::istream& operator >> (std::istream& in, Truba& t);

};

