#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor getter


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
	case 180:  newX -= distance; break;
	case 0: newX += distance; break;
	case 90:    newY += distance; break;
	case 270:  newY -= distance; break;
	}
}
// Actor setter
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
	if (getWalkDirection() == 180) { setDirection(180); }
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
//Player setter
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

		if (action == ACTION_LEFT && canMoveForward(180)) { setWalkDirection(180); }
		else if (action == ACTION_RIGHT && canMoveForward(0)) { setWalkDirection(0); }
		else if (action == ACTION_UP && canMoveForward(90)) { setWalkDirection(90); }
		else if (action == ACTION_DOWN && canMoveForward(270)) { {setWalkDirection(270); } }
		else {
			setAlive(false);
			return;
		}
	}
	int dir = getWalkDirection();
	std::cerr << dir << std::endl;
	if (!canMoveForward(dir)) {
		if (dir == 180 || dir == 0) { canMoveForward(90) ? setWalkDirection(90) : setWalkDirection(270); }
		else { canMoveForward(0) ? setWalkDirection(0) : setWalkDirection(180); }

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
//Player getter
int Player::getPlayer() const {
	return m_player_number;
}
int Player::getStayTime() const { return m_ticks_stay; }
int Player::getCoins() const { return m_coin; }
int Player::getStars() const { return m_star; }
bool Player::canMoveForward(int dir) const {
	int face = getWalkDirection();
	int back = 0;
	if (face == 180) back = 0;
	else if (face == 0) back = 180;
	else if (face == 90) back = 270;
	else back = 90;

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
vector<int>* Player::getPossibleDir() const {
	std::vector<int>* validDir = new std::vector<int>();
	if (canMoveForward(180)) validDir->push_back(180);
	if (canMoveForward(0)) validDir->push_back(0);
	if (canMoveForward(90)) validDir->push_back(90);
	if (canMoveForward(270)) validDir->push_back(270);
	return validDir;
}
int Player::getMoves() const { return m_ticks_to_move; }
//Sqaure setter
void Square::doSomething() {
	interactWith(getWorld()->getPlayer1());
	interactWith(getWorld()->getPlayer2());
}
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
void Square::setOverlappingTime(int playerNum, int num) {
	if (playerNum == 1) m_overlapping1 = num;
	else m_overlapping2 = num;
}
//Sqaure getter
int Square::getOverlappingTime(int playerNum) const {
	if (playerNum == 1) return m_overlapping1;
	else return m_overlapping2;
}
bool Square::isLandedOn(Player* player) const {
	return (player->getRealX() == getRealX() && player->getRealY() == getRealY() && player->getStayTime() == 0);
}
bool Square::isPassingThrough(Player* player) const {
	return (player->getRealX() == getRealX() && player->getRealY() == getRealY());
}

void BlueCoinSquare::interactWith(Player* player) {
	if (!isAlive()) return;
	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(3);
		getWorld()->playSound(SOUND_GIVE_COIN);
	}
}
void RedCoinSquare::interactWith(Player* player) {
	if (!isAlive()) return;
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
		std::cerr << "Changed direction: " << player->getWalkDirection() << std::endl;
	}
}
void BankSquare::interactWith(Player* player) {
	if (isFirstOverlapping(player)) {
		int deficit = player->addCoins(-5);
		getBank()->deposit(5-deficit);
		std::cerr << "Deposit money: " << 5 - deficit << std::endl;
	}

	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(getBank()->withdraw() && player->getStayTime() == 0);
		std::cerr << "Get all money" << std::endl;
	}
}
void EventSquare::interactWith(Player* player) {
	if (isLandedOn(player)) {
		int rand = randInt(1, 3);
		if (rand == 1) { teleport(player); }
		else if (rand == 2) {
			swapPlayers();
		}
		else {
			giveGun(player);
		}
	}

}
void EventSquare::teleport(Player* player) {
	//player->moveTo(1, 1);
	getWorld()->playSound(SOUND_PLAYER_TELEPORT);
	std::cerr << "Teleport" << std::endl;
}
void EventSquare::swapPlayers() {
	Player* player1 = getWorld()->getPlayer1();
	Player* player2 = getWorld()->getPlayer2();
	player1->swap(*player2);
	getWorld()->playSound(SOUND_PLAYER_TELEPORT);
	//std::cerr << "Swap" << std::endl;
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