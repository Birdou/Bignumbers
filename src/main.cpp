#include <iostream>

#include "bignum.hpp"
#include "ptime.hpp"

int main ()
{
	ptime<milliseconds> time;

	std::cout << "-----TESTE-----" << std::endl;

	time.start();
	bignum::test(100);

	std::cout << "TEMPO DE EXECUÇÃO: " << time.elapsed(time.point()) << "ms" << std::endl;
	std::cout << "---------------" << std::endl;

	return 0;
}
