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
	// When there are a lot of images, OnInit takes a lot of time to load all of them. To prevent people from waiting impatiently, the game will show "Loading ..." to show the progress of Loading.
	//
	ShowInitProgress(0, "Start Initialize...");	// The loading progress at the beginning is 0%.
	Sleep(200);

	load_background();

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//
	// This OnInit action will receive CGameStaterRun::OnInit(), so the progress is not yet 100%.
	//
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	GotoGameState(GAME_STATE_RUN);		// Switch to GAME_STATE_RUN
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	draw_text();
}

void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "resources/initialize_background.bmp" });
	background.SetTopLeft(0, 0);
}

void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	/* Print title */
	CTextDraw::ChangeFontLog(pDC, fp, 36, "Microsoft JhengHei", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 20, 228, "Game Framework Practice");

	/* Print info */
	CTextDraw::ChangeFontLog(pDC, fp, 24, "Microsoft JhengHei", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 130, 431, "Press any key to start");

	CDDraw::ReleaseBackCDC();
}