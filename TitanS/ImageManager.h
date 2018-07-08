#pragma once
#include "SingletonBase.h"

//=============================================================
//	## ImangeManager ## ( �̹��� �Ŵ��� )
//=============================================================
class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*> mapImageList;				// ������ ���� �̹��� ���
	typedef map<string, Image*>::iterator mapImageIter;		// ������ ���� �̹�������� �ݺ���
	
private:
	mapImageList _mImageList;		// ���� �̹��� Ŭ������ ���� STL ��

public:
	// �̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init();
	// �̹��� �Ŵ��� ����
	void release();


	// �� ��Ʈ������ �ʱ�ȭ
	Image* addImage(string strKey, int width, int height);
	// �̹��� ���Ϸ� �ʱ�ȭ ( �ַ� ��� )
	Image* addImage(string strKey, const char * fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// ������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	Image* addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	Image* addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	// �̹��� Ű������ ã��
	Image* findImage(string strKey);
	// �̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	// �̹��� ��ü ����
	bool deleteAll();




//=============================================================
//	## �Ϲ� ���� ##
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//=============================================================
//	## ���� ���� ## 
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//=============================================================
//	## ������ ���� ##
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);



	ImageManager() {}
	~ImageManager() {}
};

