//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_ALGO_HPP_INCLUDED
#define THX_MAT_ALGO_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_mat.hpp"
#include "thx_vec.hpp"
#include "thx_scalar_traits.hpp"
#include <cassert>

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

//------------------------------------------------------------------------------

namespace detail {

bool
equal_dispatch()
{
  return false; // TMP!!
}

} // Namespace: detail.

//! DOCS
template<int64 N, typename S>
bool
equal(const mat<N,S> &a, const mat<N,S> &b)
{
  bool t = (a[0] == b[0]);
  int64 i = 1;
  while (i < N && t) {
    t = (t && (a[i] == b[i])); 
    ++i;
  }
  return t;
}

//------------------------------------------------------------------------------

//! DOCS
template<int64 N, typename S>
bool
not_equal(const mat<N,S> &a, const mat<N,S> &b)
{
  bool t = (a[0] != b[0]);
  int64 i = 1;
  while (i < N && !t) {
    t = (t && (a[i] != b[i])); 
    ++i;
  }
  return t;
}

//------------------------------------------------------------------------------

//! DOCS
template<int64 N, typename S>
mat<N,S>
add(const mat<N,S> &a, const mat<N,S> &b)
{ 
  return (mat<N,S>(a) += b); 
}

//! DOCS
template<typename S> 
mat<2,S> 
add(const mat<2,S> &a, const mat<2,S> &b)
{
  return mat<2,S>(
    a[0] + b[0], a[2] + b[2],
    a[1] + b[1], a[3] + b[3]);
}

//! DOCS
template<typename S>
mat<3,S> 
add(const mat<3,S> &a, const mat<3,S> &b)
{
  return mat<3,S>(
    a[0] + b[0], a[3] + b[3], a[6] + b[6], 
    a[1] + b[1], a[4] + b[4], a[7] + b[7], 
    a[2] + b[2], a[5] + b[5], a[8] + b[8]);
}

//! DOCS
template<typename S>
mat<4,S> 
add(const mat<4,S> &a, const mat<4,S> &b)
{
  return mat<4,S>(
    a[0] + b[0], a[4] + b[4], a[8]  + b[8],  a[12] + b[12],
    a[1] + b[1], a[5] + b[5], a[9]  + b[9],  a[13] + b[13],
    a[2] + b[2], a[6] + b[6], a[10] + b[10], a[14] + b[14],
    a[3] + b[3], a[7] + b[7], a[11] + b[11], a[15] + b[15]);
}

//------------------------------------------------------------------------------

//! DOCS
template<int64 N, typename S>
mat<N,S>
subtract(const mat<N,S> &a, const mat<N,S> &b)
{ 
  return (mat<N,S>(a) -= b); 
}

//! DOCS
template<typename S> 
mat<2,S> 
subtract(const mat<2,S> &a, const mat<2,S> &b)
{
  return mat<2,S>(
    a[0] - b[0], a[2] - b[2],
    a[1] - b[1], a[3] - b[3]);
}

//! DOCS
template<typename S>
mat<3,S> 
subtract(const mat<3,S> &a, const mat<3,S> &b)
{
  return mat<3,S>(
    a[0] - b[0], a[3] - b[3], a[6] - b[6], 
    a[1] - b[1], a[4] - b[4], a[7] - b[7], 
    a[2] - b[2], a[5] - b[5], a[8] - b[8]);
}

//! DOCS
template<typename S>
mat<4,S> 
subtract(const mat<4,S> &a, const mat<4,S> &b)
{
  return mat<4,S>(
    a[0] - b[0], a[4] - b[4], a[8]  - b[8],  a[12] - b[12],
    a[1] - b[1], a[5] - b[5], a[9]  - b[9],  a[13] - b[13],
    a[2] - b[2], a[6] - b[6], a[10] - b[10], a[14] - b[14],
    a[3] - b[3], a[7] - b[7], a[11] - b[11], a[15] - b[15]);
}

//------------------------------------------------------------------------------

//! DOCS
template<int64 N, typename S>
mat<N,S>
mult(const S s, const mat<N,S> &a)
{ 
  return (mat<N,S>(a) *= s); 
}


//! DOCS
template<typename S>
mat<2,S> 
mult(const S s, const mat<2,S> &a)
{
  return mat<2,S>(
    s*a[0], s*a[2], 
    s*a[1], s*a[3]);
}


//! DOCS
template<typename S>
mat<3,S> 
elementwiseMult(const S s, const mat<3,S> &a)
{
  return mat<3,S>(
    s*a[0], s*a[3], s*a[6], 
    s*a[1], s*a[4], s*a[7], 
    s*a[2], s*a[5], s*a[8]);
}


//! DOCS
template<typename S>
mat<4,S> 
elementwiseMult(const S s, const mat<4,S> &a)
{
  return mat<4,4,S>(
    s*a[0], s*a[4], s*a[8],  s*a[12], 
    s*a[1], s*a[5], s*a[9],  s*a[13], 
    s*a[2], s*a[6], s*a[10], s*a[14], 
    s*a[3], s*a[7], s*a[11], s*a[15]);
}

//------------------------------------------------------------------------------

//! Matrix multiplication.
template<int64 N, typename S>
mat<N,S>
mult(const mat<N,S> &a, const mat<N,S> &b)
{ 
  return mat<N,S>(a) *= b; 
}

//! Matrix multiplication.
template<typename S>
mat<2,S> 
mult(const mat<2,S> &a, const mat<2,S> &b)
{ 
  return mat<2,S>(
      a(0,0)*b(0,0) + a(0,1)*b(1,0),  // v0
      a(0,0)*b(0,1) + a(0,1)*b(1,1),  // v2
      a(1,0)*b(0,0) + a(1,1)*b(1,0),  // v1
      a(1,0)*b(0,1) + a(1,1)*b(1,1)); // v4
}

//! Matrix multiplication.
template<typename S>
mat<3,S> 
mult(const mat<3,S> &a, const mat<3,S> &b)
{ 
  return mat<3,S>(
    a(0,0)*b(0,0) + a(0,1)*b(1,0) + a(0,2)*b(2,0),  // v0
    a(0,0)*b(0,1) + a(0,1)*b(1,1) + a(0,2)*b(2,1),  // v3
    a(0,0)*b(0,2) + a(0,1)*b(1,2) + a(0,2)*b(2,2),  // v6
    a(1,0)*b(0,0) + a(1,1)*b(1,0) + a(1,2)*b(2,0),  // v1
    a(1,0)*b(0,1) + a(1,1)*b(1,1) + a(1,2)*b(2,1),  // v4
    a(1,0)*b(0,2) + a(1,1)*b(1,2) + a(1,2)*b(2,2),  // v7
    a(2,0)*b(0,0) + a(2,1)*b(1,0) + a(2,2)*b(2,0),  // v2
    a(2,0)*b(0,1) + a(2,1)*b(1,1) + a(2,2)*b(2,1),  // v5
    a(2,0)*b(0,2) + a(2,1)*b(1,2) + a(2,2)*b(2,2)); // v8
}

//! Matrix multiplication.
template<typename S>
mat<4,S> 
mult(const mat<4,S> &a, const mat<4,S> &b)
{ 
  return mat<4,S>(
    a(0,0)*b(0,0)+a(0,1)*b(1,0)+a(0,2)*b(2,0)+a(0,3)*b(3,0),  // v0
    a(0,0)*b(0,1)+a(0,1)*b(1,1)+a(0,2)*b(2,1)+a(0,3)*b(3,1),  // v4
    a(0,0)*b(0,2)+a(0,1)*b(1,2)+a(0,2)*b(2,2)+a(0,3)*b(3,2),  // v8
    a(0,0)*b(0,3)+a(0,1)*b(1,3)+a(0,2)*b(2,3)+a(0,3)*b(3,3),  // v12
    a(1,0)*b(0,0)+a(1,1)*b(1,0)+a(1,2)*b(2,0)+a(1,3)*b(3,0),  // v1
    a(1,0)*b(0,1)+a(1,1)*b(1,1)+a(1,2)*b(2,1)+a(1,3)*b(3,1),  // v5
    a(1,0)*b(0,2)+a(1,1)*b(1,2)+a(1,2)*b(2,2)+a(1,3)*b(3,2),  // v9
    a(1,0)*b(0,3)+a(1,1)*b(1,3)+a(1,2)*b(2,3)+a(1,3)*b(3,3),  // v13
    a(2,0)*b(0,0)+a(2,1)*b(1,0)+a(2,2)*b(2,0)+a(2,3)*b(3,0),  // v2
    a(2,0)*b(0,1)+a(2,1)*b(1,1)+a(2,2)*b(2,1)+a(2,3)*b(3,1),  // v6
    a(2,0)*b(0,2)+a(2,1)*b(1,2)+a(2,2)*b(2,2)+a(2,3)*b(3,2),  // v10
    a(2,0)*b(0,3)+a(2,1)*b(1,3)+a(2,2)*b(2,3)+a(2,3)*b(3,3),  // v14
    a(3,0)*b(0,0)+a(3,1)*b(1,0)+a(3,2)*b(2,0)+a(3,3)*b(3,0),  // v3
    a(3,0)*b(0,1)+a(3,1)*b(1,1)+a(3,2)*b(2,1)+a(3,3)*b(3,1),  // v7
    a(3,0)*b(0,2)+a(3,1)*b(1,2)+a(3,2)*b(2,2)+a(3,3)*b(3,2),  // v11
    a(3,0)*b(0,3)+a(3,1)*b(1,3)+a(3,2)*b(2,3)+a(3,3)*b(3,3)); // v15
}

//------------------------------------------------------------------------------

//! NxN determinant.
template<int64 N, typename S>
S
determinant(const mat<N,S> &a);
// TODO: Implement!


//! 2x2 determinant.
template<typename S>	
S 
determinant(const mat<2,S> &a) 
{
  return (a(0,0)*a(1,1) - a(1,0)*a(0,1));
}


//! 3x3 determinant.
template<typename S>	
S 
determinant(const mat<3,S> &a) 
{
  return (a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1)) - 
          a(0,1)*(a(1,0)*a(2,2) - a(1,2)*a(2,0)) + 
          a(0,2)*(a(1,0)*a(2,1) - a(1,1)*a(2,0)));
}


//! 4-by-4 determinant.
template<typename S>	
S 
determinant(const mat<4,S> &a) 
{ 
  return (a(0,0)*a(1,1)*a(2,2)*a(3,3) + 
          a(0,1)*a(1,2)*a(2,3)*a(3,0) + 
          a(0,2)*a(1,3)*a(2,0)*a(3,1) + 
          a(0,3)*a(1,0)*a(2,1)*a(3,2) - 
          a(0,0)*a(1,3)*a(2,2)*a(3,1) -
          a(0,1)*a(1,0)*a(2,3)*a(3,2) -
          a(0,2)*a(1,1)*a(2,0)*a(3,3) -
          a(0,3)*a(1,2)*a(2,1)*a(3,0));
}

//------------------------------------------------------------------------------

//! Transpose provided NxN matrix.
template<int64 N, typename S>
void
transpose(mat<N,S> &a)
{ 
  a = transposed(a); 
}

//! Transpose provided 2x2 matrix.
template<typename S>	
void 
transpose(mat<2,S> &a) 
{ 
  a = transposed(a); 
}

//! Transpose provided 3x3 matrix.
template<typename S>	
void 
transpose(mat<3,S> &a) 
{ 
  a = transposed(a); 
}

//! Transpose provided 4x4 matrix.
template<typename S>	
void 
transpose(mat<4,S> &a) 
{ 
  a = transposed(a); 
}

//------------------------------------------------------------------------------

//! Return NxN transpose.
template<int64 N, typename S>
mat<N,S> 
transposed(const mat<N,S> &a)
{
  mat<N,S> b(a);  // Copy.
  S tmp;
  for (int64 i = 0; i < N; ++i) {
    for (int64 j = 0; j < N; ++j) {
      tmp = b(i,j);   // Swap.
      b(i,j) = b(j,i);
      b(j,i) = tmp;
    }
  }
  return b;
}

//! Return 2x2 transpose.
template<typename S> 
mat<2,S> 
transposed(const mat<2,S> &a)
{
  return mat<2,S>(a(0,0), a(1,0),
                  a(0,1), a(1,1));
}

//! Return 3x3 transpose.
template<typename S> 
mat<3,S> 
transposed(const mat<3,S> &a)
{
  return mat<3,S>(a(0,0), a(1,0), a(2,0),
                  a(0,1), a(1,1), a(2,1),
                  a(0,2), a(1,2), a(2,2));
}

//! Return 4x4 transpose.
template<typename S>
mat<4,S> 
transposed(const mat<4,S> &a)
{
  return mat<4,S>(a(0,0), a(1,0), a(2,0), a(3,0),
                  a(0,1), a(1,1), a(2,1), a(3,1),
                  a(0,2), a(1,2), a(2,2), a(3,2),
                  a(0,3), a(1,3), a(2,3), a(3,3));
}

//------------------------------------------------------------------------------

//namespace detail {
//
//  struct real_scalar_tag {};
//  struct integer_scalar_tag {};
//
//  template<int64 N, typename S>
//  gauss_jacobi_dispatch(mat<N,S> &a, mat<N,S> &b, real_scalar_tag)
//  {
//
//  }
//
//} // Namespace: detail.


template<int64 N, typename S>
void
gauss_jacobi(mat<N,S> &a, mat<N,S> &b)
{
#if 0
  //detail::gauss_jacobi_dispatch(a, b, scalar_traits<S>::scalar_category());

  //typename iterator_traits<InputIterator>::iterator_category category;
  //detail::advance_dispatch(i, n, category);  


    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point");
   
    int64 icol(0);
    int64 irow(0);
    int64 idxc[N];
    int64 idxr[N];
    int64 ipiv[N];

    for (int64 i(0); i < N; ++i) {
        ipiv[i] = 0;    
    }

    for (int64 i(0); i < N; ++i) {
        S big(0);
        for (int64 j(0); j < N; ++j) {
            if (1 != ipiv[j]) {
                for (int64 k(0); k < N; ++k) {
                    if (0 == ipiv[k] && scalar_traits<S>::abs(a(j,k)) >= big) {
                        big = scalar_traits<S>::abs(a(j,k));
                        irow = j;
                        icol = k;
                    }
                }
            }
        }

        ++ipiv[icol];
        if (irow != icol) {
            for (int64 r(0); r < N; ++r) {	
                S tmp(a(irow,r));      // Swap a.
                a(irow,r) = a(icol,r);
                a(icol,r) = tmp;

                tmp = b(irow,r);       // Swap b.
                b(irow,r) = b(icol,r);
                b(icol,r) = tmp;
            }
        }

        idxr[i] = irow;
        idxc[i] = icol;

        assert(!is_zero(scalar_traits<S>::abs(a(icol,icol))));
        const S pivinv(1/a(icol,icol));
        a(icol,icol) = 1;

        for (int64 r(0); r < N; ++r) {
            a(icol,r) *= pivinv;
            b(icol,r) *= pivinv;
        }

        for (int64 c(0); c < N; ++c) {
            if (c != icol) {
                const S tmp(a(c,icol));
                a(c,icol) = 0;

                for (int64 r(0); r < N; ++r) {
                    a(c,r) -= a(icol,r)*tmp;
                    b(c,r) -= b(icol,r)*tmp;
                }
            }
        }
    }

    for (int64 i(N - 1); i >= 0; --i) {
        if (idxr[i] != idxc[i]) {
            for (int64 c(0); c < N; ++c) {
                const S tmp(a(c,idxr[i]));
                a(c,idxr[i]) = a(c,idxc[i]);
                a(c,idxc[i]) = tmp;
            }
        }
    }
#endif
}


//------------------------------------------------------------------------------

//! Invert provided NxN matrix.
template<int64 N, typename S>
void 
invert(mat<N,S> &a)
{ 
  a = inverted(a); 
}

//------------------------------------------------------------------------------

//! Inverted.
template<int64 N, typename S>
mat<N,S> 
inverted(const mat<N,S> &a)
{
    mat<N,S> c(a);  // Copy.
    mat<N,S> b(1);  // Identity.
    gauss_jacobi(c, b); 
    return c;
}

template<typename S> 
mat<2,S> 
inverted(const mat<2,S> &a)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point");

    const S inv_det = 1/determinant(a);
    return mat<2,S>(
         inv_det*a(1,1), -inv_det*a(0,1),
        -inv_det*a(1,0),  inv_det*a(0,0));
}

template<typename S> 
mat<3,S> 
inverted(const mat<3,S> &a)
{
    static_assert(std::is_floating_point<S>::value, 
                 "Scalar type must be floating point");

    const S inv_det = 1/determinant(a);
    return mat<3,S>(
        inv_det*(a(1,1)*a(2,2) - a(1,2)*a(2,1)), 
        inv_det*(a(0,2)*a(2,1) - a(0,1)*a(2,2)), 
        inv_det*(a(0,1)*a(1,2) - a(0,2)*a(1,1)),
        inv_det*(a(1,2)*a(2,0) - a(1,0)*a(2,2)), 
        inv_det*(a(0,0)*a(2,2) - a(0,2)*a(2,0)), 
        inv_det*(a(0,2)*a(1,0) - a(0,0)*a(1,2)),
        inv_det*(a(1,0)*a(2,1) - a(1,1)*a(2,0)), 
        inv_det*(a(0,1)*a(2,0) - a(0,0)*a(2,1)), 
        inv_det*(a(0,0)*a(1,1) - a(0,1)*a(1,0)));
}

template<typename S> 
mat<4,S> 
inverted(const mat<4,S> &a)
{
    // Not yet optimized!

    // Use the norm of A to establish a sensible tolerance for singularity.

    typedef typename scalar_traits<S> traits;

    const S tol = 64*std::numeric_limits<S>::epsilon()*(
                     traits::abs(a(0,0)) + traits::abs(a(0,1)) +
                     traits::abs(a(0,1)) + traits::abs(a(0,2)) +
                     traits::abs(a(1,0)) + traits::abs(a(1,1)) +
                     traits::abs(a(1,1)) + traits::abs(a(1,2)) +
                     traits::abs(a(2,0)) + traits::abs(a(2,1)) +
                     traits::abs(a(2,1)) + traits::abs(a(2,2)) +
                     traits::abs(a(3,0)) + traits::abs(a(3,1)) +
                     traits::abs(a(3,1)) + traits::abs(a(3,2)));

    // Orthonormalize the rows of A using Modified Gram-Schmidt, saving the
    // coefficients in L.

    S Q[4][4] = {{0}};
    S L[4][4] = {{0}};
    
    // Row 0.

    S m = traits::sqrt(sqr(a(0,0)) + sqr(a(0,1)) + sqr(a(0,2)) + sqr(a(0,3)));
    if (m > tol) {
        // Store normalized row in Q, reciprocal of magnitude in diagonal of L.

        const S r(1/m);
        L[0][0] = r;
        Q[0][0] = r*a(0,0); 
        Q[0][1] = r*a(0,1);
        Q[0][2] = r*a(0,2); 
        Q[0][3] = r*a(0,3);
    }

    // Row 1.

    S d = Q[0][0]*a(1,0) + Q[0][1]*a(1,1) + Q[0][2]*a(1,2) + Q[0][3]*a(1,3);
    L[1][0] = d;
    S row[4];
    row[0] = a(1,0) - d*Q[0][0]; 
    row[1] = a(1,1) - d*Q[0][1];
    row[2] = a(1,2) - d*Q[0][2]; 
    row[3] = a(1,3) - d*Q[0][3];

    m = traits::sqrt(sqr(row[0]) + sqr(row[1]) + sqr(row[2]) + sqr(row[3]));
    if (m > tol) {
        // Store normalized row in Q, reciprocal of magnitude in diagonal of L.

        const S r(1/m);
        L[1][1] = r;
        Q[1][0] = r*row[0]; 
        Q[1][1] = r*row[1]; 
        Q[1][2] = r*row[2]; 
        Q[1][3] = r*row[3];
    }

    // Row 2.

    d = Q[0][0]*a(2,0) + Q[0][1]*a(2,1) + Q[0][2]*a(2,2) + Q[0][3]*a(2,3);
    L[2][0] = d;
    row[0] = a(2,0) - d*Q[0][0]; 
    row[1] = a(2,1) - d*Q[0][1];
    row[2] = a(2,2) - d*Q[0][2]; 
    row[3] = a(2,3) - d*Q[0][3];

    d = Q[1][0]*row[0] + Q[1][1]*row[1] + Q[1][2]*row[2] + Q[1][3]*row[3];
    L[2][1] = d;
    row[0] -= d*Q[1][0]; 
    row[1] -= d*Q[1][1]; 
    row[2] -= d*Q[1][2]; 
    row[3] -= d*Q[1][3];
    
    m = traits::sqrt(sqr(row[0]) + sqr(row[1]) + sqr(row[2]) + sqr(row[3]));
    if (m > tol) {
        // Store normalized row in Q, reciprocal of magnitude in diagonal of L.

        const S r(1/m);
        L[2][2] = r;
        Q[2][0] = r*row[0]; 
        Q[2][1] = r*row[1]; 
        Q[2][2] = r*row[2]; 
        Q[2][3] = r*row[3];
    }

    // Row 3.

    d = Q[0][0]*a(3,0) + Q[0][1]*a(3,1) + Q[0][2]*a(3,2) + Q[0][3]*a(3,3);
    L[3][0] = d;
    row[0] = a(3,0) - d*Q[0][0]; 
    row[1] = a(3,1) - d*Q[0][1];
    row[2] = a(3,2) - d*Q[0][2]; 
    row[3] = a(3,3) - d*Q[0][3];

    d = Q[1][0]*row[0] + Q[1][1]*row[1] + Q[1][2]*row[2] + Q[1][3]*row[3];
    L[3][1] = d;
    row[0] -= d*Q[1][0]; 
    row[1] -= d*Q[1][1]; 
    row[2] -= d*Q[1][2]; 
    row[3] -= d*Q[1][3];

    d = Q[2][0]*row[0] + Q[2][1]*row[1] + Q[2][2]*row[2] + Q[2][3]*row[3];
    L[3][2] = d;
    row[0] -= d*Q[2][0]; 
    row[1] -= d*Q[2][1]; 
    row[2] -= d*Q[2][2]; 
    row[3] -= d*Q[2][3];

    m = traits::sqrt(sqr(row[0]) + sqr(row[1]) + sqr(row[2]) + sqr(row[3]));
    if (m > tol) {
        // Store normalized row in Q, reciprocal of magnitude in diagonal of L.

        const S r(1/m);
        L[3][3] = r;
        Q[3][0] = r*row[0]; 
        Q[3][1] = r*row[1]; 
        Q[3][2] = r*row[2]; 
        Q[3][3] = r*row[3];
    }

    // Invert L in place (the diagonal is already correct)

    L[1][0] = -L[1][0]*L[0][0]*L[1][1];
    L[3][2] = -L[3][2]*L[2][2]*L[3][3];
    const S w(L[2][0]*L[0][0] + L[2][1]*L[1][0]);
    const S x(L[2][1]*L[1][1]);
    const S y(L[3][0]*L[0][0] + L[3][1]*L[1][0]);
    const S z(L[3][1]*L[1][1]);
    L[2][0] = -L[2][2]*w;
    L[2][1] = -L[2][2]*x;
    L[3][0] = -L[3][2]*w - L[3][3]*y;
    L[3][1] = -L[3][2]*x - L[3][3]*z;

    // Multiply B = Q^T*inv(L).
    mat<4,S> b;

    b(0,0) = Q[0][0]*L[0][0]+Q[1][0]*L[1][0]+Q[2][0]*L[2][0]+Q[3][0]*L[3][0];
    b(0,1) = Q[0][0]*L[0][1]+Q[1][0]*L[1][1]+Q[2][0]*L[2][1]+Q[3][0]*L[3][1];
    b(0,2) = Q[0][0]*L[0][2]+Q[1][0]*L[1][2]+Q[2][0]*L[2][2]+Q[3][0]*L[3][2];
    b(0,3) = Q[0][0]*L[0][3]+Q[1][0]*L[1][3]+Q[2][0]*L[2][3]+Q[3][0]*L[3][3];
    b(1,0) = Q[0][1]*L[0][0]+Q[1][1]*L[1][0]+Q[2][1]*L[2][0]+Q[3][1]*L[3][0];
    b(1,1) = Q[0][1]*L[0][1]+Q[1][1]*L[1][1]+Q[2][1]*L[2][1]+Q[3][1]*L[3][1];
    b(1,2) = Q[0][1]*L[0][2]+Q[1][1]*L[1][2]+Q[2][1]*L[2][2]+Q[3][1]*L[3][2];
    b(1,3) = Q[0][1]*L[0][3]+Q[1][1]*L[1][3]+Q[2][1]*L[2][3]+Q[3][1]*L[3][3];
    b(2,0) = Q[0][2]*L[0][0]+Q[1][2]*L[1][0]+Q[2][2]*L[2][0]+Q[3][2]*L[3][0];
    b(2,1) = Q[0][2]*L[0][1]+Q[1][2]*L[1][1]+Q[2][2]*L[2][1]+Q[3][2]*L[3][1];
    b(2,2) = Q[0][2]*L[0][2]+Q[1][2]*L[1][2]+Q[2][2]*L[2][2]+Q[3][2]*L[3][2];
    b(2,3) = Q[0][2]*L[0][3]+Q[1][2]*L[1][3]+Q[2][2]*L[2][3]+Q[3][2]*L[3][3];
    b(3,0) = Q[0][3]*L[0][0]+Q[1][3]*L[1][0]+Q[2][3]*L[2][0]+Q[3][3]*L[3][0];
    b(3,1) = Q[0][3]*L[0][1]+Q[1][3]*L[1][1]+Q[2][3]*L[2][1]+Q[3][3]*L[3][1];
    b(3,2) = Q[0][3]*L[0][2]+Q[1][3]*L[1][2]+Q[2][3]*L[2][2]+Q[3][3]*L[3][2];
    b(3,3) = Q[0][3]*L[0][3]+Q[1][3]*L[1][3]+Q[2][3]*L[2][3]+Q[3][3]*L[3][3];

    return b;
}

END_THX_NAMESPACE

#endif	// THX_MAT_ALGO_HPP_INCLUDED
