#include <iostream>
#include <sstream>
#include <vector>
#include "cell.h"

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    out << "[";
    if (!vec.empty()) {
        out << vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            out << ", " << vec[i];
        }
    }
    out << "]";
    return out;
}

Cell::Cell()
    : info {""}
{}

Cell::Cell(int x)
    :info {std::to_string(x)}
{}

Cell::Cell(bool b)
    :info {b ? "true" : "false"}
{}

Cell::Cell(char ch)
    :info {ch}
{}

Cell::Cell(double x)
    :info {std::to_string(x)}
{}

Cell::Cell(std::string str)
    :info {str}
{}

Cell::Cell(const std::vector<int> init) 
{
    info = "[";
    for (auto it = init.begin(); it != init.end(); ++it) {
        info += std::to_string(*it);
        if (std::next(it) != init.end())
            info += ",";
    }
    info += "]";
}


Cell::Cell(const Cell& rhv) 
    :info {rhv.info}
{}

Cell::Cell(Cell&& rhv)
    :info {rhv.info}
{}

Cell& Cell::operator= (const Cell& rhv)
{
    if (this != &rhv) {
        info = rhv.info;
    }
    return *this;
}

Cell& Cell::operator= (Cell&& rhv)
{
    if (this != &rhv) {
        info = rhv.info;
        rhv.info = "";
    }
    return *this; 
}

Cell::operator int() const
{
    try{
        int x = std::stoi(info);
        return x;
    } catch (...) {
        return 0;
    }
    return 0;
}

Cell::operator bool() const
{
    return !info.empty();
}

Cell::operator char() const
{
    if (!info.empty()) {
        return info[0];
    } else {
        return '\0';
    }
}

Cell::operator double() const
{
    try {
        double x = std::stod(info);
        return x;
    } catch (...) {
        return 0;
    } 
    return 0;
}


Cell::operator std::string() const
{
    return info;
}

Cell::operator std::vector<int>() const
{
    std::vector<int> result;
    std::string tmp = info;
    //tmp = tmp.substr(1);
    //tmp.pop_back();
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == '[' || tmp[i] == ']' || tmp[i] == ','){
            tmp[i] = ' ';
        }
    }
    std::stringstream ss(tmp);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}

Cell& Cell::operator=(int x)
{
    info = std::to_string(x);
    return *this;
}

Cell& Cell::operator=(bool x)
{
    info = x ? "true" : "false";
    return *this;
}

Cell& Cell::operator=(char ch)
{
    info = ch;
    return *this;
}

Cell& Cell::operator=(double x)
{
    info = std::to_string(x); 
    return *this;
}

Cell& Cell::operator=(std::string str)
{
    info = str;
    return *this;
}

Cell& Cell::operator=(std::vector<int> vec)
{
    info.clear();
    info += "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        info += std::to_string(vec[i]);
        if (i < vec.size() - 1) {
            info += ",";
        }
    }
    info += "]";
    return *this;
}

bool operator ==(const Cell& c1, const Cell& c2)
{
    return (std::string(c1) == std::string(c2));
}

bool operator !=(const Cell& c1, const Cell& c2)
{
    return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& out, const Cell& rhv)
{
    out << std::string(rhv);
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) 
{
    std::string str;
    in >> str;
    ob = Cell(str); 
    return in;
}






















