//============================================================================
// Name        : BinaryEdwards.h
// Author      : Houdeifa Aflihaou <houdeifa.aflihaou@gmail.com>
// Version     : 1.0
// Copyright   : Your copyright notice
// Description :
//============================================================================


#ifndef BINARYEDWARDS_H_
#define BINARYEDWARDS_H_
#include "coordinatesBEC.h"
#include "numberBEC.h"

class BinaryEdwards{
 numberBEC d;
 int order;
 numberBEC G;
 numberBEC addition(numberBEC A, numberBEC B);
 numberBEC doubling(numberBEC A);
 numberBEC scalarMultiplication(int n,numberBEC A);
public:
 friend coordinatesBEC operator+(coordinatesBEC& A, coordinatesBEC& B);
 friend coordinatesBEC operator*(int n,  const coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
 friend coordinatesBEC operator*(numberBEC& n, coordinatesBEC& B); //if n = 2 doubling otherwise => scalarMult
};


#endif /* BINARYEDWARDS_H_ */
