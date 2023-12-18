#include "Truba.h"
#include "utils.h"
using namespace std;

int Truba::MaxID = 0;

Truba::Truba()
{
	cout << "Truba::Truba()" << endl;
    id = MaxID++;
	lenght = 100-id;
	name = "Unknown";
}
//
//Truba::Truba(std::string name)
//{
//	this -> name = name;
//	
//}
//
//Truba::Truba(const Truba& t)
//{
//	cout << "Truba::Truba(const Truba& t)" << endl;
//}
//
//Truba::Truba(Truba&& t) // конструктор перемещения
//{
//	cout << "Truba::Truba(Truba&& t)" << endl;
//}
//
//Truba::~Truba() // освобождаем ресурсы
//{
//	cout << "Truba::~Truba()" << endl;
//}

//std::string Truba::GetName() const
//{
//	return name;
//}
//
//void Truba::SetName(std::string new_name)
//{
//	name = new_name;
//}

ostream& operator<<(std::ostream& out, const Truba& t)
{
        out << "MaxID: " << Truba::MaxID
            << "Id: " << t.id
            << "\tLenght: " << t.lenght
            << "\tDiam: " << t.diam
            << "\tRepair status: ";
        if (t.repair)
        {
            cout << "Not in repearing\n" << endl;
        }
        else
        {
            cout << "In repearing\n" << endl;
        }
        return out;
	// TODO: вставьте здесь оператор return
}

std::istream& operator>>(std::istream& in, Truba& t)
{
    cout << "Add the name of pipe: ";
    in >> t.name;

    cout << "Add the lenght (up to 30000 m): ";
    t.lenght = GetCorrectNumber(0.0, 30000.0);

    cout << "Add the diam (from 114 to 1500 mm): ";
    t.diam = GetCorrectNumber(114.0, 1500.0);

    return in;
    // TODO: вставьте здесь оператор return
}
