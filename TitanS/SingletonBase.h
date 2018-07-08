#pragma once


//=============================================================
//	## singletonBase ## (싱글톤 패턴)
//=============================================================

template <typename T>
class SingletonBase
{
protected:
	// 싱글톤 인스턴스 선언
	static T* singleton;

	SingletonBase() {}
	virtual ~SingletonBase() {}

public:
	// 싱글톤 가져오기
	static T* getSingleton();
	// 싱글톤 메모리에서 해제하기
	void releaseSingleton();


};
// 싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

template<typename T>
inline T * SingletonBase<T>::getSingleton()
{
	// 싱글톤이 없으면 새로 생성
	if (!singleton)	singleton = new T;

	return singleton;
}

// 싱글톤 메모리에서 해제
template<typename T>
inline void SingletonBase<T>::releaseSingleton()
{
	// 싱글톤을 생성했을 때만 해제
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
