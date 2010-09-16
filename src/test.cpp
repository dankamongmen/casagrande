#include <list>
#include <iostream>
#include <stdlib.h>
#include <casagrande.h>
#include <initializer_list>

template <class C,class I,class T> static int
tester(const std::initializer_list<T> il){
	unsigned count = 0;

	C cg;
	cg.push_back(il);
	for(I i = cg.begin() ; i != cg.end() ; ++i){
		std::cout << "Element #" << count << ": " << *i << std::endl;
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	C dg = cg; // test copy constructor
	count = 0;
	for(I i = dg.begin() ; i != dg.end() ; ++i){
		std::cout << "Element #" << count << ": " << *i << std::endl;
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	if(count != il.size()){
		std::cerr << "Expected " << il.size() << " elements." << std::endl;
		return -1;
	}
	return 0;
}

int main(void){
	const std::initializer_list<int> il = {0, 1, 2, 3, 4, 9, 8, 7, 6};

	std::cout << "Performing deque tests (problem 1)..." << std::endl;
	if(tester<casagrande<int>,casagrande<int>::const_iterator,int>(il)){
		std::cerr << "Error during deque tests!" << std::endl;
		return EXIT_FAILURE;
	}
	/*
	std::cout << "Performing queue tests (problem 2)..." << std::endl;
	if(p2()){
		std::cerr << "Error during queue tests!" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Performing stack tests (problem 3)..." << std::endl;
	if(p3()){
		std::cerr << "Error during stack tests!" << std::endl;
		return EXIT_FAILURE;
	}
	*/
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
