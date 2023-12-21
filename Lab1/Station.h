#pragma once
#include <string> 
#include <fstream> 
#include <iostream> 
#include <unordered_map> 

class station
{
private:
    int ID;
    static int newID;

    std::string name_s;
    int cex;
    int workingcex;
    double k;

    friend std::ostream& operator<<(std::ostream& out, const station& s);
    friend std::istream& operator>>(std::istream& in, station& s);

    friend std::ofstream& operator<<(std::ofstream& outf, const station& s);
    friend std::ifstream& operator>>(std::ifstream& fin, station& s);

public:
    station() : ID(newID++) {}

    [[nodiscard]] int get_ID() const { return ID; }
    [[nodiscard]] std::string get_name_s() const { return this->name_s; }
    [[nodiscard]] int get_cex() const { return this->cex; }
    [[nodiscard]] int get_workingcex() const { return this->workingcex; }
    [[nodiscard]] double get_k() const { return this->k; }


    void set_KS(std::string name_s_, int cex_, int workingcex_, double k_)
    {
        this->name_s = name_s_;
        this->cex = cex_;
        this->workingcex = workingcex_;
        this->k = k_;
    }
    void set_workingcex(int workingcex_) { this->workingcex = workingcex_; }
    void set_ID(int ID_) { this->ID = ID_; }
    static int get_newID() { return newID; }

    void set_newID(int newID_) { this->newID = newID_; }
};