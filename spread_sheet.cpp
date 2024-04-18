#include <iostream>
#include <iomanip>
#include "spread_sheet.h"


SpreadSheet::SpreadSheet(size_t row, size_t col)
    :row {row}
    ,col {col}
    ,ptr {new Cell*[row]}
{
    for(int i = 0; i < row; ++i) {
        ptr[i] = new Cell[col];
    }
}


SpreadSheet::SpreadSheet()
    :SpreadSheet(2, 2)
{}

SpreadSheet::SpreadSheet(size_t size) 
    :SpreadSheet(size, size)
{}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    :row {rhv.row}
    ,col {rhv.col}
    ,ptr {new Cell*[row]}
{
    for(int i = 0; i < row; ++i) { 
        ptr[i] = new Cell[col]; 
    }
    for(int i = 0; i < row; ++i) { 
        for(int j = 0; j < col; ++j) { 
            ptr[i][j] = rhv.ptr[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
    :row {rhv.row}
    ,col {rhv.col} 
    ,ptr {rhv.ptr}
{
    rhv.ptr = nullptr;
    rhv.col = 0;
    rhv.row = 0;
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if (this != &rhv) {
        for(int i = 0; i < row; ++i){
            delete[] ptr[i];
        }
        delete[] ptr;
        row = rhv.row;
        col = rhv.col;
        ptr = new Cell*[row];
        for(int i = 0; i < row; ++i){
            ptr[i] = new Cell[col];
        }
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                ptr[i][j] = rhv.ptr[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv)
{
    if (this != &rhv) {
        for(int i = 0; i < row; ++i){
            delete[] ptr[i];
        }
        delete[] ptr;
        row = rhv.row;    
        col = rhv.col;
        ptr = rhv.ptr;
        rhv.ptr = nullptr;
    }
    return *this;
}

Proxy SpreadSheet::operator[](size_t i){
    return Proxy(ptr[i]);
}

const Proxy SpreadSheet::operator[](size_t i) const {
    return Proxy(ptr[i]);
}

Proxy::Proxy(Cell* p)
    :ptr {p}
{}

Cell& Proxy::operator[](size_t pos)
{
    return ptr[pos]; 
}


const Cell& Proxy::operator[](size_t j) const
{
    return ptr[j];
}

void SpreadSheet::clear() noexcept
{
    for(int i = 0; i < row; ++i) {
        delete[] ptr[i];
    }
    delete[] ptr;
    ptr = nullptr;
    col = 0;
    row = 0;
}

void SpreadSheet::resizeRow(int new_row, int value)
{
    int size = row + new_row;
    Cell** tmp = new Cell*[size];
    for(int i = 0; i < size; ++i){
        tmp[i] = new Cell[col];
    }
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            tmp[i][j] = ptr[i][j];
        }
    }
    for(int i = row; i < size; ++i){
        for(int j = 0; j < col; ++j){
            tmp[i][j] = value;
        }
    }
    for(int i = 0; i < row; ++i){
        delete[] ptr[i];
    }
    delete[] ptr;
    ptr = tmp;
    row = size;
    tmp = nullptr;
}

void SpreadSheet::resizeCol(int new_col, int value)
{
    int size = col + new_col;
    Cell** tmp = new Cell*[row];
    for(int i = 0; i < row; ++i){
        tmp[i] = new Cell[size];
    }
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            tmp[i][j] = ptr[i][j];
        }
    }
    for(int i = 0; i < row; ++i){
        for(int j = col; j < size; ++j){
            tmp[i][j] = value;
        }
    }
    for(int i = 0; i < row; ++i){
        delete[] ptr[i];
    }
    delete[] ptr;
    ptr = tmp;
    col = size;
    tmp = nullptr;
} 

void SpreadSheet::resize(int new_row, int new_col, int value)
{
    resizeRow(new_row, value);
    resizeCol(new_col, value);
}

size_t SpreadSheet::getRow() const
{
    return row;
}

size_t SpreadSheet::getCol() const
{
    return col;
}

void SpreadSheet::rotate(int x)
{
    bool flag = false;
    if (x < 0) {
        flag = true;
        x *= -1;
    }
    x = x % 4;
    if (x == 0) {
        return;
    }
    if (!flag) {
        for(int i = 0; i < x; ++i) {
            mirrorH();
            mirrorD();
        }
    } else {
        for(int i = 0; i < x; ++i) {  
            mirrorV();
            mirrorD();
        }
    }
}

void SpreadSheet::mirrorH()
{
    for(int i = 0; i < row / 2; ++i) { 
        for(int j = 0; j < col; ++j) {
            std::swap(ptr[i][j], ptr[row - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorV() 
{
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col / 2; ++j) {
            std::swap(ptr[i][j], ptr[i][col - j - 1]); 
        }
    }
}

void SpreadSheet::mirrorD()
{
    for(int i = 1; i < row; ++i) {
        for(int j = 0; j < i; ++j) {
            std::swap(ptr[i][j], ptr[j][i]);        
        }
    }
}

void SpreadSheet::mirrorSD()
{
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col - i; ++j) {
            std::swap(ptr[i][j], ptr[row - 1 - j][col - 1 - i]);
        }
    }
}


void SpreadSheet::removeRow(size_t ind)
{
    if (ind >= row) {
        throw std::out_of_range("Invalid index.");
    }

    ind -= 1;
    Cell** temp = new Cell*[row - 1];
    for (int i = 0, k = 0; i < row; ++i) {
        if (i == ind) {
            continue;
        }
        temp[k] = new Cell[col];
        for (int j = 0; j < col; ++j) {
            temp[k][j] = ptr[i][j];
        }
        ++k;
    }

    for (int i = 0; i < row; ++i) {
        delete[] ptr[i];
    }
    delete[] ptr;

    ptr = temp;
    --row;
}

void SpreadSheet::removeCol(size_t ind)
{
    if (ind >= col) {
        throw std::out_of_range("Invalid index.");  
    }

    ind -= 1;
    Cell** temp = new Cell*[row];
    for (int i = 0; i < row; ++i) {
        temp[i] = new Cell[col - 1];
        for (int j = 0, k = 0; j < col; ++j) {
            if (j == ind) {
                continue;
            }
            temp[i][k++] = ptr[i][j];
        }
    }

    for (int i = 0; i < row; ++i) {
        delete[] ptr[i];
    }
    delete[] ptr;

    ptr = temp;
    --col;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> init)
{
    auto it = init.end(); 
    while (it != init.begin()) {
        --it; 
        removeRow(*it); 
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> init)
{
    auto it = init.end();
    while (it != init.begin()) {
        --it;
        removeCol(*it);
    }
}


SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet slicedSheet;
    size_t numRows = rows.size();
    size_t numCols = cols.size();

    slicedSheet.row = numRows;
    slicedSheet.col = numCols;
    slicedSheet.ptr = new Cell*[numRows];

    size_t rowIndex = 0;
    for (auto row : rows) {
        size_t colIndex = 0;
        slicedSheet.ptr[rowIndex] = new Cell[numCols];
        for (auto col : cols) {
            slicedSheet.ptr[rowIndex][colIndex] = ptr[row - 1][col - 1];
            colIndex++;
        }
        rowIndex++;
    }
    return slicedSheet;    
}
/*
std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    for(int i = 0; i < ob.getRow(); ++i) {
        for(int j = 0; j < ob.getCol(); ++j) { 
            out << std::setw(8) << std::left << ob[i][j]; 
        }
        out << std::endl;
    }
    return out;
}
*/

std::ostream& operator<<(std::ostream& out, const SpreadSheet& rhv)
{
    int width = 8;
    double width_table = rhv.getCol() * 9.1;
    int h_line = 1;
    for (size_t i = 0; i < rhv.getRow(); ++i)
    {
        for(size_t k = 0; k < width_table; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for(size_t j = 0; j < rhv.getCol(); ++j)
       	{
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << rhv[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }
    for(size_t k = 0; k < width_table; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs) {
    if (lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol()) {
        return false;
    }

    for (int i = 0; i < lhs.getRow(); ++i) {
        for (int j = 0; j < lhs.getCol(); ++j) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs) {
    return !(lhs == rhs);
}





















