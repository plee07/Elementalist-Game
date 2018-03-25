#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	float movementSpeed;
	int attackDamage; // I don't really need this
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	Texture PushProjectile;

	Projectile();
	void update();
};

