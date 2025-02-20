#pragma once

template<typename Object>
struct AVLNode {
	Object element;
	AVLNode* left;
	AVLNode* right;
	int height;
	explicit AVLNode(const Object& e, AVLNode* l = nullptr, AVLNode* r = nullptr, int h = 0)
		: element(e), left(l), right(r), height(h) {};
	explicit AVLNode(Object&& e, AVLNode* l = nullptr, AVLNode* r = nullptr, int h = 0)
		: element(e), left(l), right(r), height(h) {};
};