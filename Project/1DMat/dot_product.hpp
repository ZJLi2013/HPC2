#ifndef DOT_PRODUCT_HPP
#define DOT_PRODUCT_HPP

#include <mpi.h>
#include <cassert>

#include "vector_lee.hpp"

int DotProduct(const Vector & x, const Vector & y, double & result)
{
  assert(x.localLength == y.localLength);

  double local_result = 0.0;
  double * xv = x.values;
  double * yv = y.values;
  if (yv==xv) {
   for (local_int_t i=0; i<x.localLength; i++) local_result += xv[i]*xv[i];
  } else {
   for (local_int_t i=0; i<x.localLength; i++) local_result += xv[i]*yv[i];
  }

  // Use MPI's reduce function to collect all partial sums
  double global_result = 0.0;
  MPI_Allreduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM,
      MPI_COMM_WORLD);
  result = global_result;

  return(0);
}

#endif

