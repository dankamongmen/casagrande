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

typedef typename C::iterator iterator;
typedef typename C::const_iterator const_iterator;

typedef ptrdiff_t difference_type;
typedef size_t size_type;

reference front() { return store.front(); }
const_reference front() const { return store.front(); }

iterator begin(){ return store.begin(); }
const_iterator begin() const { return store.begin(); }

iterator end(){ return store.end(); }
const_iterator end() const { return store.end(); }

size_type size() const { return store.size(); }
bool empty() const { return store.empty(); }

size_type max_size() const { return store.max_size(); }

inline void pop(){
	store.pop_front();
}

inline void push(const value_type &val){
	store.push_back(val);
}

inline void push(const std::initializer_list<value_type> ti){
	store.push_back(ti);
}

friend std::ostream& operator<<(std::ostream& out,const Skipqueue& sq){
	out << sq.store;
	return out;
}

};

#endif
