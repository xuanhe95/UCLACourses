#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>

#include <vector>

#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();


  bool hasSquare(int x, int y);
  Square* getRandomSquare();

  //bool getSquare(int x, int y, Square* &square);
  Player* getPlayer1();
  Player* getPlayer2();

private:
	Board* m_board;
	std::vector<Actor*>* m_actors = new std::vector<Actor*>();
	Player* m_player1;
	Player* m_player2;
	CentralBank* bank;
};

#endif // STUDENTWORLD_H_
