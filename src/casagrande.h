#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <cstring>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
class casagrande {
	unsigned elems;
	T *block; // FIXME

public:
	casagrande(){ elems = 0; block = 0; }

	// Copy constructor
	casagrande(const casagrande &src){
		if((block = (T *)malloc(sizeof(*block) * src.elems)) == 0){
			throw std::bad_alloc();
		}
		memcpy(block,src.block,sizeof(*block) * src.elems);
		elems = src.elems;
	}

	~casagrande(){ free(block); }

	typedef T value_type;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	typedef value_type *iterator;
	typedef const value_type *const_iterator;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	casagrande & operator=(const casagrande &src){
		T *tmp;

		if((tmp = (T *)malloc(sizeof(*block) * src.elems)) == 0){
			throw std::bad_alloc();
		}
		free(block);
		block = tmp;
		memcpy(block,src.block,sizeof(*block) * src.elems);
		elems = src.elems;
		return *this;
	}

	reference operator[](size_type n){
		return &block[n]; // FIXME
	}

	const_reference operator[](size_type n) const;

	reference front() { return operator[](0); }
	const_reference front() const { return operator[](0); }

	reference back() { return operator[](elems); }
	const_reference back() const { return operator[](elems); }

	iterator begin(){ return &block[0]; } // FIXME
	const_iterator begin() const { return &block[0]; } // FIXME

	// FIXME
	iterator end(){ return &block[elems]; }
	const_iterator end() const { return &block[elems]; } // FIXME

	size_type size() const { return elems; }
	bool empty() const { return !elems; }

	// FIXME
	size_type max_size() const { return elems; }

	void push_back(const value_type &val){
		T *tmp;

		if((tmp = (T *)realloc(block,sizeof(*tmp) * (elems + 1))) == 0){
			throw std::bad_alloc();
		}
		block = tmp;
		block[elems++] = val;
	}

	void push_back(const std::initializer_list<value_type> ti){
		const_iterator cil;

		for(cil = ti.begin() ; cil != ti.end() ; ++cil){
			push_back(*cil);
		}
	}

	void swap(casagrande &){}
};

#endif
