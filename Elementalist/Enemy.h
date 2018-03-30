#pragma once
#include "Entity.h"
#include <ctime>

class Enemy : public Entity
{
public:
	float movementSpeed;
	int spriteAnimation;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	int movementTime;
	Texture EnemyTexture;

	Enemy(String texture);
	void update();
	void enemyMovement();
};

