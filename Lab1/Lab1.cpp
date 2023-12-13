#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Tru"
using namespace std;

struct CS 
{
    string name;
    double effective;
    int workshops;
    int work_workshops;
};

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear(); // чистим поток  
        cin.ignore(10000, '\n'); // сбрасываем данные которые уже ввели в поток  
        cout << "Type number (" << min << "-" << max << "):" << endl;
    }
    return x;
}


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
        << "6. Input Compression Station" << endl
        << "7. Print CS" << endl
        << "8. Save CS" << endl
        << "9. Load CS" << endl
        << "10. Edit CS" << endl
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
ostream& operator << (ostream& out, const Truba& t)
{
    out << "Name: " << t.name 
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
}

istream& operator >> (istream& in, CS& s)
{
    cout << "Type name of CS: ";
    in >> s.name;

    cout << "Type workshops: ";
    s.workshops = GetCorrectNumber(1, 1000000);

    cout << "Type workshops in work: ";
    s.work_workshops = GetCorrectNumber(1, s.workshops);

    cout << "Type effective score (0 - 100%):";
    s.effective = GetCorrectNumber(0.0, 100.0);

    return in;
}
istream& operator >> (istream& in, Truba& t)
{
    cout << "Add the name of pipe: ";
    in >> t.name;

    cout << "Add the lenght (up to 30000 m): ";
    t.lenght = GetCorrectNumber(0.0, 30000.0);

    cout << "Add the diam (from 114 to 1500 mm): ";
    t.diam = GetCorrectNumber(114.0, 1500.0);

    return in;
}

Truba& SelectTruba(vector<Truba>& g)
{
    cout << "Enter index of Pipe: ";
    unsigned int index = GetCorrectNumber<uint64_t>(1, g.size());
    return g[index - 1];
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
    vector <CS> group1;
    while (1) // бесконечный цикл 
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 10))
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
            for (auto& tr : group)
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
            CS cs;
            cin >> cs;
            group1.push_back(cs);
            break;
        }
        case 7:
        {
            cout << SelectCS(group1) << endl;
            break;
        }
        //case 8:
        //{
        //    cs = LoadCS();
        //    break;
        //}
        //case 9:
        //{
        //    SaveCS(cs);
        //    break;
        //}
        case 10:
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