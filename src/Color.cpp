#include "Color.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>

HSV::HSV(double a){
	H = 0;
	S = 0;
	V = 0;
	A = a;
}
HSV::HSV(double h, double s, double v, double a){
	H= fmod(h, 360.0);
	S= std::clamp(s, 0.0, 1.0);
	V= std::clamp(v, 0.0, 1.0);
	A = std::clamp(a, 0.0, 1.0)*255.0;
}

std::ostream& operator<<(std::ostream& os, const HSV& hsv){
	os<<"{"<<hsv.H<<", "<<hsv.S<<", "<<hsv.V<<"}";
	return os;
}

HSI::HSI(double a){
	H = 0;
	S = 0;
	I = 0;
	A = a;
}
HSI::HSI(double h, double s, double i, double a){
	H= fmod(h, 360.0);
	S= std::clamp(s, 0.0, 1.0);
	I= std::clamp(i, 0.0, 1.0);
	A = std::clamp(a, 0.0, 1.0)*255.0;
}

std::ostream& operator<<(std::ostream& os, const HSI& hsi){
	os<<"{"<<hsi.H<<", "<<hsi.S<<", "<<hsi.I<<"}";
	return os;
}

RGB::RGB(double a){
	R=0;
	G=0;
	B=0;
	A = a;
}
RGB::RGB(int g, double a){
	int trueG = std::clamp(g, 0, 255);
	R = trueG;
	G = trueG;
	B = trueG;
	A = std::clamp(a, 0.0, 1.0)*255.0;
}
RGB::RGB(int r, int g, int b, double a){
	R = std::clamp(r, 0, 255);
	G = std::clamp(g, 0, 255);
	B = std::clamp(b, 0, 255);
	A = std::clamp(a, 0.0, 1.0)*255.0;
}

RGB RGB::operator+(RGB rgb){
	return RGB(R+rgb.R, G+rgb.G, B+rgb.B);
}
RGB RGB::operator-(RGB rgb){
	return RGB(R-rgb.R, G-rgb.G, B-rgb.B);
}
RGB RGB::operator*(double S){
	return RGB((double)R*S, (double)G*S, (double)B*S);
}
RGB RGB::operator/(double S){
	return RGB((double)R/S, (double)G/S, (double)B/S);
}

std::ostream& operator<<(std::ostream& os, const RGB& rgb){
	os<<"{"<<static_cast<int>(rgb.R)<<", "<<static_cast<int>(rgb.G)<<", "<<static_cast<int>(rgb.B)<<"}";
	return os;
}

RGB cc::Hsv2Rgb(HSV hsv){
	while(hsv.H<0){
		hsv.H+=360.0;
	}
	hsv.H = fmod(hsv.H, 360);
	double C = hsv.V*hsv.S;
	double X = C*(1.0-abs(fmod(hsv.H/60.0, 2)-1));
	double m = hsv.V-C;

	double Rt=0, Gt=0, Bt=0;
	if(hsv.H>=0 && hsv.H<60){
		Rt = C;
		Gt = X;
		Bt = 0;
	}
	else if(hsv.H>=60 && hsv.H<120){
		Rt = X;
		Gt = C;
		Bt = 0;
	}
	else if(hsv.H>=120 && hsv.H<180){
		Rt = 0;
		Gt = C;
		Bt = X;
	}
	else if(hsv.H>=180 && hsv.H<240){
		Rt = 0;
		Gt = X;
		Bt = C;
	}
	else if(hsv.H>=240 && hsv.H<300){
		Rt = X;
		Gt = 0;
		Bt = C;
	}
	else if(hsv.H>=300 && hsv.H<360){
		Rt = C;
		Gt = 0;
		Bt = X;
	}
    return RGB((int)((Rt + m) * 255), (int)((Gt + m) * 255), (int)((Bt + m) * 255), (double)hsv.A/255.0);
}
HSV cc::Rgb2Hsv(RGB rgb){
	double Rt = (double)rgb.R / 255.0;
	double Gt = (double)rgb.G / 255.0;
	double Bt = (double)rgb.B / 255.0;

	double Cmax = std::max(Rt, std::max(Gt, Bt));
    double Cmin = std::min(Rt, std::min(Gt, Bt));

	double delta = Cmax - Cmin;	

	double H = 0;
	if(delta == 0){
		H = 0;
	}
	else if(Cmax == Rt){
        H = 60.0*(fmod((Gt-Bt)/delta, 6.0));
	}
	else if(Cmax == Gt){
		H = 60.0*((Bt-Rt)/delta + 2);
	}
	else if(Cmax == Bt){
		H = 60.0*((Rt-Gt)/delta + 4);
	}
	else{
		return HSV();
	}

	while(H<0){
		H+=360.0;
	}

	double S;
	if(Cmax == 0){
		S = 0;
	}
	else{
		S = delta/Cmax;
	}

	double V = Cmax;

	return HSV(H, S, V, (double)rgb.A/255.0);
}

HSI cc::Rgb2Hsi(RGB rgb){
	double Rt = (double)rgb.R / 255.0;
	double Gt = (double)rgb.G / 255.0;
	double Bt = (double)rgb.B / 255.0;

	double Cmax = std::max(Rt, std::max(Gt, Bt));
    double Cmin = std::min(Rt, std::min(Gt, Bt));

	double delta = Cmax - Cmin;	

	double H = 0;
	if(delta == 0){
		H = 0;
	}
	else if(Cmax == Rt){
        H = 60.0*(fmod((Gt-Bt)/delta, 6.0));
	}
	else if(Cmax == Gt){
		H = 60.0*((Bt-Rt)/delta + 2);
	}
	else if(Cmax == Bt){
		H = 60.0*((Rt-Gt)/delta + 4);
	}
	else{
		return HSI();
	}

	while(H<0){
		H+=360.0;
	}
	double I = (Rt+Gt+Bt)/3;

	double S;
	if(I!=0){
		S = 1 - ((std::min(std::min(Rt, Gt), Bt))/I);
	}
	else{
		S=0;
	}
	std::cout<<H<<"; "<<S<<"; "<<I<<std::endl;
	return HSI(H, S, I, (double)rgb.A/255.0);
}

RGB cc::Hsi2Rgb(HSI hsi){
	double I = hsi.I;
	double S = hsi.S;
	double H = hsi.H;
	if(hsi.H == 0){
		return RGB(255.0 * I + 2*I*S, 255.0 * I-I*S, 255.0 * I-I*S, (double)hsi.A/255.0);
	}
	else if(H>0 && H<120){
		return RGB(255.0 * I+I*S*cos((M_PI/180.0)*(H))/cos((M_PI/180.0)*(60.0-H)), 255.0 * I+I*S*(1.0-cos((M_PI/180.0)*(H))/cos((M_PI/180.0)*(60.0-H))), 255.0 * I-I*S, (double)hsi.A/255.0);
	}
	else if(H == 120){
		return RGB(255.0 * I-I*S, 255.0 * I+2*I*S, 255.0 * I-I*S, (double)hsi.A/255.0);
	}
	else if(H>120 && H<240){
		return RGB(255.0 * I-I*S, 255.0 * I+I*S*cos((M_PI/180.0)*(H-120.0))/cos((M_PI/180.0)*(180.0-H)), 255.0 * I+I*S*(1.0-cos((M_PI/180.0)*(H-120.0))/cos((M_PI/180.0)*(180.0-H))), (double)hsi.A/255.0);
	}
	else if(H == 240){
		return RGB(255.0 * I-I*S, 255.0 * I-I*S, 255.0 * I+2*I*S, (double)hsi.A/255.0);
	}
	else if(H>240 && H<360){
		return RGB(255.0 * I+I*S*(1.0-cos((M_PI/180.0)*(H-240.0))/cos((M_PI/180.0)*(300.0-H))), 255.0 * I-I*S, 255.0 * I+I*S*cos((M_PI/180.0)*(H-240.0))/cos((M_PI/180.0)*(300.0-H)), (double)hsi.A/255.0);
	}
	return RGB((double)hsi.A/255.0);
}

RGB cc::Difference(RGB rgb1, RGB rgb2){
	return RGB(abs(rgb1.R-rgb2.R), abs(rgb1.G - rgb2.G), abs(rgb1.B - rgb2.B));
}
