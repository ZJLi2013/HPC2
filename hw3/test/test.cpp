#include "Hpc2Algorithm.h"

int main()
{
	int col(5), row(5);
	Matrix A(col, row);
	Vector x(col), b(row);
	int max_iter = 1000;
	double tol = 1e-4;

	A.RandInit();
	b[0]=1.0;
	b[4]=1.0;

	int flag = CG(A, x, b, max_iter, tol);
        x.DisplayVec();

	 return 0;
}


