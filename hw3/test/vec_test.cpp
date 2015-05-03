
#include "Vector.h"

int main()
{
	Vector v1(5), v2(5);

	for(int i=0; i<v1.GetSize(); i++)
	{
		v1[i] = i;
	}

	v2 = v1;

	v2.DisplayVec();

	return 0;
}
