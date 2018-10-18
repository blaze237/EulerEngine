#pragma once
#include "MathTools.h"

class Colour
{
public:
	Colour(int r, int g, int b, int a = 255)
	{
		this->r = MathTools::clamp<int>(r, 0, 255);
		this->g = MathTools::clamp<int>(g, 0, 255);
		this->b = MathTools::clamp<int>(b, 0, 255);
		this->a = MathTools::clamp<int>(a, 0, 255);
	}
	~Colour()
	{
	}

	int get

	
private:
	int r, g, b, a;
};