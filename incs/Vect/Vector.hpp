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
			pointer			_ptr;
			allocator_type	_alloc;
			size_type		_curr_len;
			size_type		_cap;
			size_type		_next_size;

		//member functions & access operations
		public :
			//member func
			Vector();
			Vector( const allocator_type& alloc );
			Vector( size_type count,
                 const value_type& value,
                 const allocator_type& alloc);
			Vector( size_type count, const Allocator& alloc = Allocator() );
			Vector( const Vector& other );
			~Vector();
			Vector& operator=( const Vector& other );
			void assign( size_type count, const T& value );
			allocator_type get_allocator() const;

			template< class InputIt >
				void assign( InputIt first, InputIt last );

			template< class InputIt >
			Vector( InputIt first, InputIt last, const allocator_type& alloc )
			{
				this->_alloc = alloc;
				this->_curr_len = last - first;
				this->_cap = last - first;
				this->_ptr = new value_type[this->_cap];
				this->_next_size = sizeof (value_type) * this->_cap* 2;
				//assign values
			}
					

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

	//member funcs definitions
	template < typename T, typename Alloc >
	Vector<T, Alloc>::Vector(const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_curr_len = 0;
		this->_cap = 0;
		this->_ptr = 0;
		this->_next_size = sizeof (value_type) * 2;
	}

	template < class T, class Alloc >
	Vector<T, Alloc>::Vector( size_type count,
                 const value_type& value,
                 const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_curr_len = count;
		this->_cap = count;
		this->_ptr = new value_type[count];
		this->_next_size = sizeof (value_type) * count * 2;
		for (size_type i = 0; i < count; ++i)
			this->_ptr[i] = value;
	}

	template < typename T, typename Alloc >
	Vector<T, Alloc>::Vector( size_type count, const allocator_type& alloc )
	{
		this->_alloc = alloc;
		this->_curr_len = count;
		this->_cap = count;
		this->_ptr = new value_type[count];
		this->_next_size = sizeof (value_type) * count * 2;
		//fill in null?
		// for (size_type i = 0; i < count; ++i)
		// 	this->_ptr[i] = value;
	}

	template < typename T, typename Alloc >
	Vector<T, Alloc>::Vector( const Vector& other )
	{
		this->_ptr = 0;
		this->_alloc = other._alloc;
		this->_curr_len = other._curr_len;
		this->_cap = other._cap;
		this->_next_size = other._next_size;
		*this = other;
	}

	template < typename T, typename Alloc >
	Vector<T, Alloc>::~Vector(  )
	{
		if (this->_ptr)
		{
			delete [] this->_ptr;
			this->_ptr = 0;
		}
	}
	
	template < typename T, typename Alloc >
	Vector<T, Alloc> &Vector<T, Alloc>::operator=(const Vector& other)
	{
		if (this->_ptr)
		{
			delete [] this->_ptr;
			this->_ptr = 0;
		}
		this->_ptr = new value_type[other._cap];
		this->_alloc = other._alloc;
		this->_curr_len = 0;
		this->_cap = other._cap;
		this->_next_size = other._next_size; 
		//assign logic here
		return *this;
	}
}//ft


#endif  //!__VECTOR__H__