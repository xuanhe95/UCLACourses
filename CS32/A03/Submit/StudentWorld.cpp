#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;



GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    /*
    1. Initialize the data structures used to keep track of your game¡¯s world.
    2. Allocate and insert Peach and Yoshi objects into the game world. Every time a
        game begins, Peach and Yoshi start out initialized in their starting location as
        specified by the current board data file.
    3. Allocate and insert all of the other objects (e.g., squares, baddies, etc.) into the
        game world as described below.
    4. Start the countdown timer for the 99-second game.
    
    */

    int boardNum = getBoardNumber();
    ostringstream board_txt;
    board_txt << "board" << setfill('0') << setw(2) << boardNum << ".txt";
    Board bd;

    string board_file = assetPath() + board_txt.str();
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
    {
        cerr << "Could not find board01.txt data file\n";
    }
    else if (result == Board::load_fail_bad_format)
    {
        cerr << "Your board was improperly formatted\n";
    }
    else if (result == Board::load_success) {
        
        cerr << "Successfully loaded board\n";
        bank = new CentralBank();
        int playerNumber = 0;
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                Board::GridEntry type = bd.getContentsOf(x, y);
                if (type == Board::player) {
                    if (playerNumber == 0) {
                        m_player1 = new Player(1, this, IID_PEACH, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                        m_player2 = new Player(2, this, IID_YOSHI, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                        Square* coin = new BlueCoinSquare(this,  x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                        m_actors->push_back(coin);
                    }
                    else m_player2 = new Player(playerNumber, this, IID_YOSHI, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    playerNumber++;
                }
                else if (type == Board::blue_coin_square) {
                    Square* coin = new BlueCoinSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    m_actors->push_back(coin);
                }
                else if (type == Board::red_coin_square) {
                    Square* coin = new RedCoinSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    m_actors->push_back(coin);
                }
                else if (type == Board::boo) {
                    CoinSquare* coin = new BlueCoinSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    Actor* npc = new Boo(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    
                    m_actors->push_back(npc);
                    m_actors->push_back(coin);

                }
                else if (type == Board::bowser) {
                    Square* coin = new BlueCoinSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    Actor* npc = new Bowser(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    
                    m_actors->push_back(npc);
                    m_actors->push_back(coin);
                }
                else if (type == Board::event_square) {
                    Square* square = new EventSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    m_actors->push_back(square);
                }
                else if (type == Board::bank_square) {
                    Square* square = new BankSquare(bank, this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    m_actors->push_back(square);
                }
                else if (type == Board::down_dir_square) {
                    Square* square = new DirectionalSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::down);
                    m_actors->push_back(square);
                }
                else if (type == Board::up_dir_square) {
                    Square* square = new DirectionalSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::up);
                    m_actors->push_back(square);
                }
                else if (type == Board::left_dir_square) {
                    Square* square = new DirectionalSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::left);
                    m_actors->push_back(square);
                }
                else if (type == Board::right_dir_square) {
                    Square* square = new DirectionalSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT, Actor::right);
                    m_actors->push_back(square);
                }
                else if (type == Board::star_square) {
                    StarSquare* star = new StarSquare(this, x * SPRITE_WIDTH, y * SPRITE_HEIGHT );
                    //CoinSquare* coin = new BlueCoinSquare(this, IID_BLUE_COIN_SQUARE, x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
                    //m_actors->push_back(coin);
                    m_actors->push_back(star);
                }
               
            }
        }
    }

	startCountdownTimer(99);  // this placeholder causes timeout after 99 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    //cerr << "MOVING" << endl;
    m_player1->doSomething();
    m_player2->doSomething();

    for (int i = 0; i < m_actors->size(); i++) {
        if (m_actors->at(i)->isAlive()) {
            m_actors->at(i)->doSomething();
        }
    }

    setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0) {
        playSound(SOUND_GAME_FINISHED);
        //setFinalScore();
        return GWSTATUS_NOT_IMPLEMENTED;
    }

        
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    while (!m_actors->empty()) {
        Actor* temp = m_actors->back();
        m_actors->pop_back();
        delete temp;
    }
    delete m_player1;
    delete m_player2;
    delete bank;
}

bool StudentWorld::hasSquare(int x, int y) {
    for (int i = 0; i < m_actors->size(); i++) {
        Actor* actor = m_actors->at(i);
        if (actor->getRealX() == x && actor->getRealY() == y) { return true; }
    }
    return false;
}
Square* getRandomSqaure() {
    
    return nullptr;
}


Player* StudentWorld::getPlayer1() { return m_player1; }
Player* StudentWorld::getPlayer2() { return m_player2; }
