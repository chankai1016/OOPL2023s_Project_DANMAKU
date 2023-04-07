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
// This class is the end state of the game (Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	//
	// When there are a lot of images, OnInit takes a lot of time to
	// load all of them. To prevent people from waiting impatiently,
	// the game will show "Loading ..." to show the progress of Loading.
	//
	ShowInitProgress(66, "Initialize..."); // Take the progress of the previous state, here the progress is regarded as 66%.
	//
	// Start loading data
	//
	Sleep(1000); // Slow down to see the progress clearly, the actual game please delete this Sleep
	//
	// The final progress is 100%.
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);
}

void CGameStateOver::OnShow()
{
}