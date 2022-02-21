#ifndef __SETUTILS__H__
#define __SETUTILS__H__
#define BLACK_RBT 0
#define RED_RBT 1
#include <main.hpp>
#include "Utils.hpp"

//RBT node
template <class T>
struct RBTNode
{
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
	T		value;
	bool	color;
	bool 	is_end; //need extra end node for iter?
};

//‘RBTNode<std::__cxx11::basic_string<char>, ft::pair<const std::__cxx11::basic_string<char>, int> >*’
// ‘RBTNode<std::__cxx11::basic_string<char>, int>*’

#endif  //!__SETUTILS__H__