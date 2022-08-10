//============================================================================
// Name        : number.cpp
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : The basic class to represent a number and define GF(2^m) operations
//============================================================================

#include "number.h"
/**
 * Default constructor : intiaite all values to 0 as default
 */
number::number(){
	value[0] = 0;
	value[1] = 0;
	poly[0] = 0;
	poly[1] = 0;
}
/**
 * int constructor : the value entred will go to the least significant register
 * @param v int that will be stocked in LS register
 */
number::number(int v){
	value[0] = v;
	value[1] = 0;
	poly[0] = 0;
	poly[1] = 0;
}
/**
 * string constructor : the value entred (in hexadecimals) will be converted and stocked
 * @param s string that represent the value in hexadecimals
 */
number::number(const std::string& s){
	value[0] = 0;
	value[1] = 0;
	if(s.length() == 0) return;
	int Len = 64;
	if(s.length() < 64 ) Len = s.length();

	int64_t H = 0, L = 0, tmp = 0;
	int j = Len-1;
	for(int i = 0;i<Len;i++){
		bool charUsed = false;
		tmp<<=4;
		if(s[i] <= '9' && s[i]>='0') {
			tmp += (s[i] - '0');
			charUsed = true;
		}
		if(s[i] <= 'f' && s[i]>='a') {
			tmp += (s[i] - 'a') + 10;
			charUsed = true;
		}
		if(s[i] <= 'F' && s[i]>='A') {
			tmp += (s[i] - 'A') + 10;
			charUsed = true;
		}
		if(j == 16){
			H = tmp;
			tmp = 0;
		}
		if(!charUsed) return;
		j--;
	}
	L = tmp;
	value[0] = L;
	value[1] = H;
}
/**
 * array constructor : the value entred as array of 64 bit size for each word will be socked in intern registers, least to hight significant is from 0 to N , where N is the number of 64 bit words
 * @param v is uint64_t pointer that points to an of size N array
 */
number::number(uint64_t * v){
	value[0] = v[0];
	value[1] = v[1];
	poly[0] = 0;
	poly[1] = 0;
}
/**
 * array constructor : the value entred as array of in values for each word will be socked in intern registers, least to hight significant is from 0 to N , where N is the number of 64 bit words
 * @param v is int pointer that points to an of size N array
 */
number::number(int * v){
	value[0] = v[0];
	value[1] = v[1];
	poly[0] = 0;
	poly[1] = 0;
}
/**
 * copy constructor : this constructor will copy the data from another "number"
 * @param A is a reference if a number that will be used as source of datas
 */
number::number(number& A){

	value[0] = A.value[0];
	value[1] = A.value[1];
	poly[0] = A.poly[0];
	poly[1] = A.poly[1];
	polyOrder= A.polyOrder;
	polynomeIsSet = A.polynomeIsSet;
}
/**
 * copy constructor : this constructor will copy the data from another "number", this accepts rvalues
 * @param A is a const reference of a number that will be used as source of datas
 */
number::number(const number& A){

	value[0] = A.value[0];
	value[1] = A.value[1];
	poly[0] = A.poly[0];
	poly[1] = A.poly[1];
	polyOrder= A.polyOrder;
	polynomeIsSet = A.polynomeIsSet;
}
/**
 * const char array constructor : this constuctor accepts an array for char containing hexadecimal numbers, convert and store the values internally
 * @param s is a const char array contains hexadecimal numbers
 */
number::number(const char * s){
	std::string str = std::string(s);
	number A(str);
	value[0] = A.value[0];
	value[1] = A.value[1];
	poly[0] = 0;
	poly[1] = 0;
}
int number::getOrder(){
	return order;
}
/**
 * const int equal operator : copy the value from int to store it in least significant register
 * @param n is const int reference of number
 * @return an instance of number that contains the data entred
 */
number number::operator=(const int& n){
	value[0] = n;
	value[1] = 0;
	poly[0] = 0;
	poly[1] = 0;
	return *this;
}
/**
 * const char array equal operator : copy the values from array of characters that represent the values in hexadecimals, convert and store the values internally
 * @param s is a const char array contains hexadecimal numbers
 * @return an instance of number that contains the data entred
 */
number number::operator=(const char * s){
	std::string str = std::string(s);
	number A(str);
	this->value[0] = A.value[0];
	this->value[1] = A.value[1];
	poly[0] = 0;
	poly[1] = 0;
	return A;
}
/**
 * copy equal operator : this operation will copy the data from another "number", this accepts rvalues
 * @param A is a const reference of a number that will be used as source of datas
 * @return an instance of number that contains the data entred
 */
number number::operator=(const number& A){
	value[0] = A.value[0];
	value[1] = A.value[1];
	poly[0] = A.poly[0];
	poly[1] = A.poly[1];
	polyOrder= A.polyOrder;
	polynomeIsSet = A.polynomeIsSet;
	return *this;
}
/**
 * addition in GF(2^m) between the number B and this number
 * @param B is a reference of number that won't be modified
 * @return the result of the addition
 */
number number::operator+(number& B) // otherwise, both parameters may be const references
{
	uint64_t v[2] = {B.value[0]^value[0],B.value[1]^value[1]};
	number A(v);
	A.poly[0] = poly[0];
	A.poly[1] = poly[1];
	A.polyOrder= polyOrder;
	A.polynomeIsSet = polynomeIsSet;
	return A;
}
number number::operator+(const number& B) // otherwise, both parameters may be const references
{
	number A(B);
	return this->operator+(A);
}
/**
 * verify if the n'th bit is set
 * @param n the order of bit that will be verified (counting from 0 as the LSB)
 * @return a bool value : true if the bit is set (equals 1) , or false if clear (equals 0)
 */
bool number::isBitSet(int n){
	if(n < 64 ) return (this->value[0] & ((int64_t)1<<n)) != 0;
	else return (this->value[1] & ((int64_t)1<<(n-64))) != 0;
}
/**
 * Used to defines the irreducible polynomial that will be used to calculate the GF(2^m) operations
 * @param P a const reference of number that will be the source of data, rvalue is accepted
 */
void number::setPoly(const number& P){

	poly[0] = P.value[0];
	poly[1] = P.value[1];
	int64_t tmp = poly[1];
	polynomeIsSet = false;
	int64_t mask = (int64_t)1 << 63;
	for(int i = 0;i<64;i++){
		if((tmp & mask) != 0){
			polynomeIsSet = true;
			polyOrder = 127-i;
			break;
		}
		mask>>=1;
	}
	mask = (int64_t)1 << 63;
	tmp = poly[0];
	if(polynomeIsSet != true)
		for(int i = 0;i<64;i++){
			if((tmp & mask) != 0){
				polynomeIsSet = true;
				polyOrder = 63-i;
				break;
			}
			mask>>=1;
		}
}
/**
 * Delete the irreducible polynomial datas
 */
void number::clearPoly(){
	polynomeIsSet = false;
	poly[0] = 0;
	poly[1] = 0;
}
/**
 * multiplication in GF(2^m) between the number B and this number
 * , this will use the irreducible polynomial, so it's recommended to make sure that
 * it's defined before do any operation of multiplication
 * @param B is a reference of number that won't be modified
 * @return the result of the multiplication
 */
number number::operator*(number& B)
{
	uint64_t v[2] = {0};
	number A(v);
	number C(*this);
	number PolyN(this->poly);

	uint64_t mask = 1;
	for(int i = 0;i<64;i++){
		if(B.value[0]&mask){
			A = A + C;
		}
		C <<=1;
		mask <<=1;
		if(polynomeIsSet & C.isBitSet(polyOrder)){
			C = C + PolyN;
		}
	}
	mask = 0;
	for(int i = 0;i<64;i++){
		if(B.value[1]&mask){
			A = A + C;
		}
		C <<=1;
		mask <<=1;
		if(polynomeIsSet & C.isBitSet(polyOrder)){
			C = C + PolyN;
		}
	}
	A.poly[0] = poly[0];
	A.poly[1] = poly[1];
	A.polyOrder= polyOrder;
	A.polynomeIsSet = polynomeIsSet;
	return A;
}
number number::operator*(const number& B)
{
 number A(B);
 return this->operator*(A);
}
/**
 * inversion in GF(2^m) of this number, the value of this number will be modified once this function is called,
 * this will use the irreducible polynomial so it's recommended to make sure that
 * it's defined before do any operation of inversion
 */
void number::inv(){
	uint64_t vV[2] = {0};
	uint64_t vU[2] = {0};
	vU[0] = (uint64_t) 1;
	number S(poly);
	number R(*this);
	number V(vV);
	number U(vU);
	int teta = 0;
	for (int i = 0;i<(2*(polyOrder));i++){
		if(!R.isBitSet(polyOrder)){
			R <<=1;
			U <<=1;
			teta++;
		}else{
			if(S.isBitSet(polyOrder)){
				S += R;
				V += U;
			}
			S <<=1;
			if(teta == 0){
				number TMP;
				TMP = S;
				S = R;
				R = TMP;

				TMP = U;
				U = V <<1;
				V = TMP;
				teta = 1;
			}else{
				U >>=1;
				teta--;
			}
		}

	}
	this->value[0] = U.value[0];
	this->value[1] = U.value[1];
}
/**
 * Return a string value that represent polynomial A(x) form of data value stored
 * @return a string value representing the polynomial form
 */
std::string number::getAsPoly(){
	std::string s = "";
	uint64_t mask = (int64_t) 1 << 63;
	int crt = 0;
	for(int i = 0;i<64;i++){
		if((value[1] & mask) != 0){
			std::string intStr = std::to_string(127-i);
			if(crt == 0) s += " x^" + intStr;
			else s += " + x^" + intStr;
			crt++;
		}
		mask >>=1;
	}
	mask = (uint64_t) 1 << 63;
	for(int i = 0;i<64;i++){

		if((value[0] & mask) != 0){
			std::string intStr = std::to_string(63-i);

			if(crt == 0){
				if((63-i) == 0) s += " 1";
				else if((63-i) == 1) s+= " x";
				else s += " x^" +intStr;
			}
			else{
				if((63-i) == 0) s += " + 1";
				else if((63-i) == 1) s += " + x";
				else s += " + x^" +intStr;
			}
			crt++;

		}
		mask >>=1;

	}
	if(crt == 0) s += " 0";

	return s;

}

/**
 * Return a string value that represent the irreducible polynomial P(x) that is used to calculate the operations
 * @return a string value representing the polynomial form of the irreducible polynomial
 */
std::string number::getIrrPoly(){
	number K(this->poly);
	return K.getAsPoly();
}
/**
 * Print the value stored in the number in polynomial form
 */
void number::printPoly(){
	std::string s = this->getAsPoly();
	std::cout<<s;
}
/**
 * AND bit operator that calculates a bit by bit AND between this number and a number B
 * @param B is a reference of number that won't be modified
 * @return the result of AND operator in form of new instance
 */
number number::operator&(number& B){

	uint64_t v[2] = {value[0]&B.value[0],value[1]&B.value[0]};
	number A(v);
	return A;
}
/**
 * Addtion in GF(2^m) field between this number and a another number B,
 * The result will be stored in the current number, so the number will be modified
 * @param B is a reference of number that won't be modified
 */
void number::operator+=(number& B){

	(*this) = (*this + B);
}
/**
 * Division in GF(2^m) field between this number and a another number B,
 * This will use the irreducible polynomial P(x), so make sure to be defined,
 * The result will be stored in a new instance of number that will be returned
 * @param B is a reference of number that won't be modified
 */
number number::operator/(number& B) // otherwise, both parameters may be const references
{
	number C(B);
	C.inv();
	number  A = (*this) * C;
	return A;
}
number number::operator/(const number& B) // otherwise, both parameters may be const references
{
	number C(B);
	return this->operator/(C);
}
bool number::operator==(number& B)
{
	return ((this->value[0] == B.value[0]) && (this->value[1] == B.value[1])); // return the result by value (uses move constructor)
}
bool number::operator==(int i)
{
	return ((this->value[0] == i) && (this->value[1] == 0));
}
bool operator==(int n,number &B){
	return B.operator==(n);
}
/**
 * Division in GF(2^m) field between this a int number and a number B,
 * This will use the irreducible polynomial P(x), so make sure to be defined,
 * This Division can only be used to invert a number R = A^-1, so the only number n accepted is 1
 * Otherwise the returned number will be 0
 * The result will be stored in a new instance of number that will be returned
 * @param n is an int number that will be divided by B (only 1 will be accepted)
 * @param B is a reference of number that won't be modified
 * @return the result of inversion if successful otherwise return a number contains 0
 */
number operator/(int n,number& B){

	uint64_t v[2] = {0,0};
	number R(v);
	if(n != 1)
	return R;
	R = number(B);
	R.inv();
	return R;
}
/**
 * Left shifting of the number by i bits
 * @param i is the amount of bit to shift the number
 * @return the result of the shifting
 */
number number::operator<<(int i){
	uint64_t v0=0,v1=0;
	if(i> 128) i = 128;
	if(i >= 64){
		i -= 64;
		v1 = (value[0]<<i);


		uint64_t v[2] = {v0,v1};
		number A(v);
		return A;
	}
	uint64_t tmp = (value[0]>>(64-i)) & (((uint64_t) 1<<i) - 1);
	v0 = value[0]<<i;
	v1 = (value[1]<<i) ;
	v1 += tmp;

	uint64_t v[2] = {v0,v1};
	number A(v);
	return A;
}

/**
 * Right shifting of the number by i bits
 * @param i is the amount of bit to shift the number
 * @return the result of the shifting
 */
number number::operator>>(int i){
		uint64_t v0=0,v1=0;
		if(i> 128) i = 128;
		if( i>= 64){
			i -=64;
			v0 = (value[1]>>i) ;


			uint64_t v[2] = {v0,v1};
			number A(v);

		}
		uint64_t tmp = value[1] & (((uint64_t) 1<<i) - 1);
		v0 = value[0]>>i;
		v1 = (value[1]>>i) ;
		v0 += (tmp<<(64-i));

		uint64_t v[2] = {v0,v1};
		number A(v);
		return A;
}
/**
 * Left shifting of the number by i bits, this will be applied to the current number
 * @param i is the amount of bit to shift the number
 */
void number::operator<<=(int i){
	(*this) = (*this) << i;
}
/**
 * Right shifting of the number by i bits, this will be applied to the current number
 * @param i is the amount of bit to shift the number
 */
void number::operator>>=(int i){
	(*this) = (*this) >> i;
}
/**
 * Display operator to display the number in the Console using streams
 * @param i is the amount of bit to shift the number
 */
std::ostream& operator<<(std::ostream& os, number& n)
{
	os  << std::hex<<"0x"<< n.value[1]<<n.value[0] <<std::dec;
	return os;
}
