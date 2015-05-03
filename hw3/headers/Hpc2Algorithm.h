/*#ifndef MATRIX_H_
#define MATRIX_H_
#ifndef VECTOR_H_
#define VECTOR_H_
*/

#include "Matrix.h"
#include <iostream>

//class Hpc2Algorithm
	int CG( Matrix& A, Vector& x,  Vector& b, int& max_iter, double& tol);
	int CGS(); //Cojugate Gradient Squared
	int BiCG(); //BiConjugate Gradient
	int BiCGSTAB(); //BiConjuagate Gradient Stabilized
	int GMRES(); //General Minimum Residual
	int QMR(); // Quasi Minimal Residual
//#endif

