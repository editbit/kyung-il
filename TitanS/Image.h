#pragma once

//=============================================================
//	## Image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================
class Image
{   
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	// ���ҽ� �ε�
		LOAD_FILE,			// ���Ϸ� �ε�
		LOAD_EMPTY,			// �� ��Ʈ�� �ε�
		LOAD_END
	};

	typedef struct TagImage
	{
		DWORD		redID;				// ���ҽ� ID,		unsigned long
		HDC			hMemDC;				// �޸� DC
		HBITMAP		hBit;				// ��Ʈ��
		HBITMAP		hOBit;				// �õ� ��Ʈ��
		float		x;					// �̹��� x��ǥ
		float		y;					// �̹��� y��ǥ
		int			width;				// �̹��� ���� ũ��
		int			height;				// �̹��� ���� ũ��
		int			currentFrameX;		// ���� ������x
		int			currentFrameY;		// ���� ������y
		int			maxFrameX;			// �ִ� x������ ����
		int			maxFrameY;			// �ִ� y������ ����
		int			frameWidth;			// 1�������� ���α���
		int			frameHeight;		// 1�������� ���α���
		BYTE		loadType;			// �̹��� �ε� Ÿ��,	unsigned char

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
	LPIMAGE_INFO	_imageInfo;		// �̹��� ����
	CHAR*			_fileName;		// �̹��� �̸�
	BOOL			_isTrans;		// ���� ����( true�̸� ��� ����� )
	COLORREF		_transColor;	// ���� ���� RGB �ڵ� ( ����Ÿ = RGB(255, 0, 255) )

	LPIMAGE_INFO	_blendImage;	// ���ĺ��� �̹���
	BLENDFUNCTION	_blendFunc;		// ���ĺ��� ���

	LPIMAGE_INFO _scaleImage;

public:
	Image();
	~Image();

	//=============================================================
	//	## �ʱ�ȭ ## 
	//=============================================================
	// �� ��Ʈ������ �ʱ�ȭ
	HRESULT init(int width, int height);
	// �̹��� ���ҽ��� �ʱ�ȭ( ��� ���� )
	HRESULT init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ ( �ַ� ��� )
	HRESULT init(const char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char * fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	HRESULT init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// ���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend();
	// ������ �̹��� �ʱ�ȭ
	HRESULT initForScale();


	//=============================================================
	//	## ���� ##
	//=============================================================
	void release();


	//=============================================================
	//	## �Ϲ� ���� ##
	//=============================================================
	void render(HDC hdc, int destX = 0, int destY = 0);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//=============================================================
	//	## ���� ���� ## 
	//=============================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//=============================================================
	//	## ������ ���� ##
	//=============================================================
	void frameRender(HDC hdc, int destX = 0, int destY = 0);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//=============================================================
	//	## �������� ##
	//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//=============================================================
	//	## �����Ϸ��� ##
	//=============================================================
	void scaleRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight);
	void scaleAlphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);



	//=============================================================
	//	## inline ## (�ζ��� �Լ��� - ����, ����) 
	//=============================================================

	// DC ���
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	// �̹��� x��ǥ
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// �̹��� y��ǥ
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// �̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	// �̹��� ����, ���� ũ��
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	// �ٿ�� �ڽ�( �浹�� ��Ʈ )
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

	// ������ x
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	// ������ y
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� �� �������� ����, ���� ũ��
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	// �ƽ� ������ x, y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

};

