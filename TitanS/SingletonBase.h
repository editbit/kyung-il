#pragma once


//=============================================================
//	## singletonBase ## (�̱��� ����)
//=============================================================

template <typename T>
class SingletonBase
{
protected:
	// �̱��� �ν��Ͻ� ����
	static T* singleton;

	SingletonBase() {}
	virtual ~SingletonBase() {}

public:
	// �̱��� ��������
	static T* getSingleton();
	// �̱��� �޸𸮿��� �����ϱ�
	void releaseSingleton();


};
// �̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleton = 0;

template<typename T>
inline T * SingletonBase<T>::getSingleton()
{
	// �̱����� ������ ���� ����
	if (!singleton)	singleton = new T;

	return singleton;
}

// �̱��� �޸𸮿��� ����
template<typename T>
inline void SingletonBase<T>::releaseSingleton()
{
	// �̱����� �������� ���� ����
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
