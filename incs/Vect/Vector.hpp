#ifndef __VECTOR__H__
#define __VECTOR__H__
#include "main.hpp"
#include "VectorUtils.hpp"
#include "VectorIter.hpp"

namespace ft
{
	template<
    class T,
    class Allocator = std::allocator<T>
	>class Vector
	{
		//Member types & functions
		public :
			typedef	T												value_type;
			typedef	Allocator										allocator_type;
			typedef size_t											size_type;
			typedef T& 												reference;
			typedef const T& 										const_reference;
			typedef T*												pointer;
			typedef	const	T*													const_pointer;
			typedef	VectorIter<value_type, pointer, reference>					iterator;
			typedef	VectorIter<value_type, const_pointer, const_reference>		const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		//helpers and attributes
		private :

		//member functions & access operations
		public :
			//member func
			Vector();
			Vector( const Allocator& alloc );
			Vector( size_type count,
                 const T& value = T(),
                 const Allocator& alloc = Allocator());
			Vector( size_type count, const Allocator& alloc = Allocator() );
			Vector( const Vector& other );
			~Vector();
			Vector& operator=( const Vector& other );
			void assign( size_type count, const T& value );
			allocator_type get_allocator() const;

			template< class InputIt >
				void assign( InputIt first, InputIt last );

			template< class InputIt >
			Vector( InputIt first, InputIt last,
					const Allocator& alloc = Allocator() );

			//element access
			reference at( size_type pos );
			const_reference at( size_type pos ) const;

			reference operator[]( size_type pos );
			const_reference operator[]( size_type pos ) const;

			reference front();
			const_reference front() const;

			reference back();
			const_reference back() const;

			T* data();
			const T* data() const;

			//iterators
			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			//capacity
			bool empty() const;

			iterator insert( iterator pos, const T& value );
			void insert( iterator pos, size_type count, const T& value );

			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last );

			iterator erase( iterator pos );
			iterator erase( const_iterator pos );
			iterator erase( iterator first, iterator last );
			iterator erase( const_iterator first, const_iterator last );

			void push_back( const T& value );
			void pop_back();

			void resize( size_type count );
			void resize( size_type count, T value = T() );

			void swap( Vector& other );

			//comparison operators
			bool operator==( const Vector<T,Allocator>& rhs );
			bool operator!=( const Vector<T,Allocator>& rhs );
			bool operator<=( const Vector<T,Allocator>& rhs );
			bool operator<( const Vector<T,Allocator>& rhs );
			bool operator>=( const Vector<T,Allocator>& rhs );
			bool operator>( const Vector<T,Allocator>& rhs );
	};
}//ft


#endif  //!__VECTOR__H__