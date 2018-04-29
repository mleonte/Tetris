#pragma once
#include <vector>
#include <stdlib.h>
#include <tuple>
#include "Utils.h"

enum BlockType { I, O, T, S, Z, J, L };

struct Block
{
	Block();
	Colour* colour;
	int x;
	int y;
	~Block();
};

class Tetromino {
public:
	Tetromino(BlockType type);

	std::vector<Block*> blocks;
	int x;
	int y;
	BlockType type;

	void initializeBlocks(std::vector<int>, Colour*);
	void rotateClockwise();
	void rotateCounterClockwise();
	int minX();
	int maxX();
	int minY();
	int maxY();
	Block* operator[](const int);
	~Tetromino();
};

