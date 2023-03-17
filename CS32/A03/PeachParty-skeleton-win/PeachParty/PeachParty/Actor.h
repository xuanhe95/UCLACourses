#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// ===========================================================================================================================
// ACTOR CLASS
// ===========================================================================================================================

class Actor : public GraphObject {
public:
	static const int left = 180;
	static const int right = 0;
	static const int up = 90;
	static const int down = 270;
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		GraphObject(imageID, startX, startY, dir, depth, size),
		m_world(world),
		m_alive(true) {}
	// pure virtual functions
	virtual void doSomething() = 0;
	virtual bool isSquare() const = 0;

	// get status
	void setAlive(bool alive);
	bool isAlive() const;
	StudentWorld* getWorld() const;

	// get relation with other actors
	bool isOverlap(Actor* other) const;
	bool isLandedOn(Actor* other) const;

private:
	StudentWorld* m_world;	// hold world class
	bool m_alive;
};

// ===========================================================================================================================
// CHARACTER CLASS (ALL MOVE STUFF) : Actor
// ===========================================================================================================================

class Character :public Actor
{
public:
	Character(StudentWorld* world, int imageID, int startX, int startY, bool waiting, bool impactable, bool startMove, int dir = 0) :
		Actor(world, imageID, startX, startY, dir, 0, 1.0),
		m_impactable(impactable),
		m_moving(startMove),
		m_walkDir(right),
		m_ticks_to_move(0),
		m_ticks_stay(0),
		m_waiting_to_roll(waiting),
		m_realX(startX),
		m_realY(startY)
	{}

	// virtual functions
	virtual bool isSquare() const;
	virtual void randomTeleport();

	int getMoves() const;
	void setMoves(int num);

	// waiting or walking
	void setWaiting(bool wait);
	bool isWaiting() const;
	// waiting time counter
	void setStayTime(int num);
	int getStayTime() const;
	// help when characters' animations are moving
	bool isMoving() const;
	void setMoving(bool move);
	// get some status

	bool isImpactable() const;
	virtual void impacted();	// stub for future
	

	// another position system to guide characters when they are moving
	// get and maintain all kind of directions
	void setRealX(int x);
	void setRealY(int y);
	int getRealX() const;
	int getRealY() const;
	void getRealPositionInThisDirection(int angle, int distance, int& newX, int& newY) const;
	void updateSpriteDirection();
	void setWalkDirection(int dir);
	int getWalkDirection() const;
	bool canMoveForward(int dir) const;
	void updateRealPosition();
	std::vector<int>* getPossibleDir() const;

	// swap two characters
	void swap(Character& other);
private:
	bool m_impactable;
	bool m_moving;
	int m_walkDir;
	int m_ticks_to_move;
	int m_ticks_stay;
	bool m_waiting_to_roll;
	int m_realX;
	int m_realY;
};

// ===========================================================================================================================
// PLAYER CLASS (PEACH AND YOSHI) : Character : Actor
// ===========================================================================================================================


class Player : public Character {
public:
	Player(int player, StudentWorld* world, int imageID, int startX, int startY) :
		Character(world, imageID, startX, startY, true, false, true),
		m_player_number(player),
		m_coin(0),
		m_star(0),
		m_has_vortex(false){}
	// virtual funcions
	virtual void doSomething();
	virtual void walkingStep();

	// maintain coins, stars and vortex
	int getPlayer() const;
	void setCoins(int num);
	void setStarts(int num);
	int getCoins() const;
	int getStars() const;
	int addCoins(int num);
	void addStars(int num);
	int getDices() const;
	bool hasVortex() const;
	void setVortex(bool vortex);
private:
	int m_player_number;	// to distinguish Peach or Yoshi
	int m_coin;
	int m_star;
	bool m_has_vortex;
};

// ===========================================================================================================================
// BADDIE CLASS : Character : Actor
// ===========================================================================================================================

class Baddie :public Character{
public:
	Baddie(StudentWorld* world, int imageID, int startX, int startY) :
		Character(world, imageID, startX, startY, true, true, true),
		m_travel_distance(0),
		m_pause_counter(180)
	{}

	// pure virtual functions
	virtual void interactWith(Player* player) = 0;
	virtual void walkingStep() = 0;
	// virtual funcions;
	virtual void doSomething();
	// maintain pause counter
	int getPauseCounter() const;
	void setPauseCounter(int num);
	// action when inpacted
	void impacted();
private:
	int m_pause_counter;
	int m_travel_distance;
};

// ===========================================================================================================================
// BOWSER CLASS : Baddie : Character : Actor
// ===========================================================================================================================

class Bowser :public Baddie {
public:
	Bowser(StudentWorld* world, int startX, int startY) :
		Baddie(world, IID_BOWSER, startX, startY) {
	}
	virtual void interactWith(Player* player);
	virtual void walkingStep();
};

// ===========================================================================================================================
// BOO CLASS : Baddie : Character : Actor
// ===========================================================================================================================

class Boo :public Baddie {
public:
	Boo(StudentWorld* world, int startX, int startY) :
		Baddie(world, IID_BOO, startX, startY) {
	}

	virtual void interactWith(Player* player);
	virtual void walkingStep();
};

// ===========================================================================================================================
// VORTEX CLASS : Character : Actor
// ===========================================================================================================================

class Vortex :public Character {
public:
	Vortex(StudentWorld* world, int startX, int startY, int dir) :
		Character(world, IID_VORTEX, startX, startY, false, false, true, dir)
	{}
	virtual void doSomething();
	virtual void interactWith(Character* character);
};

// ===========================================================================================================================
// SQUARE CLASS (ALL STABLE STUFF)  : Actor
// ===========================================================================================================================


class Square : public Actor {
public:
	Square(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		Actor(world, imageID, startX, startY, dir, depth, size),
		m_overlapping1(0),
		m_overlapping2(0) {}

	virtual void interactWith(Player* player) = 0;
	void doSomething();
	bool isSquare() const;
	// helper functions to test whether players (first) passing / landed a sqaure
	bool isLandedOn(Player* player) const;
	bool isPassingThrough(Player* player) const;
	bool isFirstPassing(Player* player);
	bool isFirstOverlapping(Player* player);
	// maintain overlapping time counter
	int getOverlappingTime(int playerNum) const;
	void setOverlappingTime(int playerNum, int num);
private:
	int m_overlapping1;	// overlapping time counter to decide whether first contact
	int m_overlapping2;
};
// ===========================================================================================================================
// RED COIN SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

class RedCoinSquare :public Square {
public:
	RedCoinSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_RED_COIN_SQUARE, startX, startY, 0, 1, 1.0){ }
	virtual void interactWith(Player* player);
};
// ===========================================================================================================================
// BLUE COIN SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

class BlueCoinSquare :public Square {
public:
	BlueCoinSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_BLUE_COIN_SQUARE,startX, startY, 0, 1, 1.0) { }
	virtual void interactWith(Player* player);
};
// ===========================================================================================================================
// EVENT SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

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

// ===========================================================================================================================
// CENTRAL BANK
// ===========================================================================================================================

class CentralBank {
public:
	void deposit(int num);
	int withdraw();
	int getMoney();
private:
	int m_money;
};
// ===========================================================================================================================
// BANK SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

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
// ===========================================================================================================================
// STAR SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

class StarSquare :public Square {
public:
	StarSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_STAR_SQUARE, startX, startY, 0, 1, 1.0) { }
	virtual void interactWith(Player* player);
};
// ===========================================================================================================================
// DIRECTIONAL SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

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
// ===========================================================================================================================
// DROPPING SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

class DroppingSquare :public Square {
public:
	DroppingSquare(StudentWorld* world, int startX, int startY) :
		Square(world, IID_DROPPING_SQUARE, startX, startY, 0, 1, 1.0)
	{ }
	virtual void interactWith(Player* player);
};


#endif  //ACTOR_H_