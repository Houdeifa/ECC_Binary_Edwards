/*
 * coordinatesBEC.h
 *
 *  Created on: 8 août 2022
 *      Author: a858370
 */

#ifndef COORDINATESBEC_H_
#define COORDINATESBEC_H_
#include "numberBECv2.h"
class coordinatesBEC {
	numberBECv2 x;
	numberBECv2 y;
	numberBECv2 z;
	numberBECv2 d;
public:
	bool log = false;
	numberBECv2 getX();
	numberBECv2 getY();
	numberBECv2 getZ();
	numberBECv2 getD();
	void setD(const numberBECv2& D);
	void calculate_normal_coords();
	void setCoords(const numberBECv2& X,const numberBECv2& Y,const numberBECv2& Z);
	coordinatesBEC();
	coordinatesBEC(const numberBECv2& X,const numberBECv2& Y);
	coordinatesBEC(const numberBECv2& X,const numberBECv2& Y, const numberBECv2& Z);
	coordinatesBEC(const numberBECv2& X,const numberBECv2& Y,const numberBECv2& Z,const numberBECv2& D);
	coordinatesBEC(const coordinatesBEC& N);
	friend std::ostream& operator<<(std::ostream& os,const coordinatesBEC& n);
	void  operator+=( coordinatesBEC& B);
	void  operator*=( numberBECv2& B);
	void  operator*=( int B);
	 friend coordinatesBEC operator+(coordinatesBEC& A, coordinatesBEC& B);
	 friend coordinatesBEC operator*(int n,  const coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
	 friend coordinatesBEC operator*(const numberBECv2& n,const  coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
	virtual ~coordinatesBEC();
};

#endif /* COORDINATESBEC_H_ */
