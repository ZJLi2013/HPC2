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

	Vector x;
	InitializeVector(x, A.localNumberOfColumns);
	buffer_matrix(A, x);
	
	if(geom->rank ==0)  std::cout << "buffer done" << std::endl;

	MPI_Finalize();

	return 0;
}
