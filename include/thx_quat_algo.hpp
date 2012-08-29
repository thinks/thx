//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_QUAT_ALGO_HPP_INCLUDED
#define THX_QUAT_ALGO_HPP_INCLUDED

#include "thx_quat.hpp"
#include "thx_vec.hpp"
#include "thx_traits.hpp"

//------------------------------------------------------------------------------

namespace thx {

//------------------------------------------------------------------------------

//! NB: Axis should be normalized, i.e. have unit length.
template<typename S> 
void
set_axis_angle(quat<S> &q, const vec<3,S> &axis, const S theta_rad)
{
    THX_STATIC_ASSERT(traits<S>::is_floating);
    
    const S st = traits<S>::sin(0.5*theta_rad);
    const S ct = traits<S>::cos(0.5*theta_rad);

    q[0] = ct;
    q[1] = st*axis[0];
    q[2] = st*axis[1];
    q[3] = st*axis[2];                
}

//------------------------------------------------------------------------------

//template<typename S> 
//vec<3,S,T>
//euler_angles(const quaternion<S,T>& q)
//{        
//   return vec<3,S,T>(
//	    rad2deg(T::pi() - T::atan2(
//							static_cast<S>(2)*(q[2]*q[3] - q[1]*q[0]), 
//				 T::one() - static_cast<S>(2)*(q[2]*q[2] + q[1]*q[1]))),
//		rad2deg(T::pi() - T::asin(static_cast<S>(2)*(q[3]*q[1] + q[2]*q[0]))),
//		rad2deg(T::pi() - T::atan2(
//							static_cast<S>(2)*(q[1]*q[2] - q[3]*q[0]), 
//			     T::one() - static_cast<S>(2)*(q[2]*q[2] + q[3]*q[3]))));
//}

//------------------------------------------------------------------------------

//template<typename S, class T> 
//void
//set_euler_angles(quaternion<S,T>* q, const vec<3,S,T>& deg)
//{        
//    quaternion<S,T> x, y, z;
//	set_axis_angle(&x, 
//				   vec<3,S,T>(T::one(), T::zero(), T::zero()), deg2rad(deg.x));
//    set_axis_angle(&y, 
//				   vec<3,S,T>(T::zero(), T::one(), T::zero()), deg2rad(deg.y));
//    set_axis_angle(&z, 
//		           vec<3,S,T>(T::zero(), T::zero(), T::one()), deg2rad(deg.z));
//    *q = x*y*z;
//}

//------------------------------------------------------------------------------

//template<typename S, class T> 
//bool
//nonzero(const quaternion<S,T>& q)
//{
//    return !(is_zero(q.v[0]) && 
//		     is_zero(q.v[1]) && 
//		     is_zero(q.v[2]) && 
//		     is_zero(q.v[3]));
//}

//------------------------------------------------------------------------------

//template<typename S, class T> 
//S
//mag2(const quaternion<S,T>& q)
//{
//    return mag2(q.v);
//}

//------------------------------------------------------------------------------

//template<typename S, class T> 
//S
//mag(const quaternion<S,T>& q)
//{
//    return mag(q.v);
//}

//------------------------------------------------------------------------------

//template<typename S, class T>
//void
//normalize(quaternion<S,T>* q)
//{
//	normalize(&q.v);
//    //a/=mag(a)+std::numeric_limits<T>::min();
//}

//------------------------------------------------------------------------------

//template<typename S>
//quat<S>
//normalized(const quat<S>& q)
//{
//	return quat<S,T>(normalized(q.v));
//    //return a/(mag(a)+std::numeric_limits<T>::min());
//}

//------------------------------------------------------------------------------

//template<typename T> unsigned int 
//hash(const quaternion<S,T>& a)
//{
//    return hash(hash(hash(hash(a.v[0])^a.v[1])^a.v[2])^a.v[3]);
//}

//------------------------------------------------------------------------------

// multiply (0,y)=q*(0,x)*q_conjugate
// requires that q be unit-length for this to be a rotation
//template<typename T> void
//apply_rotation(quaternion<S,T>& q, const vec<3,T>& x, vec<3,T>& y)
//{
//    // first form (A,B,C,D)=q*(0,x)
//    T A=-q.v[1]*x.v[0]-q.v[2]*x.v[1]-q.v[3]*x.v[2];
//    T B= q.v[0]*x.v[0]-q.v[3]*x.v[1]+q.v[2]*x.v[2];
//    T C= q.v[3]*x.v[0]+q.v[0]*x.v[1]-q.v[1]*x.v[2];
//    T D=-q.v[2]*x.v[0]+q.v[1]*x.v[1]+q.v[0]*x.v[2];
//    // then (0,y)=(A,B,C,D)*q_conjugate
//    y.v[0]=-A*q.v[1]+B*q.v[0]-C*q.v[3]+D*q.v[2];
//    y.v[1]=-A*q.v[2]+B*q.v[3]+C*q.v[0]-D*q.v[1];
//    y.v[2]=-A*q.v[3]-B*q.v[2]+C*q.v[1]+D*q.v[0];
//}

}   // Namespace: thx.

#endif  // THX_QUAT_ALGO_HPP_INCLUDED
