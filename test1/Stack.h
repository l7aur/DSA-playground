#pragma once

#include "Vector.h"

template <typename Object>
class Stack {
public:
	Stack() = default;
	~Stack() = default;
	Stack(const Stack<Object>& rhs) noexcept : s(rhs.s) {}
	Stack& operator=(const Stack<Object> rhs) noexcept;
	Stack(Stack<Object>&& rhs) noexcept : s(std::move(rhs.s)) {}
	Stack& operator=(Stack<Object>&& rhs) noexcept;

	void push(const Object& rhs) { s.push_back(rhs); }
	void push(Object&& rhs) { s.push_back(rhs); }
	void pop() { s.pop_back(); }
	const Object& top() const { return s.back(); }
	void clear() { s.clear(); }
	bool isEmpty() const { return s.empty(); }
	int size() const { return s.size(); }
	friend std::ostream& operator<<(std::ostream& out, const Stack<Object>& ss) {
		for (typename Vector<Object>::const_iterator i = ss.s.begin(); i != ss.s.end(); ++i)
			out << *i << " ";
		return out;
	}
private:
	Vector<Object> s;
};

template<typename Object>
inline Stack<Object>& Stack<Object>::operator=(const Stack<Object> rhs) noexcept
{
	Stack<Object> copy = rhs;
	std::swap(*this, rhs);
	return *this;
}

template<typename Object>
inline Stack<Object>& Stack<Object>::operator=(Stack<Object>&& rhs) noexcept
{
	std::swap(s, rhs.s);
	return *this;
}
