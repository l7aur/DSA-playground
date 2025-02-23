#pragma once

#include <iostream>

template <typename Object>
class Vector
{
public:
	// constructor
	explicit Vector(size_t initialSize = 0);
	
	// destructor
	~Vector() { delete[] objects; };
	
	// copy constructor
	Vector(const Vector& rhs) noexcept;
	
	// copy assignment
	Vector& operator=(const Vector& rhs) noexcept;
	
	// move constructor
	Vector(Vector&& rhs) noexcept;
	
	// move assignment
	Vector& operator=(Vector&& rhs) noexcept;

	// index operators
	Object& operator[](int index) { return objects[index]; };
	const Object& operator[](int index) const { return objects[index]; };

	//methods
	void resize(size_t newSize);
	void reserve(size_t capacity);
	bool isEmpty() const { return size() == 0; };
	size_t size() const { return theSize; };
	size_t capacity() const { return theCapacity; };
	void push_back(const Object& x);
	void push_back(Object&& x);
	void pop_back() { --theSize; };
	const Object& back() const { return objects[theSize - 1]; };
	const Object& front() const { return objects[0]; };

	// iterator magic
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin() { return &objects[0]; };
	const_iterator begin() const { return &objects[0]; };
	iterator end() { return &objects[theSize]; };
	const_iterator end() const { return &objects[theSize]; };

	static const int SPARE_CAPACITY = 16;
private:
	size_t theSize;
	size_t theCapacity;
	Object* objects;
};

// for pretty print
template<typename Object>
std::ostream& operator<<(std::ostream& out, const Vector<Object>& v)
{
	for (typename Vector<Object>::const_iterator i = v.begin(); i != v.end(); i++)
		out << *i << ' ';
	return out;
}

template<typename Object>
inline Vector<Object>::Vector(size_t initialSize)
	: theSize(initialSize), theCapacity(initialSize + SPARE_CAPACITY)
{
	objects = new Object[theCapacity];
}

template<typename Object>
inline Vector<Object>::Vector(const Vector& rhs) noexcept
	: theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr)
{
	objects = new Object[theCapacity];
	for (int i = 0; i < theSize; i++)
		objects[i] = rhs.objects[i];
}

template<typename Object>
inline Vector<Object>& Vector<Object>::operator=(const Vector& rhs) noexcept
{
	Vector copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename Object>
inline Vector<Object>::Vector(Vector&& rhs) noexcept
	: theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects)
{
	rhs.objects = nullptr;
	rhs.theCapacity = rhs.theSize = 0;
}

template<typename Object>
inline Vector<Object>& Vector<Object>::operator=(Vector&& rhs) noexcept
{
	std::swap(this->theSize, rhs.theSize);
	std::swap(this->theCapacity, rhs.theCapacity);
	std::swap(this->objects, rhs.objects);
	return *this;
}

template<typename Object>
inline void Vector<Object>::resize(size_t newSize)
{
	if (newSize > theCapacity)
		reserve(newSize + 2);
	theSize = newSize;
}

template<typename Object>
inline void Vector<Object>::reserve(size_t capacity)
{
	if (capacity <= theSize)
		return;
	Object* newArray = new Object[capacity];
	for (int i = 0; i < theSize; i++)
		newArray[i] = std::move(objects[i]);
	theCapacity = capacity;
	std::swap(objects, newArray);
	delete[] newArray;
}

template<typename Object>
inline void Vector<Object>::push_back(const Object& x)
{
	if (theSize == theCapacity)
		reserve(2 * theCapacity + 1);
	objects[theSize++] = x;
}

template<typename Object>
inline void Vector<Object>::push_back(Object&& x)
{
	if (theSize == theCapacity)
		reserve(2 * theCapacity + 1);
	objects[theSize++] = std::move(x);
}

