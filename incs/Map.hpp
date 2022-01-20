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
	// Refer for c++ map source code
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> >
	>
	class Map
	{
		public :
			//typedefs (refer to sourcecode)
			typedef Key										key_type;
			typedef	T										mapped_type;
			typedef	std::pair<const key_type, mapped_type>	value_type;
			typedef	Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef T& 										reference;
			typedef const T& 								const_reference;
			typedef size_t									size_type;
			typedef BSTNode<key_type, mapped_type>			*node;
			//todo define iterator
	};
}//ft

#endif  //!__MAP__H