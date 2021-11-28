#include "Button.h"

Button::Button() {
	type = -1;
	xCoord = 0.00;
	yCoord = 0.00;
}
Button::Button(int Type, int numRow, int numCol) {
	type = Type;
	int width = numCol * 32;
	int height = numRow * 32;
	if (type == 0) {
		xCoord =  (width / 2.0) + 160;
		yCoord = height;
		setSprite("test_1");
	}
	else if (type == 1) {
		xCoord = (width / 2.0) + 224;
		yCoord = height;
		setSprite("test_2");
	}
	else if (type == 2) {
		xCoord = (width / 2.0) + 288;
		yCoord = height;
		setSprite("test_3");
	}
	else if (type == 3) {
		xCoord = (width / 2.0) - 32;
		yCoord = height;
		setSprite("face_happy");
	}
	else {
		xCoord = (width / 2.0) + 96;
		yCoord = height;
		setSprite("debug");
	}
}

void Button::setSprite(string texture) {
	sprite.setTexture(TextureManager::GetTexture(texture));
	sprite.setPosition(xCoord, yCoord);
}
sf::Sprite Button::getSprite() {
	return sprite;
}