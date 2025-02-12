#pragma once

#include "Vector.h"

template <typename Object>
class Stack: private Vector<Object> {
public:
	Stack() = default;
	~Stack() = default;

	void push(const Object& x) { Vector<Object>::push_back(x); };
	void push(Object&& x) { Vector<Object>::push_back(x); };
	void pop() { Vector<Object>::pop_back(); };
	const Object& top() const { return Vector<Object>::back(); };
	void clear() { Vector<Object>::clear(); };
	friend std::ostream& operator<<(std::ostream& out, const Stack<Object>& s) {
		for (typename Vector<Object>::const_iterator i = s.begin(); i != s.end(); ++i)
			out << *i << " ";
		return out;
	};
private:
};