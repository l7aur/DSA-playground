#pragma once

#include <iostream>
#include "BinaryTreeNode.h"

template<typename Object>
class BSTree {
public:
	BSTree() : root(nullptr) {};
	~BSTree() { clear(); };
	BSTree(const BSTree<Object>& rhs) noexcept : root(nullptr) { clone(rhs.root); };
	BSTree& operator=(const BSTree& rhs) noexcept;
	BSTree(BSTree<Object>&& rhs) noexcept : root(nullptr) { clone(std::move(rhs.root)); }
	BSTree& operator=(BSTree&& rhs) noexcept;
	
	bool contains(const Object& x) const { return contains(x, root); };
	bool isEmpty() const { return root == nullptr; }
	void clear() { makeEmpty(root); }
	void insert(const Object& x) { insert(x, root); }
	void insert(Object&& x) { insert(std::move(x), root); }
	void remove(const Object& x) { remove(x, root); }
	const Object findMin() const { return findMin(root)->element; };
	const Object findMax() const { return findMax(root)->element; };
	friend std::ostream& operator<<(std::ostream& out, const BSTree& t) {
		t.printTree(out, t.root);
		return out;
	}
private:

	BinaryTreeNode<Object>* root;

	void insert(const Object& x, BinaryTreeNode<Object>*& t);
	void insert(Object&& x, BinaryTreeNode<Object>*& t);
	void remove(const Object& x, BinaryTreeNode<Object>*& t);
	bool contains(const Object& x, BinaryTreeNode<Object>* t) const;
	void makeEmpty(BinaryTreeNode<Object>*& t);
	void printTree(std::ostream& out, BinaryTreeNode<Object>* t, int depth = 0) const;
	BinaryTreeNode<Object>* clone(BinaryTreeNode<Object>* t) const;
	BinaryTreeNode<Object>* findMin(BinaryTreeNode<Object>* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->left != nullptr)
			t = t->left;
		return t;
	}
	BinaryTreeNode<Object>* findMax(BinaryTreeNode<Object>* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->right != nullptr)
			t = t->right;
		return t;
	}
};

template<typename Object>
inline void BSTree<Object>::insert(const Object& x, BinaryTreeNode<Object>*& t)
{
	if (t == nullptr)
		t = new BinaryTreeNode<Object>{ x };
	else
		(x < t->element) ? insert(x, t->left) : insert(x, t->right);
}

template<typename Object>
inline void BSTree<Object>::insert(Object&& x, BinaryTreeNode<Object>*& t)
{
	if (t == nullptr)
		t = new BinaryTreeNode<Object>{ std::move(x) };
	else
		(x < t->element) ? insert(std::move(x), t->left) : insert(std::move(x), t->right);
}

template<typename Object>
inline void BSTree<Object>::remove(const Object& x, BinaryTreeNode<Object>*& t)
{
	if (t == nullptr)
		return;
	if (t->element > x)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if(t->left != nullptr && t->right != nullptr) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		BinaryTreeNode<Object>* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename Object>
inline bool BSTree<Object>::contains(const Object& x, BinaryTreeNode<Object>* t) const
{
	if (t == nullptr)
		return false;
	if (t->element == x)
		return true;
	return (x < t->element) ? contains(x, t->left) : contains(x, t->right);
}

template<typename Object>
inline void BSTree<Object>::makeEmpty(BinaryTreeNode<Object>*& t)
{
	if (t == nullptr)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = nullptr;
}

template<typename Object>
inline void BSTree<Object>::printTree(std::ostream& out, BinaryTreeNode<Object>* t, int depth) const
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
inline typename BinaryTreeNode<Object>* BSTree<Object>::clone(BinaryTreeNode<Object>* t) const
{
	return (t == nullptr)
		? nullptr
		: new BinaryTreeNode<Object>{ t->element, clone(t->left), clone(t->right) };
}

template<typename Object>
inline BSTree<Object>& BSTree<Object>::operator=(const BSTree& rhs) noexcept
{
	makeEmpty(root);
	this->root = rhs.clone(rhs.root);
	return *this;
}

template<typename Object>
inline BSTree<Object>& BSTree<Object>::operator=(BSTree&& rhs) noexcept
{
	makeEmpty(root);
	this->root = rhs.clone(rhs.root);
	return *this;
}
