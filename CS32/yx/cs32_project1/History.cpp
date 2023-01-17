//
//  History.cpp
//  cs32_project1
//
//  Created by XYX on 2023/1/12.
//

#include "History.h"
#include "globals.h"

#include <iostream>
using namespace std;

History::History (int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 1; i <= m_rows; i++) {
        for (int j = 1; j <= m_cols; j++){
            grid[i-1][j-1] = 0;
        }
    }
}

bool History::record(int r, int c){
    if (r > m_rows || c > m_cols || r < 1 || c < 1) {
        return false;
    }
    else {
        grid[r - 1][c - 1]++;
        return true;
    }
}

void History::display() const {
    char displayGrid[MAXROWS][MAXCOLS];
    for (int i = 1; i <= m_rows; i++) {
        for (int j = 1; j <= m_cols; j++){
            if (grid[i-1][j-1] == 0) {
                displayGrid[i-1][j-1] = '.';
            }
            else if (grid[i-1][j-1] <= 26) {
                displayGrid[i-1][j-1] = 'A' + grid[i-1][j-1] - 1;
            }
            else {
                displayGrid[i-1][j-1] = 'Z';
            }
        }
    }
    clearScreen();
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
