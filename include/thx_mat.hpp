//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_HPP_INCLUDED
#define THX_MAT_HPP_INCLUDED

#include "thx_types.hpp"
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// CxR

template<int64 C, int64 R, typename S>
class mat
{
public:

	typedef S value_type;

	static const int64 rows = C;
	static const int64 cols = R;

public:

	//! CTOR.
	explicit
	mat(const S v = 0)
    {
		S *p(_v[0]);
		for (int i(0); i < (rows*cols); ++i) {
			p[i] = v;
		}
    }

	//! Copy CTOR.
	explicit
    mat(const mat<C,R,S> &rhs)
    {
		S *a(_v[0]);
		const S *b(rhs[0]);
		for (int i(0); i < (rows*cols); ++i) {
			a[i] = b[i];
		}
    }

public:		// Operators.

	mat<C,R,S>& 
	operator=(const mat<C,R,S> &rhs)
	{
		S *a(_v[0]);
		const S *b(rhs[0]);
		for (int i(0); i < (rows*cols); ++i) {
			a[i] = b[i];
		}
		return *this;
	}

	mat<C,R,S>& 
	operator+=(const mat<C,R,S> &rhs)
	{
		S *a(_v[0]);
		const S *b(rhs[0]);
		for (int i(0); i < (rows*cols); ++i) {
			a[i] += b[i];
		}
		return *this;
	}

	mat<C,R,S>& 
	operator-=(const mat<C,R,S> &rhs)
	{
		S *a(_v[0]);
		const S *b(rhs[0]);
		for (int i(0); i < (rows*cols); ++i) {
			a[i] -= b[i];
		}
		return *this;
	}

	mat<C,R,S>& 
	operator*=(const S rhs)
	{
		S *a(_v[0]);
		for (int i(0); i < (rows*cols); ++i) {
			a[i] *= rhs;
		}
		return *this;
	}

	//! Matrix multiplication.
	mat<C,R,S>& 
	operator*=(const mat<C,R,S> &b)
	{	
		const mat<C,R,S> a(*this);
		int j(0), k(0);
		int sum(0);
		for (int i(0); i < cols; ++i) {
			for (j = 0; j < rows; ++j) {
				sum = 0;
				for (k = 0; k < cols; ++k) {
					sum += a[i][k]*b[k][j];
				}
				_v[i][j] = sum;
			}
		}
		return *this;
	}

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

private:		// Member variables

	S _v[C][R];
};

//------------------------------------------------------------------------------

// 2x2

template<typename S>
class mat<2,2,S>
{
public:

	typedef S value_type;

	static const int64 dim  = 2;
	static const int64 rows = 2;
	static const int64 cols = 2;

	static const mat<2,2,S> identity;

public:

	explicit
	mat(const S v = 1)
    {
        _v[0][0] = v;
        _v[0][1] = 0;
        _v[1][0] = 0;
        _v[1][1] = v;
    }

	//! Copy CTOR.
	explicit
    mat(const mat<2,2,S> &rhs)
    {
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
    }

	//! Column-major.
	explicit
	mat(const S a0, const S a2,
		const S a1, const S a3)
	{	
        _v[0][0] = a0;
        _v[0][1] = a1;
		_v[1][0] = a2;
        _v[1][1] = a3;
	}

	//! Column-major.
	explicit
	mat(const S a[4])
	{	
        _v[0][0] = a[0];
        _v[0][1] = a[1];
		_v[1][0] = a[2];
        _v[1][1] = a[3];
	}

	//! DTOR.
	~mat() 
	{}

public:		// Operators.

	mat<2,2,S>& 
	operator=(const mat<2,2,S> &rhs)
	{
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator+=(const mat<2,2,S> &rhs)
	{
        _v[0][0] += rhs[0][0];
        _v[0][1] += rhs[0][1];
        _v[1][0] += rhs[1][0];
        _v[1][1] += rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator-=(const mat<2,2,S> &rhs)
	{
        _v[0][0] -= rhs[0][0];
        _v[0][1] -= rhs[0][1];
        _v[1][0] -= rhs[1][0];
        _v[1][1] -= rhs[1][1];
		return *this;
	}

	mat<2,2,S>& 
	operator*=(const S rhs)
	{
        _v[0][0] *= rhs;
        _v[0][1] *= rhs;
        _v[1][0] *= rhs;
        _v[1][1] *= rhs;
		return *this;
	}

	mat<2,2,S>& 
	operator*=(const mat<2,2,S,T> &b)
	{	// Matrix multiplication.
		//
		const mat<2,2,S,T> a(*this);
		_v[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1];
		_v[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1];
		_v[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1];
		_v[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1];
		return *this;
	}

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

private:		// Member variables

	S _v[2][2];
};

// Static constants.

template<typename S> 
const mat<2,2,S> mat<2,2,S>::identity(1);

//------------------------------------------------------------------------------

// 3x3

template<typename S>
class mat<3,3,S>
{
public:

	typedef S value_type;

	static const int64 dim  = 3;
	static const int64 rows = 3;
	static const int64 cols = 3;

	static const mat<3,3,S> identity;

public:

	//! CTOR.
	explicit
	mat(const S v = 1)
    {
        _v[0][0] = v;
        _v[0][1] = 0;
		_v[0][2] = 0;
        _v[1][0] = 0;
        _v[1][1] = v;
		_v[1][2] = 0;
		_v[2][0] = 0;
		_v[2][1] = 0;
		_v[2][2] = v;
    }

	//! Copy CTOR.
	explicit
    mat(const mat<3,3,S> &rhs)
    {
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[0][2] = rhs[0][2];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
        _v[1][2] = rhs[1][2];
        _v[2][0] = rhs[2][0];
        _v[2][1] = rhs[2][1];
		_v[2][2] = rhs[2][2];
    }

	//! Column-major.
	explicit
	mat(const S a0, const S a3, const S a6,
		const S a1, const S a4, const S a7,
		const S a2, const S a5, const S a8)
	{	
        _v[0][0] = a0;
        _v[0][1] = a1;
		_v[0][2] = a2;
        _v[1][0] = a3;
        _v[1][1] = a4;
		_v[1][2] = a5;
        _v[2][0] = a6;
        _v[2][1] = a7;
		_v[2][2] = a8;
	}

	//! Column-major.
	explicit
	mat(const S a[9])
	{	
        _v[0][0] = a[0];
        _v[0][1] = a[1];
		_v[0][2] = a[2];
        _v[1][0] = a[3];
        _v[1][1] = a[4];
		_v[1][2] = a[5];
        _v[2][0] = a[6];
        _v[2][1] = a[7];
		_v[2][2] = a[8];
	}

	//! DTOR.
	~mat() 
	{}

public:		// Operators.

	//! Assign.
	mat<3,3,S>& 
	operator=(const mat<3,3,S> &rhs)
	{
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[0][2] = rhs[0][2];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
        _v[1][2] = rhs[1][2];
        _v[2][0] = rhs[2][0];
        _v[2][1] = rhs[2][1];
		_v[2][2] = rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator+=(const mat<3,3,S> &rhs)
	{
        _v[0][0] += rhs[0][0];
        _v[0][1] += rhs[0][1];
        _v[0][2] += rhs[0][2];
        _v[1][0] += rhs[1][0];
        _v[1][1] += rhs[1][1];
        _v[1][2] += rhs[1][2];
        _v[2][0] += rhs[2][0];
        _v[2][1] += rhs[2][1];
		_v[2][2] += rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator-=(const mat<3,3,S> &rhs)
	{
        _v[0][0] -= rhs[0][0];
        _v[0][1] -= rhs[0][1];
        _v[0][2] -= rhs[0][2];
        _v[1][0] -= rhs[1][0];
        _v[1][1] -= rhs[1][1];
        _v[1][2] -= rhs[1][2];
        _v[2][0] -= rhs[2][0];
        _v[2][1] -= rhs[2][1];
		_v[2][2] -= rhs[2][2];
		return *this;
	}

	mat<3,3,S>& 
	operator*=(const S rhs)
	{
        _v[0][0] *= rhs;
        _v[0][1] *= rhs;
        _v[0][2] *= rhs;
        _v[1][0] *= rhs;
        _v[1][1] *= rhs;
        _v[1][2] *= rhs;
        _v[2][0] *= rhs;
        _v[2][1] *= rhs;
		_v[2][2] *= rhs;
		return *this;
	}

	//! Matrix multiplication.
	mat<3,3,S>& 
	operator*=(const mat<3,3,S> &b)
	{	
		const mat<3,3,S> a(*this);
		_v[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2];
		_v[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2];
		_v[0][2] = a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2];
		_v[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2];
		_v[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2];
		_v[1][2] = a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2];
		_v[2][2] = a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2];
		_v[2][1] = a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2];
		_v[2][2] = a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2];
		return *this;
	}

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < cols);
		return _v[i]; 
	}

private:		// Member variables.

	S _v[3][3];
};

// Static constants.

template<typename S> 
const mat<3,3,S> mat<3,3,S>::identity(1);

//------------------------------------------------------------------------------

// 4x4

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

	//! CTOR.
	explicit
	mat(const S v = 1)
    {
        _v[0][0] = v;
        _v[0][1] = 0;
		_v[0][2] = 0;
        _v[0][3] = 0;
        _v[1][0] = 0;
		_v[1][1] = v;
		_v[1][2] = 0;
		_v[1][3] = 0;
		_v[2][0] = 0;
		_v[2][1] = 0;
		_v[2][2] = v;
		_v[2][3] = 0;
		_v[3][0] = 0;
		_v[3][1] = 0;
		_v[3][2] = 0;
		_v[3][3] = v;
    }

	//! Copy CTOR.
	explicit
    mat(const mat<4,4,S> &rhs)
    {
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[0][2] = rhs[0][2];
		_v[0][3] = rhs[0][3];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
        _v[1][2] = rhs[1][2];
		_v[1][3] = rhs[1][3];
        _v[2][0] = rhs[2][0];
        _v[2][1] = rhs[2][1];
		_v[2][2] = rhs[2][2];
		_v[2][3] = rhs[2][3];
        _v[3][0] = rhs[3][0];
        _v[3][1] = rhs[3][1];
		_v[3][2] = rhs[3][2];
		_v[3][3] = rhs[3][3];
    }

	//! CTOR - column major.
	explicit
	mat(const S a0, const S a4, const S a8,  const S a12,
		const S a1, const S a5, const S a9,  const S a13,
		const S a2, const S a6, const S a10, const S a14,
		const S a3, const S a7, const S a11, const S a15)
	{	
        _v[0][0] = a0;
        _v[0][1] = a1;
		_v[0][2] = a2;
		_v[0][3] = a3;
        _v[1][0] = a4;
        _v[1][1] = a5;
		_v[1][2] = a6;
		_v[1][3] = a7;
		_v[2][0] = a8;
        _v[2][1] = a9;
		_v[2][2] = a10;
		_v[2][3] = a11;
		_v[3][0] = a12;
		_v[3][1] = a13;
		_v[3][2] = a14;
		_v[3][3] = a15;
	}

	//! CTOR - column major.
	explicit
	mat(const S a[16])
	{	
        _v[0][0] = a[0];
        _v[0][1] = a[1];
		_v[0][2] = a[2];
		_v[0][3] = a[3];
        _v[1][0] = a[4];
        _v[1][1] = a[5];
		_v[1][2] = a[6];
		_v[1][3] = a[7];
		_v[2][0] = a[8];
        _v[2][1] = a[9];
		_v[2][2] = a[10];
		_v[2][3] = a[11];
		_v[3][0] = a[12];
		_v[3][1] = a[13];
		_v[3][2] = a[14];
		_v[3][3] = a[15];
	}

	//! DTOR.
	~mat() 
	{}

public:		// Operators.

	mat<4,4,S>& 
	operator=(const mat<4,4,S> &rhs)
	{
        _v[0][0] = rhs[0][0];
        _v[0][1] = rhs[0][1];
        _v[0][2] = rhs[0][2];
		_v[0][3] = rhs[0][3];
        _v[1][0] = rhs[1][0];
        _v[1][1] = rhs[1][1];
        _v[1][2] = rhs[1][2];
		_v[1][3] = rhs[1][3];
        _v[2][0] = rhs[2][0];
        _v[2][1] = rhs[2][1];
		_v[2][2] = rhs[2][2];
		_v[2][3] = rhs[2][3];
        _v[3][0] = rhs[3][0];
        _v[3][1] = rhs[3][1];
		_v[3][2] = rhs[3][2];
		_v[3][3] = rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator+=(const mat<4,4,S> &rhs)
	{
        _v[0][0] += rhs[0][0];
        _v[0][1] += rhs[0][1];
        _v[0][2] += rhs[0][2];
		_v[0][3] += rhs[0][3];
        _v[1][0] += rhs[1][0];
        _v[1][1] += rhs[1][1];
        _v[1][2] += rhs[1][2];
		_v[1][3] += rhs[1][3];
        _v[2][0] += rhs[2][0];
        _v[2][1] += rhs[2][1];
		_v[2][2] += rhs[2][2];
		_v[2][3] += rhs[2][3];
        _v[3][0] += rhs[3][0];
        _v[3][1] += rhs[3][1];
		_v[3][2] += rhs[3][2];
		_v[3][3] += rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator-=(const mat<4,4,S> &rhs)
	{
        _v[0][0] -= rhs[0][0];
        _v[0][1] -= rhs[0][1];
        _v[0][2] -= rhs[0][2];
		_v[0][3] -= rhs[0][3];
        _v[1][0] -= rhs[1][0];
        _v[1][1] -= rhs[1][1];
        _v[1][2] -= rhs[1][2];
		_v[1][3] -= rhs[1][3];
        _v[2][0] -= rhs[2][0];
        _v[2][1] -= rhs[2][1];
		_v[2][2] -= rhs[2][2];
		_v[2][3] -= rhs[2][3];
        _v[3][0] -= rhs[3][0];
        _v[3][1] -= rhs[3][1];
		_v[3][2] -= rhs[3][2];
		_v[3][3] -= rhs[3][3];
		return *this;
	}

	mat<4,4,S>& 
	operator*=(const S rhs)
	{
        _v[0][0] *= rhs;
        _v[0][1] *= rhs;
        _v[0][2] *= rhs;
		_v[0][3] *= rhs;
        _v[1][0] *= rhs;
        _v[1][1] *= rhs;
        _v[1][2] *= rhs;
		_v[1][3] *= rhs;
        _v[2][0] *= rhs;
        _v[2][1] *= rhs;
		_v[2][2] *= rhs;
		_v[2][3] *= rhs;
        _v[3][0] *= rhs;
        _v[3][1] *= rhs;
		_v[3][2] *= rhs;
		_v[3][3] *= rhs;
		return *this;
	}

	//! Matrix multiplication.
	mat<4,4,S>&
	operator*=(const mat<4,4,S>& b)
	{	
		const mat<4,4,S,T> a(*this);
		_v[0][0]=a[0][0]*b[0][0]+a[1][0]*b[0][1]+a[2][0]*b[0][2]+a[3][0]*b[0][3];
		_v[0][1]=a[0][1]*b[0][0]+a[1][1]*b[0][1]+a[2][1]*b[0][2]+a[3][1]*b[0][3];
		_v[0][2]=a[0][2]*b[0][0]+a[1][2]*b[0][1]+a[2][2]*b[0][2]+a[3][2]*b[0][3];
		_v[0][3]=a[0][3]*b[0][0]+a[1][3]*b[0][1]+a[2][3]*b[0][2]+a[3][3]*b[0][3];
		_v[1][0]=a[0][0]*b[1][0]+a[1][0]*b[1][1]+a[2][0]*b[1][2]+a[3][0]*b[1][3];
		_v[1][1]=a[0][1]*b[1][0]+a[1][1]*b[1][1]+a[2][1]*b[1][2]+a[3][1]*b[1][3];
		_v[1][2]=a[0][2]*b[1][0]+a[1][2]*b[1][1]+a[2][2]*b[1][2]+a[3][2]*b[1][3];
		_v[1][3]=a[0][3]*b[1][0]+a[1][3]*b[1][1]+a[2][3]*b[1][2]+a[3][3]*b[1][3];
		_v[2][0]=a[0][0]*b[2][0]+a[1][0]*b[2][1]+a[2][0]*b[2][2]+a[3][0]*b[2][3];
		_v[2][1]=a[0][1]*b[2][0]+a[1][1]*b[2][1]+a[2][1]*b[2][2]+a[3][1]*b[2][3];
		_v[2][2]=a[0][2]*b[2][0]+a[1][2]*b[2][1]+a[2][2]*b[2][2]+a[3][2]*b[2][3];
		_v[2][3]=a[0][3]*b[2][0]+a[1][3]*b[2][1]+a[2][3]*b[2][2]+a[3][3]*b[2][3];
		_v[3][0]=a[0][0]*b[3][0]+a[1][0]*b[3][1]+a[2][0]*b[3][2]+a[3][0]*b[3][3];
		_v[3][1]=a[0][1]*b[3][0]+a[1][1]*b[3][1]+a[2][1]*b[3][2]+a[3][1]*b[3][3];
		_v[3][2]=a[0][2]*b[3][0]+a[1][2]*b[3][1]+a[2][2]*b[3][2]+a[3][2]*b[3][3];
		_v[3][3]=a[0][3]*b[3][0]+a[1][3]*b[3][1]+a[2][3]*b[3][2]+a[3][3]*b[3][3];
		return *this;
	}

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < cols);
		return m[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < cols);
		return m[i]; 
	}

private:		// Member variables.

	S _v[4][4];
};

// Static constants.

template<typename S> 
const mat<4,4,S> mat<4,4,S>::identity(1);

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
