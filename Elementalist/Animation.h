#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation
{
public:
	Animation();
	~Animation();

private:
	Vector2u imageCount;
	Vector2u currentImage;

};

