#ifndef BIG_UNSIGNED_HPP
#define BIG_UNSIGNED_HPP

#include <string>

class BigUnsigned{
private:
	std::string digits;
public:
	BigUnsigned();
	BigUnsigned(const std::string& s);
	~BigUnsigned();
	BigUnsigned operator+(const BigUnsigned& a, const BigUnsigned& b);
	BigUnsigned operator*(const BigUnsigned& a, const BigUnsigned& b);
};

#endif 
