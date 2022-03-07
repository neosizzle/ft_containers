#ifndef __STACK__H__
#define __STACK__H__
#include "main.hpp"
#include "Vector.hpp"

namespace ft
{
	template<
    class T,
    class Container = ft::vector<T>
	> class stack
	{
		protected:
			//member objects
			Container	c;

		public :
			//member types
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			//member functions
			stack( const Container& cont = Container() ){this->c = cont;}
			stack( const stack& other ){this->c =  other.c;}
			~stack(){}
			stack& operator=( const stack& other ) {this->c = other.c; return *this;}

			//element access
			reference top(){return this->c.back();}
			const_reference top() const {return this->c.back();}

			//capacity
			bool empty() const {return this->c.empty();}
			size_type size() const {return this->c.size();}

			//modifiers
			void push( const value_type& value ) {this->c.push_back(value);}
			void pop() {this->c.pop_back();}

			//comparison operators
			bool operator==( const stack<T,Container>& rhs ) {return this->c == rhs.c;}
			bool operator!=( const stack<T,Container>& rhs ) {return !(*this == rhs);}
			bool operator<=( const stack<T,Container>& rhs ){return this->c <= rhs.c;}
			bool operator<( const stack<T,Container>& rhs ) {return this->c < rhs.c;}
			bool operator>=( const stack<T,Container>& rhs ) {return this->c >= rhs.c;}
			bool operator>( const stack<T,Container>& rhs ) {return this->c > rhs.c;}
	};
}//ft

#endif  //!__STACK__H__