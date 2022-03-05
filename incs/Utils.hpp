#ifndef __UTILS__H__
#define __UTILS__H__
#include <main.hpp>

namespace ft
{
	//custom swap function
	template <typename T>
	void	swap(T &a, T&b)
	{
		T	temp;

		temp = a;
		a = b;
		b = temp;
	}

	//pair , replacement for std::pair
	template <class T1, class T2>
	struct pair
	{
		public:
			//member types
			typedef	T1	first_type;
			typedef	T2	second_type;

			//member vars
			first_type	first;
			second_type	second;

			//constructors
			pair(): first(), second(){}
			pair(const first_type &A, const second_type &B): first(A), second(B){}
			~pair(){}

			template <class X, class Y>
			pair(const pair<X, Y>&other): first(other.first), second(other.second){}

			//operator overloads
			pair& operator= (const pair& other)
			{
				this->first = other.first;
				this->second = other.second;
				return (*this);
			}

			bool operator== (const pair<T1,T2>& rhs) const
			{
				return (this->first == rhs.first && this->second == rhs.second);
			}

			bool operator!= (const pair<T1,T2>& rhs) const
			{
				return !(*this == rhs);
			}

			bool operator< (const ft::pair<T1,T2>& rhs) const
			{
				return (this->first < rhs.first || ((rhs.first == this->first) && (this->second < rhs.second)));
			}

			bool operator> (const ft::pair<T1,T2>& rhs) const
			{
				return (this->first > rhs.first || ((rhs.first == this->first) && (this->second > rhs.second)));
			}

			bool operator<= (const ft::pair<T1,T2>& rhs) const
			{
				return (*this < rhs || *this == rhs);
			}

			bool operator>= (const ft::pair<T1,T2>& rhs) const
			{
				return (*this > rhs || *this == rhs);
			}
	};

	template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

	//lexicographical_compare, replacement for std::lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) return false;
			else if (*first1 < *first2) return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	
	//iterator traits
	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::value_type        value_type;
		typedef typename Iter::difference_type   difference_type;
		typedef typename Iter::pointer           pointer;
		typedef typename Iter::reference         reference;
	};

	template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

	template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
		public :
			typedef		 _Tp                         value_type;
			typedef		 ptrdiff_t                   difference_type;
			typedef const _Tp*                        pointer;
			typedef const _Tp&                        reference;
    };

	//reverse iterator
	template< class Iter >
	class reverse_iterator
	{
		private:
			Iter		ptr;

		protected :
			Iter	current;
			
		public :
			typedef	typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef	typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef	typename ft::iterator_traits<Iter>::reference			reference;

			//constructors 
			reverse_iterator(void) : ptr(0){}
			reverse_iterator(const pointer ptr): ptr(ptr) {}
			reverse_iterator(const reverse_iterator &iter){*this = iter;}

			//operators
			reverse_iterator &operator=(const reverse_iterator &iter)
			{
				ptr = iter.ptr;
				return *this;
			}
			reference operator* () { return *(ptr); }
			value_type *operator-> () { return *(ptr) ; }
			bool operator== ( const reverse_iterator<Iter>& that ) const { return ptr == that.ptr ; }
			bool operator!= ( const reverse_iterator<Iter>& that ) const { return ptr != that.ptr ; }
			bool operator>= ( const reverse_iterator<Iter>& that ) const { return ptr >= that.ptr ; }
			bool operator<= ( const reverse_iterator<Iter>& that ) const { return ptr <= that.ptr ; }
			bool operator> ( const reverse_iterator<Iter>& that ) const { return ptr > that.ptr ; }
			bool operator< ( const reverse_iterator<Iter>& that ) const { return ptr < that.ptr ; }
			reverse_iterator<Iter> &operator+ (int n){return (this->base() - n);}
			reverse_iterator<Iter> &operator- (int n){return (this->base() + n);}
			reverse_iterator<Iter> &operator- (reverse_iterator<Iter>& rhs){return (rhs.base() - this->base());}
			reverse_iterator<Iter> &operator++ () { ptr-- ; return *this ; }
			reverse_iterator<Iter> &operator-- () { ptr++ ; return *this ; }
			reverse_iterator<Iter> operator++ (int) { reverse_iterator<Iter> temp(*this) ; this->operator++() ; return temp ; }
			reverse_iterator<Iter> operator-- (int) { reverse_iterator<Iter> temp(*this) ; this->operator--() ; return temp ; }
			reference operator[]( int n ) const {return (this->base()[-n-1]); }
	
			//mem funcs
			Iter base() const {return current;}
	};

	//enable if
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	//is integral

	// integral_constant
  	template<typename Bool>
	struct integral_constant_true
	{
		// static	Bool                  			value;
		enum { value = true  };
		typedef Bool                          	value_type;
		typedef integral_constant_true<Bool>  		type;
	};

	// integral_constant
	template<typename Bool>
	struct integral_constant_false
	{
		// static	Bool                  			value;
		enum { value = false  };
		typedef Bool                          	value_type;
		typedef integral_constant_false<Bool>  		type;
	};

	// The type used as a compile-time boolean with true value.
	typedef integral_constant_true<bool>     true_type;

	// template<>
	// bool	true_type::value = true;

	// The type used as a compile-time boolean with false value.
	typedef integral_constant_false<bool>     false_type;

	// template<>
	// bool	false_type::value = false;

	template<typename>
    struct is_integral_helper
    : public false_type { };

	template<>
	struct is_integral_helper<bool>
	: public true_type { };

	template<>
	struct is_integral_helper<char>
	: public true_type { };

	template<>
	struct is_integral_helper<signed char>
	: public true_type { };

	template<>
	struct is_integral_helper<unsigned char>
	: public true_type { };

	template<>
	struct is_integral_helper<wchar_t>
	: public true_type { };

	template<>
	struct is_integral_helper<short>
	: public true_type { };
	
	template<>
	struct is_integral_helper<unsigned short>
	: public true_type { };

	template<>
	struct is_integral_helper<int>
	: public true_type {};

	template<>
	struct is_integral_helper<unsigned int>
	: public true_type { };

	template<>
	struct is_integral_helper<long>
	: public true_type { };

	template<>
	struct is_integral_helper<unsigned long>
	: public true_type { };

	template<>
	struct is_integral_helper<long long>
	: public true_type { };

	template<>
	struct is_integral_helper<unsigned long long>
	: public true_type { };

	// is_integral core
  	template<typename T>
    struct is_integral : public is_integral_helper<T>::type
    {};
	

}//ft

#endif  //!__UTILS__H__