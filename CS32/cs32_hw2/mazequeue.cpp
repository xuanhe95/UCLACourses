#include<iostream>
#include <queue>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    queue<Coord> coordQueue;
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    Coord current(sr, sc);
    coordQueue.push(current);
    //update maze[sr][sc] to indicate that the algorithm has encountered it
    maze[sr][sc] = '!';
    while (!coordQueue.empty()){            //While the stack is not empty
        if (coordQueue.front().r() == er && coordQueue.front().c() == ec){
            return true;
        }
        sr = coordQueue.front().r();
        sc = coordQueue.front().c();
        coordQueue.pop();
        if (sc+1 < nCols-1 && maze[sr][sc+1] == '.'){
            Coord discover(sr, sc+1);
            coordQueue.push(discover);
            maze[sr][sc+1] = '!';
        }
        if (sr-1 >= 0 && maze[sr-1][sc] == '.') {
            Coord discover(sr-1, sc);
            coordQueue.push(discover);
            maze[sr-1][sc] = '!';
        }
        if (sc-1 >= 0 && maze[sr][sc-1] == '.'){
            Coord discover(sr, sc-1);
            coordQueue.push(discover);
            maze[sr][sc-1] = '!';
        }
        if (sr+1 < nRows-1 && maze[sr+1][sc] == '.'){
            Coord discover(sr+1, sc);
            coordQueue.push(discover);
            maze[sr+1][sc] = '!';
        }
        cerr << coordQueue.front().r() << ", " << coordQueue.front().c() << endl;
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
        
            if (pathExists(maze, 10,10, 5,3, 8,8))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }
