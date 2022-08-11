/*
 * coordinatesBEC.cpp
 *
 *  Created on: 8 août 2022
 *      Author: a858370
 */

#include "coordinatesBEC.h"

void coordinatesBEC::setD(const numberBECv2& D){
	d = numberBECv2(D);
}
void coordinatesBEC::setCoords(const numberBECv2& X,const numberBECv2& Y,const numberBECv2& Z){
	x = numberBECv2(X);
	y = numberBECv2(Y);
	z = numberBECv2(Z);
}
numberBECv2 coordinatesBEC::getX(){
	return x;
}
numberBECv2 coordinatesBEC::getY(){
	return y;
}
numberBECv2 coordinatesBEC::getZ(){
	return z;
}
numberBECv2 coordinatesBEC::getD(){
	return d;
}
coordinatesBEC::coordinatesBEC(){
	x = numberBECv2(0);
	y = numberBECv2(0);
	z = numberBECv2(1);
	d = numberBECv2(1);
}
coordinatesBEC::coordinatesBEC(const numberBECv2& X,const numberBECv2& Y){
	x = numberBECv2(X);
	y = numberBECv2(Y);
	z = numberBECv2(1);
	d = numberBECv2(1);
}
coordinatesBEC::coordinatesBEC(const coordinatesBEC& N){
	x = numberBECv2(N.x);
	y = numberBECv2(N.y);
	z = numberBECv2(N.z);
	d = numberBECv2(N.d);
}
coordinatesBEC::coordinatesBEC(const numberBECv2& X,const numberBECv2& Y,const numberBECv2& Z){
	x = numberBECv2(X);
	y = numberBECv2(Y);
	z = numberBECv2(Z);
	d = numberBECv2(1);
}
coordinatesBEC::coordinatesBEC(const numberBECv2& X,const numberBECv2& Y,const numberBECv2& Z,const numberBECv2& D){
	x = numberBECv2(X);
	y = numberBECv2(Y);
	z = numberBECv2(Z);
	d = numberBECv2(D);
}
coordinatesBEC::~coordinatesBEC() {
	// TODO Auto-generated destructor stub
}

void coordinatesBEC::calculate_normal_coords(){
	x = x / z;
	y = y / z;
	z = numberBECv2(1);
}


coordinatesBEC operator+(coordinatesBEC& N1, coordinatesBEC& N2){
	numberBECv2 X1( N1.getX());
	numberBECv2 X2( N2.getX());
	numberBECv2 Y1( N1.getY());
	numberBECv2 Y2( N2.getY());
	numberBECv2 Z1( N1.getZ());
	numberBECv2 Z2( N2.getZ());
	numberBECv2 d = N1.getD();
	numberBECv2 W1 = X1 + Y1;
	numberBECv2 W2 = X2 + Y2;
	numberBECv2 A = X1 * (X1 + Z1);
	numberBECv2 B = Y1 * (Y1 + Z1);
	numberBECv2 C =  Z1 *  Z2;
	numberBECv2 D =  W2 * Z2;
	numberBECv2 E =  d * (C*C);
	numberBECv2 H = (d*Z2 + d*W2)*W1*C;
	numberBECv2 I = d * C * Z1;
	numberBECv2 U = E + A*D;
	numberBECv2 V = E + B*D;
	numberBECv2 S = U * V;
	numberBECv2 X3 = S*Y1 + (H + X2*(I + A * (Y2 + Z2))) * V * Z1;
	numberBECv2 Y3 = S*X1 + (H + Y2*(I + B * (X2 + Z2))) * U * Z1;
	numberBECv2 Z3 = S * Z1;
	coordinatesBEC Ret(X3,Y3,Z3,d);
	return Ret;
}
coordinatesBEC operator*(int n, const coordinatesBEC& B){
	return numberBECv2(n) * B;
}
coordinatesBEC operator*(const numberBECv2& N,const  coordinatesBEC& b){
	coordinatesBEC B(b);
	numberBECv2 n(N);
	if (n == 0) return coordinatesBEC();
	if(n == 1) return coordinatesBEC(B);
	else if(n == 2){
		numberBECv2 X1 = B.getX();
		numberBECv2 Y1 = B.getY();
		numberBECv2 Z1 = B.getZ();
		numberBECv2 d = B.getD();
		numberBECv2 A = X1 * X1;
		numberBECv2 B = A * A;
		numberBECv2 C = Y1 * Y1;
		numberBECv2 D = C * C;
		numberBECv2 E = Z1 * Z1;
		numberBECv2 F = d * (E * E);
		numberBECv2 G = (B+D);
		numberBECv2 H = A * E;
		numberBECv2 I = C * E;
		numberBECv2 J = H + I;
		numberBECv2 K = G + d * J;
		numberBECv2 Z3 = F + J + G;
		numberBECv2 X3 = K + H + D;
		numberBECv2 Y3 = K + I + B;

		coordinatesBEC Ret(X3,Y3,Z3,d);
		return Ret;
	}else{
		coordinatesBEC R0;
		R0.setD(B.getD());
		coordinatesBEC R1(B);
		int order = n.getOrder();
		for(int i = order;i>=0;i--){
			if(n.isBitSet(i)){
				R1 += R0;
				R0 *= 2;
			}else{
				R0 += R1;
				R1 *= 2;
			}
		}
		coordinatesBEC Ret(R1);
		return Ret;
	}
}
void  coordinatesBEC::operator+=( coordinatesBEC& N2){
	numberBECv2 X2( N2.getX());
	numberBECv2 Y2( N2.getY());
	numberBECv2 Z2( N2.getZ());
	numberBECv2 W1 = x + y;
	if(log)
	std::cout<<"W1 = "<<W1<<std::endl;
	numberBECv2 W2 = X2 + Y2;
	numberBECv2 A = x * (x + z);
	numberBECv2 B = y * (y + z);
	numberBECv2 C =  z *  Z2;
	numberBECv2 D =  W2 * Z2;
	numberBECv2 E =  d * (C*C);
	numberBECv2 H = (d*Z2 + d*W2)*W1*C;
	numberBECv2 I = d * C * z;
	numberBECv2 U = E + A*D;
	numberBECv2 V = E + B*D;
	numberBECv2 S = U * V;
	numberBECv2 X3 = S*y + (H + X2*(I + A * (Y2 + Z2))) * V * z;
	y = S*x + (H + Y2*(I + B * (X2 + Z2))) * U * z;
	x = X3;
	z = S * z;
}
void  coordinatesBEC::operator*=( numberBECv2& N){
		numberBECv2 n(N);
		if (n == 0) return;
		if(n == 1) return;
		else if(n == 2){
			numberBECv2 A = x * x;
			numberBECv2 B = A * A;
			numberBECv2 C = y * y;
			numberBECv2 D = C * C;
			numberBECv2 E = z * z;
			numberBECv2 F = d * (E * E);
			numberBECv2 G = (B+D);
			numberBECv2 H = A * E;
			numberBECv2 I = C * E;
			numberBECv2 J = H + I;
			numberBECv2 K = G + d * J;
			z = F + J + G;
			x = K + H + D;
			y = K + I + B;

			return;
		}else{
			coordinatesBEC R0;
			R0.setD(d);
			int order = n.getOrder();
			bool first = true;
			for(int i = order;i>=0;i--){
				if(n.isBitSet(i)){
					(*this) += R0;
					R0 *= 2;
					if(first){
						first = false;
						log = false;
					}
				}else{
					R0 += (*this);
					(*this) *= 2;
				}
			}
			return ;
		}
}
void  coordinatesBEC::operator*=( int n){
if(n != 2) return;
numberBECv2 A = x * x;
numberBECv2 B = A * A;
numberBECv2 C = y * y;
numberBECv2 D = C * C;
numberBECv2 E = z * z;
numberBECv2 F = d * (E * E);
numberBECv2 G = (B+D);
numberBECv2 H = A * E;
numberBECv2 I = C * E;
numberBECv2 J = H + I;
numberBECv2 K = G + d * J;
z = F + J + G;
x = K + H + D;
y = K + I + B;

}
std::ostream& operator<<(std::ostream& os,const coordinatesBEC& n){
	os<<"getX() = "<<n.x<<std::endl;
	os<<"getY() = "<<n.y<<std::endl;
	os<<"getZ() = "<<n.z<<std::endl;
	os<<"getD() = "<<n.d<<std::endl;
}
coordinatesBEC operator*(unsigned int n, coordinatesBEC& B){
	 numberBECv2 k(n);
	 return k * B;
}
