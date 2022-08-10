/*
 * coordinatesBEC.h
 *
 *  Created on: 8 août 2022
 *      Author: a858370
 */

#ifndef COORDINATESBEC_H_
#define COORDINATESBEC_H_
#include "numberBEC.h"
class coordinatesBEC {
	numberBEC x;
	numberBEC y;
	numberBEC z;
	numberBEC d;
public:
	numberBEC getX();
	numberBEC getY();
	numberBEC getZ();
	numberBEC getD();
	void setD(const numberBEC& D);
	void setPoly(const numberBEC& P);
	void calculate_normal_coords();
	void setCoords(const numberBEC& X,const numberBEC& Y,const numberBEC& Z);
	coordinatesBEC();
	coordinatesBEC(const numberBEC& X,const numberBEC& Y);
	coordinatesBEC(const numberBEC& X,const numberBEC& Y, const numberBEC& Z);
	coordinatesBEC(const numberBEC& X,const numberBEC& Y,const numberBEC& Z,const numberBEC& D);
	coordinatesBEC(const coordinatesBEC& N);

	 friend coordinatesBEC operator+(coordinatesBEC& A, coordinatesBEC& B);
	 friend coordinatesBEC operator*(int n,  const coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
	 friend coordinatesBEC operator*(const numberBEC& n,const  coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
	virtual ~coordinatesBEC();
};

#endif /* COORDINATESBEC_H_ */
