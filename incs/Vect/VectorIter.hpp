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

		//constructors 
		VectorIter(void) : ptr(0){}
		~VectorIter(void){}
		VectorIter(const pointer ptr): ptr(ptr) {}
		VectorIter(const iterator &other): ptr(other.ptr){}

		//operators
		VectorIter &operator=(const iterator &iter)
		{
			this->ptr = iter.ptr;
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
		VectorIter &operator+=(int value) {this->p += value; return (*this);}
		VectorIter &operator-=(int value) {this->p -= value; return (*this);}
		curr_class &operator++ () { ptr++ ; return *this ; }
		curr_class &operator-- () { ptr-- ; return *this ; }
		curr_class operator++ (int) { curr_class temp(*this) ; this->operator++() ; return temp ; }
		curr_class operator-- (int) { curr_class temp(*this) ; this->operator--() ; return temp ; }

};
#endif  //!__VECTORITER__H__