#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <vector>
#include <string>
#include "Button.h"
#include "MineCounter.h"
#include <fstream>

using namespace std;

class Board {
private:
	int numCol;
	int numRow;
	int mineCount;
	int configMineCount;
	int tileCount;
	int width;
	int height;
	int numFlags;
	int numMinesLeft;
	bool negativeCounter;
	vector<vector<Tile>> tiles;
	// Buttons Index: 0 = test_1; 1 = test_2; 2 = test_3; 3 = face (happy/sad/win will be determined by whether its type is 3/4/5); 4 = debug;
	vector<Button> buttons;
	vector<MineCounter> mineCounterDigits;
	sf::Sprite negativeSign;

	
public:
	void initializeGameBoard(int NumCol, int NumRow, int MineCount, int TileCount);
	void initializeButtons();
	void initializeMines();
	void findNearbyMines();
	void resetBoard();
	int getNumRows();
	int getNumCols();
	int getWidth();
	int getHeight();
	vector<vector<Tile>>& getTiles();
	vector<Button>& getButtons();
	vector<MineCounter>& getCounterDigits();
	void updateCounter(vector<MineCounter>& mineCounterDigits);
	void addFlag();
	void removeFlag();
	void resetFlags();
	bool isNegativeCounter();
	void loadTestBoard(string fileName);
	sf::Sprite getNegativeSign();
};

