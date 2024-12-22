#ifndef GRAPHLAYER_HPP
#define GRAPHLAYER_HPP

#include "Layer.hpp"

class GraphLayer{
	public:
		static Pixel*** DrawLagrange(std::vector<vec::IVec2> points, int min, int max, RGB colorOutput = RGB(0,0,0), bool clamp = false);
};

#endif
