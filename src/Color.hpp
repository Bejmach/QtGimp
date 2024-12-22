#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

struct HSV{
	double H;
	double S;
	double V;
	unsigned char A;

	HSV(double a = 1.0);
	HSV(double h, double s, double v, double a = 1.0);

	friend std::ostream& operator<<(std::ostream& os, const HSV& hsv);
};

struct RGB{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;

	RGB(double a = 1.0);
	RGB(int g, double a = 1.0);
	RGB(int r, int g, int b, double a = 1.0);

	RGB operator+(RGB rgb);
	RGB operator-(RGB rgb);
	RGB operator*(double S);
	RGB operator/(double S);

	friend std::ostream& operator<<(std::ostream& os, const RGB& rgb);
};

struct HSI{
	double H;
	double S;
	double I;
	unsigned char A;

	HSI(double a = 1.0);
	HSI(double h, double s, double I, double a = 1.0);

	friend std::ostream& operator<<(std::ostream& os, const HSI& hsi);
};


struct cc{
	static HSV Rgb2Hsv(RGB rgb);
	static RGB Hsv2Rgb(HSV hsv);
	static HSI Rgb2Hsi(RGB rgb);
	static RGB Hsi2Rgb(HSI hsi);

	static RGB Difference(RGB rgb1, RGB rgb2);
};

#endif
