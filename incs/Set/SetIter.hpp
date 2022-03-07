#ifndef __SET_ITER__H
#define __SET_ITER__H
#include "main.hpp"
#include "SetUtils.hpp"

//custom iterator class requirements:(https://www.cplusplus.com/forum/general/225835/)
//no operator [] bcause og dont have
template <typename K, typename Pointer, typename Reference>
	class SetIter
	{
		protected :
			RBTNode<K>*										ptr;

		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef K										value_type;
			typedef K&										reference;
			typedef K const &								const_reference;
			typedef RBTNode<K>*								pointer;
			typedef SetIter<K, Pointer, Reference>			curr_class;
			typedef SetIter<K, K*, K&>						iterator;
			typedef	std::bidirectional_iterator_tag			iterator_category;

			//constructors 
			SetIter(void) : ptr(0){}
			~SetIter(void){}
			SetIter(const pointer ptr): ptr(ptr) {}
			SetIter(const iterator &other): ptr(other.ptr){}

			//operators
			SetIter &operator=(const iterator &iter)
			{
				ptr = iter.node();
				return *this;
			}
			reference operator* () { return ptr->value ; }
			const_reference operator* () const { return ptr->value ; }
			value_type *operator-> () { return &ptr->value ; }
			const_reference operator-> () const { return &ptr->value ; }
			bool operator== ( const curr_class& that ) const { return ptr == that.node() ; }
			bool operator!= ( const curr_class& that ) const { return ptr != that.node() ; }
			bool operator>= ( const curr_class& that ) const { return ptr >= that.node() ; }
			bool operator<= ( const curr_class& that ) const { return ptr <= that.node() ; }
			bool operator< ( const curr_class& that ) const { return ptr < that.node() ; }
			bool operator> ( const curr_class& that ) const { return ptr > that.node() ; }
			SetIter &operator+=(int value)
			{
				int i;

				i = -1;
				while (++i < value)
					this->ptr = ptr_next(ptr);
				return (*this);
			}
			SetIter &operator-=(int value)
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

template <typename K, typename Pointer, typename Reference>
	class ReverseSetIter
	{
		protected :
			RBTNode<K>*										ptr;

		public :
			//type defs follow https://www.cplusplus.com/forum/general/225835/
			typedef K												value_type;
			typedef K&												reference;
			typedef K const &								const_reference;
			typedef RBTNode<K>*										pointer;
			typedef ReverseSetIter<K, Pointer, Reference>			curr_class;
			typedef ReverseSetIter<K, K*, K&>						iterator;
			typedef	std::bidirectional_iterator_tag			iterator_category;


			//constructors 
			ReverseSetIter(void) : ptr(0){}
			~ReverseSetIter(void){}
			ReverseSetIter(const pointer ptr): ptr(ptr) {}
			ReverseSetIter(const iterator &iter){*this = iter;}

			//operators
			ReverseSetIter &operator=(const iterator &iter)
			{
				ptr = iter.node();
				return *this;
			}
			reference operator* () { return ptr->value ; }
			const_reference operator* () const { return ptr->value ; }
			value_type *operator-> () { return &ptr->value ; }
			const_reference operator-> () const { return &ptr->value ; }
			bool operator== ( const curr_class& that ) const { return ptr == that.node() ; }
			bool operator!= ( const curr_class& that ) const { return ptr != that.node() ; }
			bool operator>= ( const curr_class& that ) const { return ptr >= that.node() ; }
			bool operator<= ( const curr_class& that ) const { return ptr <= that.node() ; }
			bool operator< ( const curr_class& that ) const { return ptr < that.node() ; }
			bool operator> ( const curr_class& that ) const { return ptr > that.node() ; }
			ReverseSetIter &operator+=(int value)
			{
				int i;

				i = -1;
				while (++i < value)
					this->ptr = ptr_prev(ptr);
				return (*this);
			}
			ReverseSetIter &operator-=(int value)
			{
				int i;

				i = -1;
				while (++i < value)
					this->ptr = ptr_next(ptr);
				return (*this);
			}
			curr_class &operator++ () { ptr = ptr_prev(ptr) ; return *this ; }
			curr_class &operator-- () { ptr = ptr_next(ptr) ; return *this ; }
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

#endif  //!__SET_ITER__H