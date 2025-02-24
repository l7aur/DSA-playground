#pragma once

#include <string>

#include "Vector.h"
#include "Util.h"

template<typename AnyType>
class CuckooHashFamily {
public:
	size_t hash(const AnyType& x, int which) const;
	int getNumberOfFunctions() const;
	void generateNewFunction();
};

template<int count>
class StringHashFamily {
public:
	StringHashFamily() : MULTIPLIERS(count) { generateNewFunctions(); }
	int getNumberOfFunctions() const { return count; }
	void generateNewFunctions() {
		for (auto i = MULTIPLIERS.begin(); i != MULTIPLIERS.end(); ++i)
			*i = r.nextPositiveInt();
	}
	size_t hash(const std::string& x, int which) const {
		const int multiplier = MULTIPLIERS[which];
		size_t hashVal = 0;
		for (auto c : x)
			hashVal = multiplier * hashVal + c;
		return hashVal;
	}
private:
	Vector<int> MULTIPLIERS;
	Util::UniformRandomInt r;
};