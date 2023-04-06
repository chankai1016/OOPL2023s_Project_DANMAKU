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
			if (character.GetLeft() < 371)
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
			if (character.GetTop() < 433)
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
			if (character.GetLeft() < 381)
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
			if (character.GetTop() < 443)
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
			if (my_shot_cnt > my_shot_max)
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

	background.LoadBitmapByString({"Resources/img/back/0/back0.bmp"});
	background.SetTopLeft(32, 16);
	frame.LoadBitmapByString({"Resources/img/board/backboard.bmp"}, RGB(0, 255, 0));
	frame.SetTopLeft(0, 0);
	character.LoadBitmapByString({"Resources/img/char/0_1.bmp",
								  "Resources/img/char/0_2.bmp",
								  "Resources/img/char/0_3.bmp",
								  "Resources/img/char/0_4.bmp",
								  "Resources/img/char/0_5.bmp",
								  "Resources/img/char/0_6.bmp",
								  "Resources/img/char/0_7.bmp",
								  "Resources/img/char/0_8.bmp",
								  "Resources/img/char/0_9.bmp",
								  "Resources/img/char/0_10.bmp",
								  "Resources/img/char/0_11.bmp",
								  "Resources/img/char/0_12.bmp"},
								 RGB(0, 255, 0));
	character.SetTopLeft(180, 350);
	character.SetAnimation(1000, true);

	my_shot_cnt = 0;
	my_shot_max = 500;
	my_shot_time_cnt = 5;
	for (int i = 0; i < my_shot_max; i++)
	{
		my_shot[i].LoadBitmapByString({"Resources/img/char/bl_00.bmp"}, RGB(0, 255, 0));
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
	background.ShowBitmap();
	for (int i = 0; i < my_shot_max; i++)
	{
		if (my_shot[i].IsBitmapLoaded() == true)
		{
			my_shot[i].SetTopLeft(my_shot[i].GetLeft(), my_shot[i].GetTop() - 20);
			my_shot[i].ShowBitmap();
			character.ShowBitmap();
			frame.ShowBitmap();
		}
	}
}
