#pragma once

#include "List.h"

template<typename Object>
class Queue : private List<Object> {
public:
	Queue() = default;
	~Queue() = default;
	Queue(const Queue<Object>& q) : List<Object>(q) {}
	Queue& operator=(const Queue<Object>& q) { if (this != &q)  List<Object>::operator=(q); return *this; }

	Queue(Queue<Object>&& q) : List<Object>(std::move(q)) {}
	Queue& operator=(Queue<Object>&& q) { if (this != &q) List<Object>::operator=(std::move(q)); return *this; }

	void insert(const Object& x) { List<Object>::push_back(x); }
	void insert(Object&& x) { List<Object>::push_back(std::move(x)); }
	void pop() { List<Object>::pop_front(); }
	const Object& front() const { return List<Object>::front(); }
	void clear() { List<Object>::clear(); }
	friend std::ostream& operator<<(std::ostream& out, const Queue<Object>& q) {
		for (typename List<Object>::const_iterator i = q.begin(); i != q.end(); ++i)
			out << *i << " ";
		return out;
	}
private:
};