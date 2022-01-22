#ifndef __MAP_ITER__H
#define __MAP_ITER__H
#include "main.hpp"

//BST node
template <class Key, class T>
struct BSTNode
{
	std::pair<Key, T> pair;
	BSTNode *left;
	BSTNode *right;
	BSTNode *parent;
	bool is_leaf;
};

//custom iterator class requirements:(https://www.cplusplus.com/forum/general/225835/)
template <typename K, typename T, typename Pointer, typename Reference>
	class MapIter
	{
		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef std::pair<K, T>							value_type;
			typedef std::pair<K, T>&						reference;
			typedef BSTNode<K, T>*							pointer;
			typedef MapIter<K, T, Pointer, Reference>		curr_class;
			typedef MapIter<K, T, T*, T&>					iterator;
			pointer	ptr;

			//constructors 
			MapIter(void) : ptr(0){}
			~MapIter(void){}
			MapIter(const pointer ptr): ptr(ptr) {}
			MapIter(const iterator iter){*this = iter;}

			//operators
			MapIter &operator=(const iterator &iter)
			{
				ptr = iter.ptr;
				return *this;
			}
			reference operator* () { return ptr->pair ; }
			value_type *operator-> () { return &ptr->pair ; }
			bool operator== ( const curr_class& that ) const { return ptr == that.ptr ; }
			bool operator!= ( const curr_class& that ) const { return ptr != that.ptr ; }
			curr_class &operator++ () { ptr = ptr_next(ptr) ; return *this ; }
			curr_class &operator-- () { ptr = ptr_prev(ptr) ; return *this ; }
			curr_class operator++ (int) { curr_class temp(*this) ; this->operator++() ; return temp ; }
			curr_class operator-- (int) { curr_class temp(*this) ; this->operator--() ; return temp ; }

		private :
			//in-order traversal to get next node
			pointer	ptr_next(pointer ptr)
			{
				pointer	res;

				if (!ptr->right)
				{
					res = ptr;
					while (res->parent && res == res->parent->right)
						res = res->parent;
					res = res->parent;
				}
				else
				{
					res = ptr->right;
					while(res->left)
						res = res->left;
				}
				return res;
			}

			//in order traversal to get prev node
			pointer ptr_prev(pointer ptr)
			{
				pointer	res;

				if (!ptr->left)
				{
					res = ptr;
					while (res->parent && res == res->parent->left)
						res = res->parent;
					res = res->parent;
				}
				else
				{
					res = ptr->left;
					while(res->right)
						res = res->right;
				}
				return res;
			}

	};

template <typename K, typename T, typename Pointer, typename Reference>
	class ReverseMapIter
	{
		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef std::pair<K, T>							value_type;
			typedef std::pair<K, T>&						reference;
			typedef BSTNode<K, T>*							pointer;
			typedef ReverseMapIter<K, T, Pointer, Reference>		curr_class;
			typedef ReverseMapIter<K, T, T*, T&>					iterator;
			pointer	ptr;

			//constructors 
			ReverseMapIter(void) : ptr(0){}
			~ReverseMapIter(void){}
			ReverseMapIter(const pointer ptr): ptr(ptr) {}
			ReverseMapIter(const iterator iter){*this = iter;}

			//operators
			ReverseMapIter &operator=(const iterator &iter)
			{
				ptr = iter.ptr;
				return *this;
			}
			reference operator* () { return ptr->pair ; }
			value_type *operator-> () { return &ptr->pair ; }
			bool operator== ( const curr_class& that ) const { return ptr == that.ptr ; }
			bool operator!= ( const curr_class& that ) const { return ptr != that.ptr ; }
			curr_class &operator++ () { ptr = ptr_prev(ptr) ; return *this ; }
			curr_class &operator-- () { ptr = ptr_next(ptr) ; return *this ; }
			curr_class operator++ (int) { curr_class temp(*this) ; this->operator++() ; return temp ; }
			curr_class operator-- (int) { curr_class temp(*this) ; this->operator--() ; return temp ; }

		private :
			//in-order traversal to get next node
			pointer	ptr_next(pointer ptr)
			{
				pointer	res;

				if (!ptr->right)
				{
					res = ptr;
					while (res->parent && res == res->parent->right)
						res = res->parent;
					res = res->parent;
				}
				else
				{
					res = ptr->right;
					while(res->left)
						res = res->left;
				}
				return res;
			}

			//in order traversal to get prev node
			pointer ptr_prev(pointer ptr)
			{
				pointer	res;

				if (!ptr->left)
				{
					res = ptr;
					while (res->parent && res == res->parent->left)
						res = res->parent;
					res = res->parent;
				}
				else
				{
					res = ptr->left;
					while(res->right)
						res = res->right;
				}
				return res;
			}

	};

#endif  //!__MAP_ITER__H