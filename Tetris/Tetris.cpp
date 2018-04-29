#include "stdafx.h"  //________________________________________ Tetris.cpp
#include "Tetris.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE , LPTSTR cmdLine, int cmdShow){
	Tetris app;
	app.CreateMainWindow(L"Tetris", cmdShow, IDI_Tetris, NULL, (HBRUSH)::GetStockObject(NULL_BRUSH), hInstance);
	return app.MessageLoop(IDC_Tetris);
}

void Tetris::Window_Open(Win::Event& e)
{
	srand(time(NULL));
	board = new Board(boardWidth, boardHeight);
	stopWatch.Start();
	lastTime = stopWatch.GetSeconds();
	x = 0.0f;
}

bool Tetris::RenderScene(CG::Gdi& gdi)
{
	double currentTime = stopWatch.GetSeconds();
	double frameDelta = currentTime - lastTime;
	if (frameDelta >= (board->delay) / 1000) {
		board->step();
		lastTime = currentTime;
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
		board->step();
		y = 0;
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
	_snwprintf_s(text, 32, _TRUNCATE, L"Next Block:");
	gdi.TextOut(padding + (boardWidth * cellSize) + 3, padding + (2 * cellSize), text);
	drawNextTetromino(gdi, padding + (boardWidth * cellSize) + 10, padding + (2 * cellSize) + 30);
	return true; // return false to stop
}

void Tetris::drawBoard(CG::Gdi& gdi) {
	CG::Brush brush(RGB(20, 20, 20));
	RECT rect = { padding, padding + (2 * cellSize), padding + (boardWidth * cellSize), padding + (boardHeight * cellSize) };
	gdi.FillRect(rect, brush);

	CG::Brush brush2(RGB(90, 90, 90));
	int half = gridLineWidth / 2;
	for (int w = 0; w < boardWidth + 1; w++) {
		RECT line = { 
			padding + (w * cellSize) - half,
			padding + (2 * cellSize) - half,
			padding + (w * cellSize) + half, 
			padding + (boardHeight * cellSize) + half };
		gdi.FillRect(line, brush2);
	}
	for (int h = 2; h < boardHeight + 1; h++) {
		RECT line = { 
			padding - half, 
			padding + (h * cellSize) - half, 
			padding + (boardWidth * cellSize) + half,
			padding + (h * cellSize) + half };
		gdi.FillRect(line, brush2);
	}

}

void Tetris::drawBorderedBox(CG::Gdi& gdi, int xOffset, int yOffset, int width, int height, int halfOfLineWidth, Colour* colour) {
	RECT outline = {
		xOffset,
		yOffset,
		xOffset + width,
		yOffset + height
	};
	CG::Brush brushOutline(RGB(colour->red / 2, colour->green / 2, colour->blue / 2));
	gdi.FillRect(outline, brushOutline);

	int half = gridLineWidth / 2;
	RECT fill = {
		xOffset + halfOfLineWidth,
		yOffset + halfOfLineWidth,
		xOffset + width - halfOfLineWidth,
		yOffset + height - halfOfLineWidth
	};
	CG::Brush brushFill(RGB(colour->red, colour->green, colour->blue));
	gdi.FillRect(fill, brushFill);

}

void Tetris::drawBlocks(CG::Gdi& gdi) {
	for (int h = 2; h < boardHeight; h++) {
		for (int w = 0; w < boardWidth; w++) {
			if (board->blocks[h][w] != nullptr)
				drawBlock(gdi, board->blocks[h][w], w, h);
		}
	}
}

void Tetris::drawTetromino(CG::Gdi& gdi) {
	for (int i = 0; i < 4; i++) {
		Block* block = (*board->activeTetromino)[i];
		if (board->activeTetromino->y + block->y >= 2)
			drawBlock(gdi, block, board->activeTetromino->x + block->x, board->activeTetromino->y + block->y);
	}
}

void Tetris::drawNextTetromino(CG::Gdi& gdi, int x, int y) {
	BlockType toDraw = board->nextBlockType;
	pair<Colour*, vector<int>> params = board->getBlockTypeParams(toDraw);
	int width = cellSize / 2;
	for (int i = 0; i < 8; i += 2) {
		int blockX = params.second[i] + 1;
		int blockY = params.second[i + 1] + 1;
		int width = cellSize / 2;
		drawBorderedBox(gdi, x + (blockX * width), y + (blockY * width), width, width, 1, params.first);
	}
}

void Tetris::drawBlock(CG::Gdi& gdi, Block* block, int x, int y) {
	int half = gridLineWidth / 2;
	drawBorderedBox(gdi, padding + (x * cellSize), padding + (y * cellSize), cellSize, cellSize, half, block->colour);
}

//void Tetris::Window_Size(Win::Event& e)
//{
//	Game::Window::Window_Size(e);
//	// Use this->width and this->height
//}

void Tetris::Window_KeyDown(Win::Event& e)
{
	switch (e.wParam)
	{
	case VK_RIGHT:
		board->moveRight();
		break;
	case VK_LEFT:
		board->moveLeft();
		break;
	case VK_DOWN:
		board->step();
		break;
	}
}

void Tetris::Window_KeyUp(Win::Event& e)
{
	switch (e.wParam)
	{
	case VK_UP:
		board->rotateClockwise();
		break;
	}
}

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

