//============================================================================
// Name        : main.cpp
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Test bench file to test the operation
//============================================================================

#include <iostream>
#include "number.h"


int main() {
//	int64_t v[2] = {0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA};
	number A = "3F";
	number B = "A3";
	number Poly = "15F";
	A.setPoly(Poly);
	B.setPoly(Poly);
	std::cout<<"Poly(x) = "<<A.getIrrPoly()<<std::endl;
	std::cout<<"A(x) = "<<A.getAsPoly()<<std::endl;
	std::cout<<"B(x) = "<<B.getAsPoly()<<std::endl;
	number C = A * B;
	std::cout<<"C = A x B = "<<C<<std::endl;

	std::cout<<"C(x) = "<<C.getAsPoly()<<std::endl;
	C = A >> 1;
	std::cout<<"C = A >> 1 = "<<C<<std::endl;
	A = "50";
	A.setPoly(number("CB"));
	A = 1/A;
	std::cout<<"A^-1 = "<<A<<" = "<<A.getAsPoly()<<std::endl;

	A.setPoly(number("CB"));
	B.setPoly(number("CB"));
	B = "50";
	std::cout<<"A = "<<A<<std::endl;
	std::cout<<"Poly(x) = "<<A.getIrrPoly()<<std::endl;
	C = A * B;
	std::cout<<"C = A^1 * B = "<<C<<" = "<<C.getAsPoly()<<std::endl;
	A.setPoly(number("CB"));
	B.setPoly(number("CB"));
	std::cout<<"A = "<<A<<"& B = "<<B<<std::endl;
	std::cout<<"Poly(x) = "<<A.getIrrPoly()<<std::endl;
	C = A / B;
	std::cout<<"C = A / B = "<<C<<std::endl;
	C = 1 / B;
	std::cout<<"C = 1 / B = "<<C<<std::endl;

	return 0;
}
