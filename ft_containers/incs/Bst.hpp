#ifndef __BST__H__
#define __BST__H__
#include <iostream>
#include "BstNode.hpp"

template <class T>
class Bst
{
	private :
		BstNode<T> *start;

	public :
		Bst<T>()
		{

		}
		Bst<T>(const Bst &bst)
		{

		}
		~Bst<T>()
		{

		}

		Bst &operator=(const Bst &bst)
		{

		}
};

#endif  //!__BST__H__