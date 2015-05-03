#ifndef MATRIX_BUFFER
#define MATRIX_BUFFER

#include <mpi.h>
#include <cstdlib>
#include <iostream>

#include "sp_lee.hpp"
#include "vector_lee.hpp"

void buffer_matrix(const SparseMatrix& A, Vector& x)
{
  int num_neighbors = A.numberOfSendNeighbors;
 
  if(num_neighbors ==0) 
 {
//	std::cout << "num_neighbors == 0" << std::endl;
	return;
 } else {

//	std::cout << "number_neighhors = " << num_neighbors << std::endl; 
  
  local_int_t localNumberOfRows = A.localNumberOfRows;
  local_int_t * receiveLength = A.receiveLength;
  local_int_t * sendLength = A.sendLength;
  int * neighbors = A.neighbors;
  double * sendBuffer = A.sendBuffer;
  local_int_t totalToBeSent = A.totalToBeSent;
  local_int_t * elementsToSend = A.elementsToSend;

  double * const xv = x.values;

  int size, rank; // Number of MPI processes, My process ID
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int MPI_MY_TAG = 99;
  MPI_Request* request = new MPI_Request[num_neighbors];

  double* x_external = (double*) xv + localNumberOfRows;;
  /* post receive first */
  for (int i = 0; i < num_neighbors; i++) {
    local_int_t n_recv = receiveLength[i];
    MPI_Irecv(x_external, n_recv, MPI_DOUBLE, neighbors[i], MPI_MY_TAG, MPI_COMM_WORLD, request+i);
    x_external += n_recv;
  }
  
 /* fill up send buffer */
  for(local_int_t i=0 ; i<totalToBeSent; i++) sendBuffer[i] = xv[elementsToSend[i]];

  /* send to each neighbor */
  for(int i=0; i<num_neighbors; i++)
  {
	  local_int_t n_send = sendLength[i];
	  MPI_Send(sendBuffer, n_send,MPI_DOUBLE, neighbors[i], MPI_MY_TAG, MPI_COMM_WORLD);
	  sendBuffer += n_send;
  }

  MPI_Status status;
  for(int i=0; i<num_neighbors;i++)
  {
	  if(MPI_Wait(request+i, &status) )
	  {
		  std::exit(-1);
	  }
  }

  delete[] request;

  return;
  }

}

#endif
