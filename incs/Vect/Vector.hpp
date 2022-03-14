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
	>class vector
	{
		//Member types & functions
		public :
			typedef	T												value_type;
			typedef	Allocator										allocator_type;
			typedef size_t											size_type;
			typedef	std::ptrdiff_t									difference_type;
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
			vector();
			vector( const allocator_type& alloc );
			vector( size_type count,
                 const value_type& value,
                 const allocator_type& alloc);
			vector( size_type count, const Allocator& alloc = Allocator() );
			vector( const vector& other );
			~vector();
			vector& operator=( const vector& other );
			void assign( size_type count, const T& value );
			allocator_type get_allocator() const {return allocator_type();}

			template< class InputIt >
			void assign(InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = 0)//void * = 0
			{
				this->clear();
				while (first != last)
				{
					this->push_back(*first);
					++first;
				}
			}

			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc )
			{
				this->_alloc = alloc;
				this->_curr_len = last - first;
				this->_cap = last - first;
				this->_ptr = _alloc.allocate((this->_cap));
				for (size_type i = 0; i < this->_cap; ++i) {new (this->_ptr + i) T;} //use placement new to call type constructors
				// this->_ptr = new value_type[this->_cap]; //using new
				this->_next_size = sizeof (value_type) * this->_cap* 2;
				this->assign(first, last);
			}		

			//element access
			reference at( size_type pos );
			const_reference at( size_type pos ) const {return this->at(pos);}

			reference operator[]( size_type pos ) {return this->_ptr[pos];}
			const_reference operator[]( size_type pos ) const {return this->_ptr[pos];}

			reference front() {return this->_ptr[0];}
			const_reference front() const {return this->_ptr[0];}

			reference back() {return this->_ptr[this->_curr_len - 1];}
			const_reference back() const {return this->_ptr[this->_curr_len - 1];}

			T* data() {return this->_ptr;}
			const T* data() const {return this->_ptr;}

			//iterators
			iterator begin() { return iterator(this->_ptr);}
			const_iterator begin() const { return const_iterator(this->_ptr);}

			iterator end() { return iterator(&(this->_ptr[this->_curr_len]));}
			const_iterator end() const { return const_iterator(&(this->_ptr[this->_curr_len]));}

			reverse_iterator rbegin() { return reverse_iterator(&(this->_ptr[this->_curr_len - 1]));};
			const_reverse_iterator rbegin() const { return const_reverse_iterator(&(this->_ptr[this->_curr_len - 1]));};

			reverse_iterator rend() { return reverse_iterator(this->_ptr - 1);}
			const_reverse_iterator rend() const { return const_reverse_iterator(this->_ptr - 1);}

			//capacity
			bool 		empty() const {return this->_curr_len == 0;}
			size_type 	size() const {return this->_curr_len;}
			size_type 	max_size() const {return  (std::numeric_limits<size_type>::max() / (sizeof(value_type)));};
			void 		reserve( size_type new_cap );
			size_type 	capacity() const {return this->_cap;}

			//modifiers
			void clear();
			iterator insert( iterator pos, const T& value );
			void insert( iterator pos, size_type count, const T& value );
			void insert( iterator pos, iterator first, iterator last);
			void insert( iterator pos, const_iterator first, const_iterator last);
			iterator erase( iterator pos );
			iterator erase( const_iterator pos );
			iterator erase( iterator first, iterator last );
			iterator erase( const_iterator first, const_iterator last );

			void push_back( const T& value );
			void pop_back();

			void resize( size_type count, T value = T() );

			void swap( vector& other );
	};

	//member funcs definitions
	template < typename T, typename Alloc >
	vector<T, Alloc>::vector()
	{
		this->_alloc = std::allocator<T>();
		this->_curr_len = 0;
		this->_cap = 0;
		this->_ptr = 0;
		this->_next_size = sizeof (value_type) * 2;
	}

	template < typename T, typename Alloc >
	vector<T, Alloc>::vector(const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_curr_len = 0;
		this->_cap = 0;
		this->_ptr = 0;
		this->_next_size = sizeof (value_type) * 2;
	}

	template < class T, class Alloc >
	vector<T, Alloc>::vector( size_type count,
                 const value_type& value,
                 const allocator_type& alloc)
	{
		this->_alloc = alloc;
		this->_curr_len = count;
		this->_cap = count;
		this->_ptr = _alloc.allocate(count);//this->_ptr = _alloc.allocate(count);
		for (size_type i = 0; i < count; ++i) {new (this->_ptr + i) T;} //use placement new to call type constructors
		this->_next_size = sizeof (value_type) * count * 2;
		for (size_type i = 0; i < count; ++i)
			this->_ptr[i] = value;
	}

	template < typename T, typename Alloc >
	vector<T, Alloc>::vector( size_type count, const allocator_type& alloc )
	{
		this->_alloc = alloc;
		this->_curr_len = count;
		this->_cap = count;
		this->_ptr = _alloc.allocate(count);//this->_ptr = _alloc.allocate(count);
		for (size_type i = 0; i < count; ++i) {new (this->_ptr + i) T;} //use placement new to call type constructors
		this->_next_size = sizeof (value_type) * count * 2;
		//fill in null?
		// for (size_type i = 0; i < count; ++i)
		// 	this->_ptr[i] = value;
	}

	template < typename T, typename Alloc >
	vector<T, Alloc>::vector( const vector& other )
	{
		if (this->_ptr)
		{
			for (size_type i = 0; i < this->_curr_len; ++i) {(this->_ptr + i)->~T();}//use placement new to call type destructors
			_alloc.deallocate(this->_ptr, this->_curr_len);
			//delete [] this->_ptr;
			this->_ptr = 0;
		}
		this->_ptr = other._ptr;
		this->_alloc = other._alloc;
		this->_curr_len = other._curr_len;
		this->_cap = other._cap;
		this->_next_size = other._next_size;
		*this = other;
	}

	template < typename T, typename Alloc >
	vector<T, Alloc>::~vector(  )
	{
		if (this->_ptr)
		{
			for (size_type i = 0; i < this->_curr_len; ++i) {(this->_ptr + i)->~T();}//use placement new to call type destructors
			_alloc.deallocate(this->_ptr, this->_curr_len);
			//delete [] this->_ptr;
			this->_ptr = 0;
		}
	}
	
	template < typename T, typename Alloc >
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector& other)
	{
		// if (this->_ptr)
		// {
		// 	for (size_type i = 0; i < this->_curr_len; ++i) {(this->_ptr + i)->~T();}//use placement new to call type destructors
		// 	_alloc.deallocate(this->_ptr, this->_curr_len);
		// 	// delete [] this->_ptr;
		// 	this->_ptr = 0;
		// }
		// this->_ptr = _alloc.allocate(other._cap);
		// for (size_type i = 0; i < other._cap; ++i) {new (this->_ptr + i) T;}//use placement new to call type constructors
		// this->_ptr = new value_type[other._cap]; //using new
		
		this->assign(other.begin(), other.end());

		return *this;
	}

	template < typename T, typename Alloc >
	void	vector<T, Alloc>::assign( size_type count, const T& value )
	{
		size_t	n;

		n = -1;
		this->clear();
		while (++n < count)
			this->push_back(value);
	}

	//element access definitions
	template < typename T, typename Alloc >
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos)
	{
		if (pos >= this->_curr_len)
					throw (std::out_of_range("out of range"));
		return this->_ptr[pos];
	}

	//capacity definitions
	template < typename T, typename Alloc >
	void vector<T, Alloc>::reserve( size_type new_cap )
	{
		pointer		temp;
		size_type	i;

		if (new_cap <= this->_cap)
			return ;
		if (new_cap > this->max_size())
			throw (std::length_error("length_error"));
		
		temp = _alloc.allocate(new_cap);
		for (size_type i = 0; i < new_cap; ++i) {new (temp + i) T;} //use placement new to call type constructors
		// temp = new value_type[new_cap]; // using new
		i = -1;
		while (++i < this->_curr_len)
			temp[i] = this->_ptr[i];
		if (this->_ptr)
		{
			for (size_type i = 0; i < this->_curr_len; ++i) {(this->_ptr + i)->~T();}//use placement new to call type destructors
			_alloc.deallocate(this->_ptr, this->_curr_len);
		}
			// delete [] this->_ptr;
		this->_cap = new_cap;
		this->_ptr = temp;

	}

	//modifiers definition
	template < typename T, typename Alloc >
	void vector<T, Alloc>::clear()
	{
		// if (this->_ptr)
		// {
		// 	delete [] this->_ptr;
		// 	this->_ptr = 0;
		// }
		// this->_curr_len = 0;
		// this->_cap = 0;
		// this->_next_size = sizeof (value_type) * 2;

		//the og does not free lol, just set size to 0
		this->_curr_len = 0;
		// this->_next_size = sizeof (value_type) * 2;
	}

	template < typename T, typename Alloc >
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert( iterator pos, const T& value )
	{
		this->insert(pos, 1, value);
		return (++pos);
	}

	template < typename T, typename Alloc >
	void vector<T, Alloc>::insert( iterator pos, size_type count, const T& value )
	{
		vector<T, Alloc>	right(pos, this->end(), std::allocator<T>()); //right side of new vect
		size_type			i;	//iterator
		iterator			right_begin;	//right side begin iter
		iterator			right_end;	//right side end iter

		//adjust current length for cutting array
		this->_curr_len -= this->end() - pos;
		
		//populate mid section
		i = -1;
		while (++i < count)
			this->push_back(value);
		
		//populate right section
		right_begin = right.begin();
		right_end = right.end();
		while (right_begin != right_end)
		{
			this->push_back(*right_begin);
			right_begin++;
		}
	}

	template < typename T, typename Alloc >
	void vector<T, Alloc>::insert( iterator pos, iterator first, iterator last)
	{
		vector<T, Alloc>	right(pos, this->end(), std::allocator<T>()); //right side of new vect
		iterator			right_begin;	//right side begin iter
		iterator			right_end;	//right side end iter

		//adjust current length for cutting array
		this->_curr_len -= this->end() - pos;
		
		//populate mid section
		while (first != last)
		{
			this->push_back(*first);
			first++;
		}
		
		//populate right section
		right_begin = right.begin();
		right_end = right.end();
		while (right_begin != right_end)
		{
			this->push_back(*right_begin);
			right_begin++;
		}
	}

	template < typename T, typename Alloc >
	void vector<T, Alloc>::insert( iterator pos, const_iterator first, const_iterator last)
	{
		vector<T, Alloc>	right(pos, this->end(), std::allocator<T>()); //right side of new vect
		iterator			right_begin;	//right side begin iter
		iterator			right_end;	//right side end iter

		//adjust current length for cutting array
		this->_curr_len -= this->end() - pos;
		
		//populate mid section
		while (first != last)
		{
			this->push_back(*first);
			first++;
		}
		
		//populate right section
		right_begin = right.begin();
		right_end = right.end();
		while (right_begin != right_end)
		{
			this->push_back(*right_begin);
			right_begin++;
		}
	}

	template < typename T, typename Alloc >
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( iterator pos )
	{
		iterator	og; //original position (will soon point to deleted elem)
		iterator	end; //final element 

		og = pos;
		end = --this->end();

		//replce current value with next value
		while (pos != end)
		{
			*pos = *(pos + 1);
			pos++;
		}
		this->_curr_len--;
		return og;
	}

	template < typename T, typename Alloc >
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( const_iterator pos )
	{
		const_iterator	og; //original position (will soon point to deleted elem)
		const_iterator	end; //final element 

		og = pos;
		end = --this->end();

		//replce current value with next value
		while (pos != end)
		{
			*pos = *(pos + 1);
			pos++;
		}
		this->_curr_len--;
		return og;
	};
	template < typename T, typename Alloc >
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( iterator first, iterator last )
	{
		iterator	res;
		iterator	end;
		
		res = last;
		end = this->end();
		while (last != end)
		{
			*first = *last;
			first++;
			last++;
		}
		this->_curr_len -= (last - first);
		return res;
		
	}

	template < typename T, typename Alloc >
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase( const_iterator first, const_iterator last )
	{
		const_iterator	res;

		while (first != last)
		{
			res = this->erase(first);
			first++;
		}
		return res;
	}

	template < typename T, typename Alloc >
	void	vector<T, Alloc>::push_back( const T& value )
	{
		if (this->_curr_len >= this->_cap)
		{
			this->reserve(this->_next_size);
			this->_next_size *= this->_next_size;
		}
		this->_ptr[this->_curr_len ++] = value;
	}

	template < typename T, typename Alloc >
	void	vector<T, Alloc>::pop_back()
	{
		if (this->_curr_len)
			--this->_curr_len;
	}

	template < typename T, typename Alloc >
	void	vector<T, Alloc>::resize( size_type count, T value )
	{
		//case 1: count is lesser than length
		while (count < this->_curr_len)
			this->pop_back();

		//case 2: count is > than capacity
		if (count > this->_cap)
		{
			this->reserve(this->_next_size);
			this->_next_size *= this->_next_size;
		}

		//case 3: count > currlen
		while (count > this->_curr_len)
			this->push_back(value);
	}

	template < typename T, typename Alloc >
	void	vector<T, Alloc>::swap( vector& other )
	{
		// vector<T, Alloc>	temp;

		// temp = *this;
		// *this = other;
		// other = temp;
		pointer			_ptr_temp;
		allocator_type	_alloc_temp;
		size_type		_curr_len_temp;
		size_type		_cap_temp;
		size_type		_next_size_temp;

		_ptr_temp = this->_ptr;
		_alloc_temp = this->_alloc;
		_curr_len_temp = this->_curr_len;
		_cap_temp = this->_cap;
		_next_size_temp = this->_next_size;

		this->_ptr = other._ptr;
		this->_alloc = other._alloc;
		this->_curr_len = other._curr_len;
		this->_cap = other._cap;
		this->_next_size = other._next_size;

		other._ptr = _ptr_temp;
		other._alloc = _alloc_temp;
		other._curr_len = _curr_len_temp;
		other._cap = _cap_temp;
		other._next_size = _next_size_temp;
	}

	template < typename T, typename Alloc >
	bool	operator == (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		typename vector<T, Alloc>::const_iterator first1;
		typename vector<T, Alloc>::const_iterator last1;
		typename vector<T, Alloc>::const_iterator first2;
		typename vector<T, Alloc>::const_iterator last2;

		if (lhs.size() != rhs.size())
			return false;
		first1 = lhs.begin();
		last1 = lhs.end();
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

	template < typename T, typename Alloc >
	bool	operator != (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template < typename T, typename Alloc >
	bool	operator < (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template < typename T, typename Alloc >
	bool	operator <= (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (lhs < rhs || lhs == rhs);
	}

	template < typename T, typename Alloc >
	bool	operator > (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs <= rhs);
	}

	template < typename T, typename Alloc >
	bool	operator >= (const vector<T, Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (lhs > rhs || lhs == rhs);
	}
}//ft



#endif  //!__VECTOR__H__