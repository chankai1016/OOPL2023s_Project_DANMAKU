//#define	 INITGUID
#include "stdafx.h"
#include "../Core/game.h"
#include "../Core/MainFrm.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "audio.h"
#include "gameutil.h"
#include "gamecore.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// CMovingBitmap: Moving Bitmap class
	// This class provides graphics that can be moved
	// You need to know how to call (use) its various capabilities, but you may not know what the following programs mean
	/////////////////////////////////////////////////////////////////////////////

	//! CMovingBitmap Constructor
	/*! 
		Used to create an object that has not yet been read from the image.
	*/
	CMovingBitmap::CMovingBitmap()
	{
		isBitmapLoaded = false;
	}

		//! Get the image height of the CMovingBitmap object.
	/*!
		The image needs to be loaded first.
		\return The height of the image, in pixels.
	*/
	int CMovingBitmap::GetHeight()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Height() is called !!!");
		return locations[frameIndex].bottom - locations[frameIndex].top;
	}

	//! Get the x-axis coordinates of the upper-left corner of the CMovingBitmap object.
	/*!
		The image needs to be loaded first.
		\return The x-axis coordinate value of the upper-left corner of the image.
	*/
	int CMovingBitmap::GetLeft()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Left() is called !!!");
		return locations[frameIndex].left;
	}

	//! Reads picture resources.
	/*!
		Reads the corresponding picture by resource number `IDB_BITMAP` and filters for a specific color `color`.
		\param IDB_BITMAP Image Resource Number
		\param color Color to be filtered (default is `CLR_INVALID`, you can use `RGB(<R>, <G>, <B>`) to set the color)
	*/
	void CMovingBitmap::LoadBitmap(int IDB_BITMAP, COLORREF color)
	{
		CBitmap bitmap;
		BOOL rval = bitmap.LoadBitmap(IDB_BITMAP);
		GAME_ASSERT(rval, "Load bitmap failed !!! Please check bitmap ID (IDB_XXX).");
		BITMAP bitmapSize;
		bitmap.GetBitmap(&bitmapSize);

		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmap(IDB_BITMAP, color));
		filterColor = color;
		isBitmapLoaded = true;
	}

	//! Reads picture resources.
	/*!
		Reads the corresponding picture from the picture relative path `filepath` and filters for a specific color `color`.
		\param filepath Relative path of images
		\param color The color you want to filter (default is `CLR_INVALID`, you can use `RGB(<R>, <G>, <B>`) to set the filter color)
	*/
	void CMovingBitmap::LoadBitmap(char *filepath, COLORREF color)
	{
		HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, filepath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (hbitmap == NULL) {
			char error_msg[300];
			sprintf(error_msg, "Loading bitmap	from file \"%s\" failed !!!", filepath);
			GAME_ASSERT(false, error_msg);
		}

		CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically
		BITMAP bitmapSize;
		bmp->GetBitmap(&bitmapSize);

		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmap(filepath, color));
		imageFileName = string(filepath);
		filterColor = color;
		isBitmapLoaded = true;

		bmp->DeleteObject();
	}

	//! Reads picture resources.
	/*!
		Reads multiple pictures from the set of picture relative paths `filepaths` and filters for specific colors `color`.
		\param filepaths Photo relative path set
		\param color The color you want to filter (default is `CLR_INVALID`, you can use `RGB(<R>, <G>, <B>`) to set the filter color)
		\sa https://en.cppreference.com/w/cpp/container/vector
	*/
	void CMovingBitmap::LoadBitmap(vector<char*> filepaths, COLORREF color)
	{
		for (int i = 0; i < (int)filepaths.size(); i++) {
			LoadBitmap(filepaths[i], color);
		}
	}

	//! Reads picture resources.
	/*!
		Reads multiple pictures from the set of picture relative paths `filepaths` and filters for specific colors `color`.
		\param filepaths Photo relative path set
		\param color he color you want to filter (default is `CLR_INVALID`, you can use `RGB(<R>, <G>, <B>`) to set the filter color)
		\sa https://en.cppreference.com/w/cpp/container/vector
	*/
	void CMovingBitmap::LoadBitmapByString(vector<string> filepaths, COLORREF color)
	{

		for (int i = 0; i < (int)filepaths.size(); i++) {
			LoadBitmap((char*)filepaths[i].c_str(), color);
		}
	}

	//! Reads a blank image resource.
	/*!
		Reads a white dot matrix of a specific size.
		\param height Picture length
		\param width Image Width
	*/
	void CMovingBitmap::LoadEmptyBitmap(int height, int width) {
		HBITMAP hbitmap = CreateBitmap(width, height, 1, 32, NULL);
		CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically

		/* Fill white color to bitmap */
		HDC hdc = CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, hbitmap);
		PatBlt(hdc, 0, 0, width, height, WHITENESS);
		SelectObject(hdc, hOldBitmap);
		DeleteDC(hdc);

		BITMAP bitmapSize;
		bmp->GetBitmap(&bitmapSize);

		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmapWithHBITMAP(hbitmap));
		isBitmapLoaded = true;

		bmp->DeleteObject();
	}
	
	//! Stops the display of pictures.
	/*!
		@deprecated After v1.0.0, please do not call `ShowBitmap()` when `OnShow()` to stop displaying pictures.
		\sa ShowBitmap()
	*/
	void CMovingBitmap::UnshowBitmap()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before SetTopLeft() is called !!!");
		isAnimation = false;
		this->ShowBitmap(0);
	}

	//! Set the picture to the specified coordinates on the canvas.
	/*!
		The upper left corner of the picture will be set to the specified coordinates.
		\param x Top left corner x Coordinates
		\param y Top left corner y Coordinates
	*/
	void CMovingBitmap::SetTopLeft(int x, int y)
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before SetTopLeft() is called !!!");

		for (int i = 0; i < int(locations.size()); i++) {
			int dx = locations[i].left - x;
			int dy = locations[i].top - y;
			locations[i].left = x;
			locations[i].top = y;
			locations[i].right -= dx;
			locations[i].bottom -= dy;
		}
	}

	//! Set whether the picture is animated or not.
	/*!
		If the CMovingBitmap reads multiple pictures, you can use this function to animate the objects.
		\param delay Animation switching delay (in milliseconds)
		\param once Whether the animation is a one-time animation or not, if yes, you need to use `ToggleAnimation()` to call the animation to start.
		\sa ToggleAnimation()
	*/
	void CMovingBitmap::SetAnimation(int delay, bool once) {
		if(!once) isAnimation = true;
		isOnce = once;
		delayCount = delay;
	}

	//! Show pictures.
	/*!
		Can only be called when `onShow()` and the picture needs to be read.
	*/
	void CMovingBitmap::ShowBitmap()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before ShowBitmap() is called !!!");
		CDDraw::BltBitmapToBack(surfaceID[frameIndex], locations[frameIndex].left, locations[frameIndex].top);
		ShowBitmapBySetting();
	}

	//! Show pictures.
	/*!
		Can only be called when `onShow()` and the picture needs to be read.
		\param factor Magnification requires VGA card support, otherwise it will become abnormally slow.
	*/
	void CMovingBitmap::ShowBitmap(double factor)
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before ShowBitmap() is called !!!");
				CDDraw::BltBitmapToBack(surfaceID[frameIndex], locations[frameIndex].left, locations[frameIndex].top, factor);
		ShowBitmapBySetting();
	}

	//! Set the index value of the current picture display frame.
	/*!
		The index value of the picture display frame starts with 0.
		\param frameIndex The picture displays the index value of the frame.
	*/
	void CMovingBitmap::SetFrameIndexOfBitmap(int frameIndex) {
		GAME_ASSERT(frameIndex < (int) surfaceID.size(), "Index out of bounds when selecting pictures");
		this->frameIndex = frameIndex;
	}

	//! Get the index value of the current picture display frame.
	/*!
		\return The picture displays the index value of the frame.
	*/
	int CMovingBitmap::GetFrameIndexOfBitmap() {
		return frameIndex;
	}

		//! Get the coordinates of the y-axis in the upper-left corner of the current picture.
	/*!
		\return The coordinates of the y-axis in the upper-left corner of the picture.
	*/
	int CMovingBitmap::GetTop()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Top() is called !!!");
		return locations[frameIndex].top;
	}

	//! Get the current picture width.
	/*!
		\return Get the current picture width.
	*/
	int CMovingBitmap::GetWidth()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Width() is called !!!");
		return locations[frameIndex].right - locations[frameIndex].left;
	}

	//! Start single animation.
	/*!
		Set the animation as the initial frame and initialize the parameter value of the single animation.
	*/
	void CMovingBitmap::ToggleAnimation() {
		frameIndex = 0;
		isAnimation = true;
		isAnimationDone = false;
	}

	//! Whether the object is an animated object or not.
	/*!
		\return The boolean value indicating whether the object is an animated object.
	*/
	bool CMovingBitmap::IsAnimation() {
		return isAnimation;
	}

	//! Whether the animation object has finished executing the animation.
	/*!
		\return The boolean value that indicates whether the animation object has finished executing the animation.
	*/
	bool CMovingBitmap::IsAnimationDone() {
		return isAnimationDone;
	}

	//! Whether the animated object is a single animation object or not.
	/*!
		\return The boolean value that indicates whether the animation object is a single animation object.
	*/
	bool CMovingBitmap::IsOnceAnimation() {
		return isOnce;
	}

	//! Whether the object has read the dot matrix.
	/*!
		\return The boolean value that indicates whether the object has read the dot matrix.
	*/
	bool CMovingBitmap::IsBitmapLoaded() {
		return isBitmapLoaded;
	}

	//! The frame number of the returned object.
	/*!
		\return The frame number of the returned object.
	*/
	int CMovingBitmap::GetFrameSizeOfBitmap() {
		return (int) surfaceID.size();
	}

	//! Initialize the location object in the CMovingBitmap according to the BITMAP.
	/*!
		\param bitmapSize Initialized BITMAP object with the height and width of the dot matrix
	*/
	void CMovingBitmap::InitializeRectByBITMAP(BITMAP bitmapSize) {
		const unsigned NX = 0;
		const unsigned NY = 0;
		CRect newCrect;
		newCrect.left = NX;
		newCrect.top = NY;
		newCrect.right = NX + bitmapSize.bmWidth;
		newCrect.bottom = NY + bitmapSize.bmHeight;
		locations.push_back(newCrect);
	}

	//! The picture is displayed according to the parameters set by the user.
	void CMovingBitmap::ShowBitmapBySetting() {
		if (isAnimation == true && clock() - last_time >= delayCount) {
			frameIndex += 1;
			last_time = clock();
			if (frameIndex == surfaceID.size() && animationCount > 0) {
				animationCount -= 1;
			}
			if (frameIndex == surfaceID.size() && (isOnce || animationCount == 0)) {
				isAnimation = false;
				isAnimationDone = true;
				frameIndex = surfaceID.size() - 1;
				return;
			}
			frameIndex = frameIndex % surfaceID.size();
		}
	}

	//! Get the name of the object to load into the picture.
	/*!
		\return Returns the picture name, or an empty string if the picture has not yet been loaded.
	*/
	string CMovingBitmap::GetImageFileName() {
		return imageFileName;
	}

	//! Get the color of the object to filter.
	/*!
		\return Return the filter color, or `CLR_INVALID` if the object does not set the filter color.
	*/
	COLORREF CMovingBitmap::GetFilterColor() {
		return filterColor;
	}

	//! Whether the two objects overlap.
	/*!
		\param bmp1 The first CMovingBitmap object
		\param bmp2 The second CMovingBitmap object
		\return The return Bollinger value represents whether the two objects overlap.
	*/
	bool CMovingBitmap::IsOverlap(CMovingBitmap bmp1, CMovingBitmap bmp2) {
		CRect rect;
		BOOL isOverlap = rect.IntersectRect(bmp1.locations[bmp1.GetFrameIndexOfBitmap()], bmp2.locations[bmp2.GetFrameIndexOfBitmap()]);
		return isOverlap;
	}

	/////////////////////////////////////////////////////////////////////////////
	// CTextDraw: The class provide the ability to draw the text.
	// This class provides text presentation
	// You must know how to call (use) its various capabilities, but you may not know what the following programs mean
	/////////////////////////////////////////////////////////////////////////////

	//! The text is printed on the surface of the painting.
	/*!
		We give the responsibility of pDC acquisition to the caller, you have to get the current pDC pointer and then remember to release it.
		\param pDC，A CDC pointer, which can be obtained using `CDDraw::GetBackCDC()`.
		\param x Top left corner of text display x Coordinates
		\param y Top left corner of text display y Coordinates
		\param str Words to show
	*/
	void CTextDraw::Print(CDC *pDC, int x, int y, string str) {
		x = CDDraw::IsFullScreen() ? x + (RESOLUTION_X - SIZE_X) / 2 : x;
		y = CDDraw::IsFullScreen() ? y + (RESOLUTION_Y - SIZE_Y) / 2 : y;
		pDC->TextOut(x, y, str.c_str());
	}

	//! Set the attribute of the current text.
	/*!
		We give the responsibility of pDC acquisition to the caller, you have to get the current pDC pointer and then remember to release it.
		This setting will lose the set value when the set pDC pointer is released.
		\param pDC，A CDC pointer, which can be obtained using `CDDraw::GetBackCDC()`.
		\param size The size of the text (in pt, but not always exactly in pt due to technical limitations)
		\param fontName Font Name
		\param fontColor Font Color
		\param weight Font Boldness (default is 500)
	*/
	void CTextDraw::ChangeFontLog(CDC *pDC, int size, string fontName, COLORREF fontColor, int weight) {
		CFont* fp;

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(fontColor);
		LOGFONT lf;
		CFont f;
		memset(&lf, 0, sizeof(lf));
		lf.lfHeight = -MulDiv(size, GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY), 96);
		lf.lfWeight = weight;
		strcpy(lf.lfFaceName, fontName.c_str());
		f.CreateFontIndirect(&lf);
		fp = pDC->SelectObject(&f);
	}

}         
