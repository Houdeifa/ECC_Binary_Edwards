/*
 * numberBEC.cpp
 *
 *  Created on: 4 août 2022
 *      Author: a858370
 */

#include "numberBEC.h"

numberBEC::numberBEC(const std::vector<uint64_t>& v){
	copyValueFromVector(v);
}
numberBEC::numberBEC() {
	value.push_back(0);
	poly.push_back(0);

}
numberBEC::numberBEC(const numberBEC& A){
	this->copyValueFromVector(A.value);
	this->copyPolyFromVector(A.poly);
	this->calcPolyOrder();
	if(polyOrder > 0) this->polynomeIsSet = true;
}
numberBEC::numberBEC(int v){
	value.push_back(v);

	uint64_t mask = ((uint64_t) 1)<<63;

	order = 64;
	while(mask > 0 && (v & mask ) == 0){
		mask>>=1;
		order--;
	}
	poly.push_back(0);
	polyOrder = 0;
	polynomeIsSet = false;

}
numberBEC::numberBEC(const char * s){
	std::string str = std::string(s);
	copyFromString(str);
}

void numberBEC::copyFromString(const std::string& s){
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
numberBEC::numberBEC(const std::string& s){
	std::cout<<"creating 4"<<std::endl;
	copyFromString(s);

//	for(int i = 0;i<value.size();i++){
//		std::cout<<"(i = "<<i<<") =>"<<std::hex<<value[i]<<std::endl;
//	}

}
void numberBEC::copyValueFromVector(const std::vector<uint64_t>& vec){
	value.clear();
	for(int i = 0;i<vec.size();i++){
		value.push_back(vec[i]);
	}

}
unsigned int numberBEC::getPolyOrder(){
	return polyOrder;
}
void numberBEC::calcPolyOrder(){

	uint64_t mask = ((uint64_t) 1)<<63;
	uint64_t orderi;
	for(int i = (poly.size()-1);i>=0;i--){
		orderi = 64*(i+1);
		int counter = 64;
		while(mask > 0 && (poly[i] & mask ) == 0){
			mask>>=1;
			orderi--;
			counter--;
		}
		if(counter > 0){
			polyOrder = orderi - 1;
			polynomeIsSet = true;
			break;
		}
	}
//	std::cout<<"polyOrder = "<<polyOrder<<std::endl;

}
unsigned int numberBEC::getOrder(){
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
void numberBEC::printPoly(){
	std::string s = this->getAsPoly();
	std::cout<<s<<std::endl;
}
void numberBEC::setFromPolyCoeffs(const std::vector<uint64_t>& v){
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
numberBEC numberBEC::getPoly(){
	return numberBEC(poly);
}
bool numberBEC::isPolySet(){
	return polynomeIsSet;
}
std::ostream& operator<<(std::ostream& os,const  numberBEC& n)
{
	os  << std::hex<<"0x";

	for(int i = (n.value.size()-1);i>=0;i--){
		os<<n.value[i];
	}

	os<<std::dec;
	return os;
}
numberBEC numberBEC::operator+(const numberBEC& B){
	numberBEC C;
	numberBEC b(B);
	numberBEC * Small,* Big;
	C.value.clear();
	C.poly.clear();
	int i = 0;
	for(i = 0;i<this->poly.size();i++){
		C.poly.push_back(poly[i]);
	}
	if(value.size() < B.value.size()){
		Small = this;
		Big = &b;
	}else{
		Small = &b;
		Big = this;

	}

	for(i = 0;i <Small->value.size();i++){
		C.value.push_back(Small->value[i] ^ Big->value[i]);
	}
	for(;i<Big->value.size();i++){
		C.value.push_back(Big->value[i]);
	}
	C.calcPolyOrder();
	C.Normalize();
	return C;
}
void numberBEC::addPoly(){
	int i = 0;
	int Small,Big;
	if(poly.size() < size()){
		Small = poly.size();
		Big = size();
	}else{
		Big = poly.size();
		Small = size();

	}

	for(i = 0;i <Small;i++){
		value[i] ^= poly[i];
	}
	if(Big == value.size()) return;
	for(;i<Big;i++){
		value.push_back(poly[i]);
	}
	Normalize();
}
numberBEC numberBEC::operator*(const numberBEC& B){
	numberBEC C(*this);
	if(polynomeIsSet == false || polyOrder == 0) return C;
	numberBEC PolyN(this->poly);
	numberBEC A;
	int counter = 0;
//	if(log){
//		std::cout<<"polyOrder = "<<polyOrder<<std::endl;
//		std::cout<<"polyOrder = "<<getIrrPoly()<<std::endl;
//		std::cout<<"PolyN = "<<PolyN.getAsPoly()<<std::endl;
//	}

//	std::cout<<"this = "<<(*this)<<std::endl;
//	std::cout<<"B = "<<B<<std::endl;
	uint64_t mask = 1;
	int polyI = polyOrder / 64;
	int polyJ = polyOrder % 64;
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
			if(C.value.size() > polyI && (C.value[polyI] & polyMask) != 0){
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
//	std::cout<<"A 0 = "<<A<<std::endl;
	A.setPoly(PolyN);
//	std::cout<<"A 1 = "<<A<<std::endl;
	A.Normalize();
//	std::cout<<"A 1 = "<<A<<std::endl;
	return A;
}
void numberBEC::Normalize(){
	for(int i = (value.size()-1);i>=0;i--){
		if(value[i] != 0) break;
		value.pop_back();
	}
	if(value.size() == 0) value.push_back(0);
}
numberBEC numberBEC::operator/(const numberBEC& B){

	numberBEC C(B);
	C.inv();
	C.calcPolyOrder();
	calcPolyOrder();
//	std::cout<<"C = "<<C<<std::endl;
//	std::cout<<"(*this) = "<<(*this)<<std::endl;
	numberBEC  A = (*this) * C;
	return A;
}
numberBEC operator/(int n,const numberBEC& B){
	numberBEC R;
	if(n != 1)
		return R;
	R = numberBEC(B);
	R.calcPolyOrder();
	R.inv();
	return R;
}
void numberBEC::operator+=(const numberBEC& B){
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
bool numberBEC::isBitSet(int n){
	int i = n / 64;
	int j = n % 64;
	return i < value.size() && (value[i] & (int64_t) 1<<j) != 0;
}
numberBEC numberBEC::operator<<(int nBits){
		numberBEC A;
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
numberBEC numberBEC::operator>>(int nBits){
	numberBEC A;
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
uint64_t numberBEC::operator[](int i){
	return value[i];
}
unsigned int numberBEC::size(){
	return value.size();
}


void numberBEC::operator<<=(int nBits){
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
void numberBEC::operator>>=(int nBits){
		std::vector<uint64_t> save;
		for(int i = 0;i<this->value.size();i++){
			save.push_back(value[i]>>nBits);
		}
		for(int i = 1;i <save.size();i++){
			save[i-1] += (value[i]  &  (((uint64_t) 1<<nBits) - 1))<<(64-nBits);
		}
		value.swap(save);
}
numberBEC numberBEC::operator=(const numberBEC& A){

	this->copyValueFromVector(A.value);
	this->copyPolyFromVector(A.poly);
	this->calcPolyOrder();
	return (*this);
}
numberBEC numberBEC::operator&(const numberBEC& B){
	numberBEC C;
	numberBEC b(B);
	numberBEC * Small,* Big;
	C.value.clear();
	C.poly.clear();
	int i = 0;
	for(i = 0;i<this->poly.size();i++){
		C.value.push_back(this->value[i]);
	}
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
numberBEC::~numberBEC() {
	// TODO Auto-generated destructor stub
}
void numberBEC::setPoly(const numberBEC& P){
	poly.clear();
	this->copyPolyFromVector(P.value);
	int ValueIndex = 0;
	for(int i = (poly.size() - 1);i>=0;i--){
		if(poly[i] != 0){
			polynomeIsSet = true;
			ValueIndex = i;
			uint64_t mask = (uint64_t)1 << 63;
			for(int j = 0;j<64;j++){
				if((poly[i] & mask) != 0){
					polynomeIsSet = true;
					polyOrder = 63-j;
					break;
				}
				mask>>=1;
			}
			break;

		}
	}
	if(polynomeIsSet){
		polyOrder += 64*ValueIndex;
	}

}

std::string numberBEC::getAsPoly(){
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
void numberBEC::clearAllDatas(){
	value.clear();
	order = 0;
	this->clearPoly();

}
numberBEC numberBEC::operator=(const char * s){
	numberBEC A(s);
	(*this) = A;
}
numberBEC numberBEC::operator=(const int& n){
	value.clear();
	value.push_back(n);
	return (*this);
}
void numberBEC::copyPolyFromVector(const std::vector<uint64_t>& vec){
	poly.clear();
	for(int i = 0;i<vec.size();i++){
		poly.push_back(vec[i]);
	}

}
std::string numberBEC::getIrrPoly(){
	numberBEC K(this->poly);
	return K.getAsPoly();

}
void numberBEC::clearPoly(){
	polyOrder = 0;
	poly.clear();
	polynomeIsSet = false;

}

bool  numberBEC::operator==(const numberBEC &B){
	if(value.size() != B.value.size()) return false;
	for(int i = 0;i<this->value.size();i++){
		if(value[i] != B.value[i]) return false;
	}
	return true;
}
bool operator==(int n,const numberBEC &B){
	numberBEC N(n);
	return N == B;
}
bool operator==(const numberBEC &B, int n){
	numberBEC N(n);
	return N == B;
}
bool  numberBEC::operator==(int n){
	numberBEC N(n);
	return (*this) == N;

}
void numberBEC::inv(){
		numberBEC S(poly);
		numberBEC R(*this);
		numberBEC V;
		numberBEC U(1);
//		std::cout<<"polyOrder = "<<polyOrder<<std::endl;
//		std::cout<<"poly = "<<S<<std::endl;
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
					S.swap(R);

					numberBEC tmp = V <<1;
					U.swap(tmp);
					V = tmp;
					teta = 1;
				}else{
					U >>=1;
					teta--;
				}
			}

		}
		U.setPoly(numberBEC(poly));
		(*this) = U;
		this->calcPolyOrder();
		this->Normalize();
}
void numberBEC::swap(numberBEC& n){
	value.swap(n.value);
	poly.swap(n.poly);
	int tmp = this->polyOrder;
	bool tmpb = this->polynomeIsSet;
	polyOrder = n.polyOrder;
	n.polyOrder = tmp;

	polynomeIsSet = n.polynomeIsSet;
	n.polynomeIsSet = tmpb;
}
