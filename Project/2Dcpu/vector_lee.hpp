#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <cstdlib>

struct Vector {

      	local_int_t localLength;  //!< length of local portion of the vector
  	double * values;          //!< array of values 

};

inline void InitializeVector(Vector & v, local_int_t localLength) {
  v.localLength = localLength;
  v.values = new double[localLength];
  return;
}

inline void ZeroVector(Vector & v) {
  local_int_t localLength = v.localLength;
  double * vv = v.values;
  for (int i=0; i<localLength; ++i) vv[i] = 0.0;
  return;
}

inline void FillRandomVector(Vector & v) {
  local_int_t localLength = v.localLength;
  double * vv = v.values;
  for (int i=0; i<localLength; ++i) vv[i] = rand() / (double)(RAND_MAX) + 1;
  return;
}

inline void CopyVector(const Vector & v, Vector & w) {
  local_int_t localLength = v.localLength;
  assert(w.localLength >= localLength);
  double * vv = v.values;
  double * wv = w.values;
  for (int i=0; i<localLength; ++i) wv[i] = vv[i];
  return;
}


inline void DeleteVector(Vector & v) {

  delete [] v.values;
  v.localLength = 0;
  return;
}

#endif
