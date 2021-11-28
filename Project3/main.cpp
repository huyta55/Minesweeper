#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Board.h"
#include "RandomGenerator.h"

using namespace std;

void readBoardConfig(Board& gameBoard, vector<int>& gameDimensions) {
    ifstream inFile("boards/config.cfg");
    string lineFromFile;
    vector<int> boardDimensions;
    for (int i = 0; i < 3; ++i) {
        getline(inFile, lineFromFile);
        int temp = stoi(lineFromFile);
        boardDimensions.push_back(temp);

    }
    int numCol = boardDimensions[0];
    int width = boardDimensions[0] * 32;
    int numRow = boardDimensions[1];
    int height = (boardDimensions[1] * 32) + 88;
    int mineCount = boardDimensions[2];
    int tileCount = boardDimensions[0] * boardDimensions[1];
    gameDimensions.push_back(width); gameDimensions.push_back(height);
    gameBoard.initializeGameBoard(numCol, numRow, mineCount, tileCount);
    gameBoard.initializeButtons();
    gameBoard.initializeMines();
    gameBoard.findNearbyMines();
}
void loadAllTextures() {
    TextureManager::GetTexture("debug");
    TextureManager::GetTexture("digits");
    TextureManager::GetTexture("face_happy");
    TextureManager::GetTexture("face_lose");
    TextureManager::GetTexture("face_win");
    TextureManager::GetTexture("flag");
    TextureManager::GetTexture("mine");
    TextureManager::GetTexture("number_1");
    TextureManager::GetTexture("number_2");
    TextureManager::GetTexture("number_3");
    TextureManager::GetTexture("number_4");
    TextureManager::GetTexture("number_5");
    TextureManager::GetTexture("number_6");
    TextureManager::GetTexture("number_7");
    TextureManager::GetTexture("number_8");
    TextureManager::GetTexture("test_1");
    TextureManager::GetTexture("test_2");
    TextureManager::GetTexture("test_3");
    TextureManager::GetTexture("tile_hidden");
    TextureManager::GetTexture("tile_revealed");
}
void leftClickTile(Board& gameBoard, Tile& currentTile) {
    // Checks that the title doesn't have a flag on it and isn't a bomb and isn't already revealed
    if ((currentTile.getFlagStatus() == false) && (currentTile.getMineStatus() == false) && (currentTile.getRevealStatus() == false)) {
        vector<vector<Tile>>& tiles = gameBoard.getTiles();
        currentTile.setRevealStatus(true);
        currentTile.setSprite("tile_revealed");
        int row = currentTile.getRow(); int col = currentTile.getCol();

        // if the tile has no bombs nearby, reveal other tiles around it , and repeat until every adjacent is revealed/has a nearby bomb/ has a flag
        if (currentTile.getNearbyMines() == 0) {
            // 1 2 3
            // 8   4
            // 7 6 5
            // top row
            if (row == 0) {
                // top left corner
                if (col == 0) {
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                    // 5
                    leftClickTile(gameBoard, tiles[row + 1][col + 1]);
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                }
                // top right corner
                else if (col == gameBoard.getNumCols() - 1) {
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                    // 7
                    leftClickTile(gameBoard, tiles[row + 1][col - 1]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
                // every other column in top row
                else {
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                    // 5
                    leftClickTile(gameBoard, tiles[row + 1][col + 1]);
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                    // 7
                    leftClickTile(gameBoard, tiles[row + 1][col + 1]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
            }
            // bottom row
            else if (row == gameBoard.getNumRows() - 1) {
                // bottom left corner
                if (col == 0) {
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 3
                    leftClickTile(gameBoard, tiles[row - 1][col + 1]);
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                }
                // bottom right corner
                else if (col == gameBoard.getNumCols() - 1) {
                    // 1
                    leftClickTile(gameBoard, tiles[row - 1][col - 1]);
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
                // every other column in bottom row
                else {
                    // 1
                    leftClickTile(gameBoard, tiles[row - 1][col - 1]);
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 3
                    leftClickTile(gameBoard, tiles[row - 1][col + 1]);
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
            }
            // every row in b/w
            else {
                // far left column
                if (col == 0) {
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 3
                    leftClickTile(gameBoard, tiles[row - 1][col + 1]);
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                    // 5
                    leftClickTile(gameBoard, tiles[row + 1][col + 1]);
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                }
                // far right column
                else if (col == gameBoard.getNumCols() - 1) {
                    // 1
                    leftClickTile(gameBoard, tiles[row - 1][col - 1]);
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                    // 7
                    leftClickTile(gameBoard, tiles[row + 1][col - 1]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
                // every other column in row
                else {
                    // 1
                    leftClickTile(gameBoard, tiles[row - 1][col - 1]);
                    // 2
                    leftClickTile(gameBoard, tiles[row - 1][col]);
                    // 3
                    leftClickTile(gameBoard, tiles[row - 1][col + 1]);
                    // 4 
                    leftClickTile(gameBoard, tiles[row][col + 1]);
                    // 5
                    leftClickTile(gameBoard, tiles[row + 1][col + 1]);
                    // 6
                    leftClickTile(gameBoard, tiles[row + 1][col]);
                    // 7
                    leftClickTile(gameBoard, tiles[row + 1][col - 1]);
                    // 8
                    leftClickTile(gameBoard, tiles[row][col - 1]);
                }
            }
            
        }
        
        // else just set the tile to revealed and with the corresponding number on it
            
        else {
            int mines = currentTile.getNearbyMines();
            switch (mines) {
            case 1:
                currentTile.setNearbyMineSprite("number_1");
                break;
            case 2:
                currentTile.setNearbyMineSprite("number_2");
                break;
            case 3:
                currentTile.setNearbyMineSprite("number_3");
                break;
            case 4:
                currentTile.setNearbyMineSprite("number_4");
                break;
            case 5:
                currentTile.setNearbyMineSprite("number_5");
                break;
            case 6: 
                currentTile.setNearbyMineSprite("number_6");
                break;
            case 7:
                currentTile.setNearbyMineSprite("number_7");
                break;
            case 8:
                currentTile.setNearbyMineSprite("number_8");
                break;
            default:
                currentTile.setNearbyMineSprite("tile_revealed");
                break;
            }
        }
    }

}
void rightClickTile(Board& gameBoard, Tile& currentTile) {
    // checking that the tile hasnt been revealed
    if (currentTile.getRevealStatus() == false) {
        // if the tile currently has a flag, remove it, if not then add a flag
        if (currentTile.getFlagStatus()) {
            currentTile.setFlagStatus(false);
            gameBoard.removeFlag();
        }
        else {
            currentTile.setFlagStatus(true);
            gameBoard.addFlag();
        }
    }
}
void displayBoard(Board& gameBoard, sf::RenderWindow& game, bool debugMode, bool Lose) {
    // Drawing the sprite of the titles in the board
    for (int row = 0; row < gameBoard.getNumRows(); row++) {
        for (int col = 0; col < gameBoard.getNumCols(); col++) {
            Tile& currentTile = gameBoard.getTiles()[row][col];
            game.draw(currentTile.getTileSprite());
            // If there is a flag at the current tile, print the flag on top of the tile
            if (currentTile.getFlagStatus()) {
                game.draw(currentTile.getFlagSprite());
            }
            // If game is in debug mode or lost, print the mines on top of the tiles they currently are at
            if (debugMode || Lose) {
                if (currentTile.getMineStatus()) {
                    game.draw(currentTile.getMineSprite());
                }
            }
            // if the tile has nearby bombs and is revealed, print the number on top of the sprite
            if ((currentTile.getNearbyMines() != 0) && (currentTile.getRevealStatus())) {
                game.draw(currentTile.getNearbyMineSprite());
            }
        }
    }
    // Drawing the different buttons
    for (int currentButton = 0; currentButton < 5; ++currentButton) {
        game.draw(gameBoard.getButtons()[currentButton].getSprite());
    }
    // Drawing the mine counter
    for (int currentDigit = 0; currentDigit < 3; ++currentDigit) {
        game.draw(gameBoard.getCounterDigits()[currentDigit].getSprite());
    }
    // If the mine counter is negative, add the extra negative

    if (gameBoard.isNegativeCounter() == true) {

        game.draw(gameBoard.getNegativeSign());
    }
    
    
    game.display();
}
bool checkWin(Board& gameBoard) {
    // if every tile is either a mine or revealed, then the game is won
    bool win = true;
    for (int row = 0; row < gameBoard.getNumRows(); row++) {
        for (int col = 0; col < gameBoard.getNumCols(); col++) {
            Tile& currentTile = gameBoard.getTiles()[row][col];
            if ((currentTile.getMineStatus() == false) && (currentTile.getRevealStatus() == false)) {
                win = false;
            }
        }
    }
    // adding flags to all the bomb slots
    if (win) {
        gameBoard.resetFlags();
        for (int row = 0; row < gameBoard.getNumRows(); row++) {
            for (int col = 0; col < gameBoard.getNumCols(); col++) {
                Tile& currentTile = gameBoard.getTiles()[row][col];
                if (currentTile.getMineStatus()) {
                    currentTile.setFlagStatus(true);
                    gameBoard.addFlag();
                }
            }
        }
    }
    return win;
}
void loadBoard(int boardNum, Board& gameBoard) {
    // 1,2,3 = respective boards; 4 = lots_o_mines; 5 = recursion_test.brd
    if (boardNum == 1) {
        gameBoard.loadTestBoard("testboard1");
    }
    else if (boardNum == 2) {
        gameBoard.loadTestBoard("testboard2");
    }
    else if (boardNum == 3) {
        gameBoard.loadTestBoard("testboard3");
    }
    else if (boardNum == 4) {
        gameBoard.loadTestBoard("lots_o_mines");
    }
    else if (boardNum == 5) {
        gameBoard.loadTestBoard("recursion_test");
    }
}


int main() {

    // Loading all the textures for the minesweeper game
    loadAllTextures();
    // Loading config file and creating the window for game based on the config
    vector<int> gameDimensions;
    Board gameBoard;
    bool debugMode = false;
    bool Win = false;
    bool Lose = false;
    readBoardConfig(gameBoard, gameDimensions);
    
    sf::RenderWindow game(sf::VideoMode(gameDimensions[0], gameDimensions[1]), "Minesweeper");

    //////////---------- End of Initializiation ---------//////////

    // Starts the game
    while (game.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        game.clear(sf::Color::Black);
        sf::Event event;
        while (game.pollEvent(event))
        {
            // "close requested" event: the game closes
            if (event.type == sf::Event::Closed)
                game.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                // if the LMB is pressed, checked where it is pressed to do the correct action
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int xCursor = event.mouseButton.x;
                    int yCursor = event.mouseButton.y;
                    int currentRow; int currentCol;
                    // if the left click is below a certain y, then one of the tiles is pressed and proceed accordingly
                    if (yCursor < (gameBoard.getNumRows() * 32.0)) {
                        // Check that the game hasn't been won or lost
                        if ((Win == false) && (Lose == false)) {
                            currentRow = yCursor / 32;
                            currentCol = xCursor / 32;
                            Tile& currentTile = gameBoard.getTiles()[currentRow][currentCol];
                            // Checking win and lose condition
                            if (currentTile.getMineStatus()) {
                                Lose = true;
                                // Iterate through and change every bomb tile to revealed and turn debug mode on
                                for (int row = 0; row < gameBoard.getNumRows(); row++) {
                                    for (int col = 0; col < gameBoard.getNumCols(); col++) {
                                        Tile& temp = gameBoard.getTiles()[row][col];
                                        if (temp.getMineStatus()) {
                                            temp.setRevealStatus(true);
                                            temp.setSprite("tile_revealed");
                                        }
                                    }
                                }
                                gameBoard.getButtons()[3].setSprite("face_lose");
                            }
                            else {
                                // checks that the tile hasn't been revealed before
                                if (currentTile.getRevealStatus() == false) {
                                    leftClickTile(gameBoard, currentTile);
                                    if (checkWin(gameBoard)) {
                                        Win = true;
                                        gameBoard.getButtons()[3].setSprite("face_win");
                                    }
                                }
                            }
                        }
                    }
                    // else checks if one of the buttons is clicked
                    else {
                        // if debug button is clicked
                        if ((xCursor >= (gameBoard.getWidth() / 2.0) + 96) && (xCursor < (gameBoard.getWidth() / 2.0) + 160) && (yCursor < (gameBoard.getHeight() - 24))) {
                            // Making sure the game isn't over
                            if ((!Win) && (!Lose)) {
                                if (debugMode == true) {
                                    debugMode = false;
                                }
                                else {
                                    debugMode = true;
                                }
                            }
                        }
                        // else if face button is clicked
                        else if ((xCursor >= (gameBoard.getWidth() / 2.0) - 32) && (xCursor < (gameBoard.getWidth() / 2.0) + 32) && (yCursor < (gameBoard.getHeight() - 24))) {
                            gameBoard.resetBoard();
                            gameBoard.initializeMines();
                            gameBoard.findNearbyMines();
                            gameBoard.updateCounter(gameBoard.getCounterDigits());
                            Win = false; Lose = false;
                        }
                        // else if test1 button is clicked
                        else if ((xCursor >= (gameBoard.getWidth() / 2.0) + 160) && (xCursor < (gameBoard.getWidth() / 2.0) + 224) && (yCursor < (gameBoard.getHeight() - 24))) {
                            gameBoard.resetBoard();
                            loadBoard(1, gameBoard);
                            Win = false; Lose = false;
                        }
                        // else if test2 button is clicked
                        else if ((xCursor >= (gameBoard.getWidth() / 2.0) + 224) && (xCursor < (gameBoard.getWidth() / 2.0) + 288) && (yCursor < (gameBoard.getHeight() - 24))) {
                            gameBoard.resetBoard();
                            loadBoard(2, gameBoard);
                            Win = false; Lose = false;
                        }
                        // else if test3 button is clicked
                        else if ((xCursor >= (gameBoard.getWidth() / 2.0) + 288) && (xCursor < (gameBoard.getWidth() / 2.0) + 352) && (yCursor < (gameBoard.getHeight() - 24))) {
                            gameBoard.resetBoard();
                            loadBoard(3, gameBoard);
                            Win = false; Lose = false;

                        }
                    }


                }
                // else if the RMB is pressed, check if its on a tile and if it is, place a flag there
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    // Checking win/lose condition
                    if ((Win == false) and (Lose == false)) {
                        int xCursor = event.mouseButton.x;
                        int yCursor = event.mouseButton.y;
                        int currentRow; int currentCol;
                        // if the right click is below a certain y, then one of the tiles is pressed and proceed accordingly
                        if (yCursor < (gameBoard.getNumRows() * 32)) {
                            currentRow = yCursor / 32;
                            currentCol = xCursor / 32;
                            Tile& currentTile = gameBoard.getTiles()[currentRow][currentCol];
                            rightClickTile(gameBoard, currentTile);

                        }
                    }
                }
            }
            
        }
        displayBoard(gameBoard, game, debugMode, Lose);

    }
    
    // Clear out textures before program end
    TextureManager::Clear();
    return 0;
}