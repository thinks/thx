//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_UTILS_HPP_INCLUDED
#define THX_VEC_UTILS_HPP_INCLUDED

#include "thx_types.hpp"
#include "thx_vec.hpp"
#include "thx_utils.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// mag2
// ----
//! Squared magnitude of a vector.

template<int64 N, typename S>
S 
mag2(const vec<N,S> &v)
{
	S m(v[0]*v[0]);
	for(int64 i(1); i < N; ++i) { 
		m += (v[i]*v[i]); 
	}
	return m; 
}

//------------------------------------------------------------------------------

// mag
// ---
//! Magnitude of a vector.

template<int64 N, typename S>	
S 
mag(const vec<N,S> &v) 
{
	assert(!is_zero(mag2(v)));
	return traits<S>::sqrt(mag2(v));
}

//------------------------------------------------------------------------------

template<int64 N, typename S> 
S
dist2(const vec<N,S> &u, const vec<N,S> &v)
{ 
   S d(sqr(u[0] - v[0]));
   for(int64 i(1); i < N; ++i) { 
	   d += sqr(u[i] - v[i]); 
   }
   return d;
}

//------------------------------------------------------------------------------

template<int64 N, typename S>	
S 
dist(const vec<N,S,T> &u, const vec<N,S,T> &v) 
{
	assert(!is_zero(dist2(u, v)));
	return T::sqrt(dist2(u, v));
}

//------------------------------------------------------------------------------

template<int64 N, typename S>
void 
normalize(vec<N,S> &v) 
{ 
	v /= mag(v); 
}

//------------------------------------------------------------------------------

template<int64 N, typename S> 
vec<N,S> 
normalized(const vec<N,S> &v) 
{ 
	return v/mag(v); 
}

//------------------------------------------------------------------------------

template<typename S>
vec<2,S>
dot(const vec<N,S> &u, const vec<N,S> &v)
{ return (u[0]*v[0] + u[1]*v[1]); }

template<typename S>
vec<3,S>
dot(const vec<N,S> &u, const vec<N,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2]); }

template<typename S>
vec<4,S>
dot(const vec<N,S> &u, const vec<N,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2] + u[3]*v[3]); }

template<int64 N, typename S>
S
dot(const vec<N,S> &u, const vec<N,S> &v)
{
	S d(u[0]*v[0]);
	for(int64 i(1); i < N; ++i) { 
		d += u[i]*v[i]; 
	}
	return d;
}

//------------------------------------------------------------------------------

template<typename S> 
S
cross(const vec<2,S> &u, const vec<2,S> &v)
{ 
	return (u[0]*v[1] - u[1]*v[0]); 
}

template<typename S> 
vec<3,S>
cross(const vec<3,S> &u, const vec<3,S> &v)
{ 
	return vec<3,S>(u[1]*v[2] - u[2]*v[1], 
					u[2]*v[0] - u[0]*v[2], 
					u[0]*v[1] - u[1]*v[0]);
}

//------------------------------------------------------------------------------

template<typename S> 
vec<2,S> 
perp(const vec<2,S> &v) 
{ return vec<2,S>(-v[1], v[0]); }

//------------------------------------------------------------------------------

template<typename S>
vec<2,S>
abs(const vec<2,S> &v)
{ 
	typedef traits<S> tr;
    return vec<2,S>(tr::abs(v[0]), tr::abs(v[1])); 
}

template<typename S>
vec<3,S>
abs(const vec<3,S> &v)
{ 
	typedef traits<S> tr;
    return vec<3,S>(tr::abs(v[0]), tr::abs(v[1]), tr::abs(v[2])); 
}

template<typename S>
vec<4,S>
abs(const vec<4,S> &v)
{ 
	typedef traits<S> tr;
    return vec<4,S>(tr::abs(v[0]), tr::abs(v[1]), tr::abs(v[2]), tr::abs(v[3])); 
}

template<int64 N, typename S>
vec<N,S>
abs(const vec<N,S> &v)
{ 
   vec<N,S> r;
   for(int64 i(0); i < N; ++i) { 
	   r[i] = traits<S>::abs(v[i]); 
   }
   return r;
}

}	// Namespace: thx.

#endif	// THX_VEC_UTILS_HPP_INCLUDED
