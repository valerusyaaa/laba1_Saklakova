#include <iostream>
#include <vector>
#include <fstream>
#include "Truba.h"
#include "utils.h"
#include <chrono>
#include <format>
#include "utils.h"

using namespace std;
using namespace chrono;

struct CS 
{
    string name;
    double effective;
    int workshops;
    int work_workshops;
};




bool IsRepairCorrect(int d)
{
    return d == 1 || d == 2 || d == 0;
}

bool IsWorkshopsCorrect(int d)
{
    return d >= 0;
}

Truba LoadTruba(ifstream& fin) // поток ввода в файл
{
    Truba t;
    fin >> t.name;
    fin >> t.lenght;
    fin >> t.diam;
    fin >> t.repair;
    return t;
}

void SaveTruba(ofstream& fout, const Truba& t) // const - константные данные, данные не меняются
{
    fout << t.name << endl <<  t.lenght << endl
            << t.diam << endl << t.repair << endl;
}

CS LoadCS() // поток ввода в файл
{
    CS s;
    ifstream fin;
    fin.open("data1.txt", ios::in);
    if (fin.is_open()) // добавить флажок
    {
        fin >> s.name;
        fin >> s.workshops;
        fin >> s.work_workshops;
        fin >> s.effective;
    }
    fin.close();
    return s;
}

void SaveCS(const CS& s) // const - константные данные, данные не меняются
{
    ofstream fout; // файловый поток вывода
    fout.open("data1.txt", ios::out); //открываем файл на запись
    if (fout.is_open())
    {
        fout << s.name << endl << s.workshops << endl
            << s.work_workshops << endl << s.effective;
        fout.close();
    }
}

void PrintMenu1()
{
    cout
        << "1. Increase the number of workshops" << endl
        << "2. Reduce the number of workshops" << endl
        << "0. Exit" << endl;
}

void PrintMenu2()
{
    cout
        << "1. Edit repair status" << endl
        << "0. Exit" << endl;
}

void PrintMenu()
{
    cout << "Menu: " << endl
        << "1. Input pipe" << endl
        << "2. Print pipe" << endl
        << "3. Save pipe" << endl
        << "4. Load pipe" << endl
        << "5. Edit pipe" << endl
        << "6. Find pipe by name" << endl
        << "7. Input Compression Station" << endl
        << "8. Print CS" << endl
        << "9. Save CS" << endl
        << "10. Load CS" << endl
        << "11. Edit CS" << endl
        << "12. Find CS by name" << endl
        << "0. Exit" << endl
        << "Choose action: " << endl;
}

void EditRepair(Truba&t)
{
        // Проверяем текущее значение признака "В ремонте"
        if (t.repair) {
            t.repair = false;  // Если труба в ремонте, устанавливаем признак "Не в ремонте"
        }
        else {
            t.repair = true;   // Если труба не в ремонте, устанавливаем признак "В ремонте"
        }
}

void EditWorkshops(CS& s)
{
    while (1)
    {
        PrintMenu1();
        switch (GetCorrectNumber(0, 2))
        {
        case 1:
        {
            int n;
            cout << "Add number of increasing workshops: ";
            cin >> n;
            s.work_workshops += n;
            s.work_workshops = s.work_workshops <= s.workshops ? s.work_workshops : s.workshops;
            break;
        }
        case 2:
        {
            int n;
            cout << "Add the number of redusing workshops: ";
            cin >> n;
            s.work_workshops -= n;
            s.work_workshops = IsWorkshopsCorrect(s.work_workshops) ? s.work_workshops : 0;
            break;
        }
        case 0:
        {
            return PrintMenu();
        }
        default:
        {
            cout << "Error statement!!!" << endl;
            break;
        }
        }
    }
}
ostream& operator << (ostream& out, const CS& s)
{
    out << "Name: " << s.name
        << "\tWorkshops: " << s.workshops
        << "\tWorkshops in work: " << s.work_workshops
        << "\tEffective status (%): " << s.effective << endl;
    return out;
}

//istream& operator >> (istream& in, CS& s)
//{
//    cout << "Type name of CS: ";
//    in >> s.name;
//
//    cout << "Type workshops: ";
//    s.workshops = GetCorrectNumber(1, 1000000);
//
//    cout << "Type workshops in work: ";
//    s.work_workshops = GetCorrectNumber(1, s.workshops);
//
//    cout << "Type effective score (0 - 100%):";
//    s.effective = GetCorrectNumber(0.0, 100.0);
//
//    return in;
//}

Truba& SelectTruba(vector<Truba>& g)
{
    cout << "Enter index of Pipe: ";
    unsigned int index = GetCorrectNumber<uint64_t>(1, g.size());
    return g[index - 1];
}

template <typename T>
using Filter = bool(*)(const Truba& t, string param);

bool CheckByName(const Truba& t, string param)
{
    return t.name == param;
}

bool CheckByLenght(const Truba& t, double param)
{
    return t.lenght >= param;
}

template <typename T>
vector <int> FindTrubaByFilter(const vector<Truba>& group, Filter <T> f, T param)
{
    vector <int> res;
    int i = 0;
    for (auto& t : group)
    {
        if (f(t, param))
            res.push_back(i);
        i++;
    }
    return res;
}



CS& SelectCS(vector<CS>& k)
{
    cout << "Enter index of CS: ";
    unsigned int index = GetCorrectNumber<uint64_t>(1, k.size());
    return k[index - 1];
}

int main()
{
    system("cls");
    vector <Truba> group;
    group.resize(3);
    vector <CS> group1;
    while (1) // бесконечный цикл 
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 12))
        {
        case 1:
        {
            Truba tr;
            cin >> tr;
            group.push_back(tr);
            break;
        }
        case 2:
        {
            for (const auto& tr : group)
                cout << tr << endl;
            break;
        }
        case 3:
        {
            system("cls");
            ofstream fout;
            fout.open("data.txt", ios::out);
            if (fout.is_open())
            {
                fout << group.size() << endl;
                for (Truba& tr : group)
                {
                    SaveTruba(fout, tr);
                }
                fout.close();
            }
            break;
        }
        case 4:
        {
            ifstream fin;
            fin.open("data.txt", ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                group.reserve(count);
                while (count--)
                {
                    group.push_back(LoadTruba(fin));
                }
                fin.close();
            }
            break;
        }
        case 5:
        {
            EditRepair(SelectTruba(group));
            break;
        }
        case 6:
        {
            string name = "Unknown";
            for (int i : FindTrubaByFilter<string>(group, CheckByName, name))
                cout << group[i];

            for (int i : FindTrubaByFilter(group, CheckByLenght, 1000.0))
                cout << group[i];
            break;
        }
        //case 7:
        //{
        //    CS cs;
        //    cin >> cs;
        //    group1.push_back(cs);
        //    break;
        //}
        //case 8:
        //{
        //    cout << SelectCS(group1) << endl;
        //    break;
        //}
        //case 9:
        //{
        //    cs = LoadCS();
        //    break;
        //}
        //case 10:
        //{
        //    SaveCS(cs);
        //    break;
        //}
        case 11:
        {
            EditWorkshops(SelectCS(group1));
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Error statement!!!" << endl;
            break;
        }
        }  
    }
    return 0;
}