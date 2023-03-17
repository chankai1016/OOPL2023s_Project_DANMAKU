/////////////////////////////////////////////////////////////////////////////
// Define the three state constants used by CGame and CGameState
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
// Report program error using macro
// Note: Use macro here to keep the file name and line number for debug.
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
	// This class provides control over time, error, etc.
	// The general game does not require direct manipulation of this object, so you can ignore the use of this class
	/////////////////////////////////////////////////////////////////////////////

	class CSpecialEffect {
	public:
		static void  SetCurrentTime();					// Save the current time to ctime
		static DWORD GetEllipseTime();					// Read the current time - ctime
		static int   GetCurrentTimeCount();				// Read the number of times to store ctime
		static void  Delay(DWORD ms);					// Delay x ms
		static void  DelayFromSetCurrentTime(DWORD ms);	// Delay x ms from ctime
	private:
		static DWORD ctime;
		static int	 ctimeCount;
	};

	/////////////////////////////////////////////////////////////////////////////
	// This class will create DirectDraw objects to be used by other classes
	// General games do not need to manipulate this object directly, so you can ignore the use of this class
	/////////////////////////////////////////////////////////////////////////////

	class CDDraw {
		friend class CMovingBitmap;
	public:
		~CDDraw();
		static void  BltBackColor(DWORD);		// Color all Back plain with the specified color.
		static void  BltBackToPrimary();		// Paste Back plain to Primary plain
		static CDC*  GetBackCDC();				// Get Back Plain's DC (device context)
		static void  GetClientRect(CRect &r);	// Obtain the resolution of the setting
		static void  Init(int, int);			// Initialize direct draw
		static void  ReleaseBackCDC();			// Let go of Back Plain's DC (device context)
		static bool  SetFullScreen(bool);		// Set to full screen mode/window mode
		static bool  IsFullScreen();			// Answer whether it is full screen mode/window mode
	private:
		CDDraw();								// private constructor
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
		static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
		static void	 CheckDDFail(char *s);
		static bool  CreateSurface();
		static bool  CreateSurfaceFullScreen();
		static bool  CreateSurfaceWindowed();
		static void  LoadBitmap(int i, int IDB_BITMAP);
		static void  LoadBitmap(int i, char *filename);
		static void  LoadBitmapFromExistHBITMAP(int i, HBITMAP bitmap);
		static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
		static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
		static int   RegisterBitmap(char *filename, COLORREF ColorKey);
		static int   RegisterBitmapWithHBITMAP(HBITMAP hbitmap);
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
	// Declare undefined class
	/////////////////////////////////////////////////////////////////////////////

	class CGame;
	class CGameStateInit;
	class CGameStateRun;
	class CGameStateOver;

	/////////////////////////////////////////////////////////////////////////////
	// This class is the base class of the various states of the game (is an abstract class)
	// The use of each Public Interface should be understood, Implementation can not understand
	/////////////////////////////////////////////////////////////////////////////

	class CGameState {
	public:
		CGameState(CGame *g);
		void OnDraw();			// Template Method
		void OnCycle();			// Template Method
		//
		// virtual functions, provided by the successor implementation
		//
		virtual ~CGameState() {}								// virtual destructor
		virtual void OnBeginState() {}							// Set the initial value required to enter this state each time
		virtual void OnInit() {}								// Initial value and graphical setting of the state
		virtual void OnKeyDown(UINT, UINT, UINT) {}				// Handling keyboard down actions
		virtual void OnKeyUp(UINT, UINT, UINT) {}				// Handling keyboard up actions
		virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// Handling Mouse Actions
		virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// Handling Mouse Actions
		virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // Handling Mouse Actions 
		virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// Handling Mouse Actions
		virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// Handling Mouse Actions
	protected:
		void GotoGameState(int state);							// Jump to the specified state
		void ShowInitProgress(int percent, string message);						// Show the progress of initialization
		//
		// virtual functions, Implementation provided by successor
		//
		virtual void OnMove() {}								// Move this state of the game elements
		virtual void OnShow() = 0;								// Show this state of the game screen
		CGame *game;
		CMovingBitmap loadingBitmap;
	};

	/////////////////////////////////////////////////////////////////////////////
    // This class is the core of the game and controls the game
	// The general game does not need to directly manipulate this object, so you can ignore the use of this class
	/////////////////////////////////////////////////////////////////////////////

	class CGame {
	public:
		CGame();										// Constructor
		~CGame();										// Destructor
		bool IsRunning();								// Read if the game is in progress
		void OnDraw();									// OnDraw() of the corresponding CGameView
		void OnFilePause();								// Game Pause
		void OnInit();									// Initialization of game graphics and sound effects
		void OnInitStates();							// Initial values and graphical settings for each state of the game
		bool OnIdle();									// Game of the Main Loop
		void OnKeyDown(UINT, UINT, UINT);				// Handling keyboard down actions
		void OnKeyUp(UINT, UINT, UINT);					// Handling Keyboard Up actions
		void OnKillFocus();								// Game forced to pause
		void OnLButtonDown(UINT nFlags, CPoint point);	// Handling Mouse Actions
		void OnLButtonUp(UINT nFlags, CPoint point);	// Handling Mouse Actions
		void OnMouseMove(UINT nFlags, CPoint point);    // Handling Mouse Actions 
		void OnRButtonDown(UINT nFlags, CPoint point);	// Handling Mouse Actions
		void OnRButtonUp(UINT nFlags, CPoint point);	// Handling Mouse Actions
		void OnResume();								// Handling from "on-call restoration of the original action
		void OnSetFocus();								// Handling Focus
		void OnSuspend();								// Handling the "standby" action
		void SetGameState(int);
		static CGame *Instance();
	private:
		bool			running;			// Whether the game is in progress (not Pause)
		bool            suspended;			// Is the game being suspended
		const int		NUM_GAME_STATES;	// Number of states in the game (3 states)
		CGameState		*gameState;			// pointer points to the current game state
		CGameState		*gameStateTable[3];	// Game state object pointer
		static CGame	instance;			// Game Unique Instance
	};
}