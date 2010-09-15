#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <cstddef>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
struct casagrande {
	typedef T value_type;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	typedef value_type *iterator;
	typedef const value_type *const_iterator;

	typedef ptrdiff_t difftype;
	typedef size_t sizetype;

	const_iterator begin() const { return 0; }
	const_iterator end() const { return 0; }
	sizetype size() const { return 0; }
	bool empty() const { return true; }
	sizetype max_size() const { return 0; }

	void swap(casagrande &){}
};

#endif
