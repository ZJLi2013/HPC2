#include "Matrix.h"

int main()
{
	Matrix Mat(5,5);
	Vector Vec(5);
	
	for(int i=0; i<Vec.GetSize();i++)
	{
		Vec[i] = i;
	}
	
	Mat.RandInit();
	Mat.DisplayMat();

	Vec = Mat * Vec;

	Vec.DisplayVec();
	
	return 0;
}
