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
// This class is the game's opening screen object
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// When there are a lot of images, OnInit takes a lot of time to
	// load all of them. To prevent people from waiting impatiently,
	// the game will show "Loading ..." to show the progress of Loading.
	//
	ShowInitProgress(0, "Start Initialize..."); // The loading progress at the beginning is 0%.
												//
												// Start loading data
												//
												// Sleep(1000);				// Slow down to see the progress clearly, the actual game please delete this Sleep
												//
												// This OnInit action will receive CGameStaterRun::OnInit(), so the progress is not yet 100%.
												//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateInit::load_background()
{
	background.LoadBitmapByString({"Resources/img/back/0/back0.bmp"});
	background.SetTopLeft(0, 0);
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN); // Switch to GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
}
