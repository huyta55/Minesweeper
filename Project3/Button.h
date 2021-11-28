#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Button {
protected:
	float xCoord;
	float yCoord;
	sf::Sprite sprite;
	// Button types: 0 = test_1; 1 = test_2; 2 = test_3; 3 = face_happy; 4 = face_lose; 5 = face_win; 6 = debug;
private:
	int type;
public:
	Button();
	Button(int Type, int numRow, int numCol);
	void setSprite(string texture);
	sf::Sprite getSprite();
};

