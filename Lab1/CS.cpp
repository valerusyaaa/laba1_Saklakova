#include "CS.h"
#include "utils.h"
using namespace std;

int CS::MaxID = 0;

CS::CS()
{
    cout << "CS::CS()" << endl;
    id = MaxID++;
    effective = 100;
    workshops = 1;
    work_workshops = 1;
    /*lenght = 100 - id;*/
    name = "Unknown";
}

ostream& operator << (ostream& out, const CS& s)
{
    out << "Name: " << s.name << endl
        << "\tWorkshops: " << s.workshops << endl
        << "\tWorkshops in work: " << s.work_workshops << endl
        << "\tEffective status (%): " << s.effective << endl;
    return out;
}

istream& operator >> (istream& in, CS& s)
{
    cout << "Type name of CS: ";
    in >> s.name;

    cout << "Type workshops: ";
    s.workshops = GetCorrectNumber(1, 1000000);

    cout << "Type workshops in work: ";
    s.work_workshops = GetCorrectNumber(1, s.workshops);

    //cout << "Type effective score (0 - 100%):";
    s.effective = static_cast<double>(s.work_workshops) / s.workshops * 100.0;

    return in;
}