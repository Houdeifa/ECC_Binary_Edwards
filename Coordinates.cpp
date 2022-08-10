/*
 * Coordinates.cpp
 *
 *  Created on: 3 août 2022
 *      Author: a858370
 */
#include "Coordinates.h"


number coordinates::getX(){
	return x;
}
number coordinates::getY(){
	return y;
}
number coordinates::getZ(){
	return z;
}
number coordinates::getD(){
	return d;
}
coordinates::coordinates(){
	x = number(0);
	y = number(0);
	z = number(1);
	d = number(1);
}
coordinates::coordinates(number& A,number& B){
	x = number(A);
	y = number(B);
	z = number(1);
	d = number(1);
}
coordinates::coordinates(coordinates& A){
	x = A.x;
	y = A.y;
	z = A.z;
	d = A.d;
}
coordinates::coordinates(number& A,number& B,number& C){
	x = number(A);
	y = number(B);
	z = number(C);
	d = number(1);
}
coordinates::coordinates(number& A,number& B,number& C,number& D){
	x = number(A);
	y = number(B);
	z = number(C);
	d = number(D);
}
