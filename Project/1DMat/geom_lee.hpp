#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

typedef int local_int_t;
typedef int global_int_t;

struct Geometry
{
	int nx; //number of grid points in x-direction at sub-domain/global_domain
	int ny; //number of grid points in y-direction at sub-domain 
	int size; //number of MPI proces
	int rank; 
	
};

//void init_geom(int argc_p, char** argv_p, Geometry& geom)
void init_geom(Geometry& geom)
{
	int dim = 2;
	int iparams[dim];
		
	/* default dimension */ 
	for(int i=0; i<dim; i++)
		iparams[0] = 10;
		iparams[1] = 5;

	MPI_Bcast(iparams, 2, MPI_INT, 0, MPI_COMM_WORLD);

	geom.nx = iparams[0];
	geom.ny = iparams[1];

	MPI_Comm_rank(MPI_COMM_WORLD, &geom.rank);
	MPI_Comm_size(MPI_COMM_WORLD, &geom.size);

}

inline int ComputeRankOfMatrixRow(const Geometry& geom, global_int_t index)
{
	int gnx = geom.nx * geom.ny;
	global_int_t rank = index / gnx;
	return(rank);
}

#endif
