#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor
StudentWorld* Actor::getWorld() const { return m_world; }
int Actor::getWalkDirection() const { return m_walkDir; }
bool Actor::isOverlap(Actor* other) const {
	int x = getX();
	int y = getY();

	//int minX = x - SPRITE_WIDTH / 2;
	//int maxX = x + SPRITE_WIDTH / 2;
	//int minY = y - SPRITE_HEIGHT / 2;
	//int maxY = y + SPRITE_HEIGHT / 2;

	int otherX = other->getX();
	int otherY = other->getY();

	//int minOX = otherX - SPRITE_WIDTH / 2;
	//int maxOX = otherX - SPRITE_WIDTH / 2;
	//int minOY = otherY - SPRITE_HEIGHT / 2;
	//int maxOY = otherY + SPRITE_HEIGHT / 2;
	x -= otherX;
	y -= otherY;

	if (x < SPRITE_WIDTH && x > -SPRITE_WIDTH && y <SPRITE_HEIGHT && y > -SPRITE_HEIGHT) {
		return true;
	}
	return false;

}	//stub
bool Actor::isLandedOn(Actor* other) const { return (other->getX() == getX()) && (other->getY() == getY()); }
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
void Actor::updateSpriteDirection() {
	if (getWalkDirection() == left) { setDirection(180); }
	else { setDirection(0); }
}
void Actor::swap(Actor& other) {
	int temp = m_realX;
	m_realX = other.m_realX;
	other.m_realX = temp;
	temp = m_realY;
	m_realY = other.m_realY;
	other.m_realY = temp;
	temp = m_walkDir;
	m_walkDir = other.m_walkDir;
	other.m_walkDir = temp;

	updateSpriteDirection();
	other.updateSpriteDirection();

	int tempX = getX();
	int tempY = getY();

	moveTo(other.getX(), other.getY());
	other.moveTo(tempX, tempY);

}
//Player
void Player::doSomething() {
	//std::cerr << "WORKING" << std::endl;
	if (m_waiting_to_roll) {
		m_ticks_stay++;
		/*
		if (!canMoveForward(getWalkDirection())) {
			std::vector<int>* validDir = getPossibleDir();
			int rand = randInt(0, validDir->size()-1);
			setWalkDirection(validDir->at(rand));
			updateSpriteDirection();
		}*/
		int action = getWorld()->getAction(getPlayer());
		if (action == ACTION_ROLL) {
			std::cerr << "WORKING" << std::endl;
			int die_roll = randInt(1, 10);	// random number from 1 to 10, inclusive
			m_ticks_to_move = die_roll * 8;
			
			walkingStep();
			m_waiting_to_roll = false;
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
int Player::getPlayer() const {
	return m_player_number;
}
int Player::getStayTime() const { return m_ticks_stay; }
int Player::getCoins() const { return m_coin; }
int Player::getStars() const { return m_star; }
bool Player::canMoveForward(int dir) const {
	int face = getWalkDirection();
	int back = 0;
	if (face == left) back = right;
	else if (face == right) back = left;
	else if (face == up) back = down;
	else back = up;

	if (back == dir) {
		std::cerr << "FACE " << face << std::endl;
		std::cerr << "BACK " << back << std::endl;
		return false;
	}

	int x = getRealX();
	int y = getRealY();
	std::cerr << "Face " << face << std::endl;


	getRealPositionInThisDirection(dir, SPRITE_HEIGHT, x, y);
	if (!getWorld()->hasSquare(x, y)) {
		std::cerr << "CAN'T MOVE" << std::endl;
	}
	
	return getWorld()->hasSquare(x, y);
}
void Player::swap(Player& other) {

	bool tempWait = m_waiting_to_roll;
	m_waiting_to_roll = other.m_waiting_to_roll;
	other.m_waiting_to_roll = tempWait;

	int temp = m_ticks_to_move;
	m_ticks_to_move = other.m_ticks_to_move;
	other.m_ticks_to_move = temp;

	Actor::swap(other);
}
void Player::walkingStep() {
	if (!isAlive()) {
		updateSpriteDirection();
		int action = getWorld()->getAction(getPlayer());
		setAlive(true);

		if (action == ACTION_LEFT && canMoveForward(left)) { setWalkDirection(left); }
		else if (action == ACTION_RIGHT && canMoveForward(right)) { setWalkDirection(right); }
		else if (action == ACTION_UP && canMoveForward(up)) { setWalkDirection(up); }
		else if (action == ACTION_DOWN && canMoveForward(down)) { {setWalkDirection(down); } }
		else {
			setAlive(false);
			return;
		}
	}
	int dir = getWalkDirection();
	std::cerr << dir << std::endl;
	if (!canMoveForward(dir)) {
		if (dir == left || dir == right) { canMoveForward(up) ? setWalkDirection(up) : setWalkDirection(down); }
		else { canMoveForward(right) ? setWalkDirection(right) : setWalkDirection(left); }

	}
	updateSpriteDirection();
	moveAtAngle(getWalkDirection(), 2);
	updateRealPosition();
	if (getWorld()->hasSquare(getX(), getY()) && getPossibleDir()->size() > 1) {
		setAlive(false);
	}
	m_ticks_to_move--;
	if (m_ticks_to_move == 0) {
		std::cerr << "WALK STEP OVER" << std::endl;
		setRealX(getX());
		setRealY(getY());
		m_waiting_to_roll = true;
		m_ticks_stay = 0;
	}

}
vector<int>* Player::getPossibleDir() {
	std::vector<int>* validDir = new std::vector<int>();
	if (canMoveForward(left)) validDir->push_back(left);
	if (canMoveForward(right)) validDir->push_back(right);
	if (canMoveForward(up)) validDir->push_back(up);
	if (canMoveForward(down)) validDir->push_back(down);
	return validDir;
}
int Player::addCoins(int num) { 
	if (m_coin + num < 0) {
		int temp = m_coin;
		m_coin = 0;
		return -num - temp;
	}
	m_coin += num;
	return 0;
}
void Player::addStars(int num) { m_star += num; }
int Player::getMoves() { return m_ticks_to_move; }

bool Square::isFirstOverlapping(Player* player) {
	int x = getX();
	int y = getY();
	int otherX = player->getX();
	int otherY = player->getY();

	x -= otherX;
	y -= otherY;

	if (x < SPRITE_WIDTH && x > -SPRITE_WIDTH && y <SPRITE_HEIGHT && y > -SPRITE_HEIGHT) {
		int overlappingTime = getOverlappingTime(player->getPlayer());
		setOverlappingTime(player->getPlayer(), overlappingTime + 1);
		if (overlappingTime == 0) { return true; }
		else { return false;  }
	}
	else {
		setOverlappingTime(player->getPlayer(), 0);
		return false;
	}
	
}
int Square::getOverlappingTime(int playerNum) const {
	if (playerNum == 1) return m_overlapping1;
	else return m_overlapping2;
}
void Square::setOverlappingTime(int playerNum, int num) {
	if (playerNum == 1) m_overlapping1 = num;
	else m_overlapping2 = num;
}
bool Square::isLandedOn(Player* player) const {
	return (player->getRealX() == getRealX() && player->getRealY() == getRealY() && player->getStayTime() == 0);
}
bool Square::isPassingThrough(Player* player) const {
	return (player->getRealX() == getRealX() && player->getRealY() == getRealY());
}

void Square::doSomething() {
	interactWith(getWorld()->getPlayer1());
	interactWith(getWorld()->getPlayer2());
}


//Coin
void CoinSquare::doSomething() {

}
//
void BlueCoinSquare::interactWith(Player* player) {
	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(3);
		getWorld()->playSound(SOUND_GIVE_COIN);
	}
}
void RedCoinSquare::interactWith(Player* player) {
	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(-3); 
		getWorld()->playSound(SOUND_TAKE_COIN);
	}
}
void StarSquare::interactWith(Player* player) {
	if (isFirstOverlapping(player) && player->getCoins() >= 20) {
		player->addCoins(-20);
		player->addStars(1);
		getWorld()->playSound(SOUND_GIVE_STAR);
		std::cerr << "GET A STAR" << std::endl;
	}
}
void DirectionalSquare::interactWith(Player* player) {
	if (isPassingThrough(player)) {
		player->setWalkDirection(m_forcing_dir);
		player->updateSpriteDirection();
		player->setAlive(true);
		std::cerr << "Changed direction: " << player1->getWalkDirection() << std::endl;
	}
}

void CentralBank::deposit(int num) {
	m_money += num;
}
int CentralBank::withdraw() {
	int money = m_money;
	m_money = 0;
	return money;
}

CentralBank* BankSquare::getBank() {
	return m_bank;
}

void EventSquare::doSomething() {
	Player* player1 = getWorld()->getPlayer1();
	Player* player2 = getWorld()->getPlayer2();

	if (isLandedOn(player1)) {
		int rand = randInt(1, 3);
		if (rand == 1) { teleport(player1); }
		else if (rand == 2) {
			swapPlayers(player1, player2);
		}
		else {
			giveGun(player1);
		}
	}

}
void EventSquare::teleport(Player* player) {
	//player->moveTo(1, 1);
	getWorld()->playSound(SOUND_PLAYER_TELEPORT);
	std::cerr << "Teleport" << std::endl;
}
void EventSquare::swapPlayers(Player* player1, Player* player2) {
	player1->swap(*player2);
	getWorld()->playSound(SOUND_PLAYER_TELEPORT);
	std::cerr << "Swap" << std::endl;
}
void EventSquare::giveGun(Player* player) {
	//Vortex gun = new Vortex();
	getWorld()->playSound(SOUND_GIVE_VORTEX);
	std::cerr << "Get Vortex" << std::endl;
}

void Baddie::teleport() {

}
void Baddie::doSomething() {

}

void Bowser::doSomething() {

}

void Boo::doSomething() {
}
