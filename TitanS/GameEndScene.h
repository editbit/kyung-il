#pragma once
#include "GameNode.h"
class GameEndScene :
	public GameNode
{
public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual void release();
	virtual void update();
	virtual void render();


          
   
	GameEndScene() {}
	~GameEndScene() {}
};

