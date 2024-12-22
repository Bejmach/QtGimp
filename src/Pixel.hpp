#ifndef PIXEL_HPP
#define PIXEL_HPP

#include "Color.hpp"
#include <iostream>

class Pixel{
	public:
		RGB color;

		Pixel(double a = 0.0);//black
		Pixel(int g, double a = 1.0);//grayscale
		Pixel(int r, int g, int b, double a = 1.0);//full colours

		void SetHsv(HSV hsv);
		void SetHsv(double h, double s, double v, double a = 1.0);
		HSV GetHsv();
};

#endif
