#pragma once

#include <vector>
#include <ostream>

const size_t PENNY_MAX = 100;

enum pennyDenomination {
	PENNY1 = 1,
	PENNY2 = 2,
	PENNY5 = 5,
	PENNY10 = 10,
	PENNY25 = 25,
	PENNY50 = 50,
};

const std::vector <pennyDenomination> denominations { PENNY50, PENNY25, PENNY10, PENNY5, PENNY2, PENNY1 };

class Bank { // class to store and manipulate coins

public:
	Bank() = default;
	~Bank() = default;
	Bank(const Bank &other) : penny1(other.penny1), penny2(other.penny2), penny5(other.penny5),
		penny10(other.penny10), penny25(other.penny25), penny50(other.penny50) { }
	Bank(const size_t _penny1, const size_t _penny2, const size_t _penny5, const size_t _penny10,
		 const size_t _penny25, const size_t _penny50) : penny1(_penny1), penny2(_penny2),
		penny5(_penny5), penny10(_penny10), penny25(_penny25), penny50(_penny50) { }

	Bank &operator=(const Bank &other);

	void setPenny1(const size_t _penny1);
	void setPenny2(const size_t _penny2);
	void setPenny5(const size_t _penny5);
	void setPenny10(const size_t _penny10);
	void setPenny25(const size_t _penny25);
	void setPenny50(const size_t _penny50);

	size_t getPenny1() const;
	size_t getPenny2() const;
	size_t getPenny5() const;
	size_t getPenny10() const;
	size_t getPenny25() const;
	size_t getPenny50() const;

	void setPennyByDenomination(const size_t _penny, const size_t denomination);
	size_t getPennyByDenomination(const size_t denomination) const;

	bool IsBankEmpty();

	void printBank();
	friend std::ostream &operator<<(std::ostream &out, const Bank bank);
	Bank &operator+=(const Bank other);

private: // penny amount
	size_t penny1 = 0;
	size_t penny2 = 0;
	size_t penny5 = 0;
	size_t penny10 = 0;
	size_t penny25 = 0;
	size_t penny50 = 0;
};
