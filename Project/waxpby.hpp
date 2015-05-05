#ifndef COMPUTE_WAXPBY_HPP
#define COMPUTE_WAXPBY_HPP

#include "vector_lee.hpp"
#include <cassert>

int ComputeWAXPBY(const double alpha, const Vector& x, const double beta, const Vector& y, Vector& w)
{	// w = alpha*x + beta* y
	int n = x.localLength; 
	const double* const xv = x.values;
	const double* const yv = y.values;
	double* const wv = w.values;

	if(alpha==1.0) 
	{
		for(local_int_t i=0; i<n; i++) wv[i] = xv[i] + beta * yv[i];
	}
	else if(beta == 1.0)
	{
		for(local_int_t i=0; i<n; i++) wv[i] = alpha * xv[i] + yv[i];
	}
	else{
		for(local_int_t i=0; i<n; i++) wv[i] = alpha * xv[i] + beta * yv[i];
	}

	return 0;
}

#endif
	



