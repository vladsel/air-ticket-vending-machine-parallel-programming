#include "process_b.h"

#include <stdexcept>
#include <iostream>
#include <chrono>

#pragma warning( disable : 26812 ) // to disable enum warning
#pragma warning( disable : 4018 )

void B::setChange(const size_t _change) {
	if (_change <= PENNY_MAX)
		change = _change;
	else
		throw std::invalid_argument("\nThe change can't be more than 100\n");
}

size_t B::getChange() const {
	return change;
}

Bank B::getBank() const {
	return coins;
}

void B::printChange() {
	std::cout << "Change is: " << change << " penny" << std::endl;
}

Bank B::countChange() {
	Bank report;
	size_t i = 0;

	while (change > 0) {

		if (denominations.at(i) < 0)
			throw std::runtime_error("\nEnum pennyDenomination const is < 0\n");

		while (change >= denominations.at(i)) {
			if (coins.getPennyByDenomination(denominations.at(i)) > 0) {
				coins.setPennyByDenomination(coins.getPennyByDenomination(denominations.at(i)) - 1, denominations.at(i));
				report.setPennyByDenomination(report.getPennyByDenomination(denominations.at(i)) + 1, denominations.at(i));
				change -= denominations.at(i);
			}
			else {
				i++;
				if (i == denominations.size() && change > 0) {
					std::cout << "Sorry, but not enough change in the machine for the ticket, please try later" << std::endl;
					coins += report;
					flag++;
					if (flag == 7) // impossible to pay change (if flag == 7)
						coins = Bank();
					return Bank();
				}
			}
		}

		i++;
	}

	flag = 0;
	return report;
}

bool B::isBankEmptyProcessB() {
	return coins.IsBankEmpty();
}

void B::runThreadB(std::binary_semaphore &smphSig_BtoA, std::binary_semaphore &smphSig_AtoB) {
	std::cout << "\nThread | B |: started work" << std::endl;
	Bank ticket_change_bank; // temp calculated change in denomiinations

	while (1) {
		smphSig_AtoB.acquire();

		std::cout << "Thread | B |: ";
		printChange(); // print change
		ticket_change_bank = countChange(); // calculated change in denomiinations
		std::cout << ticket_change_bank; // print calculated change in denomiinations

		smphSig_BtoA.release();

		if (isBankEmptyProcessB()) // if bank empty = exit
			break;

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "\nThread | B |: finished work" << std::endl;
}

void B::createThreadB(std::binary_semaphore &smphSig_BtoA, std::binary_semaphore &smphSig_AtoB) {
	if (threadB.joinable())
		threadB.detach();
	else {
		threadB = std::thread([this, &smphSig_BtoA, &smphSig_AtoB]() { // create thread B
			runThreadB(smphSig_BtoA, smphSig_AtoB);
		});
	}
}

void B::joinThreadB() { // wait thread B
	if (threadB.joinable())
		threadB.join();
}
