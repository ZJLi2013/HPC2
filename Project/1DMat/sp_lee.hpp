#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include "geom_lee.hpp"
#include "vector_lee.hpp"

#include <map>
#include <vector>

struct SparseMatrix
{
	Geometry*  geom;

	/* global variable */
	global_int_t totalNumberOfRows;
	global_int_t totalNumberOfNonzeros;

	/*local variable */
	local_int_t localNumberOfRows;
	local_int_t localNumberOfColumns;
	local_int_t localNumberOfNonzeros;
	global_int_t** mtxIndG;
	global_int_t** mtxIndL;  
	double** matrixValues;

//	char* nonzerosInRow; 
	global_int_t* nonzerosInRow;

	/* global/local map define */
	std::map<global_int_t, local_int_t> globalToLocalMap;
	std::vector<global_int_t> localToGlobalMap;


	/* MPI communication coefficients */
	local_int_t numberOfExternalValues; 
	int numberOfSendNeighbors; 
	local_int_t totalToBeSent; 
	local_int_t* elementsToSend; 
       	int* neighbors;
	local_int_t* receiveLength; 
	local_int_t* sendLength; 
	double* sendBuffer; 

};

inline void InitialSparseMatrix(SparseMatrix& A, Geometry* geom)
{
	A.geom = geom;
        A.totalNumberOfRows = 0;
	A.totalNumberOfNonzeros = 0;
	A.localNumberOfRows = 0;
	A.localNumberOfColumns = 0;
	A.localNumberOfNonzeros = 0;
	A.nonzerosInRow = 0;
	A.mtxIndG = 0;
	A.mtxIndL = 0;
	A.matrixValues = 0;
	
	/* MPI */
	A.numberOfExternalValues = 0;
	A.numberOfSendNeighbors = 0;
	A.totalToBeSent = 0;
	A.elementsToSend = 0;
	A.neighbors = 0;
	A.receiveLength = 0;
	A.sendLength = 0;
	A.sendBuffer = 0;
}	

inline void DeleteMatrix(SparseMatrix& A)
{
  for (local_int_t i = 0; i< A.localNumberOfRows; ++i) {
    delete [] A.matrixValues[i];
    delete [] A.mtxIndG[i];
    delete [] A.mtxIndL[i];
  }

  if (A.nonzerosInRow)             delete [] A.nonzerosInRow;
  if (A.mtxIndG) delete [] A.mtxIndG;
  if (A.mtxIndL) delete [] A.mtxIndL;
  if (A.matrixValues) delete [] A.matrixValues;
  if (A.elementsToSend)       delete [] A.elementsToSend;
  if (A.neighbors)              delete [] A.neighbors;
  if (A.receiveLength)            delete [] A.receiveLength;
  if (A.sendLength)            delete [] A.sendLength;
  if (A.sendBuffer)            delete [] A.sendBuffer;
}

#include "create_matrix.hpp"
#include "mpi_matrix.hpp"

#endif

