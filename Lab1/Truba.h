#pragma once
#include <string>
#include <iostream>


class Truba
{
    int id;
    friend std::ostream& operator << (std::ostream& out, const Truba& t);
    friend std::istream& operator >> (std::istream& in, Truba& t);
public:
    static int MaxID; // статическое поле общее для всех объектов класса
    std::string name;
    double lenght;
    double diam;
    bool repair = true;

    Truba(); 

    int get_idPipe() const { return id; };

    

};

