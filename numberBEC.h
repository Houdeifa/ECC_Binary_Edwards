/*
 * numberBEC.h
 *
 *  Created on: 4 août 2022
 *      Author: a858370
 */

#ifndef NUMBERBEC_H_
#define NUMBERBEC_H_
#include <cstdint>
#include <iostream>
#include <vector>

class numberBEC {
	static int constructed0;
	static int constructed1;
	static int constructed2;
	static int constructed3;
	static int constructed4;
	static int constructed5;
	static int destructed;
	std::vector<uint64_t> value; // vector used to stock the data
	std::vector<uint64_t> poly; // vector used to stock the irreducible polynomial
	int order = 0; // the order of the MSB
	int polyOrder= 0; // number represent the order of the irreducible polynomial
	bool polynomeIsSet = false; // a boolean to tell if the irreducible polynomial is defined
public:
	bool log = false;
	void inv();
	void Normalize();
	static void print_const_and_dust();
	static void reset_const_and_dust();
	numberBEC();
	numberBEC(const numberBEC& A);
	numberBEC(int v);
	numberBEC(const std::string& s);
	numberBEC(const std::vector<uint64_t>& v);
	numberBEC(const char * s);
	void addPoly();
	virtual ~numberBEC();
	void copyFromString(const std::string& s);
	void printPoly();
	unsigned int getOrder();
	unsigned int getPolyOrder();
	void calcPolyOrder();
	void setFromPolyCoeffs(const std::vector<uint64_t>& v);
	std::string getAsPoly();
	std::string getIrrPoly();
	numberBEC operator=(const int& n);
	numberBEC operator=(const char * s);
	numberBEC operator=(const numberBEC& A);
	numberBEC operator&(const numberBEC& B);
	void operator+=(const numberBEC& B);
	numberBEC getPoly();
	bool isPolySet();
	friend std::ostream& operator<<(std::ostream& os,const numberBEC& n);
	friend numberBEC operator/(int A,const numberBEC& B);
	bool  operator==(const numberBEC &B);
	friend bool operator==(int n,const numberBEC &B);
	friend bool operator==(const numberBEC &B, int n);
	bool  operator==(int n);
	numberBEC operator+(const numberBEC& B);
	numberBEC operator*(const numberBEC& B);
	numberBEC operator/(const numberBEC& B);
	void operator<<=(int i);
	void operator>>=(int i);
	void setPoly(const numberBEC& P);
	void swap(numberBEC& n);
	void clearPoly();
	bool isBitSet(int n);
	numberBEC operator<<(int nBits);
	numberBEC operator>>(int nBits);
	void clearAllDatas();
	void copyValueFromVector(const std::vector<uint64_t>& vec);
	void copyPolyFromVector(const std::vector<uint64_t>& vec);
	unsigned int size();
	uint64_t operator[](int);
};

#endif /* NUMBERBEC_H_ */
