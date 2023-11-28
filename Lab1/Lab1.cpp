#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//Создать консольное приложение, описывающее базовые сущности трубопроводного транспорта газа или нефти : труба и КС или НПС(в сильно упрощенном варианте).
//
//Свойства трубы : километровая отметка(название), длина, диаметр, признак "в ремонте".
//
//Свойства КС : название, количество цехов, количество цехов в работе, эффективность(некий показатель, обобщающий различные специфические характеристики)
//
//Для каждой структуры реализовать операции : считывание с консоли, вывод на консоль, редактирование признака "в ремонте" для трубы, запуск и останов цеха в КС, сохранение данных в файл, загрузка данных из файла.
//
//При запуске программы выводится меню, запрашивающее в бесконечном цикле действие от пользователя.Пример меню : 1. Добавить трубу 2. Добавить КС 3. Просмотр всех объектов 4. Редактировать трубу 5. Редактировать КС 6. Сохранить 7. Загрузить 0. Выход
//
//Поддержка русского языка не обязательна.
//
//Обязательно : проверка корректности совершаемых действий.Программа должна быть устойчива к любым действиям пользователя.
//
//Повод для снижения балла : неосмысленное наименование переменных и функций, необоснованное использование глобальных переменных, неструктурированный код.
//
//Ход выполнения работы фиксируется коммитами в github(с осмысленными комментариями).К ответу прикрепляется ссылка на финальный коммит!

//number of workshops in operation

//void toggleRepairStatus(bool* repairStatus) {
//    // Проверяем текущее значение признака "В ремонте"
//    if (*repairStatus) {
//        *repairStatus = false;  // Если труба в ремонте, устанавливаем признак "Не в ремонте"
//    }
//    else {
//        *repairStatus = true;   // Если труба не в ремонте, устанавливаем признак "В ремонте"
//    }
//}
//
//int main() {
//    bool pipeInRepair = true;
//
//    std::cout << "Текущий признак 'В ремонте': ";
//    if (pipeInRepair) {
//        std::cout << "В ремонте\n";
//    }
//    else {
//        std::cout << "Не в ремонте\n";
//    }
//
//    toggleRepairStatus(&pipeInRepair);
//
//    std::cout << "После переключения признака 'В ремонте': ";
//    if (pipeInRepair) {
//        std::cout << "В ремонте\n";
//    }
//    else {
//        std::cout << "Не в ремонте\n";
//    }
//
//    return 0;
//}


struct Truba // new data type
{
    string name;
    double lenght;
    double diam;
    bool repair = true;
};

struct CS 
{
    string name;
    double effective;
    int workshops;
    int work_workshops;
};

int GetCorrectNumber(int min, int max)
{
    int x;
    do
    {
        cin.clear(); // чистим поток
        cin.ignore(10000, '\n'); // сбрасываем данные которые уже ввели в поток
        cout << "Type number (" << min <<  "-" << max <<"):";
        cin >> x;
    } while (cin.fail() || x < min || x > max);
    return x;
}

bool IsDiamCorrect(double d)
{
    return d > 114 && d <= 1500;
}

bool IsLenghtCorrect(double d)
{
    return d > 0 && d <= 30000;
}

bool IsRepairCorrect(int d)
{
    return d == 1 || d == 2 || d == 0;
}

bool IsEffectiveCorrect(int d)
{
    return d >= 0 && d <= 100;
}

bool IsWorkshopsCorrect(int d)
{
    return d >= 0;
}

bool IsWorkshopsCorrect1(int d)
{
    return d >= 0;
}

Truba InputTruba() // создает трубу внутри функции
{
    Truba t;
    cout << "Add the name of pipe: ";
    cin.ignore(10000, '\n');
    getline(cin, t.name);

    do
    {  
        cin.clear(); // чистим поток
        cin.ignore(10000, '\n'); // сбрасываем данные которые уже ввели в поток
        cout << "Add the lenght (up to 30000 m): ";
        cin >> t.lenght;
    }
    while (cin.fail() || !IsLenghtCorrect(t.lenght));

    do
    {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        //Согласно ГОСТ 20295 (трубы стальные сварные прямошовные, а также спиральношовные трубы), диаметр магистральных труб находится в пределах 114—1420 мм.
        cout << "Add the diam (from 114 to 1500 mm): ";
        cin >> t.diam;
    }
    while (cin.fail() || !IsDiamCorrect(t.diam));

    //do
    //{
    //    cin.clear(); 
    //    cin.ignore(10000, '\n'); 
    //    cout << "Repair or not? (1 - repair, 2 - not repair, 0 - no information): ";
    //    cin >> t.repair;
    //} while (cin.fail() || !IsRepairCorrect(t.repair));

    return t;
}

Truba LoadTruba() // поток ввода в файл
{
    Truba t;
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open())
    {
        fin >> t.name;
        fin >> t.lenght;
        fin >> t.diam;
        fin >> t.repair;
        fin.close();
    }
    return t;
}

void PrintTruba(const Truba& t) // const - константные данные, данные не меняются
{
    cout << "Name: " << t.name << endl;
        cout << "Lenght: " << t.lenght
        << "\tDiam: " << t.diam
        << "\tRepair status: ";
        if (t.repair) 
        {
            cout << "Not in repearing\n";
        }
        else
        {
            cout << "In repearing\n";
        };
    //if (t.repair == 1)
    //{
    //    cout << "\tRepair status: In repearing" << endl;
    //}

    //else if (t.repair == 2)
    //{
    //    cout << "\tRepair status : Not in repearing" << endl;
    //}

    //else
    //{
    //   cout << "\tRepair status : No information" << endl;
    //};

}

void SaveTruba(const Truba& t) // const - константные данные, данные не меняются
{
    ofstream fout; // файловый поток вывода
    fout.open("data.txt", ios::out); //открываем файл на запись
    if (fout.is_open())
    {
        fout << t.name << endl <<  t.lenght << endl
            << t.diam << endl << t.repair;
        fout.close();
    }
}

CS InputCS()
{
    CS s;
    cout << "Type name of CS: ";
    getline(cin, s.name);
    /*cin >> s.name;*/
    do
    {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Type workshops: ";
        cin >> s.workshops;
    } 
    while (cin.fail());

    do
    {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Type workshops in work: ";
        cin >> s.work_workshops;
    } while (cin.fail() || s.work_workshops > s.workshops);

    do
    {
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Type effective score (1 - 100%): ";
        cin >> s.effective;
    } 
    while (cin.fail() || !IsEffectiveCorrect(s.effective));

    return s;
}

void PrintCS(const CS& s) 
{
    cout << "Name: " << s.name
        << "\tWorkshops: " << s.workshops
        << "\tWorkshops in work: " << s.work_workshops
        << "\tEffective status (%): " << s.effective << endl;
}

CS LoadCS() // поток ввода в файл
{
    CS s;
    ifstream fin;
    fin.open("data1.txt", ios::in);
    if (fin.is_open())
    {
        fin >> s.name;
        fin >> s.workshops;
        fin >> s.work_workshops;
        fin >> s.effective;

        fin.close();
    }
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
        << "0. Exit" << endl;
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

int main()
{
    Truba tr;
    CS cs;
    while (1) // бесконечный цикл 
    {
        PrintMenu();

        switch (GetCorrectNumber(0, 10))
        {
        case 1:
        {
            tr = InputTruba(); //хранение введенных данных
            break;
        }
        case 2:
        {
            PrintTruba(tr);
            break;
        }
        case 3:
        {
            SaveTruba(tr);
            break;
        }
        case 4:
        {
            tr = LoadTruba();
            break;
        }
        case 5:
        {
            EditRepair(tr);
            break;
        }
        case 6:
        {
            cs = InputCS();
            break;
        }
        case 7:
        {
            PrintCS(cs);
            break;
        }
        case 8:
        {
            cs = LoadCS();
            break;
        }
        case 9:
        {
            SaveCS(cs);
            break;
        }
        case 10:
        {
            EditWorkshops(cs);
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

//структура для ввода/вывода 
//сохранение и считывание в файл
//логичность разбиения переменных, функций, 1 функция - 1 значение, не нужно побочных эффектов,1 логически-законченная операция

//int GetCorrectNumber(int min, int max)
//{
//    int x;
//    do
//    {
//        cin.clear(); // чистим поток
//        cin.ignore(10000, '\n'); // сбрасываем данные которые уже ввели в поток
//        cout << "Type number (" << min <<  "-" << max <<"):";
//        cin >> x;
//    } while (cin.fail() || x < min || x > max);
//    return x;
//}
//
//bool IsScoreCorrect(double d)
//{
//    return d >= 2 && d <= 5;
//}
//
//struct Student // new data type
//{
//    string name;
//    double score;
//};
//
////void Hello() // вывод строки
////{
////    string s;
////    cout << "Type your name: ";
////    cin >> s;
////    cout << "Hello, " << s << endl;
////}
//// 
////void LearnMass() // работа с вектором и массивом
////{
////    int mass[5][2] = { };
////    vector <int> v;
////    size_t n = 0;
////    cin >> n;
////    v.resize(n);
////}
//
//void LearnStruct() // работа со структурами
//{
//    vector <Student> group;
//    size_t n = 0;
//    cin >> n;
//    group.resize(n);
//    //Student s = {"Ivan", 5}; // create the student Ivan with "5" score
//    //group[0] = s;
//    //s.score -= 0.5;
//    group[0] = { "Ivan", 5 };
//    group[0].score -= 0.5;
//}
//
//Student InputStudent() // создает студента внутри функции
//{
//    Student s;
//    cout << "Type name:";
//    cin >> s.name;
//    do
//    {
//        cin.clear(); // чистим поток
//        cin.ignore(10000, '\n'); // сбрасываем данные которые уже ввели в поток
//        cout << "Type score (2-5):";
//        cin >> s.score;
//    }
//    while (cin.fail() || !IsScoreCorrect(s.score));
//    return s;
//}
//
//Student LoadStudent() // поток ввода в файл
//{
//    Student s;
//    ifstream fin;
//    fin.open("data.txt", ios::in);
//    if (fin.is_open())
//    {
//        fin >> s.name;
//        fin >> s.score;
//        fin.close();
//    }
//    return s;
//}
//
//void PrintStudent(const Student& s) // const - константные данные, данные не меняются
//{
//    cout << "Name: " << s.name
//        << "\tScore: " << s.score << endl;
//}
//void SaveStudent(const Student& s) // const - константные данные, данные не меняются
//{
//    ofstream fout; // файловый поток вывода
//    fout.open("data.txt", ios::out); //открываем файл на запись
//    if (fout.is_open())
//    {
//        fout << s.name << endl <<  s.score << endl;
//        fout.close();
//    }
//    
//}
//
//void EditStudent(Student& s)
//{
//    s.score -= 0.2;
//    s.score = IsScoreCorrect(s.score) ? s.score : 2;
//}
//
//void PrintMenu()
//{
//    cout << "1. Input student" << endl
//        << "2. Print Student" << endl
//        << "3. Save to file" << endl
//        << "4. Load from file" << endl
//        << "5. Edit student" << endl
//        << "0. Edit" << endl;
//}
//int main()
//{
//    //Hello();
//    //LearnMass();
//    //LearnStruct();
//    Student st;
//    while (1) // бесконечный цикл 
//    {
//        PrintMenu();
//
//        switch (GetCorrectNumber(0, 5))
//        {
//        case 1:
//        {
//            st = InputStudent(); //хранение введенных данных в st
//            break;
//        }
//        case 2:
//        {
//            PrintStudent(st);
//            break;
//        }
//        case 3:
//        {
//            SaveStudent(st);
//            break;
//        }
//        case 4:
//        {
//            st = LoadStudent();
//            break;
//        }
//        case 5:
//        {
//            EditStudent(st);
//            break;
//        }
//        case 0:
//        {
//            return 0;
//        }
//        default:
//        {
//            cout << "Error statement!!!" << endl;
//            break;
//        }
//        }  
//    }
//    //PrintStudent(st);
//    //EditStudent(st); // для редактирования
//    //SaveStudent(st);
//    //PrintStudent(st);
//   // PrintMenu();
//    return 0;
//}