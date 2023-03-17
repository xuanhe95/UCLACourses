
#include<iostream>
#include <cassert>
using namespace std;

//=================== COMMENT OUT UP ====================

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr < 0 || sr >= nRows || sc < 0 || sc >= nCols || maze[sr][sc] != '.') return false;
    // if out of bound or there is no way, return false
    if (sr == er && sc == ec) return true;  // if we reach our goal
    maze[sr][sc] = 'X'; //mark as visited
    bool east = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec); //recursively search four directions
    bool north = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
    bool west = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    bool south = pathExists(maze, nRows, nCols, sr, sc + 1, er, ec);
    return east || north || west || south;  // return if any direction could reach our goal
}

//=================== COMMENT OUT DOWN ====================

int main(){
        string maze1[10] = {
            "XXXXXXXXXX",
            "X........X",
            "XX.X.XXXXX",
            "X..X.X...X",
            "X..X...X.X",
            "XXXX.XXX.X",
            "X..X...XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
        };
        assert(pathExists(maze1, 10, 10, 2, 2, 6, 6));
        string maze2[10] = {
            "XXXXXXXXXX",
            "X........X",
            "XX.X.XXXXX",
            "X..X.X...X",
            "X..X...X.X",
            "XXXX.XXX.X",
            "X..X...XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
        };
        assert(!pathExists(maze2, 10, 10, 2, 2, 8, 1));
        string maze3[10] = {
            "XXXXXXXXXX",
            "X........X",
            "XX.XXXXXXX",
            "X..X.X...X",
            "X..X...X.X",
            "XXXX.XXX.X",
            "X..X...XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
        };
        assert(!pathExists(maze3, 10, 10, 6, 6, 2, 2));
        string maze4[10] = {
            "XXXXXXXXXX",
            "X........X",
            "XX.X.XXXXX",
            "X..X.X...X",
            "X..X...X.X",
            "XXXX.XXX.X",
            "X......XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
        };
        assert(pathExists(maze4, 10, 10, 2, 2, 8, 1));

        cerr << "pass all test!" << endl;

}

