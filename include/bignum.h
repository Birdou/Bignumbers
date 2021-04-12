#include <iostream>
#include <string>
#include <sstream>

#ifndef BIGNUM_H
#define BIGNUM_H

#define size_t_maxnumber  18446744073709551615
#define ssize_t_maxnumber 9223372036854775807

class bignum
{
private:
	bool signal = false;
	std::string number;
public:
	bignum()
	{
		signal = false;
		number = "0";
	}
	bignum(const ssize_t& num)     { setNumber(num); }
	bignum(const std::string& num) { setNumber(num); }
	bignum(const bignum& num)      { setNumber(num); }

	~bignum() {}

	bool getSignal() const;
	void setSignal(bool);

	const std::string& getNumber() const;
	std::string getString() const;

	void setNumber(const bignum&);
	void setNumber(const std::string&);
	void setNumber(const ssize_t&);

	void forceNumber(const std::string&);

	void plusplus();   //USO INTERNO
	void minusminus(); //USO INTERNO

	static bignum addition       (bignum&, bignum&); //USO INTERNO
	static bignum subtraction    (bignum&, bignum&); //USO INTERNO
	static bignum multiplication (bignum&, bignum&); //USO INTERNO
	static bignum division       (bignum&, bignum&); //USO INTERNO

	friend bignum operator+(const bignum&      num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }
	friend bignum operator+(const bignum&      num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }
	friend bignum operator+(const std::string& num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }
	friend bignum operator+(const bignum&      num1, const ssize_t&     num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }
	friend bignum operator+(const ssize_t&     num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }
	friend bignum operator+(const ssize_t&     num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return       addition(num1_, num2_); }

	friend bignum operator-(const bignum&      num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }
	friend bignum operator-(const bignum&      num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }
	friend bignum operator-(const std::string& num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }
	friend bignum operator-(const bignum&      num1, const ssize_t&     num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }
	friend bignum operator-(const ssize_t&     num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }
	friend bignum operator-(const ssize_t&     num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return    subtraction(num1_, num2_); }

	friend bignum operator*(const bignum&      num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	friend bignum operator*(const bignum&      num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	friend bignum operator*(const std::string& num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	friend bignum operator*(const bignum&      num1, const ssize_t&     num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	friend bignum operator*(const ssize_t&     num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	friend bignum operator*(const ssize_t&     num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }

	friend bignum operator/(const bignum&      num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }
	friend bignum operator/(const bignum&      num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }
	friend bignum operator/(const std::string& num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }
	friend bignum operator/(const bignum&      num1, const ssize_t&     num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }
	friend bignum operator/(const ssize_t&     num1, const bignum&      num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }
	friend bignum operator/(const ssize_t&     num1, const std::string& num2) { bignum num1_(num1), num2_(num2); return       division(num1_, num2_); }

	friend std::ostream& operator<<(std::ostream& stream, const bignum& num)
	{
		stream << num.getString();
		return stream;
	}
	friend std::istream& operator>>(std::istream& stream, bignum& num)
	{
		std::string str; stream >> str;
		num.setNumber(str);
		return stream;
	}

	bignum& operator=(const bignum&      v) { this->setNumber(v); return *this; }
	bignum& operator=(const std::string& v) { this->setNumber(v); return *this; }
	bignum& operator=(const ssize_t&     v) { this->setNumber(v); return *this; }

	bignum& operator++();
	bignum& operator--();

	//OPERATOR ==
	bool operator==(const bignum&      num) const;
	bool operator==(const std::string& num) const;
	bool operator==(const ssize_t&     num) const;
	//OPERATOR !=
	bool operator!=(const bignum&      num) const;
	bool operator!=(const std::string& num) const;
	bool operator!=(const ssize_t&     num) const;
	//OPERATOR <
	bool operator< (const bignum&      num) const;
	bool operator< (const std::string& num) const;
	bool operator< (const ssize_t&     num) const;
	//OPERATOR >
	bool operator> (const bignum&      num) const;
	bool operator> (const std::string& num) const;
	bool operator> (const ssize_t&     num) const;
	//OPERATOR >=
	bool operator>=(const bignum&      num) const;
	bool operator>=(const std::string& num) const;
	bool operator>=(const ssize_t&     num) const;
	//OPERATOR <=
	bool operator<=(const bignum&      num) const;
	bool operator<=(const std::string& num) const;
	bool operator<=(const ssize_t&     num) const;

	bignum& operator+=(const bignum&      num);
	bignum& operator+=(const std::string& num);
	bignum& operator+=(const ssize_t&     num);
	bignum& operator-=(const bignum&      num);
	bignum& operator-=(const std::string& num);
	bignum& operator-=(const ssize_t&     num);
	bignum& operator*=(const bignum&      num);
	bignum& operator*=(const std::string& num);
	bignum& operator*=(const ssize_t&     num);
	bignum& operator/=(const bignum&      num);
	bignum& operator/=(const std::string& num);
	bignum& operator/=(const ssize_t&     num);
};

inline bool operator==(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ == num2; }
inline bool operator!=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ != num2; }
inline bool operator< (const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ <  num2; }
inline bool operator> (const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ >  num2; }
inline bool operator>=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ >= num2; }
inline bool operator<=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ <= num2; }

std::string big_complement(const std::string& num, const size_t& len);

std::string big_invert(const std::string&);
std::string big_formatter(const std::string&);

std::string big_superscript(const std::string&);
std::string big_superscript(const ssize_t&);

std::string big_subscribed(const std::string&);
std::string big_subscribed(const ssize_t&);

std::string big_scientific(const std::string&, const ssize_t&);
std::string big_scientific(const bignum&, const ssize_t&);
std::string big_E(const std::string&, const ssize_t&);
std::string big_E(const bignum&, const ssize_t&);

bignum big_pow(const bignum&, const bignum&);
bignum big_pow(const bignum&, const std::string&);
bignum big_pow(const bignum&, const ssize_t&);

bignum big_factorial(const bignum&);
bignum big_factorial(const std::string&);
bignum big_factorial(const ssize_t&);

void big_verificationInRange(const ssize_t&);

size_t bigger(const ssize_t&, const ssize_t&);

#endif //BIGNUM_H
