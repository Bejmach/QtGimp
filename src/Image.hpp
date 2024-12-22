#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Layer.hpp"

#include <iostream>
#include <fstream>

class Image{
	private:
		vec::IVec2 size = vec::IVec2(0,0);

		Layer* firstLayer = nullptr;
		Layer* lastLayer = nullptr;

		void UpdateLastLayer();

		Pixel*** renderImage;
		
		
		
	public:

		size_t focusedLayerId;


		Image();
		Image(vec::IVec2 vec);
		~Image();

		void UpdateRender();

		void Resize(vec::IVec2 vec);

		int GetLayersNumber();
		vec::IVec2 GetLayerPosition(int layerId);
		vec::IVec2 GetLayerSize(int layerId);

		void AddLayer(int newLayerId);
		void AddLayerStart();
		void AddLayerEnd();
		void MoveLayer(int layerId, int newLayerId);
		void SwapLayers(int layer1Id, int layer2Id);
		void DeleteLayer(int layerId);
		void DeleteAllLayers();

		Layer* GetLayer(int layerId);
        Layer* GetLastLayer();
        Layer* GetFirstLayer();

		vec::IVec2 GetSize();
		Pixel*** GetRender();
		
		void Open(std::string path);
		void Save(std::string name);
		void Close();

		Pixel*** PrepareNewRender(vec::IVec2 vec);
		void DeallocateRender();
		void ClearRender();

		void ScaleToContent();

		std::pair<bool, std::string> ConsoleInput(std::string command);

		void ApplyLayerBuffer();
		void RevertLayerBuffer();
};

#endif
