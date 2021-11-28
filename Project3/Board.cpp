#include "Board.h"
#include "RandomGenerator.h"

// Initialization Functions
void Board::initializeGameBoard(int NumCol, int NumRow, int MineCount, int TileCount) {
	numCol = NumCol; numRow = NumRow; mineCount = MineCount; tileCount = TileCount; configMineCount = mineCount;
	// Dividing the board into tiles and then storing them
	// For each row of tiles, store the column tiles in a vector of tiles
	width = numCol * 32;
	height = (numRow * 32) + 88;
	int x = 0; int y = 0;
	for (int currentRow = 0; currentRow < numRow; currentRow++) {
		x = 0;
		vector<Tile> newRow;
		tiles.push_back(newRow);
		for (int currentCol = 0; currentCol < numCol; ++currentCol) {
			Tile newTile = Tile(x, y, currentRow, currentCol);
			tiles[currentRow].push_back(newTile);
			x += 32;
		}
		y += 32;
	}
}
void Board::initializeButtons() {
	// Using for loop to create the buttons and their type
	for (int i = 0; i < 5; ++i) {
		Button newButton = Button(i, numRow, numCol);
		buttons.push_back(newButton);
	}
	// Initializing the mineCounter
	negativeCounter = false;
	for (int i = 1; i < 4; ++i) {
		MineCounter newDigit = MineCounter(i, numRow, numCol, mineCount);
		mineCounterDigits.push_back(newDigit);
	}
	negativeSign.setTexture(TextureManager::GetTexture("digits"));
	negativeSign.setTextureRect(sf::IntRect(210, 0, 21, 32));
	negativeSign.setPosition(0.0, numRow * 32.0);
}
void Board::resetBoard() {
	// Iterating through each of the tiles and resetting them
	for (int row = 0; row < numRow; row++) {
		for (int col = 0; col < numCol; col++) {
			Tile& currentTile = tiles[row][col];
			currentTile.setFlagStatus(false);
			currentTile.setMineStatus(false);
			currentTile.setNearbyMines(0);
			currentTile.setRevealStatus(false);
			currentTile.setSprite("tile_hidden");
		}
	}
	numFlags = 0;
	// Resetting sprite of Face button
	buttons[3].setSprite("face_happy");
	mineCount = configMineCount;
}
void Board::initializeMines() {
	// Generating the mines and updating the status of tiles that the bombs are placed on
	float bombRow; float bombCol;
	for (int i = 0; i < mineCount; ++i) {
		while (true) {
			bombRow = RandomGenerator::Float(0.0, numRow);
			bombCol = RandomGenerator::Float(0.0, numCol);
			// if the title generated doesn't have a bomb, put a bomb there and break out to go to next bomb, else generate again
			if (tiles[bombRow][bombCol].getMineStatus() == false) {
				tiles[bombRow][bombCol].setMineStatus(true);
				break;
			}
		}

	}
}
void Board::findNearbyMines() {
	int numMines = 0;
	for (int row = 0; row < numRow; ++row) {
		for (int col = 0; col < numCol; ++col) {
			if (tiles[row][col].getMineStatus() == false) {
				numMines = 0;
				// 1 2 3
				// 8   4
				// 7 6 5
				// top row
				if (row == 0) {
					// top left corner
					if (col == 0) {
						// checks 4-6 for bombs
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
						if (tiles[row + 1][col + 1].getMineStatus()) {
							numMines++;
						}
					}
					// top right corner
					else if (col == numCol - 1) {
						// checks 6-8 for bombs
						// 6
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
						// 7
						if (tiles[row + 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 8
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}


					}
					// every other column in top row
					else {
						// checks 4-8 for bombs
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
						if (tiles[row + 1][col + 1].getMineStatus()) {
							numMines++;
						}
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}
						if (tiles[row + 1][col - 1].getMineStatus()) {
							numMines++;
						}
					}
				}
				// bottom row
				else if (row == numRow - 1) {
					// bottom left corner
					if (col == 0) {
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 3
						if (tiles[row - 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 4
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
					}
					// bottom right corner
					else if (col == numCol - 1) {
						// 1
						if (tiles[row - 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 8
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}
					}
					// every other column in bottom row
					else {
						// 1
						if (tiles[row - 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 3
						if (tiles[row - 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 4
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
						// 8
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}
					}
				}
				// every row in b/w
				else {
					// far left column
					if (col == 0) {
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 3
						if (tiles[row - 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 4
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
						// 5
						if (tiles[row + 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 6
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
					}
					// far right column
					else if (col == numCol - 1) {
						// 1
						if (tiles[row - 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 6
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
						// 7
						if (tiles[row + 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 8
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}
					}

					// every other column in row
					else {
						// 1
						if (tiles[row - 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 2
						if (tiles[row - 1][col].getMineStatus()) {
							numMines++;
						}
						// 3
						if (tiles[row - 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 4
						if (tiles[row][col + 1].getMineStatus()) {
							numMines++;
						}
						// 5
						if (tiles[row + 1][col + 1].getMineStatus()) {
							numMines++;
						}
						// 6
						if (tiles[row + 1][col].getMineStatus()) {
							numMines++;
						}
						// 7
						if (tiles[row + 1][col - 1].getMineStatus()) {
							numMines++;
						}
						// 8
						if (tiles[row][col - 1].getMineStatus()) {
							numMines++;
						}

					}
				}

				// Adjusting the tile's nearby mine count to the number of mines found
				tiles[row][col].setNearbyMines(numMines);
			}
		}
	}
}
void Board::addFlag() {
	numFlags++;
	updateCounter(mineCounterDigits);
}
void Board::removeFlag() {
	numFlags--;
	updateCounter(mineCounterDigits);
}
void Board::resetFlags() {
	numFlags = 0;
}
void Board::updateCounter(vector<MineCounter>& mineCounterDigits) {
	int temp = numMinesLeft = mineCount - numFlags;
	if (temp < 0) {
		temp *= -1;
		negativeCounter = true;
	}
	else {
		negativeCounter = false;
	}
	if (temp > 99) {
		mineCounterDigits[0].setDigit(temp / 100);
		mineCounterDigits[1].setDigit((temp % 100) / 10);
		mineCounterDigits[2].setDigit(temp % 10);
	}
	else if (temp > 9) {
		mineCounterDigits[0].setDigit(0);
		mineCounterDigits[1].setDigit(temp / 10);
		mineCounterDigits[2].setDigit(temp % 10);
	}
	else {
		mineCounterDigits[0].setDigit(0);
		mineCounterDigits[1].setDigit(0);
		mineCounterDigits[2].setDigit(temp);
	}
	// updating the sprite of the digits
	mineCounterDigits[0].loadSpriteNumber(mineCounterDigits[0].getDigit());
	mineCounterDigits[1].loadSpriteNumber(mineCounterDigits[1].getDigit());
	mineCounterDigits[2].loadSpriteNumber(mineCounterDigits[2].getDigit());
}
void Board::loadTestBoard(string fileName) {
	int tempMineCount = 0;
	string actualName = "boards/";
	actualName += (fileName + ".brd");
	ifstream inFile(actualName);
	string lineFromFile;
	for (int row = 0; row < 16; row++) {
		getline(inFile, lineFromFile);
		for (int col = 0; col < 25; col++) {
			// if the current character in the row is 1, then place a bomb in the corresponding tile
			if (lineFromFile[col] == '1') {
				tiles[row][col].setMineStatus(true);
				tempMineCount++;
			}
		}
		cout << endl;
	}
	mineCount = tempMineCount;
	updateCounter(mineCounterDigits);
	findNearbyMines();
}

int Board::getNumCols() {
	return numCol;
}
int Board::getNumRows() {
	return numRow;
}
int Board::getWidth() {
	return width;
}
int Board::getHeight() {
	return height;
}
bool Board::isNegativeCounter() {
	return negativeCounter;
}
sf::Sprite Board::getNegativeSign() {
	return negativeSign;
}
vector<vector<Tile>>& Board::getTiles() {
	return tiles;
}
vector<Button>& Board::getButtons() {
	return buttons;
}
vector<MineCounter>& Board::getCounterDigits() {
	return mineCounterDigits;
}


