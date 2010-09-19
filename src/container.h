#ifndef SRC_CONTAINER
#define SRC_CONTAINER

#include <initializer_list>

#include <iostream>

template <class T>
class Container {

public:
	typedef T *iterator;
	typedef const T *const_iterator;

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

const T& pop(){
	// FIXME
	return fixme;
}

void push(const T &ref){
	// FIXME
	std::cout << "pushed: " << ref << std::endl;
}

void push(const std::initializer_list<T> il){
	const_iterator cil;

	for(cil = il.begin() ; cil != il.end() ; ++cil){
		push(*cil);
	}
}

private:
	T fixme;

};

#endif
