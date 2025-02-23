#pragma once

#include <string>
#include <cmath>

template<typename Key>
class Hash {
public:
	size_t operator() (const Key& k) const { return 0; };
};

template<>
class Hash<std::string> {
public:
	size_t operator()(const std::string& key) {
		size_t hashVal = 0;
		for (char c : key)
			hashVal = hashVal * 37 + c;
		return hashVal;
	}
};

template<>
class Hash<int> {
public:
	size_t operator()(const int& x) {
		return std::abs(x);
	}
};