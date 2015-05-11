#ifndef CREATE_MATRIX
#define CREATE_MATRIX

#include "sp_lee.hpp"

void create_matrix(SparseMatrix& A)
{
  global_int_t nx = A.geom->nx;
  global_int_t ny = A.geom->ny;
  global_int_t npx = A.geom->npx;
  global_int_t npy = A.geom->npy;
  global_int_t ipx = A.geom->ipx;
  global_int_t ipy = A.geom->ipy;
  global_int_t gnx = nx*npx;
  global_int_t gny = ny*npy;  

  	local_int_t localNumberOfRows = nx * ny;
        local_int_t numberOfNonzerosPerRow = 9 ;
	global_int_t totalNumberOfRows = localNumberOfRows * A.geom->size;
	
	global_int_t* nonzerosInRow = new char[localNumberOfRows];
	global_int_t** mtxIndG = new global_int_t*[localNumberOfRows];
	local_int_t** mtxIndL = new local_int_t*[localNumberOfRows];
	double** matrixValues = new double*[localNumberOfRows];
	
	A.localToGlobalMap.resize(localNumberOfRows); //define the size of local

	//inital A
	for(local_int_t i=0; i<localNumberOfRows; i++)
	{
		matrixValues[i] = 0;
		mtxIndG[i] = 0;
		mtxIndL[i] = 0;
	}

	for(local_int_t i=0; i<localNumberOfRows; i++)
	{
		matrixValues[i] = new double[numberOfNonzerosPerRow];
		mtxIndL[i] = new local_int_t[numberOfNonzerosPerRow];
		mtxIndG[i] = new global_int_t[numberOfNonzerosPerRow];
	}

	local_int_t localNumberOfNonzeros = 0;
	/* fill value into sparse matrix */
	for(local_int_t iy=0; iy<ny; iy++)
	{
		global_int_t giy = ipy*ny + iy;
		for(local_int_t ix=0; ix<nx; ix++)
		{
			global_int_t gix = ipx*nx + ix;
			
			local_int_t currentLocalRow = iy * nx + ix;
			global_int_t currentGlobalRow = giy*gnx + gix;

			A.globalToLocalMap[currentGlobalRow] = currentLocalRow;
			A.localToGlobalMap[currentLocalRow] = currentGlobalRow;

			char NumberOfNonzerosInRow = 0;
			double* currentValuePointer = matrixValues[currentLocalRow];
			int* currentIndexP = mtxIndG[currentLocalRow];

			for(int sy=-1; sy<=1; sy++){
				if(giy+sy>-1 && giy+sy<gny){
					for(int sx=-1; sx<=1;sx++){
						if(gix+sx>-1 && gix+sx<gnx){
							int curcol = currentGlobalRow + sy*gnx + sx;
							if(curcol == currentGlobalRow)
							{
								*(currentValuePointer++) = 9.0;
							}else{
								*(currentValuePointer++) = -1.0;
							}
							NumberOfNonzerosInRow++;
							*currentIndexP++ = curcol;

						}

					}
				}
			}
			
			nonzerosInRow[currentLocalRow] = NumberOfNonzerosInRow;
			localNumberOfNonzeros += NumberOfNonzerosInRow;

		}
	}

	global_int_t totalNumberOfNonzeros = 0;
	MPI_Allreduce(&localNumberOfNonzeros, &totalNumberOfNonzeros, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	A.totalNumberOfRows = totalNumberOfRows;
	A.totalNumberOfNonzeros = totalNumberOfNonzeros;
  	A.localNumberOfRows = localNumberOfRows;
 	A.localNumberOfColumns = localNumberOfRows;
 	A.localNumberOfNonzeros = localNumberOfNonzeros;
	A.nonzerosInRow = nonzerosInRow;
	A.mtxIndG = mtxIndG;
	A.mtxIndL = mtxIndL;
 	A.matrixValues = matrixValues;

	return ; 
}

#endif
