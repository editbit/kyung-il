#pragma once
#include "GameNode.h"




class MainGame : public GameNode
{
private:
	Image * _bgImage;

	GameEndScene * endScene;
	GameStartScene *startScene;
	GamePlayScene *playScene;
	GameNode * currentScene;

	int _loopX, _loopY, _alpha;

public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render();

	MainGame() {}
	virtual ~MainGame() {}
};
