#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <cstddef>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
struct casagrande {
	typedef T vtype;

	typedef vtype *pointer;
	typedef const vtype *const_pointer;
	typedef vtype &reference;
	typedef const vtype &const_reference;

	typedef vtype *iterator;
	typedef const vtype *const_iterator;

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
