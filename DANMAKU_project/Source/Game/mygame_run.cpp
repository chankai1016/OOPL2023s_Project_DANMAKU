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
	background.LoadBitmapByString({ "Resources/img/back/0/back0.bmp" });
	background.SetTopLeft(0, 0);
	background.ShowBitmap();
}

void CGameStateRun::OnInit()  								// The initial values and graphics settings of the game
{
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
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
}
