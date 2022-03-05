#ifndef __STACK__H__
#define __STACK__H__
#include "main.hpp"
#include "Vector.hpp"

namespace ft
{
	template<
    class T,
    class Container = ft::Vector<T>
	> class Stack
	{
		public :
			//member types
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			//member objects
			Container	c;

			//member functions
			// Stack(){ }
			Stack( const Container& cont = Container() ){this->c = cont;}
			Stack( const Stack& other ){this->c =  other.c;}
			~Stack(){}
			Stack& operator=( const Stack& other ) {this->c = other.c; return *this;}

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
			bool operator==( const Stack<T,Container>& rhs ) {return this->c == rhs.c;}
			bool operator!=( const Stack<T,Container>& rhs ) {return !(*this == rhs);}
			bool operator<=( const Stack<T,Container>& rhs ){return this->c <= rhs.c;}
			bool operator<( const Stack<T,Container>& rhs ) {return this->c < rhs.c;}
			bool operator>=( const Stack<T,Container>& rhs ) {return this->c >= rhs.c;}
			bool operator>( const Stack<T,Container>& rhs ) {return this->c > rhs.c;}
	};
}//ft

#endif  //!__STACK__H__