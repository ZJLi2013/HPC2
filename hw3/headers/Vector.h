//http://shallots.blog.163.com/blog/static/1677392272010115101018754/
//https://github.com/bodya17/Vector/blob/master/vector.cpp
//http://www.cplusplus.com/forum/general/8493/

//class Matrix;
class Vector
{
	double* v;
	int size;

	public:
	Vector();
	Vector(int n);
	~Vector();
	void DisplayVec() const;
	int GetSize() const;
	double& operator[](int i) const;
	Vector& operator=(const Vector& v1);
	Vector& operator+=(const Vector& v1);
	Vector& operator-=(const Vector& v1);
	Vector operator*(const double Coef) const;
	friend Vector operator*(const double Coef, Vector& v1);
	Vector operator+(const Vector& v1) const;
	Vector operator-(const Vector& v1) const;
	double norm() const;
	double dot_product(const Vector& v1) const;
};
	

