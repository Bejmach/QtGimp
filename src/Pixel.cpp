#include <iostream>

#include "Pixel.hpp"

Pixel::Pixel(double a){
	color = RGB(a);
}
Pixel::Pixel(int g, double a){
	color = RGB(g, a);
}
Pixel::Pixel(int r, int g, int b, double a){
	color = RGB(r, g, b, a);
}

void Pixel::SetHsv(HSV hsv){
	color = RGB(cc::Hsv2Rgb(hsv));
}
void Pixel::SetHsv(double h, double s, double v, double a){
	color = RGB(cc::Hsv2Rgb(HSV(h, s, v, a)));
}

HSV Pixel::GetHsv(){
	return cc::Rgb2Hsv(color);
}
