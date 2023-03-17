#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0) :
		GraphObject(imageID, startX, startY, 0, 0, 1.0),
		m_world(world)
	{}
	virtual void doSomething();
	const bool isOverlap(const Actor& other);
	const bool isLandedOn(const Actor& other);
	StudentWorld* getWorld();
	const int getWalkDirection();
	void setWalkDirection(int dir);
private:
	int m_walkDir = right;
	StudentWorld* m_world;
};

class Player : public Actor {
public:
	Player(int player, StudentWorld* world, int imageID, int startX, int startY) :
		Actor(world, imageID, startX, startY, 0, 0, 1.0),
		m_player_number(player),
		m_coin(0),
		m_star(0),
		m_ticks_to_move(0),
		m_ticks_stay(0),
		m_waiting_to_roll(true)
	{
	}
	virtual void doSomething();
	void walkingStep();
	void addCoins(int num);
	int getNumber();
	int getMoves();
	bool canMoveForward(int dir);
	void updateSpriteDirection();
private:
	int m_player_number;
	int m_coin;
	int m_star;
	int m_ticks_to_move;
	int m_ticks_stay;
	bool m_waiting_to_roll;
};

class Square : public Actor {
public:
	Square(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0) :
		Actor(world, imageID, startX, startY, 0, 0, 1.0),
		m_alive(true)
	{}
	const bool isAlive();
	void setAlive(bool alive);
private:
	int m_alive;
};

class CoinSquare : public Square {
public:
	CoinSquare(int type, StudentWorld* world, int imageID, int startX, int startY) :
		Square(world, imageID, startX, startY, 0, 1, 1.0),
		m_type(type),
		m_ticks1(0),
		m_ticks2(0)
	{
	}
	void doSomething();
	void CoinSquare::giveOrTake(Player& plyaer, int num, int type);
private:
	int m_type;
	int m_ticks1;
	int m_ticks2;
};

#endif // ACTOR_H_
