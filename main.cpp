//============================================================================
// Name        : main.cpp
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Test bench file to test the operation
//============================================================================

#include <iostream>
#include "number.h"
#include "numberBEC.h"
#include "coordinatesBEC.h"
#include <cstdint>
#include <vector>
#include <chrono>


int main() {
	numberBEC P;
	P.setFromPolyCoeffs(std::vector<uint64_t>({0,159,223}));
	numberBEC D;
	D.setFromPolyCoeffs(std::vector<uint64_t>({0,5,36,64}));
	numberBEC X = "205bfedd71b0b0fdfeb3345af71cc721790e83c4b88094e9a63f6d43";
	numberBEC Y = "205bfeddf1b0b0fd7eb3345af71cc721790e83c4b88094e9a63f6d43";
	std::cout<<"P(x) = "<<P.getAsPoly()<<std::endl;
	std::cout<<"X = "<<X<<std::endl;
	std::cout<<"Y = "<<Y<<std::endl;
	X.setPoly(P);
	Y.setPoly(P);
	D.setPoly(P);
	numberBEC x2 = X * X;
	numberBEC xy = X * Y;
	numberBEC y2 = Y * Y;
//	D.log = true;
	numberBEC left = D*(X+Y+x2+y2);
	numberBEC right = xy + xy*(X + Y) + x2*y2;
	std::cout<<"left = "<<left<<std::endl;
	std::cout<<"right = "<<right<<std::endl;


	coordinatesBEC A(X,Y,numberBEC(1),D);
	A.setPoly(P);
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
	x2 = X * X;
	xy = X * Y;
	y2 = Y * Y;
	left = D*(X+Y+x2+y2);
	right = xy + xy*(X + Y) + x2*y2;
	std::cout<<"left = "<<left<<std::endl;
	std::cout<<"right = "<<right<<std::endl;

	numberBEC N = "205bfeddf1b0b0fd7eb3345af71cc721790e83c4b88094e9a63f6d43";
	auto start = std::chrono::high_resolution_clock::now();
	R = A;
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

	return 0;
}
