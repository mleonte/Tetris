#include "stdafx.h"  //________________________________________ Tetris.cpp
#include "Tetris.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Tetris app;
	app.CreateMainWindow(L"Tetris", cmdShow, IDI_Tetris, NULL, (HBRUSH)::GetStockObject(NULL_BRUSH), hInstance);
	return app.MessageLoop(IDC_Tetris);
}

void Tetris::Window_Open(Win::Event& e)
{
	board = new Board(boardWidth, boardHeight);
	stopWatch.Start();
	lastTime = stopWatch.GetSeconds();
	x = 0.0f;
}

bool Tetris::RenderScene(CG::Gdi& gdi)
{
	double currentTime = stopWatch.GetSeconds();
	if (currentTime - lastTime >= (board->delay) / 1000) {
		board->step();
		lastTime = currentTime;
	}
	//______________ Update the game
	if (keyboard[VK_RIGHT] && board->activeTetromino->x + board->activeTetromino->maxX() + 1 < boardWidth )
	{
		x += tetrominoMoveSpeed * deltaSec;
	}
	if (keyboard[VK_LEFT] && board->activeTetromino->x + board->activeTetromino->minX() > 0)
	{
		x -= tetrominoMoveSpeed * deltaSec;
	}
	if (keyboard[VK_DOWN] && board->activeTetromino->y + board->activeTetromino->maxY() + 1 < boardHeight)
	{
		y += tetrominoMoveSpeed * deltaSec;
	}
	if (keyboard[VK_UP])
	{
		r += (tetrominoMoveSpeed / 2) * deltaSec;
	}

	if (x <= -cellSize) {
		board->activeTetromino->x -= 1;
		x = 0;
	}
	else if (x >= cellSize) {
		board->activeTetromino->x += 1;
		x = 0;
	}
	if (y >= cellSize) {
		board->activeTetromino->y += 1;
		y = 0;
	}
	if (r > cellSize)
	{
		board->activeTetromino->rotateClockwise();
		r = 0;
	}
	// if (keyboard['A'])
	//{
	//	::PlaySound(MAKEINTRESOURCE(IDR_MYSOUND), hInstance, SND_RESOURCE | SND_ASYNC);
	// }

	//____________________________________________ Paint Window Background
	CG::Brush brush(RGB(100, 100, 255));
	RECT rect = {0, 0, width, height};
	gdi.FillRect(rect, brush);
	drawBoard(gdi);
	drawBlocks(gdi);
	drawTetromino(gdi);
	//____________________________________________ Paint Small Circle
	gdi.Circle((int)x, 20, 10);
	//____________________________________________ Display FPS
	wchar_t text[32];
	_snwprintf_s(text, 32, _TRUNCATE, L"%d", framesPerSecond);
	gdi.TextOut(0, 0, text);
	return true; // return false to stop
}

void Tetris::drawBoard(CG::Gdi& gdi) {
	CG::Brush brush(RGB(20, 20, 20));
	RECT rect = { padding, padding, padding + (boardWidth * cellSize), padding + (boardHeight * cellSize) };
	gdi.FillRect(rect, brush);

	CG::Brush brush2(RGB(90, 90, 90));
	int half = gridLineWidth / 2;
	for (int w = 0; w < boardWidth + 1; w++) {
		RECT line = { 
			padding + (w * cellSize) - half,
			padding - half,
			padding + (w * cellSize) + half, 
			padding + (boardHeight * cellSize) + half };
		gdi.FillRect(line, brush2);
	}
	for (int h = 0; h < boardHeight + 1; h++) {
		RECT line = { 
			padding - half, 
			padding + (h * cellSize) - half, 
			padding + (boardWidth * cellSize) + half,
			padding + (h * cellSize) + half };
		gdi.FillRect(line, brush2);
	}

}

void Tetris::drawBlocks(CG::Gdi& gdi) {
	for (int h = 2; h < boardHeight; h++) {
		for (int w = 0; w < boardWidth; w++) {
			if (board->blocks[h][w] != nullptr)
				drawBlock(gdi, board->blocks[h][w]);
		}
	}
}

void Tetris::drawTetromino(CG::Gdi& gdi) {
	for (int i = 0; i < 4; i++) {
		drawBlock(gdi, (*board->activeTetromino)[i], board->activeTetromino->x, board->activeTetromino->y);
	}
}

void Tetris::drawBlock(CG::Gdi& gdi, Block* block, int offsetX, int offsetY) {
	RECT outline = {
		padding + ((offsetX + block->x) * cellSize),
		padding + ((offsetY + block->y) * cellSize),
		padding + ((offsetX + block->x) * cellSize) + cellSize,
		padding + ((offsetY + block->y) * cellSize) + cellSize
	};
	CG::Brush brushOutline(RGB(block->colour->red / 2, block->colour->green / 2, block->colour->blue / 2));
	gdi.FillRect(outline, brushOutline);

	int half = gridLineWidth / 2;
	RECT fill = {
		padding + ((offsetX + block->x) * cellSize) + half,
		padding + ((offsetY + block->y) * cellSize) + half,
		padding + ((offsetX + block->x) * cellSize) + cellSize - half,
		padding + ((offsetY + block->y) * cellSize) + cellSize - half
	};
	CG::Brush brushFill(RGB(block->colour->red, block->colour->green, block->colour->blue));
	gdi.FillRect(fill, brushFill);
}

//void Tetris::Window_Size(Win::Event& e)
//{
//	Game::Window::Window_Size(e);
//	// Use this->width and this->height
//}

//void Tetris::Window_KeyDown(Win::Event& e)
//{
//	switch (e.wParam)
//	{
//	case VK_SHIFT:
//		break;
//	case VK_UP:
//		break;
//	case 'A':
//		break;
//	}
//}

//void Tetris::Window_KeyUp(Win::Event& e)
//{
//	switch (e.wParam)
//	{
//	case VK_SHIFT:
//		break;
//	case VK_UP:
//		break;
//	case 'A':
//		break;
//	}
//}

//void Tetris::Window_LButtonDown(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//	this->SetFocus();
//}

//void Tetris::Window_LButtonUp(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//}

//void Tetris::Window_MouseMove(Win::Event& e)
//{
//	const int x = GET_X_LPARAM(e.lParam);
//	const int y = GET_Y_LPARAM(e.lParam);
//}

