#include "stdafx.h"
#include "Board.h"


Board::Board(int width, int height) : width(width), height(height), delay(1000), gameOver(false)
{
	for (int h = 0; h < height; h++) {
		blocks.push_back(vector<Block*>());
		for (int w = 0; w < width; w++) {
			blocks[h].push_back(nullptr);
		}
	}
	initializeTetromino();
}


void Board::newTurn()
{
	initializeTetromino();
	delay = (int)(delay * 0.95);
}

void Board::initializeTetromino(){
	BlockType type = (BlockType)(rand() % 7);
	activeTetromino = new Tetromino(type);
	activeTetromino->x = (width / 2);
	activeTetromino->y = 0;
}

void Board::step()
{
	int x = activeTetromino->x;
	int y = activeTetromino->y;
	if (any_of(
		activeTetromino->blocks.begin(),
		activeTetromino->blocks.end(),
		[this, x, y](Block* block) 
			{ if (y + block->y + 1 == height) return true; 
			  else return blocks[y + block->y + 1][x + block->x] != nullptr; }))
	{
		updateBoard();
	}
	else {
		activeTetromino->y++;
	}
}

void Board::updateBoard() {
	deconstructTetromino();
	deleteFullRows();
	checkForLoss();
	initializeTetromino();
}

void Board::deconstructTetromino()
{
	for (int i = 0; i < 4; i++) {
		Block* block = (*activeTetromino)[i];
		block->x += activeTetromino->x;
		block->y += activeTetromino->y;
		blocks[block->y][block->x] = block;
	}
	activeTetromino->~Tetromino();
}

void Board::deleteFullRows() {
	vector<int> rowsToDelete;
	for (int i = 0; i < height; i++) {
		if (all_of(blocks[i].begin(), blocks[i].end(), [](Block* block) { return block != nullptr; })) {
			rowsToDelete.push_back(i);
		}
	}

	for (int i = rowsToDelete.size() - 1; i >= 0; i--) {
		blocks.erase(blocks.begin() + i);
		blocks.insert(blocks.begin(), vector<Block*>());
		for (int j = 0; j < width; j++) blocks[0].push_back(nullptr);

		/*for (int k = i; k > 0; k--)
			for (int m = 0; m < width; m++) {
				if (blocks[k][m] != nullptr) {
					blocks[k][m]->y += 1;
				}
			}*/
	}
}

void Board::checkForLoss() {
	if (any_of(blocks[0].begin(), blocks[0].end(), [](Block* block) { return block != nullptr; }) ||
		any_of(blocks[1].begin(), blocks[1].end(), [](Block* block) { return block != nullptr; }))
		gameOver = true;
}

Board::~Board()
{
}
