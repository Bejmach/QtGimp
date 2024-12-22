#ifndef LAYEREDITOR_HPP
#define LAYEREDITOR_HPP

#include "Image.hpp"
#include "Layer.hpp"

namespace LE{
	enum class Operations {Undefined, Negativ, Saturation, Contrast, Brightness, Sobel, SobelOut, Lagrange, Blur, GaussianBlur, DOG, PseudoFresnel, Sharpening, Noise, NoiseG, NoiseGMult};

	void Negativ(Image* img);
	void Saturation(Image* img, int factor = 0);
	void Contrast(Image* img, int factor = 0);
	void Brightness(Image* img, double factor = 0.0);

	void NoiseG(Image* img, double factor = 0.5);
	void NoiseGMult(Image* img, double factor = 0.5);
	void Noise(Image* img, double factor = 0.5);

	void Sobel(Image* img, double factor = 1.0);
	void SobelOutline(Image* img, double factor = 1.0);
	void Previtt(Image* img);
	void LagrangeCC(Image* img, std::vector<vec::IVec2> pointsR, std::vector<vec::IVec2> pointsG, std::vector<vec::IVec2> pointsB);
	void LagrangeCCNoHash(Image* img, std::vector<vec::IVec2> pointsR, std::vector<vec::IVec2> pointsG, std::vector<vec::IVec2> pointsB);

	void Blur(Image* img, int kernelSize = 2);

	RGB GaussianPixel(const std::vector<std::vector<double>>& kernel, vec::IVec2 position, Layer* layer);
	void GaussianBlur(Image *img, int kernelSize = 2.0, double sigma = 1.0);
	void DOG(Image *img, int kernelSize = 2, double sigma1 = 1.0, double sigma2 = 2.0);

	void PseudoFresnel(Image *img, int kernelSize = 10, double sigma = 10.0, RGB color = RGB(255,255,255));

	void Sharpening(Image* img);

	void Apply(Image* img);
	void Revert(Image* img);
}

#endif
