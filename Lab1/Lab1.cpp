#include <iostream>
#include <vector>
#include <fstream>
#include "Truba.h"
#include "utils.h"
#include <chrono>
#include <format>
#include "CS.h"
#include <unordered_map>

using namespace std;
//using namespace chrono;

//ofstream logFile;

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

CS LoadCS(ifstream& fin) // поток ввода в файл
{
    CS s;
    fin >> s.name;
    fin >> s.workshops;
    fin >> s.work_workshops;
    fin >> s.effective;
    return s;
}

void SaveCS(ofstream& fout, const CS& s) // const - константные данные, данные не меняются
{
    fout << s.name << endl << s.workshops << endl
         << s.work_workshops << endl << s.effective 
         << endl;
    
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
        << "7. Find pipe by repair status" << endl
        << "8. Input Compression Station" << endl
        << "9. Print CS" << endl
        << "10. Save CS" << endl
        << "11. Load CS" << endl
        << "12. Edit CS" << endl
        << "13. Find CS by name" << endl
        << "14 Find CS by % of not work" << endl
        << "15. Delete Truba" << endl
        << "16. Delete CS" << endl
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
        string action = "Edited repair status of pipe: " + t.name;
        //LogAction(action);
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
            string action = "Edited workshops of CS: " + s.name;
            //LogAction(action);
        }
        case 2:
        {
            int n;
            cout << "Add the number of redusing workshops: ";
            cin >> n;
            s.work_workshops -= n;
            s.work_workshops = IsWorkshopsCorrect(s.work_workshops) ? s.work_workshops : 0;
            break;
            string action = "Edited workshops of CS: " + s.name;
            //LogAction(action);
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

Truba& SelectTruba(vector<Truba>& g)
{
    cout << "Enter index of Pipe: ";
    unsigned int index = GetCorrectNumber<uint64_t>(1, g.size());
    return g[index - 1];
}

template <typename T>
using Filter = bool(*)(const Truba& t, T param);

bool CheckByName(const Truba& t, string param)
{
    cout << "Add the name of Pipe:";
    cin >> param;
    return t.name == param;
}

bool CheckByRepair(const Truba& t, bool param)
{
    return t.repair == param;
}

CS& SelectCS(vector<CS>& k)
{
    cout << "Enter index of CS: ";
    unsigned int index = GetCorrectNumber<uint64_t>(1, k.size());
    return k[index - 1];
}

template <typename T>
using Filter1 = bool(*)(const CS& s, T param);

bool CheckByName(const CS& s, string param)
{
    cout << "Add the name of CS:";
    cin >> param;
    return s.name == param;
}

bool CheckByEffective(const CS& s, double param)
{
    cout << "Add the number of working workshops:";
    cin >> param;
    return (s.workshops / param) * 100;
}

template <typename T>
unordered_map<int, int> FindCSByFilter(const unordered_map<int,CS>& group1, Filter1<T> f, T param)
{
    vector<int> res;
    int i = 0;
    for (auto& [id,s] : group1)
    {
        if (f(s, param))
            res[i] = i;
        i++;
    }
    return res;
}

template <typename T>
unordered_map<int, int> FindTrubaByFilter(const unordered_map<int,Truba>& group, Filter<T> f, T param)
{
    vector<int> res;
    int i = 0;
    for (auto& [id,t] : group)
    {
        if (f(t, param))
            res[i] = i;
        i++;
    }
    return res;
}


//template <typename T>
//vector <int> FindCSByFilter(const vector<CS>& group1, Filter1 <T> f, T param)
//{
//    vector <int> res;
//    int i = 0;
//    for (auto& s : group1)
//    {
//        if (f(s, param))
//            res.push_back(i);
//        i++;
//    }
//    return res;
//}

template <typename T>
void EditPipesByFilter(unordered_map<int, Truba>& group, Filter<T> filter, T param)
{
    vector<int> indices = FindTrubaByFilter(group, filter, param);

    // Определить, нужно редактировать все найденные трубы или по выбору пользователя

    // Если нужно редактировать все найденные трубы
    for (int index : indices) {
        EditRepair(group[index]); // Редактировать трубу
    }

    // Если нужно редактировать по выбору пользователя
    for (int index : indices) {
        cout << "Do you want to edit pipe " << index + 1 << "? (Y/N): ";
        char choice;
        cin >> choice;
        if (toupper(choice) == 'Y') {
            EditRepair(group[index]); // Редактировать трубу
        }
    }
}

template <typename T>
void EditCSByFilter(map<int, CS>& group1, Filter<T> filter, T param)
{
    vector<int> indices = FindCSByFilter(group1, filter, param);

    // Определить, нужно редактировать все найденные трубы или по выбору пользователя

    // Если нужно редактировать все найденные трубы
    for (int index : indices) {
        EditWorkshops(group1[index]); // Редактировать трубу
    }

    // Если нужно редактировать по выбору пользователя
    for (int index : indices) {
        cout << "Do you want to edit CS " << index + 1 << "? (Y/N): ";
        char choice;
        cin >> choice;
        if (toupper(choice) == 'Y') {
            EditWorkshops(group1[index]); // Редактировать трубу
        }
    }
}


//template <typename T>
//void EditPipesByFilter(vector<Truba>& group, Filter<T> filter, T param)
//{
//    vector<int> indices = FindTrubaByFilter(group, filter, param);
//
//    // Определить, нужно редактировать все найденные трубы или по выбору пользователя
//
//    // Если нужно редактировать все найденные трубы
//    for (int index : indices) {
//        EditRepair(group[index]); // Редактировать трубу
//    }
//
//    // Если нужно редактировать по выбору пользователя
//    for (int index : indices) {
//        cout << "Do you want to edit pipe " << index + 1 << "? (Y/N): ";
//        char choice;
//        cin >> choice;
//        if (toupper(choice) == 'Y') {
//            EditRepair(group[index]); // Редактировать трубу
//        }
//    }
//}


//void LogAction(const string& action)
//{
//    // Получение текущей даты и времени
//    time_t now = time(nullptr);
//    struct tm timeinfo;
//    localtime_s(&timeinfo, &now);
//    char buffer[80];
//    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
//
//    // Запись действия пользователя в лог
//    if (logFile.is_open()) {
//        logFile << "[" << buffer << "] " << action << endl;
//    }
//}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

//int main() {
//    std::string filename = "data1.txt";
//
//    if (fileExists(filename)) {
//        // Файл существует, продолжаем выполнение программы
//        std::cout << "Файл существует!" << std::endl;
//
//        // Ваш код для открытия файла и чтения данных
//
//    }
//    else {
//        // Файл не существует, выводим сообщение пользователю
//        std::cout << "Файл не найден!" << std::endl;
//    }
//
//    return 0;
//}

//void DeleteTruba(vector<Truba>& group, Truba& t) {
//    auto it = find(group.begin(), group.end(), t);
//    if (it != group.end()) {
//        group.erase(it);
//        cout << "Pipe deleted successfully." << endl;
//    }
//    else {
//        cout << "Pipe not found." << endl;
//    }
//}

//void DeleteCS(vector<CS>& group1, CS& s) {
//    auto it = find(group1.begin(), group1.end(), s);
//    if (it != group1.end()) {
//        group1.erase(it);
//        cout << "Compression Station deleted successfully." << endl;
//    }
//    else {
//        cout << "Compression Station not found." << endl;
//    }
//}

void main()
{
    // Открытие файла для записи лога
    //logFile.open("log.txt");
    //if (!logFile.is_open()) {
    //    cout << "Error: Failed to open log file!" << endl;
    //    return 1; // Если не удалось открыть файл для записи лога, завершаем программу с ошибкой
    //}
   ///* redirect_output_wrapper cerr_out(cerr);
   // string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());*/
   // ofstream logfile("log_" + time);
   // if (logfile)
   // {
   //     cerr_out.redirect(logfile);
   // }


    unordered_map <int, Truba> group;
    //group.resize(1);
    unordered_map <int, CS> group1;
    //group1.resize(1);
    while (true) // бесконечный цикл 
    {
        PrintMenu();
        switch (GetCorrectNumber(0, 16))
        {
        case 1:
        {
            Truba tr;
            cin >> tr;
            group.insert({get_idPipe(),tr});
            break;
        }
        case 2:
        {
            cout << SelectTruba(group) << endl;
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

            if (fileExists("data.txt")) {
                ifstream fin;
                // Файл существует, продолжаем выполнение программы
                cout << "File is exist!" << endl;

                // Ваш код для открытия файла и чтения данных
                fin.open("data.txt", ios::in);
                if (fin.is_open())
                {
                    int count;
                    fin >> count;
                    group.reserve(count);
                    while (count--)
                    {
                        group.insert(LoadTruba(fin));
                    }
                    fin.close();
                }
            }
            else {
                // Файл не существует, выводим сообщение пользователю
                std::cout << "File didn't find!!!" << endl;
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
            //    string name;
            //    cout << "Add the name of the pipe for finding by name:";
            //    cin >> name;
            //    for (int i : FindTrubaByFilter(group, CheckByName, name))
            //        cout << group[i];
            break;
        }
        case 7:
        {
            //    bool repair;
            //    cout << "Add the status of Pipe (0 - in repair, 1 - not in repear): ";
            //    cin >> repair;
            //        for (int i : EditPipesByFilter<bool>(group, CheckByRepair, repair))
            //            cout << group[i];
            //break;
        }
        case 8:
        {
            CS cs;
            cin >> cs;
            group1.insert(cs);
            break;
        }
        case 9:
        {
            cout << SelectCS(group1) << endl;
            break;
        }
        case 10:
        {
            ifstream fin;
            string filename = "data1.txt";

            if (fileExists(filename)) {
                // Файл существует, продолжаем выполнение программы
                cout << "File is exist!" << endl;

                // Ваш код для открытия файла и чтения данных
                fin.open("data1.txt", ios::in);
                if (fin.is_open())
                {
                    int count;
                    fin >> count;
                    group1.reserve(count);
                    while (count--)
                    {
                        group1.insert(LoadCS(fin));
                    }
                    fin.close();
                }
            }
            else
                std::cout << "File didn't find!!!" << endl; // Файл не существует, выводим сообщение пользователю
            break;
        }
        case 11:
        {
            system("cls");
            ofstream fout;
            fout.open("data1.txt", ios::out);
            if (fout.good())
            {
                fout << group1.size() << endl;
                for (CS& cs : group1)
                {
                    SaveCS(fout, cs);
                }
                fout.close();
            }
            else
            {
                cout << "Error: Unable to open file for writing!" << endl;
            }
            break;
        }
        case 12:
        {
            EditWorkshops(SelectCS(group1));

            break;
        }
        //case 13:
        //{
        //    string name;
        //    cout << "Add the name of the CS for finding by name:";
        //    cin >> name;
        //    for (int i : FindCSByFilter(group1, CheckByName, name))
        //        cout << group1[i];
        //    break;
        //}
        //case 14:
        //{
        //    double effective;
        //    cout << "Add the effective % of the CS for finding by name:";
        //    cin >> effective;
        //    for (int i : FindCSByFilter<double>(group1, CheckByEffective, effective))
        //        cout << group1[i];
        //    break;

        //}
        //case 15:
        //{
        //    Truba& t;
        //    SelectTruba(group);
        //    DeleteTruba(group, t); // Удаление выбранной трубы
        //}
        //case 16:
        //{
        //    CS s = SelectCS(group1);
        //    DeleteCS(group1, s);
        //}
        case 0:
        {
            exit(0);
        }
        default:
        {
            cout << "Error statement!!!" << endl;
        }
        }  
    }
    //logFile.close();
}