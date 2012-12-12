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
#include "thx_vec_algo.hpp"
#include "thx_mat_algo.hpp"
#include "thx_quat_algo.hpp"
#include <iostream>

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

//! Unary operator: -vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator-(vec<N,S> const& v) {
  return vec_negate(v);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> == vec<N,S>
template<int64 N, typename S>
bool
operator==(const vec<N,S> &u, const vec<N,S> &v)
{
  return vec_equal(u, v);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> != vec<N,S>
template<int64 N, typename S>
bool
operator!=(const vec<N,S> &u, const vec<N,S> &v)
{	
  return vec_not_equal(u, v);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> + vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator+(const vec<N,S> &u, const vec<N,S> &v)
{ 
  return add(u, v);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> - vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator-(const vec<N,S> &u, const vec<N,S> &v)
{ 
  return subtract(u, v);
}

//------------------------------------------------------------------------------

//! Binary operator: scalar * vec<N,S>
template<int64 N, typename S>
vec<N,S>
operator*(const S s, const vec<N,S> &v)
{ 
	return mult(s, v);
}

//------------------------------------------------------------------------------

//! Binary operator: vec<N,S> * scalar
template<int64 N, typename S>
vec<N,S>
operator*(const vec<N,S> &v, const S s)
{ 
  return mult(s, v);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> == mat<N,S>
template<int64 N, typename S>
bool
operator==(const mat<N,S> &a, const mat<N,S> &b)
{
  return equal(a, b);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> != mat<N,S>
template<int64 N, typename S>
bool
operator!=(const mat<N,S> &a, const mat<N,S> &b)
{
  return not_equal(a, b);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> + mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator+(const mat<N,S> &a, const mat<N,S> &b)
{ 
  return add(a, b);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> - mat<N,S>
template<int64 N, typename S>
bool
operator-(const mat<N,S> &a, const mat<N,S> &b)
{ 
	return subtract(a, b); 
}

//------------------------------------------------------------------------------

//! Binary operator: scalar * mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator*(const S s, const mat<N,S> &a)
{ 
	return mult(s, a);
}

//! Binary operator: mat<N,S> * scalar
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const S s)
{ 
  return mult(s, a);
}

//------------------------------------------------------------------------------

//! Binary operator: mat<N,S> * mat<N,S>
template<int64 N, typename S>
mat<N,S>
operator*(const mat<N,S> &a, const mat<N,S> &b)
{ 
  return mult(a, b);
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

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

//! Binary operator: std::ostream << vec<N,S>
template<size_t N, typename S>
ostream&
operator<<(ostream &os, const thx::vec<N,S> &rhs)
{
  typedef typename thx::vec<N,S>::size_type size_type;
  static const size_type size = typename thx::vec<N,S>::linear_size;

  os  << "[";
  for (size_type i = 0; i < size; ++i) {
      os << rhs[i] << (i != (size - 1) ? ", " : "");
  }
  os << "]";
  return os;
}

END_STD_NAMESPACE

#endif // THX_OPERATORS_HPP_INCLUDED
