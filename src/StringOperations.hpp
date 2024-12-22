#ifndef STRINGOPERATIONS_HPP
#define STRINGOPERATIONS_HPP

#include <iostream>
#include <vector>
#include <algorithm>

namespace SO{
	std::vector<std::string> Split(std::string str, std::string delimiter);

	bool isNumeric(const std::string& s);
}

#endif
