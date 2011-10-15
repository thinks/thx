//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_MAT_HPP_INCLUDED
#define THX_MAT_HPP_INCLUDED

#include "thx_types.hpp"
#include <algorithm>
#include <cassert>

//------------------------------------------------------------------------------

namespace thx
{

// mat<N,S> anatomy:
//
// Define value_type
// Define dimension
// Define linear size
// Define identity constant (specializations only)
//
// Empty CTOR (set to identity by default)
// Copy CTOR
// Array CTOR (specializations only)
// Value CTOR (specializations only)
// (All mat's have default DTOR)
//
// operator=
// operator+=
// operator-=
// operator*=(scalar)
// operator*=(matrix)
//
// operator()(row, col) const
// operator()(row, col)
// operator[](i) const
// operator[](i)
// 
// Matrix values are stored in column-major order. 

//------------------------------------------------------------------------------

// mat<N,S>

template<int64 N, typename S>
class mat
{
public:

    typedef S value_type;
    static const int64 dim = N;
    static const int64 size = N*N;

public:

    //! Empty CTOR.
    explicit
    mat(const S s = 1)
    {
        for (int64 i(0); i < N; ++i) {
            for (int64 j(0); j < N; ++j) {
                _at(i,j) = ((i == j) ? s : 0); // Set diagonal to value.
            }
        }
    }

    //! Copy CTOR.
    //explicit
    mat(const mat<N,S> &rhs)
    { std::copy(_v, _v + size, rhs._v); }

public:		// Operators.

    mat<N,S>& 
    operator=(const mat<N,S> &rhs)
    {
        std::copy(_v, _v + size, rhs._v);
        return *this;
    }

    mat<N,S>& 
    operator+=(const mat<N,S> &b)
    {
        for (int64 i(0); i < size; ++i) {
            _v[i] += rhs[i];
        }
        return *this;
    }

    mat<N,S>& 
    operator-=(const mat<N,S> &b)
    {
        for (int64 i(0); i < size; ++i) {
            _v[i] = rhs[i];
        }
        return *this;
    }

    mat<N,S>& 
    operator*=(const S s)
    {
        for (int64 i(0); i < size; ++i) {
            _v[i] *= s;
        }
        return *this;
    }

    //! Matrix multiplication.
    mat<N,S>& 
    operator*=(const mat<N,S> &b)
    {	
        const mat<N,S> a(*this);  // Deep copy.
        for (int64 i(0); i < N; ++i) {
            for (int64 j(0); j < N; ++j) {
                _at(i,j) = 0;
                for (int64 k(0); k < N; ++k) {
                    _at(i,j) = _at(i,j) + a(i,k)*b(k,j);
                }
            }
        }
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _at(i,j); }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _at(i,j); }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

private:

    S
    _at(const int64 i, const int64 j) const
    { return _v[i + N*j]; }

    S&
    _at(const int64 i, const int64 j)
    { return _v[i + N*j]; }

private:		// Member variables

    S _v[N*N];
    //S _v[N][N]; //! {col_0:{row_0,row_1,...} col_1:{row_0,row_1} ...}
};

//------------------------------------------------------------------------------

// mat<2,S>

template<typename S>
class mat<2,S>
{
public:

    typedef S value_type;
    static const int64 dim = 2;
    static const int64 size = 4;
    static const mat<2,S> identity;

public:

    //! Empty CTOR.
    explicit
    mat(const S v = 1)
    {
        _v[0] = v;
        _v[1] = 0;
        _v[2] = 0;
        _v[3] = v;
    }

    //! Copy CTOR.
    //explicit
    mat(const mat<2,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
    }

    //! Array CTOR - column-major.
    explicit
    mat(const S a[4])
    {	
        _v[0] = a[0];
        _v[1] = a[1];
        _v[2] = a[2];
        _v[3] = a[3];
    }

    //! Value CTOR - column-major.
    explicit
    mat(const S a0, const S a2,
        const S a1, const S a3)
    {	
        _v[0] = a0;
        _v[1] = a1;
        _v[2] = a2;
        _v[3] = a3;
    }

public:		// Operators.

    //! Assignment.
    mat<2,S>& 
    operator=(const mat<2,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
        return *this;
    }

    mat<2,S>& 
    operator+=(const mat<2,S> &b)
    {
        _v[0] += b[0];
        _v[1] += b[1];
        _v[2] += b[2];
        _v[3] += b[3];
        return *this;
    }

    mat<2,S>& 
    operator-=(const mat<2,S> &b)
    {
        _v[0] -= b[0];
        _v[1] -= b[1];
        _v[2] -= b[2];
        _v[3] -= b[3];
        return *this;
    }

    mat<2,S>& 
    operator*=(const S s)
    {
        _v[0] *= s;
        _v[1] *= s;
        _v[2] *= s;
        _v[3] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<2,S>& 
    operator*=(const mat<2,S> &b)
    {	
        const mat<2,S> a(*this);
        _at(0,0) = a(0,0)*b(0,0) + a(0,1)*b(1,0);
        _at(0,1) = a(0,0)*b(0,1) + a(0,1)*b(1,1);
        _at(1,0) = a(1,0)*b(0,0) + a(1,1)*b(1,0);
        _at(1,1) = a(1,0)*b(0,1) + a(1,1)*b(1,1);
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _at(i,j); }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S
    operator()(const int64 i, const int64 j) const
    { return _at(i,j); }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    S
    operator[](const int64 i) const
    { return _v[i]; }

private:

    S
    _at(const int64 i, const int64 j) const
    { return _v[i + 2*j]; }

    S&
    _at(const int64 i, const int64 j)
    { return _v[i + 2*j]; }

private:		// Member variables

    S _v[4];
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

    //! Empty CTOR.
    explicit
    mat(const S v = 1)
    {
        _v[0] = v;
        _v[1] = 0;
        _v[2] = 0;
        _v[3] = 0;
        _v[4] = v;
        _v[5] = 0;
        _v[6] = 0;
        _v[7] = 0;
        _v[8] = v;
    }

    //! Copy CTOR.
    //explicit
    mat(const mat<3,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
        _v[4] = rhs[4];
        _v[5] = rhs[5];
        _v[6] = rhs[6];
        _v[7] = rhs[7];
        _v[8] = rhs[8];
    }

    //! Array CTOR - column-major.
    explicit
    mat(const S a[9])
    {	
        _v[0] = a[0];
        _v[1] = a[1];
        _v[2] = a[2];
        _v[3] = a[3];
        _v[4] = a[4];
        _v[5] = a[5];
        _v[6] = a[6];
        _v[7] = a[7];
        _v[8] = a[8];
    }

    //! Value CTOR - column-major.
    explicit
    mat(const S a0, const S a3, const S a6,
        const S a1, const S a4, const S a7,
        const S a2, const S a5, const S a8)
    {	
        _v[0] = a0;
        _v[1] = a1;
        _v[2] = a2;
        _v[3] = a3;
        _v[4] = a4;
        _v[5] = a5;
        _v[6] = a6;
        _v[7] = a7;
        _v[8] = a8;
    }

public:		// Operators.

    //! Assignment.
    mat<3,S>& 
    operator=(const mat<3,S> &rhs)
    {
        _v[0] = rhs[0];
        _v[1] = rhs[1];
        _v[2] = rhs[2];
        _v[3] = rhs[3];
        _v[4] = rhs[4];
        _v[5] = rhs[5];
        _v[6] = rhs[6];
        _v[7] = rhs[7];
        _v[8] = rhs[8];
        return *this;
    }

    mat<3,S>& 
    operator+=(const mat<3,S> &b)
    {
        _v[0] += b[0];
        _v[1] += b[1];
        _v[2] += b[2];
        _v[3] += b[3];
        _v[4] += b[4];
        _v[5] += b[5];
        _v[6] += b[6];
        _v[7] += b[7];
        _v[8] += b[8];
        return *this;
    }

    mat<3,S>& 
    operator-=(const mat<3,S> &b)
    {
        _v[0] -= b[0];
        _v[1] -= b[1];
        _v[2] -= b[2];
        _v[3] -= b[3];
        _v[4] -= b[4];
        _v[5] -= b[5];
        _v[6] -= b[6];
        _v[7] -= b[7];
        _v[8] -= b[8];
        return *this;
    }

    mat<3,S>& 
    operator*=(const S s)
    {
        _v[0] *= s;
        _v[1] *= s;
        _v[2] *= s;
        _v[3] *= s;
        _v[4] *= s;
        _v[5] *= s;
        _v[6] *= s;
        _v[7] *= s;
        _v[8] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<3,S>& 
    operator*=(const mat<3,S> &b)
    {	
        _at(0,0) = a(0,0)*b(0,0) + a(0,1)*b(1,0) + a(0,2)*b(2,0);
        _at(0,1) = a(0,0)*b(0,1) + a(0,1)*b(1,1);
        _at(1,0) = a(1,0)*b(0,0) + a(1,1)*b(1,0);
        _at(1,1) = a(1,0)*b(0,1) + a(1,1)*b(1,1);


        const mat<3,S> a(*this);    // Copy.

        _at(0,0) = a(0,0)*b(0,0) + a(0,1)*b(1,0) + a(0,2)*b(2,0);
        _at(0,1) = a(0,0)*b(0,1) + a(0,1)*b(1,1) + a(0,2)*b(2,1);
        _at(0,2) = a(0,0)*b(0,2) + a(0,1)*b(1,2) + a(0,2)*b(2,2)

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

    //! Return i'th column. No bounds checking!
    S*	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th column. No bounds checking!
    const S*
    operator[](const int64 i) const
    { return _v[i]; }

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

public:		// Operators.

    //! Assignment.
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

    //! Return i'th column. No bounds checking!
    S*	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th column. No bounds checking!
    const S*
    operator[](const int64 i) const
    { return _v[i]; }

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
