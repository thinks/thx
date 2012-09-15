//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_ALGO_HPP_INCLUDED
#define THX_VEC_ALGO_HPP_INCLUDED

#include "thx_types.hpp"
#include "thx_vec.hpp"
#include "thx_mat.hpp"
#include "thx_traits.hpp"
#include <type_traits>
#include <cassert>

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

//! Compute vec<N,S> inner product.
template<int64 N, typename S>
S
inner_product(const vec<N,S> &u, const vec<N,S> &v)
{
    static_assert(vec<N,S>::dim >= 2, "Vector dimension must be >= 2");

    S d = u[0]*v[0];
    for (auto i = 1; i < N; ++i) { 
        d += u[i]*v[i]; 
    }
    return d;
}


//! Compute vec<2,S> inner product.
template<typename S>
S
inner_product(const vec<2,S> &u, const vec<2,S> &v)
{ return (u[0]*v[0] + u[1]*v[1]); }


//! Compute vec<3,S> inner product.
template<typename S>
S
inner_product(const vec<3,S> &u, const vec<3,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2]); }


//! Compute vec<4,S> inner product.
template<typename S>
S
inner_product(const vec<4,S> &u, const vec<4,S> &v)
{ return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2] + u[3]*v[3]); }

//------------------------------------------------------------------------------

//! Compute vec<N,S> outer product. TODO: Verify!
template<int64 N, typename S>
mat<N,S> 
outer_product(const vec<N,S> &u, const vec<N,S> &v)
{
    mat<N,S> r;
    for (auto i = 0; i < N; ++i) {
        for (auto j = 0; j < N; ++j) {
            r(i,j) = u[i]*v[j];
        }
    }
    return r;
}


//! Compute vec<2,S> outer product.
template<typename S> 
mat<2,S> 
outer_product(const vec<2,S> &u, const vec<2,S> &v)
{
    return mat<2,S>(
        u[0]*v[0], u[0]*v[1],
        u[1]*v[0], u[1]*v[1]);
}


//! Compute vec<3,S> outer product.
template<typename S> 
mat<3,S>
outer_product(const vec<3,S> &u, const vec<3,S> &v)
{
    return mat<3,S>(
        u[0]*v[0], u[0]*v[1], u[0]*v[2],
        u[1]*v[0], u[1]*v[1], u[1]*v[2],
        u[2]*v[0], u[2]*v[1], u[2]*v[2]);
}


//! Compute vec<4,S> outer product.
template<typename S>
mat<4,S>
outer_product(const vec<4,S> &u, const vec<4,S> &v)
{
    return mat<4,S>(
        u[0]*v[0], u[0]*v[1], u[0]*v[2], u[0]*v[3],
        u[1]*v[0], u[1]*v[1], u[1]*v[2], u[1]*v[3],
        u[2]*v[0], u[2]*v[1], u[2]*v[2], u[2]*v[3],
        u[3]*v[0], u[3]*v[1], u[3]*v[2], u[3]*v[3]);
}

//------------------------------------------------------------------------------

//! Dot product, convenience wrapper for inner product.
template<int64 N, typename S>
S
dot(const vec<N,S> &u, const vec<N,S> &v)
{ 
	return inner_product(u, v); 
}

//------------------------------------------------------------------------------

//! Squared magnitude of a vector.
template<int64 N, typename S>
S 
mag_squared(const vec<N,S> &v)
{ 
	return dot(v,v); 
}

//------------------------------------------------------------------------------

//! Magnitude of a vector. No zero checking!
template<int64 N, typename S>	
S 
mag(const vec<N,S> &v) 
{ 
	return traits<S>::sqrt(mag_squared(v)); 
}

//------------------------------------------------------------------------------

//! Squared distance.
template<int64 N, typename S> 
S
dist_squared(const vec<N,S> &u, const vec<N,S> &v)
{ 
	return mag_squared(u - v); 
}

//------------------------------------------------------------------------------

//! Euclidean distance.
template<int64 N, typename S>	
S 
dist(const vec<N,S> &u, const vec<N,S> &v) 
{ 
	return mag(u - v); 
}

//------------------------------------------------------------------------------

//! Normalize input. No divide-by-zero checking!
template<int64 N, typename S>
void 
normalize(vec<N,S> &v) 
{ 
	static_assert(std::is_floating_point<S>::value, 
				 "Scalar type must be floating point");
    v *= (1/mag(v));
}

//------------------------------------------------------------------------------

//! Return normalized version of input.
template<int64 N, typename S> 
vec<N,S> 
normalized(const vec<N,S> &v) 
{ 
	static_assert(std::is_floating_point<S>::value, 
				 "Scalar type must be floating point");
    return (1/mag(v))*v;
}

//------------------------------------------------------------------------------

//! 2D cross product.
template<typename S> 
S
cross(const vec<2,S> &u, const vec<2,S> &v)
{ 
	return (u[0]*v[1] - u[1]*v[0]); 
}


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
{ 
    return vec<2,S>(-v[1], v[0]); 
}

END_THX_NAMESPACE

#endif	// THX_VEC_ALGO_HPP_INCLUDED
