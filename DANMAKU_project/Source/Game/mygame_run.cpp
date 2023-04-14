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

void CGameStateRun::OnMove() // Mobile game elements
{
	if (ShiftKeyDown == false)
	{
		if (LeftKeyDown == true)
		{
			if (character.GetLeft() < 363)
			{
				character.SetTopLeft(character.GetLeft() + 10, character.GetTop());
			}
		}
		if (RightKeyDown == true)
		{
			if (10 < character.GetLeft())
			{
				character.SetTopLeft(character.GetLeft() - 10, character.GetTop());
			}
		}
		if (DownKeyDown == true)
		{
			if (character.GetTop() < 430)
			{
				character.SetTopLeft(character.GetLeft(), character.GetTop() + 10);
			}
		}
		if (UpKeyDown == true)
		{
			if (10 < character.GetTop())
			{
				character.SetTopLeft(character.GetLeft(), character.GetTop() - 10);
			}
		}
	}
	else
	{
		if (LeftKeyDown == true)
		{
			if (character.GetLeft() < 363)
			{
				character.SetTopLeft(character.GetLeft() + 5, character.GetTop());
			}
		}
		if (RightKeyDown == true)
		{
			if (0 < character.GetLeft())
			{
				character.SetTopLeft(character.GetLeft() - 5, character.GetTop());
			}
		}
		if (DownKeyDown == true)
		{
			if (character.GetTop() < 430)
			{
				character.SetTopLeft(character.GetLeft(), character.GetTop() + 5);
			}
		}
		if (UpKeyDown == true)
		{
			if (0 < character.GetTop())
			{
				character.SetTopLeft(character.GetLeft(), character.GetTop() - 5);
			}
		}
	}

	// bullet
	if (ZKeyDown == true)
	{
		if (my_shot_time_cnt >= 5)
		{
			my_shot_time_cnt = 0;
			my_shot[my_shot_cnt].SetTopLeft(character.GetLeft() + 20, character.GetTop());
			my_shot[my_shot_cnt].ShowBitmap();
			my_shot_cnt++;
			my_shot[my_shot_cnt].SetTopLeft(character.GetLeft() + 42, character.GetTop());
			my_shot[my_shot_cnt].ShowBitmap();
			my_shot_cnt++;
			if (my_shot_cnt >= my_shot_max)
			{
				my_shot_cnt = 0;
			}
		}
		my_shot_time_cnt++;
	}
	else
	{
		my_shot_time_cnt = 5;
	}
}

void CGameStateRun::OnInit() // The initial values and graphics settings of the game
{
	ZKeyDown = false;
	ShiftKeyDown = false;

	for (int i = 0; i < 2; i++)
	{
		background[i].LoadBitmapByString({ "Resources/img/back/0/back0.bmp" });
	}
	background[0].SetTopLeft(32, 0);
	background[1].SetTopLeft(32, -700);

	frame.LoadBitmapByString({"Resources/img/board/backboard.bmp"}, RGB(0, 255, 0));
	frame.SetTopLeft(0, 0);

	character.LoadBitmapByString({"Resources/img/char/0_1.bmp","Resources/img/char/0_2.bmp","Resources/img/char/0_3.bmp","Resources/img/char/0_4.bmp"}, RGB(0, 255, 0));
	character.SetTopLeft(180, 350);
	character.SetAnimation(200, false);
	character.ToggleAnimation();

	my_shot_cnt = 0;
	my_shot_max = 500;
	my_shot_time_cnt = 5;
	for (int i = 0; i < my_shot_max; i++)
	{
		my_shot[i].LoadBitmapByString({"Resources/img/char/bl_00.bmp"}, RGB(0, 255, 0));
	}

	enemy_max = 5;
	for (int i = 0; i < enemy_max; i++)
	{
		enemy[i].LoadBitmapByString({ "Resources/img/char/ball.bmp" }, RGB(255, 0, 0));
		enemy[i].SetTopLeft(50 + (i * 50) , 50);
	}

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT)
	{
		LeftKeyDown = true;
	}
	if (nChar == VK_LEFT)
	{
		RightKeyDown = true;
	}
	if (nChar == VK_DOWN)
	{
		DownKeyDown = true;
	}
	if (nChar == VK_UP)
	{
		UpKeyDown = true;
	}
	if (nChar == VK_SHIFT)
	{
		ShiftKeyDown = true;
	}
	if (nChar == 0x5A)
	{
		ZKeyDown = true;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT)
	{
		LeftKeyDown = false;
	}
	if (nChar == VK_LEFT)
	{
		RightKeyDown = false;
	}
	if (nChar == VK_DOWN)
	{
		DownKeyDown = false;
	}
	if (nChar == VK_UP)
	{
		UpKeyDown = false;
	}
	if (nChar == VK_SHIFT)
	{
		ShiftKeyDown = false;
	}
	if (nChar == 0x5A)
	{
		ZKeyDown = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // Handling Mouse Actions
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // Handling Mouse Actions
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // Handling Mouse Actions
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // Handling Mouse Actions
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // Handling Mouse Actions
{
}

void CGameStateRun::OnShow()
{
	for (int i = 0; i < 2; i++) {
		background[i].SetTopLeft(background[i].GetLeft(), background[i].GetTop() + 2);
		background[i].ShowBitmap();
		if (background[i].GetTop() >= 700) {
			background[i].SetTopLeft(32, -700);
		}
	}

	for (int i = 0; i < my_shot_max; i++)
	{
		if (my_shot[i].IsBitmapLoaded() == true)
		{
			my_shot[i].SetTopLeft(my_shot[i].GetLeft(), my_shot[i].GetTop() - 20);
			my_shot[i].ShowBitmap();
		}
		for (int j = 0; j < enemy_max; j++)
		{
			if (enemy[j].IsBitmapLoaded() == true)
			{
				enemy[j].ShowBitmap();
			}
			if ((enemy[j].GetLeft() <= my_shot[i].GetLeft() &&
				enemy[j].GetLeft()+100 >= my_shot[i].GetLeft())
			&& (enemy[j].GetTop() <= my_shot[i].GetTop() &&
				enemy[j].GetTop()+100 >= my_shot[i].GetTop())) {
				enemy[j].UnshowBitmap();
			}
		}
	}

	character.ShowBitmap();
	frame.ShowBitmap();
	//show_text_by_phase();
}

//void CGameStateRun::show_text_by_phase() {
//	CDC *pDC = CDDraw::GetBackCDC();
//
//	CTextDraw::ChangeFontLog(pDC, 21, "Microsoft JhengHei", RGB(0, 0, 0), 500);
//	CTextDraw::Print(pDC, 15, 168, "animation, so that it can move up and down.");
//}