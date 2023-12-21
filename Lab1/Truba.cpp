#include "Truba.h"
#include "utils.h"
using namespace std;

int Truba::MaxID = 0;

Truba::Truba()
{
	//cout << "Truba::Truba()" << endl;
    name = "Unknown";
    id = MaxID++;
	lenght = 1000-id;
    diam = 200;
    repair = false;
}

ostream& operator<<(ostream& out, const Truba& t)
{
        PRINT_PARAM(cout, t.id);
        PRINT_PARAM(cout, t.name);
        PRINT_PARAM(cout, t.lenght);
        PRINT_PARAM(cout, t.diam);
        //out << "MaxID: " << Truba::MaxID
        //    << "Id: " << t.id
        //    << "\tLenght: " << t.lenght
        //    << "\tDiam: " << t.diam
        //    << "\tRepair status: ";
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
    INPUT_LINE(in, t.name);

    cout << "Add the lenght (up to 30000 m): ";
    t.lenght = GetCorrectNumber(0.0, 30000.0);

    cout << "Add the diam (from 114 to 1500 mm): ";
    t.diam = GetCorrectNumber(114.0, 1500.0);

    return in;
}
