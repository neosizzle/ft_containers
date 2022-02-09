#ifndef __SET__H
#define __SET__H
#include "main.hpp"
#include "SetIter.hpp"
#include "SetUtils.hpp"

namespace ft
{

	// Class std::Set wrapper with performance instrumentation.
	// Refer for c++ Set reference (https://en.cppreference.com/w/cpp/container/Set)
	// Refer for c++ Set source code (https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/stl__Set_8h-source.html)
	template <class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key>
	>
	class Set
	{
		//Member types & functions
		public :
			//typedefs (refer to sourcecode)
			typedef Key															key_type;
			typedef	Key															value_type;
			typedef	Compare														key_compare;
			typedef size_t														size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef Allocator													allocator_type;
			typedef Key& 														reference;
			typedef const Key& 													const_reference;
			typedef Key*														pointer;
			typedef	const	Key*												const_pointer;
			typedef RBTNode<key_type>											*node;
			typedef SetIter<key_type, pointer, reference>						iterator;
			typedef ReverseSetIter<key_type, pointer, reference>				reverse_iterator;
			typedef SetIter<key_type, const_pointer, const_reference>			const_iterator;
			typedef ReverseSetIter<key_type, const_pointer, const_reference>	const_reverse_iterator;

			//binary function for C++98 implementation
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class Set<Key, Compare, Allocator>;
				protected : 
					Compare cmp; // compare is the Sets compare object
					value_compare (Compare c) : cmp(c) {}
				public :
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& left, const value_type& right) const
					{
						return comp(left, right);
					}
			};

		//helpers and attributes
		private :
			allocator_type	_allocator;
			node			_root;
			key_compare		_compare;
			size_type		_len;
			bool			_ll_case;//left consecutive nodes in a straight line
			bool			_lr_case;//left consecutive nodes in a triangle
			bool			_rr_case;//mirrored llcase
			bool			_rl_case;//mirrored lrcase

			//node _new_node(key_type key, Setped_type value, node paren)
			//creates and initializes new node and returns the pointer to that node
			node _new_node(key_type key, value_type value, node parent, bool is_end = false, bool color = RED_RBT)
			{
				node	res;

				(void) key;
				res = new RBTNode<key_type>();
				res->value = value;
				res->left = 0;
				res->right = 0;
				res->parent = parent;
				res->is_end = is_end;
				res->color = color;

				return res;
			}

			//find sibling of given node
			node	_get_sibling(node n)
			{
				if (!n || !n->parent)
					return 0;
				else if (n == n->parent->left)
					return n->parent->right;
				else
					return n->parent->left;
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

			//performs left rotation on a given node
			node	_rotate_left(node n)
			{
				node pivot;
				node child;

				pivot = n->right;
				child = pivot->left;
				pivot->left = n;
				n->right = child;
				n->parent = pivot;
				if (child)
					child->parent = n;
				return pivot;
			}

			//performs right rotation on a given node
			node	_rotate_right(node n)
			{
				node pivot;
				node child;

				pivot = n->left;
				child = pivot->right;
				pivot->right = n;
				n->left = child;
				n->parent = pivot;
				if (child)
					child->parent = n;
				return pivot;
			}
			//node _insert_node(node n, key_type key, Setped_type value)
			//insert node n into bst (n is not null)
			//base case: check if node is leaf . If it is, add to left or right subtree
			//recurse left if value is smaller than curr node
			//vice versa if larger
			node _insert_node(node n, key_type key, value_type value, bool is_end = false, bool color = RED_RBT)
			{
				bool	conflict;//true if there is red red violation

				if (!n)
				{
					return (_new_node(key, value, 0, is_end, color));
				}
				else if (n->is_end)
				{
					n->is_end = false;
					n->right = _new_node(key_type(), value_type(), n, true, BLACK_RBT);
					n->value = value;
					n->color = RED_RBT;
					return (n);
				}
				else if (key < n->value)
				{
					n->left = _insert_node(n->left, key, value);
					n->left->parent = n;
					if (n != this->_root)
					{
						if (n->color == RED_RBT && n->left->color == RED_RBT)
							conflict = true;
					}
				}
				else if (key > n->value)
				{
					n->right = _insert_node(n->right, key, value);
					n->right->parent = n;
					if (n != this->_root)
					{
						if (n->color == RED_RBT && n->right->color == RED_RBT)
							conflict = true;
					}					
				}

				//move nodes according to case
				if (this->_ll_case)
				{
					n = _rotate_left(n);
					n->color = BLACK_RBT;
					n->left->color = RED_RBT;
					this->_ll_case = false;
				}
				else if (this->_rr_case)
				{
					n = _rotate_right(n);
					n->color = BLACK_RBT;
					n->right->color = RED_RBT;
					this->_rr_case = false;
				}
				else if (this->_rl_case)
				{
					n->right = _rotate_right(n->right);
					n->right->parent = n;
					n = _rotate_left(n);
					n->color = BLACK_RBT;
					n->left->color = RED_RBT;
					this->_rl_case = false;
				}
				else if (this->_lr_case)
				{
					n->left = _rotate_left(n->left);
					n->left->parent = n;
					n = _rotate_right(n);
					n->color = BLACK_RBT;
					n->right->color = RED_RBT;
					this->_rl_case = false;
				}

				//if conflicts exists, turn on specific flags or the 
				//backtrack to execute
				// if (conflict)
				// {
				// 	//if current node is a right child
				// 	if (n->parent->right == n)
				// 	{
				// 		//no sibling or black sibling
				// 		if (!n->parent->left || n->parent->left->color == BLACK_RBT) 
				// 		{
				// 			if (!n->left && n->left->color == RED_RBT) // left child is red
				// 				this->_rl_case = true;
				// 			else if (!n->right && n->right->color == RED_RBT) // right child is red
				// 				this->_ll_case = true;
				// 		}
				// 		else
				// 		//red sibling
				// 		{
				// 			n->parent->left->color = BLACK_RBT;
				// 			n->color = BLACK_RBT;
				// 			if (n->parent != this->_root)
				// 				n->parent->color = RED_RBT;
				// 		}
				// 	}
				// 	//current node is left child
				// 	else
				// 	{
				// 		//no sibling or black sibling
				// 		if (!n->parent->right || n->parent->right->color == BLACK_RBT) 
				// 		{
				// 			if (!n->right && n->right->color == RED_RBT) // left child is red
				// 				this->_lr_case = true;
				// 			else if (!n->left && n->left->color == RED_RBT)// right child is red
				// 				this->_rr_case = true;
				// 		}
				// 		//red sibling
				// 		else
				// 		{
				// 			n->parent->right->color = BLACK_RBT;
				// 			n->color = BLACK_RBT;
				// 			if (n->parent != this->_root)
				// 				n->parent->color = RED_RBT;
				// 		}
						
				// 	}
					
				// }
				// conflict = false;
				return n;
			}

			//node _find(node n, key_type key) const
			//if curr nodes key is equal to key, return curr node (base case)
			node _find(node n, key_type key) const
			{
				if (!n->is_end && n->value == key)
					return n;
				if (n->right && key > n->value)
					return _find(n->right, key);
				if (n->left && key < n->value)
					return _find(n->left, key);
				return this->_end();
			}

			//find replace, will find the replacement node where n is node to delete
			//case 1: node has 2 children - return inorder successor
			//case 2: node is leaf - return null
			//case 3: node has 1 child - return that child
			node	_find_replace_del(node n)
			{
				iterator	iter;

				if (n->left && n->right)
				{
					iter = iterator(n);
					return ++iter;
				}
				else if (!n->left && !n->right)
					return 0;
				else
				{
					if (n->left)
						return n->left;
					else
						return n->right;
				}
			}

			// fixes double black cases
			// ignore root node
			void	_fix_double_black(node n)
			{
				Node	sibling;
				Node	parent;

				if (n == this->_root)
					return ;
				sibling = this->_get_sibling(n);
				parent = this->parent;

				//no sibling, double black pushed up
				if (!sibling)
					_fix_double_black(parent);
				else
				{
					//red sibling
					if (sibling->color == RED_RBT)
					{
						//recolor
						sibling->color = BLACK_RBT;
						parent->color = RED_RBT;

						//sibling is left child
						if (sibling->parent && (sibling == sibling->parent->left))
							this->_rotate_right(parent);
						else
							this->_rotate_left(parent);
					}

					//black sibling
					else
					{
						//sibling has red child
						if ((sibling->left && sibling->left->color == RED_RBT) ||
							(sibling->right && sibling->right->color == RED_RBT))
						{
							if (sibling->left && sibling->left->color == RED_RBT)
							{
								//sibling is on left
								if (sibling->parent && (sibling == sibling->parent->left))
								{
									//recolor and rotate
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									_rotate_right(parent);
								}

								//sibling is on right
								else
								{
									//recolor and rotate
									sibling->left->color = parent->color;
									_rotate_right(sibling);
									_rotate_left(parent);
								}
							}
							else
							{
								//sibling is on left
								if (sibling->parent && (sibling == sibling->parent->left))
								{
									//recolor and rotate
									sibling->right->color = parent->color;
									_rotate_left(sibling);
									_rotate_rightt(parent);
								}

								//sibling is on right
								else
								{
									//recolor and rotate
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									_rotate_left(parent);
								}
							}
							parent->color = BLACK_RBT;
						}

						//sibling has only black children
						else
						{
							sibling->color = RED_RBT;
							//pass to parent if parent is black
							if (parent->color == BLACK_RBT)
								this->_fix_double_black(parent);
							else
								parent->color == BLACK_RBT
						}
					}
				}
			}

			//void _delete_node(node n)
			//case 1. Node is leaf - remove node
			//case 2. Node has 1 child - copy child node and delete child
			//case 3. Node has 2 children. Find inorder predeseccor, swap and delete successor
			void _delete_node(node n)
			{
				node		successor;

				if (n->is_end)
				{
					if (n->parent && n->parent->is_end)
						delete n;
					return ; 
				}
				else if (n->parent && !n->left && !n->right)
				{
					if (n->parent->left == n)
						n->parent->left = 0;
					else if (n->parent->right == n)
						n->parent->right = 0;
					delete n;
					return ;
				}
				else if (n->parent && !n->left && n->right)
				{
					successor = n->right;
					if (n->parent->left == n)
						n->parent->left = successor;
					else if (n->parent->right == n)
						n->parent->right = successor;
					successor->parent = n->parent;
					delete n;
					return ;
				}
				else if (n->parent && n->left && !n->right)
				{
					successor = n->left;
					if (n->parent->left == n)
						n->parent->left = successor;
					else if (n->parent->right == n)
						n->parent->right = successor;
					successor->parent = n->parent;
					delete n;
					return ;
				}
				successor = (++iterator(n)).node();
				if (successor->is_end)
				{
					// std::cout << "end node found\n";
					n->is_end = true;
					if (n->left)
						successor = (--iterator(n)).node();
					n->left = 0;
					n->right = 0;
				}
				ft::swap(successor->value, n->value);				
				_delete_node(successor);
			}

			//void _init_tree(void)
			void _init_tree(void)
			{
				this->_root = _new_node(key_type(), value_type(), 0, true, RED_RBT);
				this->_len = 0;
			}


			//node _end(void) const
			node _end() const
			{
				node	temp;

				temp = this->_root;
				while (!temp->is_end)
					temp = temp->right;
				
				return (temp);
			}

		//member functions & access operations
		public :
			//Member functions
			explicit Set(const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type());
			Set(Set<Key> &other);
			~Set();
			Set &operator=(Set<Key> &other);
			allocator_type	get_allocator() {return allocator_type();}

			//iterators
			iterator	begin();
			iterator	end(){return (iterator(this->_end()));}

			const_iterator	begin() const;
			const_iterator	end() const {return (const_iterator(this->_end()));}

			reverse_iterator	rbegin();
			reverse_iterator	rend()
			{
				//why the fuck is this not root??
				reverse_iterator	i;

				i = reverse_iterator(this->_root);
				++i;
				return (reverse_iterator(i.node()));
			}

			const_reverse_iterator	rbegin() const;
			const_reverse_iterator	rend() const 
			{
				//why the fuck is this not root??
				reverse_iterator	i;

				i = const_reverse_iterator(this->_root);
				++i;
				return (const_reverse_iterator(i.node()));
			}

			//capacity
			bool empty() const {return (this->_len == 0);}
			size_type size() const {return (this->_len);}
			size_type max_size() const {return (std::numeric_limits<size_type>::max() / (sizeof(RBTNode<key_type>)));}

			//modifiers
			void clear();
			ft::pair<iterator, bool> insert( const value_type& value );
			iterator insert( iterator hint, const value_type& value );
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const Key& key );
			void swap( Set& other );

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
			}

			//lookup
			size_type count( const Key& key ) const;
			iterator find( const Key& key );
			const_iterator find( const Key& key ) const;
			ft::pair<iterator,iterator> equal_range( const Key& key );
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
			iterator lower_bound( const Key& key );
			const_iterator lower_bound( const Key& key ) const;
			iterator upper_bound( const Key& key ); 
			const_iterator upper_bound( const Key& key ) const;

			//comparison operators
			bool operator==( const Set<Key,Compare,Allocator>& rhs );
			bool operator!=( const Set<Key,Compare,Allocator>& rhs );
			bool operator<=( const Set<Key,Compare,Allocator>& rhs );
			bool operator<( const Set<Key,Compare,Allocator>& rhs );
			bool operator>=( const Set<Key,Compare,Allocator>& rhs );
			bool operator>( const Set<Key,Compare,Allocator>& rhs );
	};

	//member function definitions
	template <class Key, class Compare, class Alloc >
	Set<Key, Compare, Alloc>::Set(const key_compare &comp, const allocator_type alloc)
	{
		this->_allocator = alloc;
		this->_compare = comp;
		this->_init_tree();
	}

	template <class Key, class Compare, class Alloc >
	Set<Key, Compare, Alloc>::Set(Set<Key> &other)
	{
		this->_init_tree();
		*this = other;
	}

	template <class Key, class Compare, class Alloc >
	Set<Key, Compare, Alloc>::~Set()
	{
		this->_free_tree(this->_root);
	}


	template <class Key, class Compare, class Alloc >
	Set<Key, Compare, Alloc> &Set<Key, Compare, Alloc>::operator= (Set<Key> &other)
	{	
		this->clear();
		this->insert(other.begin(), other.end());
		return (*this);
	}

	//Iterator definitions
	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::iterator Set<Key, Compare, Alloc>::begin()
	{
		node n = this->_root;
		// std::cout << "curr root in begin : " << n->pair.second << "\n";
		if (!n->left && !n->right)
			return (iterator(n));
		while (n->left)
			n = n->left;
		return (iterator(n));
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::const_iterator Set<Key, Compare, Alloc>::begin() const
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (const_iterator(n));
		while (n->left)
			n = n->left;
		return (const_iterator(n));
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::reverse_iterator Set<Key, Compare, Alloc>::rbegin()
	{
		iterator	iter;

		iter = this->end();
		iter--;
		return (reverse_iterator(iter.node()));
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::const_reverse_iterator Set<Key, Compare, Alloc>::rbegin() const
	{
		iterator	iter;

		iter = this->end();
		iter--;
		return (const_reverse_iterator(iter.node()));	
	}

	//modifiers definitions
	template <class Key, class Compare, class Alloc >
	void Set<Key, Compare, Alloc>::erase(iterator position)
	{
		node	n;
		int		move_root;

		n = position.node();
		move_root = 0;
		if (this->_root == n)
			move_root = 1;
		_delete_node(n);
		if (move_root)
		{
			this->_root = (position).node();
		}
		--this->_len;
	}

	template <class Key, class Compare, class Alloc >
	void Set<Key, Compare, Alloc>::erase(iterator first, iterator last)
	{
		while (first != last)
			this->erase(first);
	}

	template <class Key, class Compare, class Alloc >
	size_t Set<Key, Compare, Alloc>::erase( const Key& key )
	{
		size_type	i;
		iterator	iter;

		i = 0;
		iter = this->find(key);
		while (iter != this->end())
		{
			this->erase(iter);
			++i;
			iter = this->find(key);
		}
		return i;
	}

	template <class Key, class Compare, class Alloc >
	void Set<Key, Compare, Alloc>::clear()
	{
		while (this->begin() != this->end())
			this->erase(this->begin());
		// this->erase(this->begin(), this->end());
	}

	template <class Key, class Compare, class Alloc >
	ft::pair<typename Set<Key, Compare, Alloc>::iterator, bool> Set<Key, Compare, Alloc>::insert( const value_type& value )
	{
		iterator	iter;

		iter = this->find(value);
		if (iter != this->end())
		{
			// std::cout << "dup found insert()\n";
			return (ft::make_pair(iter, false));
		}
		++this->_len;
		// if (this->_len == 1)
		// {
		// 	delete this->_root;
		// 	this->_root = _new_node(value.first, value.second, 0);
		// 	return (ft::make_pair(iterator(this->_root), true));
		// }
		return (ft::make_pair(iterator(this->_insert_node(this->_root, value, value)), true));
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::iterator Set<Key, Compare, Alloc>::insert( iterator hint, const value_type& value )
	{
		iterator	iter;

		iter = this->find(value);
		if (iter != this->end())
			return (iter);
		++this->len;
		return (iterator(this->_insert_node(hint.node(), value, value)));
	}

	template <class Key, class Compare, class Alloc >
	void Set<Key, Compare, Alloc>::swap( Set& other )
	{
		Set<Key, Compare, Alloc> temp = *this;
		*this = other;
		other = temp;
	}

	//lookup definitions
	template <class Key, class Compare, class Alloc >
	size_t Set<Key, Compare, Alloc>::count( const Key& key ) const
	{
		node	found;

		found = _find(this->_root, key);
		if (!found->is_end)
			return 1;
		return 0;
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::iterator  Set<Key, Compare, Alloc>::find( const Key& key )
	{
		node	found;

		if (this->empty())
			return this->end();
		found = _find(this->_root, key);
		return iterator(found);
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::const_iterator Set<Key, Compare, Alloc>::find( const Key& key ) const
	{
		node	found;

		if (this->empty())
			return this->end();
		found = _find(this->_root, key);
		return const_iterator(found);
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::iterator Set<Key, Compare, Alloc>::lower_bound( const Key& key )
	{
		iterator begin;
		iterator end;

		begin = this->begin();
		end = this->end();
		while (begin != end)
		{
			if (this->_compare(*begin, key) <= 0)
				return begin;
			++begin;
		}
		return end;
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::const_iterator Set<Key, Compare, Alloc>::lower_bound( const Key& key ) const
	{
		const_iterator begin;
		const_iterator end;

		begin = this->begin();
		end = this->end();
		while (begin != end)
		{
			if (this->_compare(begin->first, key) <= 0)
				return begin;
			++begin;
		}
		return end;
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::iterator Set<Key, Compare, Alloc>::upper_bound( const Key& key )
	{
		iterator begin;
		iterator end;

		begin = this->begin();
		end = this->end();
		while (begin != end)
		{
			if (*begin != key && this->_compare(*begin, key) <= 0)
				return begin;
			++begin;
		}
		return end;
	}

	template <class Key, class Compare, class Alloc >
	typename Set<Key, Compare, Alloc>::const_iterator Set<Key, Compare, Alloc>::upper_bound( const Key& key ) const
	{
		const_iterator begin;
		const_iterator end;

		begin = this->begin();
		end = this->end();
		while (begin != end)
		{
			if (begin->first != key && this->_compare(begin->first, key) <= 0)
				return begin;
			++begin;
		}
		return end;
	}

	template <class Key, class Compare, class Alloc >
	typename ft::pair<typename Set<Key, Compare, Alloc>::iterator, typename Set<Key, Compare, Alloc>::iterator>
	Set<Key, Compare, Alloc>::equal_range( const Key& key )
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template <class Key, class Compare, class Alloc >
	typename ft::pair<typename Set<Key, Compare, Alloc>::const_iterator, typename Set<Key, Compare, Alloc>::const_iterator>
	Set<Key, Compare, Alloc>::equal_range( const Key& key ) const
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	//comparison operators
	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator==( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		const_iterator first1;
		const_iterator last1;
		const_iterator first2;
		const_iterator last2;

		first1 = this->begin();
		last1 = this->end();
		first2 = rhs.begin();
		last2 = rhs.end();

		while (first1 != last1)
		{
			if ((first2 == last2) || *first1 != *first2) return false ;
			first1++;
			first2++;
		}
		return (first2 == last2);
		return false;
	}

	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator!=( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		return !(*this == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator<( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator<=( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		return (*this < rhs || *this == rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator>( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		return !(*this <= rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool Set<Key, Compare, Alloc>::operator>=( const ft::Set<Key, Compare,Alloc>& rhs )
	{
		return (*this > rhs || *this == rhs);
	}
	
}//ft

#endif  //!__SET__H