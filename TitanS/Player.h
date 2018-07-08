#pragma once
#include "GameNode.h"

#define PI 3.141592f

#define MAX_POWER 10.0f

#define WALK_SPEED 3.0f
#define RUN_SPEED 6.0f
#define ROLL_TIME 30
#define ROLL_SPEED 10.0f
#define MAX_STATE 6
#define MAX_STAGE 2

enum DIRECTION
{
	RIGHT, UP, LEFT, DOWN, RIGHT_DOWN, LEFT_DOWN, LEFT_UP, RIGHT_UP, NONE
};

enum STATE
{
	IDLE, WALK, RUN, ROLL, ATTACK, DEAD
};


class Player : public GameNode
{
	float x, y, z;
	float oldX, oldY, oldZ;
	float dirX, dirY;
	float speed;
	float angle;
	float shootingPower;
	int state;
	int xAxis, yAxis;
	int dir;

	int rollCount;
	int aniCount;
	int aniIndex;

	RECT collisionBox;
	
	POINT camera;
	
	Image * playerImage[MAX_STATE] = {0};


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Player() {}
	~Player() {}

	void changeState(int _state);
	bool changeDir();
	void inputProcess();
	void setCollisionBox();
	void collideWall(RECT wall);

	RECT getCollisionBox() { return collisionBox; }
	POINT getCamera() { return camera; }
	int getDir() { return dir; }
	int getState() { return state; }
	float getShootingPower() { return shootingPower; }
	float getX() { return x; };
	float getY() { return y; };
	float getZ() { return z; };
	float getSpeed() { return speed; }
	float getAngle() { return angle; }

	void setCamera(POINT _camera) { camera = _camera; }
	void setShootingPower(float _power) { shootingPower = _power; }
	void setDir(int _dir) { dir = _dir; }
	void setState(int _state) { state = _state; }
	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
	void setZ(float _z) { z = _z; }
	void setSpeed(float _speed) { speed = _speed; }
	void setAngle(float _angle) { angle = _angle; }

};

