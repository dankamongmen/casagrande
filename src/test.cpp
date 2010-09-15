#include <iostream>
#include <stdlib.h>
#include <casagrande.h>

// Container -- problem 1
template <class T>
static int
p1(){
	unsigned count;

	casagrande<T> cg;
	typename casagrande<T>::const_iterator i = cg.begin();
	for(count = 0 ; i != cg.end() ; ++i){
		++count;
	}
	std::cout << "Iterated over " << count << " elements." << std::endl;
	return 0;
}

// Queue -- problem 2
static int
p2(){
	return -1;
}

// Stack -- problem 3
static int
p3(){
	return -1;
}

int main(void){
	std::cout << "Performing deque tests (problem 1)..." << std::endl;
	if(p1<int>()){
		std::cerr << "Error during deque tests!" << std::endl;
		return EXIT_FAILURE;
	}
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
	std::cout << "All tests succeeded!" << std::endl;
	return EXIT_SUCCESS;
}
