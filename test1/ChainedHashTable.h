#pragma once

#include <iostream>
#include "Vector.h"
#include "List.h"
#include "Hash.h"

template<typename Object>
class ChainedHashTable {
public:
	explicit ChainedHashTable(const size_t size = 101) {
		theLists = Vector<List<Object>>(nextPrime(size));
		currentSize = 0;
		for (int i = 0; i < size; i++)
			theLists[i] = List<Object>();
	}
	size_t size() const { return theLists.size(); }
	List<Object>& operator[](const size_t i) { return theLists[i]; };
	const List<Object>& operator[](const size_t i) const { return theLists[static_cast<int>(i)]; };
	bool contains(const Object& x);
	void makeEmpty();
	bool insert(const Object& x);
	bool insert(Object&& x);
	bool remove(const Object& x);
private:
	Vector<List<Object>> theLists;
	size_t currentSize;

	void rehash();
	size_t myHash(const Object& x) const;
	size_t nextPrime(const size_t& x) const;
};

template<typename Object>
std::ostream& operator<<(std::ostream& out, const ChainedHashTable<Object>& tab) {
	for(size_t i = 0; i < tab.size(); i++) {
		out << "Hash value " << i << " -> ";
		for (auto j = tab[i].begin(); j != tab[i].end(); j++)
			out << *j << ' ';
		out << '\n';
	}
	return out;
}

template<typename Object>
inline void ChainedHashTable<Object>::rehash()
{
	Vector<List<Object>> oldLists = theLists;
	theLists.resize(nextPrime(2 * theLists.size()));
	for (auto i = theLists.begin(); i != theLists.end(); ++i)
		i->clear();

	currentSize = 0;
	for (auto i = oldLists.begin(); i != oldLists.end(); ++i)
		for (auto j = i->begin(); j != i->end(); ++j)
			i->insert(i->begin(), std::move(*j));
}

template<typename Object>
inline size_t ChainedHashTable<Object>::myHash(const Object& x) const
{
	static Hash<Object> h;
	return h(x) % theLists.size();
}

template<typename Object>
inline size_t ChainedHashTable<Object>::nextPrime(const size_t& x) const
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
inline bool ChainedHashTable<Object>::contains(const Object& x)
{
	auto& l = theLists[myHash(x)];
	return (l.find(x, l.begin(), l.end()) != l.end());
}

template<typename Object>
inline void ChainedHashTable<Object>::makeEmpty()
{
	for (auto& l : theLists)
		l.clear();
}

template<typename Object>
inline bool ChainedHashTable<Object>::insert(const Object& x)
{
	auto& l = theLists[static_cast<int>(myHash(x))];
	if (l.find(x, l.begin(), l.end()) != l.end())
		return false;
	l.push_back(x);
	if (++currentSize > theLists.size())
		rehash();
	return true;
}

template<typename Object>
inline bool ChainedHashTable<Object>::insert(Object&& x)
{
	auto& l = theLists[static_cast<int>(myHash(x))];
	if (l.find(x, l.begin(), l.end()) != l.end())
		return false;
	l.push_back(std::move(x), l.begin(), l.end());
	if (++currentSize > theLists.size())
		rehash();
	return true;
}

template<typename Object>
inline bool ChainedHashTable<Object>::remove(const Object& x)
{
	auto& l = theLists[static_cast<int>(myHash(x))];
	auto itr = l.find(x, l.begin(), l.end());
	if (itr == l.end())
		return false;
	l.erase(itr);
	--currentSize;
	return true;
}
