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

T & value(){
	return obj;
}

friend std::ostream & operator<<(std::ostream & out,const Skipnode &sn){
	out << sn.obj;
	return out;
}

};

template <class T>
class Skiplist {

public:
Skiplist(){
	head = 0;
}

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
	return head.value();
}

T& pop(){
	// FIXME
	return head->value();
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
	if(sl.head){
		out << sl.head; // FIXME
	}
	return out;
}

private:
	Skipnode<T> * head;

};

#endif
