#pragma once

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
		Object& retrieve() const { return current->data; };
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
private:
	struct Node {
		Object data;
		Node* next, * prev;
		Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr);
		Node(Object&& d, Node* p = nullptr, Node* n = nullptr);
	};

public:
	List() { init(); };
	~List();
	List(const List& rhs);
	List& operator=(const List& rhs);
	List(const List&& rhs);
	List& operator=(List&& rhs);

	int size() const { return theSize; };
	bool empty() const { return theSize == 0; };
	void clear();
	Object& front() { return head->next; };
	const Object& front() const { return head->next; };
	Object& back() { return tail->prev; };
	const Object& back() const { return tail->prev; };
	void push_front(const Object& x);
	void push_front(Object&& x);
	void push_back(const Object& x);
	void push_back(Object&& x);
	void pop_front();
	void pop_back();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	iterator insert(iterator itr, const Object& x);
	iterator insert(iterator itr, Object&& x);
	iterator erase(iterator itr);
	iterator erase(iterator from, iterator to);

private:
	int theSize;
	Node* head, * tail;

	void init();
};

// for pretty print
template <typename Object>
std::ostream& operator<<(std::ostream& out, const List<Object>& l) {
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
inline List<Object>::List(const List& rhs)
{
	init();
	for (auto& i : rhs)
		push_back(i);
}

template<typename Object>
inline List<Object>& List<Object>::operator=(const List& rhs)
{
	List<Object> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename Object>
inline List<Object>::List(const List&& rhs)
	: theSize(rhs.theSize), head(rhs.head), tail(rhs.tail)
{
	rhs.theSize = 0;
	rhs.head = rhs.tail = nullptr;
}

template<typename Object>
inline List<Object>& List<Object>::operator=(List&& rhs)
{
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

template<typename Object>
inline void List<Object>::push_front(const Object& x)
{
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
inline void List<Object>::init()
{
	theSize = 0;
	head = new Node();
	tail = new Node();
	head->next = tail;
	tail->prev = head;
}
