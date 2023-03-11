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
// This class is the runtime object of the game, where the main game program is located
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

void CGameStateRun::OnMove()
{
	
}

void CGameStateRun::OnInit()  								// Initial values and graphic settings of the game.
{
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // Handle mouse actions
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// Handle mouse actions
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// Handle mouse actions
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // Handle mouse actions
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// Handle mouse actions
{
}

void CGameStateRun::OnShow()
{
}