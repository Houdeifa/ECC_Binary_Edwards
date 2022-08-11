/*
 * numberBECv2.cpp
 *
 *  Created on: 4 août 2022
 *      Author: a858370
 */

#include "numberBECv2.h"

numberBECv2::numberBECv2(const std::vector<uint64_t>& v){
	numberBECv2::constructed4++;
	copyValueFromVector(v);
}
numberBECv2::numberBECv2() {
	numberBECv2::constructed0++;
	value.push_back(0);
	poly.push_back(0);

}
int numberBECv2::constructed0 = 0;
int numberBECv2::constructed1 = 0;
int numberBECv2::constructed2 = 0;
int numberBECv2::constructed3 = 0;
int numberBECv2::constructed4 = 0;
int numberBECv2::constructed5 = 0;
int numberBECv2::destructed = 0;
int numberBECv2::polyOrder= 0;
bool numberBECv2::polynomeIsSet = false;
unsigned int numberBECv2::polyI = 0;
unsigned int numberBECv2::polyJ = 0;
std::vector<uint64_t> numberBECv2::poly;
void numberBECv2::reset_const_and_dust(){
	numberBECv2::constructed0 = 0;
	numberBECv2::constructed1 = 0;
	numberBECv2::constructed2 = 0;
	numberBECv2::constructed3 = 0;
	numberBECv2::constructed4 = 0;
	numberBECv2::constructed5 = 0;
	numberBECv2::destructed = 0;
}
numberBECv2::numberBECv2(const numberBECv2& A){
	numberBECv2::constructed1++;
	copyValueFromVector(A.value);
}
numberBECv2::numberBECv2(int v){
	numberBECv2::constructed2++;
	value.push_back(v);

	uint64_t mask = ((uint64_t) 1)<<63;

	order = 64;
	while(mask > 0 && (v & mask ) == 0){
		mask>>=1;
		order--;
	}

}

void numberBECv2::print_const_and_dust(){
	std::cout<<"numberBECv2::constructed0 = "<<numberBECv2::constructed0<<std::endl;
	std::cout<<"numberBECv2::constructed1 = "<<numberBECv2::constructed1<<std::endl;
	std::cout<<"numberBECv2::constructed2 = "<<numberBECv2::constructed2<<std::endl;
	std::cout<<"numberBECv2::constructed3 = "<<numberBECv2::constructed3<<std::endl;
	std::cout<<"numberBECv2::constructed4 = "<<numberBECv2::constructed4<<std::endl;
	std::cout<<"numberBECv2::constructed5 = "<<numberBECv2::constructed5<<std::endl;
	std::cout<<"numberBECv2::destructed = "<<numberBECv2::destructed<<std::endl;
}
numberBECv2::numberBECv2(const char * s){
	numberBECv2::constructed5++;
	std::string str = std::string(s);
	copyFromString(str);
}

void numberBECv2::copyFromString(const std::string& s){
	if(s.length() == 0){
		value.push_back(0);
		order = 0;
		return;
	}
	int Len = s.length();
	int VectorSize = Len/16;
	if(Len%16 == 0) VectorSize--;
	value = std::vector((VectorSize+1),(uint64_t)0);
	int64_t tmp = 0;
	int j = VectorSize;
	int k = (Len-1);
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
		if((k % 16) == 0){
			value[j] = tmp;
			tmp = 0;
			j--;
		}
		if(!charUsed) return;
		k--;
	}
	if(j >= 0){
		value[j] = tmp;
	}
}
numberBECv2::numberBECv2(const std::string& s){

	numberBECv2::constructed3++;
	copyFromString(s);

//	for(int i = 0;i<value.size();i++){
//		std::cout<<"(i = "<<i<<") =>"<<std::hex<<value[i]<<std::endl;
//	}

}
void numberBECv2::copyValueFromVector(const std::vector<uint64_t>& vec){
	value.clear();
	for(int i = 0;i<vec.size();i++){
		value.push_back(vec[i]);
	}

}
unsigned int numberBECv2::getPolyOrder(){
	return numberBECv2::polyOrder;
}
void numberBECv2::calcPolyOrder(){

	uint64_t mask = ((uint64_t) 1)<<63;
	uint64_t orderi;
	for(int i = (numberBECv2::poly.size()-1);i>=0;i--){
		orderi = 64*(i+1);
		int counter = 64;
		while(mask > 0 && (numberBECv2::poly[i] & mask ) == 0){
			mask>>=1;
			orderi--;
			counter--;
		}
		if(counter > 0){
			numberBECv2::polyOrder = orderi - 1;
			numberBECv2::polynomeIsSet = true;
			break;
		}
	}
//	std::cout<<"polyOrder = "<<polyOrder<<std::endl;

}
unsigned int numberBECv2::getOrder(){
	order = 0;
	uint64_t mask = ((uint64_t) 1)<<63;
	uint64_t orderi;
	for(int i = (value.size()-1);i>=0;i--){
		orderi = 64*(i+1);
		int counter = 64;
		while(mask > 0 && (value[i] & mask ) == 0){
			mask>>=1;
			orderi--;
			counter--;
		}
		if(counter > 0){
			order = orderi - 1;
			return order;
		}
	}
	return order;
}
void numberBECv2::printPoly(){
	std::string s = this->getAsPoly();
	std::cout<<s<<std::endl;
}
void numberBECv2::setFromPolyCoeffs(const std::vector<uint64_t>& v){
	value.clear();
	uint64_t tmp = 0;
	for(int i = 0;i<v.size();i++){
//		std::cout<<"loop : v[i="<<i<<"] = "<<v[i]<<std::endl;
		int n = v[i] / 64;
		if(n > 0 && value.size() < n){
			int N = value.size();
//			std::cout<<"rest : tmp = "<<tmp<<std::endl;
//			std::cout<<"rest : n = "<<n<<std::endl;
//			std::cout<<"rest : value.size() = "<<value.size()<<std::endl;
			for(int j = 0;j<(n-N);j++) {value.push_back(tmp);tmp=0;}
//			std::cout<<"rest : ===> insert"<<std::endl;
//			std::cout<<"rest : value.size() = "<<value.size()<<std::endl;
			tmp = 0;
		}
		tmp += (uint64_t) 1 << (v[i]%64);
//		std::cout<<"loop : tmp = "<<tmp<<std::endl;
	}
	if(tmp > 0){
		int n = v[v.size()-1] / 64 + 1;
		int N = value.size();
//		std::cout<<"exit : tmp = "<<tmp<<std::endl;
//		std::cout<<"exit : n = "<<n<<std::endl;
//		std::cout<<"exit : v.size() = "<<N<<std::endl;
		for(int j = 0;j<(n-N);j++) {value.push_back(tmp);tmp=0;}
	}

}
numberBECv2 numberBECv2::getPoly(){
	return numberBECv2(numberBECv2::poly);
}
bool numberBECv2::isPolySet(){
	return numberBECv2::polynomeIsSet;
}
std::ostream& operator<<(std::ostream& os,const  numberBECv2& n)
{
	os  << std::hex<<"0x";

	for(int i = (n.value.size()-1);i>=0;i--){
		os<<n.value[i];
	}

	os<<std::dec;
	return os;
}
numberBECv2 numberBECv2::operator+(const numberBECv2& B){
	numberBECv2 C;
	numberBECv2 b(B);
	numberBECv2 * Small,* Big;
	C.value.clear();
	if(value.size() < B.value.size()){
		Small = this;
		Big = &b;
	}else{
		Small = &b;
		Big = this;

	}

	int i = 0;
	for(i = 0;i <Small->value.size();i++){
		C.value.push_back(Small->value[i] ^ Big->value[i]);
	}
	for(;i<Big->value.size();i++){
		C.value.push_back(Big->value[i]);
	}
	C.Normalize();
	return C;
}
void numberBECv2::addPoly(){
	int i = 0;
	int Small,Big;
	if(numberBECv2::poly.size() < size()){
		Small = numberBECv2::poly.size();
		Big = size();
	}else{
		Big = numberBECv2::poly.size();
		Small = size();

	}

	for(i = 0;i <Small;i++){
		value[i] ^= numberBECv2::poly[i];
	}
	if(Big == value.size()) return;
	for(;i<Big;i++){
		value.push_back(numberBECv2::poly[i]);
	}
	Normalize();
}
numberBECv2 numberBECv2::operator*(const numberBECv2& B){
	numberBECv2 C(*this);
	if(numberBECv2::polynomeIsSet == false || numberBECv2::polyOrder == 0) return C;
	numberBECv2 PolyN(numberBECv2::poly);
	numberBECv2 A;
	int counter = 0;

//	std::cout<<"this = "<<(*this)<<std::endl;
//	std::cout<<"B = "<<B<<std::endl;
	uint64_t mask = 1;
	uint64_t polyMask = (((int64_t) 1)<<polyJ);
	for(int j = 0;j < B.value.size();j++){
		mask = 1;
//		std::cout<<"j = "<<j<<std::endl;
//		std::cout<<"value[j] = "<<std::hex<<value[j]<<std::endl;
		for(int i = 0;i<64;i++){
//			if(log && counter < 5){
//				std::cout<<"0 C.getAsPoly() = "<<C.getAsPoly()<<std::endl;
//			}
			if((B.value[j]&mask) != 0){
				A += C;
//				std::cout << "A = "<<A<<std::endl;
			}
//			if(log && counter < 5){
//				std::cout<<"1 C.getAsPoly() = "<<C.getAsPoly()<<std::endl;
//			}
			C <<=1;
			mask <<=1;

//			if(log && counter < 5){
//				std::cout<<"2 C.getAsPoly() = "<<C.getAsPoly()<<std::endl;
//				std::cout<<"polyI = "<<polyI<<std::endl;
//				std::cout<<"polyMask = "<<polyMask<<std::endl;
//				std::cout<<"C.value[polyI] = "<<C.value[polyI]<<std::endl;
//			}
			if(C.value.size() > numberBECv2::polyI && (C.value[numberBECv2::polyI] & polyMask) != 0){
//				if(counter < 3){
//					counter++;
//				if(log)
//					std::cout<<"C.getAsPoly() = "<<C.getAsPoly()<<std::endl;
//
//				}
				C.addPoly();
			}
//			if(log && counter < 5){
//				std::cout<<"3 C.getAsPoly() = "<<C.getAsPoly()<<std::endl;
//				counter++;
//			}
		}
	}
	A.Normalize();
	return A;
}
void numberBECv2::Normalize(){
	for(int i = (value.size()-1);i>=0;i--){
		if(value[i] != 0) break;
		value.pop_back();
	}
	if(value.size() == 0) value.push_back(0);
}
numberBECv2 numberBECv2::operator/(const numberBECv2& B){

	numberBECv2 C(B);
	C.inv();
//	std::cout<<"C = "<<C<<std::endl;
//	std::cout<<"(*this) = "<<(*this)<<std::endl;
	numberBECv2  A = (*this) * C;
	return A;
}
numberBECv2 operator/(int n,const numberBECv2& B){
	numberBECv2 R;
	if(n != 1)
		return R;
	R = numberBECv2(B);
	R.inv();
	return R;
}
void numberBECv2::operator+=(const numberBECv2& B){
	int Small,Big;
	if(value.size() < B.value.size()){
		Small = value.size();
		Big = B.value.size();
	}else{
		Big = value.size();
		Small = B.value.size();
	}
	int i = 0;
	for(i = 0;i <Small;i++){
		this->value[i] ^=B.value[i];
	}
	if(Big == value.size()) return;
	for(;i<Big;i++){
		value.push_back(B.value[i]);
	}

}
bool numberBECv2::isBitSet(int n){
	int i = n / 64;
	int j = n % 64;
	return i < value.size() && (value[i] & (int64_t) 1<<j) != 0;
}
numberBECv2 numberBECv2::operator<<(int nBits){
		numberBECv2 A;
		A.value.clear();
		for(int i = 0;i<this->value.size();i++){
			A.value.push_back(this->value[i]<<nBits);
		}
		for(int i = 1;i <A.value.size();i++){
			A.value[i] += (this->value[i-1] >> (64-nBits)) &  (((uint64_t) 1<<nBits) - 1);
		}
		A.value.push_back((this->value[A.value.size()-1] >> (64-nBits)) &  (((uint64_t) 1<<nBits) - 1));
		return A;
}
numberBECv2 numberBECv2::operator>>(int nBits){
	numberBECv2 A;
	A.value.clear();
	for(int i = 0;i<this->value.size();i++){
		A.value.push_back(value[i]>>nBits);
	}
	for(int i = 1;i <A.value.size();i++){
		A.value[i-1] += (value[i]  &  (((uint64_t) 1<<nBits) - 1))<<(64-nBits);
	}
	if(A[A.size()-1] == 0){
		A.value.pop_back();
	}
	return A;

}
uint64_t numberBECv2::operator[](int i){
	return value[i];
}
unsigned int numberBECv2::size(){
	return value.size();
}


void numberBECv2::operator<<=(int nBits){
	std::vector<uint64_t> save;
	for(int i = 0;i<this->value.size();i++){
		save.push_back(this->value[i]<<nBits);
	}
	for(int i = 1;i <save.size();i++){
		save[i] += (value[i-1] >> (64-nBits)) &  (((uint64_t) 1<<nBits) - 1);
	}
	save.push_back((value[value.size()-1] >> (64-nBits)) &  (((uint64_t) 1<<nBits) - 1));

	value.swap(save);

}
void numberBECv2::operator>>=(int nBits){
		std::vector<uint64_t> save;
		for(int i = 0;i<this->value.size();i++){
			save.push_back(value[i]>>nBits);
		}
		for(int i = 1;i <save.size();i++){
			save[i-1] += (value[i]  &  (((uint64_t) 1<<nBits) - 1))<<(64-nBits);
		}
		value.swap(save);
}
numberBECv2 numberBECv2::operator=(const numberBECv2& A){

	this->copyValueFromVector(A.value);
	return (*this);
}
numberBECv2 numberBECv2::operator&(const numberBECv2& B){
	numberBECv2 C;
	numberBECv2 b(B);
	numberBECv2 * Small,* Big;
	value.clear();
	int i = 0;
	if(this->value.size() < B.value.size()){
		Small = this;
		Big = &b;
	}else{
		Small = &b;
		Big = this;

	}

	for(i = 0;i <Small->value.size();i++){
		C.value.push_back(Small->value[i] & Big->value[i]);
	}
	for(;i<Big->value.size();i++){
		C.value.push_back(Big->value[i]);
	}
	return C;
}
numberBECv2::~numberBECv2() {
	numberBECv2::destructed++;
	// TODO Auto-generated destructor stub
}
void numberBECv2::setPoly(const numberBECv2& P){
	copyPolyFromVector(P.value);
	calcPolyOrder();
	numberBECv2::polyI = numberBECv2::polyOrder / 64;
	numberBECv2::polyJ = numberBECv2::polyOrder % 64;

}

std::string numberBECv2::getAsPoly(){
	std::string s = "";
	bool isSet = false;

	for(int i = (value.size()-1);i>=0;i--){
		uint64_t mask = (int64_t) 1 << 63;

		for(int j = 0;j<64;j++){
			if((value[i] & mask) != 0){
				int number = (i+1)*64-1-j;
				std::string intStr = std::to_string(number);
				if(isSet == false){
					if(number == 0) s += " 1";
					else if(number == 1) s += " x";
					else s += " x^" + intStr;
				}
				else{
					if(number == 0) s += " + 1";
					else if(number == 1) s += " + x";
					else s += " + x^" + intStr;
				}
				isSet = true;
			}
			mask >>=1;
		}
	}
	if(isSet == false) s += " 0";

	return s;

}
void numberBECv2::clearAllDatas(){
	value.clear();
	order = 0;
	this->clearPoly();

}
numberBECv2 numberBECv2::operator=(const char * s){
	numberBECv2 A(s);
	(*this) = A;
}
numberBECv2 numberBECv2::operator=(const int& n){
	value.clear();
	value.push_back(n);
	return (*this);
}
void numberBECv2::copyPolyFromVector(const std::vector<uint64_t>& vec){
	numberBECv2::poly.clear();
	for(int i = 0;i<vec.size();i++){
		numberBECv2::poly.push_back(vec[i]);
	}

}
std::string numberBECv2::getIrrPoly(){
	numberBECv2 K(numberBECv2::poly);
	return K.getAsPoly();

}
void numberBECv2::clearPoly(){
	numberBECv2::polyOrder = 0;
	numberBECv2::poly.clear();
	numberBECv2::polynomeIsSet = false;

}

bool  numberBECv2::operator==(const numberBECv2 &B){
	if(value.size() != B.value.size()) return false;
	for(int i = 0;i<this->value.size();i++){
		if(value[i] != B.value[i]) return false;
	}
	return true;
}
bool operator==(int n,const numberBECv2 &B){
	numberBECv2 N(n);
	return N == B;
}
bool operator==(const numberBECv2 &B, int n){
	numberBECv2 N(n);
	return N == B;
}
bool  numberBECv2::operator==(int n){
	numberBECv2 N(n);
	return (*this) == N;

}
void numberBECv2::inv(){
		numberBECv2 S(numberBECv2::poly);
		numberBECv2 R(*this);
		numberBECv2 V;
		numberBECv2 U(1);
//		std::cout<<"polyOrder = "<<polyOrder<<std::endl;
//		std::cout<<"poly = "<<S<<std::endl;
		int teta = 0;
		for (int i = 0;i<(2*(numberBECv2::polyOrder));i++){
			if(!R.isBitSet(numberBECv2::polyOrder)){
				R <<=1;
				U <<=1;
				teta++;
			}else{
				if(S.isBitSet(numberBECv2::polyOrder)){
					S += R;
					V += U;
				}
				S <<=1;
				if(teta == 0){
					S.swap(R);

					numberBECv2 tmp = V <<1;
					U.swap(tmp);
					V = tmp;
					teta = 1;
				}else{
					U >>=1;
					teta--;
				}
			}

		}
		(*this) = U;
		this->Normalize();
}
void numberBECv2::swap(numberBECv2& n){
	value.swap(n.value);
}
