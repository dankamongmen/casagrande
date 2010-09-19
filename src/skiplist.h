#ifndef SRC_SKIPLIST
#define SRC_SKIPLIST

#include <initializer_list>

#include <iostream>

template <class T>
class Skipnode {

private:
	T obj;
	Skipnode<T> **ptrs;

public:
	Skipnode(int level,const T &obj){
		ptrs = new Skipnode<T> *[level + 1];
		this->obj = obj;
	}

	~Skipnode(){
		delete[] ptrs;
	}
};

template <class T>
class Skiplist {

public:
	typedef T *iterator;
	typedef const T *const_iterator;

	static const int levels = 1; // FIXME decay to linked list

iterator begin(){
	// FIXME
	return 0;
}

const_iterator begin() const {
	// FIXME
	return 0;
}

iterator end(){
	// FIXME
	return 0;
}

const_iterator end() const {
	// FIXME
	return 0;
}

T& operator[](const int idx){
	// FIXME
	return fixme;
}

T& pop(){
	// FIXME
	return fixme;
}

void push(const T &ref){
	Skipnode<T>(levels,ref);
	// FIXME
	std::cout << "pushed: " << ref << std::endl;
}

void push(const std::initializer_list<T> il){
	const_iterator cil;

	for(cil = il.begin() ; cil != il.end() ; ++cil){
		push(*cil);
	}
}

friend std::ostream & operator<<(std::ostream & out,const Skiplist &sl){
	out << sl.fixme; // FIXME
	return out;
}

private:
	T fixme;

};

#endif
