#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cmath>

const int INF = 1 << 30;
class pipe
{
private:
    int ID;
    static int newID;

    std::string name_p;
    double len;
    int d;
    bool remont;

    friend std::ostream& operator<<(std::ostream& out, const pipe& p);
    friend std::istream& operator>>(std::istream& in, pipe& p);

    friend std::ofstream& operator<<(std::ofstream& outf, const pipe& p);
    friend std::ifstream& operator>>(std::ifstream& fin, pipe& p);

public:
    pipe() : ID(newID++) {}

    [[nodiscard]] int get_ID() const { return ID; }
    [[nodiscard]] std::string get_name_p() const { return this->name_p; }
    [[nodiscard]] double get_len() const { return this->len; }
    [[nodiscard]] int get_d() const { return this->d; }
    [[nodiscard]] bool get_remont() const { return this->remont; }

    [[nodiscard]] double get_efficiency() const
    {
        return this->remont == 0 ? sqrt((pow(this->d, 5) / this->len)) : 0;
    }
    [[nodiscard]] double get_weight() const
    {
        return this->remont == 0 ? this->len : INF;//std::numeric_limits<int>::infinity();
    }


    //    void set_Pipe(std::string name_p_, double len_, int d_, bool remont_)
    //    {
    //        this->name_p = name_p_;
    //        this->len = len_;
    //        this->d = d_;
    //        this->remont = remont_;
    //    }
    void set_remont(bool remont_) { this->remont = remont_; }
    void set_ID(int ID_) { this->ID = ID_; }
    static int get_newID() { return newID; }

    void set_newID(int newID_) { this->newID = newID_; }
}