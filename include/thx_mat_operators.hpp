//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_OPERATORS_HPP_INCLUDED
#define THX_MAT_OPERATORS_HPP_INCLUDED

#include "thx_mat.hpp"

//------------------------------------------------------------------------------

namespace thx 
{

//! Binary operator: mat == mat
template<int64 N, typename S>
bool
operator==(const mat<N,S> &a, const mat<N,S> &b)
{
    const S *pa(a[0]);
    const S *pb(b[0]);

    bool t(pa[0] == pb[0]);
    int64 i(1);
    while (i < N && t) {
        t = (t && (pa[i] == pb[i])); 
        ++i;
    }
    return t;
}

template<typename S>
bool 
operator==(const mat<2,S> &a, const mat<2,S> &b)
{
    return (a[0] == b[0] &&  
            a[1] == b[1] &&  
            a[2] == b[2] &&
            a[3] == b[3]);
}

template<typename S>
bool 
operator==(const mat<3,S> &a, const mat<3,S> &b)
{
    return (a[0] == b[0] &&  
            a[1] == b[1] &&  
            a[2] == b[2] &&  
            a[3] == b[3] &&
            a[4] == b[4] &&
            a[5] == b[5] &&
            a[6] == b[6] &&
            a[7] == b[7] &&
            a[8] == b[8]);
}

template<typename S>
bool 
operator==(const mat<4,S> &a, const mat<4,S> &b)
{
    return (a[0][0] == b[0][0] &&  
            a[0][1] == b[0][1] &&  
            a[0][2] == b[0][2] &&
            a[0][3] == b[0][3] &&
            a[1][0] == b[1][0] &&
            a[1][1] == b[1][1] &&
            a[1][2] == b[1][2] &&
            a[1][3] == b[1][3] &&
            a[2][0] == b[2][0] &&
            a[2][1] == b[2][1] &&
            a[2][2] == b[2][2] &&
            a[2][3] == b[2][3] &&
            a[3][0] == b[3][0] &&
            a[3][1] == b[3][1] &&
            a[3][2] == b[3][2] &&
            a[3][3] == b[3][3]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat != mat
template<int64 N, typename S>
bool
operator!=(const mat<N,S> &a, const mat<N,S> &b)
{
    const S *pa(a[0]);
    const S *pb(b[0]);

    bool t(pa[0] != pb[0]);
    int64 i(1);
    while (i < N && !t) {
        t = (t && (pa[i] != pb[i])); 
        ++i;
    }
    return t;
}

template<typename S>
bool 
operator!=(const mat<2,S> &a, const mat<2,S> &b)
{ return !(a == b); }

template<typename S>
bool 
operator!=(const mat<3,S> &a, const mat<3,S> &b)
{ return !(a == b); }

template<typename S>
bool 
operator!=(const mat<4,S> &a, const mat<4,S> &b)
{ return !(a == b); }

//------------------------------------------------------------------------------

//! Binary operator: mat + mat
template<int64 N, typename S>
bool
operator+(const mat<N,S> &a, const mat<N,S> &b)
{ return (mat<N,S>(a) += b); }

template<typename S> 
mat<2,S> 
operator+(const mat<2,S> &a, const mat<2,S> &b)
{
    return mat<2,S>(
        a[0] + b[0], a[2] + b[2],
        a[1] + b[1], a[3] + b[3]);
}

template<typename S>
mat<3,S> 
operator+(const mat<3,S> &a, const mat<3,S> &b)
{
    return mat<3,S>(
        a[0][0] + b[0][0], a[1][0] + b[1][0], a[2][0] + b[2][0], 
        a[0][1] + b[0][1], a[1][1] + b[1][1], a[2][1] + b[2][1], 
        a[0][2] + b[0][2], a[1][2] + b[1][2], a[2][2] + b[2][2]);
}

template<typename S>
mat<4,S> 
operator+(const mat<4,S> &a, const mat<4,S> &b)
{
    return mat<4,S>(
        a[0][0]+b[0][0], a[1][0]+b[1][0], a[2][0]+b[2][0], a[3][0]+b[3][0], 
        a[0][1]+b[0][1], a[1][1]+b[1][1], a[2][1]+b[2][1], a[3][1]+b[3][1], 
        a[0][2]+b[0][2], a[1][2]+b[1][2], a[2][2]+b[2][2], a[3][2]+b[3][2], 
        a[0][3]+b[0][3], a[1][3]+b[1][3], a[2][3]+b[2][3], a[3][3]+b[3][3]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat - mat
template<int64 N, typename S>
bool
operator-(const mat<N,S> &a, const mat<N,S> &b)
{ return (mat<N,S>(a) -= b); }

template<typename S>
mat<2,S> 
operator-(const mat<2,S> &a, const mat<2,S> &b)
{
    return mat<2,S>(
        a[0] - b[0], a[2] - b[2],
        a[1] - b[1], a[3] - b[3]);
}

template<typename S>
mat<3,S> 
operator-(const mat<3,S> &a, const mat<3,S> &b)
{
    return mat<3,S>(
        a[0][0] - b[0][0], a[1][0] - b[1][0], a[2][0] - b[2][0], 
        a[0][1] - b[0][1], a[1][1] - b[1][1], a[2][1] - b[2][1], 
        a[0][2] - b[0][2], a[1][2] - b[1][2], a[2][2] - b[2][2]);
}

template<typename S>
mat<4,S> 
operator-(const mat<4,S> &a, const mat<4,S> &b)
{
    return mat<4,S>(
        a[0][0]-b[0][0], a[1][0]-b[1][0], a[2][0]-b[2][0], a[3][0]-b[3][0], 
        a[0][1]-b[0][1], a[1][1]-b[1][1], a[2][1]-b[2][1], a[3][1]-b[3][1], 
        a[0][2]-b[0][2], a[1][2]-b[1][2], a[2][2]-b[2][2], a[3][2]-b[3][2], 
        a[0][3]-b[0][3], a[1][3]-b[1][3], a[2][3]-b[2][3], a[3][3]-b[3][3]);
}

//------------------------------------------------------------------------------

//! Binary operator: scalar * mat
template<int64 N, typename S>
bool
operator*(const S s, const mat<N,S> &a)
{ return (mat<N,S>(a) *= s); }

template<typename S>
mat<2,S> 
operator*(const S s, const mat<2,S> &a)
{
    return mat<2,S>(
        s*a[0], s*a[2], 
        s*a[1], s*a[3]);
}

template<typename S>
mat<3,S> 
operator*(const S s, const mat<3,S> &a)
{
    return mat<3,S>(
        s*a[0][0], s*a[1][0], s*a[2][0], 
        s*a[0][1], s*a[1][1], s*a[2][1], 
        s*a[0][2], s*a[1][2], s*a[2][2]);
}

template<typename S>
mat<4,S> 
operator*(const S s, const mat<4,S> &a)
{
    return mat<4,4,S>(
        s*a[0][0], s*a[1][0], s*a[2][0], s*a[3][0], 
        s*a[0][1], s*a[1][1], s*a[2][1], s*a[3][1], 
        s*a[0][2], s*a[1][2], s*a[2][2], s*a[3][2], 
        s*a[0][3], s*a[1][3], s*a[2][3], s*a[3][3]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat * scalar
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<2,S> 
operator*(const mat<2,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<3,S> 
operator*(const mat<3,S> &a, const S b)
{ return b*a; }

template<typename S>
mat<4,S> 
operator*(const mat<4,S> &a, const S b)
{ return b*a; }

//------------------------------------------------------------------------------

//! Binary operator: mat * mat
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const mat<N,S> &b)
{ return mat<N,S>(a) *= b; }

template<typename S>
mat<2,S> 
operator*(const mat<2,S> &a, const mat<2,S> &b)
{	
    return mat<2,S>(
        a(0,0)*b(0,0) + a(0,1)*b(1,0), a(0,0)*b(0,1) + a(0,1)*b(1,1),
        a(1,0)*b(0,0) + a(1,1)*b(1,0), a(1,0)*b(0,1) + a(1,1)*b(1,1));
}

template<typename S>
mat<3,S> 
operator*(const mat<3,S> &a, const mat<3,S> &b)
{	
    return mat<3,S>(
        a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2],
        a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2], 
        a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2],
        a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2],
        a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2], 
        a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2],
        a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2],
        a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2], 
        a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2]);
}

template<typename S>
mat<4,S> 
operator*(const mat<4,S> &a, const mat<4,S> &b)
{	
    return mat<4,S>(
        a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2] + a[3][0]*b[0][3],
        a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2] + a[3][0]*b[1][3],
        a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2] + a[3][0]*b[2][3],
        a[0][0]*b[3][0] + a[1][0]*b[3][1] + a[2][0]*b[3][2] + a[3][0]*b[3][3],
        a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2] + a[3][1]*b[0][3],
        a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2] + a[3][1]*b[1][3],
        a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2] + a[3][1]*b[2][3],
        a[0][1]*b[3][0] + a[1][1]*b[3][1] + a[2][1]*b[3][2] + a[3][1]*b[3][3],
        a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2] + a[3][2]*b[0][3],
        a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2] + a[3][2]*b[1][3],
        a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2] + a[3][2]*b[2][3],
        a[0][2]*b[3][0] + a[1][2]*b[3][1] + a[2][2]*b[3][2] + a[3][2]*b[3][3],
        a[0][3]*b[0][0] + a[1][3]*b[0][1] + a[2][3]*b[0][2] + a[3][3]*b[0][3],
        a[0][3]*b[1][0] + a[1][3]*b[1][1] + a[2][3]*b[1][2] + a[3][3]*b[1][3],
        a[0][3]*b[2][0] + a[1][3]*b[2][1] + a[2][3]*b[2][2] + a[3][3]*b[2][3],
        a[0][3]*b[3][0] + a[1][3]*b[3][1] + a[2][3]*b[3][2] + a[3][3]*b[3][3]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat * vec
template<int64 N, typename S>
vec<N,S>
operator*(const mat<N,S> &a, const vec<N,S> &v)
{ 
    vec<R,S> u;
    for (int64 r(0); r < N; ++r) {
        u[r] = 0;
        for (int64 c(0); c < N; ++c) {
            u[r] = u[r] + a[c][r]*v[c];
        }
    }
    return u;    
}

template<typename S>
vec<2,S> 
operator*(const mat<2,S> &a, const vec<2,S> &v)
{	
    return vec<2,S>(
        a(0,0)*v[0] + a(0,1)*v[1], 
        a(1,0)*v[0] + a(1,1)*v[1]);
}

template<typename S>
vec<3,S> 
operator*(const mat<3,S> &a, const vec<3,S> &v)
{	
    return vec<3,S>(
        a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2], 
        a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2],
        a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2]);
}

template<typename S>
vec<4,S> 
operator*(const mat<4,S> &a, const vec<4,S> &v)
{	
    return vec<4,S>(
        a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2] + a[3][0]*v[3], 
        a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2] + a[3][1]*v[3],
        a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2] + a[3][2]*v[3],
        a[0][3]*v[0] + a[1][3]*v[1] + a[2][3]*v[2] + a[3][3]*v[3]);
}

//------------------------------------------------------------------------------

// Binary operator: vec * mat
template<int64 N, typename S>
vec<N,S>
operator*(const vec<N,S> &v, const mat<N,S> &a)
{ 
    vec<R,S> u;
    int j(0), k(0);
    for (int64 c(0); c < N; ++c) {
        u[c] = 0;
        for (int64 r(0); r < N; ++r) {
            u[c] = u[c] + v[r]*a[c][r];
        }
    }
    return u;    
}

template<typename S>
vec<2,S> 
operator*(const vec<2,S> &v, const mat<2,S> &a)
{	
    return vec<2,S>(
        v[0]*a(0,0) + v[1]*a(1,0), 
        v[0]*a(0,1) + v[1]*a(1,1));
}

template<typename S>
vec<3,S> 
operator*(const vec<3,S> &v, const mat<3,S> &a)
{	
    return vec<3,S>(
        v[0]*a[0][0] + v[1]*a[0][1] + v[2]*a[0][2],
        v[0]*a[1][0] + v[1]*a[1][1] + v[2]*a[1][2],
        v[0]*a[2][0] + v[1]*a[2][1] + v[2]*a[2][2]);
}

template<typename S>
vec<4,S> 
operator*(const vec<4,S> &v, const mat<4,S> &a)
{	
    return vec<4,S>(
        v[0]*a[0][0] + v[1]*a[0][1] + v[2]*a[0][2] + v[3]*a[0][3],
        v[0]*a[1][0] + v[1]*a[1][1] + v[2]*a[1][2] + v[3]*a[1][3],
        v[0]*a[2][0] + v[1]*a[2][1] + v[2]*a[2][2] + v[3]*a[2][3],
        v[0]*a[3][0] + v[1]*a[3][1] + v[2]*a[3][2] + v[3]*a[3][3]);
}

}	// Namespace: thx.

#endif	// THX_MAT_OPERATORS_HPP_INCLUDED
