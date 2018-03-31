#pragma once
#include "Entity.h"
#include <vector>

class Projectile : public Entity
{
public:
	float movementSpeed;
	int direction; // 1 - up, 2 - down, 3 - left, 4 - right
	bool removeProjectile;
	Texture ProjectileTexture;

	Projectile();
	void update();
};

