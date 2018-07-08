#include "stdafx.h"
#include "Image.h"
Image::Image()
	: _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _blendImage(NULL), _transColor(RGB(0, 0, 0)), _scaleImage(NULL)
{
}
Image::~Image()
{
}


//=============================================================
//	## 초기화 ## 
//=============================================================
HRESULT Image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 알파블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->redID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForScale()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_scaleImage = new IMAGE_INFO;
	_scaleImage->loadType = LOAD_FILE;
	_scaleImage->redID = 0;
	_scaleImage->hMemDC = CreateCompatibleDC(hdc);
	_scaleImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_scaleImage->hOBit = (HBITMAP)SelectObject(_scaleImage->hMemDC, _scaleImage->hBit);
	_scaleImage->width = WINSIZEX;
	_scaleImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release()
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	// 알파블렌드 이미지 정보가 있다면
	if (_blendImage)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		// 포인터 삭제
		SAFE_DELETE(_blendImage);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,					//복사될 좌표 시작점 X
			0,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									// 알파블렌드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									// 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	// 알파블렌드를 처음 사용한다면
	// 알파블렌드를 사용할 수 있도록 초기화
	if (!_blendImage) this->initForAlphaBlend();

	// 알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 블렌드이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 블렌드이미지를 화면에 그린다
									// 알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할 때
	{
		// 알파블렌드
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}


//=============================================================
//	## 프레임 렌더 ##
//=============================================================
void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,													//복사할 장소의 DC
			destX,													//복사될 좌표 시작점 X
			destY,													//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//X축 복사 시작 지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//Y축 복사 시작 지점
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor);											//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY)
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,													//복사할 장소의 DC
			destX,													//복사될 좌표 시작점 X
			destY,													//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//X축 복사 시작 지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//Y축 복사 시작 지점
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor);											//복사할때 제외할 색상 (마젠타)
	}
	else //원본 이미지 그래도 출력할꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}


//=============================================================
//	## 루프렌더 ##
//=============================================================

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(알파렌더-이미지잘라서붙이기)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void Image::scaleRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	/*

	BLACKONWHITE = STRETCH_ANDSCANS

	AND 논리 연산을 사용한다. 흰색을 생략하고 검정색을 보존한다. 검정색이 우선 보존된다.

	WHITEONBLACK = STRETCH_ORSCANS

	OR 논리 연산을 사용한다. 검정색을 생략하고 흰색을 보존한다. 흰색이 우선 보존된다.

	COLORONCOLOR = STRETCH_DELETESCANS

	생략되는 픽셀을 별도의 논리 연산없이 삭제한다.

	HALFTONE = STRETCH_HALFTONE

	복사대상과 복사원의 사각 블록끼리 대입하여 평균 색상을 구한다. 95/98에서 이 모드는 지원되지 않는다.
	*/
	if (!_scaleImage) this->initForScale();

	if (_isTrans) //배경색 없앤 후 스케일 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 스케일이미지에 그린다
		BitBlt(_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 스케일이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_scaleImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 스케일이미지를 화면에 그린다

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, destWidth, destHeight,
			_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight, SRCCOPY);
	}
	else //원본 이미지 그대로 스케일 할 때
	{
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, destWidth, destHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);
	}
}



void Image::scaleAlphaRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_scaleImage) this->initForScale();
	if (!_blendImage) this->initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 스케일 할 때
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 스케일이미지에 그린다
		BitBlt(_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. 메모리DC 이미지의 배경을 없앤후 다시 스케일이미지에 그린다
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_scaleImage->hMemDC,					//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			sourWidth,		//복사될 이미지 가로크기
			sourHeight,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX, sourY,					//복사 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)

									//3. 스케일이미지를 화면에 그린다

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_blendImage->hMemDC, 0, 0, destWidth, destHeight,
			_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight, SRCCOPY);


		AlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_blendImage->hMemDC, 0, 0, destWidth, destHeight, _blendFunc);
	}
	else //원본 이미지 그대로 스케일 할 때
	{

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_blendImage->hMemDC, 0, 0, destWidth, destHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, SRCCOPY);

		AlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_blendImage->hMemDC, 0, 0, destWidth, destHeight, _blendFunc);


		/*AlphaBlend(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
		_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, destWidth, destHeight,
		_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, SRCCOPY);*/
	}
}
