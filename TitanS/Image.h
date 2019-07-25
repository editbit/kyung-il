#pragma once

//=============================================================
//	## Image ## (앞으로 계속 업데이트 된다)
//=============================================================
class Image
{   
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	// 리소스 로딩
		LOAD_FILE,			// 파일로 로딩
		LOAD_EMPTY,			// 빈 비트맵 로딩
		LOAD_END
	};

	typedef struct TagImage
	{
		DWORD		redID;				// 리소스 ID,		unsigned long
		HDC			hMemDC;				// 메모리 DC
		HBITMAP		hBit;				// 비트맵
		HBITMAP		hOBit;				// 올드 비트맵
		float		x;					// 이미지 x좌표
		float		y;					// 이미지 y좌표
		int			width;				// 이미지 가로 크기
		int			height;				// 이미지 세로 크기
		int			currentFrameX;		// 현재 프레임x
		int			currentFrameY;		// 현재 프레임y
		int			maxFrameX;			// 최대 x프레임 개수
		int			maxFrameY;			// 최대 y프레임 개수
		int			frameWidth;			// 1프레임의 가로길이
		int			frameHeight;		// 1프레임의 세로길이
		BYTE		loadType;			// 이미지 로드 타입,	unsigned char

		TagImage()
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		// 이미지 정보
	CHAR*			_fileName;		// 이미지 이름
	BOOL			_isTrans;		// 배경색 유무( true이면 배경 지우기 )
	COLORREF		_transColor;	// 지울 배경색 RGB 코드 ( 마젠타 = RGB(255, 0, 255) )

	LPIMAGE_INFO	_blendImage;	// 알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		// 알파블렌드 기능

	LPIMAGE_INFO _scaleImage;

public:
	Image();
	~Image();

	//=============================================================
	//	## 초기화 ## 
	//=============================================================
	// 빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	// 이미지 리소스로 초기화( 사용 안함 )
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화 ( 주로 사용 )
	HRESULT init(const char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char * fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 프레임 이미지 파일로 초기화 (주 사용)
	HRESULT init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// 알파블렌드 초기화
	HRESULT initForAlphaBlend();
	// 스케일 이미지 초기화
	HRESULT initForScale();


	//=============================================================
	//	## 해제 ##
	//=============================================================
	void release();


	//=============================================================
	//	## 일반 렌더 ##
	//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//=============================================================
	//	## 알파 렌더 ## 
	//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//=============================================================
	//	## 프레임 렌더 ##
	//=============================================================
	void frameRender(HDC hdc, int destX = 0, int destY = 0);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//=============================================================
	//	## 루프렌더 ##
	//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//=============================================================
	//	## 스케일렌더 ##
	//=============================================================
	void scaleRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	void scaleAlphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);



	//=============================================================
	//	## inline ## (인라인 함수들 - 겟터, 셋터) 
	//=============================================================

	// DC 얻기
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	// 이미지 x좌표
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// 이미지 y좌표
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	// 이미지 가로, 세로 크기
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	// 바운딩 박스( 충돌용 렉트 )
	inline RECT boundingBox()
	{
		return { (int)_imageInfo->x,							// left
			(int)_imageInfo->y,								// top
			(int)_imageInfo->x + _imageInfo->width,			// right
			(int)_imageInfo->y + _imageInfo->height };		// bottom
	}
	inline RECT boundingBoxWidthFrame()
	{
		return { (int)_imageInfo->x,							// left
			(int)_imageInfo->y,								// top
			(int)_imageInfo->x + _imageInfo->frameWidth,			// right
			(int)_imageInfo->y + _imageInfo->frameHeight };		// bottom
	}

	// 프레임 x
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	// 프레임 y
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 한 프레임의 가로, 세로 크기
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	// 맥스 프레임 x, y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

};

