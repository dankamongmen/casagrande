#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <iostream>

#include <cstddef>
#include <initializer_list>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
class casagrande {
	unsigned elems;

public:
	typedef T value_type;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	typedef value_type *iterator;
	typedef const value_type *const_iterator;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	const_iterator begin() const { return 0; }
	const_iterator end() const { return 0; }
	size_type size() const { return 0; }
	bool empty() const { return true; }
	size_type max_size() const { return 0; }

	iterator insert(iterator,const value_type &);
	void insert(iterator,size_type,const value_type &);

	void insert(const_iterator ci,const std::initializer_list<value_type> ti){
		// FIXME this is all bogon junk
		std::cout << "ci: " << " ti: " << std::endl;
		if(ci == 0){
			std::cout << "interesting" << std::endl;
		}
		std::cout << ti.size() << std::endl;
	}

	void swap(casagrande &){}
};

#endif
