#include <iostream>

#include "bignum.h"
#include "ptime.h"

int main ()
{
	ptime<microseconds> time;

	bignum a(10000);
	
	std::cout << big_E(big_factorial(a), 10) << std::endl;


	/*std::cout << "-----TESTE-----" << std::endl;

	time.start();
	big_verificationInRange(100);
	time.point();

	std::cout << "TEMPO DE EXECUÇÃO: " << time.elapsed(1) << "ms" << std::endl;
	std::cout << "---------------" << std::endl;
	*/
	
	return 0;
}
