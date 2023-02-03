#include <stack>
#include <queue>
#include <iostream>

using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
//char getChar(int row, int col);
bool pathExistsQ(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> s;
    s.push(Coord(sr, sc));
    while (!s.empty()) {
        Coord cur = s.top();
        s.pop();
        int row = cur.r();
        int col = cur.c();

        if (row == er && col == ec) return true;

        if (row+1 < nRows && maze[row+1][col] == '.') {
            s.push(Coord(row+1, col));
            maze[row + 1][col] = 'X';
        }
        if (row - 1 > 0 && maze[row - 1][col] == '.') {
            s.push(Coord(row - 1, col));
            maze[row - 1][col] = 'X';
        }
        if (col + 1 < nCols && maze[row][col + 1] == '.') {
            s.push(Coord(row, col + 1));
            maze[row][col + 1] = 'X';
        }
        if (col - 1 < nCols && maze[row][col - 1] == '.') {
            s.push(Coord(row, col - 1));
            maze[row][col - 1] = 'X';
        }
    }
    return false;
}

bool pathExistsQ(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> q;
    q.push(Coord(sr, sc));
    while (!q.empty()) {
        Coord cur = q.front();
        q.pop();
    
        int row = cur.r();
        int col = cur.c();

        if (row == er && col == ec) return true;

        if (row + 1 < nRows && maze[row + 1][col] == '.') {
            q.push(Coord(row + 1, col));
            maze[row + 1][col] = 'X';
        }
        if (row - 1 > 0 && maze[row - 1][col] == '.') {
            q.push(Coord(row - 1, col));
            maze[row - 1][col] = 'X';
        }
        if (col + 1 < nCols && maze[row][col + 1] == '.') {
            q.push(Coord(row, col + 1));
            maze[row][col + 1] = 'X';
        }
        if (col - 1 < nCols && maze[row][col - 1] == '.') {
            q.push(Coord(row, col - 1));
            maze[row][col - 1] = 'X';
        }
    }
    return false;

}


int main()
{
    string maze[10] = {
                    "XXXXXXXXXX",
                    "X..X...X.X",
                    "X.XXXX.X.X",
                    "X.X.X..X.X",
                    "X...X.XX.X",
                    "XXX......X",
                    "X.X.XXXX.X",
                    "X.XXX....X",
                    "X...X..X.X",
                    "XXXXXXXXXX"
    };

    if (pathExistsQ(maze, 10, 10, 5, 3, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


