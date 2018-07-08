#pragma once
#include "GameNode.h"

#define MAX_MAP 2

struct Goliath
{
	enum { HEAD, BODY, SHOULDER, HAND, BOTTOM1, BOTTOM2, PAINT };

	float x, y;
	int headAniIndex;
	int aniCount;
	int appearCount;

	int state;

	Image * shape[7];



	Goliath() {
		for (int i = 0; i < 4; ++i)
		{
			shape[i] = new Image;
		}
		shape[HEAD] = IMAGEMANAGER->addFrameImage("head", "resource\\goliathHead_500x100.bmp", 500, 100, 5, 1);
		shape[BODY] = IMAGEMANAGER->addImage("body", "resource\\goliathBody_176x206.bmp", 176, 206, true, RGB(255, 0, 255));
		shape[SHOULDER] = IMAGEMANAGER->addFrameImage("shoulder", "resource\\goliathShoulder_76x160.bmp", 76, 160, 1, 2);
		shape[HAND] = IMAGEMANAGER->addFrameImage("head", "resource\\goliathHands_288x168.bmp", 288, 168, 3, 2);
		shape[BOTTOM1] = IMAGEMANAGER->addImage("bottom1", "resource\\goliathBottom_240x106.bmp", 240, 106, true, RGB(255, 0, 255));
		shape[BOTTOM2] = IMAGEMANAGER->addImage("bottom2", "resource\\bottom_240x22.bmp", 240, 22, true, RGB(255, 0, 255));
		shape[PAINT] = IMAGEMANAGER->addImage("paint", "resource\\goliathBPaint_148x80.bmp", 148, 80, true, RGB(255, 0, 255));

		x = 300; y = 100;
		headAniIndex = 0;
		aniCount = 0;
		appearCount = 0;
		state = 1;
	}
	~Goliath() {}


	void appear(HDC hdc, int _h)
	{
		//276
		int _y = (int)y + 276 - _h;
		int bodyH = _h, headH = _h, shoulderH = _h;


		if (_h > 70)
		{
			bodyH = _h - 70;
			if (_h - 70 > shape[BODY]->getHeight())
			{
				bodyH = shape[BODY]->getHeight();
			}
			shape[BODY]->render(hdc, x + 38, _y + 70, 0, 0, shape[BODY]->getWidth(), bodyH);
		}

		if (_h > 0)
		{
			if (_h > shape[HEAD]->getFrameHeight())
			{
				headH = shape[HEAD]->getHeight();
			}
			shape[HEAD]->render(hdc, x + 38 + 88 - 50, _y, 0, 0, shape[HEAD]->getFrameWidth(), headH);
		}
		if (_h > 70)
		{
			shoulderH = _h - 70;
			if (_h - 70 > shape[SHOULDER]->getFrameHeight())
			{
				shoulderH = shape[SHOULDER]->getFrameHeight();
			}
			shape[SHOULDER]->setFrameY(0);
			shape[SHOULDER]->render(hdc, x + 176, _y + 70, 0, 0, shape[SHOULDER]->getFrameWidth(), shoulderH);
			shape[SHOULDER]->setFrameY(1);
			shape[SHOULDER]->render(hdc, x, _y + 70, 0, shape[SHOULDER]->getFrameHeight(), shape[SHOULDER]->getFrameWidth(), shoulderH);
		}



		if (_y <= y)
		{
			state = 0;
			return;
		}
	}


	void render(HDC hdc)
	{

		shape[BODY]->render(hdc, x + 38, y + 70);
		shape[PAINT]->render(hdc, x + 51, y + 120);

		shape[HEAD]->setFrameX(headAniIndex);
		shape[HEAD]->frameRender(hdc, x + 38 + 88 - 50, y);
		if ((aniCount = aniCount + 1) % 10 == 0)
		{
			//headAniIndex = (headAniIndex + 1) % shape[HEAD]->getMaxFrameX();
			headAniIndex++;
			if (headAniIndex >= shape[HEAD]->getMaxFrameX())
				headAniIndex = shape[HEAD]->getMaxFrameX();
		}

		shape[SHOULDER]->setFrameY(0);
		shape[SHOULDER]->frameRender(hdc, x + 176, y + 70);
		shape[SHOULDER]->setFrameY(1);
		shape[SHOULDER]->frameRender(hdc, x, y + 70);

	}
};


class GamePlayScene :
	public GameNode
{
private:
	Player * player;

	int count, index;
	int golAppear;

	float x = WINSIZEX/2, y = WINSIZEY/2 + 100;
	float gx, gy;

	int curMap;
	Stage map[MAX_MAP];

	RECT camera;
	Image * _bgImage;

public:

	virtual HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual void release();
	virtual void update();
	virtual void render();

	void setCamera(int x, int y);
	void initStage();

	void rendWallRECT();
	void collide();

	GamePlayScene() {}
	~GamePlayScene() {}
};

