#pragma once
#include <iostream>

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
	const Object findMin() { return findMin(root)->element; };
	const Object findMax() { return findMax(root)->element; };
	friend std::ostream& operator<<(std::ostream& out, const BSTree& t) {
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
	BinaryNode* findMin(BinaryNode* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->left != nullptr)
			t = t->left;
		return t;
	}
	BinaryNode* findMax(BinaryNode* t) const {
		if (t == nullptr)
			return nullptr;
		while (t->right != nullptr)
			t = t->right;
		return t;
	}
};

template<typename Object>
inline void BSTree<Object>::insert(const Object& x, BinaryNode*& t)
{
	if (t == nullptr)
		t = new BinaryNode{ x, nullptr, nullptr };
	else
		(x < t->element) ? insert(x, t->left) : insert(x, t->right);
}

template<typename Object>
inline void BSTree<Object>::insert(Object&& x, BinaryNode*& t)
{
	if (t == nullptr)
		t = new BinaryNode{ std::move(x), nullptr, nullptr };
	else
		(x < t->element) ? insert(std::move(x), t->left) : insert(std::move(x), t->right);
}

template<typename Object>
inline void BSTree<Object>::remove(const Object& x, BinaryNode*& t)
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
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename Object>
inline bool BSTree<Object>::contains(const Object& x, BinaryNode* t) const
{
	if (t == nullptr)
		return false;
	if (t->element == x)
		return true;
	return (x < t->element) ? contains(x, t->left) : contains(x, t->right);
}

template<typename Object>
inline void BSTree<Object>::makeEmpty(BinaryNode*& t)
{
	if (t == nullptr)
		return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t = nullptr;
}

template<typename Object>
inline void BSTree<Object>::printTree(std::ostream& out, BinaryNode* t, int depth) const
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
inline typename BSTree<Object>::BinaryNode* BSTree<Object>::clone(BinaryNode* t) const
{
	return (t == nullptr)
		? nullptr
		: new BinaryNode{ t->element, clone(t->left), clone(t->right) };
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
