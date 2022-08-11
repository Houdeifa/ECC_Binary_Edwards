//============================================================================
// Name        : main.cpp
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Test bench file to test the operation
//============================================================================

#include <iostream>
#include "number.h"
#include "numberBECv2.h"
#include "coordinatesBEC.h"
#include <cstdint>
#include <vector>
#include <chrono>


int main() {
	numberBECv2 P;
	P.setFromPolyCoeffs(std::vector<uint64_t>({0,159,223}));
	numberBECv2 D;
	D.setFromPolyCoeffs(std::vector<uint64_t>({0,5,36,64}));
	numberBECv2 X = "205bfedd71b0b0fdfeb3345af71cc721790e83c4b88094e9a63f6d43";
	numberBECv2 Y = "205bfeddf1b0b0fd7eb3345af71cc721790e83c4b88094e9a63f6d43";
	numberBECv2::setPoly(P);
	std::cout<<"P(x) = "<<P.getAsPoly()<<std::endl;
	std::cout<<"X = "<<X<<std::endl;
	std::cout<<"Y = "<<Y<<std::endl;
	std::cout<<"P(x) = "<<numberBECv2::getIrrPoly()<<std::endl;
	numberBECv2 x2 = X * X;
	numberBECv2 xy = X * Y;
	numberBECv2 y2 = Y * Y;
//	D.log = true;
	numberBECv2 left = D*(X+Y+x2+y2);
	numberBECv2 right = xy + xy*(X + Y) + x2*y2;
	std::cout<<"left = "<<left<<std::endl;
	std::cout<<"right = "<<right<<std::endl;


	coordinatesBEC A(X,Y,numberBECv2(1),D);
	std::cout<<"polyOrder = "<<numberBECv2::getPolyOrder()<<std::endl;
	coordinatesBEC R = A + A;
	R.calculate_normal_coords();
	coordinatesBEC B = R;
	R  = B + A;
	std::cout<<"A added"<<std::endl;
	R.calculate_normal_coords();
	X = R.getX();
	Y = R.getY();
	std::cout<<"X "<<X<<std::endl;
	std::cout<<"Y "<<Y<<std::endl;
	X.log = true;
	x2 = X * X;
	xy = X * Y;
	y2 = Y * Y;
	std::cout<<"X2 "<<x2<<std::endl;
	std::cout<<"Y2 "<<y2<<std::endl;
	left = D*(X+Y+x2+y2);
	right = xy + xy*(X + Y) + x2*y2;
	std::cout<<"left = "<<left<<std::endl;
	std::cout<<"right = "<<right<<std::endl;

	numberBECv2 N = "205bfeddf1b0b0fd7eb3345af71cc721790e83c4b88094e9a63f6d43";
	R = A;
	auto start = std::chrono::high_resolution_clock::now();
	R *= N;
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
	        elapsed).count();
	std::cout<<"time in ms = "<<microseconds<<"ms"<<std::endl;
	std::cout<<"time in s = "<<microseconds/1000<<"s"<<std::endl;
	R.calculate_normal_coords();
	X = R.getX();
	Y = R.getY();
	x2 = X * X;
	xy = X * Y;
	y2 = Y * Y;
	left = D*(X+Y+x2+y2);
	right = xy + xy*(X + Y) + x2*y2;
	std::cout<<"left = "<<left<<std::endl;
	std::cout<<"right = "<<right<<std::endl;
	numberBECv2::print_const_and_dust();
	return 0;
}
