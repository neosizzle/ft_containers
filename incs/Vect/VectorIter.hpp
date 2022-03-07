#ifndef __VECTORITER__H__
#define __VECTORITER__H__

template <typename K, typename Pointer, typename Reference>
class VectorIter
{
	protected:
		K*		ptr;

	public :
		typedef K									value_type;
		typedef K&									reference;
		typedef K const &							const_reference;
		typedef K*									pointer;
		typedef VectorIter<K, Pointer, Reference>	curr_class;
		typedef VectorIter<K, K*, K&>				iterator;
		typedef	std::ptrdiff_t						difference_type;
		typedef	std::random_access_iterator_tag		iterator_category;

		//constructors 
		VectorIter(void) : ptr(0){}
		~VectorIter(void){}
		VectorIter(const pointer ptr): ptr(ptr) {}
		VectorIter(const iterator &other): ptr(other.ptr){}

		//operators
		VectorIter &operator=(const iterator &iter)
		{
			this->ptr = iter.base();
			return *this;
		}
		reference operator* () { return *ptr ; }
		const_reference operator* () const { return *ptr ; }
		value_type *operator-> () { return ptr; }
		const_reference operator-> () const { return ptr ; }
		reference operator[](int val) {return (*(this->p + val));}
		const_reference operator[](int val) const {return (*(this->p + val));}
		bool operator== ( const curr_class& that ) const { return ptr == that.ptr ; }
		bool operator!= ( const curr_class& that ) const { return ptr != that.ptr ; }
		bool operator>= ( const curr_class& that ) const { return ptr >= that.ptr ; }
		bool operator<= ( const curr_class& that ) const { return ptr <= that.ptr ; }
		bool operator< ( const curr_class& that ) const { return ptr < that.ptr ; }
		bool operator> ( const curr_class& that ) const { return ptr > that.ptr ; }
		VectorIter &operator+=(int value) {this->ptr += value; return (*this);}
		VectorIter &operator-=(int value) {this->ptr -= value; return (*this);}
		curr_class &operator++ () { ptr++ ; return *this ; }
		curr_class &operator-- () { ptr-- ; return *this ; }
		curr_class operator++ (int) { curr_class temp(*this) ; this->operator++() ; return temp ; }
		curr_class operator-- (int) { curr_class temp(*this) ; this->operator--() ; return temp ; }
		size_t  operator-( const curr_class& rhs) {return this->ptr - rhs.ptr;}
		size_t  operator+( const curr_class& rhs) {return this->ptr + rhs.ptr;}
		curr_class operator-( size_t n ) {curr_class temp(*this) ; temp -= n ; return temp ;}
		curr_class operator+( size_t n ) {curr_class temp(*this) ; temp += n ; return temp ;}

		pointer	base() const {return this->ptr;}
};
#endif  //!__VECTORITER__H__