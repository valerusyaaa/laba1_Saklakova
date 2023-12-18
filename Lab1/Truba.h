#pragma once
#include <string>
#include <iostream>


class Truba
{
    int id;
public:
    static int MaxID; // ����������� ���� ����� ��� ���� �������� ������
    std::string name;
    double lenght;
    double diam;
    bool repair = true;

    Truba(); //����������� �� ���������
    //Truba(std::string name);
    //Truba(const Truba& t);
    //Truba(Truba&& t);
    //~Truba(); //����������
    //std::string GetName() const;
    //void SetName(std::string);

    friend std::ostream& operator << (std::ostream& out, const Truba& t);
    friend std::istream& operator >> (std::istream& in, Truba& t);

};

