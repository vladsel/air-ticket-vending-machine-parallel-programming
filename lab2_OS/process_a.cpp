#include "process_a.h"

#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>

size_t A::requestSale(const size_t choice) {
	if (choice == 0) { // to turn on the machine
		if (turned_on == true)
			std::cout << "\nThe machine is working now, you can buy a ticket\n" << std::endl;
		else {
			if (choice == 0) {
				turned_on = true;
				std::cout << "\nThe machine was successfully turned on, you can buy a ticket\n" << std::endl;
			}
			else
				std::cout << "\nThe machine wasn't turned on, you need to switch { 0 } to turn it on\n" << std::endl;
		}
		return 0;
	}

	if (turned_on == true) { // to make a request to buy a ticket	
		if (choice <= tickets.size()) {
			std::cout << "Buy a ticket to: " << tickets[choice - 1].first << "; ticket price: "
				<< tickets[choice - 1].second << " penny" << std::endl;
			return PENNY_MAX - tickets[choice - 1].second;
		}
		else
			std::cout << "\nYour choice is incorrect, please choose the correct option\n" << std::endl;
	}
	else
		std::cout << "\nThe machine is off, you need to switch { 0 } to turn it on\n" << std::endl;
	return 0;
}

size_t A::addTicketGetIndex(const std::string place, const size_t price) {
	if (price <= PENNY_MAX && !place.empty()) {
		tickets.push_back(std::make_pair(place, price));
		return tickets.size() - 1;
	}
	else
		throw std::invalid_argument("\nThe change can't be more than 100\n");
}

std::vector<std::pair<std::string, size_t>> A::getTickets() const {
	return tickets;
}

void A::runThreadA(B &procB, std::binary_semaphore &smphSig_AtoB, std::binary_semaphore &smphSig_BtoA) {
	std::cout << "\nThread | A |: started work" << std::endl;

	std::random_device rand;
	std::minstd_rand linear(rand());
	std::uniform_int_distribution<size_t> range(1, 5);

	requestSale(0); // turn on the machine
	size_t ticket_change = 0;

	while (1) {
		smphSig_BtoA.acquire();

		if (procB.isBankEmptyProcessB()) // if bank empty = exit
			break;

		std::cout << "Thread | A |: ";
		ticket_change = requestSale(range(linear)); // buy ticket request
		procB.setChange(ticket_change); // set change to process B
		std::cout << "Thread | A |: Change sent to thread B" << std::endl;

		smphSig_AtoB.release();

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "\nThread | A |: finished work" << std::endl;
}

void A::createThreadA(B &procB, std::binary_semaphore &smphSig_AtoB, std::binary_semaphore &smphSig_BtoA) {
	if (threadA.joinable())
		threadA.detach();
	else {
		threadA = std::thread([this, &procB, &smphSig_AtoB, &smphSig_BtoA]() { // create thread A
			runThreadA(procB, smphSig_AtoB, smphSig_BtoA);
		});
	}
}

void A::joinThreadA() { // wait thread A
	if (threadA.joinable())
		threadA.join();
}
