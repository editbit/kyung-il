#include "stdafx.h"
#include "ImageManager.h"


HRESULT ImageManager::init()
{
	return S_OK;
}

void ImageManager::release()
{
	this->deleteAll();
}

// �� ��Ʈ������ �ʱ�ȭ
Image * ImageManager::addImage(string strKey, int width, int height)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image * img = findImage(strKey);
	
	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	// ���ٸ� �̹����� ���� ����
	img = new Image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/* STL ���� �ٽ� */
	// Ű, ��
	// ù ��° = Ű => first
	// �� ��° = ��(value) => second
	// �����͸� �߰��� �� Ű, ���� ������ �־�� �Ѵ�.
	// pair, make_pair�� ����ؼ� �߰��Ѵ�.
	// pair�� ��� ��������� Ű�� ���� �ڷ����� ����ؾ��Ѵ�.
	//		=> pair<string, Image*>(strKey, img));
	//				=> _mImageList.insert(pair<string, Image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

// �̹��� ���Ϸ� �ʱ�ȭ ( �ַ� ��� )
Image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image * img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	// ���ٸ� �̹����� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image * img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	// ���ٸ� �̹����� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// ������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
Image * ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image * img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	// ���ٸ� �̹����� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image * img = findImage(strKey);

	// �߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	// ���ٸ� �̹����� ���� ����
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// �̹��� Ű������ ã��
Image * ImageManager::findImage(string strKey)
{
	// �ش� Ű �̻�
	mapImageIter key = _mImageList.find(strKey);

	// �˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		return key->second;
	}

	// �˻��� Ű�� �̹����� �� ã�Ҵٸ� NULL ��ȯ
	return NULL;
}

// �̹��� Ű������ ����
BOOL ImageManager::deleteImage(string strKey)
{
	// �ش� Ű �̻�
	mapImageIter key = _mImageList.find(strKey);

	// �˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return TRUE;
	}

	// �˻��� Ű�� �̹����� �� ã�Ҵٸ� NULL ��ȯ
	return FALSE;
}

// �̹��� ��ü ����
bool ImageManager::deleteAll()
{
	// �� ��ü�� ���鼭 �ϳ��� ���� �����
	mapImageIter iter = _mImageList.begin();

	for (;iter != _mImageList.end();)
	{
		// �̹����� ������ �̹��� Ŭ���� ����
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);

			iter = _mImageList.erase(iter);
		}
		else	// �̹����� ������
		{
			++iter;
		}
	}

	// �� ��ü�� ����
	_mImageList.clear();

	return TRUE;
}


//=============================================================
//	## �Ϲ� ���� ##
//=============================================================
void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	// �̹����� ã�Ƽ� �׳� ������Ű�� ��
	Image* img = findImage(strKey);

	if(img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	// �̹����� ã�Ƽ� �׳� ������Ű�� ��
	Image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}


//=============================================================
//	## ���� ���� ## 
//=============================================================
void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	Image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}


//=============================================================
//	## ������ ���� ##
//=============================================================
void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}
