#include <iostream>
#include "spread_sheet.h"

int main()
{

    SpreadSheet ob(5, 5);
    for (int i = 0; i < ob.getRow(); ++i) {
        for (int j = 0; j < ob.getCol(); ++j) {
            ob[i][j] = rand()%2;
        }
    }

    std::cout << ob << std::endl;

    ob.resizeRow(4);
    ob.resizeCol(6);

    Cell objj("");
    for (int i = 0; i < ob.getRow(); ++i) {
        for (int j = 0; j < ob.getCol(); ++j) {
            if (ob[i][j] == objj) {
                continue;
            }
            int z = i + j % 4;
            
            switch (z) {
                case 0: {
                    ob[i][j] = i * j;
                    break;
                }
                case 1: {
                    ob[i][j] = std::to_string(i + j);
                    break;
                }
                case 2: {
                    ob[i][j] = i * 1.2 / j;
                    break;
                }
                case 3: {
                    ob[i][j] = std::vector(i, j);
                    break;
                }
            }    
        }
    }

    std::cout << ob << std::endl;

    ob.resize(5, 5);

    std::cout << ob << std::endl;

    std::initializer_list<size_t> rows = {1, 5, 7, 8, 9};
    std::initializer_list<size_t> cols = {1, 2, 3, 4, 8, 10, 12};

    ob.mirrorH();
    ob.mirrorV();

    std::cout << ob << std::endl;

    SpreadSheet ob2 = ob.slice(rows, cols);

    std::cout << ob2 << std::endl;



    ob.mirrorD();
    ob2.mirrorD();

    std::cout << std::boolalpha << (ob2 == ob.slice(cols, rows)) << std::endl;

    std::vector<int> v1 = ob[11][8];
    std::vector<int> v2 = ob2[4][2];
    
    std::cout << std::boolalpha << v1.empty() << std::endl;
    std::cout << std::boolalpha << v2.empty() << std::endl;

    std::cout << std::boolalpha << (v1 == v2) << std::endl;
    


    return 0;
}

