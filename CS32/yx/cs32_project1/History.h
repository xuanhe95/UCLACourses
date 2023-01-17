//
//  History.hpp
//  cs32_project1
//
//  Created by XYX on 2023/1/12.
//

#ifndef History_hpp
#define History_hpp

#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_rows;
        int m_cols;
        int grid[MAXROWS][MAXCOLS];
};

#endif
