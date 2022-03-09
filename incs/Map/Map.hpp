#ifndef __MAP__H
#define __MAP__H
#include "main.hpp"
#include "MapIter.hpp"
#include "MapUtils.hpp"

namespace ft
{
	
	// Class std::map wrapper with performance instrumentation.
	// Refer for c++ map reference (https://en.cppreference.com/w/cpp/container/map)
	// Refer for c++ map source code (https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/stl__map_8h-source.html)
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<BSTNode<Key, T> > //class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
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
			typedef std::ptrdiff_t							difference_type;
			typedef BSTNode<key_type, mapped_type>			*node;
			typedef MapIter<key_type, mapped_type, pointer, reference>						iterator;
			typedef ReverseMapIter<key_type, mapped_type, pointer, reference>				reverse_iterator;
			typedef MapIter<key_type, mapped_type, const_pointer, const_reference>			const_iterator;
			typedef ReverseMapIter<key_type, mapped_type, const_pointer, const_reference>	const_reverse_iterator;

			//binary function for C++98 implementation
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Allocator>;
				protected : 
					Compare cmp; // compare is the maps compare object
					value_compare (Compare c) : cmp(c) {}
				public :
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& left, const value_type& right) const
					{
						return cmp(left.first, right.first);
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
			node _new_node(key_type key, mapped_type value, node parent, bool is_end = false)
			{
				node	res;

				// res = new BSTNode<key_type, mapped_type>();
				res = _allocator.allocate(1);
				_allocator.construct(res, BSTNode<key_type, mapped_type>());
				res->pair = ft::make_pair(key, value);
				res->left = 0;
				res->right = 0;
				res->parent = parent;
				res->is_end = is_end;

				return res;
			}

			//void	free_tree(node n);
			void	_free_tree(node n)
			{
				if (n->left)
					_free_tree(n->left);
				if (n->right)
					_free_tree(n->right);
				// delete n;
				(n)->~BSTNode<key_type, mapped_type>();
				_allocator.deallocate(n, 1);
			}

			//node _insert_node(node n, key_type key, mapped_type value)
			//insert node n into bst (n is not null)
			//base case: check if node is leaf . If it is, add to left or right subtree
			//recurse left if value is smaller than curr node
			//vice versa if larger
			node _insert_node(node n, key_type key, mapped_type value, bool is_end = false)
			{
				if (n->is_end)
				{
					n->is_end = false;
					n->right = _new_node(key_type(), mapped_type(), n, true);
					n->pair = ft::make_pair(key, value);
					return (n);
				}
				if (key < n->pair.first)
				{
					if (n->left)
						return _insert_node(n->left, key, value);
					else
						n->left = _new_node(key, value, n, is_end);
					return n->left;
				}
				else if (key > n->pair.first)
				{
					if (n->right)
						return _insert_node(n->right, key, value);
					else
						n->right = _new_node(key, value, n, is_end);
					return n->right;						
				}
				return this->_end();
			}

			//node _find(node n, key_type key) const
			//if curr nodes key is equal to key, return curr node (base case)
			node _find(node n, key_type key) const
			{
				if (!n->is_end && n->pair.first == key)
					return n;
				if (n->right && key > n->pair.first)
					return _find(n->right, key);
				if (n->left && key < n->pair.first)
					return _find(n->left, key);
				return this->_end();
			}

			//void _delete_node(node n)
			//case 1. Node is leaf - remove node
			//case 2. Node has 1 child - copy child node and delete child
			//case 3. Node has 2 children. Find inorder predeseccor, swap and delete successor
			void _delete_node(node n)
			{
				node	successor;

				if (n->is_end)
				{
					if (n->parent && n->parent->is_end)
					{
						(n)->~BSTNode<key_type, mapped_type>();
						_allocator.deallocate(n, 1); // delete n; 
					}
					return ; 
				}
				else if (n->parent && !n->left && !n->right)
				{
					if (n->parent->left == n)
						n->parent->left = 0;
					else if (n->parent->right == n)
						n->parent->right = 0;
					// std::cout << "1st rule deleting (" << n->pair.first << ", " << n->pair.second << ") \n";
					(n)->~BSTNode<key_type, mapped_type>();
					_allocator.deallocate(n, 1); //delete n;
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
					// std::cout << "2nd rule deleting (" << n->pair.first << ", " << n->pair.second << ") \n";
					// std::cout << "2nd rule parent (" << n->parent->pair.first << ", " << n->parent->pair.second << ") \n";
					(n)->~BSTNode<key_type, mapped_type>();
					_allocator.deallocate(n, 1);//delete n;
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
					// std::cout << "3rd rule deleting (" << n->pair.first << ", " << n->pair.second << ") \n";
					(n)->~BSTNode<key_type, mapped_type>();
					_allocator.deallocate(n, 1); //delete n;
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
				ft::swap(successor->pair, n->pair);
				// std::cout << "4th rule recursing. current pair : (" << n->pair.first << ", " << n->pair.second << ") ";
				// std::cout << "successor pair : (" << successor->pair.first << ", " << successor->pair.second << ") \n";
				// std::cout << "successor parent : (" << successor->parent->pair.first << ", " << successor->parent->pair.second << ") \n";
				_delete_node(successor);
				// std::cout << "should change now : (" << n->pair.first << ", " << n->pair.second << ") \n";
			}

			//void _init_tree(void)
			void _init_tree(void)
			{
				this->_root = _new_node(key_type(), mapped_type(), 0, true);
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
			explicit map(const key_compare &comp = key_compare(), const allocator_type alloc = allocator_type());
			map(map<Key, T> &other);
			~map();
			map &operator=(map<Key, T> &other);
			allocator_type	get_allocator() const {return allocator_type();}

			//element access
			mapped_type &at( const key_type& key );
			mapped_type &operator[](const key_type& key);

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
			size_type max_size() const {return (std::numeric_limits<size_type>::max() / (sizeof(BSTNode<key_type, mapped_type>)));}

			//modifiers
			void clear();
			ft::pair<iterator, bool> insert( const value_type& value );
			iterator insert( iterator hint, const value_type& value );
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const Key& key );
			void swap( map& other );

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					// std::cout << "inserting (" << first->first << ", " << first->second << ") \n";
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
			bool operator==( const map<Key,T,Compare,Allocator>& rhs );
			bool operator!=( const map<Key,T,Compare,Allocator>& rhs );
			bool operator<=( const map<Key,T,Compare,Allocator>& rhs );
			bool operator<( const map<Key,T,Compare,Allocator>& rhs );
			bool operator>=( const map<Key,T,Compare,Allocator>& rhs );
			bool operator>( const map<Key,T,Compare,Allocator>& rhs );
			
			//observers
			key_compare 	key_comp() const;
			value_compare 	value_comp() const;
	};

	//member function definitions
	template <class Key, class T, class Compare, class Alloc >
	map<Key, T, Compare, Alloc>::map(const key_compare &comp, const allocator_type alloc)
	{
		this->_allocator = alloc;
		this->_compare = comp;
		this->_init_tree();
	}

	template <class Key, class T, class Compare, class Alloc >
	map<Key, T, Compare, Alloc>::map(map<Key, T> &other)
	{
		this->_init_tree();
		*this = other;
	}

	template <class Key, class T, class Compare, class Alloc >
	map<Key, T, Compare, Alloc>::~map()
	{
		this->_free_tree(this->_root);
	}


	template <class Key, class T, class Compare, class Alloc >
	map<Key, T, Compare, Alloc> &map<Key, T, Compare, Alloc>::operator= (map<Key, T> &other)
	{	
		this->clear();
		this->insert(other.begin(), other.end());
		return (*this);
	}

	//element access definitions
	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc> ::mapped_type &map<Key, T, Compare, Alloc>::at(const key_type& k)
	{
		node	n;

		n = this->_find(this->_root, k);
		if (n->is_end)
			throw std::out_of_range("out_of_range");
		return n->pair.second;
	}
	
	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc> ::mapped_type &map<Key, T, Compare, Alloc>::operator [] (const key_type& k)
	{	
		iterator temp;

		temp = this->find(k);
		if (temp != this->end())
			return temp->second;
		return (this->insert(ft::make_pair(k, mapped_type())).first->second);
	}

	//Iterator definitions
	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::begin()
	{
		node n = this->_root;
		// std::cout << "curr root in begin : " << n->pair.second << "\n";
		if (!n->left && !n->right)
			return (iterator(n));
		while (n->left)
			n = n->left;
		return (iterator(n));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::begin() const
	{
		node n = this->_root;
		if (!n->left && !n->right)
			return (const_iterator(n));
		while (n->left)
			n = n->left;
		return (const_iterator(n));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::reverse_iterator map<Key, T, Compare, Alloc>::rbegin()
	{
		iterator	iter;

		iter = this->end();
		iter--;
		return (reverse_iterator(iter.node()));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator map<Key, T, Compare, Alloc>::rbegin() const
	{
		iterator	iter;

		iter = this->end();
		iter--;
		return (const_reverse_iterator(iter.node()));	
	}

	//modifiers definitions
	template <class Key, class T, class Compare, class Alloc >
	void map<Key, T, Compare, Alloc>::erase(iterator position)
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
			// std::cout << "new root : (" << this->_root->pair.first << ", " << this->_root->pair.second << ") \n";
		}
		// std::cout << "root after erase : (" << this->_root->pair.first << ", " << this->_root->pair.second << ") \n";
		--this->_len;
	}

	template <class Key, class T, class Compare, class Alloc >
	void map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		while (first != last)
			this->erase(first);
	}

	template <class Key, class T, class Compare, class Alloc >
	size_t map<Key, T, Compare, Alloc>::erase( const Key& key )
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

	template <class Key, class T, class Compare, class Alloc >
	void map<Key, T, Compare, Alloc>::clear()
	{
		while (this->begin() != this->end())
			this->erase(this->begin());
		// this->erase(this->begin(), this->end());
	}

	template <class Key, class T, class Compare, class Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool> map<Key, T, Compare, Alloc>::insert( const value_type& value )
	{
		iterator	iter;

		iter = this->find(value.first);
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
		return (ft::make_pair(iterator(this->_insert_node(this->_root, value.first, value.second)), true));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::insert( iterator hint, const value_type& value )
	{
		iterator	iter;

		iter = this->find(value.first);
		if (iter != this->end())
			return (iter);
		++this->len;
		return (iterator(this->_insert_node(hint.node(), value.first, value.second)));
	}

	template <class Key, class T, class Compare, class Alloc >
	void map<Key, T, Compare, Alloc>::swap( map& other )
	{
		// map<Key, T, Compare, Alloc> temp = *this;
		// *this = other;
		// other = temp;

		allocator_type	_allocator_temp;
		node			_root_temp;
		key_compare		_compare_temp;
		size_type		_len_temp;

		_root_temp = this->_root;
		_allocator_temp = this->_allocator;
		_compare_temp = this->_compare;
		_len_temp = this->_len;

		this->_root = other._root;
		this->_allocator = other._allocator;
		this->_compare = other._compare;
		this->_len = other._len;

		other._root = _root_temp;
		other._allocator = _allocator_temp;
		other._compare = _compare_temp;
		other._len = _len_temp;
	}

	//lookup definitions
	template <class Key, class T, class Compare, class Alloc >
	size_t map<Key, T, Compare, Alloc>::count( const Key& key ) const
	{
		node	found;

		found = _find(this->_root, key);
		if (!found->is_end)
			return 1;
		return 0;
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::iterator  map<Key, T, Compare, Alloc>::find( const Key& key )
	{
		node	found;

		if (this->empty())
			return this->end();
		found = _find(this->_root, key);
		return iterator(found);
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::find( const Key& key ) const
	{
		node	found;

		if (this->empty())
			return this->end();
		found = _find(this->_root, key);
		return const_iterator(found);
	}

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::lower_bound( const Key& key )
	{
		iterator begin;
		iterator end;

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

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::lower_bound( const Key& key ) const
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

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::upper_bound( const Key& key )
	{
		iterator begin;
		iterator end;

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

	template <class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::upper_bound( const Key& key ) const
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

	template <class Key, class T, class Compare, class Alloc >
	typename ft::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
	map<Key, T, Compare, Alloc>::equal_range( const Key& key )
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template <class Key, class T, class Compare, class Alloc >
	typename ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>
	map<Key, T, Compare, Alloc>::equal_range( const Key& key ) const
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	//comparison operators
	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator==( const ft::map<Key,T,Compare,Alloc>& rhs )
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

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator!=( const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(*this == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator<( const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator<=( const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (*this < rhs || *this == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator>( const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(*this <= rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool map<Key, T, Compare, Alloc>::operator>=( const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (*this > rhs || *this == rhs);
	}

	//observers
	template< class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::key_compare 	map<Key, T, Compare, Alloc>::key_comp() const
	{
		return this->_compare;
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map<Key, T, Compare, Alloc>::value_compare 	map<Key, T, Compare, Alloc>::value_comp() const
	{
		return value_compare(this->_compare);
	}
	
}//ft

#endif  //!__MAP__H