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

    Truba(); //����������� �� ���������
    ~Truba(); //����������
    std::string GetName() const;
    void SetName(std::string);
};

