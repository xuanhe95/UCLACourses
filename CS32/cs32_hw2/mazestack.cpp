#include<iostream>
#include <stack>
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
    stack<Coord> coordStack;
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    Coord current(sr, sc);
    coordStack.push(current);
    //update maze[sr][sc] to indicate that the algorithm has encountered it
    maze[sr][sc] = '!';
    while (!coordStack.empty()){            //While the stack is not empty
        if (coordStack.top().r() == er && coordStack.top().c() == ec){
            return true;
        }
        sr = coordStack.top().r();
        sc = coordStack.top().c();
        coordStack.pop();
        if (sc+1 < nCols-1 && maze[sr][sc+1] == '.'){
            Coord discover(sr, sc+1);
            coordStack.push(discover);
            maze[sr][sc+1] = '!';
        }
        if (sr-1 >= 0 && maze[sr-1][sc] == '.') {
            Coord discover(sr-1, sc);
            coordStack.push(discover);
            maze[sr-1][sc] = '!';
        }
        if (sc-1 >= 0 && maze[sr][sc-1] == '.'){
            Coord discover(sr, sc-1);
            coordStack.push(discover);
            maze[sr][sc-1] = '!';
        }
        if (sr+1 < nRows-1 && maze[sr+1][sc] == '.'){
            Coord discover(sr+1, sc);
            coordStack.push(discover);
            maze[sr+1][sc] = '!';
        }
        cerr << coordStack.top().r() << ", " << coordStack.top().c() << endl;
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
