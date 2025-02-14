#pragma once

#include <iostream>

template <typename Object>
class List {
public:
	class const_iterator {
	public:
		const_iterator() : current(nullptr) {};
		const Object& operator*() const { return retrieve(); };
		const_iterator& operator++();
		const_iterator& operator++(int);
		bool operator==(const const_iterator& rhs) const { return current == rhs.current; };
		bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); };

	protected:
		struct List<Object>::Node* current;
		const Object& retrieve() const { return current->data; };
		const_iterator(struct List<Object>::Node* p) : current(p) {};

		friend class List<Object>;
	};
	class iterator : public const_iterator{
	public:
		iterator() {};
		Object& operator*() { return const_iterator::operator*(); };
		iterator& operator++();
		iterator& operator++(int);
	protected:
		iterator(struct List<Object>::Node* p) : const_iterator(p) {};

		friend class List<Object>;
	};
	List() { init(); };
	~List();
	List(const List& rhs) noexcept;
	List& operator=(const List& rhs) noexcept;
	List(List&& rhs) noexcept;
	List& operator=(List&& rhs) noexcept;

	int size() const { return theSize; };
	bool empty() const { return theSize == 0; };
	void clear();
	Object& front() { return *begin(); };
	const Object& front() const { return *begin(); };
	Object& back() { return *--end(); };
	const Object& back() const { return *--end(); };
	void push_front(const Object& x) { insert(begin(), x); };
	void push_front(Object&& x) { insert(begin(), std::move(x)); };
	void push_back(const Object& x) { insert(end(), x); };
	void push_back(Object&& x) { insert(end(), std::move(x)); };
	void pop_front() { erase(begin()); };
	void pop_back() { erase(--end()); };

	iterator begin() { return head->next; };
	const_iterator begin() const { return head->next; };
	iterator end() { return tail; };
	const_iterator end() const { return tail; };
	iterator insert(iterator itr, const Object& x);
	iterator insert(iterator itr, Object&& x);
	iterator erase(iterator itr);
	iterator erase(iterator from, iterator to);

private:
	struct Node {
		Object data;
		Node* next, * prev;
		Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr);
		Node(Object&& d, Node* p = nullptr, Node* n = nullptr);
	};
	int theSize;
	Node* head, * tail;

	void init();
};

// for pretty print
template <typename Object>
std::ostream& operator<<(std::ostream& out, const List<Object>& l) {
	for (typename List<Object>::const_iterator i = l.begin(); i != l.end(); ++i)
		out << *i << " ";
	return out;
}

template<typename Object>
inline List<Object>::~List()
{
	clear();
	delete head;
	delete tail;
}

template<typename Object>
inline List<Object>::List(const List& rhs) noexcept
{
	init();
	for (auto& i : rhs)
		push_back(i);
}

template<typename Object>
inline List<Object>& List<Object>::operator=(const List& rhs) noexcept
{
	List<Object> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename Object>
inline List<Object>::List(List&& rhs) noexcept
	: theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
{
	rhs.theSize = 0;
	rhs.head = rhs.tail = nullptr;
}

template<typename Object>
inline List<Object>& List<Object>::operator=(List&& rhs) noexcept
{
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

template<typename Object>
inline void List<Object>::clear()
{
	while (!empty())
		pop_front();
}

template<typename Object>
inline List<Object>::Node::Node(const Object& d, Node* p, Node* n)
	: data(d), prev(p), next(n)
{
}

template<typename Object>
inline List<Object>::Node::Node(Object&& d, Node* p, Node* n)
	: data(std::move(d)), prev(p), next(n)
{
}

template<typename Object>
inline typename List<Object>::const_iterator& List<Object>::const_iterator::operator++()
{
	current = current->next;
	return *this;
}

template<typename Object>
inline typename List<Object>::const_iterator& List<Object>::const_iterator::operator++(int)
{
	const_iterator old = *this;
	++(*this);
	return old;
}

template<typename Object>
inline typename List<Object>::iterator& List<Object>::iterator::operator++()
{
	this->current = this->current->next;
	return *this;
}

template<typename Object>
inline typename List<Object>::iterator& List<Object>::iterator::operator++(int)
{
	iterator old = *this;
	++(*this);
	return old;
}

template<typename Object>
inline typename List<Object>::iterator List<Object>::insert(iterator itr, const Object& x)
{
	Node* p = itr.current;
	++theSize;
	return { p->prev = p->prev->next = new Node{x, p->prev, p} };
}

template<typename Object>
inline typename List<Object>::iterator List<Object>::insert(iterator itr, Object&& x)
{
	Node* p = itr.current;
	++theSize;
	return { p->prev = p->prev->next = new Node{std::move(x), p->prev, p} };
}

template<typename Object>
inline typename List<Object>::iterator List<Object>::erase(iterator itr)
{
	Node* p = itr.current;
	iterator retVal{ p->next };
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--theSize;
	return retVal;
}

template<typename Object>
inline typename List<Object>::iterator List<Object>::erase(iterator from, iterator to)
{
	for (iterator i = from; i != to;)
		i = erase(i);
	return to;
}

template<typename Object>
inline void List<Object>::init()
{
	theSize = 0;
	head = new Node();
	tail = new Node();
	head->next = tail;
	tail->prev = head;
}
