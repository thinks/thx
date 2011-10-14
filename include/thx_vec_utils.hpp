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
#include "thx_traits.hpp"
#include "thx_static_assert.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx {

//------------------------------------------------------------------------------

//! Dot product.
template<int64 N, typename S>
S
dot(const vec<N,S> &u, const vec<N,S> &v)
{
	S d(u[0]*v[0]);
	for (int64 i(1); i < N; ++i) { 
		d += u[i]*v[i]; 
	}
	return d;
}

template<typename S>
S
dot(const vec<2,S> &u, const vec<2,S> &v)
{ return (u[0]*v[0] + u[1]*v[1]); }

template<typename S>
S
dot(const vec<3,S> &u, const vec<3,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2]); }

template<typename S>
S
dot(const vec<4,S> &u, const vec<4,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2] + u[3]*v[3]); }

//------------------------------------------------------------------------------

//! Squared magnitude of a vector.
template<int64 N, typename S>
S 
mag2(const vec<N,S> &v)
{ return dot(v,v); }

//------------------------------------------------------------------------------

// mag
// ---
//! Magnitude of a vector. No zero checking!

template<int64 N, typename S>	
S 
mag(const vec<N,S> &v) 
{ return traits<S>::sqrt(mag2(v)); }

//------------------------------------------------------------------------------

template<int64 N, typename S> 
S
dist2(const vec<N,S> &u, const vec<N,S> &v)
{ return mag2(u - v); }

//------------------------------------------------------------------------------

template<int64 N, typename S>	
S 
dist(const vec<N,S> &u, const vec<N,S> &v) 
{ return mag(u - v); }

//------------------------------------------------------------------------------

template<int64 N, typename S>
void 
normalize(vec<N,S> &v) 
{ 
    THX_STATIC_ASSERT(traits<S>::is_floating, error__non_floating_point_type);
   
    const S inv_mag(1/mag(v));
    v *= inv_mag;
}

//------------------------------------------------------------------------------

template<int64 N, typename S> 
vec<N,S> 
normalized(const vec<N,S> &v) 
{ 
    THX_STATIC_ASSERT(traits<S>::is_floating, error__non_floating_point_type);

    const S inv_mag(1/mag(v));
    return inv_mag*v;
}

//------------------------------------------------------------------------------

//! 2D cross product.
template<typename S> 
S
cross(const vec<2,S> &u, const vec<2,S> &v)
{ return (u[0]*v[1] - u[1]*v[0]); }


//! 3D cross product.
template<typename S> 
vec<3,S>
cross(const vec<3,S> &u, const vec<3,S> &v)
{ 
	return vec<3,S>(u[1]*v[2] - u[2]*v[1], 
					u[2]*v[0] - u[0]*v[2], 
					u[0]*v[1] - u[1]*v[0]);
}

//------------------------------------------------------------------------------

//! Returns a perpendicular vector.
template<typename S> 
vec<2,S> 
perp(const vec<2,S> &v) 
{ return vec<2,S>(-v[1], v[0]); }

//------------------------------------------------------------------------------

}	// Namespace: thx.

#endif	// THX_VEC_UTILS_HPP_INCLUDED
