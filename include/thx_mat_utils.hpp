//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_UTILS_HPP_INCLUDED
#define THX_MAT_UTILS_HPP_INCLUDED

#include "thx_mat.hpp"
#include "thx_vec.hpp"
#include "thx_utils.hpp"
#include "thx_static_assert.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx {

//------------------------------------------------------------------------------

//! Determinant. TODO
template<int64 N, typename S>
S
determinant(const mat<N,S> &a);

template<typename S>	
S 
determinant(const mat<2,S> &a) 
{
    return (a(0,0)*a(1,1) - a(1,0)*a(0,1));
}

template<typename S>	
S 
determinant(const mat<3,S> &a) 
{
    return (a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1)) - 
            a(0,1)*(a(1,0)*a(2,2) - a(1,2)*a(2,0)) + 
            a(0,2)*(a(1,0)*a(2,1) - a(1,1)*a(2,0)));
}

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

//! Transpose.
template<int64 N, typename S>
void
transpose(mat<N,S> &a)
{ a = transposed(a); }

template<typename S>	
void 
transpose(mat<2,S> &a) 
{ a = transposed(a); }

template<typename S>	
void 
transpose(mat<3,S> &a) 
{ a = transposed(a); }

template<typename S>	
void 
transpose(mat<4,S> &a) 
{ a = transposed(a); }

//------------------------------------------------------------------------------

//! Transposed.
template<int64 N, typename S>
mat<N,S> 
transposed(const mat<N,S> &a)
{
    mat<N,S> b(a);  // Copy.
    for (int64 i(0); i < N; ++i) {
        for (int64 j(0); j < N; ++j) {
            const S tmp(b(i,j));   // Swap.
            b(i,j) = b(j,i);
            b(j,i) = tmp;
        }
    }
    return b;
}

template<typename S> 
mat<2,S> 
transposed(const mat<2,S> &a)
{
    return mat<2,S>(a(0,0), a(1,0),
                    a(0,1), a(1,1));
}

template<typename S> 
mat<3,S> 
transposed(const mat<3,S> &a)
{
    return mat<3,S>(a(0,0), a(1,0), a(2,0),
                    a(0,1), a(1,1), a(2,1),
                    a(0,2), a(1,2), a(2,2));
}

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

template<int64 N, typename S>
void
gauss_jacobi(mat<N,S> &a, mat<N,S> &b)
{
    /*
    THX_STATIC_ASSERT(traits<S>::is_floating, error__non_floating_point_type);
   
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
                    if (0 == ipiv[k] && traits<S>::abs(a[j][k]) >= big) {
                        big = traits<S>::abs(a[j][k]);
                        irow = j;
                        icol = k;
                    }
                }
            }
        }

        ++ipiv[icol];
        if (irow != icol) {
            for (int64 r(0); r < N; ++r) {	
                S tmp(a[irow][r]);      // Swap a.
                a[irow][r] = a[icol][r];
                a[icol][r] = tmp;

                tmp = b[irow][r];       // Swap b.
                b[irow][r] = b[icol][r];
                b[icol][r] = tmp;
            }
        }

        idxr[i] = irow;
        idxc[i] = icol;

        assert(!is_zero(traits<S>::abs(a[icol][icol])));
        const S pivinv(1/a[icol][icol]);
        a[icol][icol] = 1;

        for (int64 r(0); r < N; ++r) {
            a[icol][r] *= pivinv;
            b[icol][r] *= pivinv;
        }

        for (int64 c(0); c < N; ++c) {
            if (c != icol) {
                const S tmp(a[c][icol]);
                a[c][icol] = 0;

                for (int64 r(0); r < N; ++r) {
                    a[c][r] -= a[icol][r]*tmp;
                    b[c][r] -= b[icol][r]*tmp;
                }
            }
        }
    }

    for (int64 i(N - 1); i >= 0; --i) {
        if (idxr[i] != idxc[i]) {
            for (int64 c(0); c < N; ++c) {
                const S tmp(a[c][idxr[i]]);
                a[c][idxr[i]] = a[c][idxc[i]];
                a[c][idxc[i]] = tmp;
            }
        }
    }
    */
}

//------------------------------------------------------------------------------

//! Invert.
template<int64 N, typename S>
void 
invert(mat<N,S> &a)
{ a = inverted(a); }

template<typename S> 
void 
invert(mat<2,S> &a)
{ a = inverted(a); }

template<typename S> 
void
invert(mat<3,S> &a)
{ a = inverted(a); }

template<typename S>
void 
invert(mat<4,S> &a);	

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
    THX_STATIC_ASSERT(traits<S>::is_floating, error__non_floating_point_type);
    assert(!is_zero(determinant(a)));

    const S inv_det(1/determinant(a));
    return mat<2,S>(
         inv_det*a(1,1), -inv_det*a(0,1),
        -inv_det*a(1,0),  inv_det*a(0,0));
}

template<typename S> 
mat<3,S> 
inverted(const mat<3,S> &a)
{
    THX_STATIC_ASSERT(traits<S>::is_floating, error__non_floating_point_type);
    assert(!is_zero(determinant(a)));

    const S inv_det(1/determinant(a));
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
inverted(const mat<4,S> &a);

}	// Namespace: thx.

#endif	// THX_MAT_UTILS_HPP_INCLUDED
