/////////////////////////////////////////////////////////////////////////////
// Defining the game's configurable environment and conditions
/////////////////////////////////////////////////////////////////////////////

#define GAME_TITLE           "Game"
#define SIZE_X				 655		// Set the resolution of the game screen to 640x480
#define SIZE_Y				 500		// Note: If you don't use the standard resolution, you can't switch to full screen.
#define OPEN_AS_FULLSCREEN	 false		// Whether to open the game in full screen or not
#define SHOW_LOAD_PROGRESS   true		// Whether to show the progress of loading (OnInit)
#define DEFAULT_BG_COLOR	 RGB(0, 0, 0)	// The default background color of the game screen (black)
#define GAME_CYCLE_TIME		 15		    // Run Move and Show every 33ms (30 times per second)
#define SHOW_GAME_CYCLE_TIME false		// whether to show the cycle time in debug mode
#define ENABLE_GAME_PAUSE	 false		// whether to allow Ctrl-Q to pause the game
#define ENABLE_AUDIO		 true		// Enable the sound interface
#define ENABLE_TOOLBAR       false      // whether to turn off the toolbar
#define ENABLE_MENU          false      // Turn off menu or not
#define ENABLE_STATUSBAR     false      // turn off the statusbar
#define RESOLUTION_X     1920           // For full screen, set to the current window resolution (width).
#define RESOLUTION_Y     1080           // For full screen, please set to the current window resolution (height).
