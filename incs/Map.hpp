#ifndef __MAP__H
#define __MAP__H
#include "main.hpp"
#include "MapIter.hpp"
#include "MapUtils.hpp"

namespace ft
{
	//helper function to swap refernce between 2 elems
	template <typename T>
	void	swap(T &a, T&b)
	{
		T	temp;

		temp = a;
		a = b;
		b = temp;
	}

	// Class std::Map wrapper with performance instrumentation.
	// Refer for c++ map reference (https://en.cppreference.com/w/cpp/container/map)
	// Refer for c++ map source code (https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/stl__map_8h-source.html)
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class Map
	{
		//Member types & functions
		public :
			//typedefs (refer to sourcecode)
			typedef Key										key_type;
			typedef	T										mapped_type;
			typedef	ft::pair<const key_type, mapped_type>	value_type;
			typedef	Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef T& 										reference;
			typedef const T& 								const_reference;
			typedef T*										pointer;
			typedef	const	T*								const_pointer;
			typedef size_t									size_type;
			typedef BSTNode<key_type, mapped_type>			*node;
			typedef MapIter<key_type, mapped_type, pointer, reference>						iterator;
			typedef ReverseMapIter<key_type, mapped_type, pointer, reference>				reverse_iterator;
			typedef MapIter<key_type, mapped_type, const_pointer, const_reference>			const_iterator;
			typedef ReverseMapIter<key_type, mapped_type, const_pointer, const_reference>	const_reverse_iterator;

			//binary function for C++98 implementation
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class Map<Key, T, Compare, Allocator>;
				protected : 
					Compare cmp; // compare is the maps compare object
					value_compare (Compare c) : cmp(c) {}
				public :
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& left, const value_type& right) const
					{
						return comp(left.first, right.first);
					}
			};

			//helpers and attributes
			private :
				allocator_type	_allocator;
				node			_root;
				key_compare		_compare;
				size_type		_len;

				//node _new_node(key_type key, mapped_type value, node paren)
				//creates and initializes new node and returns the pointer to that node
				node _new_node(key_type key, mapped_type value, node parent)
				{
					node	res;

					res = new BSTNode<key_type, value_type>();
					res.pair = ft::make_pair(key, value);
					res.left = 0;
					res.right = 0;
					res.parent = parent;

					return res;
				}

				//void	free_tree(node n);
				void	_free_tree(node n)
				{
					if (n->left)
						_free_tree(n->left);
					if (n->right)
						_free_tree(n->right);
					delete n;
				}

				//node _insert_node(node n, key_type key, mapped_type value)
				//insert node n into bst (n is not null)
				//base case: check if node is leaf . If it is, add to left or right subtree
				//recurse left if value is smaller than curr node
				//vice versa if larger
				node _insert_node(node n, key_type key, mapped_type value)
				{
					if (!n->left && !n->right)
					{
						if (key < n->pair.first)
						{
							n->left = _new_node(key, value, n);
							return n->left;
						}
						else
						{
							n->right = _new_node(key, value, n);
							return n->right;							
						}
					}
					if (key < n->pair.first)
					{
						if (n->left)
							return _insert_node(n->left, key, value);
						else
							n->left = _new_node(key, value, n);
						return n->left;
					}
					if (key > n->pair.first)
					{
						if (n->right)
							return _insert_node(n->right, key, value);
						else
							n->right = _new_node(key, value, n);
						return n->right;						
					}
				}

				//node _find(node n, key_type key) const
				//if curr nodes key is equal to key, return curr node (base case)
				node _find(node n, key_type key) const
				{
					if (!n || n->pair.first == key)
						return n;
					if (n->right && key > n->pair.first)
						return _find(n->right, key);
					if (n->left && key < n->pair.first)
						return _find(n->left, key);
					return 0;
				}

				//void _delete_node(node n)
				//case 1. Node is leaf - remove node
				//case 2. Node has 1 child - copy child node and delete child
				//case 3. Node has 2 children. Find inorder predeseccor, swap and delete successor
				void _delete_node(node n)
				{
					node	successor;

					if (!n->left && !n->right)
					{
						if (n->parent->left == n)
							n->parent->left = 0;
						else if (n->parent->right == n)
							n->parent->right = 0;
					}
					else if (!n->left && n->right)
					{
						successor = n->right;
						if (n->parent->left == n)
							n->parent->left = successor;
						else if (n->parent->right == n)
							n->parent->right = successor;
					}
					else if (n->left && !n->right)
					{
						successor = n->left;
						if (n->parent->left == n)
							n->parent->left = successor;
						else if (n->parent->right == n)
							n->parent->right = successor;
					}
					else
					{
						successor = (++iterator(n)).node();
						if (!successor)
							successor = (--iterator(n)).node();
						ft::swap(successor->pair, n->pair);
						_delete_node(successor);
						return ;
					}

					delete n;
				}

				//void _init_tree(void)
				void _init_tree(void)
				{
					this._root = _new_node(key_type(), mapped_type(), 0);
					this._length = 0;
				}


				//node _end(void) const (?)

			//member functions & access operations
			public :

				//iterators
				iterator	begin();
				iterator	end(){return 0;};

				const_iterator	begin() const;
				const_iterator	end() const {return 0;}

				reverse_iterator	rbegin(){return 0;}
				reverse_iterator	rend();

				const_reverse_iterator	rbegin() const {return 0;}
				const_reverse_iterator	rend() const;

	};

	//Iterator definitions
	template <class Key, class T, class Compare, class Alloc >
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>::begin()
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (iterator(n));
		while (n->left)
			n = n->left;
		return (iterator(n));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>::begin() const
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (iterator(n));
		while (n->left)
			n = n->left;
		return (const_iterator(n));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename Map<Key, T, Compare, Alloc>::reverse_iterator Map<Key, T, Compare, Alloc>::rend()
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (reverse_iterator(n));
		while (n->right)
			n = n->right;
		return (reverse_iterator(n));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename Map<Key, T, Compare, Alloc>::const_reverse_iterator Map<Key, T, Compare, Alloc>::rend() const
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (const_reverse_iterator(n));
		while (n->right)
			n = n->right;
		return (const_reverse_iterator(n));
	}
}//ft

#endif  //!__MAP__H