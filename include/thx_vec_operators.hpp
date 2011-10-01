//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_OPERATORS_HPP_INCLUDED
#define THX_VEC_OPERATORS_HPP_INCLUDED

#include "thx_vec.hpp"

//------------------------------------------------------------------------------

namespace thx 
{

// Unary operator: -vec

template<int64 N, typename S>
vec<2,S>
operator-(const vec<2,S>& v)
{ return vec<2,S>(-v[0], -v[1]); }

template<typename S>
vec<3,S>
operator-(const vec<3,S> &v)
{ return vec<3,S>(-v[0], -v[1], -v[2]); }

template<typename S>
vec<4,S>
operator-(const vec<4,S> &v)
{ return vec<4,S>(-v[0], -v[1], -v[2], -v[3]); }

template<int64 N, typename S>
vec<N,S>
operator-(const vec<N,S> &v)
{
	vec<N,S> r;
	for (int64 i(0); i < N; ++i) {
		r[i] = -v[i]; 
	}
	return r;
}

//------------------------------------------------------------------------------

// Binary operator: vec == vec

template<typename S>
bool
operator==(const vec<2,S>& u, const vec<2,S>& v)
{ return (u[0] == v[0] && u[1] == v[1]); }

template<typename S>
bool
operator==(const vec<3,S>& u, const vec<3,S>& v)
{ return (u[0] == v[0] && u[1] == v[1] && u[2] == v[2]); }

template<typename S>
bool
operator==(const vec<4,S>& u, const vec<4,S>& v)
{ return (u[0] == v[0] && u[1] == v[1] && u[2] == v[2] && u[3] == v[3]); }

template<int64 N, typename S>
bool
operator==(const vec<N,S>& u, const vec<N,S>& v)
{	
   bool t(u[0] == v[0]);
   int64 i(1);
   while (i < N && t) {
      t = (t && (u[i] == v[i])); 
      ++i;
   }
   return t;
}

//------------------------------------------------------------------------------

// Binary operator: vec != vec

template<typename S>
bool 
operator!=(const vec<2,S>& u, const vec<2,S>& v) 
{ return !(u == v); }

template<typename S>
bool 
operator!=(const vec<3,S>& u, const vec<3,S>& v) 
{ return !(u == v); }

template<typename S>
bool 
operator!=(const vec<4,S>& u, const vec<4,S>& v) 
{ return !(u == v); }

template<int64 N, typename S>
bool
operator!=(const vec<N,S>& u, const vec<N,S>& v)
{	
   bool t(u[0] != v[0]);
   int64 i(1);
   while (i < N && !t) {
      t = (t || (u[i] != v[i])); 
      ++i;
   }
   return t;
}

//------------------------------------------------------------------------------

// Binary operator: vec + vec

template<typename S>
vec<2,S>
operator+(const vec<2,S> &u, const vec<2,S> &v)
{ return vec<2,S>(u[0] + v[0], u[1] + v[1]); }

template<typename S>
vec<3,S>
operator+(const vec<3,S> &u, const vec<3,S> &v)
{ return vec<3,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2]); }

template<typename S>
vec<4,S>
operator+(const vec<4,S> &u, const vec<4,S> &v)
{ return vec<4,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2], u[3] + v[3]); }

template<int64 N, typename S>
vec<N,S>
operator+(const vec<N,S> &u, const vec<N,S> &v)
{
	vec<N,S> s(u);
	s += v;
	return s;
}

//------------------------------------------------------------------------------

// Binary operator: vec - vec

template<typename S>
vec<2,S>
operator-(const vec<2,S> &u, const vec<2,S> &v)
{ return vec<2,S>(u[0] - v[0], u[1] - v[1]); }

template<typename S>
vec<3,S>
operator-(const vec<3,S> &u, const vec<3,S> &v)
{ return vec<3,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2]); }

template<typename S>
vec<4,S>
operator-(const vec<4,S> &u, const vec<4,S> &v)
{ return vec<4,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2], u[3] - v[3]); }

template<int64 N, typename S>
vec<N,S>
operator-(const vec<N,S> &u, const vec<N,S> &v)
{
	vec<N,S> r(u);
	r -= v;
	return r;
}

//------------------------------------------------------------------------------

// Binary operator: scalar * vec

template<typename S>
vec<2,S>
operator*(const S s, const vec<2,S> &v)
{ return vec<2,S>(s*v[0], s*v[1]); }

template<typename S>
vec<3,S>
operator*(const S s, const vec<3,S> &v)
{ return vec<3,S>(s*v[0], s*v[1], s*v[2]); }

template<typename S>
vec<4,S>
operator*(const S s, const vec<4,S> &v)
{ return vec<4,S>(s*v[0], s*v[1], s*v[2], s*v[3]); }

template<int64 N, typename S>
vec<N,S>
operator*(const S s, const vec<N,S> &v)
{
	vec<N,S> r(v);
	r *= s;
	return r;
}

//------------------------------------------------------------------------------

// Binary operator: vec * scalar

template<typename S>
vec<2,S>
operator*(const vec<2,S> &v, const S s)
{ return s*v; }

template<typename S>
vec<3,S>
operator*(const vec<3,S> &v, const S s)
{ return s*v; }

template<typename S>
vec<4,S>
operator*(const vec<4,S> &v, const S s)
{ return s*v; }

template<int64 N, typename S>
vec<N,S>
operator*(const vec<N,S>& v, const S s)
{ return s*v; }

}	// Namespace: thx.

#endif	// THX_VEC_OPERATORS_HPP_INCLUDED
