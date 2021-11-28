#pragma once
#include "Button.h";

using namespace std;

class MineCounter : public Button {
private:
	int digit;
public:
	MineCounter(int ID, int numRow, int numCol, int mineCount);
	void loadSpriteNumber(int num);
	int getDigit();
	void setDigit(int num);
};

