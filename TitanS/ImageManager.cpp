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

// 빈 비트맵으로 초기화
Image * ImageManager::addImage(string strKey, int width, int height)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image * img = findImage(strKey);
	
	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	// 없다면 이미지를 새로 생성
	img = new Image;
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/* STL 맵의 핵심 */
	// 키, 값
	// 첫 번째 = 키 => first
	// 두 번째 = 값(value) => second
	// 데이터를 추가할 때 키, 값을 쌍으로 넣어야 한다.
	// pair, make_pair를 사용해서 추가한다.
	// pair의 경우 명시적으로 키와 값의 자료형을 명시해야한다.
	//		=> pair<string, Image*>(strKey, img));
	//				=> _mImageList.insert(pair<string, Image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));
	
	return img;
}

// 이미지 파일로 초기화 ( 주로 사용 )
Image * ImageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image * img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	// 없다면 이미지를 새로 생성
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
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image * img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	// 없다면 이미지를 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 프레임 이미지 파일로 초기화 (주 사용)
Image * ImageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image * img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	// 없다면 이미지를 새로 생성
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
	// 추가하려는 이미지가 존재하는지 키값으로 확인
	Image * img = findImage(strKey);

	// 추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	// 없다면 이미지를 새로 생성
	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// 이미지 키값으로 찾기
Image * ImageManager::findImage(string strKey)
{
	// 해당 키 겁색
	mapImageIter key = _mImageList.find(strKey);

	// 검색한 키를 찾았다면 이미지클래스 리턴
	if (key != _mImageList.end())
	{
		return key->second;
	}

	// 검색한 키로 이미지를 못 찾았다면 NULL 반환
	return NULL;
}

// 이미지 키값으로 삭제
BOOL ImageManager::deleteImage(string strKey)
{
	// 해당 키 겁색
	mapImageIter key = _mImageList.find(strKey);

	// 검색한 키를 찾았다면 이미지클래스 리턴
	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);

		_mImageList.erase(key);

		return TRUE;
	}

	// 검색한 키로 이미지를 못 찾았다면 NULL 반환
	return FALSE;
}

// 이미지 전체 삭제
bool ImageManager::deleteAll()
{
	// 맵 전체를 돌면서 하나씩 전부 지운다
	mapImageIter iter = _mImageList.begin();

	for (;iter != _mImageList.end();)
	{
		// 이미지가 있으면 이미지 클래스 삭제
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);

			iter = _mImageList.erase(iter);
		}
		else	// 이미지가 없으면
		{
			++iter;
		}
	}

	// 맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}


//=============================================================
//	## 일반 렌더 ##
//=============================================================
void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	// 이미지를 찾아서 그냥 렌더시키면 됨
	Image* img = findImage(strKey);

	if(img) img->render(hdc, destX, destY);
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	// 이미지를 찾아서 그냥 렌더시키면 됨
	Image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}


//=============================================================
//	## 알파 렌더 ## 
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
//	## 프레임 렌더 ##
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
