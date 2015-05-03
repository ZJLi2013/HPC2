#include <mpi.h>
#include <iostream>

#include "geom_lee.hpp"
#include "vector_lee.hpp"
#include "sp_lee.hpp"
#include "spmv.hpp"

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
	Vector x, y;
	int VecSize = 50;
	InitializeVector(x, VecSize);
	InitializeVector(y,VecSize);
	FillRandomVector(x);
	ZeroVector(y);

	double t1 = MPI_Wtime();
	int err = spmv(A, x, y);	
	if(A.geom->rank==0 && err) std::cout << "SPMV Error" << std::endl;
	double t2 = MPI_Wtime();
	double timing = t2 - t1;
	if(A.geom->rank==0)   std::cout << "timing = " << timing << "\n" << std::endl;
	
	MPI_Finalize();

	return 0;
}
