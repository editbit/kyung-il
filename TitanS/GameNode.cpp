#include "stdafx.h"
#include "GameNode.h"


//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT GameNode::init()
{

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		SetTimer(_hWnd, 1, 10, NULL);			// 타이머 초기화
		KEYMANAGER->init();						// 키 매니저 초기화
		RND->init();
		IMAGEMANAGER->init();					// 이미지 매니저 초기화
	}

	return S_OK;
}


//=============================================================
//	## 해제 ## release(void)
//=============================================================
void GameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		// 키 매니저 싱글톤 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		// 랜덤펑션 싱글톤 해제 ( 싱글톤 연습 )
		RND->release();
		RND->releaseSingleton();
		// 이미지 매니저 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void GameNode::update()
{
	// 새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다.)
	// 더블버퍼링 이후 사용하지 않는다(true => false)
	InvalidateRect(_hWnd, NULL, FALSE);		// ture == TRUE
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void GameNode::render()
{

}

//=============================================================
//	## 메인프로시져 ##
//=============================================================
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:	//esc 키를 누르면 화면종료
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
