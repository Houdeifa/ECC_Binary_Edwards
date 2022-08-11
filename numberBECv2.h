/*
 * numberBECv2v2.h
 *
 *  Created on: 10 août 2022
 *      Author: a858370
 */

#ifndef numberBECV2_H_
#define numberBECV2_H_
#include <cstdint>
#include <iostream>
#include <vector>

class numberBECv2 {static int constructed0;
	static int constructed1;
	static int constructed2;
	static int constructed3;
	static int constructed4;
	static int constructed5;
	static int destructed;
	static unsigned int polyI;
	static unsigned int polyJ;
	std::vector<uint64_t> value; // vector used to stock the data
	static std::vector<uint64_t> poly; // vector used to stock the irreducible polynomial
	int order = 0; // the order of the MSB
	static int polyOrder; // number represent the order of the irreducible polynomial
	static bool polynomeIsSet; // a boolean to tell if the irreducible polynomial is defined
public:
	bool log = false;
	void inv();
	void Normalize();
	static void print_const_and_dust();
	static void reset_const_and_dust();
	numberBECv2();
	numberBECv2(const numberBECv2& A);
	numberBECv2(int v);
	numberBECv2(const std::string& s);
	numberBECv2(const std::vector<uint64_t>& v);
	numberBECv2(const char * s);
	void addPoly();
	virtual ~numberBECv2();
	void copyFromString(const std::string& s);
	void printPoly();
	unsigned int getOrder();
	static unsigned int getPolyOrder();
	static void calcPolyOrder();
	void setFromPolyCoeffs(const std::vector<uint64_t>& v);
	std::string getAsPoly();
	static std::string getIrrPoly();
	numberBECv2 operator=(const int& n);
	numberBECv2 operator=(const char * s);
	numberBECv2 operator=(const numberBECv2& A);
	numberBECv2 operator&(const numberBECv2& B);
	void operator+=(const numberBECv2& B);
	static numberBECv2 getPoly();
	bool isPolySet();
	friend std::ostream& operator<<(std::ostream& os,const numberBECv2& n);
	friend numberBECv2 operator/(int A,const numberBECv2& B);
	bool  operator==(const numberBECv2 &B);
	friend bool operator==(int n,const numberBECv2 &B);
	friend bool operator==(const numberBECv2 &B, int n);
	bool  operator==(int n);
	numberBECv2 operator+(const numberBECv2& B);
	numberBECv2 operator*(const numberBECv2& B);
	numberBECv2 operator/(const numberBECv2& B);
	void operator<<=(int i);
	void operator>>=(int i);
	static void setPoly(const numberBECv2& P);
	void swap(numberBECv2& n);
	void clearPoly();
	bool isBitSet(int n);
	numberBECv2 operator<<(int nBits);
	numberBECv2 operator>>(int nBits);
	void clearAllDatas();
	void copyValueFromVector(const std::vector<uint64_t>& vec);
	static void copyPolyFromVector(const std::vector<uint64_t>& vec);
	unsigned int size();
	uint64_t operator[](int);
};

#endif /* numberBECv2_H_ */
