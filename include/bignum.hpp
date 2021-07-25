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

	static bignum addition       (bignum&, bignum&);
	static bignum subtraction    (bignum&, bignum&);
	static bignum multiplication (bignum&, bignum&);
	static bignum division       (bignum&, bignum&);
	static bignum modulo         (bignum&, bignum&);

	bool equ(const bignum&) const;
	bool neq(const bignum&) const;
	bool lss(const bignum&) const;
	bool gtr(const bignum&) const;
	bool leq(const bignum&) const;
	bool geq(const bignum&) const;

public:
	bignum()
	{
		signal = false;
		number = "0";
	}

	bignum(const bignum& num)      { setNumber(num); }
	void setNumber(const bignum&);

	bignum(const std::string& num) { setNumber(num); }
	void setNumber(const std::string&);

	bignum(const ssize_t& num)     { setNumber(num); }
	void setNumber(const ssize_t&);

	~bignum(){}

	static void test(const ssize_t&);

	size_t size() { return signal ? number.size() + 1 : number.size(); }
	size_t length() { return size(); }

	std::string::iterator begin() { return number.begin(); }
	std::string::iterator end() { return number.end(); }

	bool getSignal() const;
	void setSignal(bool);

	const std::string& getNumber() const;
	std::string getString() const;

	const char& operator[](size_t) const;

	void forceNumber(const std::string&);

	void plusplus();
	void minusminus();

	template<typename t1, typename t2>
	friend bignum operator+(const t1& num1, const t2& num2) { bignum num1_(num1), num2_(num2); return addition(num1_, num2_); }
	
	template<typename t1, typename t2>
	friend bignum operator-(const t1& num1, const t2& num2) { bignum num1_(num1), num2_(num2); return subtraction(num1_, num2_); }
	
	template<typename t1, typename t2>
	friend bignum operator*(const t1& num1, const t2& num2) { bignum num1_(num1), num2_(num2); return multiplication(num1_, num2_); }
	
	template<typename t1, typename t2>
	friend bignum operator/(const t1& num1, const t2& num2) { bignum num1_(num1), num2_(num2); return division(num1_, num2_); }
	
	template<typename t1, typename t2>
	friend bignum operator%(const t1& num1, const t2& num2) { bignum num1_(num1), num2_(num2); return modulo(num1_, num2_); }

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

	template<typename type>
	bignum& operator=(const type& value) { this->setNumber(value); return *this; }

	bignum& operator++();
	bignum& operator--();
	bignum operator++(int);
	bignum operator--(int);

	template<typename type>
	bool operator==(const type& _num) const { return equ(bignum(_num)); }

	template<typename type>
	bool operator!=(const type& _num) const { return !equ(bignum(_num)); }
	
	template<typename type>
	bool operator< (const type& _num) const { return lss(bignum(_num)); }
	
	template<typename type>
	bool operator> (const type& _num) const { return gtr(bignum(_num)); }
	
	template<typename type>
	bool operator>=(const type& _num) const { return geq(bignum(_num)); }
	
	template<typename type>
	bool operator<=(const type& _num) const { return leq(bignum(_num)); }
	
	template<typename type>
	bignum& operator+=(const type& num) { *this = *this + num; return *this; }

	template<typename type>
	bignum& operator-=(const type& num) { *this = *this - num; return *this; }

	template<typename type>
	bignum& operator*=(const type& num) { *this = *this * num; return *this; }

	template<typename type>
	bignum& operator/=(const type& num) { *this = *this / num; return *this; }

	template<typename type>
	bignum& operator%=(const type& num) { *this = *this % num; return *this; }

	static std::string complement(const std::string& num, const size_t& len);
	static std::string invert(const std::string&);
	static std::string formatter(const std::string&);

	static std::string superscript(const std::string&);
	static std::string superscript(const ssize_t&);

	static std::string subscribed(const std::string&);
	static std::string subscribed(const ssize_t&);

	std::string scientific(const ssize_t&);
	std::string E(const ssize_t&);

	template<typename type>
	bignum pow(const type& exp)
	{
		if (exp < 0)
		{
			return 0;
		}
		if (exp == 0)
		{
			return bignum(1);
		}
		bignum pow(*this);
		for (bignum i(1); i < exp; i.plusplus())
		{
			pow = *this * pow;
		}
		return pow;
	}

	bignum factorial()
	{
		if (*this <= 0)
		{
			return 0;
		}
		bignum fact(1);
		for (bignum i(*this); i > 1; i.minusminus())
		{
			fact = fact * i;
		}
		return fact;
	}
};

inline bool operator==(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ == num2; }
inline bool operator!=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ != num2; }
inline bool operator< (const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ <  num2; }
inline bool operator> (const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ >  num2; }
inline bool operator>=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ >= num2; }
inline bool operator<=(const ssize_t& num1, const bignum& num2) { bignum num1_(num1); return num1_ <= num2; }

#endif //BIGNUM_H
