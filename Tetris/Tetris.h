#pragma once  //______________________________________ Tetris.h  
#include "Resource.h"
#include "Board.h"
#include "Tetromino.h"
#include <time.h>
class Tetris: public Game::Window
{
public:
	Tetris()
	{
	}
	~Tetris()
	{
	}
	float x;
	float y;
	float r;
	double lastTime;
	int cellSize = 30;
	int boardWidth = 10;
	int boardHeight = 20;
	int padding = 50;
	int gridLineWidth = 2;
	int tetrominoMoveSpeed = 600;
	Board* board;
	bool RenderScene(CG::Gdi& gdi);
	void drawBoard(CG::Gdi& gdi);
	void drawBlocks(CG::Gdi & gdi);
	void drawTetromino(CG::Gdi & gdi);
	void drawBlock(CG::Gdi & gdi, Block * block, int offsetX = 0, int offsetY = 0);
	const wchar_t * GetClassName(){return L"Tetris";}
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	void InitializeGui()
	{
		this->Text = L"Tetris";
	}
	//void Window_KeyDown(Win::Event& e);
	//void Window_KeyUp(Win::Event& e);
	//void Window_LButtonDown(Win::Event& e);
	//void Window_LButtonUp(Win::Event& e);
	//void Window_MouseMove(Win::Event& e);
	//void Window_Size(Win::Event& e);
	void Window_Open(Win::Event& e);
	void GetWindowInformation(CREATESTRUCT& createStruct)
	{
		createStruct.style = WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
	}
	bool EventHandler(Win::Event& e)
	{
		return false;
	}
};
