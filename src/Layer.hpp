#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Vector.hpp"
#include "Pixel.hpp"
#include "Color.hpp"

Pixel*** PrepareNewMap(vec::IVec2 size);

class InsertPixel{
	public:
		InsertPixel(RGB _color, vec::IVec2 _position);

		RGB color = RGB();
		vec::IVec2 position = vec::IVec2::Undefined;
};

class Layer{
	private:
		vec::IVec2 size;
		vec::IVec2 startPosition;

		void OpenPpm(std::string path);

		

	protected:
		

	public:
		void Allocate();
		void Dealocate();

		Pixel*** layerMap = nullptr;
		Pixel*** buffer = nullptr;

		bool hasBuffer();

		Layer* nextLayer = nullptr;
		Layer* previousLayer = nullptr;

		void Move(vec::IVec2 vec);
		void Resize(vec::IVec2 vec);
		void Edit(std::vector<InsertPixel> inserted);
		void Open(std::string path);
		void Save(std::string name);

		Layer();
		Layer(std::string path);
		Layer(vec::IVec2 vec);
		~Layer();

		Pixel* GetPixel(vec::IVec2 vec);
		Pixel* GetBuffer(vec::IVec2 vec);
		vec::IVec2 GetSize();
		vec::IVec2 GetStart();

		void SetBuffer(Pixel*** _buffer);
		
		void AllocateBuffer();
		void DeallocateBuffer();

		void ReadFile(std::string path);
		void WriteFile(std::string name);

		int GetLayerId();
};

#endif
