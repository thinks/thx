//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_VEC_TRAITS_HPP_INCLUDED
#define THX_VEC_TRAITS_HPP_INCLUDED

#include "thx_namespace.hpp"
#include "thx_vec.hpp"

//------------------------------------------------------------------------------

BEGIN_THX_NAMESPACE

// Not defined.
template<class V>
struct vec_traits;

// Specialization for vec.
template<std::size_t N, typename S>
struct vec_traits<typename vec<N,S>>
{
  typedef typename vec<N,S>::value_type value_type;
  typedef typename vec<N,S>::size_type size_type;
  static const size_type linear_size = typename vec<N,S>::linear_size;
  static const size_type dim = typename vec<N,S>::dim;
};

END_THX_NAMESPACE

#endif // THX_VEC_TRAITS_HPP_INCLUDED
