#ifndef __UTIL__H__
#define __UTIL__H__

#include <sstream>
#include <cstddef>
#include <limits>
#include <typeinfo>
#include <iostream>

//custom null pointer class
class null_ptr
{

	public :
		//non member null conversion
		template<class T>
		operator T*() const {return (0);};

		//member null conversion
		template<class C, class T>
		operator T C::*() const {return (0);};

	private :
		//disable getting address
		void operator &() const;

};

namespace ft
{
	//custom tostring function
	//sstream http://www.cplusplus.com/articles/D9j2Nwbp/
	template <typename T>
	std::string to_string(T data)
	{
		std::string		res;
		std::ostringstream 	stream;

		stream << data;
		res = stream.str();
		return res;
	}	
} // namespace ft


#endif  //!__UTIL__H__