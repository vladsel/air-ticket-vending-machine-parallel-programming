#pragma once

#include "bank.h"

#include <thread>
#include <semaphore>

class B { // process B to determine an amount of coins for the change

public:
	B() = default;
	~B() = default;
	B(Bank _coins) : coins(_coins) {}

	void setChange(const size_t _change);
	size_t getChange() const;
	Bank getBank() const;

	void printChange();
	Bank countChange();

	bool isBankEmptyProcessB();

	void runThreadB(std::binary_semaphore &smphSig_BtoA, std::binary_semaphore &smphSig_AtoB);
	void createThreadB(std::binary_semaphore &smphSig_BtoA, std::binary_semaphore &smphSig_AtoB);
	void joinThreadB();

private:
	// PENNY1 = 50, PENNY2 = 25, PENNY5 = 20, PENNY10 = 15, PENNY25 = 10, PENNY50 = 5
	Bank coins;
	size_t flag = 0; // flag indicating the impossibility of paying change (if flag == 7)

	size_t change = 0; // critical section

	std::thread threadB;
};
