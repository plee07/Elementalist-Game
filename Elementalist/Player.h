#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	float movementSpeed;
	int spriteAnimation;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	Texture PlayerTexture;

	Player();
	void update();
	void playerMovement();
};

