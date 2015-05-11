#ifndef CG_HPP
#define CG_HPP

#include "sp_lee.hpp"
#include "vector_lee.hpp"
#include "spmv.hpp"
#include "dot_product.hpp"
#include "waxpby.hpp"

#include <iostream>
#include <cmath> 

int cg(const SparseMatrix& A, const Vector& b, Vector& x, const int max_iter, const double eps, int & cur_iter)
{
	double normr = 0.0 ,rtr = 0.0, oldrtr = 0.0, alpha =0.0, beta = 0.0, dAd = 0.0;
	local_int_t nrow = A.localNumberOfRows;
	local_int_t ncol = A.localNumberOfColumns;
	Vector r, d, Ad;
	InitializeVector(r, nrow); //residual vector
	InitializeVector(d, ncol); // direction vector
	InitializeVector(Ad, nrow); // A * d
	
	CopyVector(x, d);  //initial d
	spmv(A, d, Ad);    //initial Ad
	ScalarProduct(1.0, b, -1.0, Ad, r); //initial r=b-Ax
	DotProduct(r, r, normr);  
	normr = sqrt(normr);

	double normr0 = normr;

	for(int k=0; k<max_iter && normr/normr0 > eps; k++)
	{
		if(k==0)
		{ 
		//initial search direction along initial residual
			CopyVector(r, d); 
			DotProduct(r, r, rtr); // rtr = r' * r
		}else
		{
			oldrtr = rtr;
			DotProduct(r, r, rtr); // current rtr
			beta = rtr/oldrtr; 
			//update search direction
			ScalarProduct(1.0, r, beta, d, d);
		}

		// alpha = rtr / dAd 
		spmv(A, d, Ad);
	        DotProduct(d, Ad, dAd);
		alpha = rtr / dAd;
		ScalarProduct(1.0, x, alpha, d, x); // x = x + alpha * d	
		ScalarProduct(1.0, r, -alpha, Ad, r); // r = r - alpha* Ad
		DotProduct(r, r, normr); 
		normr = sqrt(normr);

		if(A.geom->rank ==0 && k == max_iter-1)
			std::cout << "Iteration= " << k+1 << "Residual= " << normr/normr0 << std::endl;
		cur_iter = k;
	}

	return 0;
}


#endif
