#pragma once 
#include <string> 
#include <iostream> 
#include <limits> 
#include <vector> 
#include <unordered_map> 

class redirect_output_wrapper
{
    std::streambuf* const old_buf;
    std::ostream& stream;

public:
    redirect_output_wrapper(std::ostream& src)
        : old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper()
    {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

template <typename T>
T InputNum(T start, T end)
{
    T param;
    while (!(std::cin >> param)  (std::cin.peek() != '\n')  (param < start) || (param > end))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "incorrect data, try again\n"
            << "__> ";
    }
    std::cerr << param << "\n";
    return param;