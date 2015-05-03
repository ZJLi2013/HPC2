//http://shallots.blog.163.com/blog/static/1677392272010115101018754/

#include "Vector.h"

class Matrix
{
	double* p_data;
	int row, col;
	public:
	Matrix(int r, int c);
	~Matrix();
	void RandInit();
	void DisplayMat() const ;
	Vector operator*(Vector& v) const;
};

