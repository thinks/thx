//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_HPP_INCLUDED
#define THX_MAT_HPP_INCLUDED

#include "thx_traits.hpp"
#include "thx_types.hpp"
#include "thx_static_assert.hpp"
//#include "thx_quaternion.hpp"
//#include "thx_utils.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// TODO: Implement!?
template<int64 C, int64 R, typename S>
class mat;

//------------------------------------------------------------------------------

// 2x2 matrix.

template<typename S>
class mat<2,2,S>
{
public:		// Types and constants.

	typedef S value_type;

	static const int64 dim  = 2;
	static const int64 rows = 2;
	static const int64 cols = 2;

	static const mat<2,2,S> identity;

public:		// CTOR/DTOR.

	//! CTOR.
	explicit
	mat(const S v = traits<S>::one())
    {
        m[0][0] = v;
        m[0][1] = traits<S>::zero();
        m[1][0] = traits<S>::zero();
        m[1][1] = v;
    }

	//! Copy CTOR.
	explicit
    mat(const mat<2,2,S> &rhs)
    {
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
    }


	explicit
	mat(const S a0, const S a2,
		const S a1, const S a3)
	{	
		// Column-major.

        m[0][0] = a0;
        m[0][1] = a1;
		m[1][0] = a2;
        m[1][1] = a3;
	}

	explicit
	mat(const S a[4])
	{	
		// Column-major.

		m[0][0] = a[0];
        m[0][1] = a[1];
		m[1][0] = a[2];
        m[1][1] = a[3];
	}

	//! DTOR.
	~mat() 
	{}

public:

	mat<2,2,S>& 
	operator=(const mat<2,2,S>& rhs)
	{
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator+=(const mat<2,2,S>& rhs)
	{
        m[0][0] += rhs[0][0];
        m[0][1] += rhs[0][1];
        m[1][0] += rhs[1][0];
        m[1][1] += rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator-=(const mat<2,2,S> &rhs)
	{
        m[0][0] -= rhs[0][0];
        m[0][1] -= rhs[0][1];
        m[1][0] -= rhs[1][0];
        m[1][1] -= rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator*=(const S rhs)
	{
        m[0][0] *= rhs;
        m[0][1] *= rhs;
        m[1][0] *= rhs;
        m[1][1] *= rhs;
		return *this;
	}

	mat<2,2,S>& 
	operator*=(const mat<2,2,S> &rhs)
	{	
		// Matrix multiplication.

		const mat<2,2,S> lhs(*this);
		m[0][0] = lhs[0][0]*rhs[0][0] + lhs[1][0]*rhs[0][1];
		m[0][1] = lhs[0][1]*rhs[0][0] + lhs[1][1]*rhs[0][1];
		m[1][0] = lhs[0][0]*rhs[1][0] + lhs[1][0]*rhs[1][1];
		m[1][1] = lhs[0][1]*rhs[1][0] + lhs[1][1]*rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			m[0][0] *= inv_fact;
			m[0][1] *= inv_fact;
			m[1][0] *= inv_fact;
			m[1][1] *= inv_fact;
		}
		else
		{
			m[0][0] /= rhs;
			m[0][1] /= rhs;
			m[1][0] /= rhs;
			m[1][1] /= rhs;
		}
		return *this;
	}

public:

	S*	
    operator[](const int64 c)
    {	
		assert(0 <= c && c < cols);
		return m[c]; 
	}

    const S*
    operator[](const int64 c) const
    {	
		assert(0 <= c && c < cols);
		return m[c]; 
	}

private:

	S _m[2][2];
};

// Static constants.
//
template<typename S> 
const mat<2,2,S> 
mat<2,2,S>::identity(traits<S>::one());

//------------------------------------------------------------------------------

// 3x3 matrix.

template<typename S>
class mat<3,3,S>
{
public:

	typedef S value_type;

	static const int64 dim  = 3;
	static const int64 rows = 3;
	static const int64 cols = 3;

	static const mat<3,3,S,T> identity;

public:

	explicit
	mat(const S v = T::one())
    {
        m[0][0] = v;
        m[0][1] = T::zero();
		m[0][2] = T::zero();
        m[1][0] = T::zero();
        m[1][1] = v;
		m[1][2] = T::zero();
		m[2][0] = T::zero();
		m[2][1] = T::zero();
		m[2][2] = v;
    }

	explicit
	mat(const S a0, const S a3, const S a6,
		const S a1, const S a4, const S a7,
		const S a2, const S a5, const S a8)
	{	// Column-major.
		//
        m[0][0] = a0;
        m[0][1] = a1;
		m[0][2] = a2;
        m[1][0] = a3;
        m[1][1] = a4;
		m[1][2] = a5;
        m[2][0] = a6;
        m[2][1] = a7;
		m[2][2] = a8;
	}

	explicit
	mat(const S a[9])
	{	// Column-major.
		//
        m[0][0] = a[0];
        m[0][1] = a[1];
		m[0][2] = a[2];
        m[1][0] = a[3];
        m[1][1] = a[4];
		m[1][2] = a[5];
        m[2][0] = a[6];
        m[2][1] = a[7];
		m[2][2] = a[8];
	}

	//explicit
	//mat(const quaternion<S,T>& q)
	//{
	//	m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
 //       m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
 //       m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
 //       
 //       m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
 //       m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
 //       m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
 //       
 //       m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
 //       m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
 //       m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
	//}

	explicit
    mat(const mat<3,3,S>& rhs)
    {
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[0][2] = rhs[0][2];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
        m[1][2] = rhs[1][2];
        m[2][0] = rhs[2][0];
        m[2][1] = rhs[2][1];
		m[2][2] = rhs[2][2];
    }

	//! DTOR.
	~mat() 
	{}

public:

	mat<3,3,S>& 
	operator=(const mat<3,3,S> &rhs)
	{
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[0][2] = rhs[0][2];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
        m[1][2] = rhs[1][2];
        m[2][0] = rhs[2][0];
        m[2][1] = rhs[2][1];
		m[2][2] = rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator+=(const mat<3,3,S> &rhs)
	{
        m[0][0] += rhs[0][0];
        m[0][1] += rhs[0][1];
        m[0][2] += rhs[0][2];
        m[1][0] += rhs[1][0];
        m[1][1] += rhs[1][1];
        m[1][2] += rhs[1][2];
        m[2][0] += rhs[2][0];
        m[2][1] += rhs[2][1];
		m[2][2] += rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator-=(const mat<3,3,S> &rhs)
	{
        m[0][0] -= rhs[0][0];
        m[0][1] -= rhs[0][1];
        m[0][2] -= rhs[0][2];
        m[1][0] -= rhs[1][0];
        m[1][1] -= rhs[1][1];
        m[1][2] -= rhs[1][2];
        m[2][0] -= rhs[2][0];
        m[2][1] -= rhs[2][1];
		m[2][2] -= rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator*=(const S rhs)
	{
        m[0][0] *= rhs;
        m[0][1] *= rhs;
        m[0][2] *= rhs;
        m[1][0] *= rhs;
        m[1][1] *= rhs;
        m[1][2] *= rhs;
        m[2][0] *= rhs;
        m[2][1] *= rhs;
		m[2][2] *= rhs;
		return *this;
	}

	mat<3,3,S>& 
	operator*=(const mat<3,3,S>& rhs)
	{	
		// Matrix multiplication.

		const mat<3,3,S> lhs(*this);
		m[0][0] = lhs[0][0]*rhs[0][0]+lhs[1][0]*rhs[0][1]+lhs[2][0]*rhs[0][2];
		m[0][1] = lhs[0][1]*rhs[0][0]+lhs[1][1]*rhs[0][1]+lhs[2][1]*rhs[0][2];
		m[0][2] = lhs[0][2]*rhs[0][0]+lhs[1][2]*rhs[0][1]+lhs[2][2]*rhs[0][2];
		m[1][0] = lhs[0][0]*rhs[1][0]+lhs[1][0]*rhs[1][1]+lhs[2][0]*rhs[1][2];
		m[1][1] = lhs[0][1]*rhs[1][0]+lhs[1][1]*rhs[1][1]+lhs[2][1]*rhs[1][2];
		m[1][2] = lhs[0][2]*rhs[1][0]+lhs[1][2]*rhs[1][1]+lhs[2][2]*rhs[1][2];
		m[2][0] = lhs[0][0]*rhs[2][0]+lhs[1][0]*rhs[2][1]+lhs[2][0]*rhs[2][2];
		m[2][1] = lhs[0][1]*rhs[2][0]+lhs[1][1]*rhs[2][1]+lhs[2][1]*rhs[2][2];
		m[2][2] = lhs[0][2]*rhs[2][0]+lhs[1][2]*rhs[2][1]+lhs[2][2]*rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			m[0][0] *= inv_fact;
			m[0][1] *= inv_fact;
			m[0][2] *= inv_fact;
			m[1][0] *= inv_fact;
			m[1][1] *= inv_fact;
			m[1][2] *= inv_fact;
			m[2][0] *= inv_fact;
			m[2][1] *= inv_fact;
			m[2][2] *= inv_fact;
		}
		else
		{
			m[0][0] /= rhs;
			m[0][1] /= rhs;
			m[0][2] /= rhs;
			m[1][0] /= rhs;
			m[1][1] /= rhs;
			m[1][2] /= rhs;
			m[2][0] /= rhs;
			m[2][1] /= rhs;
			m[2][2] /= rhs;
		}
		return *this;
	}

public:

	S*	
    operator[](const int64 c)
    {	
		assert(0 <= c && c < cols);
		return m[c]; 
	}

    const S*
    operator[](const int64 c) const
    {	
		assert(0 <= c && c < cols);
		return m[c]; 
	}

private:	// Member variables.

	S m[3][3];	// m[col][row]
};

// Static constants.

template<typename S> 
const mat<3,3,S> mat<3,3,S>::identity(T::one());

//------------------------------------------------------------------------------

// 4x4 matrix

template<typename S>
class mat<4,4,S>
{
public:

	typedef S value_type;
	
	static const int64 dim  = 4;
	static const int64 rows = 4;
	static const int64 cols = 4;

	static const mat<4,4,S> identity;

public:

	explicit
	mat(const S v = T::one())
    {
        m[0][0] = v;
        m[0][1] = T::zero();
		m[0][2] = T::zero();
        m[0][3] = T::zero();
        m[1][0] = T::zero();
		m[1][1] = v;
		m[1][2] = T::zero();
		m[1][3] = T::zero();
		m[2][0] = T::zero();
		m[2][1] = T::zero();
		m[2][2] = v;
		m[2][3] = T::zero();
		m[3][0] = T::zero();
		m[3][1] = T::zero();
		m[3][2] = T::zero();
		m[3][3] = v;
    }

	explicit
	mat(const S a0, const S a4, const S a8,  const S a12,
		const S a1, const S a5, const S a9,  const S a13,
		const S a2, const S a6, const S a10, const S a14,
		const S a3, const S a7, const S a11, const S a15)
	{	// Column-major.
		//
        m[0][0] = a0;
        m[0][1] = a1;
		m[0][2] = a2;
		m[0][3] = a3;
        m[1][0] = a4;
        m[1][1] = a5;
		m[1][2] = a6;
		m[1][3] = a7;
		m[2][0] = a8;
        m[2][1] = a9;
		m[2][2] = a10;
		m[2][3] = a11;
		m[3][0] = a12;
		m[3][1] = a13;
		m[3][2] = a14;
		m[3][3] = a15;
	}

	explicit
	mat(const S a[16])
	{	
        m[0][0] = a[0];
        m[0][1] = a[1];
		m[0][2] = a[2];
		m[0][3] = a[3];
        m[1][0] = a[4];
        m[1][1] = a[5];
		m[1][2] = a[6];
		m[1][3] = a[7];
		m[2][0] = a[8];
        m[2][1] = a[9];
		m[2][2] = a[10];
		m[2][3] = a[11];
		m[3][0] = a[12];
		m[3][1] = a[13];
		m[3][2] = a[14];
		m[3][3] = a[15];
	}

	//explicit
	//mat(const quaternion<S,T>& q)
	//{
	//	m[0][0] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.w*q.v.w);
 //       m[0][1] =		     static_cast<S>(2)*(q.v.y*q.v.z + q.v.w*q.v.x);
 //       m[0][2] =		     static_cast<S>(2)*(q.v.y*q.v.w - q.v.z*q.v.x);
	//	m[0][3] = T::zero();
 //       
 //       m[1][0] =		     static_cast<S>(2)*(q.v.y*q.v.z - q.v.w*q.v.x);
 //       m[1][1] = T::one() - static_cast<S>(2)*(q.v.w*q.v.w + q.v.y*q.v.y);
 //       m[1][2] =		     static_cast<S>(2)*(q.v.z*q.v.w + q.v.y*q.v.x);
 //       m[1][3] = T::zero();
 //       
 //       m[2][0] =		     static_cast<S>(2)*(q.v.w*q.v.y + q.v.z*q.v.x);
 //       m[2][1] =		     static_cast<S>(2)*(q.v.z*q.v.w - q.v.y*q.v.x);
 //       m[2][2] = T::one() - static_cast<S>(2)*(q.v.z*q.v.z + q.v.y*q.v.y);
 //       m[2][3] = T::zero();
 //       
 //       m[3][0] = T::zero();
 //       m[3][1] = T::zero();
 //       m[3][2] = T::zero();
 //       m[3][3] = T::one();
	//}

	explicit
    mat(const mat<4,4,S>& rhs)
    {
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[0][2] = rhs[0][2];
		m[0][3] = rhs[0][3];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
        m[1][2] = rhs[1][2];
		m[1][3] = rhs[1][3];
        m[2][0] = rhs[2][0];
        m[2][1] = rhs[2][1];
		m[2][2] = rhs[2][2];
		m[2][3] = rhs[2][3];
        m[3][0] = rhs[3][0];
        m[3][1] = rhs[3][1];
		m[3][2] = rhs[3][2];
		m[3][3] = rhs[3][3];
    }

	//! DTOR.
	~mat() 
	{}

public:

	mat<4,4,S>& 
	operator=(const mat<4,4,S> &rhs)
	{
        m[0][0] = rhs[0][0];
        m[0][1] = rhs[0][1];
        m[0][2] = rhs[0][2];
		m[0][3] = rhs[0][3];
        m[1][0] = rhs[1][0];
        m[1][1] = rhs[1][1];
        m[1][2] = rhs[1][2];
		m[1][3] = rhs[1][3];
        m[2][0] = rhs[2][0];
        m[2][1] = rhs[2][1];
		m[2][2] = rhs[2][2];
		m[2][3] = rhs[2][3];
        m[3][0] = rhs[3][0];
        m[3][1] = rhs[3][1];
		m[3][2] = rhs[3][2];
		m[3][3] = rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator+=(const mat<4,4,S> &rhs)
	{
        m[0][0] += rhs[0][0];
        m[0][1] += rhs[0][1];
        m[0][2] += rhs[0][2];
		m[0][3] += rhs[0][3];
        m[1][0] += rhs[1][0];
        m[1][1] += rhs[1][1];
        m[1][2] += rhs[1][2];
		m[1][3] += rhs[1][3];
        m[2][0] += rhs[2][0];
        m[2][1] += rhs[2][1];
		m[2][2] += rhs[2][2];
		m[2][3] += rhs[2][3];
        m[3][0] += rhs[3][0];
        m[3][1] += rhs[3][1];
		m[3][2] += rhs[3][2];
		m[3][3] += rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator-=(const mat<4,4,S> &rhs)
	{
        m[0][0] -= rhs[0][0];
        m[0][1] -= rhs[0][1];
        m[0][2] -= rhs[0][2];
		m[0][3] -= rhs[0][3];
        m[1][0] -= rhs[1][0];
        m[1][1] -= rhs[1][1];
        m[1][2] -= rhs[1][2];
		m[1][3] -= rhs[1][3];
        m[2][0] -= rhs[2][0];
        m[2][1] -= rhs[2][1];
		m[2][2] -= rhs[2][2];
		m[2][3] -= rhs[2][3];
        m[3][0] -= rhs[3][0];
        m[3][1] -= rhs[3][1];
		m[3][2] -= rhs[3][2];
		m[3][3] -= rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator*=(const S rhs)
	{
        m[0][0] *= rhs;
        m[0][1] *= rhs;
        m[0][2] *= rhs;
		m[0][3] *= rhs;
        m[1][0] *= rhs;
        m[1][1] *= rhs;
        m[1][2] *= rhs;
		m[1][3] *= rhs;
        m[2][0] *= rhs;
        m[2][1] *= rhs;
		m[2][2] *= rhs;
		m[2][3] *= rhs;
        m[3][0] *= rhs;
        m[3][1] *= rhs;
		m[3][2] *= rhs;
		m[3][3] *= rhs;
		return *this;
	}

	mat<4,4,S>
	operator*=(const mat<4,4,S> &r)
	{	
		// Matrix multiplication.
		
		const mat<4,4,S,T> l(*this);
		m[0][0]=l[0][0]*r[0][0]+l[1][0]*r[0][1]+l[2][0]*r[0][2]+l[3][0]*r[0][3];
		m[0][1]=l[0][1]*r[0][0]+l[1][1]*r[0][1]+l[2][1]*r[0][2]+l[3][1]*r[0][3];
		m[0][2]=l[0][2]*r[0][0]+l[1][2]*r[0][1]+l[2][2]*r[0][2]+l[3][2]*r[0][3];
		m[0][3]=l[0][3]*r[0][0]+l[1][3]*r[0][1]+l[2][3]*r[0][2]+l[3][3]*r[0][3];
		m[1][0]=l[0][0]*r[1][0]+l[1][0]*r[1][1]+l[2][0]*r[1][2]+l[3][0]*r[1][3];
		m[1][1]=l[0][1]*r[1][0]+l[1][1]*r[1][1]+l[2][1]*r[1][2]+l[3][1]*r[1][3];
		m[1][2]=l[0][2]*r[1][0]+l[1][2]*r[1][1]+l[2][2]*r[1][2]+l[3][2]*r[1][3];
		m[1][3]=l[0][3]*r[1][0]+l[1][3]*r[1][1]+l[2][3]*r[1][2]+l[3][3]*r[1][3];
		m[2][0]=l[0][0]*r[2][0]+l[1][0]*r[2][1]+l[2][0]*r[2][2]+l[3][0]*r[2][3];
		m[2][1]=l[0][1]*r[2][0]+l[1][1]*r[2][1]+l[2][1]*r[2][2]+l[3][1]*r[2][3];
		m[2][2]=l[0][2]*r[2][0]+l[1][2]*r[2][1]+l[2][2]*r[2][2]+l[3][2]*r[2][3];
		m[2][3]=l[0][3]*r[2][0]+l[1][3]*r[2][1]+l[2][3]*r[2][2]+l[3][3]*r[2][3];
		m[3][0]=l[0][0]*r[3][0]+l[1][0]*r[3][1]+l[2][0]*r[3][2]+l[3][0]*r[3][3];
		m[3][1]=l[0][1]*r[3][0]+l[1][1]*r[3][1]+l[2][1]*r[3][2]+l[3][1]*r[3][3];
		m[3][2]=l[0][2]*r[3][0]+l[1][2]*r[3][1]+l[2][2]*r[3][2]+l[3][2]*r[3][3];
		m[3][3]=l[0][3]*r[3][0]+l[1][3]*r[3][1]+l[2][3]*r[3][2]+l[3][3]*r[3][3];
		return *this;
	}

	mat<4,4,S,T>& 
	operator/=(const S rhs)
	{
		assert(!is_zero(rhs));
		if( T::is_floating )
		{	// Compile-time branching.
			//
			const S inv_fact(T::one()/rhs);
			m[0][0] *= inv_fact;
			m[0][1] *= inv_fact;
			m[0][2] *= inv_fact;
			m[0][3] *= inv_fact;
			m[1][0] *= inv_fact;
			m[1][1] *= inv_fact;
			m[1][2] *= inv_fact;
			m[1][3] *= inv_fact;
			m[2][0] *= inv_fact;
			m[2][1] *= inv_fact;
			m[2][2] *= inv_fact;
			m[2][3] *= inv_fact;
			m[3][0] *= inv_fact;
			m[3][1] *= inv_fact;
			m[3][2] *= inv_fact;
			m[3][3] *= inv_fact;
		}
		else
		{
			m[0][0] /= rhs;
			m[0][1] /= rhs;
			m[0][2] /= rhs;
			m[0][3] /= rhs;
			m[1][0] /= rhs;
			m[1][1] /= rhs;
			m[1][2] /= rhs;
			m[1][3] /= rhs;
			m[2][0] /= rhs;
			m[2][1] /= rhs;
			m[2][2] /= rhs;
			m[2][3] /= rhs;
			m[3][0] /= rhs;
			m[3][1] /= rhs;
			m[3][2] /= rhs;
			m[3][3] /= rhs;
		}
		return *this;
	}

public:

	S*	
    operator[](const int64 i)
    {	// Return column[i]
		//
		assert(0 <= i && i < cols);
		return m[i]; 
	}

    const S*
    operator[](const int64 i) const
    {	// Return column[i]
		//
		assert(0 <= i && i < cols);
		return m[i]; 
	}

private:	// Member variables.

	S _m[4][4];	// m[col][row]
};

// Static constants.

template<typename S> 
const mat<4,4,S> mat<4,4,S>::identity(T::one());

//------------------------------------------------------------------------------

// Convenient types, add more if appropriate.

typedef mat<2,2,float32>	mat22f32;
typedef mat<2,2,float64>	mat22f64;
typedef mat<2,2,int8>		mat22i8;
typedef mat<2,2,int16>		mat22i16;
typedef mat<2,2,int32>		mat22i32;
typedef mat<2,2,int64>		mat22i64;
typedef mat<2,2,uint8>		mat22ui8;
typedef mat<2,2,uint16>		mat22ui16;
typedef mat<2,2,uint32>		mat22ui32;
typedef mat<2,2,uint64>		mat22ui64;

typedef mat<3,3,float32>	mat33f32;
typedef mat<3,3,float64>	mat33f64;
typedef mat<3,3,int8>		mat33i8;
typedef mat<3,3,int16>		mat33i16;
typedef mat<3,3,int32>		mat33i32;
typedef mat<3,3,int64>		mat33i64;
typedef mat<3,3,uint8>		mat33ui8;
typedef mat<3,3,uint16>		mat33ui16;
typedef mat<3,3,uint32>		mat33ui32;
typedef mat<3,3,uint64>		mat33ui64;

typedef mat<4,4,float32>	mat44f32;
typedef mat<4,4,float64>	mat44f64;
typedef mat<4,4,int8>		mat44i8;
typedef mat<4,4,int16>		mat44i16;
typedef mat<4,4,int32>		mat44i32;
typedef mat<4,4,int64>		mat44i64;
typedef mat<4,4,uint8>		mat44ui8;
typedef mat<4,4,uint16>		mat44ui16;
typedef mat<4,4,uint32>		mat44ui32;
typedef mat<4,4,uint64>		mat44ui64;

}	// Namespace: thx.

#endif	// THX_MAT_HPP_INCLUDED
