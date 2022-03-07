#ifndef __MAP_ITER__H
#define __MAP_ITER__H
#include "main.hpp"
#include "MapUtils.hpp"

//custom iterator class requirements:(https://www.cplusplus.com/forum/general/225835/)
template <typename K, typename T, typename Pointer, typename Reference>
	class MapIter
	{
		protected :
			BSTNode<K, T>*	ptr;

		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef ft::pair<K, T>							value_type;
			typedef ft::pair<K, T>&							reference;
			typedef ft::pair<K, T> const &					const_reference;
			typedef BSTNode<K, T>*							pointer;
			typedef MapIter<K, T, Pointer, Reference>		curr_class;
			typedef MapIter<K, T, T*, T&>					iterator;
			typedef	std::bidirectional_iterator_tag			iterator_category;

			//constructors 
			MapIter(void) : ptr(0){}
			~MapIter(void){}
			MapIter(const pointer ptr): ptr(ptr) {}
			MapIter(const iterator &other): ptr(other.ptr){}

			//operators
			MapIter &operator=(const iterator &iter)
			{
				ptr = iter.node();
				return *this;
			}
			reference operator* () { return ptr->pair ; }
			const_reference operator* () const { return ptr->pair ; }
			value_type *operator-> () { return &ptr->pair ; }
			const_reference operator-> () const { return &ptr->pair ; }
			bool operator== ( const curr_class& that ) const { return ptr == that.node() ; }
			bool operator!= ( const curr_class& that ) const { return ptr != that.node() ; }
			bool operator>= ( const curr_class& that ) const { return ptr >= that.node() ; }
			bool operator<= ( const curr_class& that ) const { return ptr <= that.node() ; }
			bool operator< ( const curr_class& that ) const { return ptr < that.node() ; }
			bool operator> ( const curr_class& that ) const { return ptr > that.node() ; }
			MapIter &operator+=(int value)
			{
				int i;

				i = -1;
				while (++i < value)
					this->ptr = ptr_next(ptr);
				return (*this);
			}
			MapIter &operator-=(int value)
			{
				int i;

				i = -1;
				while (++i < value)
					this->ptr = ptr_prev(ptr);
				return (*this);
			}
			curr_class &operator++ () { ptr = ptr_next(ptr) ; return *this ; }
			curr_class &operator-- () { ptr = ptr_prev(ptr) ; return *this ; }
			curr_class operator++ (int) { curr_class temp(*this) ; this->operator++() ; return temp ; }
			curr_class operator-- (int) { curr_class temp(*this) ; this->operator--() ; return temp ; }

			//mem funcs
			pointer node(void) const { return (ptr);}

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
		protected :
			BSTNode<K, T>*	ptr;

		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef ft::pair<K, T>								value_type;
			typedef ft::pair<K, T>&								reference;
			typedef ft::pair<K, T> const &						const_reference;
			typedef BSTNode<K, T>*								pointer;
			typedef ReverseMapIter<K, T, Pointer, Reference>	curr_class;
			typedef ReverseMapIter<K, T, T*, T&>				iterator;
			typedef	std::bidirectional_iterator_tag				iterator_category;

			//constructors 
			ReverseMapIter(void) : ptr(0){}
			~ReverseMapIter(void){}
			ReverseMapIter(const pointer ptr): ptr(ptr) {}
			ReverseMapIter(const iterator &iter){*this = iter;}

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

			//mem funcs
			pointer node(void) { return (ptr);}

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
				pointer	original;

				if (!ptr->left)
				{
					res = ptr;
					original = ptr;
					while (res->parent && res == res->parent->left)
						res = res->parent;
					original = res;
					res = res->parent;
					if (!res)
					{
						res = this->ptr_next(original);
						while (!res->is_end)
						{
							original = res;
							res = this->ptr_next(original);
						}
						return original;
					}
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