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

// mat<N,S>

template<int64 N, typename S>
class mat
{
public:

	typedef S value_type;
    static const int64 dim = N;

public:

	//! Empty CTOR.
	explicit
	mat(const S s = 1)
    {
		for (int64 i(0); i < N; ++i) {
            for (int64 j(0); j < N; ++j) {
                _v[i][j] = ((i == j) ? s : 0); // Set diagonal to value.
            }
		}
    }

	//! Copy CTOR.
	//explicit
    mat(const mat<N,S> &rhs)
    {
		for (int64 i(0); i < (rows*cols); ++i) {
			_v[i] = rhs[i];
		}
    }

public:		// Operators.

	mat<N,S>& 
	operator=(const mat<N,S> &b)
	{
		for (int64 i(0); i < (rows*cols); ++i) {
			_v[i] = b[i];
		}
		return *this;
	}

	mat<N,S>& 
	operator+=(const mat<N,S> &b)
	{
		for (int64 i(0); i < (rows*cols); ++i) {
			_v[i] += b[i];
		}
		return *this;
	}

	mat<N,S>& 
	operator-=(const mat<N,S> &b)
	{
		for (int64 i(0); i < (rows*cols); ++i) {
			_v[i] -= b[i];
		}
		return *this;
	}

	mat<N,S>& 
	operator*=(const S s)
	{
		for (int64 i(0); i < (rows*cols); ++i) {
			_v[i] *= s;
		}
		return *this;
	}

	//! Matrix multiplication. NB: Algorithm for square matrices only.
	mat<N,S>& 
	operator*=(const mat<N,S> &b)
	{	
		const mat<C,R,S> a(*this);  // Deep copy.
		int j(0), k(0);
		for (int i(0); i < dim; ++i) {
			for (j = 0; j < dim; ++j) {
                _v[i][j] = 0;
				for (k = 0; k < dim; ++k) {
                    _v[i][j] = _v[i][j] + a[i][k]*b[k][j];
				}
			}
		}
		return *this;
	}

public:     // Access operators.

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

private:		// Member variables

	S _v[N][N];
};

//------------------------------------------------------------------------------

// mat<2,S>

template<typename S>
class mat<2,S>
{
public:

	typedef S value_type;
	static const int64 dim = 2;

	static const mat<2,S> identity;

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
	//explicit
    mat(const mat<2,S> &rhs)
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

	mat<2,S>& 
	operator=(const mat<2,S> &b)
	{
        _v[0][0] = b[0][0];
        _v[0][1] = b[0][1];
        _v[1][0] = b[1][0];
        _v[1][1] = b[1][1];
		return *this;
	}

	mat<2,S>& 
	operator+=(const mat<2,S> &b)
	{
        _v[0][0] += b[0][0];
        _v[0][1] += b[0][1];
        _v[1][0] += b[1][0];
        _v[1][1] += b[1][1];
		return *this;
	}

	mat<2,S>& 
	operator-=(const mat<2,S> &b)
	{
        _v[0][0] -= b[0][0];
        _v[0][1] -= b[0][1];
        _v[1][0] -= b[1][0];
        _v[1][1] -= b[1][1];
		return *this;
	}

	mat<2,S>& 
	operator*=(const S s)
	{
        _v[0][0] *= s;
        _v[0][1] *= s;
        _v[1][0] *= s;
        _v[1][1] *= s;
		return *this;
	}

	mat<2,S>& 
	operator*=(const mat<2,S> &b)
	{	// Matrix multiplication.
		//
		const mat<2,S> a(*this);
		_v[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1];
		_v[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1];
		_v[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1];
		_v[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1];
		return *this;
	}

public:     // Access operators.

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

private:		// Member variables

	S _v[2][2];
};

// Static constants.

template<typename S> 
const mat<2,S> mat<2,S>::identity(1);

//------------------------------------------------------------------------------

// mat<3,S>

template<typename S>
class mat<3,S>
{
public:

	typedef S value_type;
	static const int64 dim = 3;
	static const mat<3,S> identity;

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
	//explicit
    mat(const mat<3,S> &rhs)
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
	mat<3,S>& 
	operator=(const mat<3,S> &rhs)
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

	mat<3,S>& 
	operator+=(const mat<3,S> &b)
	{
        _v[0][0] += b[0][0];
        _v[0][1] += b[0][1];
        _v[0][2] += b[0][2];
        _v[1][0] += b[1][0];
        _v[1][1] += b[1][1];
        _v[1][2] += b[1][2];
        _v[2][0] += b[2][0];
        _v[2][1] += b[2][1];
		_v[2][2] += b[2][2];
		return *this;
	}

	mat<3,S>& 
	operator-=(const mat<3,S> &b)
	{
        _v[0][0] -= b[0][0];
        _v[0][1] -= b[0][1];
        _v[0][2] -= b[0][2];
        _v[1][0] -= b[1][0];
        _v[1][1] -= b[1][1];
        _v[1][2] -= b[1][2];
        _v[2][0] -= b[2][0];
        _v[2][1] -= b[2][1];
		_v[2][2] -= b[2][2];
		return *this;
	}

	mat<3,S>& 
	operator*=(const S s)
	{
        _v[0][0] *= s;
        _v[0][1] *= s;
        _v[0][2] *= s;
        _v[1][0] *= s;
        _v[1][1] *= s;
        _v[1][2] *= s;
        _v[2][0] *= s;
        _v[2][1] *= s;
		_v[2][2] *= s;
		return *this;
	}

	//! Matrix multiplication.
	mat<3,S>& 
	operator*=(const mat<3,S> &b)
	{	
		const mat<3,S> a(*this);
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

public:     // Access operators.

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

private:		// Member variables.

	S _v[3][3];
};

// Static constants.

template<typename S> 
const mat<3,S> mat<3,S>::identity(1);

//------------------------------------------------------------------------------

// mat<4,S>

template<typename S>
class mat<4,S>
{
public:

	typedef S value_type;
	static const int64 dim = 4;
	static const mat<4,S> identity;

public:

	//! Empty CTOR.
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
	//explicit
    mat(const mat<4,S> &rhs)
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

	//! Value CTOR - column major.
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

	//! Array CTOR - column major.
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

	mat<4,S>& 
	operator=(const mat<4,S> &rhs)
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

	mat<4,S>& 
	operator+=(const mat<4,S> &b)
	{
        _v[0][0] += b[0][0];
        _v[0][1] += b[0][1];
        _v[0][2] += b[0][2];
		_v[0][3] += b[0][3];
        _v[1][0] += b[1][0];
        _v[1][1] += b[1][1];
        _v[1][2] += b[1][2];
		_v[1][3] += b[1][3];
        _v[2][0] += b[2][0];
        _v[2][1] += b[2][1];
		_v[2][2] += b[2][2];
		_v[2][3] += b[2][3];
        _v[3][0] += b[3][0];
        _v[3][1] += b[3][1];
		_v[3][2] += b[3][2];
		_v[3][3] += b[3][3];
		return *this;
	}

	mat<4,S>& 
	operator-=(const mat<4,S> &b)
	{
        _v[0][0] -= b[0][0];
        _v[0][1] -= b[0][1];
        _v[0][2] -= b[0][2];
		_v[0][3] -= b[0][3];
        _v[1][0] -= b[1][0];
        _v[1][1] -= b[1][1];
        _v[1][2] -= b[1][2];
		_v[1][3] -= b[1][3];
        _v[2][0] -= b[2][0];
        _v[2][1] -= b[2][1];
		_v[2][2] -= b[2][2];
		_v[2][3] -= b[2][3];
        _v[3][0] -= b[3][0];
        _v[3][1] -= b[3][1];
		_v[3][2] -= b[3][2];
		_v[3][3] -= b[3][3];
		return *this;
	}

	mat<4,S>& 
	operator*=(const S s)
	{
        _v[0][0] *= s;
        _v[0][1] *= s;
        _v[0][2] *= s;
		_v[0][3] *= s;
        _v[1][0] *= s;
        _v[1][1] *= s;
        _v[1][2] *= s;
		_v[1][3] *= s;
        _v[2][0] *= s;
        _v[2][1] *= s;
		_v[2][2] *= s;
		_v[2][3] *= s;
        _v[3][0] *= s;
        _v[3][1] *= s;
		_v[3][2] *= s;
		_v[3][3] *= s;
		return *this;
	}

	//! Matrix multiplication.
	mat<4,S>&
	operator*=(const mat<4,S> &b)
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

public:     // Access operators.

	//! Return i'th column.
	S*	
    operator[](const int64 i)
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

	//! Return i'th column.
    const S*
    operator[](const int64 i) const
    {	
		assert(0 <= i && i < dim);
		return _v[i]; 
	}

private:		// Member variables.

	S _v[4][4];
};

// Static constants.

template<typename S> 
const mat<4,S> mat<4,S>::identity(1);

//------------------------------------------------------------------------------

// Convenient types, add more if appropriate.

typedef mat<2,float32>	mat2f32;
typedef mat<2,float64>	mat2f64;
typedef mat<2,int8>		mat2i8;
typedef mat<2,int16>	mat2i16;
typedef mat<2,int32>	mat2i32;
typedef mat<2,int64>	mat2i64;
typedef mat<2,uint8>	mat2ui8;
typedef mat<2,uint16>	mat2ui16;
typedef mat<2,uint32>	mat2ui32;
typedef mat<2,uint64>	mat2ui64;

typedef mat<3,float32>	mat3f32;
typedef mat<3,float64>	mat3f64;
typedef mat<3,int8>		mat3i8;
typedef mat<3,int16>	mat3i16;
typedef mat<3,int32>	mat3i32;
typedef mat<3,int64>	mat3i64;
typedef mat<3,uint8>	mat3ui8;
typedef mat<3,uint16>	mat3ui16;
typedef mat<3,uint32>	mat3ui32;
typedef mat<3,uint64>	mat3ui64;

typedef mat<4,float32>	mat4f32;
typedef mat<4,float64>	mat4f64;
typedef mat<4,int8>		mat4i8;
typedef mat<4,int16>	mat4i16;
typedef mat<4,int32>	mat4i32;
typedef mat<4,int64>	mat4i64;
typedef mat<4,uint8>	mat4ui8;
typedef mat<4,uint16>	mat4ui16;
typedef mat<4,uint32>	mat4ui32;
typedef mat<4,uint64>	mat4ui64;

}	// Namespace: thx.

#endif	// THX_MAT_HPP_INCLUDED
