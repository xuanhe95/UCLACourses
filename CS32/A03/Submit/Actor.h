#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		GraphObject(imageID, startX, startY, dir, depth, size),
		m_world(world),
		m_realX(startX),
		m_realY(startY),
		m_walkDir(right),
		m_alive(true)
		//m_active(true)
	{}
	virtual void doSomething()=0;

	
	void setWalkDirection(int dir);
	void setRealX(int x);
	void setRealY(int y);
	void updateRealPosition();
	void setAlive(bool alive);
	//const
	bool isOverlap(Actor* other) const;
	bool isLandedOn(Actor* other) const;
	//bool isActive() const;

	int getWalkDirection() const;
	int getRealX() const;
	int getRealY() const;
	void getRealPositionInThisDirection(int angle, int distance, int& newX, int& newY) const;
	bool isAlive() const;
	StudentWorld* getWorld() const;
	void updateSpriteDirection();
	void swap(Actor& other);


private:
	StudentWorld* m_world;
	int m_walkDir;
	int m_realX;
	int m_realY;
	bool m_alive;
	//bool m_active;
};

class Player : public Actor {
public:
	Player(int player, StudentWorld* world, int imageID, int startX, int startY, bool impactable = false) :
		Actor(world, imageID, startX, startY, 0, 0, 1.0),
		m_player_number(player),
		m_coin(0),
		m_star(0),
		m_ticks_to_move(0),
		m_ticks_stay(0),
		m_waiting_to_roll(true),
		m_has_vortex(false),
		m_impactable(impactable)
	{}
	// const
	int getPlayer() const;
	bool canMoveForward(int dir) const;
	int getStayTime() const;
	int getCoins() const;
	int getStars() const;
	

	std::vector<int>* getPossibleDir() const;



	virtual void doSomething();
	void walkingStep();
	int addCoins(int num);
	int getMoves() const;
	void swap(Player& other);

	void addStars(int num);
private:
	int m_player_number;
	int m_coin;
	int m_star;
	int m_ticks_to_move;
	int m_ticks_stay;
	bool m_waiting_to_roll;
	bool m_has_vortex;
	bool m_impactable;
};

class Square : public Actor {
public:
	Square(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		Actor(world, imageID, startX, startY, dir, 1, 1.0),
		m_overlapping1(0),
		m_overlapping2(0) {}
	virtual void doSomething();
	bool isFirstOverlapping(Player* player);
	int getOverlappingTime(int playerNum) const;
	void setOverlappingTime(int playerNum, int num);
	bool isLandedOn(Player* player) const;
	bool isPassingThrough(Player* player) const;
	virtual void interactWith(Player* player) = 0;
private:
	int m_overlapping1;
	int m_overlapping2;
};

class CoinSquare : public Square {
public:
	CoinSquare(StudentWorld* world, int imageID, int startX, int startY, int dir = right, int depth = 0, double size = 1.0) :
		Square(world, imageID, startX, startY, dir, 1, 1.0)
	{
	}
	virtual void interactWith(Player* player) = 0;
};

class RedCoinSquare :public CoinSquare {
public:
	RedCoinSquare(StudentWorld* world, int startX, int startY) :
		CoinSquare(world, IID_RED_COIN_SQUARE, startX, startY, 0, 1, 1.0){ }
	virtual void interactWith(Player* player);
};

class BlueCoinSquare :public CoinSquare {
public:
	BlueCoinSquare(StudentWorld* world, int startX, int startY) :
		CoinSquare(world, IID_BLUE_COIN_SQUARE,startX, startY, 0, 1, 1.0) { }
	virtual void interactWith(Player* player);
};

class EventSquare :public Square {
public:
	EventSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_EVENT_SQUARE, startX, startY, 0, 1, 1.0)
		 { }
	virtual void interactWith(Player* player);
	void teleport(Player* player);
	void swapPlayers();
	void giveGun(Player* player);
};

class CentralBank {
public:
	void deposit(int num);
	int withdraw();
private:
	int m_money;
};

class BankSquare :public Square {
public:
	BankSquare(CentralBank* bank, StudentWorld* world, int startX, int startY) :
		Square(world, IID_BANK_SQUARE, startX, startY, 0, 1, 1.0),
		m_bank(bank){ }
	virtual void interactWith(Player* player);
	CentralBank* getBank();
private:
	CentralBank* m_bank;
};

class StarSquare :public Square {
public:
	StarSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_STAR_SQUARE, startX, startY, 0, 1, 1.0) { }
	virtual void interactWith(Player* player);
};

class DirectionalSquare :public Square {
public:
	DirectionalSquare(StudentWorld* world,int startX, int startY, int dir) :
		Square(world, IID_DIR_SQUARE, startX, startY, dir, 1, 1.0),
		m_forcing_dir(dir)
	{ 
		//setDirection(dir);
	}
	virtual void interactWith(Player* player);
	int getForcingDirection();
private:
	int m_forcing_dir;
};

class DroppingSquare :public Square {
	DroppingSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_DROPPING_SQUARE, startX, startY, 0, 1, 1.0)
	{ }
	virtual void interactWith(Player* player);
};

class Baddie :public Actor {
public:
	Baddie(StudentWorld* world, int imageID,int startX, int startY) :
		Actor(world, imageID, startX, startY, 0, 0, 1.0),
		m_walking(false),
		m_travel_distance(0),
		m_ticks_wait(180)
	{}
	virtual void doSomething();
	virtual void teleport();
private:
	bool m_walking;
	int m_travel_distance;
	int m_ticks_wait;
};

class Bowser :public Baddie {
public:
	Bowser(StudentWorld* world, int startX, int startY) :
		Baddie(world, IID_BOWSER, startX, startY) {

	}
	virtual void doSomething();
};
class Boo:public Baddie { 
public:
	Boo(StudentWorld* world, int startX, int startY) :
		Baddie(world, IID_BOO, startX, startY) {
	}
	
	virtual void doSomething(); };
class Vortex:public Actor{
	Vortex(Player* player, StudentWorld* world, int startX, int startY) :
		Actor(world, IID_VORTEX, startX, startY, 0, 0, 1.0),
		m_holder(player)
	{}
	virtual void doSomething(); 
private:
	Player* m_holder;
};

#endif  //ACTOR_H_