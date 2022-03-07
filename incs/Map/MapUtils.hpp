#ifndef __MAPUTILS__H__
#define __MAPUTILS__H__
#include <main.hpp>
#include "Utils.hpp"

//BST node
template <class Key, class T>
struct BSTNode
{
	BSTNode *left;
	BSTNode *right;
	BSTNode *parent;
	ft::pair<Key, T> pair;
	bool is_end; //need extra end node for iter?
};

#endif  //!__MAPUTILS__H__