#include "Tile.h"

// creating a tile
Tile::Tile(float x, float y, int Row, int Col) {
	mine = false; nearbyBombs = 0; flag = false; revealed = false; row = Row; col = Col;
	xCoord = x; yCoord = y;
	tileSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	tileSprite.setPosition(xCoord, yCoord);
	mineSprite.setTexture(TextureManager::GetTexture("mine"));
	mineSprite.setPosition(xCoord, yCoord);
	flagSprite.setTexture(TextureManager::GetTexture("flag"));
	flagSprite.setPosition(xCoord, yCoord);
}

// set functions
void Tile::setCoords(float x, float y) {
	xCoord = x;
	yCoord = y;
}
void Tile::setMineStatus(bool status) {
	mine = status;
}
void Tile::setNearbyMines(int bombs) {
	nearbyBombs = bombs;
}
void Tile::setSprite(string texture) {
	tileSprite.setTexture(TextureManager::GetTexture(texture));
	tileSprite.setPosition(xCoord, yCoord);
}
void Tile::setRevealStatus(bool status) {
	revealed = status;
}
void Tile::setFlagStatus(bool status) {
	flag = status;
}
void Tile::setNearbyMineSprite(string texture) {
	nearbyMineSprite.setTexture(TextureManager::GetTexture(texture));
	nearbyMineSprite.setPosition(xCoord, yCoord);
}

// get functions
bool Tile::getMineStatus() {
	return mine;
}
bool Tile::getFlagStatus() {
	return flag;
}
bool Tile::getRevealStatus() {
	return revealed;
}
int Tile::getNearbyMines() {
	return nearbyBombs;
}
float Tile::getXCoord() {
	return xCoord;
}
float Tile::getYCoord() {
	return yCoord;
}
int Tile::getRow() {
	return row;
}
int Tile::getCol() {
	return col;
}
sf::Sprite Tile::getTileSprite() {
	return tileSprite;
}
sf::Sprite Tile::getMineSprite() {
	return mineSprite;
}
sf::Sprite Tile::getFlagSprite() {
	return flagSprite;
}
sf::Sprite Tile::getNearbyMineSprite() {
	return nearbyMineSprite;
}