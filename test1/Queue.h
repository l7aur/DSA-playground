#pragma once

#include "List.h"

template<typename Object>
class Queue {
public:
	Queue() {};
	~Queue() {};
	Queue(const Queue<Object>& rhs) noexcept : q(rhs.q) {}
	Queue& operator=(const Queue<Object>& rhs) noexcept;

	Queue(Queue<Object>&& rhs) noexcept : q(std::move(rhs.q)) {}
	Queue& operator=(Queue<Object>&& rhs) noexcept;

	void insert(const Object& x) { q.push_back(x); }
	void insert(Object&& x) { q.push_back(std::move(x)); }
	void pop() { q.pop_front(); }
	const Object& front() const { return q.front(); }
	void clear() { q.clear(); }
	bool isEmpty() const { return q.empty(); }
	int size() const { return q.size(); }
	friend std::ostream& operator<<(std::ostream& out, const Queue<Object>& qq) {
		
		for (typename List<Object>::const_iterator i = qq.q.begin(); i != qq.q.end(); ++i)
			out << *i << " ";
		return out;
	}
private:
	List<Object> q{};
};

template<typename Object>
inline Queue<Object>& Queue<Object>::operator=(const Queue<Object>& rhs) noexcept
{
	Queue<Object> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename Object>
inline Queue<Object>& Queue<Object>::operator=(Queue<Object>&& rhs) noexcept
{
	std::swap(q, rhs.q);
	return *this;
}
