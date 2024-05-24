#pragma once

#include "process_b.h"

#include <string>
//#include <vector>
//#include <thread>
//#include <semaphore>

class A { // class determines the fact of sale and the amount of change

public:
	A() = default;
	~A() = default;

	size_t requestSale(const size_t choice);
	size_t addTicketGetIndex(const std::string place, const size_t price); // to add ticket price, method returns ticket index in vector
	std::vector <std::pair <std::string, size_t>> getTickets() const;

	void runThreadA(B &procB, std::binary_semaphore &smphSig_AtoB, std::binary_semaphore &smphSig_BtoA);
	void createThreadA(B &procB, std::binary_semaphore &smphSig_AtoB, std::binary_semaphore &smphSig_BtoA);
	void joinThreadA();

	void releaseSemaphore();
	void acquireSemaphore();

private:
	bool turned_on = false;
	std::vector <std::pair <std::string, size_t>> tickets // tickets price
	{ 
		{"Kyiv", 28},
		{"moscowia", 37},
		{"London", 50},
		{"Berlin", 77},
		{"Paris", 91}
	}; 
	/*
	* [0] = buy a ticket to Kyiv for 28 penny
	* [1] = buy a ticket to moscowia for 37 penny
	* [2] = buy a ticket to London for 50 penny
	* [3] = buy a ticket to Berlin for 77 penny
	* [4] = buy a ticket to Paris for 91 penny
	*/

	std::thread threadA;
};
