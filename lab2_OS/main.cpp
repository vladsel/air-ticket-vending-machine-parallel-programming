#include "process_a.h"
//#include "process_b.h"
//#include "bank.h"

#include <iostream>
#include <stdexcept>
//#include <semaphore>

int main() { // critical section is change in class B
	try {
		A procA; // process A
		B procB(Bank(50, 25, 20, 15, 10, 5)); // process B with given bank

		std::binary_semaphore smphSig_AtoB { 0 }; // semaphore process A to process B
		std::binary_semaphore smphSig_BtoA { 1 }; // semaphore process B to process A

		std::cout << "\nInitial bank:\n" << std::endl; 
		std::cout << procB.getBank(); 

		procA.createThreadA(procB, smphSig_AtoB, smphSig_BtoA); // create thread A
		procB.createThreadB(smphSig_BtoA, smphSig_AtoB); // create thread B

		procA.joinThreadA(); // wait thread A
		procB.joinThreadB(); // wait thread B

		std::cout << "\nBank is empty\n" << std::endl;

		return 0;
	}
	catch (const std::exception &ex) {
		std::cout << "\n" << ex.what() << std::endl;
		std::terminate();
	}
	catch (...) {
		std::cout << "\nUnknow error\n" << std::endl;
		std::terminate();
	}
}
