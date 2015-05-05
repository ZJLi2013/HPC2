ALL:spmv
SRC=main_spmv.cpp 
OBJ=${SRC: .cpp = .o}
TARG = spmv


# CCR center running enviroment
# module load intel-mpi
INCLUDE += -I${INTEL_MPI}/include64/
LIB_PATH += -L${INTEL_MPI}/lib64/ -lmpi


${OBJ}:${SRC}
	mpicxx -g ${CPPFLAGS} $^ $@


${TARG}:${OBJ}
	mpicxx -g ${CPPFLAGS} $^ -o $@  ${LIB_PATH}
