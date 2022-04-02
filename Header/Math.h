#pragma once
#include <iostream>

struct Vector2 
{	
	
	Vector2()
		:x(0.0f),y(0.0f)
	{}
	Vector2(float p_x, float p_y)
		:x(p_x), y(p_y) 
	{}
	float x, y;
	void print()
	{
		std::cout << x << " ," << y << std::endl;
	}
};