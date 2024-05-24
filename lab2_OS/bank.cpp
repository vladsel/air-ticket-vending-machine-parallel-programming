#include "bank.h"

#include <iostream>

#pragma warning( disable : 26812 ) // to disable enum warning

Bank &Bank::operator=(const Bank &other) {
	penny1 = other.penny1;
	penny2 = other.penny2;
	penny5 = other.penny5;
	penny10 = other.penny10;
	penny25 = other.penny25;
	penny50 = other.penny50;
	return *this;
}

void Bank::setPenny1(const size_t _penny1) {
	penny1 = _penny1;
}

void Bank::setPenny2(const size_t _penny2) {
	penny2 = _penny2;
}

void Bank::setPenny5(const size_t _penny5) {
	penny5 = _penny5;
}

void Bank::setPenny10(const size_t _penny10) {
	penny10 = _penny10;
}

void Bank::setPenny25(const size_t _penny25) {
	penny25 = _penny25;
}

void Bank::setPenny50(const size_t _penny50) {
	penny50 = _penny50;
}

size_t Bank::getPenny1() const {
	return penny1;
}

size_t Bank::getPenny2() const {
	return penny2;
}

size_t Bank::getPenny5() const {
	return penny5;
}

size_t Bank::getPenny10() const {
	return penny10;
}

size_t Bank::getPenny25() const {
	return penny25;
}

size_t Bank::getPenny50() const {
	return penny50;
}

void Bank::setPennyByDenomination(const size_t _penny, const size_t denomination) {
	switch (denomination) {
		case PENNY1:
			setPenny1(_penny);
			break;
		case PENNY2:
			setPenny2(_penny);
			break;
		case PENNY5:
			setPenny5(_penny);
			break;
		case PENNY10:
			setPenny10(_penny);
			break;
		case PENNY25:
			setPenny25(_penny);
			break;
		case PENNY50:
			setPenny50(_penny);
			break;
		default:
			break;
	}
}

size_t Bank::getPennyByDenomination(const size_t denomination) const {
	switch (denomination) {
		case PENNY1:
			return getPenny1();
		case PENNY2:
			return getPenny2();
		case PENNY5:
			return getPenny5();
		case PENNY10:
			return getPenny10();
		case PENNY25:
			return getPenny25();
		case PENNY50:
			return getPenny50();
		default:
			break;
	}
	return 0;
}

bool Bank::IsBankEmpty() {
	return penny1 == 0 && penny2 == 0 && penny5 == 0 && penny10 == 0 && penny25 == 0 && penny50 == 0;
}

void Bank::printBank() {
	size_t temp = 0;
	for (const auto &it : denominations) {
		temp = getPennyByDenomination(it);
		if (temp > 0)
			std::cout << "Denomination is: " << it << "; amount is: " << temp << std::endl;
	}
	std::cout << std::endl;
}

Bank &Bank::operator+=(const Bank other) {
	penny1 += other.penny1;
	penny2 += other.penny2;
	penny5 += other.penny5;
	penny10 += other.penny10;
	penny25 += other.penny25;
	penny50 += other.penny50;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const Bank bank) {
	size_t temp = 0;
	for (const auto &it : denominations) {
		temp = bank.getPennyByDenomination(it);
		if (temp > 0)
			out << "Denomination is: " << it << "; amount is: " << temp << std::endl;
	}
	out << std::endl;
	return out;
}
