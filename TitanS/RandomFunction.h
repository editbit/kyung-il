#pragma once
#include "SingletonBase.h"
#include <ctime>

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		//srand((unsigned int)time(NULL));
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init() { return S_OK; }
	void release() {}

	// GetInt
	inline int getInt(int num) { return rand() % num; }
	// GetFromIntTo
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }
};

