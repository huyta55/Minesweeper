#include "MineCounter.h"

MineCounter::MineCounter(int ID, int numRow, int numCol, int mineCount) {
	yCoord = numRow * 32.0;
	int Digit1; int Digit2; int Digit3;
	// Finding the digits of the minecount
	if (mineCount > 99) {
		Digit1 = (mineCount / 100);
		Digit2 = (mineCount % 100) / 10;
		Digit3 = mineCount % 10;
	}
	else if (mineCount > 9) {
		Digit1 = 0;
		Digit2 = mineCount / 10;
		Digit3 = mineCount % 10;
	}
	else {
		Digit1 = 0;
		Digit2 = 0;
		Digit3 = mineCount;
	}
	// Assigning the correct sprite depending on the digit
	if (ID == 1) {
		xCoord = 21.0;
		digit = Digit1;
	}
	else if (ID == 2) {
		xCoord = 42.0;
		digit = Digit2;
	}
	else {
		xCoord = 63.0;
		digit = Digit3;
	}
	loadSpriteNumber(digit);
}

void MineCounter::loadSpriteNumber(int num) {
	sprite.setTexture(TextureManager::GetTexture("digits"));
	sprite.setPosition(xCoord, yCoord);
	if (num == 0) {
		sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
	}
	else if (num == 1) {
		sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
	}
	else if (num == 2) {
		sprite.setTextureRect(sf::IntRect(42, 0, 21, 32));
	}
	else if (num == 3) {
		sprite.setTextureRect(sf::IntRect(63, 0, 21, 32));
	}
	else if (num == 4) {
		sprite.setTextureRect(sf::IntRect(84, 0, 21, 32));
	}
	else if (num == 5) {
		sprite.setTextureRect(sf::IntRect(105, 0, 21, 32));
	}
	else if (num == 6) {
		sprite.setTextureRect(sf::IntRect(126, 0, 21, 32));
	}
	else if (num == 7) {
		sprite.setTextureRect(sf::IntRect(147, 0, 21, 32));
	}
	else if (num == 8) {
		sprite.setTextureRect(sf::IntRect(168, 0, 21, 32));
	}
	else if (num == 9) {
		sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
	}
	else {
		sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
	}
}

int MineCounter::getDigit() {
	return digit;
}

void MineCounter::setDigit(int num) {
	digit = num;
}
