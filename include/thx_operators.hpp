//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_OPERATORS_HPP_INCLUDED
#define THX_OPERATORS_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_vec.hpp"
#include "thx_mat.hpp"
#include "thx_quat.hpp"

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

//! Unary operator: -vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator-(const vec<N,S> &v)
{
    vec<N,S> r;
    for (auto i = 0; i < N; ++i) {
        r[i] = -v[i]; 
    }
    return r;
}


//! Unary operator: -vec<2,S>
template<typename S>
vec<2,S>
operator-(const vec<2,S> &v)
{ 
    return vec<2,S>(-v[0], -v[1]); 
}


//! Unary operator: -vec<3,S>
template<typename S>
vec<3,S>
operator-(const vec<3,S> &v)
{ 
    return vec<3,S>(-v[0], -v[1], -v[2]); 
}


//! Unary operator: -vec<4,S>
template<typename S>
vec<4,S>
operator-(const vec<4,S> &v)
{ 
    return vec<4,S>(-v[0], -v[1], -v[2], -v[3]); 
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> == vec<N,S>
template<int64 N, typename S>
bool
operator==(const vec<N,S> &u, const vec<N,S> &v)
{	
   bool t = u[0] == v[0];
   int64 i = 1;
   while (i < N && t) {
      t = (t && (u[i] == v[i])); 
      ++i;
   }
   return t;
}


//! Binary operator: vec<2,S> == vec<2,S>
template<typename S>
bool
operator==(const vec<2,S> &u, const vec<2,S> &v)
{ 
    return (u[0] == v[0] && u[1] == v[1]); 
}


//! Binary operator: vec<3,S> == vec<3,S>
template<typename S>
bool
operator==(const vec<3,S> &u, const vec<3,S> &v)
{ 
    return (u[0] == v[0] && (u[1] == v[1] && u[2] == v[2])); 
}


//! Binary operator: vec<4,S> == vec<4,S>
template<typename S>
bool
operator==(const vec<4,S> &u, const vec<4,S> &v)
{ 
    return (u[0] == v[0] && (u[1] == v[1] && (u[2] == v[2] && u[3] == v[3]))); 
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> != vec<N,S>
template<int64 N, typename S>
bool
operator!=(const vec<N,S> &u, const vec<N,S> &v)
{	
   bool t = u[0] != v[0];
   int64 i = 1;
   while (i < N && !t) {
      t = (t || (u[i] != v[i])); 
      ++i;
   }
   return t;
}


//! Binary operator: vec<2,S> != vec<2,S>
template<typename S>
bool 
operator!=(const vec<2,S> &u, const vec<2,S> &v) 
{ 
    return !(u == v); 
}


//! Binary operator: vec<3,S> != vec<3,S>
template<typename S>
bool 
operator!=(const vec<3,S> &u, const vec<3,S> &v) 
{ 
    return !(u == v); 
}


//! Binary operator: vec<4,S> != vec<4,S>
template<typename S>
bool 
operator!=(const vec<4,S> &u, const vec<4,S> &v) 
{ 
    return !(u == v); 
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> + vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator+(const vec<N,S> &u, const vec<N,S> &v)
{ 
	return vec<N,S>(u) += v; 
}


//! Binary operator: vec<2,S> + vec<2,S>
template<typename S>
vec<2,S>
operator+(const vec<2,S> &u, const vec<2,S> &v)
{ 
	return vec<2,S>(u[0] + v[0], u[1] + v[1]); 
}


//! Binary operator: vec<3,S> + vec<3,S>
template<typename S>
vec<3,S>
operator+(const vec<3,S> &u, const vec<3,S> &v)
{ 
	return vec<3,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2]); 
}


//! Binary operator: vec<4,S> + vec<4,S>
template<typename S>
vec<4,S>
operator+(const vec<4,S> &u, const vec<4,S> &v)
{ 
	return vec<4,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2], u[3] + v[3]); 
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> - vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator-(const vec<N,S> &u, const vec<N,S> &v)
{ 
	return vec<N,S>(u) -= v; 
}


//! Binary operator: vec<2,S> - vec<2,S>
template<typename S>
vec<2,S>
operator-(const vec<2,S> &u, const vec<2,S> &v)
{ 
	return vec<2,S>(u[0] - v[0], u[1] - v[1]); 
}


//! Binary operator: vec<3,S> - vec<3,S>
template<typename S>
vec<3,S>
operator-(const vec<3,S> &u, const vec<3,S> &v)
{ 
	return vec<3,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2]); 
}


//! Binary operator: vec<4,S> - vec<4,S>
template<typename S>
vec<4,S>
operator-(const vec<4,S> &u, const vec<4,S> &v)
{ 
	return vec<4,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2], u[3] - v[3]); 
}

//------------------------------------------------------------------------------

//! Binary operator: scalar * vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator*(const S s, const vec<N,S> &v)
{ 
	return vec<N,S>(v) *= s; 
}


//! Binary operator: scalar * vec<2,S>
template<typename S>
vec<2,S>
operator*(const S s, const vec<2,S> &v)
{ 
	return vec<2,S>(s*v[0], s*v[1]); 
}


//! Binary operator: scalar * vec<3,S>
template<typename S>
vec<3,S>
operator*(const S s, const vec<3,S> &v)
{ 
	return vec<3,S>(s*v[0], s*v[1], s*v[2]); 
}


//! Binary operator: scalar * vec<4,S>
template<typename S>
vec<4,S>
operator*(const S s, const vec<4,S> &v)
{ 
	return vec<4,S>(s*v[0], s*v[1], s*v[2], s*v[3]); 
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> * scalar
template<int64 N, typename S>
vec<N,S>
operator*(const vec<N,S> &v, const S s)
{ return s*v; }

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> == mat<N,S>
template<int64 N, typename S>
bool
operator==(const mat<N,S> &a, const mat<N,S> &b)
{
    bool t = a[0] == b[0];
    int64 i = 1;
    while (i < N && t) {
        t = (t && (a[i] == b[i])); 
        ++i;
    }
    return t;
}


//! Binary operator: mat<2,S> == mat<2,S>
template<typename S>
bool 
operator==(const mat<2,S> &a, const mat<2,S> &b)
{
    return (a[0] == b[0] &&  
            a[1] == b[1] &&  
            a[2] == b[2] &&
            a[3] == b[3]);
}


//! Binary operator: mat<3,S> == mat<3,S>
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


//! Binary operator: mat<4,S> == mat<4,S>
template<typename S>
bool 
operator==(const mat<4,S> &a, const mat<4,S> &b)
{
    return (a[0]  == b[0]  &&  
            a[1]  == b[1]  &&  
            a[2]  == b[2]  &&
            a[3]  == b[3]  &&
            a[4]  == b[4]  &&
            a[5]  == b[5]  &&
            a[6]  == b[6]  &&
            a[7]  == b[7]  &&
            a[8]  == b[8]  &&
            a[9]  == b[9]  &&
            a[10] == b[10] &&
            a[11] == b[11] &&
            a[12] == b[12] &&
            a[13] == b[13] &&
            a[14] == b[14] &&
            a[15] == b[15]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> != mat<N,S>
template<int64 N, typename S>
bool
operator!=(const mat<N,S> &a, const mat<N,S> &b)
{
    bool t = a[0] != b[0];
    int64 i = 1;
    while (i < N && !t) {
        t = (t && (a[i] != b[i])); 
        ++i;
    }
    return t;
}


//! Binary operator: mat<2,S> != mat<2,S>
template<typename S>
bool 
operator!=(const mat<2,S> &a, const mat<2,S> &b)
{ 
	return !(a == b); 
}


//! Binary operator: mat<3,S> != mat<3,S>
template<typename S>
bool 
operator!=(const mat<3,S> &a, const mat<3,S> &b)
{ 
	return !(a == b); 
}


//! Binary operator: mat<4,S> != mat<4,S>
template<typename S>
bool 
operator!=(const mat<4,S> &a, const mat<4,S> &b)
{ 
	return !(a == b); 
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> + mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator+(const mat<N,S> &a, const mat<N,S> &b)
{ 
	return (mat<N,S>(a) += b); 
}


//! Binary operator: mat<2,S> + mat<2,S>
template<typename S> 
mat<2,S> 
operator+(const mat<2,S> &a, const mat<2,S> &b)
{
    return mat<2,S>(
        a[0] + b[0], a[2] + b[2],
        a[1] + b[1], a[3] + b[3]);
}


//! Binary operator: mat<3,S> + mat<3,S>
template<typename S>
mat<3,S> 
operator+(const mat<3,S> &a, const mat<3,S> &b)
{
    return mat<3,S>(
        a[0] + b[0], a[3] + b[3], a[6] + b[6], 
        a[1] + b[1], a[4] + b[4], a[7] + b[7], 
        a[2] + b[2], a[5] + b[5], a[8] + b[8]);
}


//! Binary operator: mat<4,S> + mat<4,S>
template<typename S>
mat<4,S> 
operator+(const mat<4,S> &a, const mat<4,S> &b)
{
    return mat<4,S>(
        a[0] + b[0], a[4] + b[4], a[8]  + b[8],  a[12] + b[12],
        a[1] + b[1], a[5] + b[5], a[9]  + b[9],  a[13] + b[13],
        a[2] + b[2], a[6] + b[6], a[10] + b[10], a[14] + b[14],
        a[3] + b[3], a[7] + b[7], a[11] + b[11], a[15] + b[15]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> - mat<N,S>
template<int64 N, typename S>
bool
operator-(const mat<N,S> &a, const mat<N,S> &b)
{ 
	return (mat<N,S>(a) -= b); 
}


//! Binary operator: mat<2,S> - mat<2,S>
template<typename S>
mat<2,S> 
operator-(const mat<2,S> &a, const mat<2,S> &b)
{
    return mat<2,S>(
        a[0] - b[0], a[2] - b[2],
        a[1] - b[1], a[3] - b[3]);
}


//! Binary operator: mat<3,S> - mat<3,S>
template<typename S>
mat<3,S> 
operator-(const mat<3,S> &a, const mat<3,S> &b)
{
    return mat<3,S>(
        a[0] - b[0], a[3] - b[3], a[6] - b[6], 
        a[1] - b[1], a[4] - b[4], a[7] - b[7], 
        a[2] - b[2], a[5] - b[5], a[8] - b[8]);
}


//! Binary operator: mat<4,S> - mat<4,S>
template<typename S>
mat<4,S> 
operator-(const mat<4,S> &a, const mat<4,S> &b)
{
    return mat<4,S>(
        a[0] - b[0], a[4] - b[4], a[8]  - b[8],  a[12] - b[12],
        a[1] - b[1], a[5] - b[5], a[9]  - b[9],  a[13] - b[13],
        a[2] - b[2], a[6] - b[6], a[10] - b[10], a[14] - b[14],
        a[3] - b[3], a[7] - b[7], a[11] - b[11], a[15] - b[15]);
}

//------------------------------------------------------------------------------

//! Binary operator: scalar * mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator*(const S s, const mat<N,S> &a)
{ 
	return (mat<N,S>(a) *= s); 
}


//! Binary operator: scalar * mat<2,S>
template<typename S>
mat<2,S> 
operator*(const S s, const mat<2,S> &a)
{
    return mat<2,S>(
        s*a[0], s*a[2], 
        s*a[1], s*a[3]);
}


//! Binary operator: scalar * mat<3,S>
template<typename S>
mat<3,S> 
operator*(const S s, const mat<3,S> &a)
{
    return mat<3,S>(
        s*a[0], s*a[3], s*a[6], 
        s*a[1], s*a[4], s*a[7], 
        s*a[2], s*a[5], s*a[8]);
}


//! Binary operator: scalar * mat<4,S>
template<typename S>
mat<4,S> 
operator*(const S s, const mat<4,S> &a)
{
    return mat<4,4,S>(
        s*a[0], s*a[4], s*a[8],  s*a[12], 
        s*a[1], s*a[5], s*a[9],  s*a[13], 
        s*a[2], s*a[6], s*a[10], s*a[14], 
        s*a[3], s*a[7], s*a[11], s*a[15]);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> * scalar
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const S b)
{ return b*a; }

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> * mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const mat<N,S> &b)
{ 
	return mat<N,S>(a) *= b; 
}


//! Binary operator: mat<2,S> * mat<2,S>
template<typename S>
mat<2,S> 
operator*(const mat<2,S> &a, const mat<2,S> &b)
{	
    return mat<2,S>(
        a(0,0)*b(0,0) + a(0,1)*b(1,0),  // v0
        a(0,0)*b(0,1) + a(0,1)*b(1,1),  // v2
        a(1,0)*b(0,0) + a(1,1)*b(1,0),  // v1
        a(1,0)*b(0,1) + a(1,1)*b(1,1)); // v4
}


//! Binary operator: mat<3,S> * mat<3,S>
template<typename S>
mat<3,S> 
operator*(const mat<3,S> &a, const mat<3,S> &b)
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


//! Binary operator: mat<4,S> * mat<4,S>
template<typename S>
mat<4,S> 
operator*(const mat<4,S> &a, const mat<4,S> &b)
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

//! Binary operator: mat<N,S> * vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator*(const mat<N,S> &a, const vec<N,S> &v)
{ 
    vec<N,S> u(0);
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            u[i] += a(i,j)*v[j];
        }
    }
    return u;    
}


//! Binary operator: mat<2,S> * vec<2,S>
template<typename S>
vec<2,S> 
operator*(const mat<2,S> &a, const vec<2,S> &v)
{	
    return vec<2,S>(
        a(0,0)*v[0] + a(0,1)*v[1], 
        a(1,0)*v[0] + a(1,1)*v[1]);
}


//! Binary operator: mat<3,S> * vec<3,S>
template<typename S>
vec<3,S> 
operator*(const mat<3,S> &a, const vec<3,S> &v)
{	
    return vec<3,S>(
        a(0,0)*v[0] + a(0,1)*v[1] + a(0,2)*v[2],
        a(1,0)*v[0] + a(1,1)*v[1] + a(1,2)*v[2],
        a(2,0)*v[0] + a(2,1)*v[1] + a(2,2)*v[2]);
}


//! Binary operator: mat<4,S> * vec<4,S>
template<typename S>
vec<4,S> 
operator*(const mat<4,S> &a, const vec<4,S> &v)
{	
    return vec<4,S>(
        a(0,0)*v[0] + a(0,1)*v[1] + a(0,2)*v[2] + a(0,3)*v[3],
        a(1,0)*v[0] + a(1,1)*v[1] + a(1,2)*v[2] + a(1,3)*v[3],
        a(2,0)*v[0] + a(2,1)*v[1] + a(2,2)*v[2] + a(2,3)*v[3],
        a(3,0)*v[0] + a(3,1)*v[1] + a(3,2)*v[2] + a(3,3)*v[3]);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> * mat<N,S>
template<int64 N, typename S>
vec<N,S>
operator*(const vec<N,S> &v, const mat<N,S> &a)
{ 
    vec<R,S> u(0);
    for (auto j = 0; j < N; ++j) {
        for (auto i = 0; i < N; ++i) {
            u[j] += v[i]*a(i,j);
        }
    }
    return u;    
}


//! Binary operator: vec<2,S> * mat<2,S>
template<typename S>
vec<2,S> 
operator*(const vec<2,S> &v, const mat<2,S> &a)
{	
    return vec<2,S>(
        v[0]*a(0,0) + v[1]*a(1,0), 
        v[0]*a(0,1) + v[1]*a(1,1));
}


//! Binary operator: vec<3,S> * mat<3,S>
template<typename S>
vec<3,S> 
operator*(const vec<3,S> &v, const mat<3,S> &a)
{	
    return vec<3,S>(
        v[0]*a(0,0) + v[1]*a(1,0) + v[2]*a(2,0),
        v[0]*a(0,1) + v[1]*a(1,1) + v[2]*a(2,1),
        v[0]*a(0,2) + v[1]*a(1,2) + v[2]*a(2,2));
}


//! Binary operator: vec<4,S> * mat<4,S>
template<typename S>
vec<4,S> 
operator*(const vec<4,S> &v, const mat<4,S> &a)
{	
    return vec<4,S>(
        v[0]*a(0,0) + v[1]*a(1,0) + v[2]*a(2,0) + v[3]*a(3,0),
        v[0]*a(0,1) + v[1]*a(1,1) + v[2]*a(2,1) + v[3]*a(3,1),
        v[0]*a(0,2) + v[1]*a(1,2) + v[2]*a(2,2) + v[3]*a(3,2),
        v[0]*a(0,3) + v[1]*a(1,3) + v[2]*a(2,3) + v[3]*a(3,3));
}

//------------------------------------------------------------------------------

// Binary operator: quat == quat
template<typename S>
bool
operator==(const quat<S>& q, const quat<S>& r)
{ 
	return (q[0] == r[0] && q[1] == r[1] && q[2] == r[2] && q[3] == r[3]); 
}

//------------------------------------------------------------------------------

// Binary operator: quat != quat
template<typename S> 
bool
operator!=(const quat<S> &q, const quat<S> &r)
{ return !(q == r); }

//------------------------------------------------------------------------------

// Binary operator: quat + quat
template<typename S> 
quat<S>
operator+(const quat<S> &q, const quat<S> &r)
{ return quat<S>(q[0] + r[0], q[1] + r[1], q[2] + r[2], q[3] + r[3]); }

//------------------------------------------------------------------------------

// Binary operator: quat - quat
template<typename S> 
quat<S>
operator-(const quat<S> &q, const quat<S> &r)
{ return quat<S>(q[0] - r[0], q[1] - r[1], q[2] - r[2], q[3] - r[3]); }

//------------------------------------------------------------------------------

// Binary operator: scalar * quat
template<typename S> 
quat<S>
operator*(const S s, const quat<S> &q)
{ return quat<S>(s*q[0], s*q[1], s*q[2], s*q[3]); }

//------------------------------------------------------------------------------

// Binary operator: quat * scalar
template<typename S> 
quat<S>
operator*(const quat<S>& q, const S s)
{ return s*q; }

//------------------------------------------------------------------------------

// Binary operator: quat * quat
template<typename S> 
quat<S>
operator*(const quat<S> &q, const quat<S> &r)
{
    return quat<S>(
        q[0]*r[0] - q[1]*r[1] - q[2]*r[2] - q[3]*r[3],
        q[0]*r[1] + q[1]*r[0] + q[2]*r[3] - q[3]*r[2],
        q[0]*r[2] + q[2]*r[0] + q[3]*r[1] - q[1]*r[3],
        q[0]*r[3] + q[3]*r[0] + q[1]*r[2] - q[2]*r[1]);
}

END_THX_NAMESPACE

#endif // THX_OPERATORS_HPP_INCLUDED