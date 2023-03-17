#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

StudentWorld* Actor::getWorld() { return m_world; }
const int Actor::getWalkDirection() { return m_walkDir; }
void Actor::setWalkDirection(int dir) { m_walkDir = dir; }
const bool Actor::isOverlap(const Actor& other) { return false; }	//stub
const bool Actor::isLandedOn(const Actor& other) { return (other.getX() == getX()) && (other.getY() == getY()); }
void Actor::doSomething() { return; }

//const int Empty::getID() { return IID_; }

void Player::doSomething() {
	if (m_waiting_to_roll) {
		m_ticks_stay++;
		if (!canMoveForward(getWalkDirection())) {
			std::vector<int>* validDir = new std::vector<int>();
			if (canMoveForward(left)) validDir->push_back(left);
			if (canMoveForward(right)) validDir->push_back(right);
			if (canMoveForward(up)) validDir->push_back(up);
			if (canMoveForward(down)) validDir->push_back(down);
			int rand = randInt(0, validDir->size() - 1);
			setWalkDirection(validDir->at(rand));
			updateSpriteDirection();
		}
		int action = getWorld()->getAction(getNumber());
		if (action == ACTION_ROLL) {
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

}

void Player::updateSpriteDirection() {
	if (getWalkDirection() == left) { setDirection(180); }
	else { setDirection(0); }
}

void Player::walkingStep() {
	int dir = getWalkDirection();
	if (!canMoveForward(dir)) {
		if (dir == left || dir == right) { canMoveForward(up) ? setWalkDirection(up) : setWalkDirection(down); }
		else { canMoveForward(right) ? setWalkDirection(right) : setWalkDirection(left); }
		updateSpriteDirection();
	}
	moveAtAngle(getWalkDirection(), 2);
	m_ticks_to_move--;
	if (m_ticks_to_move == 0) {
		m_waiting_to_roll = true;
		m_ticks_stay = 0;
	}
}

int Player::getNumber() {
	return m_player_number;
}

bool Player::canMoveForward(int dir) {
	int x = getX();
	int y = getY();
	getPositionInThisDirection(dir, 1, x, y);
	return true;//getWorld()->hasSquare(x, y);
}

void Player::addCoins(int num) { m_coin += num; }

int Player::getMoves() { return m_ticks_to_move; }

const bool Square::isAlive() { return m_alive; }

void Square::setAlive(bool alive) { m_alive = alive; }

void CoinSquare::doSomething() {
	if (!isAlive()) return;
	/*
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
	*/
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
