/////////////////////////////////////////////////////////////////////////////
// Defines three state constants used by CGame and CGameState.
/////////////////////////////////////////////////////////////////////////////

enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Macro for reporting program errors
// Note: Use a macro here to retain the file name and line number for debugging purposes.
/////////////////////////////////////////////////////////////////////////////

#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
																			\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// This class controls time, errors, etc.
	// In a typical game, there is no need to manipulate this object directly, so the use of this class can be ignored
	/////////////////////////////////////////////////////////////////////////////

	class CSpecialEffect {
	public:
		static void  SetCurrentTime();
		static DWORD GetEllipseTime();
		static int   GetCurrentTimeCount();
		static void  Delay(DWORD ms);
		static void  DelayFromSetCurrentTime(DWORD ms);
	private:
		static DWORD ctime;
		static int	 ctimeCount;
	};

	/////////////////////////////////////////////////////////////////////////////
	// This class creates a DirectDraw object for use by other classes.
	// In a normal game, there is no need to manipulate this object directly, so the use of this class can be ignored.
	/////////////////////////////////////////////////////////////////////////////

	class CDDraw {
		friend class CMovingBitmap;
	public:
		~CDDraw();
		static void  BltBackColor(DWORD);
		static void  BltBackToPrimary();
		static CDC*  GetBackCDC();
		static void  GetClientRect(CRect &r);
		static void  Init(int, int);
		static void  ReleaseBackCDC();
		static bool  SetFullScreen(bool);
		static bool  IsFullScreen();
	private:
		CDDraw();
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
		static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
		static void	 CheckDDFail(char *s);
		static bool  CreateSurface();
		static bool  CreateSurfaceFullScreen();
		static bool  CreateSurfaceWindowed();
		static void  LoadBitmap(int i, int IDB_BITMAP);
		static void  LoadBitmap(int i, char *filename);
		static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
		static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
		static int   RegisterBitmap(char *filename, COLORREF ColorKey);
		static void  ReleaseSurface();
		static void  RestoreSurface();
		static void  SetColorKey(unsigned SurfaceID, COLORREF color);
		static HDC					hdc;
		static CDC					cdc;
		static CView				*pCView;
		static LPDIRECTDRAW2		lpDD;
		static LPDIRECTDRAWCLIPPER	lpClipperPrimary;
		static LPDIRECTDRAWCLIPPER	lpClipperBack;
		static LPDIRECTDRAWSURFACE	lpDDSPrimary;
		static LPDIRECTDRAWSURFACE	lpDDSBack;
		static vector<LPDIRECTDRAWSURFACE>	lpDDS;
		static HRESULT				ddrval;
		static vector<int>			BitmapID;
		static vector<string>		BitmapName;
		static vector<CRect>		BitmapRect;
		static vector<COLORREF>		BitmapColorKey;
		static bool					fullscreen;
		static CDDraw				ddraw;
		static int					size_x, size_y;
	};

	/////////////////////////////////////////////////////////////////////////////
	// Undefined class is declared
	/////////////////////////////////////////////////////////////////////////////

	class CGame;
	class CGameStateInit;
	class CGameStateRun;
	class CGameStateOver;

	/////////////////////////////////////////////////////////////////////////////
	// This class is the base class for the various states of the game (it is an abstract class).
	// You need to know how to use each Public Interface; you do not need to know Implementation.
	/////////////////////////////////////////////////////////////////////////////

	class CGameState {
	public:
		CGameState(CGame *g);
		void OnDraw();
		void OnCycle();

		virtual ~CGameState() {}
		virtual void OnBeginState() {}
		virtual void OnInit() {}
		virtual void OnKeyDown(UINT, UINT, UINT) {}
		virtual void OnKeyUp(UINT, UINT, UINT) {}
		virtual void OnLButtonDown(UINT nFlags, CPoint point) {}
		virtual void OnLButtonUp(UINT nFlags, CPoint point) {}
		virtual void OnMouseMove(UINT nFlags, CPoint point) {}
		virtual void OnRButtonDown(UINT nFlags, CPoint point) {}
		virtual void OnRButtonUp(UINT nFlags, CPoint point) {}
	protected:
		void GotoGameState(int state);
		void ShowInitProgress(int percent, string message);
		virtual void OnMove() {}
		virtual void OnShow() = 0;
		CGame *game;
		CMovingBitmap loadingBitmap;
	};

	/////////////////////////////////////////////////////////////////////////////
	// This class is the core of the game and controls game play
	// In a normal game, there is no need to manipulate this object directly, so the use of this class may be ignored
	/////////////////////////////////////////////////////////////////////////////

	class CGame {
	public:
		CGame();										// Constructor
		~CGame();										// Destructor
		bool IsRunning();
		void OnDraw();
		void OnFilePause();
		void OnInit();
		void OnInitStates();
		bool OnIdle();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnKillFocus();
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void OnRButtonDown(UINT nFlags, CPoint point);
		void OnRButtonUp(UINT nFlags, CPoint point);
		void OnResume();
		void OnSetFocus();
		void OnSuspend();
		void SetGameState(int);
		static CGame *Instance();
	private:
		bool			running;
		bool            suspended;
		const int		NUM_GAME_STATES;
		CGameState		*gameState;
		CGameState		*gameStateTable[3];
		static CGame	instance;
	};
}