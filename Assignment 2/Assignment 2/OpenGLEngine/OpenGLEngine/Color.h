#pragma once
struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float _r = 1, float _g = 1, float _b = 1 , float _a = 1) 
		: r(_r), g(_g), b(_b), a(_a) 
	{

	}

public:
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Blue;
	static const Color Green;
	static const Color Yellow;
	static const Color Purple;
	static const Color Orange;
	static const Color Cyan;
	static const Color Magenta;
	static const Color Beige;
	static const Color Brown;
};
