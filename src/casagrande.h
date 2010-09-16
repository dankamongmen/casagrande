#ifndef CASAGRANDE_CASAGRANDE
#define CASAGRANDE_CASAGRANDE

#include <cstring>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

// Adapted from Austern 98's "Trivial Container" (p 71)
template <class T>
class casagrande {
	unsigned elems,telems;
	T *block;

public:
	casagrande(){ telems = elems = 0; block = 0; }

	// Copy constructor
	casagrande(const casagrande &src){
		if((block = (T *)malloc(sizeof(*block) * src.elems)) == 0){
			throw std::bad_alloc();
		}
		memcpy(block,src.block,sizeof(*block) * src.elems);
		telems = src.telems;
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
		telems = src.telems;
		return *this;
	}

	reference operator[](size_type n){
		return &block[n];
	}

	const_reference operator[](size_type n) const;

	reference front() { return operator[](0); }
	const_reference front() const { return operator[](0); }

	reference back() { return operator[](elems); }
	const_reference back() const { return operator[](elems); }

	iterator begin(){ return &block[0]; }
	const_iterator begin() const { return &block[0]; }

	iterator end(){ return &block[elems]; }
	const_iterator end() const { return &block[elems]; }

	size_type size() const { return elems; }
	bool empty() const { return !elems; }

	size_type max_size() const { return telems; }

	inline void push_back(const value_type &val){
		T *tmp;

		if(elems == telems){
			if((tmp = (T *)realloc(block,sizeof(*tmp) * (elems + 1))) == 0){
				throw std::bad_alloc();
			}
			telems = elems + 1;
		}
		block = tmp;
		block[elems++] = val;
	}

	inline void push_back(const std::initializer_list<value_type> ti){
		const_iterator cil;

		for(cil = ti.begin() ; cil != ti.end() ; ++cil){
			push_back(*cil);
		}
	}

	inline void push(const value_type &val){ push_back(val); }
	inline void push(const std::initializer_list<value_type> ti){ push_back(ti); }

	inline const value_type &pop_back(){
		if(elems){
			return &block[--elems];
		}
		throw std::range_error();
	}

	inline const value_type &pop(){ return pop_back(); }

	inline void push_front(const value_type &val){
		T *tmp;

		if(elems >= telems){
			if((tmp = (T *)realloc(block,sizeof(*tmp) * (elems + 1))) == 0){
				throw std::bad_alloc();
			}
			telems = elems + 1;
		}
		block = tmp;
		if(elems){
			memmove(block + 1,block,sizeof(*block) * elems);
		}
		++elems;
		block[0] = val;
	}

	inline void push_front(const std::initializer_list<value_type> ti){
		const_iterator cil;

		for(cil = ti.begin() ; cil != ti.end() ; ++cil){
			push_front(*cil);
		}
	}

	inline const value_type &pop_front(){
		if(elems){
			value_type *r = &block[0];
			if(--elems){ // FIXME ugh horrible
				memmove(block,block + 1,sizeof(*block) * elems);
			}
			return r;
		}
		throw std::range_error();
	}

};

#endif
