#include "Station.h"
#include "utils.h"

int station::newID = 1;

std::ofstream& operator<<(std::ofstream& outf, const station& s)
{
    outf << "s\n"
        << s.get_ID() << "\n"
        << s.get_name_s() << "\n"
        << s.get_cex() << "\n"
        << s.get_workingcex() << "\n"
        << s.get_k() << "\n";

    return outf;
}

std::ifstream& operator>>(std::ifstream& fin, station& s)
{

    std::string name;
    int id;
    int cexx;
    int wcex;
    double kk;
    fin >> id;
    fin >> std::ws;
    getline(fin, name);
    fin >> cexx >> wcex >> kk;
    s.set_ID(id);
    s.set_KS(name, cexx, wcex, kk);
    return fin;
}
std::ostream& operator<<(std::ostream& out, const station& s)
{
    out << "ID " << s.get_ID() << "\n"
        << "Name KS:  " << s.get_name_s() << "\n"
        << "Number of workshops:  " << s.get_cex() << "\n"
        << "Number of workshops in work:  " << s.get_workingcex() << "\n"
        << "Ratio:  " << s.get_k() << "\n";
    return out;
}

int inputWcex(int cexx, int wcex)
{
    while ((!(std::cin >> wcex)  (std::cin.peek() != '\n'))  (wcex > cexx))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "incorrect data, input int<=" << wcex << "\n"
            << "__> ";
    }
    std::cerr << wcex << "\n";
    return wcex;
}

std::istream& operator>>(std::istream& in, station& s)
{
    std::cout << "Input name KS\n"
        << "__> ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, s.name_s);
    std::cerr << s.name_s << "\n";

    std::cout << "\nInput number of workshops\n"
        << "__> ";
    s.cex = InputNum<int>(1, 100000);

    std::cout << "Input number of workshops in work\n"
        << "__> ";
    s.workingcex = inputWcex(s.cex, s.workingcex);

    std::cout << "Input ratio\n"
        << "__> ";
    s.k = InputNum<int>(0, 100);

    return in;
}