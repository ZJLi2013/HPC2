ALL:spMatrix
SRC=main.cpp 
OBJ=${SRC: .cpp = .o}
TARG = spMatrix


#INCLUDE += -I${INTEL_MPI}/include64/
#LIB_PATH += -L${INTEL_MPI}/lib64/ -lmpi

CPPFLAGS= -I/Users/zhengjia/petsc-3.4.5/externalpackages/mpich-3.0.4-106/src/mpl/include -I/Users/zhengjia/petsc-3.4.5/externalpackages/mpich-3.0.4-106/src/mpl/include -I/Users/zhengjia/petsc-3.4.5/externalpackages/mpich-3.0.4-106/src/openpa/src -I/Users/zhengjia/petsc-3.4.5/externalpackages/mpich-3.0.4-106/src/openpa/src -I/Users/zhengjia/petsc-3.4.5/externalpackages/mpich-3.0.4-106/src/mpi/romio/include


${OBJ}:${SRC}
	mpicxx -g ${CPPFLAGS} $^ $@


${TARG}:${OBJ}
	mpicxx -g ${CPPFLAGS} $^ -o $@  #${LIB_PATH}
