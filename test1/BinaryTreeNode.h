#pragma once

#include <utility>

template<typename Object>
struct BinaryTreeNode {
	Object element;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	explicit BinaryTreeNode(const Object& obj, BinaryTreeNode* l = nullptr, BinaryTreeNode* r = nullptr) 
		: element(obj), left(l), right(r) {};
	explicit BinaryTreeNode(Object&& obj, BinaryTreeNode* l = nullptr, BinaryTreeNode* r = nullptr) 
		: element(std::move(obj)), left(l), right(r) {};
};