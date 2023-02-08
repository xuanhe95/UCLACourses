#include <stack>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (maze[sr][sc] != '.') {
        return false;
    }
    maze[sr][sc] = 'X';
    stack<Coord> s;
    s.push(Coord(sr, sc));
    while (!s.empty()) {
        Coord cur = s.top();
        //cout << "(" << cur.r() << ", " << cur.c() << ")" << ", ";
        s.pop();
        int row = cur.r();
        int col = cur.c();

        if (row == er && col == ec) return true;


        if (col + 1 < nCols && maze[row][col + 1] == '.') { //East
            s.push(Coord(row, col + 1));
            maze[row][col + 1] = 'X';
        }
        if (row - 1 > 0 && maze[row - 1][col] == '.') { //North
            s.push(Coord(row - 1, col));
            maze[row - 1][col] = 'X';
        }
        if (col - 1 < nCols && maze[row][col - 1] == '.') { //West
            s.push(Coord(row, col - 1));
            maze[row][col - 1] = 'X';
        }
        if (row + 1 < nRows && maze[row + 1][col] == '.') { //South
            s.push(Coord(row + 1, col));
            maze[row + 1][col] = 'X';
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

    if (pathExists(maze, 10, 10, 5, 3, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
