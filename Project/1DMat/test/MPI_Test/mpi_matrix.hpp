#ifndef MPI_MATRIX
#define MPI_MATRIX

#include <mpi.h>
#include <map>
#include <set>

#include "sp_lee.hpp"
#include "geom_lee.hpp" //computeRankOfMatrixRow

void mpi_matrix(SparseMatrix& A)
{
	local_int_t localNumberOfRows = A.localNumberOfRows;
	char* nonzerosInRow = A.nonzerosInRow;
	global_int_t** mtxIndG = A.mtxIndG;
	local_int_t** mtxIndL = A.mtxIndL;
	std::map<int, std::set<global_int_t> > sendList, receiveList; 
	// cpu_rank ---> GlobalRows 

	typedef std::map<int, std::set<global_int_t> >:: iterator map_iter;
	typedef std::set<global_int_t>::iterator set_iter;

//	std::map<local_int_t, local_int_t> externalToLocalMap;
	std::map<global_int_t, local_int_t> externalToLocalMap;

	for(local_int_t i=0; i<localNumberOfRows; i++)
	{
		global_int_t currentGlobalRow = A.localToGlobalMap[i];
		for(int j=0; j<nonzerosInRow[i];j++)
		{
			global_int_t curIndex = mtxIndG[i][j];
			int rankIdOfColumnEntry = ComputeRankOfMatrixRow(*(A.geom), curIndex);
			if(A.geom->rank != rankIdOfColumnEntry)
			{ //it comes from another procs
			  receiveList[rankIdOfColumnEntry].insert(curIndex);
			  sendList[rankIdOfColumnEntry].insert(currentGlobalRow);
			}
		}
	}

	//count number of matrix entries to send and receive
	local_int_t totalToBeSent = 0;
	for(map_iter curNeighbor = sendList.begin(); curNeighbor != sendList.end(); ++curNeighbor)
	{	totalToBeSent += (curNeighbor->second).size(); }

	local_int_t totalToBeReceived = 0;
	for(map_iter curNeighbor = receiveList.begin(); curNeighbor != receiveList.end(); ++curNeighbor)
	{	totalToBeReceived += (curNeighbor->second).size(); }
	
	//arrays and lists needed by ExchangeHalo function
	double* sendBuffer = new double[totalToBeSent];
	local_int_t* elementsToSend = new local_int_t[totalToBeSent];
	int* neighbors = new int[sendList.size()];
	local_int_t* receiveLength = new local_int_t[receiveList.size()];
	local_int_t* sendLength = new local_int_t[sendList.size()];

	int neighborCount = 0;
	local_int_t receiveEntryCount = 0;
	local_int_t sendEntryCount = 0;

	for(map_iter curNeighbor=receiveList.begin(); curNeighbor != receiveList.end(); curNeighbor++, neighborCount++)
	{
		int neighborId = curNeighbor->first;
		neighbors[neighborCount] = neighborId;
		receiveLength[neighborCount] = receiveList[neighborId].size();
		sendLength[neighborCount] = sendList[neighborId].size();

		for(set_iter i=receiveList[neighborId].begin(); i != receiveList[neighborId].end(); i++, receiveEntryCount++)
		{
			// *i is global_int, while defination of externalToLocalMap is lcoal to local map ??
			externalToLocalMap[*i] = localNumberOfRows + receiveEntryCount;
		}

		for(set_iter i=sendList[neighborId].begin(); i!=sendList[neighborId].end(); i++, sendEntryCount++)
		{
			elementsToSend[sendEntryCount] = A.globalToLocalMap[*i];
		}
	}

	//Convert Matrix indices to local IDs
	for(local_int_t i=0; i<localNumberOfRows; i++)
	{
		for(int j=0; j<nonzerosInRow[i]; j++)
		{
			global_int_t curIndex = mtxIndG[i][j];
			int rankOfColumnEntry = ComputeRankOfMatrixRow( *(A.geom), curIndex);
			if(A.geom->rank == rankOfColumnEntry)
			{
				mtxIndL[i][j] = A.globalToLocalMap[curIndex];
			}else
			{
				mtxIndL[i][j] = externalToLocalMap[curIndex];
			}
		}
	}

	A.numberOfExternalValues = externalToLocalMap.size();
  	A.localNumberOfColumns = A.localNumberOfRows + A.numberOfExternalValues;
  	A.numberOfSendNeighbors = sendList.size();
  	A.totalToBeSent = totalToBeSent;
  	A.elementsToSend = elementsToSend;
  	A.neighbors = neighbors;
  	A.receiveLength = receiveLength;
  	A.sendLength = sendLength;
  	A.sendBuffer = sendBuffer;
	

}

#endif
