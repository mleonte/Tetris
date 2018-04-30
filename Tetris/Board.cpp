#include "stdafx.h"
#include "Board.h"


Board::Board(int width, int height) : width(width), height(height), delay(1000), gameOver(false)
{
	reset();
}


void Board::newTurn()
{
	initializeTetromino();
	delay = (int)(delay * 0.95);
}

void Board::initializeTetromino(){
	pair<Colour*, vector<int>> params = getBlockTypeParams(nextBlockType);
	activeTetromino = new Tetromino(params.first, params.second);
	activeTetromino->x = (width / 2);
	activeTetromino->y = 1;
	nextBlockType = (BlockType)(rand() % 7);
}

void Board::step()
{
	activeTetromino->y++;
	if (this->outOfBounds() || this->collidesWithBlock())
	{
		activeTetromino->y--;
		updateBoard();
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
		block->x = 0;
		block->y = 0;
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
		blocks.erase(blocks.begin() + rowsToDelete[i]);
	}

	for (int i = 0; i < rowsToDelete.size(); i++) {
		score += pow(1000, 1 + (i * 0.05));
		vector<Block*> newVec = vector<Block*>();
		for (int j = 0; j < width; j++) newVec.push_back(nullptr);
		blocks.insert(blocks.begin(), newVec);
	}
}

void Board::checkForLoss() {
	if (any_of(blocks[0].begin(), blocks[0].end(), [](Block* block) { return block != nullptr; }) ||
		any_of(blocks[1].begin(), blocks[1].end(), [](Block* block) { return block != nullptr; }))
		gameOver = true;
}

void Board::rotateClockwise() {
	this->activeTetromino->rotateClockwise();
	if (outOfBounds() || collidesWithBlock())
		this->activeTetromino->rotateCounterClockwise();

}


void Board::rotateCounterClockwise() {
	this->activeTetromino->rotateCounterClockwise();
	if (outOfBounds() || collidesWithBlock())
		this->activeTetromino->rotateClockwise();
}


void Board::moveLeft() {
	activeTetromino->x--;
	if (outOfBounds() || collidesWithBlock())
		activeTetromino->x++;
}


void Board::moveRight() {
	activeTetromino->x++;
	if (outOfBounds() || collidesWithBlock())
		activeTetromino->x--;
}

bool Board::outOfBounds() {
	return (activeTetromino->maxX() >= width ||activeTetromino->minX() < 0 ||
			activeTetromino->maxY() >= height || activeTetromino->minY() < 0);
}

bool Board::collidesWithBlock() {
	int x = activeTetromino->x;
	int y = activeTetromino->y;
	return (any_of(
		activeTetromino->blocks.begin(),
		activeTetromino->blocks.end(),
		[this, x, y](Block* block)
	{ return blocks[y + block->y][x + block->x] != nullptr; }));
}

pair<Colour*, vector<int>> Board::getBlockTypeParams(BlockType type) {
	Colour* col;
	vector<int> coords;
	switch (type)
	{
		// 0 0 0 0
		// 1 1 1 1
	case I:
		col = new Colour(0, 255, 255);
		coords = { -1, 0, 0, 0, 1, 0, 2, 0 };
		break;
		// 1 1
		// 1 1
	case O:
		col = new Colour(255, 0, 255);
		coords = { 0, 0, 1, 0, 0, 1, 1, 1 };
		break;
		// 0 1 0 
		// 1 1 1 
	case T:
		col = new Colour(139, 0, 139);
		coords = { 0, -1, -1, 0, 0, 0, 1, 0 };
		break;
		// 0 1 1 
		// 1 1 0 
	case S:
		col = new Colour(0, 255, 0);
		coords = { 0, -1, -1, 0, 0, 0, 1, -1 };
		break;
		// 1 1 0 
		// 0 1 1 
	case Z:
		col = new Colour(255, 0, 0);
		coords = { 0, -1, -1, -1, 0, 0, 1, 0 };
		break;
		// 1 0 0 
		// 1 1 1 
	case J:
		col = new Colour(0, 0, 255);
		coords = { -1, -1, -1, 0, 0, 0, 1, 0 };
		break;
		// 0 0 1 
		// 1 1 1 
	case L:
		col = new Colour(255, 165, 0);
		coords = { 1, -1, -1, 0, 0, 0, 1, 0 };
		break;
	default:
		col = nullptr;
		break;
	}
	return make_pair(col, coords);
}

void Board::reset() {
	blocks = vector<vector<Block*>>();
	for (int h = 0; h < height; h++) {
		blocks.push_back(vector<Block*>());
		for (int w = 0; w < width; w++) {
			blocks[h].push_back(nullptr);
		}
	}
	nextBlockType = (BlockType)(rand() % 7);
	initializeTetromino();
	score = 0;
	gameOver = false;
}


Board::~Board()
{
}
