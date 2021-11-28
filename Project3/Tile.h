#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Tile {
private:
	bool mine;
	bool flag;
	bool revealed;
	int nearbyBombs;
	int row;
	int col;
	float xCoord;
	float yCoord;
	sf::Sprite tileSprite;
	sf::Sprite mineSprite;
	sf::Sprite flagSprite;
	sf::Sprite nearbyMineSprite;
public:
	Tile(float x, float y, int Row, int Col);

	// set functions
	void setMineStatus(bool status);
	void setCoords(float x, float y);
	void setNearbyMines(int bombs);
	void setSprite(string texture);
	void setRevealStatus(bool status);
	void setFlagStatus(bool status);
	void setNearbyMineSprite(string texture);

	// get functions
	bool getFlagStatus();
	bool getRevealStatus();
	bool getMineStatus();
	int getNearbyMines();
	float getXCoord();
	float getYCoord();
	sf::Sprite getTileSprite();
	sf::Sprite getMineSprite();
	sf::Sprite getFlagSprite();
	sf::Sprite getNearbyMineSprite();
	int getRow();
	int getCol();
};
