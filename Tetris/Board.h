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
	BlockType nextBlockType;

	void newTurn();
	void initializeTetromino();
	void step();
	void updateBoard();
	void deconstructTetromino();
	void deleteFullRows();
	void checkForLoss();
	void rotateClockwise();
	void rotateCounterClockwise();
	void moveLeft();
	void moveRight();
	bool outOfBounds();
	bool collidesWithBlock();
	pair<Colour*, vector<int>> getBlockTypeParams(BlockType type);
	~Board();
};

