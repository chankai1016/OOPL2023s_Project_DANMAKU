/*
 * mygame.h: This file contains the interface to the game's own classes.
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// Define various sound effect numbers
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// This class is the object of the opening screen of the game.
	// It is necessary to understand the implementation of each Member function.
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// Game defaults and graphics settings
		void OnBeginState();							// Set the number of variables required for each playback
		void OnKeyUp(UINT, UINT, UINT); 				// Process keyUp action
		void OnLButtonDown(UINT nFlags, CPoint point);  // Handle mouse actions
	protected:
		void OnShow();									// Show game screen in this state.
	private:
		CMovingBitmap logo; // csie logo
		void load_background();
		void draw_text();
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	// This class is the execution object of the game, and the main game is here
	// Need to understand the implementation of each member function
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// Set variables required for each replay
		void OnInit();  								// Game defaults and graphics settings
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // Handle mouse actions
		void OnLButtonUp(UINT nFlags, CPoint point);	// Handle mouse actions
		void OnMouseMove(UINT nFlags, CPoint point);	// Handle mouse actions
		void OnRButtonDown(UINT nFlags, CPoint point);  // Handle mouse actions
		void OnRButtonUp(UINT nFlags, CPoint point);	// Handle mouse actions
	protected:
		void OnMove();									// Move game elements
		void OnShow();									// Display the game screen in this state.
	private:
		int phase = 1;
		int sub_phase = 1;

		CMovingBitmap background;
		CMovingBitmap character;
		CMovingBitmap player_shot;
		CMovingBitmap enemy_shot;

		// 関数をここに定義

		typedef struct {
			int flag;       //フラグ
			int cnt;        //カウンタ
			int power;      //パワー
			int point;      //ポイント
			int score;      //スコア
			int num;        //残機数
			int mutekicnt;  //無敵状態とカウント
			int shot_mode;  //ショットモード
			int money;      //お金
			int img;        //画像
			int slow;       //スローかどうか
			double x, y;     //座標
		}ch_t;

	};

	/////////////////////////////////////////////////////////////////////////////
	// This class is in the Game Over state
	// Need to understand the implementation of each member function
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// Set variables required for each replay.
		void OnInit();
	protected:
		void OnMove();									// Move game elements
		void OnShow();									// Show game screen in this state.
	private:
		int counter;	// Countdown counter
		CMovingBitmap background;
		void load_background();
	};

}