#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(Colour* colour, vector<int> coords)
{
	blocks = { new Block(), new Block(), new Block(), new Block() };
	initializeBlocks(coords, colour);
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
	for (int i = 0; i < 4; i++) {
		int oldX = blocks[i]->x;
		blocks[i]->x = blocks[i]->y;
		blocks[i]->y = -oldX;
	}
}


void Tetromino::rotateCounterClockwise() {
	for (int i = 0; i < 4; i++) {
		int oldX = blocks[i]->x;
		blocks[i]->x = -blocks[i]->y;
		blocks[i]->y = oldX;
	}
}


int Tetromino::minX() {
	return x + min(min(blocks[0]->x, blocks[1]->x), min(blocks[2]->x, blocks[3]->x));
}


int Tetromino::maxX() {
	return x + max(max(blocks[0]->x, blocks[1]->x), max(blocks[2]->x, blocks[3]->x));
}


int Tetromino::minY() {
	return y + min(min(blocks[0]->y, blocks[1]->y), min(blocks[2]->y, blocks[3]->y));
}


int Tetromino::maxY() {
	return y + max(max(blocks[0]->y, blocks[1]->y), max(blocks[2]->y, blocks[3]->y));
}


Tetromino::~Tetromino()
{
}

Block::Block() {
}


Block::~Block()
{
}
