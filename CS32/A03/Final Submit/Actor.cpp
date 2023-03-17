#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


// ===========================================================================================================================
// ACTOR CLASS
// ===========================================================================================================================

// interact with whole world
StudentWorld* Actor::getWorld() const { return m_world; }
//	maintain alive status
bool Actor::isAlive() const { return m_alive; }
void Actor::setAlive(bool alive) { m_alive = alive; }
// check two actors' position realation
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
// ===========================================================================================================================
// CHARACTER CLASS (ALL MOVE STUFF) : Actor
// ===========================================================================================================================

// another position system to guide characters when they are moving
int Character::getRealX() const { return m_realX; }
int Character::getRealY() const { return m_realY; }
void Character::setRealX(int x) { m_realX = x; }
void Character::setRealY(int y) { m_realY = y; }
// maintaining walk direction
int Character::getWalkDirection() const { return m_walkDir; }
void Character::setWalkDirection(int dir) { m_walkDir = dir; }

// waiting or walking
bool Character::isWaiting() const { return m_waiting_to_roll; }
void Character::setWaiting(bool wait) { m_waiting_to_roll = wait; }

// help when characters' animations are moving
bool Character::isMoving() const { return m_moving; }

// get some status
bool Character::isImpactable()const { return m_impactable; }
bool Character::isSquare() const { return false; }

// a stay time counter to help characters not being actived by one square twice
int Character::getStayTime() const { return m_ticks_stay; }
void Character::setStayTime(int num) { m_ticks_stay = num; }

void Character::setMoves(int num) { m_ticks_to_move = num; }
void Character::setMoving(bool move) { m_moving = move; }

// maintain positions
void Character::updateRealPosition(){
	//getX() % SPRITE_WIDTH == 0 && getX() % SPRITE_HEIGHT == 0
	if (getWorld()->hasSquare(getX(),getY())) {
		setRealX(getX());
		setRealY(getY());
		//std::cerr << "Position UPDATED" << std::endl;
	}
}
void Character::updateSpriteDirection() {
	if (getWalkDirection() == 180) { setDirection(180); }
	else { setDirection(0); }
}
//count next square's position
void Character::getRealPositionInThisDirection(int angle, int distance, int& newX, int& newY) const {
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
//swap characters
void Character::swap(Character& other) {
	int temp = m_realX;
	m_realX = other.m_realX;
	other.m_realX = temp;
	temp = m_realY;
	m_realY = other.m_realY;
	other.m_realY = temp;
	temp = m_walkDir;
	m_walkDir = other.m_walkDir;
	other.m_walkDir = temp;


	bool waitingTemp = m_waiting_to_roll;
	m_waiting_to_roll = other.m_waiting_to_roll;
	other.m_waiting_to_roll = waitingTemp;

	int tempMoves = m_ticks_to_move;
	m_ticks_to_move = other.m_ticks_to_move;
	other.m_ticks_to_move = tempMoves;

	int tempStay = m_ticks_stay;
	m_ticks_stay = other.m_ticks_stay;
	other.m_ticks_stay = tempStay;


	updateSpriteDirection();
	other.updateSpriteDirection();

	int tempX = getX();
	int tempY = getY();

	moveTo(other.getX(), other.getY());
	other.moveTo(tempX, tempY);

}

// get possible direction
bool Character::canMoveForward(int dir) const {	// can move to next square
	int face = getWalkDirection();
	int back = 0;
	if (face == 180) back = 0;
	else if (face == 0) back = 180;
	else if (face == 90) back = 270;
	else back = 90;

	if (back == dir) {
		//std::cerr << "FACE " << face << std::endl;
		//std::cerr << "BACK " << back << std::endl;
		return false;
	}

	int x = getRealX();
	int y = getRealY();
	//std::cerr << "Face " << face << std::endl;

	getRealPositionInThisDirection(dir, SPRITE_HEIGHT, x, y);
	if (!getWorld()->hasSquare(x, y)) {
		//std::cerr << "CAN'T MOVE" << std::endl;
	}

	return getWorld()->hasSquare(x, y);
}
vector<int>* Character::getPossibleDir() const {
	std::vector<int>* validDir = new std::vector<int>();
	if (canMoveForward(180)) validDir->push_back(180);
	if (canMoveForward(0)) validDir->push_back(0);
	if (canMoveForward(90)) validDir->push_back(90);
	if (canMoveForward(270)) validDir->push_back(270);
	return validDir;
}
int Character::getMoves() const { return m_ticks_to_move; }

// teleport a character to a random square
void Character::randomTeleport() {
	Square* square = getWorld()->getRandomSquare();
	moveTo(square->getX(), square->getY());
	updateRealPosition();
	updateSpriteDirection();
	setStayTime(1);
}

// stub for future
void Character::impacted() {}

// ===========================================================================================================================
// PLAYER CLASS (PEACH AND YOSHI) : Character : Actor
// ===========================================================================================================================


// maintain coins
void Player::setCoins(int num) { m_coin = num; }
int Player::addCoins(int num) {
	if (m_coin + num < 0) {
		int temp = m_coin;
		m_coin = 0;
		return -num - temp;
	}
	m_coin += num;
	return 0;
}
int Player::getCoins() const { return m_coin; }
// maintain star
void Player::setStarts(int num) { m_star = num; }
void Player::addStars(int num) {
	if (m_star + num < 0) {
		m_star = 0;
		return;
	}
	m_star += num;
}
int Player::getStars() const { return m_star; }
// vortex
bool Player::hasVortex() const { return m_has_vortex; }
void Player::setVortex(bool vortex) { m_has_vortex = vortex; }
// moving
void Player::doSomething() {
	//std::cerr << "WORKING" << std::endl;
	if (isWaiting()) {
		setStayTime(getStayTime() + 1);
		//cerr << getStayTime() << endl;
		if (!canMoveForward(getWalkDirection())) {
			std::vector<int>* validDir = getPossibleDir();
			int rand = randInt(0, validDir->size()-1);
			setWalkDirection(validDir->at(rand));
			updateSpriteDirection();
		}
		int action = getWorld()->getAction(getPlayer());
		if (action == ACTION_ROLL) {
			//std::cerr << "WORKING" << std::endl;
			int die_roll = randInt(1, 10);	// random number from 1 to 10, inclusive
			setMoves(die_roll * 8);
			walkingStep();
			setWaiting(false);
		}
		else if (action == ACTION_FIRE) {
			if (hasVortex()) {
				cerr << "V" << endl;
				getWorld()->createVortex(getX(), getY(), getWalkDirection());
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				setVortex(false);
			}
			return;
		}
		else { return; }
	}
	else {
		walkingStep();
	}

}
void Player::walkingStep() {
	//cerr << "WALKING" << endl;
	if (!isMoving()) {	//alive for moving
		updateSpriteDirection();
		int action = getWorld()->getAction(getPlayer());
		setMoving(true);

		if (action == ACTION_LEFT && canMoveForward(180)) { setWalkDirection(180); }
		else if (action == ACTION_RIGHT && canMoveForward(0)) { setWalkDirection(0); }
		else if (action == ACTION_UP && canMoveForward(90)) { setWalkDirection(90); }
		else if (action == ACTION_DOWN && canMoveForward(270)) { {setWalkDirection(270); } }
		else {
			setMoving(false);
			return;
		}
	}
	int dir = getWalkDirection();
	//std::cerr << dir << std::endl;
	if (!canMoveForward(dir)) {
		if (dir == 180 || dir == 0) { canMoveForward(90) ? setWalkDirection(90) : setWalkDirection(270); }
		else { canMoveForward(0) ? setWalkDirection(0) : setWalkDirection(180); }
	}
	updateSpriteDirection();
	moveAtAngle(getWalkDirection(), 2);
	updateRealPosition();
	if (getWorld()->hasSquare(getX(), getY()) && getPossibleDir()->size() > 1) { setMoving(false); }
	setMoves(getMoves() - 1);
	if (getMoves() == 0) {
		std::cerr << "WALK STEP OVER" << std::endl;
		//setMoving(false);
		setRealX(getX());
		setRealY(getY());
		setWaiting(true);
		setStayTime(0);
	}

}
// get some status
int Player::getDices() const { return getMoves() / 8; }
int Player::getPlayer() const { return m_player_number; }

// ===========================================================================================================================
// BADDIE CLASS : Character : Actor
// ===========================================================================================================================

void Baddie::doSomething() {
	interactWith(getWorld()->getPlayer1());
	interactWith(getWorld()->getPlayer2());
	walkingStep();
}
void Baddie::impacted() {
	randomTeleport();
	setWalkDirection(right);
	updateSpriteDirection();
	setWaiting(true);
	setPauseCounter(180);
}
// maintain pause counter
void Baddie::setPauseCounter(int num){
	m_pause_counter = num;
}
int Baddie::getPauseCounter() const { return m_pause_counter; }

// ===========================================================================================================================
// BOWSER CLASS : Baddie : Character : Actor
// ===========================================================================================================================

void Bowser::walkingStep() {
	if (isWaiting()) {
		setPauseCounter(getPauseCounter() - 1);
		if (getPauseCounter() == 0) {
			//cerr << "PAUSE ENDED" << endl;
			int squares_to_move = randInt(1, 10);
			setMoves(squares_to_move * 8);
			std::vector<int>* possibleDir = getPossibleDir();
			int rdm = randInt(0, possibleDir->size() - 1);
			int dir = possibleDir->at(rdm);
			setWalkDirection(dir);
			updateSpriteDirection();
			setWaiting(false);
		}
	}
	if (!isWaiting()) {
		if (getWorld()->hasSquare(getX(), getY())) {
			if (getWorld()->hasSquare(getX(), getY()) && getPossibleDir()->size() > 1) {
				std::vector<int>* possibleDir = getPossibleDir();
				int rdm = randInt(0, possibleDir->size() - 1);
				setWalkDirection(possibleDir->at(rdm));
			}
			else if (!canMoveForward(getWalkDirection())) {
				int dir = getWalkDirection();
				if (dir == 180 || dir == 0) { canMoveForward(90) ? setWalkDirection(90) : setWalkDirection(270); }
				else { canMoveForward(0) ? setWalkDirection(0) : setWalkDirection(180); }
			}
		}
		updateSpriteDirection();
		moveAtAngle(getWalkDirection(), 2);
		updateRealPosition();

		setMoves(getMoves() - 1);
		if (getMoves() == 0) {
			cerr << "Broser Stoped" << endl;
			setWaiting(true);
			setPauseCounter(180);
			int rdm = randInt(0, 3);
			if (rdm == 0) {
				getWorld()->deleteAndReplaceSquare(getX(), getY());
				getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
			}
		}
	}
}
void Bowser::interactWith(Player* player) {
	if (isWaiting()) {
		if (isLandedOn(player) && player->isWaiting() && player->getStayTime() == 0) {
			int rdm = randInt(0, 1);
			if (rdm == 0) {
				player->addCoins(-1000000);
				player->addStars(-1000000);
				getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
			}
		}
    }
}

// ===========================================================================================================================
// BOO CLASS : Baddie : Character : Actor
// ===========================================================================================================================

void Boo::interactWith(Player* player){
	if (isWaiting()) {
		if (isLandedOn(player) && player->isWaiting() && player->getStayTime() == 0) {
			int rdm = randInt(0, 1);
			int curPlayerNumber = player->getPlayer();
			Player* other = curPlayerNumber == 1 ? getWorld()->getPlayer2() : getWorld()->getPlayer1();
			if (rdm == 0) {
				int temp = player->getCoins();
				player->setCoins(other->getCoins());
				other->setCoins(temp);
			}
			else {
				int temp = player->getStars();
				player->setStarts(other->getStars());
				other->setStarts(temp);
			}
			getWorld()->playSound(SOUND_BOO_ACTIVATE);
		}
	}
}
void Boo::walkingStep() {
	if (isWaiting()) {
		setPauseCounter(getPauseCounter() - 1);
		if (getPauseCounter() == 0) {
			int squares_to_move = randInt(1, 3);
			setMoves(squares_to_move * 8);
			std::vector<int>* possibleDir = getPossibleDir();
			int rdm = randInt(0, possibleDir->size() - 1);
			int dir = possibleDir->at(rdm);
			setWalkDirection(dir);
			updateSpriteDirection();
			setWaiting(false);
		}

	}
	else if (!isWaiting()) {
		if (getWorld()->hasSquare(getX(), getY())) {
			if (getWorld()->hasSquare(getX(), getY()) && getPossibleDir()->size() > 1) {
				std::vector<int>* possibleDir = getPossibleDir();
				int rdm = randInt(0, possibleDir->size() - 1);
				setWalkDirection(possibleDir->at(rdm));
			}
			else if (!canMoveForward(getWalkDirection())) {
				int dir = getWalkDirection();
				if (dir == 180 || dir == 0) { canMoveForward(90) ? setWalkDirection(90) : setWalkDirection(270); }
				else { canMoveForward(0) ? setWalkDirection(0) : setWalkDirection(180); }
			}
		}
		updateSpriteDirection();
		moveAtAngle(getWalkDirection(), 2);
		updateRealPosition();
		setMoves(getMoves() - 1);
		if (getMoves() == 0) {
			setWaiting(true);
			setPauseCounter(180);
		}


	}
}

// ===========================================================================================================================
// VORTEX CLASS : Character : Actor
// ===========================================================================================================================

void Vortex::doSomething() {
	if (!isAlive()) { return; }
	moveAtAngle(getDirection(), 2);
	if (getX() < 0 || getX() >= VIEW_WIDTH || getY() < 0 || getY() >= VIEW_HEIGHT) { setAlive(false); }

	int x = getX();
	int y = getY();
	getPositionInThisDirection(getDirection(), SPRITE_HEIGHT, x, y);
	Character* baddie = getWorld()->getCharacter(x, y);
	if (baddie != nullptr) { interactWith(baddie); }

}
void Vortex::interactWith(Character* character) {
	if (character->isImpactable()) {
		character->impacted();
		setAlive(false);
	}
}

// ===========================================================================================================================
// SQUARE CLASS (ALL STABLE STUFF)  : Actor
// ===========================================================================================================================

void Square::doSomething() {
	interactWith(getWorld()->getPlayer1());
	interactWith(getWorld()->getPlayer2());
}
bool Square::isSquare() const { return true; }

// maintain a counter to count whether this is the first time that a square passing through / overlapping with a player
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
		else { return false; }
	}
	else {
		setOverlappingTime(player->getPlayer(), 0);
		return false;
	}
}
bool Square::isFirstPassing(Player* player) {
	int x = getX();
	int y = getY();
	int otherX = player->getX();
	int otherY = player->getY();

	x -= otherX;
	y -= otherY;

	if (isPassingThrough(player)) {
		int overlappingTime = getOverlappingTime(player->getPlayer());
		setOverlappingTime(player->getPlayer(), overlappingTime + 1);
		if (overlappingTime == 0) { return true; }
		else { return false; }
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
int Square::getOverlappingTime(int playerNum) const {
	if (playerNum == 1) return m_overlapping1;
	else return m_overlapping2;
}

// check player is landeed on / passing through a square
bool Square::isLandedOn(Player* player) const {
	return (player->getRealX() == getX() && player->getRealY() == getY() && player->getStayTime() == 0);
}
bool Square::isPassingThrough(Player* player) const {
	return (player->getRealX() == getX() && player->getRealY() == getY());
}

// ===========================================================================================================================
// BLUE COIN SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void BlueCoinSquare::interactWith(Player* player) {
	if (!isAlive()) return;
	if (isLandedOn(player) && player->getStayTime() == 0) {
		cerr << "ADD COINS" << endl;
		player->addCoins(3);
		getWorld()->playSound(SOUND_GIVE_COIN);
	}
}

// ===========================================================================================================================
// RED COIN SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void RedCoinSquare::interactWith(Player* player) {
	if (!isAlive()) return;
	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(-3);
		getWorld()->playSound(SOUND_TAKE_COIN);
	}
}

// ===========================================================================================================================
// STAR SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void StarSquare::interactWith(Player* player) {
	if (isFirstOverlapping(player) && player->getCoins() >= 20) {
		player->addCoins(-20);
		player->addStars(1);
		getWorld()->playSound(SOUND_GIVE_STAR);
		std::cerr << "GET A STAR" << std::endl;
	}
}

// ===========================================================================================================================
// DIRECTIONAL SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void DirectionalSquare::interactWith(Player* player) {
	if (isPassingThrough(player)) {
		player->setWalkDirection(m_forcing_dir);
		player->updateSpriteDirection();
		player->setMoving(true);
		std::cerr << "Changed direction: " << player->getWalkDirection() << std::endl;
	}
}

// ===========================================================================================================================
// BANK SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void BankSquare::interactWith(Player* player) {
	if (isLandedOn(player) && player->getStayTime() == 0) {
		player->addCoins(getBank()->withdraw() && player->getStayTime() == 0);
		std::cerr << "Get all money" << std::endl;
		getWorld()->playSound(SOUND_WITHDRAW_BANK);
	}
	else if (isFirstPassing(player)) {
		int deficit = player->addCoins(-5);
		getBank()->deposit(5 - deficit);
		std::cerr << "Deposit money: " << 5 - deficit << std::endl;
		getWorld()->playSound(SOUND_DEPOSIT_BANK);
	}


}
// get bank class
CentralBank* BankSquare::getBank() { return m_bank; }
// ===========================================================================================================================
// EVENT SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

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
// three possible events
void EventSquare::teleport(Player* player) {
	//player->moveTo(1, 1);
	player->randomTeleport();
	getWorld()->playSound(SOUND_PLAYER_TELEPORT);
	//std::cerr << "Teleport" << std::endl;
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
	player->setVortex(true);
	getWorld()->playSound(SOUND_GIVE_VORTEX);
	std::cerr << "Get Vortex" << std::endl;
}

// ===========================================================================================================================
// DROPPING SQUARE CLASS : SQUARE : Actor
// ===========================================================================================================================

void DroppingSquare::interactWith(Player* player) {
	if (isLandedOn(player)) {
		int rdm = randInt(0, 1);
		if (rdm == 0) {
			player->addCoins(-10);
		}
		else {
			player->addStars(-1);
		}
		getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
	}
}

// ===========================================================================================================================
// CENTRAL BANK
// ===========================================================================================================================

void CentralBank::deposit(int num) {
	m_money += num;
}
int CentralBank::withdraw() {
	int money = m_money;
	m_money = 0;
	return money;
}
int CentralBank::getMoney() {
	return m_money;
}

