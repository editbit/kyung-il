#pragma once
#include "SingletonBase.h"

//=============================================================
//	## KeyManager ## ( 키 매니저 )
//=============================================================

#define KEYMAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	// 키 매니저 초기화. 
	HRESULT init();
	// 키 매니저 해제
	void release();

	// 키가 한 번만 눌렸나?
	bool isOnceKeyDown(int key);

	// 키가 한 번 눌렀다 땠나?
	bool isOnceKeyUp(int key);

	// 키가 계속 눌린 상태인가?
	bool isStayKeyDown(int key);

	// 토글키냐?
	bool isToggleKey(int key);

	KeyManager() {}
	~KeyManager() {}
};

