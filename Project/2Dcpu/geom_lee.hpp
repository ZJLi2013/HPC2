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
	int npx; //nubmer of procs in x-direction
	int npy;
	int ipx; //current rank's of x in the npx by npy procs matrix
	int ipy;
};

//void init_geom(int argc_p, char** argv_p, Geometry& geom)
void init_geom(Geometry& geom)
{
	int iparams[4];
		
	/* default dimension */ 
		iparams[0] = 10;
		iparams[1] = 5;
		iparams[2] = 2; //npx
		iparams[3] = 2; //npy

	MPI_Bcast(iparams, 4, MPI_INT, 0, MPI_COMM_WORLD);

	geom.nx = iparams[0];
	geom.ny = iparams[1];
	geom.npx = iparams[2];
	geom.npy = iparams[3];

	MPI_Comm_rank(MPI_COMM_WORLD, &geom.rank);
	MPI_Comm_size(MPI_COMM_WORLD, &geom.size);

	geom.ipy = geom.rank / geom.npx;
	geom.ipx = geom.rank % geom.npx;
}

inline int ComputeRankOfMatrixRow(const Geometry& geom, global_int_t index)
{
	global_int_t  gnx = geom.nx * geom.npx;
	global_int_t  iy = index/gnx; 
	global_int_t  ipy = iy/geom.ny; 
	global_int_t  ix = index%gnx;
	global_int_t  ipx = ix/geom.nx;
	
	global_int_t rank = ipx + geom.npx*ipy;
	return(rank);
}

#endif
