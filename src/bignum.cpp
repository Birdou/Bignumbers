#include "bignum.h"

bool bignum::getSignal() const
{
	return signal;
}

void bignum::setSignal(bool sign)
{
	this->signal = sign;
}

const std::string& bignum::getNumber() const
{
	return number;
}

void bignum::setNumber(const bignum& num)
{
	this->number = num.getNumber();
	this->signal = num.getSignal();
}
void bignum::setNumber(const std::string& _string)
{
	short initial;
	if (_string[0] == '-')
	{
		initial = 1;
		this->signal = true;
	}
	else
	{
		initial = 0;
		this->signal = false;
	}
	this->number = _string.substr(initial);
}
void bignum::setNumber(const ssize_t& num)
{
	if (num < 0)
	{
		this->number = std::to_string(num * -1);
		this->signal = true;
	}
	else
	{
		this->number = std::to_string(num);
		this->signal = false;
	}
}

void bignum::forceNumber(const std::string& num)
{
	if (num[0] == '-')
	{
		signal = true;
		number = num.substr(1);
	}
	else
	{
		number = num;
	}
}

std::string bignum::getString() const
{
	if (signal)
	{
		return "-" + number;
	}
	return number;
}

void bignum::plusplus()
{
	std::stringstream sstream;
	if (!signal)
	{
		short up = 1, n;
		for (ssize_t i = number.length() - 1; i >= 0; i--)
		{
			if (i > 0 && up == 0)
			{
				number = number.substr(0, i + 1) + big_invert(sstream.str());
				return;
			}

			n = (number[i] - '0') + up;
			up = 0;

			if (i == 0 && n == 10)
			{
				sstream << "01";
			}
			else if (n == 10)
			{
				up = 1;
				sstream << "0";
			}
			else
			{
				sstream << n;
			}
		}
	}
	else
	{
		short up = 1, n;
		if (number == "1")
		{
			number = "0";
			signal = false;
			return;
		}
		for (ssize_t i = number.length() - 1; i >= 0; i--)
		{
			if (i > 0 && up == 0)
			{
				number = number.substr(0, i + 1) + big_invert(sstream.str());
				return;
			}
			n = (number[i] - '0') - up;
			up = 0;

			if (n == -1 && i == 0)
			{
				number = "0";
				signal = false;
				return;
			}
			else if (n == -1)
			{
				up = 1;
				sstream << "9";
			}
			else
			{
				if(i == 0 && n == 0)
				{
					break;
				}
				sstream << n;				
			}
		}
	}
	number = big_invert(sstream.str());
}

void bignum::minusminus()
{
	std::stringstream sstream;
	if (signal)
	{
		short up = 1, n;
		for (ssize_t i = number.length() - 1; i >= 0; i--)
		{
			if (i > 0 && up == 0)
			{
				number = number.substr(0, i + 1) + big_invert(sstream.str());
				return;
			}

			n = (number[i] - '0') + up;
			up = 0;

			if (i == 0 && n == 10)
			{
				sstream << "01";
			}
			else if (i > 0 && n == 10)
			{
				up = 1;
				sstream << "0";
			}
			else
			{
				sstream << n;
			}
		}
	}
	else
	{
		short up = 1, n;
		if (number == "0")
		{
			number = "1";
			signal = true;
			return;
		}
		if (number == "1")
		{
			number = "0";
			signal = false;
			return;
		}
		for (ssize_t i = number.length() - 1; i >= 0; i--)
		{
			if (i > 0 && up == 0)
			{
				number = number.substr(0, i + 1) + big_invert(sstream.str());
				return;
			}

			n = (number[i] - '0') - up;
			up = 0;

			if (n == -1 && i == 0)
			{
				number = "0";
				signal = false;
				return;
			}
			else if (n == -1)
			{
				up = 1;
				sstream << "9";
			}
			else
			{
				if(i == 0 && n == 0)
				{
					break;
				}
				sstream << n;				
			}
		}
	}
	number = big_invert(sstream.str());
}

bool bignum::operator==(const bignum&      num) const
{
	std::string this_string = this->getNumber(), num_string = num.getNumber();
	ssize_t this_lenght = this->getNumber().length(), num_lenght = num.getNumber().length();
	bool this_signal = this->getSignal(), num_signal = num.getSignal();
	if (this_signal != num_signal || this_lenght != num_lenght)
	{
		return false;
	}
	else
	{
		for (ssize_t i = 0; i < this_lenght; i++)
		{
			if (this_string[i] != num_string[i])
			{
				return false;
			}
		}
		return true;
	}
}
bool bignum::operator==(const std::string& num) const
{
	bignum num1(num);
	return *this == num1;
}
bool bignum::operator==(const ssize_t&     num) const
{
	bignum num1(num);
	return *this == num1;
}

bool bignum::operator!=(const bignum&      num) const
{
	return !(*this == num);
}
bool bignum::operator!=(const std::string& num) const
{
	bignum num1(num);
	return !(*this == num);
}
bool bignum::operator!=(const ssize_t&     num) const
{
	bignum num1(num);
	return !(*this == num);
}

bool bignum::operator< (const bignum&      num) const
{
	std::string this_string = this->getNumber(), num_string = num.getNumber();
	ssize_t this_lenght = this->getNumber().length(), num_lenght = num.getNumber().length();
	bool this_signal = this->getSignal(), num_signal = num.getSignal();

	if (this_signal && !num_signal)
	{
		return true;
	}
	else if (!this_signal && num_signal)
	{
		return false;
	}
	else if (this_lenght < num_lenght)
	{
		if (this_signal)
		{
			return false;
		}
		return true;
	}
	else if (this_lenght > num_lenght)
	{
		if (this_signal)
		{
			return true;
		}
		return false;
	}
	else if (this_signal == num_signal && this_lenght == num_lenght)
	{
		short t, n;
		for (ssize_t i = 0; i < this_lenght; i++)
		{
			t = this_string[i] - '0';
			n = num_string[i] - '0';
			if (t == n)
			{
				continue;
			}
			if (t < n)
			{
				if (this_signal)
				{
					return false;
				}
				return true;
			}
			else
			{
				if (this_signal)
				{
					return true;
				}
				return false;
			}
		}
	}

	return false;
}
bool bignum::operator< (const std::string& num) const
{
	bignum num1(num);
	return *this < num1;
}
bool bignum::operator< (const ssize_t&     num) const
{
	bignum num1(num);
	return *this < num1;
}

bool bignum::operator> (const bignum&      num) const
{
	std::string this_string = this->getNumber(), num_string = num.getNumber();
	ssize_t this_lenght = this->getNumber().length(), num_lenght = num.getNumber().length();
	bool this_signal = this->getSignal(), num_signal = num.getSignal();

	if (this_signal && !num_signal)
	{
		return false;
	}
	else if (!this_signal && num_signal)
	{
		return true;
	}
	else if (this_lenght < num_lenght)
	{
		if (this_signal)
		{
			return true;
		}
		return false;
	}
	else if (this_lenght > num_lenght)
	{
		if (this_signal)
		{
			return false;
		}
		return true;
	}
	else if (this_signal == num_signal && this_lenght == num_lenght)
	{
		short t, n;
		for (ssize_t i = 0; i < this_lenght; i++)
		{
			t = this_string[i] - '0';
			n = num_string[i] - '0';
			if (t == n)
			{
				continue;
			}
			if (t > n)
			{
				if (this_signal)
				{
					return false;
				}
				return true;
			}
			else
			{
				if (this_signal)
				{
					return true;
				}
				return false;
			}
		}
	}

	return false;
}
bool bignum::operator> (const std::string& num) const
{
	bignum num1(num);
	return *this > num1;
}
bool bignum::operator> (const ssize_t&     num) const
{
	bignum num1(num);
	return *this > num1;
}

bool bignum::operator<=(const bignum&      num) const
{
	if (*this < num || *this == num)
	{
		return true;
	}
	return false;
}
bool bignum::operator<=(const std::string& num) const
{
	bignum num1(num);
	if (*this < num1 || *this == num1)
	{
		return true;
	}
	return false;
}
bool bignum::operator<=(const ssize_t&     num) const
{
	bignum num1(num);
	if (*this < num1 || *this == num1)
	{
		return true;
	}
	return false;
}

bool bignum::operator>=(const bignum&      num) const
{
	if (*this > num || *this == num)
	{
		return true;
	}
	return false;
}
bool bignum::operator>=(const std::string& num) const
{
	bignum num1(num);
	if (*this > num1 || *this == num1)
	{
		return true;
	}
	return false;
}
bool bignum::operator>=(const ssize_t&     num) const
{
	bignum num1(num);
	if (*this < num1 || *this == num1)
	{
		return true;
	}
	return false;
}

bignum bignum::addition(bignum& num1, bignum& num2)
{
	if (!num1.getSignal() && num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum sum = bignum::subtraction(num1, num2);
		return sum;
	}
	else if (num1.getSignal() && !num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum sum = bignum::subtraction(num2, num1);
		return sum;
	}
	else if (num1.getSignal() && num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum sum = bignum::addition(num1, num2);
		sum.setSignal(true);
		return sum;
	}
	
	std::stringstream sstream;
	short x = 0, y = 0, total, up = 0, down = 0;
	ssize_t xp = num1.getNumber().length() - 1, yp = num2.getNumber().length() - 1;
	std::string num1_string = num1.getNumber(), num2_string = num2.getNumber();

	while (xp >= 0 || yp >= 0 || up > 0)
	{
		if (xp >= 0)
		{
			x = num1_string[xp] - '0';
			xp--;
		}
		else
		{
			x = 0;
		}

		if (yp >= 0)
		{
			y = num2_string[yp] - '0';
			yp--;
		}
		else
		{
			y = 0;
		}

		total = x + y + up;
		if(total >= 10)
		{
			up = 1;
			down = total - 10;
		}
		else
		{
			up = 0;
			down = total;
		}
		sstream << down;
	}
	bignum sum = big_invert(sstream.str());
	return sum;
}

bignum bignum::subtraction(bignum& num1, bignum& num2)
{
	if (num1.getSignal() && !num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum dif = addition(num1, num2);
		dif.setSignal(true);
		return dif;
	}
	else if (!num1.getSignal() && num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum dif = addition(num1, num2);
		return dif;
	}
	else if (num1.getSignal() && num2.getSignal())
	{
		num1.setSignal(false);
		num2.setSignal(false);
		bignum dif = subtraction(num2, num1);
		return dif;
	}

	std::stringstream sstream;
	ssize_t xp = num1.getNumber().length(), yp = num2.getNumber().length();
	size_t b = bigger(xp, yp);
	std::string num1_string = num1.getNumber(), num2_string = num2.getNumber();

	if(yp < xp)
	{
		std::stringstream ss;
		for(int i = 0; i < xp - yp; ++i)
			ss << 0;
		ss << num2_string;
		num2_string = ss.str();
	}
	bignum sum, c;
	c.forceNumber(big_complement(num2_string, b));
	sum = num1 + c;
	if (sum.getNumber().length() > b)
	{
		++sum;
		sum = big_formatter(sum.getNumber().substr(1));
		return sum;
	}
	else
	{
		sum = big_complement(sum.getNumber(), 0);
		sum.setSignal(true);
		sum = big_formatter(sum.getString());
		return sum;
	}
}

bignum bignum::multiplication(bignum& num1, bignum& num2)
{
	std::string num1_string = num1.getNumber(), num2_string = num2.getNumber();
	ssize_t num1_lenght = num1_string.length(), num2_lenght = num2_string.length();

	bignum vsum(0);
	short operation = 0, total, up = 0, down = 0;
	std::stringstream sstream;

	for (ssize_t i = num2_lenght - 1; i >= 0; i--)
	{
		sstream.str("");
		for (short k = 0; k < operation; k++)
		{
			sstream << "0";
		}
		for (ssize_t j = num1_lenght - 1; j >= 0; j--)
		{
			total = ((num2_string[i] - '0') * (num1_string[j] - '0')) + up;
			if (j == 0)
			{
				sstream << total % 10;
				if (total >= 10)
				{
					sstream << total / 10;
				}

				up = 0;
			}
			else
			{
				down = total % 10;
				sstream << down;
				up = total / 10;
			}
		}
		vsum = vsum + big_invert(sstream.str());
		operation++;
	}
	if (num1.getSignal() != num2.getSignal())
	{
		if (vsum.getString() != "0")
			vsum.setSignal(true);
	}
	vsum = big_formatter(vsum.getString());
	return vsum;
}

bignum bignum::division(bignum& num1, bignum& num2)
{
	if (num2 == 0)
	{
		return 0;
	}
	bool num1_signal = false, num2_signal = false;
	if (num1.getSignal())
	{
		num1_signal = true;
		num1.setSignal(false);
	}
	if (num2.getSignal())
	{
		num2_signal = true;
		num2.setSignal(false);
	}
	bignum total(0), numerator(num1), tmp, e(1);
	while (1)
	{
		if (numerator <= 0)
		{
			break;
		}

		tmp = num2 * e;

		if (numerator > tmp)
		{
			e = e * 10;
			continue;
		}
		else
		{
			if (e > 1)
			{
				e = e / 10;
				tmp = num2 * e;
			}
		}
		if (numerator >= tmp)
		{
			numerator = numerator - tmp;
			total = total + e;
		}
		else
		{
			break;
		}
		e = 1;
	}
	if (num1_signal != num2_signal)
	{
		if (total.getString() != "0")
			total.setSignal(true);
	}
	return total;
}

bignum& bignum::operator++()
{
	this->plusplus();
	return *this;
}
bignum& bignum::operator--()
{
	this->minusminus();
	return *this;
}

bignum& bignum::operator+=(const bignum&      num)
{
	*this = *this + num;
	return *this;
}
bignum& bignum::operator+=(const std::string& num)
{
	*this = *this + num;
	return *this;
}
bignum& bignum::operator+=(const ssize_t&     num)
{
	*this = *this + num;
	return *this;
}

bignum& bignum::operator-=(const bignum&      num)
{
	*this = *this - num;
	return *this;
}
bignum& bignum::operator-=(const std::string& num)
{
	*this = *this - num;
	return *this;
}
bignum& bignum::operator-=(const ssize_t&     num)
{
	*this = *this + num;
	return *this;
}

bignum& bignum::operator*=(const bignum&      num)
{
	*this = *this * num;
	return *this;
}
bignum& bignum::operator*=(const std::string& num)
{
	*this = *this * num;
	return *this;
}
bignum& bignum::operator*=(const ssize_t&     num)
{
	*this = *this + num;
	return *this;
}

bignum& bignum::operator/=(const bignum&      num)
{
	*this = *this / num;
	return *this;
}
bignum& bignum::operator/=(const std::string& num)
{
	*this = *this / num;
	return *this;
}
bignum& bignum::operator/=(const ssize_t&     num)
{
	*this = *this + num;
	return *this;
}

std::string big_complement(const std::string& num, const size_t& len)
{
	std::stringstream ss;
	size_t nlen = num.length();
	if(len > nlen)
	{
		for(size_t i = 0; i < len - nlen; ++i)
		{
			ss << 9;
		}
	}
	for(size_t i = 0; i < nlen; ++i)
	{
		ss << 9 - (num[i] - '0');
	}
	return ss.str();
}

std::string big_invert(const std::string& _string)
{
	std::stringstream sstream;
	short initial = 0;
	if (_string[0] == '-')
	{
		initial = 1;
		sstream << "-";
	}
	for (ssize_t i = _string.length() - 1; i >= initial; i--)
	{
		sstream << _string[i];
	}
	return sstream.str();
}

std::string big_formatter(const std::string& _string)
{
	std::stringstream sstream;
	short initial = 0;
	bool isfind = false;

	if (_string[0] == '-')
	{
		initial = 1;
		sstream << "-";
	}

	size_t slen = _string.length();
	for (size_t i = initial; i < slen; ++i)
	{
		if (i == slen - 1)
		{
			if (_string[i] == '0' && !isfind)
			{
				return "0";
			}
		}

		if (_string[i] != '0')
		{
			isfind = true;
		}
		else if (!isfind)
		{
			continue;
		}
		sstream << _string[i];
	}
	return sstream.str();
}

std::string big_superscript(const std::string& num)
{
	std::stringstream sstream;
	for (size_t i = 0; i < num.length(); i++)
	{
		if(num[i] == '-')
		{
			sstream << "⁻";
		}
		else if(num[i] == '0')
		{
			sstream << "⁰";
		}
		else if(num[i] == '1')
		{
			sstream << "¹";
		}
		else if(num[i] == '2')
		{
			sstream << "²";
		}
		else if(num[i] == '3')
		{
			sstream << "³";
		}
		else if(num[i] == '4')
		{
			sstream << "⁴";
		}
		else if(num[i] == '5')
		{
			sstream << "⁵";
		}
		else if(num[i] == '6')
		{
			sstream << "⁶";
		}
		else if(num[i] == '7')
		{
			sstream << "⁷";
		}
		else if(num[i] == '8')
		{
			sstream << "⁸";
		}
		else if(num[i] == '9')
		{
			sstream << "⁹";
		}
		else
		{
			sstream << num[i];
		}
	}
	return sstream.str();
}
std::string big_superscript(const ssize_t&     num)
{
	std::string number = std::to_string(num);
	return big_superscript(number);
}

std::string big_subscribed(const std::string& num)
{
	std::stringstream sstream;
	for (size_t i = 0; i < num.length(); i++)
	{
		if(num[i] == '-')
		{
			sstream << "₋";
		}
		else if(num[i] == '0')
		{
			sstream << "₀";
		}
		else if(num[i] == '1')
		{
			sstream << "₁";
		}
		else if(num[i] == '2')
		{
			sstream << "₂";
		}
		else if(num[i] == '3')
		{
			sstream << "₃";
		}
		else if(num[i] == '4')
		{
			sstream << "₄";
		}
		else if(num[i] == '5')
		{
			sstream << "₅";
		}
		else if(num[i] == '6')
		{
			sstream << "₆";
		}
		else if(num[i] == '7')
		{
			sstream << "₇";
		}
		else if(num[i] == '8')
		{
			sstream << "₈";
		}
		else if(num[i] == '9')
		{
			sstream << "₉";
		}
		else
		{
			sstream << num[i];
		}
	}
	return sstream.str();
}
std::string big_subscribed(const ssize_t&     num)
{
	std::string number = std::to_string(num);
	return big_subscribed(number);
}

std::string big_scientific(const std::string& num, const ssize_t& precision)
{
	if (precision < 0)
	{
		return num;
	}

	std::stringstream sstream;
	short initial = 0;
	if (num[0] == '-')
	{
		initial = 1;
		sstream << "-";
	}
	sstream << num[initial];
	if (precision > 0)
	{
		sstream << ",";
	}
	for (size_t i = initial + 1; i <= (size_t)precision; i++)
	{
		if (i >= num.length())
		{
			sstream << "0";
		}
		else
		{
			sstream << num[i];
		}
	}
	sstream << "×10" << big_superscript(num.length() - initial - 1);
	return sstream.str();
}
std::string big_scientific(const bignum&      num, const ssize_t& precision)
{
	return big_scientific(num.getString(), precision);
}

std::string big_E(const std::string& num, const ssize_t& precision)
{
	if (precision < 0)
	{
		return num;
	}

	std::stringstream sstream;
	short initial = 0;
	if (num[0] == '-')
	{
		initial = 1;
		sstream << "-";
	}
	sstream << num[initial];
	if (precision > 0)
	{
		sstream << ",";
	}
	for (size_t i = initial + 1; i <= (size_t)precision; i++)
	{
		if (i >= num.length())
		{
			sstream << "0";
		}
		else
		{
			sstream << num[i];
		}
	}
	sstream << "E" << num.length() - initial - 1;
	return sstream.str();
}
std::string big_E(const bignum&      num, const ssize_t& precision)
{
	return big_E(num.getString(), precision);
}

bignum big_pow(const bignum& num, const bignum&      e)
{
	if (e < "0")
	{
		return bignum(0);
	}
	if (e == "0")
	{
		return bignum(1);
	}
	bignum pow(num);
	for (bignum i(1); i < e; i.plusplus())
	{
		pow = num * pow;
	}
	return pow;
}
bignum big_pow(const bignum& num, const std::string& e)
{
	bignum _e(e);
	return big_pow(num, _e);
}
bignum big_pow(const bignum& num, const ssize_t&     e)
{
	if (e == 0)
	{
		return bignum(1);
	}
	bignum pow(num);
	for (ssize_t i = 1; i < e; ++i)
	{
		pow = num * pow;
	}
	return pow;
}

bignum big_factorial(const bignum&      num)
{
	if (num <= "0")
	{
		return bignum(0);
	}
	bignum fact(1);
	for (bignum i(num); i > "1"; i.minusminus())
	{
		fact = fact * i;
	}
	return fact.getString();
}
bignum big_factorial(const std::string& num)
{
	bignum _num(num);
	return big_factorial(_num);
}
bignum big_factorial(const ssize_t&     num)
{
	bignum _num(num);
	return big_factorial(_num);
}


void big_verificationInRange(const ssize_t& range)
{
	ssize_t procedimentos = 0, falhas = 0;
	bignum ii, jj;
	for (ssize_t i = range * -1; i <= range; i++)
	{
		for (ssize_t j = range * -1; j <= range; j++)
		{
			ii = i;
			jj = j;
			if (ii + jj != i + j)
			{
				std::cout << "resultado obtido: " << ii << " + " << jj << " = " << ii + jj << "\n";
				std::cout << "\tesperado: " << i << " + " << j << " = " << i + j << "\n";
				falhas++;
			}

			if (ii - jj != i - j)
			{
				std::cout << "resultado obtido: " << ii << " - " << jj << " = " << ii - jj << "\n";
				std::cout << "\tesperado: " << i << " - " << j << " = " << i - j << "\n";
				falhas++;
			}

			if (ii * jj != i * j)
			{
				std::cout << "resultado obtido: " << ii << " * " << jj << " = " << ii * jj << "\n";
				std::cout << "\tesperado: " << i << " * " << j << " = " << i * j << "\n";
				falhas++;
			}

			if (j != 0)
			{
				if (ii / jj != i / j)
				{
					std::cout << "resultado obtido: " << ii << " / " << jj << " = " << ii / jj << "\n";
					std::cout << "\tesperado: " << i << " / " << j << " = " << i / j << "\n";
					falhas++;
				}
			}
			procedimentos += 4;
		}
			
	}

	ii.setNumber(range * -1);
	for (ssize_t i = range * -1; i <= range; i++)
	{
		if (ii != i)
		{
			std::cout << "resultado incorreto de ++" << i - 1 << " = " << ii.getString() << "\n";
			std::cout << "esperado: " << i << "\n";
			falhas++;
			break;
		}
		++ii;
		procedimentos++;
	}

	ii.setNumber(range);
	for (ssize_t i = range; i >= range * -1; i--)
	{
		if (ii != i)
		{
			std::cout << "resultado incorreto de --" << i + 1 << " = " << ii.getString() << "\n";
			std::cout << "esperado: " << i << "\n";
			falhas++;
			break;
		}
		--ii;
		procedimentos++;
	}

	for (int i = range * -1; i <= range; i++)
	{
		for (int j = range * -1; j <= range; j++)
		{
			ii.setNumber(i);
			jj.setNumber(j);

			if ((i == j) != (ii == jj))
			{
				std::cout << "resultado incorreto de " << i << " == " << j << " = " << (ii == jj) << "\n";
				std::cout << "esperado: " << (i == j) << "\n";
				falhas++;
			}
			if ((i != j) != (ii != jj))
			{
				std::cout << "resultado incorreto de " << i << " != " << j << " = " << (ii != jj) << "\n";
				std::cout << "esperado: " << (i != j) << "\n";
				falhas++;
			}
			if ((i < j) != (ii < jj))
			{
				std::cout << "resultado incorreto de " << i << " < " << j << " = " << (ii < jj) << "\n";
				std::cout << "esperado: " << (i < j) << "\n";
				falhas++;
			}
			if ((i > j) != (ii > jj))
			{
				std::cout << "resultado incorreto de " << i << " > " << j << " = " << (ii > jj) << "\n";
				std::cout << "esperado: " << (i > j) << "\n";
				falhas++;
			}
			if ((i <= j) != (ii <= jj))
			{
				std::cout << "resultado incorreto de " << i << " <= " << j << " = " << (ii <= jj) << "\n";
				std::cout << "esperado: " << (i <= j) << "\n";
				falhas++;
			}
			if ((i >= j) != (ii >= jj))
			{
				std::cout << "resultado incorreto de " << i << " >= " << j << " = " << (ii >= jj) << "\n";
				std::cout << "esperado: " << (i >= j) << "\n";
				falhas++;
			}
			procedimentos += 6;
		}
	}
	std::cout << "TESTES REALIZADOS: " << procedimentos << "\n";
	std::cout << "TESTES FALHOS: " << falhas << "\n";
}

size_t bigger(const ssize_t& num1, const ssize_t& num2)
{
	if(num1 >= num2)
	{
		return num1;
	}
	return num2;
}