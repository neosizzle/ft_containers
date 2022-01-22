#ifndef __MAP__H
#define __MAP__H
#include "main.hpp"
#include "MapIter.hpp"

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

	/// Class std::map wrapper with performance instrumentation.
	// Refer for c++ map reference (https://en.cppreference.com/w/cpp/container/map)
	// Refer for c++ map source code (https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/stl__map_8h-source.html)
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> >
	>
	class Map
	{
		//Member types & functions
		public :
			//typedefs (refer to sourcecode)
			typedef Key										key_type;
			typedef	T										mapped_type;
			typedef	std::pair<const key_type, mapped_type>	value_type;
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
				friend class Map<Key, T, Compare, Alloc>;
				protected : 
					Compare cmp; // compare is the maps compare object
					value_compare (Compare c) : comp(c) {}
				public :
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& left, const value_type& right) const
						return comp(left.first, right.first);
			}

			//helpers and attributes
			private :
				allocator_type	_allocator;
				node			_root;
				key_compare		_compare;
				size_type		_len;

				//node _new_node(key_type key, mapped_type value, node parent, bool is_leaf = false)

				//void	free_tree(node n);

				//node _insert_node(node n, key_type key, mapped_type value, bool is_leaf = false)

				//node _find(node n, key_type key) const

				//void _delete_node(node n)

				//void _init_tree(void)


				//node _end(void) const 

			//member functions & access operations
			public :

	};
}//ft

#endif  //!__MAP__H