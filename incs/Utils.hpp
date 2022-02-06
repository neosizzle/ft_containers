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
	
}//ft

#endif  //!__UTILS__H__