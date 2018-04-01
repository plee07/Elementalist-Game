#pragma once
#include "Entity.h"
#include <ctime>

class Player : public Entity
{
public:
	float movementSpeed;
	int spriteAnimation;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	int playerStatus; // 0 - neutral, 1 - earth, 2 - fire, 3 - water, 4 - thunder
	bool playerPause;
	bool playerDead;
	Texture PlayerTexture;

	Player();
	void update();
	void playerMovement();
	void playerTerror();
	void playerDeath();
};

