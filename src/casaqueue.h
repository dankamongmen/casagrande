#ifndef SRC_SKIPQUEUE
#define SRC_SKIPQUEUE

#include <skiplist.h>

template <class T, class C = Skiplist<T>> class Skipqueue {
private:
	C store;

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

	reference operator[](size_type n){
		return &store.block[n];
	}

	const_reference operator[](size_type n) const;

	reference front() { return store.front(); }
	const_reference front() const { return store.front(); }

	reference back() { return store.back(); }
	const_reference back() const { return store.back(); }

	iterator begin(){ return store.begin(); }
	const_iterator begin() const { return store.begin(); }

	iterator end(){ return store.end(); }
	const_iterator end() const { return store.end(); }

	size_type size() const { return store.size(); }
	bool empty() const { return store.empty(); }

	size_type max_size() const { return store.max_size(); }

	inline const value_type &pop(){
		return store.pop_back();
	}

	inline void push(const value_type &val){
		store.push_front(val);
	}

	inline void push(const std::initializer_list<value_type> ti){
		store.push_front(ti);
	}

	inline const value_type &pop_back(){
		return store.pop_back();
	}

	inline void push_front(const value_type &val){
		store.push_front(val);
	}

	inline void push_front(const std::initializer_list<value_type> ti){
		store.push_front(ti);
	}
};

#endif
