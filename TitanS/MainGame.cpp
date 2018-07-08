#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	// �̰����� �ʱ�ȭ�� �Ѵ�.
	//_bgImage = IMAGEMANAGER->addImage("���", "resource\\stage1.bmp", WINSIZEX, WINSIZEY);


	startScene = new GameStartScene;
	startScene->init();

	playScene = new GamePlayScene;
	playScene->init();

	endScene = new GameEndScene;
	endScene->init();

	currentScene = startScene;

	_loopX = _loopY = 0;


	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void MainGame::release(void)
{
	GameNode::release();
	// �̹��� Ŭ���� ���� ������ ��� X
	// init�Լ����� �����Ҵ��� �޸𸮸� delete�� �������ش�.

	startScene->release();
	endScene->release();
	playScene->release();

	SAFE_DELETE(startScene);
	SAFE_DELETE(endScene);
	SAFE_DELETE(playScene);

}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// �̰����� ����, Ű����, ���콺 ��� ������Ʈ�� �Ѵ�
	// �����Ѱ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�.


	//��׶��� ����
	//_loopX++;
	//_loopX += 3;
	//_loopY++;

	currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(' '))
	{
		currentScene = playScene;
		currentScene->init();
	}
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void MainGame::render()
{
	// ��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	/*
	font = CreateFont(
	���� ũ��, ���� ��, ���� ����, ���� ����, ���� ����,
	����(bool), ����(bool), ��Ҽ�(bool),
	���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
	)
	*/
	// ���� ���� ����ũ�⿡ ���� ����ϰ� ǥ��. 0���� �δ� ���� ����
	
	/* ��Ʈ ����
	HFONT font;
	HFONT oldFont;

	font = CreateFont(70, 0, 0, 0, 600, false, false, true, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	char str[128];
	sprintf_s(str, "��Ʈ ����");
	TextOut(getMemDC(), 100, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	*/

//======================================================================================
	// ��� 1
	//_bgImage->render(getMemDC());
	// ��� 2
	//IMAGEMANAGER->render("���", getMemDC());
	// ��� 3
	//IMAGEMANAGER->findImage("���")->render(getMemDC());

	//RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	//_bgImage->loopRender(getMemDC(), &rc, _loopX, _loopY);
	//_bgImage->loopAlphaRender(getMemDC(), &rc, _loopX, _loopY, _alpha);
	
	
	currentScene->render();

//======================================================================================
	// ������� ������ HDC�� �׸��� 
	this->getBackBuffer()->render(getHDC());
}
