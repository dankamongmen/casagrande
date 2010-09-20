#ifndef SRC_SKIPLIST
#define SRC_SKIPLIST

#include <map>
#include <stdexcept>
#include <initializer_list>

template <class T>
class Skipnode { // FIXME make internal to Skiplist?

private:
T obj;
Skipnode<T> **ptrs;

public:
Skipnode(int level,const T& obj){
	ptrs = new Skipnode<T> *[level + 1];
	do{
		ptrs[level] = 0;
	}while(level--);
	this->obj = obj;
}

~Skipnode(){
	delete[] ptrs;
}

T& operator*(){
	return obj;
}

const T& operator*() const {
	return obj;
}

Skipnode<T> *ptrat(int level){
	return ptrs[level];
}

Skipnode<T> **lnptrat(int level){
	return &ptrs[level];
}

friend std::ostream& operator<<(std::ostream& out,const Skipnode& sn){
	return out << sn.obj;
}

};

template <class T,bool MTSafe = false>
class Skiplist {

class SkipIterator{
public:
SkipIterator(Skipnode<T> *p) : sn(p){}
~SkipIterator(){}

SkipIterator& operator=(const SkipIterator& other){
	sn = other.sn;
	return *this;
}

bool operator==(const SkipIterator& other) const {
	return sn == other.sn;
}

bool operator!=(const SkipIterator& other) const {
	return sn != other.sn;
}

SkipIterator& operator++(){
	if(sn != NULL){
		sn = sn->ptrat(0);
	}
	return *this;
}

T& operator*() const {
	return **sn;
}

T* operator->() const {
	return &*(Skiplist<T>::SkipIterator)*this;
}

private:
Skipnode<T> *sn;
};

class ConstSkipIterator{
public:
ConstSkipIterator(Skipnode<T> *p) : sn(p){}
~ConstSkipIterator(){}

ConstSkipIterator& operator=(const ConstSkipIterator& other){
	sn = other.sn;
	return *this;
}

bool operator==(const ConstSkipIterator& other) const {
	return sn == other.sn;
}

bool operator!=(const ConstSkipIterator& other) const {
	return sn != other.sn;
}

bool operator!=(ConstSkipIterator& other) const {
	return sn != other.sn;
}

ConstSkipIterator& operator++(){
	if(sn != NULL){
		sn = sn->ptrat(0);
	}
	return *this;
}

const T& operator*() const {
	return **sn;
}

T* operator->() const {
	return &*(Skiplist<T>::ConstSkipIterator)*this;
}

private:
Skipnode<T> *sn;
};

private:
uintmax_t uuid;

// We need these to implement an ordering on Skiplists, so that we can use
// a std::map to track external locks, since we regularly need to lock at
// instance-scope, but have only a constant instance...is there a better way?
static uintmax_t uuid_counter;
static pthread_mutex_t lock_counter;
static std::map<uintmax_t,pthread_mutex_t> locks;

size_t nodes;
Skipnode<T> *head;
Skipnode<T> **link;
static const int levels = 1; // FIXME decay to linked list

static void inline safelock(pthread_mutex_t *lock){
	if(MTSafe){
		if(pthread_mutex_lock(lock)){
			throw std::runtime_error("pthread_mutex_lock()");
		}
	}
}

static void inline safelock(const Skiplist &sl){
	safelock(&locks[sl.uuid]);
}

static void inline safeunlock(pthread_mutex_t *lock){
	if(MTSafe){
		if(pthread_mutex_unlock(lock)){
			throw std::runtime_error("pthread_mutex_unlock()");
		}
	}
}

static void inline safeunlock(const Skiplist &sl){
	safeunlock(&locks[sl.uuid]);
}

static void inline dirtyunlock(pthread_mutex_t *lock){
	if(MTSafe){
		pthread_mutex_unlock(lock);
	}
}

static void inline dirtyunlock(const Skiplist &sl){
	dirtyunlock(&locks[sl.uuid]);
}

static void destroy(Skipnode<T> *head){
	Skipnode<T> *sn;

	while( (sn = head) ){
		head = sn->ptrat(0);
		delete sn;
	}
}

public:
Skiplist(){
	nodes = 0;
	head = 0;
	link = &head;
	safelock(&lock_counter);
	uuid = uuid_counter++;
	safeunlock(&lock_counter);
	if(pthread_mutex_init(&locks[uuid],NULL)){
		throw std::bad_alloc();
	}
}

// No actions may be performed while (or once) the destructor is invoked!
~Skiplist(){
	pthread_mutex_destroy(&locks[uuid]);
	destroy(head);
}

// Copy constructor
Skiplist(const Skiplist& src){
	nodes = 0;
	head = 0;
	link = &head;
	for(const_iterator i = src.begin() ; i != src.end() ; ++i){
		push_back(*i);
	}
	safelock(&lock_counter);
	uuid = uuid_counter++;
	safeunlock(&lock_counter);
}

// Assignment
Skiplist& operator=(const Skiplist& src){
	Skipnode<T> *ohead = 0;
	Skipnode<T> **olink = &ohead;

	try{
		for(const_iterator i = src.begin() ; i != src.end() ; ++i){
			Skipnode<T> *tmp = new Skipnode<T>(levels,*i);
			*olink = tmp;
			olink = tmp->lnptrat(0);
		}
	}catch(...){
		destroy(ohead);
		throw;
	}
	destroy(head);
	head = ohead;
	link = &head;
	nodes = 0;
	// do not take on the new uuid!
	return *this;
}

// Relationals (needed by map)
bool operator<(const Skiplist& src){
	return uuid < src.uuid;
}

size_t size() const {
	return nodes;
}

bool empty() const {
	return nodes == 0;
}

typedef T *pointer;
typedef const T *const_pointer;
typedef T& reference;
typedef const T& const_reference;
typedef SkipIterator iterator;
typedef ConstSkipIterator const_iterator;
typedef ptrdiff_t difference_type;
typedef size_t size_type;

iterator begin(){
	return iterator(head);
}

const_iterator begin() const {
	return const_iterator(head);
}

iterator end(){
	return iterator(0);
}

const_iterator end() const {
	return const_iterator(0);
}

T& operator[](const int idx){
	iterator i;
	safelock(*this);
	try{
		int x = idx;

	       	i = begin();
		while(i != end() && x--){
			++i;
		}
		if(i == end()){
			throw std::range_error("out-of-bounds");
		}
	}catch(...){
		dirtyunlock(*this);
		throw;
	}
	safeunlock(*this);
	return *i;
}

// FIXME ought be O(1) for deque, ack!
void pop_back(){
	Skipnode<T> **prev;

	safelock(*this);
	try{
		if(*(prev = &head) == 0){
			throw std::range_error("underflow");
		}
		while((*prev)->ptrat(0)){
			prev = (*prev)->lnptrat(0);
		}
		link = prev;
		T& ret = ***prev;
		delete(*prev);
		*prev = 0;
		--nodes;
	}catch(...){
		dirtyunlock(*this);
		throw;
	}
	safeunlock(*this);
}

// Undefined behavior when empty
T& front(){
	return **head;
}

void pop_front(){
	Skipnode<T> **prev,*tmp;

	safelock(*this);
	try{
		if(*(prev = &head) == 0){
			throw std::range_error("underflow");
		}
		if(link == head->lnptrat(0)){
			link = &head;
		}
		tmp = *prev;
		*prev = (*prev)->ptrat(0);
		delete(tmp);
		--nodes;
	}catch(...){
		dirtyunlock(*this);
		throw;
	}
	safeunlock(*this);
}

void push_back(const T& ref){
	Skipnode<T> *sn = new Skipnode<T>(levels,ref);
	safelock(*this);
	*link = sn;
	link = sn->lnptrat(0);
	++nodes;
	safeunlock(*this);
}

// Individual pushes are locked, but not the list as a whole.
void push_back(const std::initializer_list<T> il){
	const T *cil;

	for(cil = il.begin() ; cil != il.end() ; ++cil){
		push_back(*cil);
	}
}

void push_front(const T& ref){
	Skipnode<T> *sn = new Skipnode<T>(levels,ref);
	safelock(*this);
	if((*sn->lnptrat(0) = head) == 0){
		link = sn->lnptrat(0);
	}
	head = sn;
	++nodes;
	safeunlock(*this);
}

// Individual pushes are locked, but not the list as a whole.
void push_front(const std::initializer_list<T> il){
	const T *cil = il.end();

	while(cil-- != il.begin()){
		push_front(*cil);
	}
}

// FIXME ugh!
void push_front_rev(const std::initializer_list<T> il){
	const T *cil = il.begin();

	while(cil != il.end()){
		push_front(*cil++);
	}
}

void pop(){
	pop_front();
}

void push(const T& ref){
	return push_front(ref);
}

void push(const std::initializer_list<T> il){
	return push_front(il);
}

friend std::ostream& operator<<(std::ostream&  out,const Skiplist& sl){
	Skipnode<T> *sn;

	safelock(sl);
	try{
		if(MTSafe){
			out << "*LOCKED* ";
		}
		for(sn = sl.head ; sn ; sn = sn->ptrat(0)){
			if(sn != sl.head){
				out << ", ";
			}
			out << *sn;
		}
		if(MTSafe){
			out << " *LOCKED*";
		}
	}catch(...){
		dirtyunlock(sl);
		throw;
	}
	safeunlock(sl);
	return out;
}

};

template <class T,bool MTSafe> std::map<uintmax_t,pthread_mutex_t> Skiplist<T,MTSafe>::locks;
template <class T,bool MTSafe> pthread_mutex_t Skiplist<T,MTSafe>::lock_counter
	= PTHREAD_MUTEX_INITIALIZER;
template <class T,bool MTSafe> uintmax_t Skiplist<T,MTSafe>::uuid_counter = 0;

#endif
