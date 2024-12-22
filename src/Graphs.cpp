#include "Graphs.hpp"

std::vector<int> Graphs::Lagrange(std::vector<vec::IVec2> points, std::vector<int> inputs){
	std::vector<int> outputs(inputs.size());
	if(points.size()<2){
		return outputs;
	}

	for(int i=0; i<inputs.size(); i++){
		std::vector<double> pointAnswers;
		for(int j=0; j<points.size(); j++){
			double upperFunction = 1;
			double lowerFunction = 1;
			int pointX = points[j].x;

			for(int g=0; g<points.size(); g++){
				if(j == g) continue;

				upperFunction = upperFunction * (double)(inputs[i] - points[g].x);
				lowerFunction = lowerFunction * (double)(pointX-points[g].x);
			}
			pointAnswers.push_back(((double)points[j].y*upperFunction)/lowerFunction);
		}
		double finalAnswer = 0;
		for(int j=0; j<pointAnswers.size(); j++){
			finalAnswer+=pointAnswers[j];
		}
		outputs[i] = finalAnswer;
	}
	return outputs;
}
