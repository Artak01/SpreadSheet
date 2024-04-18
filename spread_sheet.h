#ifndef SPREAD_SHEET_H
#define SPREAD_SHEET_H
#include "cell.h"

class Proxy
{
public:
    explicit Proxy(Cell* p);

    Cell& operator[](size_t pos);
    const Cell& operator[](size_t pos) const;

private:
    Cell* ptr;  
};


class SpreadSheet
{
public:
    SpreadSheet();
    SpreadSheet(const SpreadSheet& rhv);
    SpreadSheet(SpreadSheet&& rhv);
    SpreadSheet(size_t size);//si
    SpreadSheet(size_t row, size_t col);//si
    ~SpreadSheet();//////////

    const SpreadSheet& operator=(const SpreadSheet& rhv);
    const SpreadSheet& operator=(SpreadSheet&& rhv);
    Proxy operator[] (size_t i);
    const Proxy operator[](size_t i) const;
    
    void clear() noexcept;//////

    void resizeRow(int new_row, int value = 0);
    void resizeCol(int new_col, int value = 0);
    void resize(int new_row, int new_col, int value = 0);
    
    size_t getRow() const;//s
    size_t getCol() const;//s

    void rotate(int x);//int
    void mirrorH();//
    void mirrorV();//
    void mirrorD();//
    void mirrorSD();//

    void removeRow(size_t ind);
    void removeCol(size_t ind);
    void removeRows(std::initializer_list<size_t> init);
    void removeCols(std::initializer_list<size_t> init);
    
    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);

private:
    size_t row;
    size_t col;
    Cell** ptr;
};

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob);
bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs);
bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs);

#endif 
