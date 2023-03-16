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
// This class is the end state (Game Over) of the game.
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
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
	// If there are a lot of images, it will take time for OnInit to load them all.
	// Show the user "Loading ..." on the game screen to indicate the loading progress. on the game screen to indicate loading progress.
	//
	ShowInitProgress(66, "Initialize...");	// Take the progress of the previous state, here progress is considered 66%.
	//
	// Start reading data
	//
	Sleep(1000);				// Slow down to check progress and remove this Sleep in the actual game
	//
	// Final progress is 100%
	//
	ShowInitProgress(100, "OK!");

	Sleep(1000);

	load_background();

}

void CGameStateOver::OnShow()
{

}

void CGameStateOver::load_background() {
	background.LoadBitmapByString({ "Resources/back/0/back0.bmp" });
	background.SetTopLeft(0, 0);
}