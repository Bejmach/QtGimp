#include <vector>

#include "GraphLayer.hpp"
#include "Graphs.hpp"

Pixel*** GraphLayer::DrawLagrange(std::vector<vec::IVec2> points, int min, int max, RGB colorOutput, bool clamp){
	if(points.size()<2){
		return nullptr;
	}
	int size = max-min+1;
	

	std::vector<int> inputs(size);
	for(int i=0; i<size; i++){
		inputs[i] = i+min;
	}

	Pixel*** graph = new Pixel**[size];
	for (int i = 0; i < size; i++) {
		graph[i] = new Pixel*[size];
		for (int j = 0; j < size; j++) {
			graph[i][j] = nullptr; // Initialize to nullptr
		}
	}


	for(int i=0; i<points.size(); i++){
		for(int j=0; j<points.size(); j++){
			if(i==j) continue;
			if(points[i].x == points[j].x){
				return graph;
			}
		}	
	}

	std::vector<int> answers = Graphs::Lagrange(points, inputs);

	if(clamp){
		for(int i=0; i<answers.size(); i++){
			if(answers[i]>max){
				answers[i] = max;
			}
			else if(answers[i]<min){
				answers[i] = min;
			}
		}
	}

	for (int i = 0; i < size && i < answers.size(); i++) {
		int y = answers[i] - min; // Map y to graph index
		if (y >= 0 && y < size) {
			delete graph[i][size-1-y];
			graph[i][size-1 - y] = new Pixel(colorOutput.R, colorOutput.G, colorOutput.B, colorOutput.A);
		}
	}

	return graph;
}
