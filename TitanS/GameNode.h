#pragma once

// 백버퍼 이미지를 정적변수로 만들어 두기
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode
{
private:
	HDC _hdc;				// 화면 HDC
	bool _managerInit;		// 매니저 초기화 여부

public:
	virtual HRESULT init();	// void를 사용해도 됨. HRESULT: 정상적인 종료 여부 등의 여러 값을 가질 수 있음. 제일 많이 사용하는 것이 S_OK(정상 종료), E_FAIL(에러 발생)
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	// 백버퍼 이미지 얻기
	Image* getBackBuffer() { return _backBuffer; }

	// 메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	// HDC 얻기 (화면DC)
	HDC getHDC() { return _hdc; }

	// 메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} // 소멸자에 virtual 키워드를 붙이는 이유 면접시 단골질문
};

