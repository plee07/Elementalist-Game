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
	int enemyStatus;
	bool enemyDead;
	Sprite deadSprite;
	SoundBuffer buffer;
	Sound sound;
	Texture EnemyTexture;

	Enemy(String texture, int status, String sound);
	void update();
	void enemyMovement();
	void enemyTerror();
};

