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
// This class is the object of the opening screen of the game
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// If there are a lot of images, it will take time for OnInit to load them all.
	// Show the user "Loading ..." on the game screen to indicate the loading progress. on the game screen to indicate loading progress.
	//
	ShowInitProgress(0, "Start Initialize...");	// 0% loading progress at start
	//
	// Start reading data
	//
	Sleep(1000);				// Slow down to check progress, remove this Sleep in the actual game
	//
	// This OnInit action receives CGameStaterRun::OnInit(), so progress is not 100% yet
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// Switch to GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
}
