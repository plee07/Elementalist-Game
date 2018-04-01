#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Entity
{
public:
	RectangleShape rect;
	Sprite sprite;
	Text text;
	Clock clock;
	Time timer;

	Entity();

};

