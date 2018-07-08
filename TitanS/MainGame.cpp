#include "stdafx.h"
#include "MainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	// 이곳에서 초기화를 한다.
	//_bgImage = IMAGEMANAGER->addImage("배경", "resource\\stage1.bmp", WINSIZEX, WINSIZEY);


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
//	## 해제 ## release(void)
//=============================================================
void MainGame::release(void)
{
	GameNode::release();
	// 이미지 클래스 나갈 때까진 사용 X
	// init함수에서 동적할당한 메모리만 delete로 해제해준다.

	startScene->release();
	endScene->release();
	playScene->release();

	SAFE_DELETE(startScene);
	SAFE_DELETE(endScene);
	SAFE_DELETE(playScene);

}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void MainGame::update(void)
{
	GameNode::update();
	// 이곳에서 계산식, 키보드, 마우스 등등 업데이트를 한다
	// 간단한게 이곳에서 코딩한다고 생각하면 된다.


	//백그라운드 루프
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
//	## 렌더 ## render(HDC hdc)
//=============================================================
void MainGame::render()
{
	// 흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	/*
	font = CreateFont(
	문자 크기, 문자 폭, 문자 기울기, 문자 방향, 문자 굵기,
	기울기(bool), 밑줄(bool), 취소선(bool),
	문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	)
	*/
	// 문자 폭은 문자크기에 따라 비례하게 표시. 0으로 두는 것이 좋음
	
	/* 폰트 사용법
	HFONT font;
	HFONT oldFont;

	font = CreateFont(70, 0, 0, 0, 600, false, false, true, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	char str[128];
	sprintf_s(str, "폰트 사용법");
	TextOut(getMemDC(), 100, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	*/

//======================================================================================
	// 방법 1
	//_bgImage->render(getMemDC());
	// 방법 2
	//IMAGEMANAGER->render("배경", getMemDC());
	// 방법 3
	//IMAGEMANAGER->findImage("배경")->render(getMemDC());

	//RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	//_bgImage->loopRender(getMemDC(), &rc, _loopX, _loopY);
	//_bgImage->loopAlphaRender(getMemDC(), &rc, _loopX, _loopY, _alpha);
	
	
	currentScene->render();

//======================================================================================
	// 백버퍼의 내용을 HDC에 그린다 
	this->getBackBuffer()->render(getHDC());
}
