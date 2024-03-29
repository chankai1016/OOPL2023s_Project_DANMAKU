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
// This class is the game execution object of the game, where the main game program is located
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

void CGameStateRun::OnMove()							// Move game elements
{
	if ((phase == 3) && (character.Left() == chest_and_key.Left()) && (character.Top() == chest_and_key.Top())) {
		chest_and_key.SelectShowBitmap(1);
	}
	if ((phase == 5) && (character.Left() > door[0].Left() - 10) && (character.Left() < door[0].Left() + 10) && (character.Top() == door[0].Top())) {
		door[0].SelectShowBitmap(1);
	}
	if ((phase == 5) && (character.Left() > door[1].Left() - 10) && (character.Left() < door[1].Left() + 10) && (character.Top() == door[1].Top())) {
		door[1].SelectShowBitmap(1);
	}
	if ((phase == 5) && (character.Left() > door[2].Left() - 10) && (character.Left() < door[2].Left() + 10) && (character.Top() == door[2].Top())) {
		door[2].SelectShowBitmap(1);
	}
}

void CGameStateRun::OnInit()  								// Initial values and graphic settings of the game.
{
	background.LoadBitmapByString({ 
		"resources/phase11_background.bmp", 
		"resources/phase12_background.bmp", 
		"resources/phase21_background.bmp", 
		"resources/phase22_background.bmp", 
		"resources/phase31_background.bmp", 
		"resources/phase32_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase42_background.bmp",
		"resources/phase51_background.bmp",
		"resources/phase52_background.bmp",
		"resources/phase61_background.bmp",
		"resources/phase62_background.bmp",
	});
	background.SetTopLeft(0, 0);

	character.LoadBitmapByString({ "resources/giraffe.bmp" });
	character.SetTopLeft(150, 265);

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);
	bee.SetAnimation(2, false);

	ball.LoadBitmapByString({ "resources/ball-3.bmp", "resources/ball-2.bmp", "resources/ball-1.bmp", "resources/ball-ok.bmp" });
	ball.SetTopLeft(150, 430);
	ball.SetAnimation(1000, true);

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/door_close.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door[i].SetTopLeft(462 - 100 * i, 265);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN) {
		if (phase == 1) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_1();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		} else if (phase == 2) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_2();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 3) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_3();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 4) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_4();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 5) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_5();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 6) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_6();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	//if (nChar == VK_RIGHT) {
	//	if ((character.Left() < 480) && (character.Top() == 265)) {
	//		character.SetTopLeft(character.Left()+15, character.Top());
	//	}
	//}
	//if (nChar == VK_LEFT) {
	//	if ((character.Left() > 150) && (character.Top() == 265)) {
	//		character.SetTopLeft(character.Left()-15, character.Top());
	//	}
	//}
	//if (nChar == VK_DOWN) {
	//	if ((character.Left() == 150) && (character.Top() < 430)) {
	//		character.SetTopLeft(character.Left(), character.Top()+15);
	//	}
	//}
	//if (nChar == VK_UP) {
	//	if ((character.Left() == 150) && (character.Top() > 265)) {
	//		character.SetTopLeft(character.Left(), character.Top()-15);
	//	}
	//}
	switch (nChar) {
		case VK_RIGHT:
			if ((character.Left() < 480) && (character.Top() == 265)) {
				character.SetTopLeft(character.Left() + 15, character.Top());
			}
			break;
		case VK_LEFT:
			if ((character.Left() > 150) && (character.Top() == 265)) {
				character.SetTopLeft(character.Left() - 15, character.Top());
			}
			break;
		case VK_DOWN:
			if ((character.Left() == 150) && (character.Top() < 430)) {
				character.SetTopLeft(character.Left(), character.Top() + 15);
			}
			break;
		case VK_UP:
			if ((character.Left() == 150) && (character.Top() > 265)) {
				character.SetTopLeft(character.Left(), character.Top() - 15);
			}
			break;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // Handles mouse actions
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// Handles mouse actions
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// Handles mouse actions
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // Handles mouse actions
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// Handles mouse actions
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();
	show_text_by_phase();
}

void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {
		background.SelectShowBitmap((phase - 1) * 2 + (sub_phase - 1));
		background.ShowBitmap();
		character.ShowBitmap();
		if (phase == 3 && sub_phase == 1) {
			chest_and_key.ShowBitmap();
		}
		if (phase == 4 && sub_phase == 1) {
			bee.ShowBitmap();
		}
		if (phase == 5 && sub_phase == 1) {
			for (int i = 0; i < 3; i++) {
				door[i].ShowBitmap();
			}
		}
		if (phase == 6 && sub_phase == 1) {
			ball.ShowBitmap();
			if (ball.GetSelectShowBitmap() == 0) {
				ball.ToggleAnimation();
			}
		}
	}
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	CTextDraw::ChangeFontLog(pDC, fp, 21, "Microsoft JhengHei", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 30, 100, "Modify your main character!");
		CTextDraw::Print(pDC, 30, 134, "Replace the grey squares with the");
		CTextDraw::Print(pDC, 30, 168, "giraffe.bmp image in resources!");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 30, 134, "Next stage: Let the giraffe be able");
		CTextDraw::Print(pDC, 30, 168, "to move up and down to this position!");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 15, 100, "Help you prepare a chest.");
		CTextDraw::Print(pDC, 15, 134, "Design the program to make the giraffe touch");
		CTextDraw::Print(pDC, 15, 168, "the treasure chest and then disappear it!");
		CTextDraw::Print(pDC, 15, 202, "Remember to remove the background of the");
		CTextDraw::Print(pDC, 15, 236, "chest, and use RGB(255, 255, 255).");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 15, 100, "Help you prepare a bee buddy.");
		CTextDraw::Print(pDC, 15, 134, "Has helped it to do two frames of");
		CTextDraw::Print(pDC, 15, 168, "animation, so that it can move up and down.");
		CTextDraw::Print(pDC, 15, 202, "Write a program to give your bee");
		CTextDraw::Print(pDC, 15, 236, "best friend an animation!");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 30, 100, "Help you prepare three doors.");
		CTextDraw::Print(pDC, 30, 134, "The design program allows the giraffe to");
		CTextDraw::Print(pDC, 30, 168, "touch the door after the door will open.");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 30, 100, "Help you prepare a ball that counts down.");
		CTextDraw::Print(pDC, 30, 134, "Design the program to let the ball count ");
		CTextDraw::Print(pDC, 30, 168, "down, then stop the animation after.");
		CTextDraw::Print(pDC, 220, 537, "Press the Enter key to verify.");
	} else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "Done!");
	}

	CDDraw::ReleaseBackCDC();
}

bool CGameStateRun::validate_phase_1() {
	return character.GetImageFilename() == "resources/giraffe.bmp";
}

bool CGameStateRun::validate_phase_2() {
	return character.Top() > 204 && character.Top() < 325 && character.Left() > 339 && character.Left() < 459;
}

bool CGameStateRun::validate_phase_3() {
	return (
		character.Top() + character.Height() >= chest_and_key.Top()
		&& character.Left() + character.Width() >= chest_and_key.Left()
		&& chest_and_key.GetSelectShowBitmap() == 1
		&& chest_and_key.GetFilterColor() == RGB(255, 255, 255)
		);
}

bool CGameStateRun::validate_phase_4() {
	return bee.IsAnimation() && bee.GetMovingBitmapFrame() == 2;
}

bool CGameStateRun::validate_phase_5() {
	bool check_all_door_is_open = true;
	for (int i = 0; i < 3; i++) {
		check_all_door_is_open &= (door[i].GetSelectShowBitmap() == 1);
	}
	return check_all_door_is_open;
}

bool CGameStateRun::validate_phase_6() {
	return ball.IsAnimationDone() && !ball.IsAnimation();
}