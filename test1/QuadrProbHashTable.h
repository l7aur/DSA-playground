#pragma once

#include <iostream>
#include <string>
#include "Vector.h"
#include "Hash.h"

/* SUPPOSE A LOAD FACTOR OF AT MOST 0.5 FOR CORRECT FUNCTIONALITY */
/* 
* (Theorem)
* It can be proved that if the load factor is below 0.5 and the size
* of the table is a prime number means that there is always a free
* spot to insert a new item under the assumptions of quadratic probing.
*/
template<typename Object>
class QuadrProbHashTable {
public:
	explicit QuadrProbHashTable(size_t size = 101) : array(nextPrime(size)) { makeEmpty(); }
	bool contains(const Object& x) const { return isActive(findPos(x)); }
	void makeEmpty();
	bool insert(const Object& x);
	bool insert(Object&& x);
	bool remove(const Object& x);
	const size_t size() const { return array.size(); }
	const Object& at(int i) const { return array[i].element; }
	std::string getState(int i) const;

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry {
		Object element;
		EntryType info;
		HashEntry(const Object& x = Object{}, EntryType t = EMPTY)
			: element(x), info(t) { }
		HashEntry(Object&& x, EntryType t = EMPTY)
			: element(std::move(x)), info(t) { }
	};
	Vector<HashEntry> array;
	size_t currentSize;
	
	bool isActive(size_t currentPos) const { return (array[static_cast<int>(currentPos)].info == ACTIVE); }
	size_t findPos(const Object& x) const;
	void rehash() { };
	size_t myHash(const Object& x) const;
	size_t nextPrime(const size_t& x) const;
	//int qProbingF(const int& i) const { return i * i; }
};

template<typename Object>
std::ostream& operator<<(std::ostream& out, const QuadrProbHashTable<Object>& tab) {
	for (int i = 0; i < tab.size(); i++)
		out << "Hash value " << i << ": " << tab.getState(i) << " -> " << tab.at(i) << '\n';
	return out;
}

template<typename Object>
inline size_t QuadrProbHashTable<Object>::findPos(const Object& x) const
{
	/*
	this method supposes the load factor is below 0.5
	
	if the table were to be used for load factors above 0.5
	an additional counter should be added to be not let the 
	while iterate over the same entries multiple times
	*/
	 
	int offset = 1;
	int currentPos = static_cast<int>(myHash(x));
	while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
		currentPos += offset;
		offset += 2;
		if (currentPos >= array.size())
			currentPos -= static_cast<int>(array.size());
	}
	return static_cast<size_t>(currentPos);
}

template<typename Object>
inline size_t QuadrProbHashTable<Object>::myHash(const Object& x) const
{
	static Hash<Object> h;
	return h(x) % array.size();
}

template<typename Object>
inline size_t QuadrProbHashTable<Object>::nextPrime(const size_t& x) const
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

template<typename Object>
inline void QuadrProbHashTable<Object>::makeEmpty()
{
	currentSize = 0;
	for (auto i = array.begin(); i != array.end(); ++i)
		i->info = EMPTY;
}

template<typename Object>
inline bool QuadrProbHashTable<Object>::insert(const Object& x)
{
	size_t currentPos = findPos(x);
	if (isActive(currentPos))
		return false;
	array[static_cast<int>(currentPos)].element = x;
	array[static_cast<int>(currentPos)].info = ACTIVE;
	if (++currentSize > array.size() / 2)
		rehash();
	return true;
}

template<typename Object>
inline bool QuadrProbHashTable<Object>::insert(Object&& x)
{
	size_t currentPos = findPos(x);
	if (isActive(currentPos))
		return false;
	array[static_cast<int>(currentPos)].element = std::move(x);
	array[static_cast<int>(currentPos)].info = ACTIVE;
	if (++currentSize > array.size() / 2)
		rehash();
	return true;
}

template<typename Object>
inline bool QuadrProbHashTable<Object>::remove(const Object& x)
{
	size_t currentPos = findPos(x);
	if (!isActive(currentPos))
		return false;
	array[static_cast<int>(currentPos)].info = DELETED;
	return true;
}

template<typename Object>
inline std::string QuadrProbHashTable<Object>::getState(int i) const
{
	switch (array[i].info)
	{
	case EMPTY:
		return "EMPTY";
	case DELETED:
		return "DELETED";
	}
	return "ACTIVE";
}
