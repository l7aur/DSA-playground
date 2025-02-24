#pragma once

#include "CuckooHashFamily.h"
#include "Vector.h"
#include "Util.h"

template<typename AnyType, typename HashFamily>
class CuckooHashTable {
public:
	explicit CuckooHashTable(const size_t size = 101)
		: array{ Util::nextPrime(size) }, rehashes{ 0 }, r{}
	{
		numHashFunctions = hashFunctions.getNumberOfFunctions();
		makeEmpty();
	}
	void makeEmpty() {
		currentSize = 0;
		for (auto i = array.begin(); i != array.end(); ++i)
			i->isActive = false;
	}
	bool contains(const AnyType& x) const { return findPos(x) != -1; };
	bool remove(const AnyType& x);
	bool insert(const AnyType& x);
	bool insert(AnyType&& x);

private:
	struct HashEntry {
		AnyType element;
		bool isActive;
		HashEntry(const AnyType& e = AnyType(), bool a = false)
			: element{ e }, isActive{ a } { }
		HashEntry(AnyType&& e, bool a = false)
			: element{ std::move(e) }, isActive{ a } { }
	};

	Vector<HashEntry> array;
	int currentSize;
	int numHashFunctions;
	int rehashes;
	Util::UniformRandomInt r;
	HashFamily hashFunctions;

	bool insertHelper1(const AnyType& xx);
	bool insertHelper1(AnyType&& xx);
	bool isActive(int currentPos) const { return array[currentPos].isActive; };
	size_t myHash(const AnyType& x, int which) const { return hashFunctions.hash(x, which) % array.size(); }
	int findPos(const AnyType& x) const {
		for (int i = 0; i < numHashFunctions; ++i) {
			int pos = myHash(x, i);
			if (isActive(pos) && array[pos].element == x)
				return pos;
		}
		return -1;
	}
	void expand() { rehash(static_cast<int>(array.size() / MAX_LOAD / 10.0f)); }
	void rehash() {
		hashFunctions.generateNewFunctions();
		rehash(array.size());
	}
	void rehash(int newSize) {
		Vector<HashEntry> oldArray = array;
		array.resize(Util::nextPrime(newSize));
		for (auto i = array.begin(); i != array.end(); ++i)
			i->isActive = false;
		currentSize = 0;
		for (auto i = array.begin(); i != array.end(); ++i)
			if (i->isActive)
				insert(std::move(i->element));
	}

	static const int MAX_LOAD = 4; // use a / 10 every time it is used
	static const int ALLOWED_REHASHES = 5;
};

template<typename AnyType, typename HashFamily>
inline bool CuckooHashTable<AnyType, HashFamily>::remove(const AnyType& x)
{
	int currPos = findPos(x);
	if (!isActive(currPos))
		return false;
	array[currPos].isActive = false;
	--currentSize;
	return true;
}

template<typename AnyType, typename HashFamily>
inline bool CuckooHashTable<AnyType, HashFamily>::insert(const AnyType& x)
{
	if (contains(x))
		return false;
	if (currentSize >= array.size() * MAX_LOAD / 10.0f)
		expand();
	return insertHelper1(x);
}

template<typename AnyType, typename HashFamily>
inline bool CuckooHashTable<AnyType, HashFamily>::insert(AnyType&& x)
{
	if (contains(x))
		return false;
	if (currentSize >= array.size() * MAX_LOAD / 10.0f)
		expand();
	return insertHelper1(std::move(x));
}

template<typename AnyType, typename HashFamily>
inline bool CuckooHashTable<AnyType, HashFamily>::insertHelper1(const AnyType& xx)
{
	const int COUNT_LIMIT = 100;
	AnyType x = xx;
	while (true) {
		int lastPos = -1;
		int pos;
		for (int count = 0; count < COUNT_LIMIT; count++) {
			for (int i = 0; i < numHashFunctions; i++) {
				pos = myHash(x, i);
				if (!isActive(pos)) {
					array[pos] = std::move(HashEntry{ std::move(x), true });
					++currentSize;
					return true;
				}
			}
			int i = 0;
			do {
				pos = myHash(x, r.nextPositiveInt(numHashFunctions));
			} while (pos == lastPos && i++ < 5);
			lastPos = pos;
			std::swap(x, array[pos].element);
		}
		if (++rehashes > ALLOWED_REHASHES) {
			expand();
			rehashes = 0;
		}
		else
			rehash();
	}
	return false;
}

template<typename AnyType, typename HashFamily>
inline bool CuckooHashTable<AnyType, HashFamily>::insertHelper1(AnyType&& xx)
{
	const int COUNT_LIMIT = 100;
	AnyType x = std::move(xx);
	while (true) {
		int lastPos = -1;
		int pos;
		for (int count = 0; count < COUNT_LIMIT; count++) {
			for (int i = 0; i < numHashFunctions; i++) {
				pos = myHash(x, i);
				if (!isActive(pos)) {
					array[pos] = std::move(HashEntry{ std::move(x), true });
					++currentSize;
					return true;
				}
			}
			int i = 0;
			do {
				pos = myHash(x, r.nextPositiveInt(numHashFunctions));
			} while (pos == lastPos && i++ < 5);
			lastPos = pos;
			std::swap(std::move(x), array[pos].element);
		}
		if (++rehashes > ALLOWED_REHASHES) {
			expand();
			rehashes = 0;
		}
		else
			rehash();
	}
	return false;
}
