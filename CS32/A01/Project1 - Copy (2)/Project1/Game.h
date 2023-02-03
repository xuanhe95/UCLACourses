
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <string>
class Arena;

bool recommendMove(const Arena& a, int r, int c, int& bestDir);
int computeDanger(const Arena& a, int r, int c);


class Game
{
    public:
        // Constructor/destructor
        Game(int rows, int cols, int nRabbits);
        ~Game();

        // Mutators
        void play();

    private:
        Arena* m_arena;

        // Helper functions
        std::string takePlayerTurn();
};
#endif