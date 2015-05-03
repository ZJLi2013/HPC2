#include <iostream>
#include <stdio.h>

int main()
{

	int ipy = 0;

	int nx=10; int ny=5;

  	int localNumberOfRows = nx * ny;
        int numberOfNonzerosPerRow = 9 ;
	
	int* nonzerosInRow = new int[localNumberOfRows];
	int** mtxIndG = new int*[localNumberOfRows];
	double** matrixValues = new double*[localNumberOfRows];
	

	//inital A
	for(int i=0; i<localNumberOfRows; i++)
	{
		matrixValues[i] = 0;
		mtxIndG[i] = 0;
	}

	for(int i=0; i<localNumberOfRows; i++)
	{
		matrixValues[i] = new double[numberOfNonzerosPerRow];
		mtxIndG[i] = new int[numberOfNonzerosPerRow];
	}

	int localNumberOfNonzeros = 0;
	/* fill value into sparse matrix */
	for(int iy=0; iy<ny; iy++)
	{
		for(int ix=0; ix<nx; ix++)
		{
			int currentLocalRow = iy * nx + ix;

			char NumberOfNonzerosInRow = 0;
			double* currentValuePointer = matrixValues[currentLocalRow];
			int* currentIndexP = mtxIndG[currentLocalRow];

			for(int sy=-1; sy<=1; sy++){
				if(iy+sy>-1 && iy+sy<ny){
					for(int sx=-1; sx<=1;sx++){
						if(ix+sx>-1 && ix+sx<nx){
							int curcol = currentLocalRow + sy*nx + sx;
							if(curcol == currentLocalRow)
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

	FILE* fm = 0;	
	fm = fopen("matrix.dat", "w");
	for( int i=0; i<localNumberOfRows; i++)
	{
		const double* const currentRowValues = matrixValues[i];
		const int* const currentRowIndices = mtxIndG[i];
		const int currentNumberOfNonzeros = nonzerosInRow[i];

		for(int j=0; j<currentNumberOfNonzeros; j++)
			fprintf(fm, "%d %d %22.16e\n", i+1, currentRowIndices[j]+1, currentRowValues[j]);
	}

	fclose(fm);
	
	return 0 ; 
}


