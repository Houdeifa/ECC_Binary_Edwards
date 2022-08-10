/*
 * coordinatesBEC.cpp
 *
 *  Created on: 8 août 2022
 *      Author: a858370
 */

#include "coordinatesBEC.h"

void coordinatesBEC::setD(const numberBEC& D){
	d = numberBEC(D);
}
void coordinatesBEC::setCoords(const numberBEC& X,const numberBEC& Y,const numberBEC& Z){
	x = numberBEC(X);
	y = numberBEC(Y);
	z = numberBEC(Z);
	if(!z.isPolySet()){
		if(x.isPolySet()){
			z.setPoly(x.getPoly());
		}else{
			z.setPoly(y.getPoly());

		}
	}
}
numberBEC coordinatesBEC::getX(){
	return x;
}
numberBEC coordinatesBEC::getY(){
	return y;
}
numberBEC coordinatesBEC::getZ(){
	return z;
}
numberBEC coordinatesBEC::getD(){
	return d;
}
coordinatesBEC::coordinatesBEC(){
	x = numberBEC(0);
	y = numberBEC(0);
	z = numberBEC(1);
	d = numberBEC(1);
}
coordinatesBEC::coordinatesBEC(const numberBEC& X,const numberBEC& Y){
	x = numberBEC(X);
	y = numberBEC(Y);
	z = numberBEC(1);
	d = numberBEC(1);
	if(x.isPolySet()){
		z.setPoly(x.getPoly());
		d.setPoly(x.getPoly());
	}else if(y.isPolySet()){
		z.setPoly(y.getPoly());
		d.setPoly(y.getPoly());
	}
}
coordinatesBEC::coordinatesBEC(const coordinatesBEC& N){
	x = N.x;
	y = N.y;
	z = N.z;
	d = N.d;
}
coordinatesBEC::coordinatesBEC(const numberBEC& X,const numberBEC& Y,const numberBEC& Z){
	x = numberBEC(X);
	y = numberBEC(Y);
	z = numberBEC(Z);
	d = numberBEC(1);
}
coordinatesBEC::coordinatesBEC(const numberBEC& X,const numberBEC& Y,const numberBEC& Z,const numberBEC& D){
	x = numberBEC(X);
	y = numberBEC(Y);
	z = numberBEC(Z);
	d = numberBEC(D);
}
coordinatesBEC::~coordinatesBEC() {
	// TODO Auto-generated destructor stub
}

void coordinatesBEC::calculate_normal_coords(){
	x = x / z;
	y = y / z;
	z = numberBEC(1);
	z.setPoly(x.getPoly());
}
void coordinatesBEC::setPoly(const numberBEC& P){
	x.setPoly(P);
	y.setPoly(P);
	z.setPoly(P);
	d.setPoly(P);
}


coordinatesBEC operator+(coordinatesBEC& N1, coordinatesBEC& N2){
	numberBEC X1( N1.getX());
	numberBEC X2( N2.getX());
	numberBEC Y1( N1.getY());
	numberBEC Y2( N2.getY());
	numberBEC Z1( N1.getZ());
	numberBEC Z2( N2.getZ());
	numberBEC d = N1.getD();
	numberBEC W1 = X1 + Y1;
	numberBEC W2 = X2 + Y2;
	numberBEC A = X1 * (X1 + Z1);
	numberBEC B = Y1 * (Y1 + Z1);
	numberBEC C =  Z1 *  Z2;
	numberBEC D =  W2 * Z2;
	numberBEC E =  d * (C*C);
	numberBEC H = (d*Z2 + d*W2)*W1*C;
	numberBEC I = d * C * Z1;
	numberBEC U = E + A*D;
	numberBEC V = E + B*D;
	numberBEC S = U * V;
	numberBEC X3 = S*Y1 + (H + X2*(I + A * (Y2 + Z2))) * V * Z1;
	numberBEC Y3 = S*X1 + (H + Y2*(I + B * (X2 + Z2))) * U * Z1;
	numberBEC Z3 = S * Z1;
	coordinatesBEC Ret(X3,Y3,Z3,d);
	return Ret;
}
coordinatesBEC operator*(int n, const coordinatesBEC& B){
	return numberBEC(n) * B;
}
coordinatesBEC operator*(const numberBEC& N,const  coordinatesBEC& b){
	coordinatesBEC B(b);
	numberBEC n(N);
	if (n == 0) return coordinatesBEC();
	if(n == 1) return coordinatesBEC(B);
	else if(n == 2){
		std::cout<<"here"<<std::endl;
		numberBEC X1 = B.getX();
		numberBEC Y1 = B.getY();
		numberBEC Z1 = B.getZ();
		numberBEC d = B.getD();
		numberBEC A = X1 * X1;
		numberBEC B = A * A;
		numberBEC C = Y1 * Y1;
		numberBEC D = C * C;
		numberBEC E = Z1 * Z1;
		numberBEC F = d * (E * E);
		numberBEC G = (B+D);
		numberBEC H = A * E;
		numberBEC I = C * E;
		numberBEC J = H + I;
		numberBEC K = G + d * J;
		numberBEC Z3 = F + J + G;
		numberBEC X3 = K + H + D;
		numberBEC Y3 = K + I + B;

		coordinatesBEC Ret(X3,Y3,Z3,d);
		return Ret;
	}else{
		coordinatesBEC R0;
		coordinatesBEC R1(B);
		int order = 0;
		for(int i = order;i>=0;i--){
			if(n.isBitSet(i)){
				R1 = R0 + R1;
				R0 = 2*R0;
			}else{
				R0 = R0 + R1;
				R1 = 2*R0;
			}
		}
		coordinatesBEC Ret(R1);
		return Ret;
	}
}
coordinatesBEC operator*(unsigned int n, coordinatesBEC& B){
	 numberBEC k(n);
	 return k * B;
}
