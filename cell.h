#ifndef CELL_H
#define CELL_H
#include <vector>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob);

class Cell
{
public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv);
    Cell(int);
    explicit Cell(bool);
    explicit Cell(char);
    explicit Cell(double);
    Cell(std::string);
    Cell(const std::vector<int> init);

    operator int() const;
    operator bool() const;
    operator char() const;
    operator double() const;
    operator std::string() const;
    operator std::vector<int>() const;

    Cell& operator= (const Cell& rhv);
    Cell& operator= (Cell&& rhv);
    Cell& operator=(int x);
    Cell& operator=(bool x);
    Cell& operator=(char x);
    Cell& operator=(double x);
    Cell& operator=(std::string x);
    Cell& operator=(std::vector<int> vec);

private:
    std::string info;
};

bool operator ==(const Cell& lhv, const Cell& rhv);
bool operator !=(const Cell& lhv, const Cell& rhv);

std::ostream& operator<<(std::ostream& out, const Cell& ob);
std::istream& operator>>(std::istream& in, Cell& ob);

#endif 

