#pragma once
#include "SingletonBase.h"

//=============================================================
//	## ImangeManager ## ( 이미지 매니저 )
//=============================================================
class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*> mapImageList;				// 맵으로 만든 이미지 목록
	typedef map<string, Image*>::iterator mapImageIter;		// 맵으로 만든 이미지목록의 반복자
	
private:
	mapImageList _mImageList;		// 실제 이미지 클래스를 담을 STL 맵

public:
	// 이미지 매니저 초기화
	HRESULT init();
	// 이미지 매니저 해제
	void release();


	// 빈 비트맵으로 초기화
	Image* addImage(string strKey, int width, int height);
	// 이미지 파일로 초기화 ( 주로 사용 )
	Image* addImage(string strKey, const char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 파일로 초기화 (주 사용)
	Image* addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	Image* addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// 이미지 키값으로 찾기
	Image* findImage(string strKey);
	// 이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	// 이미지 전체 삭제
	bool deleteAll();




//=============================================================
//	## 일반 렌더 ##
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//=============================================================
//	## 알파 렌더 ## 
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## 프레임 렌더 ##
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);



	ImageManager() {}
	~ImageManager() {}
};

