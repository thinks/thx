//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_ALGO_HPP_INCLUDED
#define THX_VEC_ALGO_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_types.hpp"
#include "thx_vec.hpp"
#include "thx_vec_traits.hpp"
#include "thx_mat.hpp"
#include "thx_scalar_traits.hpp"
#include "thx_scalar_algo.hpp"
#include <type_traits>
#include <cassert>

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

//! vec<N,S> less comparison.
template<int64 N, typename S>
bool
less(const vec<N,S> &u, const vec<N,S> &v) {
  for (auto i = vec<N,S>::linear_size; i > 0; --i) {
    if (u[i - 1] < v[i - 1]) {
      return true;
    }    
    else if (u[i - 1] > v[i - 1]) {
      return false;
    }
  }
  return false;
}

//! vec<2,S> less comparison.
template<typename S>
bool
less(const vec<2,S> &u, const vec<2,S> &v) {

}

//! vec<3,S> less comparison.
template<typename S>
bool
less(const vec<3,S> &u, const vec<3,S> &v) {
}

//! vec<4,S> less comparison.
template<typename S>
bool
less(const vec<4,S> &u, const vec<4,S> &v) {
}

//------------------------------------------------------------------------------

//! vec<N,S> less comparison.
template<int64 N, typename S>
bool
greater(const vec<N,S> &u, const vec<N,S> &v) {
  for (auto i = vec<N,S>::linear_size; i > 0; --i) {
    if (u[i - 1] < v[i - 1]) {
      return true;
    }    
    else if (u[i - 1] > v[i - 1]) {
      return false;
    }
  }
  return false;
}

//! vec<2,S> less comparison.
template<typename S>
bool
greater(const vec<2,S> &u, const vec<2,S> &v) {
}

//! vec<3,S> less comparison.
template<typename S>
bool
greater(const vec<3,S> &u, const vec<3,S> &v) {
}

//! vec<4,S> less comparison.
template<typename S>
bool
greater(const vec<4,S> &u, const vec<4,S> &v) {
  return false;
}

//------------------------------------------------------------------------------

//! vec<N,S> equal comparison.
template<class V>
bool
vec_equal(V const& u, V const& v) 
{
  typedef vec_traits<V>::size_type size_type;

  bool t = equal(u[0], v[0]);
  size_type i = 1;
  while (i < vec_traits<V>::linear_size && t) {
    t = (t && equal(u[i], v[i])); 
    ++i;
  }
  return t;
}

//------------------------------------------------------------------------------

//! vec<N,S> not equal comparison.
template<class V>
bool
vec_not_equal(V const& u, V const&v) 
{
  typedef vec_traits<V>::size_type size_type;

  bool t = not_equal(u[0], v[0]);
  size_type i = 1;
  while (i < vec_traits<V>::linear_size && !t) {
    t = (t || not_equal(u[i], v[i])); 
    ++i;
  }
  return t;
}

//------------------------------------------------------------------------------

//! DOCS
template<class V> inline THX_CONST_EXPR
V
vec_negate(V const& v) {
  typedef typename vec_traits<V>::size_type size_type;

  V u;
  for (size_type i = 0; i < vec_traits<V>::linear_size; ++i) {
    u[i] = negate(v[i]); 
  }
  return r;    
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
vec<2,S>
vec_negate(vec<2,S> const& v) { 
  return vec<2,S>(negate(v[0]), negate(v[1])); 
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
vec<3,S>
vec_negate(vec<3,S> const& v) { 
  return vec<3,S>(negate(v[0]), negate(v[1]), negate(v[2])); 
}

//! DOCS
template<typename S> inline THX_CONST_EXPR
vec<4,S>
vec_negate(vec<4,S> const& v) { 
  return vec<4,S>(negate(v[0]), negate(v[1]), negate(v[2]), negate(v[3])); 
}

//------------------------------------------------------------------------------

//! DOCS
template<class V>
V
vec_abs(V const& v) {
  using scalar_traits<vec_traits<V>::value_type>::abs;
  V u;
  for (vec_traits<V>::size_type i = 0; i < vec_traits<V>::linear_size; ++i) {
    u[i] = abs(v[i]); 
  }
  return u;  
}

//! DOCS
template<typename S>
vec<2,S>
vec_abs(vec<2,S> const& v) { 
  using scalar_traits<vec_traits<vec<2,S>>::value_type>::abs;
  return vec<2,S>(abs(v[0]), abs(v[1])); 
}

//! DOCS
template<typename S>
vec<3,S>
vec_abs(vec<3,S> const& v) { 
  using scalar_traits<vec_traits<vec<3,S>>::value_type>::abs;
  return vec<3,S>(abs(v[0]), abs(v[1]), abs(v[2])); 
}

//! DOCS
template<typename S>
vec<4,S>
vec_abs(vec<4,S> const& v) { 
  using scalar_traits<vec_traits<vec<4,S>>::value_type>::abs;
  return vec<4,S>(abs(v[0]), abs(v[1]), abs(v[2]), abs(v[3])); 
}

//------------------------------------------------------------------------------

//! Docs
template<int64 N, typename S>
vec<N,S>
vec_add(vec<N,S> const& u, vec<N,S> const& v) { 
  return vec<N,S>(u) += v; 
}

//! Docs
template<typename S>
vec<2,S>
vec_add(vec<2,S> const& u, vec<2,S> const& v) { 
  return vec<2,S>(u[0] + v[0], u[1] + v[1]); 
}

//! Docs
template<typename S>
vec<3,S>
vec_add(vec<3,S> const& u, vec<3,S> const& v) { 
  return vec<3,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2]); 
}

//! Docs
template<typename S>
vec<4,S>
vec_add(vec<4,S> const& u, vec<4,S> const& v) { 
  return vec<4,S>(u[0] + v[0], u[1] + v[1], u[2] + v[2], u[3] + v[3]); 
}

//------------------------------------------------------------------------------

//! Docs
template<int64 N, typename S>
vec<N,S>
vec_subtract(vec<N,S> const& u, vec<N,S> const& v) { 
  return vec<N,S>(u) -= v; 
}

//! Docs
template<typename S>
vec<2,S>
vec_subtract(vec<2,S> const& u, vec<2,S> const& v) { 
  return vec<2,S>(u[0] - v[0], u[1] - v[1]); 
}

//! Docs
template<typename S>
vec<3,S>
vec_subtract(vec<3,S> const& u, vec<3,S> const& v) { 
  return vec<3,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2]); 
}

//! Docs
template<typename S>
vec<4,S>
vec_subtract(vec<4,S> const& u, vec<4,S> const& v) { 
  return vec<4,S>(u[0] - v[0], u[1] - v[1], u[2] - v[2], u[3] - v[3]); 
}

//------------------------------------------------------------------------------

//! DOCS
template<int64 N, typename S>
vec<N,S>
vec_scale(S const s, vec<N,S> const& v) { 
  return vec<N,S>(v) *= s; 
}

//! DOCS
template<typename S>
vec<2,S>
vec_scale(S const s, vec<2,S> const& v) { 
  return vec<2,S>(s*v[0], s*v[1]); 
}

//! DOCS
template<typename S>
vec<3,S>
vec_scale(S const s, vec<3,S> const& v) { 
  return vec<3,S>(s*v[0], s*v[1], s*v[2]); 
}

//! DOCS
template<typename S>
vec<4,S>
vec_scale(S const s, vec<4,S> const& v) { 
  return vec<4,S>(s*v[0], s*v[1], s*v[2], s*v[3]); 
}

//------------------------------------------------------------------------------

//! Compute vec<N,S> inner product.
template<class V>
typename vec_traits<V>::value_type
inner_product(V const& u, V const& v) {
  static_assert(vec_traits<V>::linear_size >= 2, 
                "Vector dimension must be >= 2");

  typedef typename vec_traits<V>::value_type value_type;
  typedef typename vec_traits<V>::size_type size_type;

  value_type d = u[0]*v[0];
  for (size_type i = 1; i < vec_traits<V>::linear_size; ++i) { 
      d += u[i]*v[i]; 
  }
  return d;
}

//! Compute vec<2,S> inner product.
template<typename S>
S
inner_product(vec<2,S> const& u, vec<2,S> const& v) { 
  return (u[0]*v[0] + u[1]*v[1]); 
}

//! Compute vec<3,S> inner product.
template<typename S>
S
inner_product(vec<3,S> const& u, vec<3,S> const& v) { 
  return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2]); 
}

//! Compute vec<4,S> inner product.
template<typename S>
S
inner_product(vec<4,S> const& u, vec<4,S> const& v) { 
  return (u[0]*v[0] + u[1]*v[1] + u[2]*v[2] + u[3]*v[3]); 
}

//------------------------------------------------------------------------------

//! Compute vec<N,S> outer product. TODO: Verify!
template<class V>
mat<vec_traits<V>::linear_size, typename vec_traits<V>::value_type> 
outer_product(V const& u, V const& v) {
  mat<typename vec_traits<V>::dim, typename vec_traits<V>::value_type> r;
  for (auto i = 0; i < typename vec_traits<V>::linear_size; ++i) {
    for (auto j = 0; j < typename vec_traits<V>::linear_size; ++j) {
      r(i,j) = u[i]*v[j];
    }
  }
  return r;
}

//! Compute vec<2,S> outer product.
template<typename S> 
mat<2,S> 
outer_product(vec<2,S> const& u, vec<2,S> const& v) {
  return mat<2,S>(
    u[0]*v[0], u[0]*v[1],
    u[1]*v[0], u[1]*v[1]);
}

//! Compute vec<3,S> outer product.
template<typename S> 
mat<3,S>
outer_product(vec<3,S> const& u, vec<3,S> const& v) {
  return mat<3,S>(
    u[0]*v[0], u[0]*v[1], u[0]*v[2],
    u[1]*v[0], u[1]*v[1], u[1]*v[2],
    u[2]*v[0], u[2]*v[1], u[2]*v[2]);
}


//! Compute vec<4,S> outer product.
template<typename S>
mat<4,S>
outer_product(vec<4,S> const& u, vec<4,S> const& v) {
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
dot(vec<N,S> const& u, vec<N,S> const& v) { 
	return inner_product(u, v); 
}

//------------------------------------------------------------------------------

//! Squared magnitude of a vector.
template<int64 N, typename S>
S 
mag_squared(vec<N,S> const& v) { 
	return dot(v,v); 
}

//------------------------------------------------------------------------------

//! Magnitude of a vector. No zero checking!
template<int64 N, typename S>	
S 
mag(vec<N,S> const& v)  { 
	return scalar_traits<S>::sqrt(mag_squared(v)); 
}

//------------------------------------------------------------------------------

//! Euclidean distance squared.
template<int64 N, typename S> 
S
dist_squared(vec<N,S> const& u, vec<N,S> const& v) { 
	return mag_squared(u - v); 
}

//------------------------------------------------------------------------------

//! Euclidean distance.
template<int64 N, typename S>	
S 
dist(vec<N,S> const& u, vec<N,S> const& v)  { 
	return mag(u - v); 
}

//------------------------------------------------------------------------------

namespace detail {

//! Normalize input. No divide-by-zero checking!
template<int64 N, typename S> inline THX_CONST_EXPR
S
normalize_dispatch(vec<N,S> &v, real_scalar_tag) {
  v *= (1/mag(v));
}

} // Namespace: detail.

//! Normalize input. No divide-by-zero checking!
template<int64 N, typename S>
void 
normalize(vec<N,S> &v) { 
  typedef typename scalar_traits<S>::scalar_category category;
  detail::normalize_dispatch(v, category());
}

//------------------------------------------------------------------------------

// TODO dispatch!

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
cross(vec<2,S> const& u, vec<2,S> const& v) { 
	return (u[0]*v[1] - u[1]*v[0]); 
}

//! 3D cross product.
template<typename S> 
vec<3,S>
cross(vec<3,S> const& u, vec<3,S> const& v) { 
  return vec<3,S>(u[1]*v[2] - u[2]*v[1], 
                  u[2]*v[0] - u[0]*v[2], 
                  u[0]*v[1] - u[1]*v[0]);
}

//------------------------------------------------------------------------------

//! Returns a perpendicular vector.
template<typename S> 
vec<2,S> 
perp(vec<2,S> const& v) { 
  return vec<2,S>(-v[1], v[0]); 
}

END_THX_NAMESPACE

#endif	// THX_VEC_ALGO_HPP_INCLUDED
