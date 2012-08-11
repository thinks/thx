//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_QUAT_OPERATORS_HPP_INCLUDED
#define THX_QUAT_OPERATORS_HPP_INCLUDED

#include "thx_quat.hpp"

//------------------------------------------------------------------------------

namespace thx {

//------------------------------------------------------------------------------

// Binary operator: quat == quat
template<typename S>
bool
operator==(const quat<S>& q, const quat<S>& r)
{ return (q[0] == r[0] && q[1] == r[1] && q[2] == r[2] && q[3] == r[3]); }

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

//------------------------------------------------------------------------------

}   // Namespace: thx.

#endif  // THX_QUAT_OPERATORS_HPP_INCLUDED
