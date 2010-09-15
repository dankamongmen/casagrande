#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <cstddef>
#include <initializer_list>

#include <iostream>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
class casagrande {
	unsigned elems;

public:
	casagrande(){ elems = 0; }
	~casagrande(){}

	typedef T value_type;

	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	typedef value_type *iterator;
	typedef const value_type *const_iterator;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	reference operator[](size_type n){
		std::cout << "n: " << n << std::endl;
		return 0; // FIXME
	}

	const_reference operator[](size_type n) const;

	reference front() { return operator[](0); }
	const_reference front() const { return operator[](0); }

	reference back() { return operator[](elems - 1); }
	const_reference back() const { return operator[](elems - 1); }

	iterator begin(){ return 0; } // FIXME
	const_iterator begin() const { return 0; } // FIXME

	// FIXME
	iterator end(){ return 0; }
	const_iterator end() const { return 0; }

	size_type size() const { return elems; }
	bool empty() const { return !elems; }

	// FIXME
	size_type max_size() const { return elems; }

	iterator insert(const_iterator ci,const value_type &val){
		if(ci){
			// FIXME
			std::cout << "val: " << val << std::endl;
		}
		return 0;
	}

	void insert(const_iterator,size_type,const value_type &);

	void insert(const_iterator ci,const std::initializer_list<value_type> ti){
		const_iterator cil;

		for(cil = ti.begin() ; cil != ti.end() ; ++cil){
			insert(ci,*cil);
		}
	}

	void swap(casagrande &){}
};

#endif
