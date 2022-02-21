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

//‘BSTNode<std::__cxx11::basic_string<char>, ft::pair<const std::__cxx11::basic_string<char>, int> >*’
// ‘BSTNode<std::__cxx11::basic_string<char>, int>*’

#endif  //!__MAPUTILS__H__