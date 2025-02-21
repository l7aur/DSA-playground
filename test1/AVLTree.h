#pragma once

#include <iostream>
#include "AVLNode.h"

template <typename Object>
class AVLTree {
public:
	AVLTree() : root(nullptr) {};
	~AVLTree() { clear(); };
	AVLTree(const AVLTree<Object>& rhs) noexcept : root(nullptr) { clone(rhs.root); };
	AVLTree& operator=(const AVLTree& rhs) noexcept;
	AVLTree(AVLTree<Object>&& rhs) noexcept : root(nullptr) { clone(std::move(rhs.root)); }
	AVLTree& operator=(AVLTree&& rhs) noexcept;


	/* Interesting fact:
	If this class inherits the BSTree class and the insert methods are declared as virtual and/or overriden
	the compiler won't know which one to pick for something like insert(10) at runtime.
	When the methods are not virtual, the compiler matches a call at compile time based on type matching (compile-time resolution)
	When the methods are virtual, the compiler defers the matching until runtime, but at runtime overloading cannot be solved, 
	i.e. which one to call out of const& and && = conflict with the dynamic dispatch = the method that is picked depends on the type of 
	object.
	*/
	void insert(const Object& x)  { insert(x, root); }
	void insert(Object&& x) { insert(std::move(x), root); }
	void remove(const Object& x) { remove(x, root); }
	bool isEmpty() const { return root == nullptr; }
	void clear() { makeEmpty(root); }
	friend std::ostream& operator<<(std::ostream& out, const AVLTree& t) {
		t.printTree(out, t.root);
		return out;
	}
private:
	AVLNode<Object>* root;
	static const int ALLOWED_IMBALANCE_FACTOR = 1;

	int getHeight(AVLNode<Object>* t) const { return (t == nullptr) ? -1 : t->height; };
	void insert(const Object& x, AVLNode<Object>*& t);
	void insert(Object&& x, AVLNode<Object>*& t);
	void remove(const Object& x, AVLNode<Object>*& t);
	void makeEmpty(AVLNode<Object>*& t);

	void balance(AVLNode<Object>*& t);
	void rotateWithLeftChild(AVLNode<Object>*& k2);
	void rotateWithRightChild(AVLNode<Object>*& k1);
	void doubleWithLeftChild(AVLNode<Object>*& k3);
	void doubleWithRightChild(AVLNode<Object>*& k1);
	void printTree(std::ostream& out, AVLNode<Object>* t, int depth = 0) const;
	AVLTree<Object>* clone(AVLNode<Object>* t) const;
	AVLNode<Object>* findMin(AVLNode<Object>* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->left != nullptr)
			t = t->left;
		return t;
	}
	AVLNode<Object>* findMax(AVLNode<Object>* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->right != nullptr)
			t = t->right;
		return t;
	}
};

template<typename Object>
inline AVLTree<Object>& AVLTree<Object>::operator=(const AVLTree& rhs) noexcept
{
	makeEmpty(root);
	this->root = rhs.clone(rhs.root);
	return *this;
}

template<typename Object>
inline AVLTree<Object>& AVLTree<Object>::operator=(AVLTree&& rhs) noexcept
{
	makeEmpty(root);
	this->root = rhs.clone(rhs.root);
	return *this;
}

template<typename Object>
inline void AVLTree<Object>::insert(const Object& x, AVLNode<Object>*& t)
{
	if (t == nullptr)
		t = new AVLNode<Object>{ x };
	else 
		(x < t->element) ? insert(x, t->left) : insert(x, t->right);
	balance(t);
}

template<typename Object>
inline void AVLTree<Object>::insert(Object&& x, AVLNode<Object>*& t)
{
	if (t == nullptr)
		t = new AVLNode<Object>{ std::move(x) };
	else
		(x < t->element) ? insert(std::move(x), t->left) : insert(std::move(x), t->right);
	balance(t);
}

template<typename Object>
inline void AVLTree<Object>::remove(const Object& x, AVLNode<Object>*& t)
{
	if (t == nullptr)
		return;
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		AVLNode<Object>* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
	balance(t);
}

template<typename Object>
inline void AVLTree<Object>::makeEmpty(AVLNode<Object>*& t)
{
	if (t == nullptr)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = nullptr;
}

template<typename Object>
inline void AVLTree<Object>::balance(AVLNode<Object>*& t)
{
	if (t == nullptr)
		return;
	if (getHeight(t->left) - getHeight(t->right) > ALLOWED_IMBALANCE_FACTOR) {
		(getHeight(t->left->left) >= getHeight(t->left->right))
			? rotateWithLeftChild(t)
			: doubleWithLeftChild(t);
	}
	else if (getHeight(t->right) - getHeight(t->left) > ALLOWED_IMBALANCE_FACTOR) {
		(getHeight(t->right->right) >= getHeight(t->right->left))
			? rotateWithRightChild(t)
			: doubleWithRightChild(t);
	}
	t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
}

template<typename Object>
inline void AVLTree<Object>::rotateWithLeftChild(AVLNode<Object>*& k2)
{
	AVLNode<Object>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(getHeight(k2->left), getHeight(k2->right)) + 1;
	k1->height = std::max(getHeight(k1->left), k2->height) + 1;
	k2 = k1;
}

template<typename Object>
inline void AVLTree<Object>::rotateWithRightChild(AVLNode<Object>*& k1)
{
	AVLNode<Object>* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = std::max(getHeight(k1->left), getHeight(k1->right)) + 1;
	k2->height = std::max(getHeight(k2->right), k1->height) + 1;
	k1 = k2;
}

template<typename Object>
inline void AVLTree<Object>::doubleWithLeftChild(AVLNode<Object>*& k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template<typename Object>
inline void AVLTree<Object>::doubleWithRightChild(AVLNode<Object>*& k1)
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template<typename Object>
inline void AVLTree<Object>::printTree(std::ostream& out, AVLNode<Object>* t, int depth) const
{
	//pre-order traversal
	if (t == nullptr)
		return;
	for (int i = 0; i < depth; i++)
		out << ' ';
	out << t->element << '\n';
	printTree(out, t->left, depth + 1);
	printTree(out, t->right, depth + 1);
}

template<typename Object>
inline AVLTree<Object>* AVLTree<Object>::clone(AVLNode<Object>* t) const
{
	return (t == nullptr)
		? nullptr
		: new AVLNode<Object>{ t->element, clone(t->left), clone(t->right) };
}
