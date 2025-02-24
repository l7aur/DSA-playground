#pragma once

#include <random>

namespace Util {
	size_t nextPrime(const size_t& x)
	{
		size_t aux = x;
		while (true) {
			bool isPrime = true;
			if (aux % 2 == 0) {
				aux++;
				continue;
			}
			for (size_t i = 3; i * i < aux; i += 2)
				if (aux % i == 0) {
					isPrime = false;
					break;
				}
			if (isPrime) {
				if (aux < x)
					std::cerr << "Searching for the next prime overflowed!\n";
				return aux;
			}
			aux++;
		}
		std::cerr << "No next prime after " << x << " was found!\n";
		return 0;
	}

	class UniformRandomInt {
	public:
		explicit UniformRandomInt(const int seed = 0) { srand(seed); };
		int nextPositiveInt(unsigned int limit = UINT_MAX) { return rand() % limit; };
	private:
	};
}