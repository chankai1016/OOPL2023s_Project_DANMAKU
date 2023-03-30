#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// This class is the game execution object of the game, the main game program is here
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// Mobile game elements
{
	if (LeftKeyDown == true) {
		character.SetTopLeft(character.GetLeft() + 15, character.GetTop());
	}
	if (RightKeyDown == true) {
		character.SetTopLeft(character.GetLeft() - 15, character.GetTop());
	}
	if (DownKeyDown == true) {
		character.SetTopLeft(character.GetLeft(), character.GetTop() + 15);
	}
	if (UpKeyDown == true) {
		character.SetTopLeft(character.GetLeft(), character.GetTop() - 15);
	}
}

void CGameStateRun::OnInit()  								// The initial values and graphics settings of the game
{
	board.LoadBitmapByString({ "Resources/img/back/0/back0.bmp" });
	board.SetTopLeft(32, 16);
	background.LoadBitmapByString({ "Resources/img/board/backboard.bmp" });
	background.SetTopLeft(0, 0);
	character.LoadBitmapByString({ "Resources/img/char/0.bmp" });
	character.SetTopLeft(0, 0);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		LeftKeyDown = true;
	}
	if (nChar == VK_LEFT) {
		RightKeyDown = true;
	}
	if (nChar == VK_DOWN) {
		DownKeyDown = true;
	}
	if (nChar == VK_UP) {
		UpKeyDown = true;
	}
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) {
		LeftKeyDown = false;
	}
	if (nChar == VK_LEFT) {
		RightKeyDown = false;
	}
	if (nChar == VK_DOWN) {
		DownKeyDown = false;
	}
	if (nChar == VK_UP) {
		UpKeyDown = false;
	}

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // Handling Mouse Actions
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// Handling Mouse Actions
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// Handling Mouse Actions
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // Handling Mouse Actions
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// Handling Mouse Actions
{
}

void CGameStateRun::OnShow()
{
	board.ShowBitmap();
	background.ShowBitmap();
	character.ShowBitmap();
}
