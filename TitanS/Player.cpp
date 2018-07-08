#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	memset(playerImage, 0, sizeof(Image*)*MAX_STATE);
	playerImage[WALK] = IMAGEMANAGER->addFrameImage("idle", "resource\\playerMove_192x256.bmp", 192, 256, 6, 8);
	playerImage[IDLE] = playerImage[WALK];
	playerImage[RUN] = playerImage[WALK];
	playerImage[ROLL] = IMAGEMANAGER->addFrameImage("roll", "resource\\roll_192x256_6x8.bmp", 192, 256, 6, 8);

	dirX = dirY = shootingPower = aniCount = aniIndex = rollCount = 0;
	angle = -PI / 2;
	
	oldX = x = 1585;
	oldY = y = 7680;
	oldZ = z = 0;
	speed = WALK_SPEED;
	state = IDLE;
	dir = DOWN;
	xAxis = NONE;
	yAxis = DOWN;

	
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	if (state != ROLL)
	{
		inputProcess();
		if (state == RUN)
		{
			x += 0;
		}
		changeDir();
	}
	else
	{
		rollCount = (rollCount + 1) % ROLL_TIME;
		if (rollCount == 0)
		{
			changeState(IDLE);
		}
	}


	if (state == WALK || state == RUN || state == ROLL)
	{
		oldX = x;
		oldY = y;
		x += cos(angle)*speed;
		y += -sin(angle)*speed;
	}
	setCollisionBox();
}

void Player::render()
{
	switch(state)
	{
	case IDLE:
		playerImage[state]->setFrameX(0);
		break;
	case WALK:
	case ROLL:
	case RUN:
		aniCount = (aniCount + 1) % 10;
		if (state == ROLL)
		{
			aniCount = aniCount % 5;
		}
		if (aniCount == 1)
		{
			aniIndex = (aniIndex + 1);
			if (aniIndex > playerImage[state]->getMaxFrameX())
			{
				aniIndex = 0;
			}
		}
		playerImage[state]->setFrameX(aniIndex);
		break;
	}
	playerImage[state]->setFrameY(dir);
	playerImage[state]->frameRender(getMemDC(), x - playerImage[state]->getFrameWidth()/2 - camera.x,
		y - playerImage[state]->getFrameHeight()/2 - camera.y);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		

		Rectangle(getMemDC(), collisionBox.left - camera.x, collisionBox.top - camera.y,
			collisionBox.right - camera.x, collisionBox.bottom - camera.y);
	}

	char str[128];
	sprintf_s(str, "%.3f %d", speed, state);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}


void Player::changeState(int _state)
{
	switch (_state)
	{
	case IDLE:
	case ATTACK:
		speed = 0;
		break;
	case WALK:
		speed = WALK_SPEED;
		break;
	case RUN:
		speed = RUN_SPEED;
		break;
	case ROLL:
		speed = ROLL_SPEED;
		break;
	}
	state = _state;
}


bool Player::changeDir()
{
	if (xAxis == NONE && yAxis == NONE) return false;

	switch (xAxis)
	{
	case RIGHT:
		dir = RIGHT;
		angle = 0;
		if (yAxis == UP)
		{
			dir = RIGHT_UP;
			angle = PI / 4;
		}
		else if (yAxis == DOWN)
		{
			dir = RIGHT_DOWN;
			angle = - PI / 4 ;
		}
		break;
	case LEFT:
		dir = LEFT;
		angle = PI;
		if (yAxis == UP)
		{
			dir = LEFT_UP;
			angle = 3 * PI / 4;
		}
		else if (yAxis == DOWN)
		{
			dir = LEFT_DOWN;
			angle = -3 * PI / 4;
		}
		break;
	case NONE:
		if (yAxis == UP)
		{
			dir = UP;
			angle = PI / 2;
		}
		else if (yAxis == DOWN)
		{
			dir = DOWN;
			angle = - PI / 2;
		}
		break;
	}

	return true;
}


void Player::inputProcess()
{
	int oldState = state;
	bool isKeyDown = false;
	speed = 0;
	
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		state = ROLL;
		speed = ROLL_SPEED;
		rollCount = 0;
		isKeyDown = true;
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			//	state = ATTACK;
			isKeyDown = true;
			return;
		}
		else if (KEYMANAGER->isOnceKeyUp('C'))
		{
			isKeyDown = true;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			isKeyDown = true;
			xAxis = LEFT;
			changeState(WALK);

			if (KEYMANAGER->isStayKeyDown('X'))
			{
				changeState(RUN);
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			isKeyDown = true;
			xAxis = RIGHT;
			changeState(WALK);

			if (KEYMANAGER->isStayKeyDown('X'))
			{
				changeState(RUN);
			}
		}
		else {
			xAxis = NONE;
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			isKeyDown = true;
			yAxis = UP;
			changeState(WALK);

			if (KEYMANAGER->isStayKeyDown('X'))
			{
				changeState(RUN);
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			isKeyDown = true;
			yAxis = DOWN;
			changeState(WALK);

			if (KEYMANAGER->isStayKeyDown('X'))
			{
				changeState(RUN);
			}
		}
		else {
			yAxis = NONE;
		}
	}
	if (oldState != state)
	{
		aniIndex = 0;
		aniCount = 0;
	}

	if (!isKeyDown)
	{
		changeState(IDLE);
	}
}

void Player::setCollisionBox()
{
	collisionBox = RectMakeCenter(x, y, 10, 10);
}

void Player::collideWall(RECT wall)
{
	if (oldX < wall.left)
	{
		x = wall.left - (collisionBox.right - collisionBox.left)/2;
	}
	else if (oldX > wall.right)
	{
		x = wall.right + (collisionBox.right - collisionBox.left)/2;
	}
	if (oldY < wall.top)
	{
		y = wall.top - (collisionBox.bottom - collisionBox.top)/2;
	}
	else if(oldY > wall.bottom)
	{
		y = wall.bottom + (collisionBox.bottom - collisionBox.top)/2;
	}
}
