#ifndef __MAPUTILS__H__
#define __MAPUTILS__H__
#include <main.hpp>

//BST node
template <class Key, class T>
struct BSTNode
{
	std::pair<Key, T> pair;
	BSTNode *left;
	BSTNode *right;
	BSTNode *parent;
	// bool is_end; need extra end node for iter?
};

namespace ft
{
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
	
}//ft

#endif  //!__MAPUTILS__H__