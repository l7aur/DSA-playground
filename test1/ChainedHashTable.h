#pragma once

#include <iostream>
#include "Vector.h"
#include "List.h"
#include "Hash.h"

template<typename Object>
class ChainedHashTable {
public:
	explicit ChainedHashTable(const size_t size = 101) {
		theLists = Vector<List<Object>>(size);
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

	void rehash() {};
	size_t myHash(const Object& x) const;
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
inline size_t ChainedHashTable<Object>::myHash(const Object& x) const
{
	static Hash<Object> h;
	return h(x) % theLists.size();
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
