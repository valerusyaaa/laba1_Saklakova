#include "Pipe.h"
#include "utils.h"

int pipe::newID = 1;

std::ofstream& operator<<(std::ofstream& outf, const pipe& p)
{
    outf << "p\n"
        << p.get_ID() << "\n"
        << p.get_name_p() << "\n"
        << p.get_len() << "\n"
        << p.get_d() << "\n"
        << p.get_remont() << "\n";
    return outf;
}
std::ifstream& operator>>(std::ifstream& fin, pipe& p)
{
    int id;
    fin >> id;
    fin >> std::ws;
    getline(fin, p.name_p);
    fin >> p.len >> p.d >> p.remont;
    p.set_ID(id);
    //p.set_Pipe(name, len, d, remont);

    return fin;
}
std::ostream& operator<<(std::ostream& out, const pipe& p)
{
    out << "ID " << p.get_ID() << "\n"
        << "Name pipe:  " << p.get_name_p() << "\n"
        << "Length pipe:  " << p.get_len() << "\n"
        << "Diameter pipe:  " << p.get_d() << "\n"
        << "Mending:  " << p.get_remont() << "\n";
    return out;
}


std::istream& operator>>(std::istream& in, pipe& p)
{
    std::cout << "Input name pipe\n"
        << "__> ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, p.name_p);
    std::cerr << p.name_p << "\n";

    std::cout << "Input length pipe\n"
        << "__> ";
    p.len = InputNum<double>(1, 1000000000);

    std::cout << "Input diameter pipe\n"
        << "__> ";
    p.d = InputNum<int>(1, 100000);

    std::cout << "Input mending(1/0)\n"
        << "__> ";
    p.remont = InputNum<bool>(0, 1);

    return in;
}