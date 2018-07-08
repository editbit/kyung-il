#pragma once
#include "GameNode.h"
class GameStartScene :
	public GameNode
{
private:
	int aniCount;
	int aniIndex;

	Image * _bgImage;
	Image * loadingImage[3];

	bool playingScene;

public:


	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render();

	bool isEnd() { return !playingScene; }

	GameStartScene() {}
	~GameStartScene() {}
};

