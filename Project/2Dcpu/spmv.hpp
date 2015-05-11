#ifndef SPMV_H
#define SPMV_H

#include "sp_lee.hpp"
#include "vector_lee.hpp"
#include "buffer_matrix.hpp"

int spmv(const SparseMatrix& A, Vector& x, Vector& y)
{
	buffer_matrix(A,x);

	const double* const xv = x.values;
	double* const yv = y.values;
	const local_int_t nrow = A.localNumberOfRows;

	for(local_int_t i=0; i<nrow; i++)
	{
		double sum = 0.0;
		const double* const cur_vals = A.matrixValues[i];
		const local_int_t* const cur_inds = A.mtxIndL[i];
		const int cur_nnz = A.nonzerosInRow[i];

		for(int j=0; j<cur_nnz; j++)
			sum += cur_vals[j] * xv[cur_inds[j]];

		yv[i] = sum;
	}

	return 0;
}

#endif
