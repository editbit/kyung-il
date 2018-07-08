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
//	## �ʱ�ȭ ## 
//=============================================================
HRESULT Image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ����
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
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

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� ����
	if (_imageInfo->hBit == 0)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	// ���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->redID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForScale()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_scaleImage = new IMAGE_INFO;
	_scaleImage->loadType = LOAD_FILE;
	_scaleImage->redID = 0;
	_scaleImage->hMemDC = CreateCompatibleDC(hdc);
	_scaleImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_scaleImage->hOBit = (HBITMAP)SelectObject(_scaleImage->hMemDC, _scaleImage->hBit);
	_scaleImage->width = WINSIZEX;
	_scaleImage->height = WINSIZEY;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//���� �÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	// ���ĺ��� �̹��� ������ �ִٸ�
	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		// ������ ����
		SAFE_DELETE(_blendImage);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ X
			destY,					//����� ��ǥ ������ Y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ X
			destY,					//����� ��ǥ ������ Y
			sourWidth,		//����� �̹��� ����ũ��
			sourHeight,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,					//���� ��������
			sourWidth,		//���� ���� ����ũ��
			sourHeight,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// ���ĺ��带 ó�� ����Ѵٸ�
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) this->initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //���� ���� �� ���ĺ��� �� ��
	{
		//1. ����ؾ� �� ȭ��DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//2. �޸�DC �̹����� ����� ������ �ٽ� �����̹����� �׸���
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,					//������ ����� DC
			0,					//����� ��ǥ ������ X
			0,					//����� ��ǥ ������ Y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

									//3. �����̹����� ȭ�鿡 �׸���
									// ���ĺ���
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �� ��
	{
		// ���ĺ���
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// ���ĺ��带 ó�� ����Ѵٸ�
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) this->initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //���� ���� �� ���ĺ��� �� ��
	{
		//1. ����ؾ� �� ȭ��DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//2. �޸�DC �̹����� ����� ������ �ٽ� �����̹����� �׸���
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,					//������ ����� DC
			0,						//����� ��ǥ ������ X
			0,						//����� ��ǥ ������ Y
			_imageInfo->width,		//����� �̹��� ����ũ��
			_imageInfo->height,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//���� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

									//3. �����̹����� ȭ�鿡 �׸���
									// ���ĺ���
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �� ��
	{
		// ���ĺ���
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	// ���ĺ��带 ó�� ����Ѵٸ�
	// ���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ
	if (!_blendImage) this->initForAlphaBlend();

	// ���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //���� ���� �� ���ĺ��� �� ��
	{
		//1. ����ؾ� �� ȭ��DC�� �׷��� �ִ� ������ �����̹����� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. �޸�DC �̹����� ����� ������ �ٽ� �����̹����� �׸���
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,					//������ ����� DC
			0,						//����� ��ǥ ������ X
			0,						//����� ��ǥ ������ Y
			sourWidth,		//����� �̹��� ����ũ��
			sourHeight,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,					//���� ��������
			sourWidth,		//���� ���� ����ũ��
			sourHeight,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

									//3. �����̹����� ȭ�鿡 �׸���
									// ���ĺ���
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �� ��
	{
		// ���ĺ���
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}


//=============================================================
//	## ������ ���� ##
//=============================================================
void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,													//������ ����� DC
			destX,													//����� ��ǥ ������ X
			destY,													//����� ��ǥ ������ Y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//X�� ���� ���� ����
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//Y�� ���� ���� ����
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor);											//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// �̹��� ����ó��
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY)
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,													//������ ����� DC
			destX,													//����� ��ǥ ������ X
			destY,													//����� ��ǥ ������ Y
			_imageInfo->frameWidth,									//����� �̹��� ����ũ��
			_imageInfo->frameHeight,								//����� �̹��� ����ũ��
			_imageInfo->hMemDC,										//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//X�� ���� ���� ����
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//Y�� ���� ���� ����
			_imageInfo->frameWidth,									//���� ���� ����ũ��
			_imageInfo->frameHeight,								//���� ���� ����ũ��
			_transColor);											//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}


//=============================================================
//	## �������� ##
//=============================================================

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(���ķ���-�̹����߶󼭺��̱�)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void Image::scaleRender(HDC hdc, int destX, int destY, int destWidth, int destHeight, int sourX, int sourY, int sourWidth, int sourHeight)
{
	/*

	BLACKONWHITE = STRETCH_ANDSCANS

	AND �� ������ ����Ѵ�. ����� �����ϰ� �������� �����Ѵ�. �������� �켱 �����ȴ�.

	WHITEONBLACK = STRETCH_ORSCANS

	OR �� ������ ����Ѵ�. �������� �����ϰ� ����� �����Ѵ�. ����� �켱 �����ȴ�.

	COLORONCOLOR = STRETCH_DELETESCANS

	�����Ǵ� �ȼ��� ������ �� ������� �����Ѵ�.

	HALFTONE = STRETCH_HALFTONE

	������� ������� �簢 ��ϳ��� �����Ͽ� ��� ������ ���Ѵ�. 95/98���� �� ���� �������� �ʴ´�.
	*/
	if (!_scaleImage) this->initForScale();

	if (_isTrans) //���� ���� �� ������ �� ��
	{
		//1. ����ؾ� �� ȭ��DC�� �׷��� �ִ� ������ �������̹����� �׸���
		BitBlt(_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. �޸�DC �̹����� ����� ������ �ٽ� �������̹����� �׸���
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_scaleImage->hMemDC,					//������ ����� DC
			0,						//����� ��ǥ ������ X
			0,						//����� ��ǥ ������ Y
			sourWidth,		//����� �̹��� ����ũ��
			sourHeight,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,					//���� ��������
			sourWidth,		//���� ���� ����ũ��
			sourHeight,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

									//3. �������̹����� ȭ�鿡 �׸���

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, destWidth, destHeight,
			_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight, SRCCOPY);
	}
	else //���� �̹��� �״�� ������ �� ��
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

	if (_isTrans) //���� ���� �� ������ �� ��
	{
		//1. ����ؾ� �� ȭ��DC�� �׷��� �ִ� ������ �������̹����� �׸���
		BitBlt(_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight,
			hdc, destX, destY, SRCCOPY);

		//2. �޸�DC �̹����� ����� ������ �ٽ� �������̹����� �׸���
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_scaleImage->hMemDC,					//������ ����� DC
			0,						//����� ��ǥ ������ X
			0,						//����� ��ǥ ������ Y
			sourWidth,		//����� �̹��� ����ũ��
			sourHeight,		//����� �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX, sourY,					//���� ��������
			sourWidth,		//���� ���� ����ũ��
			sourHeight,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

									//3. �������̹����� ȭ�鿡 �׸���

		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(_blendImage->hMemDC, 0, 0, destWidth, destHeight,
			_scaleImage->hMemDC, 0, 0, sourWidth, sourHeight, SRCCOPY);


		AlphaBlend(hdc, destX, destY, destWidth, destHeight,
			_blendImage->hMemDC, 0, 0, destWidth, destHeight, _blendFunc);
	}
	else //���� �̹��� �״�� ������ �� ��
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
