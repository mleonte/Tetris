#pragma once
#include <tuple>
#include "Tetromino.h"


class Board
{
public:
	Board(int, int);
	vector<vector<Block*>> blocks;
	Tetromino* activeTetromino;
	int width;
	int height;
	int delay;
	int turns;
	int score;
	bool gameOver;

	void newTurn();
	void initializeTetromino();
	void step();
	void updateBoard();
	void deconstructTetromino();
	void deleteFullRows();
	void checkForLoss();
	~Board();
};

