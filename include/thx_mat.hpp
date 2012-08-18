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
// --------
//! DOCS

template<int64 N, typename S>
class mat
{
public:

    typedef S value_type;
    static const int64 dim = N;
    static const int64 size = N*N;
    static const mat<N,S> identity;

public:

    //! Default CTOR.
    explicit
    mat(const S x = 1)
    {
        for (int64 i(0); i < N; ++i) {
            for (int64 j(0); j < N; ++j) {
                _v[i + N*j] = ((i == j) ? x : 0); // Set diagonal to value.
            }
        }
    }

    //! Copy CTOR.
    mat(const mat<N,S> &rhs)
    { std::memcpy(_v, rhs._v, size*sizeof(S)); }

public:		// Operators.

    //! Assign.
    mat<N,S>& 
    operator=(const mat<N,S> &rhs)
    {
        std::memcpy(_v, rhs._v, size*sizeof(S));
        return *this;
    }

    mat<N,S>& 
    operator+=(const mat<N,S> &b)
    {
        for (int64 i(0); i < size; ++i) {
            _v[i] += b._v[i];
        }
        return *this;
    }

    mat<N,S>& 
    operator-=(const mat<N,S> &b)
    {
        for (int64 i(0); i < size; ++i) {
            _v[i] -= b._v[i];
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
        const mat<N,S> a(*this);  // Copy.
        for (int64 i(0); i < N; ++i) {
            for (int64 j(0); j < N; ++j) {
                _v[i + N*j] = 0;
                for (int64 k(0); k < N; ++k) {
                    _v[i + N*j] += a[i + N*k]*b[k + N*j];
                }
            }
        }
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + N*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    const S&
    operator()(const int64 i, const int64 j) const
    { return _v[i + N*j]; }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    const S&
    operator[](const int64 i) const
    { return _v[i]; }

private:		// Member variables

    S _v[N*N];  //!< Data.
};

// Static constants.

template<int64 N, typename S>
const mat<N,S> mat<N,S>::identity(1);

//------------------------------------------------------------------------------

// mat<2,S>
// --------
//! DOCS

template<typename S>
class mat<2,S>
{
public:

    typedef S value_type;
    static const int64 dim = 2;
    static const int64 size = 4;
    static const mat<2,S> identity;

public:

    //! Default CTOR.
    explicit
    mat(const S v = 1)
    {
        _v[0] = v; _v[2] = 0;
        _v[1] = 0; _v[3] = v;
    }

    //! Copy CTOR.
    mat(const mat<2,S> &rhs)
    { std::memcpy(_v, rhs._v, 4*sizeof(S)); }

    //! Array CTOR - column-major.
    explicit
    mat(const S v[4])
    { std::memcpy(_v, v, 4*sizeof(S)); }

    //! Value CTOR - column-major.
    explicit
    mat(const S v0, const S v2,
        const S v1, const S v3)
    {	
        _v[0] = v0; _v[2] = v2;
        _v[1] = v1; _v[3] = v3;
    }

public:		// Operators.

    //! Assignment.
    mat<2,S>& 
    operator=(const mat<2,S> &rhs)
    {
        std::memcpy(_v, rhs._v, 4*sizeof(S));
        return *this;
    }

    mat<2,S>& 
    operator+=(const mat<2,S> &b)
    {
        _v[0] += b._v[0]; _v[2] += b._v[2];
        _v[1] += b._v[1]; _v[3] += b._v[3];
        return *this;
    }

    mat<2,S>& 
    operator-=(const mat<2,S> &b)
    {
        _v[0] -= b._v[0]; _v[2] -= b._v[2];
        _v[1] -= b._v[1]; _v[3] -= b._v[3];
        return *this;
    }

    mat<2,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[2] *= s;
        _v[1] *= s; _v[3] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<2,S>& 
    operator*=(const mat<2,S> &b)
    {	
        const mat<2,S> a(*this);
        (*this)(0,0) = a(0,0)*b(0,0) + a(0,1)*b(1,0);
        (*this)(0,1) = a(0,0)*b(0,1) + a(0,1)*b(1,1);
        (*this)(1,0) = a(1,0)*b(0,0) + a(1,1)*b(1,0);
        (*this)(1,1) = a(1,0)*b(0,1) + a(1,1)*b(1,1);
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + 2*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    const S&
    operator()(const int64 i, const int64 j) const
    { return _v[i + 2*j]; }

    //! Return i'th element. No bounds checking!
    S&
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    const S&
    operator[](const int64 i) const
    { return _v[i]; }

private:		// Member variables

    S _v[4];    //!< Data.
};

// Static constants.

template<typename S> 
const mat<2,S> mat<2,S>::identity(1);

//------------------------------------------------------------------------------

// mat<3,S>
// --------
//! DOCS

template<typename S>
class mat<3,S>
{
public:

    typedef S value_type;
    static const int64 dim = 3;
    static const int64 size = 9;
    static const mat<3,S> identity;

public:

    //! Default CTOR.
    explicit
    mat(const S v = 1)
    {
        _v[0] = v; _v[3] = 0; _v[6] = 0;
        _v[1] = 0; _v[4] = v; _v[7] = 0;
        _v[2] = 0; _v[5] = 0; _v[8] = v;
    }

    //! Copy CTOR.
    mat(const mat<3,S> &rhs)
    { std::memcpy(_v, rhs._v, 9*sizeof(S)); }

    //! Array CTOR - column-major.
    explicit
    mat(const S v[9])
    { std::memcpy(_v, v, 9*sizeof(S));	}

    //! Value CTOR - column-major.
    explicit
    mat(const S v0, const S v3, const S v6,
        const S v1, const S v4, const S v7,
        const S v2, const S v5, const S v8)
    {	
        _v[0] = v0; _v[3] = v3; _v[6] = v6;
        _v[1] = v1; _v[4] = v4; _v[7] = v7;
        _v[2] = v2; _v[5] = v5; _v[8] = v8;
    }

public:		// Operators.

    //! Assign.
    mat<3,S>& 
    operator=(const mat<3,S> &rhs)
    {
        std::memcpy(_v, rhs._v, size*sizeof(S));
        return *this;
    }

    mat<3,S>& 
    operator+=(const mat<3,S> &b)
    {
        _v[0] += b._v[0]; _v[3] += b._v[3]; _v[6] += b._v[6];
        _v[1] += b._v[1]; _v[4] += b._v[4]; _v[7] += b._v[7];
        _v[2] += b._v[2]; _v[5] += b._v[5]; _v[8] += b._v[8];
        return *this;
    }

    mat<3,S>& 
    operator-=(const mat<3,S> &b)
    {
        _v[0] -= b._v[0]; _v[3] -= b._v[3]; _v[6] -= b._v[6];
        _v[1] -= b._v[1]; _v[4] -= b._v[4]; _v[7] -= b._v[7];
        _v[2] -= b._v[2]; _v[5] -= b._v[5]; _v[8] -= b._v[8];
        return *this;
    }

    mat<3,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[3] *= s; _v[6] *= s;
        _v[1] *= s; _v[4] *= s; _v[7] *= s;
        _v[2] *= s; _v[5] *= s; _v[8] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<3,S>& 
    operator*=(const mat<3,S> &b)
    {	
        const mat<3,S> a(*this);    // Copy.
        (*this)(0,0) = a(0,0)*b(0,0) + a(0,1)*b(1,0) + a(0,2)*b(2,0);
        (*this)(0,1) = a(0,0)*b(0,1) + a(0,1)*b(1,1) + a(0,2)*b(2,1);
        (*this)(0,2) = a(0,0)*b(0,2) + a(0,1)*b(1,2) + a(0,2)*b(2,2);
        (*this)(1,0) = a(1,0)*b(0,0) + a(1,1)*b(1,0) + a(1,2)*b(2,0);
        (*this)(1,1) = a(1,0)*b(0,1) + a(1,1)*b(1,1) + a(1,2)*b(2,1);
        (*this)(1,2) = a(1,0)*b(0,2) + a(1,1)*b(1,2) + a(1,2)*b(2,2);
        (*this)(2,0) = a(2,0)*b(0,0) + a(2,1)*b(1,0) + a(2,2)*b(2,0);
        (*this)(2,1) = a(2,0)*b(0,1) + a(2,1)*b(1,1) + a(2,2)*b(2,1);
        (*this)(2,2) = a(2,0)*b(0,2) + a(2,1)*b(1,2) + a(2,2)*b(2,2);
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + 3*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    const S&
    operator()(const int64 i, const int64 j) const
    { return _v[i + 3*j]; }

    //! Return i'th element. No bounds checking!
    S&	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    const S&
    operator[](const int64 i) const
    { return _v[i]; }

private:		// Member variables.

    S _v[9];    //!< Data.
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
    static const int64 size = 16;
    static const mat<4,S> identity;

public:

    //! Default CTOR.
    explicit
    mat(const S v = 1)
    {
        _v[0] = v; _v[4] = 0; _v[8]  = 0; _v[12] = 0;
        _v[1] = 0; _v[5] = v; _v[9]  = 0; _v[13] = 0;
        _v[2] = 0; _v[6] = 0; _v[10] = v; _v[14] = 0;
        _v[3] = 0; _v[7] = 0; _v[11] = 0; _v[15] = v;
    }

    //! Copy CTOR.
    mat(const mat<4,S> &rhs)
    { std::memcpy(_v, rhs._v, 16*sizeof(S)); }

    //! Array CTOR - column major.
    explicit
    mat(const S v[16])
    { std::memcpy(_v, rhs._v, 16*sizeof(S)); }

    //! Value CTOR - column major.
    explicit
    mat(const S v0, const S v4, const S v8,  const S v12,
        const S v1, const S v5, const S v9,  const S v13,
        const S v2, const S v6, const S v10, const S v14,
        const S v3, const S v7, const S v11, const S v15)
    {	
        _v[0] = v0; _v[4] = v4; _v[8]  = v8;  _v[12] = v12;
        _v[1] = v1; _v[5] = v5; _v[9]  = v9;  _v[13] = v13;
        _v[2] = v2; _v[6] = v6; _v[10] = v10; _v[14] = v14;
        _v[3] = v3; _v[7] = v7; _v[11] = v11; _v[15] = v15;
    }

public:		// Operators.

    //! Assign.
    mat<4,S>& 
    operator=(const mat<4,S> &rhs)
    {
        std::memcpy(_v, rhs._v, size*sizeof(S));
        return *this;
    }

    mat<4,S>& 
    operator+=(const mat<4,S> &b)
    {
        _v[0]+=b._v[0]; _v[4]+=b._v[4]; _v[8] +=b._v[8];  _v[12]+=b._v[12];
        _v[1]+=b._v[1]; _v[5]+=b._v[5]; _v[9] +=b._v[9];  _v[13]+=b._v[13];
        _v[2]+=b._v[2]; _v[6]+=b._v[6]; _v[10]+=b._v[10]; _v[14]+=b._v[14];
        _v[3]+=b._v[3]; _v[7]+=b._v[7]; _v[11]+=b._v[11]; _v[15]+=b._v[15];
        return *this;
    }

    mat<4,S>& 
    operator-=(const mat<4,S> &b)
    {
        _v[0]-=b._v[0]; _v[4]-=b._v[4]; _v[8] -=b._v[8];  _v[12]-=b._v[12];
        _v[1]-=b._v[1]; _v[5]-=b._v[5]; _v[9] -=b._v[9];  _v[13]-=b._v[13];
        _v[2]-=b._v[2]; _v[6]-=b._v[6]; _v[10]-=b._v[10]; _v[14]-=b._v[14];
        _v[3]-=b._v[3]; _v[7]-=b._v[7]; _v[11]-=b._v[11]; _v[15]-=b._v[15];
        return *this;
    }

    mat<4,S>& 
    operator*=(const S s)
    {
        _v[0] *= s; _v[4] *= s; _v[8]  *= s; _v[12] *= s;
        _v[1] *= s; _v[5] *= s; _v[9]  *= s; _v[13] *= s;
        _v[2] *= s; _v[6] *= s; _v[10] *= s; _v[14] *= s;
        _v[3] *= s; _v[7] *= s; _v[11] *= s; _v[15] *= s;
        return *this;
    }

    //! Matrix multiplication.
    mat<4,S>&
    operator*=(const mat<4,S> &b)
    {	
        const mat<4,S> a(*this);    // Copy.
        (*this)(0,0) = a(0,0)*b(0,0)+a(0,1)*b(1,0)+a(0,2)*b(2,0)+a(0,3)*b(3,0);
        (*this)(0,1) = a(0,0)*b(0,1)+a(0,1)*b(1,1)+a(0,2)*b(2,1)+a(0,3)*b(3,1);
        (*this)(0,2) = a(0,0)*b(0,2)+a(0,1)*b(1,2)+a(0,2)*b(2,2)+a(0,3)*b(3,2);
        (*this)(0,3) = a(0,0)*b(0,3)+a(0,1)*b(1,3)+a(0,2)*b(2,3)+a(0,3)*b(3,3);
        (*this)(1,0) = a(1,0)*b(0,0)+a(1,1)*b(1,0)+a(1,2)*b(2,0)+a(1,3)*b(3,0);
        (*this)(1,1) = a(1,0)*b(0,1)+a(1,1)*b(1,1)+a(1,2)*b(2,1)+a(1,3)*b(3,1);
        (*this)(1,2) = a(1,0)*b(0,2)+a(1,1)*b(1,2)+a(1,2)*b(2,2)+a(1,3)*b(3,2);
        (*this)(1,3) = a(1,0)*b(0,3)+a(1,1)*b(1,3)+a(1,2)*b(2,3)+a(1,3)*b(3,3);
        (*this)(2,0) = a(2,0)*b(0,0)+a(2,1)*b(1,0)+a(2,2)*b(2,0)+a(2,3)*b(3,0);
        (*this)(2,1) = a(2,0)*b(0,1)+a(2,1)*b(1,1)+a(2,2)*b(2,1)+a(2,3)*b(3,1);
        (*this)(2,2) = a(2,0)*b(0,2)+a(2,1)*b(1,2)+a(2,2)*b(2,2)+a(2,3)*b(3,2);
        (*this)(2,3) = a(2,0)*b(0,3)+a(2,1)*b(1,3)+a(2,2)*b(2,3)+a(2,3)*b(3,3);
        (*this)(3,0) = a(3,0)*b(0,0)+a(3,1)*b(1,0)+a(3,2)*b(2,0)+a(3,3)*b(3,0);
        (*this)(3,1) = a(3,0)*b(0,1)+a(3,1)*b(1,1)+a(3,2)*b(2,1)+a(3,3)*b(3,1);
        (*this)(3,2) = a(3,0)*b(0,2)+a(3,1)*b(1,2)+a(3,2)*b(2,2)+a(3,3)*b(3,2);
        (*this)(3,3) = a(3,0)*b(0,3)+a(3,1)*b(1,3)+a(3,2)*b(2,3)+a(3,3)*b(3,3);
        return *this;
    }

public:     // Access operators.

    //! Return element at row 'i' and column 'j'. No bounds checking!
    S&
    operator()(const int64 i, const int64 j)
    { return _v[i + 4*j]; }

    //! Return element at row 'i' and column 'j'. No bounds checking!
    const S&
    operator()(const int64 i, const int64 j) const
    { return _v[i + 4*j]; }

    //! Return i'th element. No bounds checking!
    S&	
    operator[](const int64 i)
    { return _v[i]; }

    //! Return i'th element. No bounds checking!
    const S&
    operator[](const int64 i) const
    { return _v[i]; }

private:		// Member variables.

    S _v[16];   //!< Data.
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

//------------------------------------------------------------------------------

namespace std
{

//! Binary operator: std::ostream << mat<N,S>
template<thx::int64 N, typename S>
ostream&
operator<<(ostream &os, const thx::mat<N,S> &rhs)
{
    for(thx::int64 i = 0; i < N; ++i) {
        os	<< "[";
        for (thx::int64 j = 0; j < N; ++j) {
            os << rhs(i,j) << (j != (N - 1) ? ", " : "");
        }
        os << "]\n";
    }
    //os.flags(f0);
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// THX_MAT_HPP_INCLUDED
