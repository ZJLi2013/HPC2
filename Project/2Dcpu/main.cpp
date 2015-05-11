#include <mpi.h>
#include <iostream>

#include "geom_lee.hpp"
#include "vector_lee.hpp"
#include "sp_lee.hpp"
#include "cg.hpp"

/* solving y = A * x */

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);

	/* input */
	Geometry* geom = new Geometry;
	init_geom(*geom);

	/* sparse matrix */
	SparseMatrix A;
	InitialSparseMatrix(A, geom);
	create_matrix(A);
	mpi_matrix(A);

	/* solution vector, rhs vector */
	Vector x, b;
	InitializeVector(x, A.localNumberOfColumns);
	InitializeVector(b, A.localNumberOfRows);
	FillRandomVector(b);
	ZeroVector(x);

	double t1 = MPI_Wtime();

	const int max_iter=100;
	const double eps=1e-6;
	int cur_iter=0;
	int err = cg(A, b, x, max_iter, eps, cur_iter) ;

	double t2 = MPI_Wtime();
	double timing = t2 - t1;
	if(A.geom->rank==0)   std::cout << "timing = " << timing << "\n" << std::endl;
	
	MPI_Finalize();

	return 0;
}
