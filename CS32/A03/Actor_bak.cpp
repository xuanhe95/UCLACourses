#include "Actor.h"
#include "StudentWorld.h"


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor
StudentWorld* Actor::getWorld() const { return m_world; }
int Actor::getWalkDirection() const { return m_walkDir; }
bool Actor::isOverlap(Actor& other) const {
	int x = getX();
	int y = getY();

	int minX = x - SPRITE_WIDTH / 2;
	int maxX = x + SPRITE_WIDTH / 2;
	int minY = y - SPRITE_HEIGHT / 2;
	int maxY = y + SPRITE_HEIGHT / 2;

	int otherX = other.getX();
	int otherY = other.getY();

	int minOX = otherX - SPRITE_WIDTH / 2;
	int maxOX = otherX - SPRITE_WIDTH / 2;
	int minOY = otherY - SPRITE_HEIGHT / 2;
	int maxOY = otherY + SPRITE_HEIGHT / 2;


	if (minX <= minOX && minY <= minOY || maxX >= maxOX && maxY >= maxOY) return true;
	return false;

}	//stub
bool Actor::isLandedOn(Actor& other) const { return (other.getX() == getX()) && (other.getY() == getY()); }
int Actor::getRealX() const { return m_realX; }
int Actor::getRealY() const { return m_realY; }
bool Actor::isAlive() const { return m_alive; }
void Actor::getRealPositionInThisDirection(int angle, int distance, int& newX, int& newY) const {
	newX = getRealX();
	newY = getRealY();
	switch (angle)
	{
	case left:  newX -= distance; break;
	case right: newX += distance; break;
	case up:    newY += distance; break;
	case down:  newY -= distance; break;
	}
}

void Actor::setWalkDirection(int dir) { m_walkDir = dir; }
void Actor::doSomething() { return; }
void Actor::setRealX(int x) { m_realX = x; }
void Actor::setRealY(int y) { m_realY = y; }
void Actor::setAlive(bool alive) { m_alive = alive; }
void Actor::updateRealPosition(){
	//getX() % SPRITE_WIDTH == 0 && getX() % SPRITE_HEIGHT == 0
	if (getWorld()->hasSquare(getX(),getY())) {
		setRealX(getX());
		setRealY(getY());
		std::cerr << "UPDATED" << std::endl;
	}
}

//Player

void Player::doSomething() {
	//std::cerr << "WORKING" << std::endl;
	if (m_waiting_to_roll) {
		m_ticks_stay++;
		/*
		if (!canMoveForward(getWalkDirection())) {
			std::vector<int>* validDir = new std::vector<int>();
			if (canMoveForward(left)) validDir->push_back(left);
			if (canMoveForward(right)) validDir->push_back(right);
			if (canMoveForward(up)) validDir->push_back(up);
			if (canMoveForward(down)) validDir->push_back(down);
			if (validDir->size() == 0) return;
			int rand = randInt(0, validDir->size()-1);
			setWalkDirection(validDir->at(rand));
			updateSpriteDirection();
		}*/
		int action = getWorld()->getAction(getPlayer());
		if (action == ACTION_ROLL) {
			std::cerr << "WORKING" << std::endl;
			int die_roll = randInt(1, 10);	// random number from 1 to 10, inclusive
			m_ticks_to_move = die_roll * 8;
			m_waiting_to_roll = false;
			walkingStep();
		}
		else if (action == ACTION_FIRE) {
			getWorld()->playSound(SOUND_PLAYER_FIRE);
		}
		else { return; }
	}
	else {
		walkingStep();
	}

}
void Player::updateSpriteDirection(){
	if (getWalkDirection() == left) { setDirection(180); }
	else { setDirection(0); }
}
int Player::getPlayer() const {
	return m_player_number;
}

void Player::walkingStep() {
	int dir = getWalkDirection();
	if ( !canMoveForward(dir) ) {
		if (dir == left || dir == right) { canMoveForward(up) ? setWalkDirection(up) : setWalkDirection(down); }
		else { canMoveForward(right) ? setWalkDirection(right) : setWalkDirection(left); }
		updateSpriteDirection();
	}
	std::cerr << getWalkDirection() << std::endl;
	moveAtAngle(getWalkDirection(), 2);
	updateRealPosition();
	m_ticks_to_move--;
	if (m_ticks_to_move == 0) {
		std::cerr << "WALK OVER" << std::endl;
		setRealX(getX());
		setRealY(getY());
		m_waiting_to_roll = true;
		m_ticks_stay = 0;
	}
}
bool Player::canMoveForward(int dir) const {
	int x = getRealX();
	int y = getRealY();
	getRealPositionInThisDirection(dir, SPRITE_HEIGHT, x, y);
	return getWorld()->hasSquare(x, y);
}
void Player::addCoins(int num) { m_coin += num; }
int Player::getMoves() { return m_ticks_to_move; }

//Coin
void CoinSquare::doSomething() {
	if (!isAlive()) return;
	Player* player1 = getWorld()->getPlayer1();
	Player* player2 = getWorld()->getPlayer2();

	if (isLandedOn(*player1) && m_ticks1 == 0) {
		giveOrTake(*player1, 3, m_type);
		m_ticks1++;
	}
	else { m_ticks1 = 0; }
	if (isLandedOn(*player2) && m_ticks2 == 0) {
		giveOrTake(*player2, 3, m_type);
		m_ticks2++;
	}
	else { m_ticks2 = 0; }
}
void CoinSquare::giveOrTake(Player& player, int num, int type) {
	if (type == 0) {
		player.addCoins(num);
		getWorld()->playSound(SOUND_GIVE_COIN);
	}
	else {
		player.addCoins(-num);
		getWorld()->playSound(SOUND_TAKE_COIN);
	}
}
void RedCoinSquare::doSomething() {
	if (isLandedOn(*getWorld()->getPlayer1())) {
		
	}
}
void BlueCoinSquare::doSomething() {

}
