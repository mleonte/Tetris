#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(BlockType type) : type(type)
{
	blocks = { new Block(), new Block(), new Block(), new Block() };
	
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
			coords = { 0, 0, -1, 0, 0, 0, 1, 0 };
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

	initializeBlocks(coords, col);
}

Block* Tetromino::operator[](const int index) {
	return blocks[index];
}

void Tetromino::initializeBlocks(vector<int> coords, Colour* col) {
	for (int i = 0; i < 7; i += 2) {
		blocks[i / 2]->x = coords[i];
		blocks[i / 2]->y = coords[i + 1];
		blocks[i / 2]->colour = col;
	}
}


void Tetromino::rotateClockwise() {
	if (type == O) return;
	for (int i = 0; i < 4; i++) {
		int oldX = blocks[i]->x;
		blocks[i]->x = blocks[i]->y;
		blocks[i]->y = -oldX;
	}
}


void Tetromino::rotateCounterClockwise() {
	if (type == O) return;
	for (int i = 0; i < 4; i++) {
		int oldX = blocks[i]->x;
		blocks[i]->x = -blocks[i]->y;
		blocks[i]->y = oldX;
	}
}


int Tetromino::minX() {
	return min(min(blocks[0]->x, blocks[1]->x), min(blocks[2]->x, blocks[3]->x));
}


int Tetromino::maxX() {
	return max(max(blocks[0]->x, blocks[1]->x), max(blocks[2]->x, blocks[3]->x));
}


int Tetromino::minY() {
	return min(min(blocks[0]->y, blocks[1]->y), min(blocks[2]->y, blocks[3]->y));
}


int Tetromino::maxY() {
	return max(max(blocks[0]->y, blocks[1]->y), max(blocks[2]->y, blocks[3]->y));
}


Tetromino::~Tetromino()
{
}

Block::Block() {
}


Block::~Block()
{
}
