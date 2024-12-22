#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <vector>
#include <filesystem>

#include "Layer.hpp"
#include "StringOperations.hpp"

//It cost 32gb of ram to run this code for 12 secounds
Pixel*** PrepareNewMap(vec::IVec2 size){
	if(size.x<=0 || size.y<=0 || size.x>=10000 || size.y>=10000){
		std::cout<<"map size not in bounds"<<std::endl;
		return nullptr;
	}
	std::cout<<"new map initialized"<<std::endl;
	Pixel*** newArr = new Pixel**[size.x];
	for(int i=0; i<size.x; i++){
		newArr[i] = new Pixel*[size.y];
		for(int j=0; j<size.y; j++){
			newArr[i][j] = new Pixel();
		}
	}
	return newArr;
}


InsertPixel::InsertPixel(RGB _color, vec::IVec2 _position){
	color = _color;
	position = _position;
}

void Layer::Dealocate(){
	if(layerMap!=nullptr){
		for(int i=0; i<size.x; i++){
			for(int j=0; j<size.y; j++){
				delete layerMap[i][j];
			}
			delete[] layerMap[i];
		}
		delete[] layerMap;
		layerMap = nullptr;
	}
}
void Layer::Allocate(){
	layerMap = PrepareNewMap(size);
}

Layer::Layer(){
	size = vec::IVec2(0,0);
	startPosition = vec::IVec2(0,0);
	
	layerMap = nullptr;
	buffer = nullptr;
}
Layer::Layer(std::string path){
	Open(path);	
}
Layer::Layer(vec::IVec2 vec){
	Dealocate();
	size = vec;
	startPosition = vec::IVec2(0,0);
	Allocate();
	buffer = nullptr;
}
Layer::~Layer(){
	Dealocate();
}

void Layer::Move(vec::IVec2 vec){
	startPosition = vec;
}
void Layer::Resize(vec::IVec2 vec){
	Pixel*** newArr = PrepareNewMap(vec);
	if(newArr == nullptr){
		std::cout<<"map coundn't be resized";
		return;
	}
	std::cout<<"map resized"<<std::endl;
	for(int i = 0; i< std::min(vec.x, size.x); i++){
		for(int j=0; j<std::min(vec.y, size.y); j++){
			newArr[i][j]->color = layerMap[i][j]->color;
		}
	}
	std::cout<<"copied"<<std::endl;

	Dealocate();
	layerMap = newArr;
	std::cout<<"allocated"<<std::endl;

	size = vec::IVec2(vec);
}
void Layer::Edit(std::vector<InsertPixel> inserted){
	int min_x = std::numeric_limits<int>::max();
	int min_y = std::numeric_limits<int>::max();
	int max_x = std::numeric_limits<int>::min();
	int max_y = std::numeric_limits<int>::min();
	for(int i=0; i<inserted.size(); i++){
		if(inserted[i].position.x<min_x) min_x = inserted[i].position.x;
		if(inserted[i].position.y<min_y) min_y = inserted[i].position.y;
		if(inserted[i].position.x>max_x) max_x = inserted[i].position.x;
		if(inserted[i].position.y>max_y) max_y = inserted[i].position.y;
	}
	std::cout<<min_x<<" "<<min_y<<" ; "<<max_x<<" "<<max_y<<std::endl;
	if(inserted.size()!=0){
		this->Resize(vec::IVec2(max_x-min_x+1, max_y-min_y+1));
		this->startPosition = vec::IVec2(min_x, min_y);
	}
	std::cout<<size.x<<" "<<size.y<<" ; "<<startPosition.x<<" "<<startPosition.y<<std::endl;
	for(int i=0; i<inserted.size(); i++){
		std::cout<<inserted[i].position.x-min_x<<"; "<<inserted[i].position.y-min_y<<std::endl;

		this->layerMap[inserted[i].position.x-min_x][inserted[i].position.y-min_y]->color = inserted[i].color;
	}
	std::cout<<"inserted"<<std::endl;
}
void Layer::Open(std::string path){
	Move(vec::IVec2(0, 0));
	if(path.find(".") == std::string::npos || path.rfind('.') == path.size()-1){
		std::cout<<"no file type"<<std::endl;
		return;
	}
	if(!std::filesystem::exists(path)){
		std::cout<<"file not exist"<<std::endl;
	}
	if(path.substr(path.rfind('.')+1) == "ppm"){
		OpenPpm(path);
	}
}
void Layer::Save(std::string name){
	std::ofstream file(name);
	if(size!=vec::IVec2(0,0) && layerMap!=nullptr){
		file<<"P3\n# created in gimpRipoff made by Bejmach\n"<<size.x<<" "<<size.y<<"\n255\n";
		for(int y=0; y<size.y; y++){
			for(int x=0; x<size.x; x++){
				file<<static_cast<int>(layerMap[x][y]->color.R)<<"\n"<<static_cast<int>(layerMap[x][y]->color.G)<<"\n"<<static_cast<int>(layerMap[x][y]->color.B)<<"\n";
			}
		}
	}
}

Pixel* Layer::GetPixel(vec::IVec2 vec){
	if(vec.x>= size.x || vec.y>=size.y || vec.x<0 || vec.y<0){
		return nullptr;
	}
	return layerMap[vec.x][vec.y];
}
Pixel* Layer::GetBuffer(vec::IVec2 vec){
	if(vec.x>= size.x || vec.y>=size.y || vec.x<0 || vec.y<0){
		return nullptr;
	}
	if(buffer!=nullptr){
		return buffer[vec.x][vec.y];
	}
	return nullptr;
}
vec::IVec2 Layer::GetSize(){
	return size;
}
vec::IVec2 Layer::GetStart(){
	return startPosition;
}

void Layer::SetBuffer(Pixel***_buffer){
	buffer = _buffer;
}


bool Layer::hasBuffer(){
	return (buffer!=nullptr);
}

void Layer::OpenPpm(std::string path){
	std::ifstream file(path, std::ios::binary);
	std::string line;
	int curLine = 2;
	vec::IVec2 maxSize;
	size_t curPixel = 0;
	int maxColor;
	RGB curColor = RGB();
	getline(file, line);
	if(line == "P3"){
		while(getline(file, line)){
			if(line[0] == '#'){
				continue;
			}
			else if(curLine==2){
				std::vector<std::string> splited = SO::Split(line, " ");
				maxSize = vec::IVec2(std::stoi(splited[0]), std::stoi(splited[1]));
				std::cout<<maxSize.x<<" ; "<<maxSize.y<<std::endl;
				Resize(maxSize);
			}
			else if(curLine==3){
				maxColor = std::stoi(line);
			}
			else if(curLine>=4){
				if((curLine-4)%3 == 0){
					curColor.R = std::stoi(line);
				}
				else if((curLine-4)%3 == 1){
					curColor.G = std::stoi(line);
				}
				else if((curLine-4)%3 == 2){
					curColor.B = std::stoi(line);
					int position_y = curPixel/maxSize.x;
					int position_x = curPixel%maxSize.x;
					layerMap[position_x][position_y]->color = curColor;
					curPixel += 1;
					curColor = RGB();
				}
			}	
			curLine+=1;
		}
	}
	else if(line == "P6"){
		size_t curSymbol = 0;
		while(getline(file, line)){
			if(line.empty() || line[0] == '#'){
				continue;
			}
			std::istringstream _stream(line);
			_stream >> maxSize.x >> maxSize.y;
			if(maxSize.x>0 && maxSize.y>0){
				std::cout<<maxSize.x<<" ; "<<maxSize.y<<std::endl;
				break;
			}
		}
		while(getline(file, line)){
			if(line.empty() || line[0] == '#'){
				continue;
			}
			std::istringstream _stream(line);
			_stream >> maxColor;
			if(maxColor>0){
				break;
			}
		}

		//file.ignore(1);

		Resize(maxSize);
	
		std::vector<char> pixelData(maxSize.x * maxSize.y * 3); // 3 bytes per pixel (RGB)
		file.read(pixelData.data(), pixelData.size());
		int curPixel = 0;

		for (int y = 0; y < maxSize.y; ++y) {
			for (int x = 0; x < maxSize.x; ++x) {
				RGB curColor;
				curColor.R = static_cast<unsigned char>(pixelData[curPixel++]);
				curColor.G = static_cast<unsigned char>(pixelData[curPixel++]);
				curColor.B = static_cast<unsigned char>(pixelData[curPixel++]);
				layerMap[x][y]->color = curColor; // Assuming layerMap is indexed as layerMap[x][y]
			}
		}
	}
}

void Layer::AllocateBuffer(){
	buffer = new Pixel**[size.x];
	for(int i=0; i<size.x; i++){
		buffer[i] = new Pixel*[size.y];
		for(int j=0; j<size.y; j++){
			buffer[i][j] = new Pixel(*layerMap[i][j]);
		}
	}
}
void Layer::DeallocateBuffer(){
	if(buffer!=nullptr){
		for(int i=0; i<size.x; i++){
			for(int j=0; j<size.y; j++){
				delete buffer[i][j];
			}
			delete[] buffer[i];
		}
		delete[] buffer;
	}
}

int Layer::GetLayerId(){
	Layer* curLayer = this;
	int layerCounter = 0;
	while(curLayer->previousLayer!=nullptr){
		layerCounter+=1;
		curLayer = curLayer->previousLayer;
	}
	return layerCounter;
}

