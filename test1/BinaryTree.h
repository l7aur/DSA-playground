#pragma once
#include <iostream>
#include <utility>

template<typename Object>
class BinaryTree {
public:
	BinaryTree() : root(nullptr) {};
	~BinaryTree() { clear(); };
	BinaryTree(const Object& rhs) noexcept : root(nullptr) { clone(rhs.root); };
	BinaryTree& operator=(const BinaryTree& rhs) noexcept;
	BinaryTree(Object&& rhs) noexcept : root(nullptr) { clone(std::move(rhs.root)); }
	BinaryTree& operator=(BinaryTree&& rhs) noexcept;
	bool contains(const Object& x) const { return contains(x, root); };
	bool isEmpty() const { return root == nullptr; }
	void clear() { makeEmpty(root); }
	void insert(const Object& x) { insert(x, root); }
	void insert(Object&& x) { insert(std::move(x), root); }
	void remove(const Object& x) { remove(x, root); }
	const struct BinaryNode* getRoot() const { return root; }
	friend std::ostream& operator<<(std::ostream& out, const BinaryTree& t) {
		t.printTree(out, t.root);
		return out;
	}
private:
	struct BinaryNode {
		Object element;
		BinaryNode* left, * right;
		BinaryNode(const Object& x, BinaryNode* l, BinaryNode* r) 
			: element(x), left(l), right(r) {}
		BinaryNode(Object&& x, BinaryNode* l, BinaryNode* r)
			: element(std::move(x)), left(l), right(r) {}
	};

	BinaryNode* root;

	void insert(const Object& x, BinaryNode*& t);
	void insert(Object&& x, BinaryNode*& t);
	void remove(const Object& x, BinaryNode*& t);
	bool contains(const Object& x, BinaryNode* t) const;
	void makeEmpty(BinaryNode*& t);
	void printTree(std::ostream& out, BinaryNode* t, int depth = 0) const;
	BinaryNode* clone(BinaryNode* t) const;
	std::pair<BinaryNode*, BinaryNode*> findRandomLeafandItsParent(BinaryNode* t);
};

template<typename Object>
inline void BinaryTree<Object>::insert(const Object& x, BinaryNode*& t)
{
	if (t == nullptr)
		t = new BinaryNode{ x, nullptr, nullptr };
	(rand() % 2 == 0)
		? insert(x, t->left)
		: insert(x, t->right);
}

template<typename Object>
inline void BinaryTree<Object>::insert(Object&& x, BinaryNode*& t)
{
	if (t == nullptr)
		t = new BinaryNode{ std::move(x), nullptr, nullptr };
	else
		(rand() % 2 == 0) ? insert(std::move(x), t->left) : insert(std::move(x), t->right);
}

template<typename Object>
inline void BinaryTree<Object>::remove(const Object& x, BinaryNode*& t)
{
	if (t == nullptr)
		return;
	if (t->element == x) {
		BinaryNode* oldNode = t;
		std::pair<BinaryNode*, BinaryNode*> p = findRandomLeafandItsParent(t);
		if (p.second != nullptr) {
			(p.second->left == p.first)
				? p.second->left == nullptr
				: p.second->right = nullptr;
			std::swap(p.first->left, oldNode->left);
			std::swap(p.first->right, oldNode->right);
		}
		delete oldNode;
	}
	else {
		remove(x, t->left);
		remove(x, t->right);
	}
}

template<typename Object>
inline bool BinaryTree<Object>::contains(const Object& x, BinaryNode* t) const
{
	if (t == nullptr)
		return false;
	if (t->element == x)
		return true;
	return contains(x, t->left) || contains(x, t->right);
}

template<typename Object>
inline void BinaryTree<Object>::makeEmpty(BinaryNode*& t)
{
	if (t == nullptr)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = nullptr;
}

template<typename Object>
inline void BinaryTree<Object>::printTree(std::ostream& out, BinaryNode* t, int depth) const
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
inline typename BinaryTree<Object>::BinaryNode* BinaryTree<Object>::clone(BinaryNode* t) const
{
	return (t == nullptr)
		? nullptr
		: new BinaryNode{ t->element, clone(t->left), clone(t->right) };
}

template<typename Object>
inline std::pair<typename BinaryTree<Object>::BinaryNode*, typename BinaryTree<Object>::BinaryNode*> BinaryTree<Object>::findRandomLeafandItsParent(BinaryNode* t)
{
	BinaryNode* p = nullptr;
	while (1) {
		if (t->left == nullptr && t->right == nullptr)
			return { t, p };
		p = t;
		if (t->left != nullptr && t->right != nullptr)
			t = (rand() % 2) ? t->left : t->right;
		else if (t->left == nullptr && t->right != nullptr)
			t = t->right;
		else
			t = t->left;
	}
	return { t, p };
}

template<typename Object>
inline BinaryTree<Object>& BinaryTree<Object>::operator=(const BinaryTree& rhs) noexcept
{
	BinaryTree<Object> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template<typename Object>
inline BinaryTree<Object>& BinaryTree<Object>::operator=(BinaryTree&& rhs) noexcept
{
	std::swap(root, rhs.root);
	return *this;
}
