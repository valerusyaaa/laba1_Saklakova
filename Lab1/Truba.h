#pragma once
#include <string>
#include <iostream>

class Truba
{
    std::string name;
    double lenght;
    double diam;
    bool repair = true;

public:

    Truba(); //конструктор по умолчанию
    ~Truba(); //деструктор
    std::string GetName() const;
    void SetName(std::string);
};

