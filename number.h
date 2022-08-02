//============================================================================
// Name        : number.h
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : The basic class to represent a number and define GF(2^m) operations
//============================================================================

#ifndef HUMBER_H
#define HUMBER_H
#include <cstdint>
#include <iostream>

class number{
	uint64_t value[2]; // array used to stock the data
	uint64_t poly[2]; // array used to stock the irreducible polynomial
	int polyOrder= 0; // number represent the order of the irreducible polynomial
	bool polynomeIsSet = false; // a boolean to tell if the irreducible polynomial is defined
	void inv();
public:
	number();
	number(number& A);
	number(const number& A);
	number(int v);
	number(const std::string& s);
	number(uint64_t * v);
	number(int * v);
	number(const char * s);
	void printPoly();
	std::string getAsPoly();
	std::string getIrrPoly();
	number operator=(const int& n);
	number operator=(const char * s);
	number operator=(const number& A);
	number operator&(number& B);
	void operator+=(number& B);
	friend std::ostream& operator<<(std::ostream& os, number& n);
	friend number operator/(int A,number& B);
	number operator+(number& B);
	number operator*(number& B);
	number operator/(number& B);
	void operator<<=(int i);
	void operator>>=(int i);
	void setPoly(const number& P);
	void clearPoly();
	bool isBitSet(int n);
	number operator<<(int i);
	number operator>>(int i);

};
#endif

