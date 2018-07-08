#include "stdafx.h"
#include "GameStartScene.h"


HRESULT GameStartScene::init()
{
	playingScene = true;
	//_bgImage = IMAGEMANAGER->addFrameImage("startBackground", "resource\\startBackground_5760x1080.bmp", 5760, 1080, 3, 1);
	_bgImage = IMAGEMANAGER->addFrameImage("startBackground", "resource\\startBackground_5760x1080.bmp", WINSIZEX * 3, WINSIZEY, 3, 1);

	loadingImage[0] = IMAGEMANAGER->addImage("loadingImage1", "resource\\loadingImage1.bmp", WINSIZEX, WINSIZEY);
	loadingImage[1] = IMAGEMANAGER->addImage("loadingImage2", "resource\\loadingImage2.bmp", WINSIZEX, WINSIZEY);
	loadingImage[2] = IMAGEMANAGER->addImage("loadingImage3", "resource\\loadingImage3.bmp", WINSIZEX, WINSIZEY);

	aniIndex = aniCount = 0;

	return S_OK;
}

void GameStartScene::release()
{
}

void GameStartScene::update()
{
}

void GameStartScene::render()
{
	aniCount = (aniCount + 1) % 10;
	if (aniCount == 1)
	{
		_bgImage->setFrameX(aniIndex);
		aniIndex = (aniIndex + 1) % _bgImage->getMaxFrameX();
	}
	_bgImage->frameRender(getMemDC(), 0, 0);
}

