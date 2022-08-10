/*
 * Coordinates.h
 *
 *  Created on: 3 août 2022
 *      Author: a858370
 */

#ifndef COORDINATES_H_
#define COORDINATES_H_
#include "number.h"

class coordinates{
	number x;
	number y;
	number z;
	number d;
public:
	number getX();
	number getY();
	number getZ();
	number getD();
	coordinates();
	coordinates(number& A,number& B);
	coordinates(number& A,number& B, number& C);
	coordinates(number& A,number& B,number& C,number& D);
	coordinates(coordinates& A);
};


#endif /* COORDINATES_H_ */
