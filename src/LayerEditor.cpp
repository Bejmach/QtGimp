#include "LayerEditor.hpp"
#include "Graphs.hpp"

#include <algorithm>
#include <unordered_map>
#include <math.h>

int randRange(int min, int max){
	return min+(std::rand() % (max-min+1));
}

void LE::Negativ(Image* img){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->AllocateBuffer();
	}
	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x, y))->color;;
			color.R = 255-color.R;
			color.G = 255-color.G;
			color.B = 255-color.B;
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
            bufferPixel->color = color;
		}
	}
}

void LE::Saturation(Image* img, int factor){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}
	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			HSV color = cc::Rgb2Hsv(layer->GetPixel(vec::IVec2(x, y))->color);
            color.S = std::clamp(color.S + color.S * factor, 0.0, 1.0);
			layer->GetBuffer(vec::IVec2(x,y))->SetHsv(color);
		}
	}
}

//Some people think they can outsmart me...
//Maybe...[snif]Maybe...
//I've yet to meet one that can outsmart the bullet
void LE::Contrast(Image* img, int factor){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	std::unordered_map<unsigned char, int> hashed;

	std::vector<vec::IVec2>points;
	
	if(factor<0){
		points.push_back(vec::IVec2(0, -factor));
		points.push_back(vec::IVec2(255, 255+factor));
	}
	else{
		points.push_back(vec::IVec2(factor, 0));
		points.push_back(vec::IVec2(255-factor, 255));
	}

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x, y))->color;

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
			
			if(hashed.find(color.R)!=hashed.end()){
				color.R = hashed[color.R];
			}
			else{
				hashed[color.R] = std::clamp(Graphs::Lagrange(points, {color.R})[0], 0, 255);
				color.R = hashed[color.R];
			}
			if(hashed.find(color.G)!=hashed.end()){
				color.G = hashed[color.G];
			}
			else{
				hashed[color.G] = std::clamp(Graphs::Lagrange(points, {color.G})[0], 0, 255);
				color.G = hashed[color.G];
			}
			if(hashed.find(color.B)!=hashed.end()){
				color.B = hashed[color.B];
			}
			else{
				hashed[color.B] = std::clamp(Graphs::Lagrange(points, {color.B})[0], 0, 255);
				color.B = hashed[color.B];
			}

			bufferPixel->color = color;
		}
	}

}


void LE::Brightness(Image* img, double factor){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}
	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			HSV color = cc::Rgb2Hsv(layer->GetPixel(vec::IVec2(x, y))->color);
			if(factor>0){
				color.V = color.V + ((1.0-color.V) * factor);
			}
			else{
				color.V = color.V + (color.V * factor);

			}
            layer->GetBuffer(vec::IVec2(x,y))->SetHsv(color);
		}
	}
}

void LE::NoiseG(Image *img, double factor){
	srand(time(NULL));
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x,y))->color;
			int random = randRange(0, 255);
			color = RGB(color.R*(1-factor) + random*factor, color.G*(1-factor) + random*factor, color.B*(1-factor) + random*factor);

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
            bufferPixel->color = color;
		}
	}
}
void LE::NoiseGMult(Image *img, double factor){
	srand(time(NULL));
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x,y))->color;
			double random = ((double)randRange(0, 100)/100.0)*factor;
			color = RGB((double)color.R*random, (double)color.G*random, (double)color.B*random);

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
            bufferPixel->color = color;
		}
	}
}
void LE::Noise(Image *img, double factor){
	srand(time(NULL));
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x,y))->color;
			RGB random = (RGB(randRange(0, 255), randRange(0, 255), randRange(0, 255)));
			color = RGB(color.R*(1-factor) + random.R*factor, color.G*(1-factor) + random.G*factor, color.B*(1-factor) + random.B*factor);

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
            bufferPixel->color = color;
		}
	}
}

//function made before all the other convolution processes, so it looks horrible
void LE::Sobel(Image *img, double factor){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}
	std::vector<std::vector<int>> kernelX = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	std::vector<std::vector<int>> kernelY = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y = 0; y<layer->GetSize().y; y++){
			std::vector<int> sobel;
			int grayX = 0;
			int grayY = 0;
			for(int Kx=-1; Kx<=1; Kx++){
				for(int Ky=-1; Ky<=1; Ky++){
					if(layer->GetPixel(vec::IVec2(x+Kx, y+Ky)) == nullptr) continue;
					RGB color = layer->GetPixel(vec::IVec2(x+Kx, y+Ky))->color;
					
					int grayscale = (color.R+color.G+color.B)/3;

					grayX += grayscale*kernelX[Ky+1][Kx+1];
					grayY += grayscale*kernelY[Ky+1][Kx+1];

				}
			}
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
            bufferPixel->color = RGB((int)((double)(grayX+grayY) * factor));
		}
	}
}
void LE::SobelOutline(Image *img, double factor){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}
	std::vector<std::vector<int>> kernelX = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
	std::vector<std::vector<int>> kernelY = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y = 0; y<layer->GetSize().y; y++){
			std::vector<int> sobel;
			int grayX = 0;
			int grayY = 0;
			for(int Kx=-1; Kx<=1; Kx++){
				for(int Ky=-1; Ky<=1; Ky++){
					if(layer->GetPixel(vec::IVec2(x+Kx, y+Ky)) == nullptr) continue;
					RGB color = layer->GetPixel(vec::IVec2(x+Kx, y+Ky))->color;
					
					int grayscale = (color.R+color.G+color.B)/3;

					grayX += grayscale*kernelX[Ky+1][Kx+1];
					grayY += grayscale*kernelY[Ky+1][Kx+1];

				}
			}
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));

			RGB sobelColor = RGB((int)((double)(grayX+grayY) * factor));
			RGB baseColor = layer->GetPixel(vec::IVec2(x, y))->color;
            bufferPixel->color = baseColor - sobelColor;
		}
	}
}

void LE::Previtt(Image *img){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	std::vector<std::vector<int>> kernelX = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
	std::vector<std::vector<int>> kernelY = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			int grayX = 0;
			int grayY = 0;
			for(int Kx=-1; Kx<=1; Kx++){
				for(int Ky = -1; Ky<=1; Ky++){
					if(layer->GetPixel(vec::IVec2(x+Kx, y+Ky)) == nullptr) continue;
					RGB color = layer->GetPixel(vec::IVec2(x+Kx, y+Ky))->color;
					
					int grayscale = (color.R+color.G+color.B)/3;

					grayX += grayscale*kernelX[Ky+1][Kx+1];
					grayY += grayscale*kernelY[Ky+1][Kx+1];

				}
			}
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
			bufferPixel->color = RGB(grayY+grayX);
		}
	}
}

void LE::LagrangeCC(Image *img, std::vector<vec::IVec2> pointsR, std::vector<vec::IVec2> pointsG, std::vector<vec::IVec2> pointsB){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	std::unordered_map<unsigned char, int> hashedR;
	std::unordered_map<unsigned char, int> hashedG;
	std::unordered_map<unsigned char, int> hashedB;

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x, y))->color;

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
			
			if(hashedR.find(color.R)!=hashedR.end()){
				color.R = hashedR[color.R];
			}
			else{
				hashedR[color.R] = std::clamp(Graphs::Lagrange(pointsR, {color.R})[0], 0, 255);
				color.R = hashedR[color.R];
			}
			if(hashedG.find(color.G)!=hashedG.end()){
				color.G = hashedG[color.G];
			}
			else{
				hashedG[color.G] = std::clamp(Graphs::Lagrange(pointsG, {color.G})[0], 0, 255);
				color.G = hashedG[color.G];
			}
			if(hashedB.find(color.B)!=hashedB.end()){
				color.B = hashedB[color.B];
			}
			else{
				hashedB[color.B] = std::clamp(Graphs::Lagrange(pointsB, {color.B})[0], 0, 255);
				color.B = hashedB[color.B];
			}

			bufferPixel->color = color;
		}
	}
}
void LE::LagrangeCCNoHash(Image *img, std::vector<vec::IVec2> pointsR, std::vector<vec::IVec2> pointsG, std::vector<vec::IVec2> pointsB){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x, y))->color;

			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
			
			color.R = std::clamp(Graphs::Lagrange(pointsR, {color.R})[0], 0, 255);
			color.G = std::clamp(Graphs::Lagrange(pointsG, {color.G})[0], 0, 255);
			color.B = std::clamp(Graphs::Lagrange(pointsB, {color.B})[0], 0, 255);

			bufferPixel->color = color;
		}
	}
}

void LE::Blur(Image *img, int kernelSize){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	int wholeKernelSize = pow(kernelSize*2+1, 2);

	for(int x=0; x<img->GetLayer(img->focusedLayerId)->GetSize().x; x++){
		for(int y=0; y<img->GetLayer(img->focusedLayerId)->GetSize().y; y++){
			int sumR = 0;
			int sumG = 0;
			int sumB = 0;
			int skipped = 0;
			for(int Kx = -kernelSize; Kx<=kernelSize; Kx++){
				for(int Ky = -kernelSize; Ky<=kernelSize; Ky++){
					if(img->GetLayer(img->focusedLayerId)->GetPixel(vec::IVec2(x+Kx, y+Ky)) == nullptr){
						skipped+=1;
						continue;
					}	

					RGB color = img->GetLayer(img->focusedLayerId)->GetPixel(vec::IVec2(x+Kx, y+Ky))->color;
					
					sumR += color.R;
					sumG += color.G;
					sumB += color.B;
				}
			}
			Pixel* bufferPixel = img->GetLayer(img->focusedLayerId)->GetBuffer(vec::IVec2(x, y));

			if(bufferPixel!=nullptr){
				bufferPixel->color = RGB(sumR/(wholeKernelSize-skipped), sumG/(wholeKernelSize-skipped), sumB/(wholeKernelSize-skipped));
			}
		}
	}
}

RGB LE::GaussianPixel(const std::vector<std::vector<double>>& kernel, vec::IVec2 position, Layer* layer){
	int kernelSize = (kernel.size()-1)/2;

	double R = 0.0;
	double G = 0.0;
	double B = 0.0;
	for(int Kx = -kernelSize; Kx<=kernelSize; Kx++){
		for(int Ky = -kernelSize; Ky<=kernelSize; Ky++){
			Pixel* pixel = layer->GetPixel(vec::IVec2(position.x+Kx, position.y+Ky));
			if(pixel == nullptr) continue;

			R += (double)pixel->color.R * kernel[Ky+kernelSize][Kx+kernelSize];
			G += (double)pixel->color.G * kernel[Ky+kernelSize][Kx+kernelSize];
			B += (double)pixel->color.B * kernel[Ky+kernelSize][Kx+kernelSize];
		}
	}
	return RGB(R, G, B);
}

void LE::GaussianBlur(Image *img, int kernelSize, double sigma){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	double sum = 0.0;

	std::vector<std::vector<double>> gaussianKernel(kernelSize*2+1, std::vector<double>(kernelSize*2+1, 0.0));
	
	for(int Kx=-kernelSize; Kx<=kernelSize; Kx++){
		for(int Ky=-kernelSize; Ky<=kernelSize; Ky++){
			gaussianKernel[Kx+kernelSize][Ky+kernelSize] = exp(-(Kx*Kx+Ky*Ky)/(2*sigma*sigma))/(M_PI * 2*sigma*sigma);
			sum+=gaussianKernel[Kx+kernelSize][Ky+kernelSize];
		}
	}
	for(int Kx=0; Kx<kernelSize*2+1; Kx++){
		for(int Ky=0; Ky<kernelSize*2+1; Ky++){
			gaussianKernel[Kx][Ky]/=sum;
		}
	}
	for(int x = 0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));

			bufferPixel->color = GaussianPixel(gaussianKernel, vec::IVec2(x, y), layer);
		}
	}
}

//what the dog doin
void LE::DOG(Image *img, int kernelSize, double sigma1, double sigma2){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	double sum1 = 0.0;
	double sum2 = 0.0;

	std::vector<std::vector<double>> gaussianKernel1(kernelSize*2+1);
	std::vector<std::vector<double>> gaussianKernel2(kernelSize*2+1);
	for(int i=0; i<gaussianKernel1.size(); i++){
		gaussianKernel1[i] = std::vector<double>(kernelSize*2+1);

		gaussianKernel2[i] = std::vector<double>(kernelSize*2+1);
	}
	for(int Kx=-kernelSize; Kx<kernelSize; Kx++){
		for(int Ky=-kernelSize; Ky<kernelSize; Ky++){

			gaussianKernel1[Kx+kernelSize][Ky+kernelSize] = exp(-(Kx*Kx+Ky*Ky)/(2*sigma1*sigma1))/(M_PI * 2*sigma1*sigma1);
			sum1+=gaussianKernel1[Kx+kernelSize][Ky+kernelSize];
			
			gaussianKernel2[Kx+kernelSize][Ky+kernelSize] = exp(-(Kx*Kx+Ky*Ky)/(2*sigma2*sigma2))/(M_PI * 2*sigma2*sigma2);
			sum2+=gaussianKernel2[Kx+kernelSize][Ky+kernelSize];
		}
	}
	for(int Kx=0; Kx<kernelSize*2+1; Kx++){
		for(int Ky=0; Ky<kernelSize*2+1; Ky++){
			gaussianKernel1[Kx][Ky]/=sum1;
			
			gaussianKernel2[Kx][Ky]/=sum2;
		}
	}

	for(int x = 0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color1 = GaussianPixel(gaussianKernel1, vec::IVec2(x, y), layer);
			RGB color2 = GaussianPixel(gaussianKernel2, vec::IVec2(x, y), layer);
		
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));

			bufferPixel->color = RGB(((color1.R + color1.G + color1.B) - (color2.R + color2.G + color2.B))/3);
		}
	}

}

void LE::PseudoFresnel(Image *img, int kernelSize, double sigma, RGB colorOverlay){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	double sum = 0.0;

	std::vector<std::vector<double>> gaussianKernel(kernelSize*2+1, std::vector<double>(kernelSize*2+1, 0.0));
	
	for(int Kx=-kernelSize; Kx<=kernelSize; Kx++){
		for(int Ky=-kernelSize; Ky<=kernelSize; Ky++){
			gaussianKernel[Kx+kernelSize][Ky+kernelSize] = exp(-(Kx*Kx+Ky*Ky)/(2*sigma*sigma))/(M_PI * 2*sigma*sigma);
			sum+=gaussianKernel[Kx+kernelSize][Ky+kernelSize];
		}
	}
	for(int Kx=0; Kx<kernelSize*2+1; Kx++){
		for(int Ky=0; Ky<kernelSize*2+1; Ky++){
			gaussianKernel[Kx][Ky]/=sum;
		}
	}
	for(int x = 0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			RGB color = layer->GetPixel(vec::IVec2(x, y))->color;
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));
				
			RGB dif = cc::Difference(color, GaussianPixel(gaussianKernel, vec::IVec2(x, y), layer));

			double value = ((double)dif.R + (double)dif.G + (double)dif.B)/765;

			bufferPixel->color = color + (colorOverlay*value);
		}
	}
}

void LE::Sharpening(Image* img){
	Layer* layer = img->GetLayer(img->focusedLayerId);
	if(!layer->hasBuffer()){
		layer->DeallocateBuffer();
		layer->AllocateBuffer();
	}

	std::vector<std::vector<int>> kernel = {{0,-1,0}, {-1, 5, -1}, {0, -1, 0}};
	for(int x=0; x<layer->GetSize().x; x++){
		for(int y=0; y<layer->GetSize().y; y++){
			int sumR = 0;
			int sumG = 0;
			int sumB = 0;
			for(int Kx = -1; Kx <= 1; Kx++){
				for(int Ky = -1; Ky <=1; Ky++){
					if(layer->GetPixel(vec::IVec2(x+Kx, y+Ky)) == nullptr){
						continue;
					}
					RGB color = layer->GetPixel(vec::IVec2(x+Kx, y+Ky))->color;
					sumR += color.R * kernel[Ky+1][Kx+1];
					sumG += color.G * kernel[Ky+1][Kx+1];
					sumB += color.B * kernel[Ky+1][Kx+1];
				}
			}
			Pixel* bufferPixel = layer->GetBuffer(vec::IVec2(x, y));

			bufferPixel->color = RGB(sumR, sumG, sumB);
		}
	}
}

void LE::Apply(Image* img){
	img->ApplyLayerBuffer();
}
void LE::Revert(Image* img){
	img->RevertLayerBuffer();
}
