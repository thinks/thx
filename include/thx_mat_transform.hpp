//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_TRANSFORM_HPP_INCLUDED
#define THX_MAT_TRANSFORM_HPP_INCLUDED

#include "thx_mat.hpp"
#include "thx_vec.hpp"
#include "thx_traits.hpp"

//------------------------------------------------------------------------------

namespace thx {

//------------------------------------------------------------------------------

//! Returns a translation matrix.
template<typename S>
mat<4,S>
translate(const vec<3,S> &v)
{
    return mat<4,S>(
        1, 0, 0, v[0],
        0, 1, 0, v[1],
        0, 0, 1, v[2],
        0, 0, 0, 1);
}

//------------------------------------------------------------------------------

// TODO: Rotate xyz, yzx, etc.

//------------------------------------------------------------------------------

//! Rotate in xy-plane.
template<typename S>
mat<2,S>
rotate(const S theta)
{
    const S ct(traits<S>::cos(theta));
    const S st(traits<S>::sin(theta));
    return mat<2,S>(
        ct, -st,
        st,  ct);
}

//------------------------------------------------------------------------------

//! Rotate around x-axis.
template<typename S>
mat<4,S>
rotate_x(const S theta)
{
    const S ct(traits<S>::cos(theta));
    const S st(traits<S>::sin(theta));
    return mat<4,S>(
        1,  0,   0, 0,
        0, ct, -st, 0,
        0, st,  ct, 0,
        0,  0,   0, 1);
}

//------------------------------------------------------------------------------

//! Rotate around y-axis.
template<typename S>
mat<4,S>
rotate_y(const S theta)
{
    const S ct(traits<S>::cos(theta));
    const S st(traits<S>::sin(theta));
    return mat<4,S>(
         ct, 0, st, 0,
          0, 1,  0, 0,
        -st, 0, ct, 0,
          0, 0,  0, 1);
}

//------------------------------------------------------------------------------

//! Rotate around z-axis.
template<typename S>
mat<4,S>
rotate_z(const S theta)
{
    const S ct(traits<S>::cos(theta));
    const S st(traits<S>::sin(theta));
    return mat<4,S>(
        ct, -st, 0, 0,
        st,  ct, 0, 0,
        0,    0, 1, 0,
        0,    0, 0, 1);
}

//------------------------------------------------------------------------------

//! Returns a scale matrix.
template<typename S>
mat<4,S>
scale(const vec<3,S> &v)
{
    return mat<4,S>(
        v[0],    0,    0, 0,
           0, v[1],    0, 0,
           0,    0, v[2], 0,
           0,    0,    0, 1);
}

}   // Namespace: thx.

#endif  // THX_MAT_TRANSFORM_HPP_INCLUDED




/*
    explicit
    mat(const quaternion<S,T>& q)
    {
        m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
        m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
        m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
        
        m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
        m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
        m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
        
        m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
        m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
        m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
    }

        explicit
    mat(const quaternion<S,T>& q)
    {
        m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
        m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
        m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
        m[0][3] = T::zero();
        
        m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
        m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
        m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
        m[1][3] = T::zero();
        
        m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
        m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
        m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
        m[2][3] = T::zero();
        
        m[3][0] = T::zero();
        m[3][1] = T::zero();
        m[3][2] = T::zero();
        m[3][3] = T::one();
    }
*/
