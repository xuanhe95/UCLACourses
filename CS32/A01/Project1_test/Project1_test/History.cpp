#include "globals.h"
#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_grid[i][j] = 0;
        }
    }
};

bool History::record(int r, int c) {
	if (r <= 0 || c <= 0 || r > m_rows || c > m_cols) return false;
	m_grid[r-1][c-1]++;
	return true;
}

void History::display() const {


    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= m_rows; r++){
        for (c = 1; c <= m_cols; c++) {
            int status = getCellStatus(r, c);
            if (status == EMPTY) displayGrid[r - 1][c - 1] = '.';
            else if (status < 26) displayGrid[r - 1][c - 1] = 'A' + status - 1;
            else displayGrid[r - 1][c - 1] = 'Z';
        }
    }


    // Draw the grid
    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;

    
}



int History::getCellStatus(int r, int c) const
{
    return m_grid[r - 1][c - 1];
}