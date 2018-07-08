#pragma once

// ����� �̹����� ���������� ����� �α�
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class GameNode
{
private:
	HDC _hdc;				// ȭ�� HDC
	bool _managerInit;		// �Ŵ��� �ʱ�ȭ ����

public:
	virtual HRESULT init();	// void�� ����ص� ��. HRESULT: �������� ���� ���� ���� ���� ���� ���� �� ����. ���� ���� ����ϴ� ���� S_OK(���� ����), E_FAIL(���� �߻�)
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	// ����� �̹��� ���
	Image* getBackBuffer() { return _backBuffer; }

	// �޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	// HDC ��� (ȭ��DC)
	HDC getHDC() { return _hdc; }

	// ���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {} // �Ҹ��ڿ� virtual Ű���带 ���̴� ���� ������ �ܰ�����
};

