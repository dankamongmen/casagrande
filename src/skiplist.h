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
	do{
		ptrs[level] = 0;
	}while(level--);
	this->obj = obj;
}

~Skipnode(){
	delete[] ptrs;
}

T & value(){
	return obj;
}

Skipnode<T> * ptrat(int level){
	return ptrs[level];
}

Skipnode<T> ** lnptrat(int level){
	return &ptrs[level];
}

friend std::ostream & operator<<(std::ostream & out,const Skipnode &sn){
	return out << sn.obj;
}

};

template <class T>
class Skiplist {

public:
Skiplist(){
	head = 0;
	link = &head;
}

~Skiplist(){
	Skipnode<T> *sn;

	while( (sn = *link) ){
		*link = sn->ptrat(0);
		delete sn;
	}
}

typedef T *iterator;
typedef const T *const_iterator;

static const int levels = 1; // FIXME decay to linked list

iterator begin(){
	return 0; // FIXME
}

const_iterator begin() const {
	return 0; // FIXME
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
	Skipnode<T> *sn = new Skipnode<T>(levels,ref);
	*link = sn; // FIXME
	link = sn->lnptrat(0);
	std::cout << "pushed: " << ref << std::endl;
}

void push(const std::initializer_list<T> il){
	const_iterator cil;

	for(cil = il.begin() ; cil != il.end() ; ++cil){
		push(*cil);
	}
}

friend std::ostream & operator<<(std::ostream & out,const Skiplist &sl){
	Skipnode<T> *sn;

	for(sn = sl.head ; sn ; sn = sn->ptrat(0)){
		out << *sn;
	}
	return out;
}

private:
	Skipnode<T> * head;
	Skipnode<T> ** link;

};

#endif
